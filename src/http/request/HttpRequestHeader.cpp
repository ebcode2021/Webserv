#include "HttpRequestHeader.hpp"

/* constructor */
HttpRequestHeader::HttpRequestHeader() : _contentType("text/html"), _transferEncoding("identity") {}

/* getter */
std::string HttpRequestHeader::getHost() const {
	return(this->_host);
}

std::string HttpRequestHeader::getUserAgent() const {
	return(this->_userAgent);
}

std::string HttpRequestHeader::getConnection() const {
	return(this->_connection);
}

std::string HttpRequestHeader::getContentType() const {
	return(this->_contentType);
}

size_t  HttpRequestHeader::getContentLength() const {
	return(this->_contentLength);
}

std::string HttpRequestHeader::getTransferEncoding() const {
	return(this->_transferEncoding);
}

std::string HttpRequestHeader::getCookie() const {
	return(this->_cookie);
}

std::string HttpRequestHeader::getSessionID() const {
	return(this->_sessionID);
}

/* setter */
void	HttpRequestHeader::setHost(std::string& host) {
	this->_host = host;
}

void	HttpRequestHeader::setUserAgent(std::string& userAgent) {
	this->_userAgent = userAgent;
}

void	HttpRequestHeader::setConnection(std::string& connection) {
	this->_connection = connection;
}

void	HttpRequestHeader::setContentType(std::string& contentType) {
	this->_contentType = contentType;
}

void	HttpRequestHeader::setContentLength(size_t contentLength) {
	this->_contentLength = contentLength;
}

void	HttpRequestHeader::setTransferEncoding(std::string& transferEncoding) {
	this->_transferEncoding = transferEncoding;
}

void	HttpRequestHeader::setCookie(std::string& cookie) {
	this->_cookie = cookie;
}

void	HttpRequestHeader::validateRequestHeader(LocationBlock& locationBlock)
{
	try
	{
		if(this->_contentLength > locationBlock.getClientMaxBodySize())
			throw ResponseException(413);
		
	}
	catch(const ResponseException &ex)
	{
		throw ResponseException(ex.statusCode());
	}
}

/* method */
std::string	HttpRequestHeader::getServerNameToHost()
{
	std::vector<std::string>	splittedHost = split(this->_host, ":");
	std::string					serverName   = splittedHost[0];

	return (serverName);
}