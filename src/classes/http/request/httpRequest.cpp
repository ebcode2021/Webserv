# include "HttpRequest.hpp"
# include "utils.hpp"

/* constructor */
HttpRequest::HttpRequest(){}

// getter
HttpRequestLine	&HttpRequest::getHttpRequestLine()
{
	return (this->_httpRequestLine);
}

const HttpRequestHeader	&HttpRequest::getHttpRequestHeader() const
{
	return (this->_httpRequestHeader);
}

HttpBody	&HttpRequest::getHttpBody()
{
	return (this->_httpBody);
}

// method
int	HttpRequest::createRequest(std::string &data, ReadPhase &mode)
{
	try
	{
		switch (mode)
		{
			case R_LINE:
				this->_httpRequestLine.initRequestLine(extractRequestLine(data));
				mode = R_HEADER;
			case R_HEADER:
				this->_httpRequestHeader.setRequestHeader(extractHeaderField(data));
				mode = R_BODY;
			case R_BODY:
				this->_httpBody += encodingData(data, this->_httpRequestHeader.getHeaderByKey(TRANSFER_ENCODING), mode);
				data.clear();
				if (compareContentLengthAndBodySize(_httpRequestHeader.getHeaderByKey(CONTENT_LENGTH), this->_httpBody.getBodySize())) {
					mode = R_END;
				}
			case R_END:
				break ;
		}
	}
	catch(const int code)
	{
		return (code);
	}
	return (0);
}

void	HttpRequest::print()
{
	this->_httpRequestLine.print();
	this->_httpRequestHeader.print();
	this->_httpBody.print();
}
