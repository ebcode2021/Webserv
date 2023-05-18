#include "HttpRequest.hpp"
#include "TcpSocket.hpp"
/* constructor */
HttpRequest::HttpRequest(){}

/* getter */
HttpRequestLine&		HttpRequest::getRequestLine() { return(this->_httpRequestLine); }

HttpRequestHeader&	HttpRequest::getRequestField() { return(this->_httpRequestHeader); }

HttpBody&				HttpRequest::getBody(){ return(this->_httpBody); }

/* setter */
void	HttpRequest::setHeader(std::vector<std::string>& header)
{
	std::vector<std::string>			requestLine = split(header[0], " ");
	std::map<std::string, std::string>	requestHeaderField = createHeaderField(header);

	this->setRequestLine(requestLine);
	this->setHeaderField(requestHeaderField);
}

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
				if (fieldName == "Host")
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

void	HttpRequest::setBody(const std::string& content)
{
	this->_httpBody.setBody(content);
}

/* parser */
void	HttpRequest::parseHeaderAndBody(const std::string& request, std::vector<std::string>& header, std::string& body)
{
	std::vector<std::string>	data;
	size_t						doubleCRLFIndex = request.find(DOUBLE_CRLF);

	// header, body
	data.push_back(request.substr(0, doubleCRLFIndex));
	data.push_back(request.substr(doubleCRLFIndex + DOUBLE_CRLF.size(), request.size()));

	int start = 0;
	size_t end = data[0].find(CRLF);
	while (end != std::string::npos)
	{
		std::string line = data[0].substr(start, end - start);
		header.push_back(line);
		start = end + CRLF.size();
		end = data[0].find(CRLF, start);
	}
	std::string lastLine = data[0].substr(start);
	header.push_back(lastLine);
	body = data[1];
}


std::map<std::string, std::string>	HttpRequest::createHeaderField(std::vector<std::string>& headerField)
{
	std::map<std::string, std::string>	headerMap;

	std::vector<std::string>::iterator it;

	for (it = headerField.begin() + 1; it != headerField.end(); ++it)
	{
		std::string	delimiter = ": ";
		std::string	header = *it;
		size_t 		pos = header.find(delimiter);

		if (pos != std::string::npos)
		{
			std::string	key	= header.substr(0, pos);
			std::string	value = header.substr(pos + delimiter.size());
			headerMap.insert(std::make_pair(key, value));
		}
	}
	return (headerMap);
}