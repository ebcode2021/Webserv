#include "HttpRequest.hpp"

/* constructor */
HttpRequest::HttpRequest(){}


/* setter */
void	HttpRequest::setRequestLine(std::vector<std::string> requestLine)
{
	this->_httpRequestLine.setMethod(requestLine.at(0));
	this->_httpRequestLine.setRequestURI(requestLine.at(1));
	this->_httpRequestLine.setVersion(requestLine.at(2));
}

void	HttpRequest::setHeaderField(std::map<std::string, std::string> headerMap)
{
	
}

void	HttpRequest::setBody(std::string content)
{
	this->_httpBody.setBody(content);
}


