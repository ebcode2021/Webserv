#include "webserv.hpp"
#include "Config.hpp"
#include "KqueueHandler.hpp"
#include "SocketEventHandler.hpp"
#include "HttpResponse.hpp"

int createSocket()
{
	int	sock = socket(AF_INET, SOCK_STREAM, 0);
	int option = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) < 0) {
        std::cout << "setsockopt error" << std::endl;
    }
	if (sock == INVALID_SOCKET)
		printErrorWithExit("배고파");
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

void cgi_test(TcpSocket* sock) {
	HttpRequest request = sock->getRequest();

	std::string REQUEST_METHOD = request.getHttpRequestLine().getMethod();
	std::string CONTENT_TYPE = request.getHttpRequestHeader().getContentType();
	std::string CONTENT_LENGTH = itos(request.getHttpRequestHeader().getContentLength());
	std::string SERVER_PROTOCOL = "HTTP/1.1";
	std::string PATH_INFO = "/Users/minsukan/Desktop/42/webserv/Webserv/resources/fileUpLoad";
	
	std::cout << CONTENT_LENGTH << std::endl;
	std::cout << sock->getBufSize() << std::endl;
	
	int pipefd[2];
	pipe(pipefd);

	//int stdinbackup = dup(STDIN_FILENO);
	int stdoutbackup = dup(STDOUT_FILENO);
	

	pid_t pid = fork();
	if (pid == 0) {
		dup2(pipefd[0], STDIN_FILENO);

		setenv("REQUEST_METHOD", REQUEST_METHOD.c_str(), 1);
		setenv("CONTENT_TYPE", CONTENT_TYPE.c_str(), 1);
		setenv("CONTENT_LENGTH", CONTENT_LENGTH.c_str(), 1);
		setenv("SERVER_PROTOCOL", SERVER_PROTOCOL.c_str(), 1);
		setenv("PATH_INFO", PATH_INFO.c_str(), 1);

		execv("/Users/minsukan/Desktop/42/webserv/Webserv/cgi_tester", 0);
		exit(1);
	}
	else {
		dup2(pipefd[1], STDOUT_FILENO);
		write(STDOUT_FILENO, sock->getBufToCStr(), sock->getBufSize());
	}
	dup2(STDOUT_FILENO, stdoutbackup);
	wait(0);
	//std::cout << "프로세스 종료?" << std::endl;
}

int main(int argc, char *argv[])
{
	(void)argc;

	if (Config::fileCheck(argc, argv))
	{
		Config config(argv[1]);
		std::vector<struct kevent>	changeList;
		std::set<int>				listenSockFdList;
		KqueueHandler				kqHandler;
		SocketEventHandler			sockEventHandler;
		
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
						int clientSock = sockEventHandler.socketAccept(); // 새로운 클라이언트
						if (clientSock == INVALID_SOCKET)
							continue ;
						TcpSocket *clientSocket = new TcpSocket(clientSock);
						kqHandler.changeEvent(clientSock, EVFILT_READ, EV_ADD, 0, 0, clientSocket); // udata에는 클라이언트 소켓 정보.(udata)
					}
					else // client 소켓이면
					{
						if (sockEventHandler.dataRecv() <= 0) {
							sockEventHandler.closeSocket();
						}
						else 
						{
							if (curSock->getReadMode() == HEADER) 
							{
								std::cout << curSock->getBuf() << std::endl;
								curSock->setRequestHeader();
								curSock->changeReadMode();
							}
							if (curSock->getReadMode() != END)
								curSock->setRequestBody();
							if (curSock->getReadMode() == END)
							{
								std::cout << "--------------------------" << std::endl;
								HttpResponse response = HttpResponse::createResponse(config, curSock->getRequest(), curSock->getClientAddr());
								
								curSock->setResponse(response);

								// test code
								if (curSock->getRequest().getHttpRequestLine().getMethod() == "POST") {
									cgi_test(curSock);
									//exit(1);
								}
								else {
									HttpResponse response = HttpResponse::createResponse(config, curSock->getRequest(), curSock->getClientAddr());
								//	response.printHttpResponse();
									curSock->setResponse(response);
								}
								//
								
								//curSock->getResponse().printHttpResponse();
								kqHandler.changeEvent(curSock->getSockFd(), EVFILT_WRITE, EV_ADD, 0, 0, curSock);
							}
						}
					}
				}
				else if (isWriteEvent(curEvent.filter) == true)
				{
					int sendsize = sockEventHandler.dataSend();
					curSock->bufClear();
					curSock->setReadMode(HEADER);
					sendsize = 10;
					kqHandler.changeEvent(curSock->getSockFd(), EVFILT_WRITE, EV_DELETE, 0, 0, curSock);
					if (sendsize == -1 || curSock->getRequest().getHttpRequestHeader().getConnection() == "close") 
						sockEventHandler.closeSocket();
				}
			}
		}
		return (0);
	}
}