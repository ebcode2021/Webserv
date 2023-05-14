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
	std::map<std::string, std::string>::const_iterator	it;
	std::vector<std::string>::const_iterator 			findIt;

	for (it = headerMap.begin(); it != headerMap.end(); ++it)
	{
		findIt = std::find(REQUEST_HEADERS.begin(), REQUEST_HEADERS.end(), it->first);
		if (findIt != REQUEST_HEADERS.end())
		{
			std::string fieldName = it->first;
			std::string fieldValue = it->second;
			
			if (fieldName == "host")
				this->_httpRequestHeader.setHost(fieldValue);
			else if (fieldName == "User-Agent")
				this->_httpRequestHeader.setUserAgent(fieldValue);
			else if (fieldName == "Connection")
				this->_httpRequestHeader.setConnection(fieldValue);
			else if (fieldName == "Conetent-Type")
				this->_httpRequestHeader.setContentType(fieldValue);
			else if (fieldName == "Content-Length")
				this->_httpRequestHeader.setContentLength(std::atoi(fieldValue.c_str()));
			else if (fieldName == "Transfer-Encoding")
				this->_httpRequestHeader.setTransferEncoding(fieldValue);
			else if (fieldName == "Cookie")
				this->_httpRequestHeader.setCookie(fieldValue);
		}
	}
}

void	HttpRequest::setBody(std::string content)
{
	this->_httpBody.setBody(content);
}


