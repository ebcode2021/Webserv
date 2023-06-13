# include "SocketEventHandler.hpp"

/* constructor */
SocketEventHandler::SocketEventHandler() {}

void	SocketEventHandler::setSocket(TcpSocket *socket) {
	this->_socket = socket;
}

void	SocketEventHandler::setSocketLingerOption(int clientSock)
{
	struct linger lingerOpt;

	lingerOpt.l_onoff = 1; //1이면 TIME_WAIT 사용
	lingerOpt.l_linger = 0; // TIME_WAIT 상태를 0초로 설정

	if (setsockopt(clientSock, SOL_SOCKET, SO_LINGER, &lingerOpt, sizeof(lingerOpt)) < 0)
		std::cout << "setsockopt error" << std::endl;
}


int SocketEventHandler::socketAccept() {
	int 		clientSock; //반환할 클라이언트 sock fd
	sockaddr_in clientAddress;
	socklen_t	clientAddressSize = sizeof(clientAddress); // client의 정보를 담는 구조체의 크기

	clientSock = accept(this->_socket->getSockFd(), (struct sockaddr *)&clientAddress, &clientAddressSize);
	
	setSocketLingerOption(clientSock);

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
		if ((readByte = recv(sockFd, buf, BUFSIZE, 0)) == -1)
			return (-1);
		if (readByte > 0) {
			//std::cout << std::string(buf, readByte) << std::endl;
			this->_socket->addBuf(std::string(buf, readByte));
			std::memset(buf, 0, BUFSIZE);
			if (readByte < static_cast<int>(BUFSIZE))
				return (true);
		}
		else if (readByte == 0)
			return (0);
		else  {
			std::cout << "-1" << std::endl;
			return (-1);
		}
	}
}

int SocketEventHandler::dataSend() 
{
	std::cout << "asdf" << std::endl;
	std::string responseMessage = this->_socket->getResponse().getResponseToString();
	std::cout << "asdasdff" << std::endl;

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
