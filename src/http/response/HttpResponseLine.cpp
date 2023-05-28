#include "HttpResponseLine.hpp"

/* constructor */
//HttpResponseLine::HttpResponseLine(){}

HttpResponseLine::HttpResponseLine(const HttpStatus& httpStatus) {	this->setHttpStatus(httpStatus); }

/* getter */
std::string	HttpResponseLine::getVersion() const { return(this->_version); }

HttpStatus	HttpResponseLine::getHttpStatus() const { return(this->_httpStatus); }

/* setter */

void	HttpResponseLine::setHttpStatus(const HttpStatus& httpStatus)
{
	this->_httpStatus = HttpStatus(httpStatus);
}

void	HttpResponseLine::setHttpResponseLine(HttpStatus& httpStatus)
{
	this->_httpStatus = httpStatus;
}