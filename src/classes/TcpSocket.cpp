# include "TcpSocket.hpp"

/* constructor*/

TcpSocket::TcpSocket(){}

TcpSocket::TcpSocket(int socketFd)
{
	this->_socketInfo.sock = socketFd;
	this->_socketInfo.sendbyte = 0;
	this->_socketInfo.recvbyte = 0;
}

void	TcpSocket::socketBind(int port)
{
	struct sockaddr_in	serverAddr;

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(port);

	int res = bind(this->_socketInfo.sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	if (res == SOCKET_ERROR)
		printErrorWithExit("bind() error");
}

void	TcpSocket::socketListen()
{
	int res = listen(this->_socketInfo.sock, SOMAXCONN);

	if (res == SOCKET_ERROR)
		printErrorWithExit("listen() error");
}

void	TcpSocket::changeToNonblocking()
{
	int flag = fcntl(this->_socketInfo.sock, F_GETFL);

	flag |= O_NONBLOCK;
	fcntl(this->_socketInfo.sock, F_SETFL, flag);
}

/* getter, setter */
int	TcpSocket::getSockFd()
{
	return (this->_socketInfo.sock);
}

int	TcpSocket::getSendByte()
{
	return (this->_socketInfo.sendbyte);
}

int	TcpSocket::getRecvByte()
{
	return (this->_socketInfo.recvbyte);
}

char*	TcpSocket::getBuf()
{
	return (this->_socketInfo.buf);
}