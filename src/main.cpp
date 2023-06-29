#include "webserv.hpp"
#include "Config.hpp"
#include "KqueueHandler.hpp"
#include "SocketEventHandler.hpp"
#include "HttpResponse.hpp"
#include "SessionStorage.hpp"
#include "CgiMetadata.hpp"


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

void	changeOpt(int fd, int option) {
	int flags = fcntl(fd, F_GETFL, 0);
	flags |= option;
	fcntl(fd, F_SETFL, flags);
}

void cgi_test(TcpSocket* sock, KqueueHandler &kq) {

	HttpRequest request = sock->getRequest();
	CgiMetadata data(request);
	//char **envp = data.createEnvp();

	int pipefd[2];
	pipe(pipefd);
	pid_t pid = fork();

	if (pid == 0) {
		dup2(pipefd[0], STDIN_FILENO);
		//dup2(pipefd[1], STDOUT_FILENO);
		std::string requestUrl = request.getHttpRequestLine().getRequestURI();
		std::string path = ROOT_PATH + requestUrl.substr(1, requestUrl.size());
		char *argv[] = {strdup(path.c_str()), NULL};
		execve(CGI_PATH.c_str(), argv, data.createEnvp());
		std::cout << path << std::endl;
		exit(1);
	}
	else {
		changeOpt(pipefd[0], O_NONBLOCK);
		changeOpt(pipefd[1], O_NONBLOCK);
		sock->setCgiInfo(new CgiInfo(pid, pipefd[0], pipefd[1]));
		sock->setSendMode(PROCESS);
		kq.changeEvent(sock->getCgiInfo()->getWriteFd(), EVFILT_WRITE, EV_ADD, 0, 0, sock);
		kq.changeEvent(sock->getCgiInfo()->getPid(), EVFILT_PROC, EV_ADD, NOTE_EXIT, 0, sock);
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
					// kq에 sock을 read-event로 등록
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
								// kq에 write event로 등록
								kqHandler.changeEvent(curSock->getSockFd(), EVFILT_WRITE, EV_ADD, 0, 0, curSock);
							}
						}
					}
				}
			}
			else if (isWriteEvent(curEvent.filter) == true)
			{
				//curSock->getResponse().printHttpResponse();
				// response 재료는. 만드는거고.
				
				int sendbyte = 0;
				if (curSock->getSendMode() == CLIENT)
					sendbyte = sockEventHandler.dataSend();
				else if (curSock->getSendMode() == PROCESS)
					sendbyte = write(curSock->getCgiInfo()->getWriteFd(), curSock->getBufToCStr(), curSock->getBufSize());
	// wait.
				if (sendbyte == -1) 
					sockEventHandler.closeSocket();
				else if (curSock->getBufSize() > static_cast<size_t>(sendbyte))
					curSock->bufTrim(sendbyte);
				else {
					
					if (curSock->getSendMode() == CLIENT) {
						if (curSock->getRequest().getHttpRequestHeader().getConnection() != "keep-alive")
							sockEventHandler.closeSocket();
						else {
							curSock->resetInfo();
							kqHandler.changeEvent(curSock->getSockFd(), EVFILT_WRITE, EV_DELETE, 0, 0, curSock);
						}
					}
					else if (curSock->getSendMode() == PROCESS) {
						close(curSock->getCgiInfo()->getWriteFd());
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
