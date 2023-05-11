# include "SocketEventHandler.hpp"

SocketEventHandler::SocketEventHandler() {}

void	SocketEventHandler::setSocket(TcpSocket *socket) {
	this->_socket = socket;
}

int SocketEventHandler::socketAccept() {
	int clientSock;
	sockaddr_in clientAddress;
	socklen_t	clientAddressSize = sizeof(clientAddress);

	clientSock = accept(this->_socket->getSockFd(), (struct sockaddr *)&clientAddress, &clientAddressSize);
	return (clientSock);
}

void SocketEventHandler::closeSocket() {
	close(this->_socket->getSockFd());
	delete (this->_socket);
}

int SocketEventHandler::dataRecv() {

	std::cout << "dataRecv" << std::endl;
	int ret = 0;
	int recvByte = recv(this->_socket->getSockFd(), this->_socket->getBuf(), BUFSIZE + 1, 0);
	if (recvByte == -1)
		return -1;
	while (recvByte == -1)
	{
		ret += recvByte;
		std::cout << "ret = " << ret << std::endl;
		this->_socket->bufJoin(this->_socket->getBuf());
		recvByte = recv(this->_socket->getSockFd(), this->_socket->getBuf(), BUFSIZE + 1, 0);
		std::cout << recvByte << std::endl;;
	}
	this->_socket->setBufbyIndex(ret, '\0');
	return (ret);
}

int SocketEventHandler::dataSend() {
	int sendByte = send(this->_socket->getSockFd(), this->_socket->getStringToCStr(), this->_socket->getStringSzie(), 0);
	return (sendByte);
}

void	SocketEventHandler::printSockBuf() {
	std::cout << this->_socket->getString() << std::endl;
}
