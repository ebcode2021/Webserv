#include "webserv.hpp"
#include "Config.hpp"
#include "KqueueHandler.hpp"
#include "SocketEventHandler.hpp"
#include "HttpResponse.hpp"

// 요청 라인 분석해서 메서드와 url 확인
// 요청이 url이 cgi 인지 확인
// cgi이면 fork()후에 표준출력으로 데이터 전달 표준 입력으로 데이터 받기
// cgi 프로그램에서는 표준입력으로 body데이터 받아서 html 생성 후 표준출력으로 데이터 전달
// cgi 에서 받은 데이터를 클라이언트로 전달

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
	SocketEventHandler sockEventHandler;
	std::set<int> listenSockList = config.getListenSockList(); 
	for (std::set<int>::iterator it = listenSockList.begin(); it != listenSockList.end(); it++)
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


void cgi_test(TcpSocket* sock) {
	HttpRequest request = sock->getRequest();

	std::string REQUEST_METHOD = request.getHttpRequestLine().getMethod();
	std::string CONTENT_TYPE = request.getHttpRequestHeader().getContentType();
	std::string CONTENT_LENGTH = itos(request.getHttpRequestHeader().getContentLength());
	std::string SERVER_PROTOCOL = "HTTP/1.1";
	std::string PATH_INFO = "/Users/minsukan/Desktop/42/webserv/Webserv/resources/fileUpLoad";
	
	std::cout << CONTENT_LENGTH << std::endl;
	std::cout << sock->getBufSzie() << std::endl;
	
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
		setenv()

		execv("/Users/minsukan/Desktop/42/webserv/Webserv/cgi_tester", 0);
		exit(1);
	}
	else {
		dup2(pipefd[1], STDOUT_FILENO);
		write(STDOUT_FILENO, sock->getBufToCStr(), sock->getBufSzie());
	}
	dup2(STDOUT_FILENO, stdoutbackup);
	wait(0);
	//std::cout << "프로세스 종료?" << std::endl;
}

int main(int argc, char *argv[])
{
	(void)argc;

	if (1) //Config::fileCheck(argc, argv))
	{
		Config config(argv[1]);
		std::vector<struct kevent>	changeList;
		std::set<int>				listenSockFdList;
		KqueueHandler				kqHandler;
		SocketEventHandler			sockEventHandler;
		
		initListenSocket(kqHandler, config, listenSockFdList);
		while(1)
		{
			kqHandler.eventListReset();
			kqHandler.waitEvent();
			kqHandler.changeListClear();
			for (int i = 0; i < kqHandler.getEventCnt(); i++)
			{
				struct kevent curEvent = kqHandler.getCurEventByIndex(i);
				TcpSocket *curSock = (TcpSocket *)curEvent.udata;

				sockEventHandler.setSocket(curSock);
				if (curEvent.filter == EVFILT_READ)
				{
					
					if (listenSockFdList.find(curEvent.ident) != listenSockFdList.end())
					{
						int clientSock = sockEventHandler.socketAccept();
						if (clientSock == INVALID_SOCKET) {
							continue ;
						}
						TcpSocket *clientSocket = new TcpSocket(clientSock);
						clientSocket->changeToNonblocking();
						kqHandler.changeEvent(clientSock, EVFILT_READ, EV_ADD, 0, 0, clientSocket);
					}
					else 
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

								// test code
								if (curSock->getRequest().getHttpRequestLine().getMethod() == "POST") {
									cgi_test(curSock);
									//exit(1);
								}
								else {
									HttpResponse response = HttpResponse::createResponse(config, curSock->getRequest());
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
				else if (curEvent.filter == EVFILT_WRITE)
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