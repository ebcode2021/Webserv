# include "SocketEventHandler.hpp"

SocketEventHandler::SocketEventHandler() {}

void	SocketEventHandler::setSocket(TcpSocket *socket) {
	this->_socket = socket;
}

int SocketEventHandler::socketAccept() {
	int clientSock;
	sockaddr_in clientAddress;
	socklen_t	clientAddressSize = sizeof(clientAddress);

	char addr[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &clientAddress.sin_addr, addr, sizeof(addr));
	//printf("[TCP 서버] 클라이언트 접속 : IP 주소=%s, 포트 번호 = %d\n", addr, ntohs(clientAddress.sin_port));

	clientSock = accept(this->_socket->getSockFd(), (struct sockaddr *)&clientAddress, &clientAddressSize);

	struct linger linger_opt;
	linger_opt.l_onoff = 1;  // 1이면 TIME_WAIT 사용
	linger_opt.l_linger = 0; // TIME_WAIT 상태를 0초로 설정
	if (setsockopt(clientSock, SOL_SOCKET, SO_LINGER,
					&linger_opt, sizeof(linger_opt)) < 0) {
		std::cout << "setsockopt error" << std::endl;
	}


	std::cout << "accept sock fd = " << clientSock << std::endl;
	if (clientSock == INVALID_SOCKET)
		printErrorWithExit("뭔가 잘못됨");
	return (clientSock);
}

void SocketEventHandler::closeSocket() {
	std::cout << "closeSocket = " << this->_socket->getSockFd() << std::endl;
	close(this->_socket->getSockFd());
	delete (this->_socket);
}

int SocketEventHandler::dataRecv() {
	const int	sockFd = this->_socket->getSockFd();
	int			readByte;
	char		buf[BUFSIZE];

	std::memset(buf, 0, BUFSIZE);
	while (true)
	{
		readByte = recv(sockFd, buf, BUFSIZE, 0);
		if (readByte > 0) {
			this->_socket->addBuf(std::string(buf, readByte));
			std::memset(buf, 0, BUFSIZE);
			if (static_cast<size_t>(readByte) < BUFSIZE)
				return (true);
		}
		else if (readByte == 0)
			return (0);
		else 
			return (-1);
	}
}

int SocketEventHandler::dataSend() 
{
    std::string responseMessage = this->_socket->getResponse().getResponseToString();
	//body = getfile(path);
	//body = createAutoIndex(path);
	//httpResponse = createHttpResponse(body);

	int sendByte = send(this->_socket->getSockFd(), responseMessage.c_str(), responseMessage.size(), 0);
	return (sendByte);
}


void SocketEventHandler::printSockFd() {
	std::cout << this->_socket->getSockFd() << std::endl;
}

int SocketEventHandler::sockBind(int port) {
	struct sockaddr_in	serverAddr;

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(port);

	return (bind(this->_socket->getSockFd(), (struct sockaddr *)&serverAddr, sizeof(serverAddr)));
}

int SocketEventHandler::sockListen() {
	return (listen(this->_socket->getSockFd(), FD_SETSIZE));
}

int	SocketEventHandler::sockAccept() {
	std::cout << "접속 수용 이벤트 발생" << std::endl;
	sockaddr_in clientAddress;
	socklen_t clientAddressSize = sizeof(clientAddress);
	std::cout << "accept 전" << std::endl;

	char addr[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &clientAddress.sin_addr, addr, sizeof(addr));
	std::cout << "클라이언트 접속: IP = " << addr << " 포트 = " << ntohs(clientAddress.sin_port) << std::endl;

	return (accept(this->_socket->getSockFd(), (struct sockaddr *)&clientAddress, &clientAddressSize));
}
