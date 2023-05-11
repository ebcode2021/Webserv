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

int SocketEventHandler::closeSocket() {
	close(this->_socket->getSockFd());
	delete (this->_socket);
}

int SocketEventHandler::dataRecv() {
	int ret;
	int recvByte = recv(this->_socket->getSockFd(), this->_socket->getBuf(), BUFSIZE + 1, 0);
	while (recvByte)
	{
		ret += recvByte;
		this->_socket->bufJoin(this->_socket->getBuf());
		recvByte = recv(this->_socket->getSockFd(), this->_socket->getBuf(), BUFSIZE + 1, 0);
	}

	return (ret);
}

int SocketEventHandler::dataSend() {
	send(this->_socket->getSockFd(), this->_socket->getStringToCStr(), this->_socket->getStringSzie(), 0);
}

void	SocketEventHandler::printSockBuf() {
	std::cout << this->_socket->getString() << std::endl;
}
