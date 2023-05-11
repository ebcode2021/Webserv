#include "webserv.hpp"
#include "Config.hpp"
#include "KqueueHandler.hpp"

/*
	[남은거?]
	1) fileCheck 공사 ->(get, post, delete ... limitExcept) -> 은비

	2) HTTP parsing

	4) 3) 한 후에 클래스 분리 (내일 끝내기)

	5) CGI(py, php) -> 같이 공부하면 좋겠어
	6) html 간단하게 사진 넣기 (은비 심심하면 요령껏...)
	7) 쿠키, 세션
*/

// 요청 라인 분석해서 메서드와 url 확인
// 요청이 url이 cgi 인지 확인
// cgi이면 fork()후에 표준출력으로 데이터 전달 표준 입력으로 데이터 받기
// cgi 프로그램에서는 표준입력으로 body데이터 받아서 html 생성 후 표준출력으로 데이터 전달
// cgi 에서 받은 데이터를 클라이언트로 전달

int createSocket()
{
	int	sock = socket(AF_INET, SOCK_STREAM, 0);

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
		
		int kq = kqueue(); // kqueue
		// 여기 for문  openListenSockets(config, changeList);

		int listenSock = createSocket();
		TcpSocket listenSocket(listenSock);
		listenSocket.socketBind(1234);
		listenSocket.socketListen();
		listenSocket.changeToNonblocking();
		listenSockList.insert(listenSock);
		struct kevent kev;
		EV_SET(&kev, listenSocket.getSockFd(), EVFILT_READ, EV_ADD, 0, 0, &listenSocket);
		changeList.push_back(kev);
	
		while(1)
		{
			struct kevent eventList[FD_SETSIZE];
			int eventCnt = kqHandler.waitEvent();
			kqHandler.changeListClear();

			for (int i = 0; i < eventCnt; i++)
			{
				struct kevent curEvent = kqHandler.getCurEventByIndex(i);
				TcpSocket *curSocket = (TcpSocket *)curEvent.udata;

				if (curEvent.filter == EVFILT_READ)  // 현재 발생한 이벤트가 read일 경우
				{
					std::cout << "읽기 이벤트 발생" << std::endl;
					if (listenSockList.find(curEvent.ident) != listenSockList.end()) // listen port일 경우
					{
						int clientSock = curSocketInfo->socketAccept();
						if (clientSock == INVALID_SOCKET) {
							printErrorWithExit("error : accept()");
						}
						TcpSocket clientSocket(clientSock);
						clientSocket.changeToNonblocking();

						EV_SET(&kev, clientSocket.getSockFd(), EVFILT_READ, EV_ADD, 0, 0, &clientSocket);
						changeList.push_back(kev);
						// EV_SET(&kev, clientSocket.getSockFd(), EVFILT_WRITE, EV_ADD, 0, 0, &clientSocket);
						// changeList.push_back(kev);
					}
					else {
						int readSize = recv(curEvent.ident, curSocketInfo->getBuf(), BUFSIZE + 1, 0);

						if (readSize == -1) {
							printErrorWithExit("error: read()");
						}
						else if (readSize == 0) {
							close(curEvent.ident);
						}
						else {
							char *curBuf = curSocketInfo->getBuf();
							curBuf[readSize] = '\0';
							std::cout << curSocketInfo->getBuf() << std::endl;
							EV_SET(&kev, curEvent.ident, EVFILT_WRITE, EV_ENABLE, 0, 0, curSocketInfo);
							changeList.push_back(kev);
						}
					}
				}
				else if (curEvent.filter == EVFILT_WRITE) // write 일 경우
				{
					std::cout << "쓰기 이벤트 발생" << std::endl;
					std::cout << "data check" << curSocketInfo->getBuf() << std::endl;
					send(curEvent.ident, curSocketInfo->getBuf(), std::strlen(curSocketInfo->getBuf()), 0);
					EV_SET(&kev, curEvent.ident, EVFILT_WRITE, EV_DISABLE, 0, 0, curSocketInfo);
					changeList.push_back(kev);
				}
				else
				{
					std::cerr << "뭔가 많이 잘못됬음" << std::endl;
					exit(1);
				}
			} 
		}
	}
	return 0;
}


		// for (1;1;1;) {
		// 	TcpSocket listenSocket(createSocket());
		// 	listenSocket.bind(port);
		// 	listenSocket.listen();
		// 	listenSocket.changeToNonblocking();
		// 	// kqueue에 이벤트 등록
		// }