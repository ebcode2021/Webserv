#include "HttpResponseHeader.hpp"
#include "PathInfo.hpp"

/* constructor */
HttpResponseHeader::HttpResponseHeader(){}

/* getter, setter */
std::string					HttpResponseHeader::getDate() const { return(this->_date); }

std::string					HttpResponseHeader::getServer() const{ return(this->_server); }

std::string					HttpResponseHeader::getContentType()const { return(this->_contentType); }

size_t						HttpResponseHeader::getContentLength() const{ return(this->_contentLength); }

std::string					HttpResponseHeader::getTransferEncoding() const{ return(this->_transferEncoding); }

std::vector<std::string>	HttpResponseHeader::getSetCookie() const{ return(this->_setCookie); }

void						HttpResponseHeader::setDate(std::string& date) { this->_date = date; }
void						HttpResponseHeader::setServer(std::string& server) { this->_server = server; }
void						HttpResponseHeader::setContentType(std::string& contentType) { this->_contentType = contentType; }
void						HttpResponseHeader::setContentLength(size_t contentLength) { this->_contentLength = contentLength; }
void						HttpResponseHeader::setTransferEncoding(std::string& transferEncoding) {this->_transferEncoding = transferEncoding;}

/* method */
void						HttpResponseHeader::setHttpResponseHeader(PathInfo &pathInfo, size_t bodySize)
{
	this->_date = getCurrentTime();
	this->_server = SERVER_NAME;
	this->_contentType = pathInfo.getFileType(); //getContentType();
	this->_contentLength = bodySize;
	this->_transferEncoding = "identity"; 
	// cookie 한 줄 추가
}

std::string					HttpResponseHeader::getCurrentTime()
{
	char buffer[100];
	
	std::time_t	currentTime = std::time(NULL);
	std::tm* 	timeInfo = std::localtime(&currentTime);

	std::strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", timeInfo);

	return buffer;
}

std::string					HttpResponseHeader::getResponseHeaderToString()
{
	std::string	responseHeader;

	responseHeader += ("Server:" + SP + this->_server + CRLF);
	responseHeader += ("Date:" + SP + this->_date + CRLF);
	responseHeader += ("Content-Type:" + SP + this->_contentType + CRLF);
	responseHeader += ("Content-Length:" + SP + itos(this->_contentLength) + CRLF);
	responseHeader += ("Transfer-Encoding:" + SP + this->_transferEncoding + CRLF);
	responseHeader += CRLF;

	return (responseHeader);
}