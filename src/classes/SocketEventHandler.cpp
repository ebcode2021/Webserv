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

// int SocketEventHandler::dataRecv() {
// 	//int recvSize = 0;
// 	int ret;
// 	char buf[BUFSIZE + 1];

// 	while (true)
// 	{
// 		ret = recv(this->_socket->getSockFd(), buf, BUFSIZE, 0);
// 		if (ret == -1)
// 			return (-1);
// 		else if (ret == 0)
// 			break;
// 		buf[ret + 1] = '\0';
// 		std::cout << "now buf = " << buf << std::endl;
// 		this->_socket->bufJoin(buf);
// 	}
// 	return (this->_socket->getStringSzie());
// }

int SocketEventHandler::dataRecv() {
    int ret = 0;
    int recvByte = recv(this->_socket->getSockFd(), this->_socket->getBuf(), BUFSIZE, 0);
    if (recvByte == -1)
        return (-1);
    while (recvByte > 0)
    {
        ret += recvByte;
        this->_socket->setBufbyIndex(recvByte + 1, '\0');
        this->_socket->bufJoin(this->_socket->getBuf());
        recvByte = recv(this->_socket->getSockFd(), this->_socket->getBuf(), BUFSIZE, 0);
    }
    return (ret);
}

std::string createHttpResponse(const std::string& body) {
    std::ostringstream response;
    
    response << "HTTP/1.1 200 OK\r\n";
    response << "Content-Type: text/html\r\n";
	response << "Connection: close\r\n";
    response << "Content-Length: " << body.length() << "\r\n";
    response << "\r\n";
    response << body;

    return response.str();
}

int SocketEventHandler::dataSend() {

	//send(this->_socket->getSockFd(), "a", 1, 0);
	//return (0);
	// 고민 해해봤봤어어??

	std::string htmlBody = "<html><body>Hello World</body></html>";
    std::string httpResponse = createHttpResponse(htmlBody);
	

	int sendByte = send(this->_socket->getSockFd(), httpResponse.c_str(), httpResponse.size(), 0);
	this->_socket->stringClear();
	return (sendByte);
}

void	SocketEventHandler::printSockBuf() {
	std::cout << this->_socket->getString() << std::endl;
}

void SocketEventHandler::printSockFd() {
	std::cout << this->_socket->getSockFd() << std::endl;
}
