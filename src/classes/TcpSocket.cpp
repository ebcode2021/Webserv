# include "TcpSocket.hpp"

/* constructor*/
TcpSocket::TcpSocket() {}

TcpSocket::TcpSocket(int socketFd)
{
	this->_socketInfo.sock = socketFd;
	this->_socketInfo.sendbyte = 0;
	this->_socketInfo.recvbyte = 0;
	this->_readMode = HEADER;
	this->_clientAddr = getClientAddrBySocket();
	this->changeToNonblocking();
}

/* getter, setter */
std::string		 TcpSocket::getBuf() {
	return (this->_socketInfo.buf);
}

std::string		TcpSocket::getClientAddr() {
	return (this->_clientAddr);
}

int				TcpSocket::getReadMode() {
	return this->_readMode;
}

HttpRequest&	TcpSocket::getRequest() {
	return(this->_request);
}

HttpResponse	TcpSocket::getResponse() {
	return (this->_response);
}

int				TcpSocket::getSockFd() {
	return (this->_socketInfo.sock);
}

int				TcpSocket::getSendByte() {
	return (this->_socketInfo.sendbyte);
}

size_t			TcpSocket::getRecvByte() {
	return (this->_socketInfo.recvbyte);
}

void			TcpSocket::setRequest(HttpRequest& httpRequest) {
	this->_request = httpRequest;
}

void			TcpSocket::setResponse(HttpResponse& httpResponse) {
	this->_response = httpResponse;
}

void			TcpSocket::setBuf(const std::string& buf) {
	this->_socketInfo.buf = buf;
}

void			TcpSocket::addBuf(const std::string& buf) {
	this->_socketInfo.buf += buf;
}

void			TcpSocket::setReadMode(int readMode) {
	this->_readMode = readMode;
}

/* method */

const char*		TcpSocket::getBufToCStr() {
	return (this->_socketInfo.buf.c_str());
}


size_t	TcpSocket::getBufSize() {
	return (this->_socketInfo.buf.size());
}

void	TcpSocket::setBufbyIndex(int idx, char a) {
	this->_socketInfo.buf[idx] = a;
}

void TcpSocket::bufClear() {
	this->_socketInfo.buf.clear();
}

void TcpSocket::addReadSize(size_t readSize) {
	this->_socketInfo.recvbyte += readSize;
}

void	TcpSocket::changeToNonblocking()
{
	int flag = fcntl(this->_socketInfo.sock, F_GETFL);

	flag |= O_NONBLOCK;
	fcntl(this->_socketInfo.sock, F_SETFL, flag);
}

std::string	TcpSocket::getClientAddrBySocket()
{
	int 				clientSocketFd = this->_socketInfo.sock;
	struct sockaddr_in	clientAddress;
	socklen_t			clientAddressLength = sizeof(clientAddress);

	if (getpeername(clientSocketFd, (struct sockaddr*)&clientAddress, &clientAddressLength) == 0)
		return (inet_ntoa(clientAddress.sin_addr));
	return ("");
}

void TcpSocket::changeReadMode() {
	if (this->getRequest().getHttpRequestLine().getMethod() == "GET")
		this->setReadMode(END);
	else if (this->getRequest().getHttpRequestHeader().getTransferEncoding() == "chunked")
		this->setReadMode(CHUNKED);
	else
		this->setReadMode(IDENTITY);
}

void	TcpSocket::setRequestHeader()
{
	std::vector<std::string>	header;
	std::string					body;
	std::string					request = this->getBuf();

	HttpRequest::parseHeaderAndBody(request, header, body);

	this->_request.splitHeader(header);
	this->setBuf(body);
	//std::cout << "buf = " << this->_socketInfo.buf << std::endl;
}

std::string TcpSocket::chunkedEncoding()
{
	std::string body;
	std::string chunkSizeString;
	size_t		pos;
	
	while (1)
	{
		pos = this->_socketInfo.buf.find("\r\n");
		std::cout << "pos = " << pos << std::endl;
		if (pos == std::string::npos)
			break ;
		chunkSizeString = this->_socketInfo.buf.substr(0, pos);
		int chunkSize = std::stoi(chunkSizeString, nullptr, 16);
		std::cout << chunkSize << std::endl;
		if (chunkSize == 0) {
			std::cout << "setReadMode = END" << std::endl;
			this->setReadMode(END);
			break ;
		}
		this->_socketInfo.buf.erase(0, pos + 2);
		std::cout << this->_socketInfo.buf.substr(0, chunkSize) << std::endl;
		body += this->_socketInfo.buf.substr(0, chunkSize);
		this->_socketInfo.buf.erase(0, chunkSize + 2);
	}
	return (body);
}

void	TcpSocket::setRequestBody()
{
	std::string encodedBuf;

	if (this->getReadMode() == IDENTITY)
	{
		std::cout << "IDENTY" << std::endl;
		encodedBuf = this->getBuf();
		std::cout << "encodedBuf size = " << encodedBuf.size() << std::endl;
		this->addReadSize(encodedBuf.size());
		this->_request.setBody(encodedBuf);
		std::cout << "recvbyte = " << this->getRecvByte() << "\ncontentlength = " << this->_request.getHttpRequestHeader().getContentLength() << std::endl;
		if (this->getRecvByte() == this->_request.getHttpRequestHeader().getContentLength())
			this->setReadMode(END);
	}
	else if (this->getReadMode() == CHUNKED)
	{
		encodedBuf = chunkedEncoding();
		this->addReadSize(encodedBuf.size());
		this->_request.setBody(encodedBuf);
	}
	this->_request.setBody(encodedBuf);
	//std::cout << _request.getBody().getBody() << std::endl;
}

/* print */
void TcpSocket::printRequestInfo()
{
	this->_request.printInfo();
}
