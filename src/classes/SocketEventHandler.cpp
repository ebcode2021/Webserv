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

int SocketEventHandler::dataSend() 
{
	std::string responseMessage = this->_socket->getResponse().getResponseToString();

	int sendByte = send(this->_socket->getSockFd(), responseMessage.c_str(), responseMessage.size(), 0);
	this->_socket->stringClear();
	return (sendByte);
}

void	SocketEventHandler::printSockBuf() {
	std::cout << this->_socket->getString() << std::endl;
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
