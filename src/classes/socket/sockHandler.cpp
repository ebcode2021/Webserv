#include "EventHandler.hpp"

/* constructor */
SockHandler::SockHandler()
{
	this->_sockInfo = NULL;
}

/* setter */
void	SockHandler::setSockInfo(SockInfo *sockInfo)
{
	this->_sockInfo = sockInfo;
}

/* socketFunction */

// int SockHandler::sockAccept() {
// 	int 		clientSock; //반환할 클라이언트 sock fd
// 	sockaddr_in clientAddress;
// 	socklen_t	clientAddressSize = sizeof(clientAddress); // client의 정보를 담는 구조체의 크기

// 	clientSock = accept(this->_sockInfo->getSockFd(), (struct sockaddr *)&clientAddress, &clientAddressSize);
	
// 	setSocketLingerOption(clientSock);

// 	return (clientSock);
// }

void SockHandler::closeSock() {
	std::cout << "closeSocket = " << this->_sockInfo->getSockFd() << std::endl;
	close(this->_sockInfo->getSockFd());
	delete (this->_sockInfo);
}

int SockHandler::sockRecv() {
	const int	sockFd = this->_sockInfo->getSockFd();
	int			readByte;
	char		buf[BUFSIZE];

	std::memset(buf, 0, BUFSIZE);
	while (true)
	{
		if ((readByte = recv(sockFd, buf, BUFSIZE, 0)) == -1)
			return (-1);
		if (readByte > 0) {
			this->_sockInfo->addBuf(std::string(buf, readByte));
			std::memset(buf, 0, BUFSIZE);
			if (readByte < static_cast<int>(BUFSIZE))
				return (true);
		}
		else if (readByte == 0)
			return (0);
		else
			return (-1);
	}
}

int SockHandler::sockBind(int port) {
	struct sockaddr_in	serverAddr;

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(port);

	return (bind(this->_sockInfo->getSockFd(), (struct sockaddr *)&serverAddr, sizeof(serverAddr)));
}

int SockHandler::sockListen() {
	return (listen(this->_sockInfo->getSockFd(), FD_SETSIZE));
}

int	SockHandler::sockAccept() {
	sockaddr_in clientAddress;
	socklen_t clientAddressSize = sizeof(clientAddress);

	char addr[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &clientAddress.sin_addr, addr, sizeof(addr));
	std::cout << "클라이언트 접속: IP = " << addr << " 포트 = " << ntohs(clientAddress.sin_port) << std::endl;

	return (accept(this->_sockInfo->getSockFd(), (struct sockaddr *)&clientAddress, &clientAddressSize));
}
