#include "HttpResponseHeader.hpp"
#include "PathInfo.hpp"

/* constructor */
HttpResponseHeader::HttpResponseHeader(){}

/* getter, setter */
std::string		HttpResponseHeader::getDate() const {
	return(this->_date);
}

std::string		HttpResponseHeader::getServer() const {
	return(this->_server);
}

std::string		HttpResponseHeader::getContentType()const {
	 return(this->_contentType);
}

size_t			HttpResponseHeader::getContentLength() const {
	return(this->_contentLength);
}

std::string		HttpResponseHeader::getTransferEncoding() const {
	return(this->_transferEncoding);
}

std::vector<std::string>	HttpResponseHeader::getSetCookie() const {
	return(this->_setCookie);
}

void			HttpResponseHeader::setDate(const std::string& date) {
	this->_date = date;
}

void			HttpResponseHeader::setServer(const std::string& server) {
	this->_server = server;
}

void			HttpResponseHeader::setContentType(const std::string& contentType) {
	this->_contentType = contentType;
}

void			HttpResponseHeader::setContentLength(const size_t contentLength) {
	this->_contentLength = contentLength;
}

void			HttpResponseHeader::setTransferEncoding(const std::string& transferEncoding) {
	this->_transferEncoding = transferEncoding;
}

/* method */
std::string		HttpResponseHeader::getResponseHeaderToString()
{
	std::string	responseHeader;

	responseHeader += ("Server:" + SP + this->_server + CRLF);
	responseHeader += ("Date:" + SP + this->_date + CRLF);
	responseHeader += ("Content-Type:" + SP + this->_contentType + CRLF);
	responseHeader += ("Transfer-Encoding:" + SP + this->_transferEncoding + CRLF);
	if (this->_contentLength > 0)
		responseHeader += ("Content-Length:" + SP + itos(this->_contentLength) + CRLF);
	responseHeader += CRLF;

	return (responseHeader);
}
