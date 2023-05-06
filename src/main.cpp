#include "webserv.hpp"
#include "Config.hpp"

/*
	[남은거?]
	1) fileCheck 공사 ->(get, post, delete ... limitExcept) -> 은비
	2) HTTP parsing
	3) kqueue read, write -> 민수
	4) 3) 한 후에 클래스 분리
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
	if (1)//Config::fileCheck(argc, argv))
	{
		Config config(argv[1]);
		std::cout << "컨피그 저장 완료" << std::endl;
		//config.printServerList();

		// fd 늘리는 로직 추가

		// create_listen_sock(); // linten sock read event 등록 
		// 저장해놓은 포트 개수만큼 listen 소켓 열어야함
		// 8080 하드코딩
		//int kq = kqueue(); // kqueue
		// openListenSockets(config, kq);

		// 이벤트에 대한 정보(Read, Write, Add, Delete)를 저장하는 vector
		std::vector<struct kevent> changeList;
		
		std::set<int> listenSockList;
		
		// 사실상 여기 for문  openListenSockets(config, changeList);

		int listenSock = createSocket();
		TcpSocket listenSocket(listenSock);
		listenSocket.socketBind(8080);
		listenSocket.socketListen();
		listenSocket.changeToNonblocking();
		listenSockList.insert(listenSock);


		// kqueue 초기화
		int kq = kqueue(); // kqueue

		// 이벤트 등록에 사용되는 kevent vector 배열


		// kqueue에 이벤트 등록
		struct kevent kev;
		EV_SET(&kev, listenSocket.getSockFd(), EVFILT_READ, EV_ADD, 0, 0, &listenSocket);
		kevent(kq, &changeList[0], changeList.size(), 0, 0, NULL);
		changeList.push_back(kev);

		while(1)
		{
			struct kevent eventList[FD_SETSIZE];
			int eventCnt = kevent(kq, &changeList[0], changeList.size(), eventList, FD_SETSIZE, NULL);
			changeList.clear();
			(void)eventCnt;
			for (int i = 0; i < eventCnt; i++) {
				struct kevent curEvent = eventList[i];

				if (listenSockList.find(curEvent.ident) != listenSockList.end()) {
					std::cout << "접속 수용 이벤트 발생" << std::endl;
					sockaddr_in client_address;
					socklen_t clientAddressSi;
					int clientSock = 
				} // listen_sock의 read 이벤트일 경우

				// else if (curEvent.flags == EVFILT_READ) // read일 경우 데이터 읽어주세요
					
				// else if (curEvent.flags == EVFILT_WRITE) // write 일 경우

				// else
				// {
				// 	std::cerr << "뭔가 잘못됬음" << std::endl;
				// 	exit(1);
				// }
			} 
			// kevent 함수 호출
			// 이벤트가 발생하면 kevent 배열에 이벤트가 발생한 kevent 구조체들을 담아서 반환
			// kevent 소켓 번호와 이벤트 플래그 확인 후 처리
				// listen_sock의 read 이벤트일 경우
					// 접속 수용
				// read일 경우
					// 소켓송수신 버퍼에 있는 데이터를 가져와서 처리
						// 아마 http 형식에 맞게 파싱해서 확인할듯
				// write일 경우
					// 클라이언트한테 데이터 전송
			// 반복
		}
	}
		// for문으로 감싼다고 생각하고
			// createListenSocket();
		// Kqueue_a kqueue_a(); // event 등록 할 수
		
	
	return 0;
}


		// for (1;1;1;) {
		// 	TcpSocket listenSocket(createSocket());
		// 	listenSocket.bind(port);
		// 	listenSocket.listen();
		// 	listenSocket.changeToNonblocking();
		// 	// kqueue에 이벤트 등록
		// }