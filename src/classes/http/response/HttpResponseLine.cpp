#include "HttpResponseLine.hpp"

/* constructor */
HttpResponseLine::HttpResponseLine() : _version(HTTP_VERSION) {}

HttpResponseLine::HttpResponseLine(const std::string& method) : _version(HTTP_VERSION) {
	if (method == "GET")
		this->_httpStatus = HttpStatus(200);
	else if (method == "POST")
		this->_httpStatus = HttpStatus(201);
	else if (method == "DELETE")
		this->_httpStatus = HttpStatus(204);
}

HttpResponseLine::HttpResponseLine(const HttpStatus& httpStatus) : _version(HTTP_VERSION) 
{
	this->setHttpStatus(httpStatus);
}

/* getter, setter */
std::string	HttpResponseLine::getVersion() const {
	return(this->_version);
}

HttpStatus	HttpResponseLine::getHttpStatus() const {
	return(this->_httpStatus);
}

void	HttpResponseLine::setHttpStatus(const HttpStatus& httpStatus) {
	this->_httpStatus = HttpStatus(httpStatus);
}

void	HttpResponseLine::setHttpResponseLine(HttpStatus& httpStatus) {
	this->_httpStatus = httpStatus;
}

/* method */
std::string	HttpResponseLine::getResponseLineToString()
{
	std::string responseLine = this->_version + SP + itos(this->_httpStatus.getStatusCode()) \
								  + SP + this->_httpStatus.getReason() + CRLF;

	return (responseLine);
}