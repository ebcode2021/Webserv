#include "webserv.hpp"
#include "Config.hpp"
#include "KqueueHandler.hpp"
#include "SocketEventHandler.hpp"
#include "HttpResponse.hpp"
#include "HttpValidator.hpp"

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

int main(int argc, char *argv[])
{
	(void)argc;
	
	if (1) //Config::fileCheck(argc, argv))
	{
		Config config(argv[1]);
		//config.printServerList();

		// fd 늘리는 로직 추가

		// create_listen_sock(); // linten sock read event 등록 
		// openListenSockets(config, kq);

		// 이벤트에 대한 정보(Read, Write, Add, Delete)를 저장하는 vector
		std::vector<struct kevent>	changeList;
		std::set<int>				listenSockList;
		KqueueHandler				kqHandler;
		SocketEventHandler			sockEventHandler;
		
		
		// 여기 for문  openListenSockets(config, changeList);

		int listenSock = createSocket();
		TcpSocket *listenSocket = new TcpSocket(listenSock);
		listenSocket->socketBind(9999);
		listenSocket->socketListen();
		listenSocket->changeToNonblocking();
		listenSockList.insert(listenSock);
		kqHandler.changeEvent(listenSocket->getSockFd(), EVFILT_READ, EV_ADD, 0, 0, listenSocket);

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
					if (listenSockList.find(curEvent.ident) != listenSockList.end())
					{
						int clientSock = sockEventHandler.socketAccept();
						if (clientSock == INVALID_SOCKET) {
							printErrorWithExit(strerror(errno));
						}
						TcpSocket *clientSocket = new TcpSocket(clientSock);
						clientSocket->changeToNonblocking();
						kqHandler.changeEvent(clientSock, EVFILT_READ, EV_ADD, 0, 0, clientSocket);
					}
					else {
						std::cout << "read fd = " << curSock->getSockFd() << std::endl;
						int ret = sockEventHandler.dataRecv();
						std::cout << "============body=============" << std::endl;
						std::cout << curSock->getString() << std::endl;
						std::cout << "============body=============" << std::endl;
						if (ret == -1) {
							std::cout << strerror(errno) << std::endl;
							printErrorWithExit("error: recv()");
						}
						else if (ret == 0) {
							std::cout << "close fd = " << curSock->getSockFd() << std::endl;
							sockEventHandler.closeSocket();
						}
						else {
							if (curSock->getReadMode() == HEADER) {
								curSock->setRequestHeader();
								if (curSock->getRequest().getHttpRequestLine().getMethod() == "GET")
									curSock->setReadMode(END);
								else if (curSock->getRequest().getHttpRequestHeader().getTransferEncoding() == "chunked")
									curSock->setReadMode(CHUNKED);
								else
									curSock->setReadMode(IDENTITY);
							}
							std::cout << curSock->getRequest().toString() << std::endl;
							if (curSock->getReadMode() != END)
								curSock->setRequestBody();
							if (curSock->getReadMode() == END)
							{
								// [은비 추가 코드] ************************
								// response 생성자에서 처리.
								//HttpResponse response(config, curSock->getRequest());
								//curSock->setResponse(response);
							//if (curSock->getReadMode() == HEADER)
							//curSock->setRequestHeader(); // << 내부에 curSock->changeReadMode()
							//else if (curSock->getReadMode() == POST)
							//curSock->setRequestBody();
							
							std::cout << curSock->getRequest().toString() << std::endl;
							{
								////////////////////////////
								std::cout << "--------------------------" << std::endl;
								HttpResponse response = HttpResponse::createResponse(config, curSock->getRequest());
								curSock->setResponse(response);
								// /HttpPage httpPage = HttpHandler::setPageFromConfigAndRequest(config, httpRequest);
							
								kqHandler.changeEvent(curSock->getSockFd(), EVFILT_WRITE, EV_ADD, 0, 0, curSock);
							}
							}
						}
				}
				else if (curEvent.filter == EVFILT_WRITE)
				{
					std::cout << "write fd = " << curSock->getSockFd() << std::endl;
					// 맞는 response 내보내게끔
					int sendsize = sockEventHandler.dataSend();
					kqHandler.changeEvent(curSock->getSockFd(), EVFILT_WRITE, EV_DELETE, 0, 0, curSock);
					if (sendsize == -1) {
						printErrorWithExit(strerror(errno));
					}
					// std::cout << "close fd = " << curSock->getSockFd() << std::endl;
					// sockEventHandler.closeSocket();
				}
			} 
		}
	}
	return (0);
}