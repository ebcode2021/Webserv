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

	for (it = headerMap.begin(); it != headerMap.end(); ++it)
	{
		std::string fieldName = it->first;
		std::string fieldValue = it->second;

		for (size_t idx = 0; idx < REQUEST_HEADER_SIZE; idx++)
		{
			if (REQUEST_HEADERS[idx] == fieldName)
			{
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
}

void	HttpRequest::setBody(std::string content)
{
	this->_httpBody.setBody(content);
}



// void delete_init() {
// 	REQUEST_HEADERS.push_back("Host");
// 	REQUEST_HEADERS.push_back("User-Agent");
// 	REQUEST_HEADERS.push_back("Connection");
// 	REQUEST_HEADERS.push_back("Content-Type");
// 	REQUEST_HEADERS.push_back("Content-Length");
// 	REQUEST_HEADERS.push_back("Transfer-Encoding");
// 	REQUEST_HEADERS.push_back("Cookie");
// 	REQUEST_HEADERS.push_back("Host");
// }