#include "webserv.hpp"
#include "Config.hpp"
#include "KqueueHandler.hpp"
#include "SocketEventHandler.hpp"
#include "HttpResponse.hpp"
#include "SessionStorage.hpp"


/*
	https일경우 리퀘스트 요청이 암호화되서 전송되기때문에 header파싱 부분에서 segfault에러
	send데이터가 큰경우 처리
	send udata확인해서 cgi에 데이터보내기
	포트 적용잘안되는거 확인
	썬더브라우저에서 connection 요청 보냈을경우
	content type 파싱 다시
*/

int createSocket()
{
	int	sock = socket(AF_INET, SOCK_STREAM, 0);
	int option = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) < 0) {
        printErrorWithExit(strerror(errno));
    }
	if (sock == INVALID_SOCKET)
		printErrorWithExit(strerror(errno));
	return (sock);
}

void initListenSocket(KqueueHandler &kqHandler, Config &config, std::set<int> &listenSockFdList) 
{
	SocketEventHandler		sockEventHandler;
	std::set<int>			listenSockList = config.getListenSockList(); 
	std::set<int>::iterator	it;

	for (it = listenSockList.begin(); it != listenSockList.end(); it++)
	{
		int listenSockFd = createSocket();
		if (listenSockFd == INVALID_SOCKET) {
			printErrorWithExit(strerror(errno));
		}
		TcpSocket *listenSock = new TcpSocket(listenSockFd);
		sockEventHandler.setSocket(listenSock);

		if (sockEventHandler.sockBind(*it) < 0)
			printErrorWithExit(strerror(errno));
		
		if (sockEventHandler.sockListen())
			printErrorWithExit(strerror(errno));
		
		listenSock->changeToNonblocking();
		kqHandler.changeEvent(listenSockFd, EVFILT_READ, EV_ADD, 0, 0, listenSock);
		listenSockFdList.insert(listenSockFd);
	}
}

bool	isListenSocketEvent(std::set<int>&	list, uintptr_t& event)
{
	return (list.find(event) != list.end());
}

bool	isReadEvent(int16_t& event)
{
	return (event == EVFILT_READ);
}

bool	isWriteEvent(int16_t& event)
{
	return (event == EVFILT_WRITE);
}

bool	isProcEvent(int16_t& event)
{
	return (event == EVFILT_PROC);
}



void cgi_test(TcpSocket* sock, KqueueHandler &kq) {
	HttpRequest request = sock->getRequest();

	///
	std::string REQUEST_METHOD = request.getHttpRequestLine().getMethod();
	std::string CONTENT_TYPE = request.getHttpRequestHeader().getContentType();
	std::string CONTENT_LENGTH = itos(request.getHttpRequestHeader().getContentLength());
	std::string SERVER_PROTOCOL = HTTP_VERSION;
	std::string PATH_INFO = "/Users/minsu/Desktop/42seoul/webserv/";
	///
	int pipefd[2];
	pipe(pipefd);
	pid_t pid = fork();

	if (pid == 0) {
		dup2(pipefd[0], STDIN_FILENO);
		setenv("REQUEST_METHOD", REQUEST_METHOD.c_str(), 1);
		setenv("CONTENT_TYPE", CONTENT_TYPE.c_str(), 1);
		setenv("CONTENT_LENGTH", CONTENT_LENGTH.c_str(), 1);
		setenv("SERVER_PROTOCOL", SERVER_PROTOCOL.c_str(), 1);
		setenv("PATH_INFO", PATH_INFO.c_str(), 1);

		setenv("SCRIPT_NAME", "upload.php", 1);
		setenv("SCRIPT_FILENAME", "upload.php", 1);
		setenv("REDIRECT_STATUS", "200", 1);
		
		//const char *argv[3] = {"/usr/bin/python3", "/Users/minsu/Desktop/42seoul/webserv/hello_cgi.py", NULL};
		//execv("/usr/bin/python3", (char**)argv);
		execv("/Users/minsu/Desktop/42seoul/webserv/php-cgi", NULL);
		exit(1);
	}
	else {
		// int sendbyte = 0;
		// while (true)
		// {
		//  	int readbyte = write(pipefd[1], sock->getBufToCStr() + sendbyte, sock->getBufSize() - sendbyte);
		// 	std::cerr << "readbyte = " << readbyte << std::endl;
		// 	if (readbyte == -1)
		// 		continue ;
		// 	else if (readbyte == 0)
		// 		break ;
		// 	else
		// 		sendbyte += readbyte;
		// }
		TcpSocket *newSock = new TcpSocket(pipefd[1]);
		newSock->setBuf(sock->getBuf());
		newSock->setSendMode(CGI);
		sock->bufClear();
		kq.changeEvent(pipefd[1], EVFILT_WRITE, EV_ADD, 0, 0, newSock);
		kq.changeEvent(pid, EVFILT_PROC, EV_ADD, NOTE_EXIT, 0, sock);
	}
}

int main(int argc, char *argv[])
{
	(void)argc;
	//Config::fileCheck(argc, argv);

	Config	config(argv[1]);

	std::cout << "server start" << std::endl;

	std::set<int>				listenSockFdList;
	KqueueHandler				kqHandler;
	SocketEventHandler			sockEventHandler;
	SessionStorage				sessionStorage;
	
	initListenSocket(kqHandler, config, listenSockFdList);

	while(1)
	{
		kqHandler.initialize();

		for (int i = 0; i < kqHandler.getEventCnt(); i++)
		{
			struct kevent curEvent = kqHandler.getCurEventByIndex(i);
			
			TcpSocket *curSock = (TcpSocket *)curEvent.udata;
			sockEventHandler.setSocket(curSock); // 소켓 -> 이벤트 처리

			if (isReadEvent(curEvent.filter) == true)
			{
				if (isListenSocketEvent(listenSockFdList, curEvent.ident) == true)
				{
					int clientSock = sockEventHandler.sockAccept(); // 새로운 클라이언트
					if (clientSock == INVALID_SOCKET)
						continue ;
					TcpSocket *clientSocket = new TcpSocket(clientSock);
					kqHandler.changeEvent(clientSock, EVFILT_READ, EV_ADD, 0, 0, clientSocket); // udata에는 클라이언트 소켓 정보.(udata)
				}
				else // client 소켓이면
				{
					if (sockEventHandler.dataRecv() <= 0)
						sockEventHandler.closeSocket();
					else 
					{
						if (curSock->getReadMode() == HEADER) 
						{
							curSock->setRequestHeader();
							curSock->changeReadMode();
							//curSock->getRequest().printInfo();
						}
						if (curSock->getReadMode() != END)
							curSock->setRequestBody();
						if (curSock->getReadMode() == END)
						{
							if (curSock->getRequest().getHttpRequestLine().getMethod() == "POST") {
								cgi_test(curSock, kqHandler);
							}
							else
							{
								HttpResponse response = HttpResponse::createResponse(config, curSock->getRequest(), curSock->getClientAddr(), sessionStorage);
								std::string reqURL = curSock->getRequest().getHttpRequestLine().getRequestURI();
								std::string sessionId = curSock->getRequest().getHttpRequestHeader().getSessionIdByCookie();

								if (reqURL != "/favicon.ico")
								{
									if (sessionStorage.isSession(sessionId) == true)
										response.getResponseHeader().setSetCookie("sessionId=" + sessionId);
									else
									{
										HttpSession	session(reqURL);
										sessionStorage.addSession(session);
										response.getResponseHeader().setSetCookie("sessionId=" + session.getSessionId());
										//session.printInfo();
									}
								}
								curSock->setResponse(response);
								curSock->setBuf(curSock->getResponse().getResponseToString());
								kqHandler.changeEvent(curSock->getSockFd(), EVFILT_WRITE, EV_ADD, 0, 0, curSock);
							}
						}
					}
				}
			}
			else if (isWriteEvent(curEvent.filter) == true)
			{
				//curSock->getResponse().printHttpResponse();
				int sendbyte;
				if (curSock->getSendMode() == SOCKET)
					sendbyte = sockEventHandler.dataSend();
				else
					sendbyte = write(curSock->getSockFd(), curSock->getBufToCStr(), curSock->getBufSize());
				if (sendbyte == -1) 
					sockEventHandler.closeSocket();
				else if (curSock->getBufSize() > static_cast<size_t>(sendbyte)) 
					curSock->bufTrim(sendbyte);
				else {
					if (curSock->getRequest().getHttpRequestHeader().getConnection() != "keep-alive")
						sockEventHandler.closeSocket();
					else {
						curSock->resetInfo();
						kqHandler.changeEvent(curSock->getSockFd(), EVFILT_WRITE, EV_DELETE, 0, 0, curSock);
					}
				}
			}
			else if (isProcEvent(curEvent.filter) == true)
			{
				std::cout << "자식 종료 감지 성공" << std::endl;
			}
		}
	}
	return (0);
}
