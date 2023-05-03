#include "webserv.hpp"
#include "Config.hpp"

int createSocket()
{
	int	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == INVALID_SOCKET)
		printErrorWithExit("배고파");
}

int main(int argc, char *argv[])
{
	if (Config::fileCheck(argc, argv))
	{
		Config config(argv[1]);
		std::cout << "컨피그 저장 완료" << std::endl;
		//config.printServerList();

		// create_listen_sock(); // linten sock read event 등록 
		// 저장해놓은 포트 개수만큼 listen 소켓 열어야함
		// 8080 하드코딩
		//int kq = kqueue(); // kqueue
		// openListenSockets(config, kq);

		// 사실상 여기 for문  openListenSockets(config, kq);
		TcpSocket listenSocket(createSocket());
		listenSocket.socketBind(8080);
		listenSocket.socketListen();
		listenSocket.changeToNonblocking();

		// kqueue에 이벤트 등록
		struct kevent kev;
		EV_SET(&kev, listenSocket.getSockFd(), EVFILT_READ, EV_ADD, 0, 0, &listenSocket);
		int kq = kqueue(); // kqueue
	}
		// for문으로 감싼다고 생각하고
			// createListenSocket();
		// Kqueue_a kqueue_a(); // event 등록 할 수


		while(1)
		{

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
	
	return 0;
}


		// for (1;1;1;) {
		// 	TcpSocket listenSocket(createSocket());
		// 	listenSocket.bind(port);
		// 	listenSocket.listen();
		// 	listenSocket.changeToNonblocking();
		// 	// kqueue에 이벤트 등록
		// }