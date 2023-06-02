# include "TcpSocket.hpp"


/* constructor*/

TcpSocket::TcpSocket() {}

TcpSocket::TcpSocket(int socketFd)
{
	this->_socketInfo.sock = socketFd;
	this->_socketInfo.sendbyte = 0;
	this->_socketInfo.recvbyte = 0;
	this->_readMode = HEADER;
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

size_t	TcpSocket::getRecvByte()
{
	return (this->_socketInfo.recvbyte);
}

void	TcpSocket::setBuf(std::string& body)
{
	this->_socketInfo.buf = body;
}

void TcpSocket::printRequestInfo()
{
	this->_request.printInfo();
}


std::string TcpSocket::getString() {
	this->_socketInfo.buf;
}

const char	*TcpSocket::getStringToCStr() {
	this->_socketInfo.buf.c_str();
}

int	TcpSocket::getReadMode() {
	return this->_readMode;
}


size_t	TcpSocket::getBufSzie() {
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

void TcpSocket::setReadMode(int readMode) {
	this->_readMode = readMode;
}

void TcpSocket::changeReadMode() {
	if (this->getRequest().getHttpRequestLine().getMethod() == "GET")
		this->setReadMode(END);
	else if (this->getRequest().getHttpRequestHeader().getTransferEncoding() == "chunked")
		this->setReadMode(CHUNKED);
	else
		this->setReadMode(IDENTITY);
}


///////////////////////////////////////////
/* 나중에 utils로 뺄거*/

void	TcpSocket::setRequestHeader()
{
	std::vector<std::string>	header;
	std::string					body;
	std::string					request = this->getString();

	HttpRequest::parseHeaderAndBody(request, header, body);

	this->_request.setHeader(header);
	this->setBuf(body);
	std::cout << "buf = " << this->_socketInfo.buf << std::endl;
}

std::string TcpSocket::chunkedEncoding()
{
	std::string body;
	std::string chunkSizeString;
	size_t		pos;
	
	while (1)
	{
		pos = this->_buf.find("\r\n");
		std::cout << "pos = " << pos << std::endl;
		if (pos == std::string::npos)
			break ;
		chunkSizeString = this->_buf.substr(0, pos);
		int chunkSize = std::stoi(chunkSizeString, nullptr, 16);
		std::cout << chunkSize << std::endl;
		if (chunkSize == 0) {
			std::cout << "setReadMode = END" << std::endl;
			this->setReadMode(END);
			break ;
		}
		this->_buf.erase(0, pos + 2);
		std::cout << _buf.substr(0, chunkSize) << std::endl;
		body += _buf.substr(0, chunkSize);
		this->_buf.erase(0, chunkSize + 2);
	}
	return (body);
}

void	TcpSocket::setRequestBody()
{
	std::string encodedBuf;

	if (this->getReadMode() == IDENTITY)
	{
		std::cout << "IDENTY" << std::endl;
		encodedBuf = this->getString();
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
HttpRequest&	TcpSocket::getRequest() { return(this->_request); }

void	TcpSocket::setRequest(HttpRequest& httpRequest) { this->_request = httpRequest; }

void	TcpSocket::setResponse(HttpResponse& httpResponse) { 
	this->_response = httpResponse; 
}

HttpResponse TcpSocket::getResponse() {
	return (this->_response);
}
