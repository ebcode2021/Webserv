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

/* method */
bool	HttpRequestLine::isRecognizedMethod(const std::string& method)
{
	for (size_t	i = 0; i < METHODS_SIZE; i++)
	{
		if (METHODS[i] == method)
			return (true);
	}
	return (false);
}

/* exception */
void	HttpRequestLine::validateRequestLine(LocationBlock& locationBlock, const std::string& clientAddr)
{
	// check http-version
	if (this->_version != HTTP_VERSION)
		throw ResponseException(505);

	// check Method
	if (isRecognizedMethod(this->_method) == false)
		throw ResponseException(405);
	
	// check limit_except
	if (locationBlock.isValidByLimitExcept(this->_method, clientAddr) == false)
		throw ResponseException(405);
}