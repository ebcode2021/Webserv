#include "HttpRequestHeader.hpp"

/* constructor */
HttpRequestHeader::HttpRequestHeader() : _contentType("text/html"), _transferEncoding("identity") {}

/* getter */
std::string HttpRequestHeader::getHost() const { return(this->_host); }

std::string HttpRequestHeader::getUserAgent() { return(this->_userAgent); }

std::string HttpRequestHeader::getConnection() { return(this->_connection); }

std::string HttpRequestHeader::getContentType() { return(this->_contentType); }

size_t  HttpRequestHeader::getContentLength() { return(this->_contentLength); }

std::string HttpRequestHeader::getTransferEncoding() { return(this->_transferEncoding); }

std::string HttpRequestHeader::getCookie() { return(this->_cookie); }

std::string HttpRequestHeader::getSessionID() { return(this->_sessionID); }


/* setter */
void	HttpRequestHeader::setHost(std::string& host) { this->_host = host; }

void	HttpRequestHeader::setUserAgent(std::string& userAgent) { this->_userAgent = userAgent; }

void	HttpRequestHeader::setConnection(std::string& connection) { this->_connection = connection; }

void	HttpRequestHeader::setContentType(std::string& contentType) { this->_contentType = contentType; }

void	HttpRequestHeader::setContentLength(size_t contentLength) { this->_contentLength = contentLength; }

void	HttpRequestHeader::setTransferEncoding(std::string& transferEncoding) { this->_transferEncoding = transferEncoding; }

void	HttpRequestHeader::setCookie(std::string& cookie) { this->_cookie = cookie; }

void	HttpRequestHeader::setSessionID(std::string& session)
{
	(void)session;
	this->_sessionID = "setCookie에서 sessionID 분리해서 갖고 있을듯. public 에서 private으로 바꿀 예정인 setter";
}



