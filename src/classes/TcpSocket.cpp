# include "TcpSocket.hpp"
# include "HttpParser.hpp"

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

void	TcpSocket::bufClear() {
	memset(this->_socketInfo.buf, 0, sizeof(BUFSIZE));
}

int		TcpSocket::socketAccept() {
	std::cout << "접속 수용 이벤트 발생" << std::endl;
	sockaddr_in clientAddress;
	socklen_t clientAddressSize = sizeof(clientAddress);
	std::cout << "accept 전" << std::endl;

	char addr[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &clientAddress.sin_addr, addr, sizeof(addr));
	std::cout << "클라이언트 접속: IP = " << addr << " 포트 = " << ntohs(clientAddress.sin_port) << std::endl;

	return (accept(getSockFd(), (struct sockaddr *)&clientAddress, &clientAddressSize));

}



void	TcpSocket::bufJoin(char *str) {
	this->buf += str;
}

std::string TcpSocket::getString() {
	return this->buf;
}

const char	*TcpSocket::getStringToCStr() {
	return this->buf.c_str();
}

size_t	TcpSocket::getStringSzie() {
	int size = this->buf.size();
	return size;
}

void	TcpSocket::setBufbyIndex(int idx, char a) {
	this->_socketInfo.buf[idx] = a;
}

void TcpSocket::stringClear() {
	this->buf.clear();
}

void TcpSocket::setRequest() {
	HttpParser::parseRequest(this->_request, this->buf);
}