#include "HttpRequestHeader.hpp"

/* constructor */
HttpRequestHeader::HttpRequestHeader() : _contentType("text/html"), _transferEncoding("identity") 
{
	this->_contentLength = 0;
}

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
	this->_cookie = parseCookie(cookie);
}




void	HttpRequestHeader::validateRequestHeader(LocationBlock locationBlock)
{
	if (this->_contentLength > locationBlock.getClientMaxBodySize())
		throw ResponseException(413);
}

/* method */
std::string	HttpRequestHeader::getServerNameToHost()
{
	std::vector<std::string>	splittedHost = split(this->_host, ":");
	std::string					serverName   = splittedHost[0];

	return (serverName);
}

std::map<std::string, std::string>	HttpRequestHeader::parseCookie(std::string& cookies)
{
	std::map<std::string, std::string>	cookieMap;

	std::vector<std::string>	splittedCookie = split(cookies, ";");
	size_t	size = splittedCookie.size();

	for (size_t i = 0; i < size; i++)
	{
		std::vector<std::string>	splitted = split(splittedCookie[i], "=");
		cookieMap.insert(std::make_pair(splitted[0], splitted[1]));
		//std::cout << "key :" << splitted[0] << std::endl;
		//std::cout << "value :" << splitted[1] << std::endl;
	}
	return (cookieMap);
}

std::string	HttpRequestHeader::getSessionIdByCookie()
{
	
	if (this->_cookie.find("sessionId") != _cookie.end())
		return (this->_cookie["sessionId"]);
	return "";
}