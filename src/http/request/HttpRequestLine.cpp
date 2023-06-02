#include "HttpRequestLine.hpp"

/* getter */
std::string	HttpRequestLine::getMethod() const {
	return(this->_method);
}

std::string	HttpRequestLine::getRequestURI() const {
	return(this->_requestURI);
}

std::string	HttpRequestLine::getVersion() const {
	return(this->_version);
}

/* setter */
void	HttpRequestLine::setMethod(const std::string& method) {
	this->_method = method;
}

void	HttpRequestLine::setRequestURI(const std::string& requestURI) {
	this->_requestURI = requestURI;
}

void	HttpRequestLine::setVersion(const std::string& version) {
	this->_version = version;
}

/* exception */
void	HttpRequestLine::validateRequestLine(LocationBlock& locationBlock)
{
	(void)locationBlock;

	// check http-version
	if (this->_version != HTTP_VERSION)
		throw ResponseException(505);

	// check Method
	if ((this->_method == "GET" || this->_method == "DELETE" || this->_method == "POST") == false)
		throw ResponseException(405);
}