# include "TcpSocket.hpp"


/* constructor*/

TcpSocket::TcpSocket(){}

TcpSocket::TcpSocket(int socketFd)
{
	this->_socketInfo.sock = socketFd;
	this->_socketInfo.sendbyte = 0;
	this->_socketInfo.recvbyte = 0;
	this->_buf = "";
	this->_readMode = HEADER;
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
	int res = listen(this->_socketInfo.sock, 256);

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

void	TcpSocket::setBuf(std::string& body)
{
	this->_buf = body;
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

void TcpSocket::printRequestInfo()
{
	std::cout << this->_request.toString() << std::endl;
}

void	TcpSocket::bufJoin(char *str) {
	this->_buf += str;
}

std::string TcpSocket::getString() {
	return this->_buf;
}

const char	*TcpSocket::getStringToCStr() {
	return this->_buf.c_str();
}

int	TcpSocket::getReadMode() {
	return this->_readMode;
}

void	TcpSocket::changeReadMode() {
	const HttpRequestHeader requestline = this->_request.getHttpRequestHeader();
	std::string encoding = requestline.getTransferEncoding();

	if (encoding == "chunked")
		this->_readMode = CHUNKED;
	else if (encoding == "identity")
		this->_readMode = IDENTITY;
}

size_t	TcpSocket::getStringSzie() {
	int size = this->_buf.size();
	return size;
}

void	TcpSocket::setBufbyIndex(int idx, char a) {
	this->_socketInfo.buf[idx] = a;
}

void TcpSocket::stringClear() {
	this->_buf.clear();
}



///////////////////////////////////////////
/* 나중에 utils로 뺄거*/

void	TcpSocket::setRequestHeader(const std::string& request)
{
	std::vector<std::string>	header;
	std::string					body;

	HttpRequest::parseHeaderAndBody(request, header, body);
	this->_request.setHeader(header);
	this->_buf = body;
}

void	TcpSocket::setRequestBody()
{
	std::string encodedBuf;

	if (this->getReadMode() == IDENTITY)
	{
		encodedBuf = this->getString();
		this->_request.setBody(encodedBuf);
	}
	else if (this->getReadMode() == CHUNKED)
	{
		// chunked된 데이터를 처리하는 방법
	}
}