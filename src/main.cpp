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
						if (sockEventHandler.dataRecv() <= 0) 
							sockEventHandler.closeSocket();
						else 
						{
							if (curSock->getReadMode() == HEADER) 
							{
								curSock->setRequestHeader();
								curSock->changeReadMode();
								curSock->printRequestInfo();
							}
							if (curSock->getReadMode() != END)
								curSock->setRequestBody();
							if (curSock->getReadMode() == END)
							{
								std::cout << "--------------------------" << std::endl;
								HttpResponse response = HttpResponse::createResponse(config, curSock->getRequest());
							//	response.printHttpResponse();
								curSock->setResponse(response);
								//curSock->getResponse().printHttpResponse();
								kqHandler.changeEvent(curSock->getSockFd(), EVFILT_WRITE, EV_ADD, 0, 0, curSock);
							}
						}
					}
				}
				else if (curEvent.filter == EVFILT_WRITE)
				{
					int sendsize = sockEventHandler.dataSend();
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