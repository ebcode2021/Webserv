#include "HttpStatus.hpp"

/* constructor */
HttpStatus::HttpStatus()
{
	this->_statusCode = 0;
}

HttpStatus::HttpStatus(const HttpStatus& httpStatus)
{
	*this = httpStatus;
}

HttpStatus::HttpStatus(const int statusCode)
{
	std::map<int, std::string>::const_iterator it = getStatusMap().find(statusCode);

	this->_statusCode = it->first;
	this->_reason = it->second;
}

HttpStatus&	HttpStatus::operator=(const HttpStatus& prev)
{
	this->_statusCode = prev.getStatusCode();
	this->_reason = prev.getReason();
	return (*this);
}

/* getter, setter */
int			HttpStatus::getStatusCode() const {
	return (this->_statusCode);
}

std::string	HttpStatus::getReason() const {
	return (this->_reason);
}

void		HttpStatus::setHttpStatus(const int statusCode)
{
	std::map<int, std::string>::const_iterator it = getStatusMap().find(statusCode);

	this->_statusCode = it->first;
	this->_reason = it->second;
}

/* method */
std::map<int, std::string>&	HttpStatus::getStatusMap() const
{
	static std::map<int, std::string> httpStatusMap;

	if (httpStatusMap.empty())
	{
		httpStatusMap.insert(std::make_pair( 0, "DEFAULT"));
		httpStatusMap.insert(std::make_pair( 200, "OK" ));
		httpStatusMap.insert(std::make_pair( 201, "Created" ));
		httpStatusMap.insert(std::make_pair( 202, "Accepted" ));
		httpStatusMap.insert(std::make_pair( 204, "No Content" ));
		httpStatusMap.insert(std::make_pair( 301, "Moved Permanently"));
		httpStatusMap.insert(std::make_pair( 302, "Found" ));
		httpStatusMap.insert(std::make_pair( 304, "Not Modified" ));
		httpStatusMap.insert(std::make_pair( 400, "Bad Request" ));
		httpStatusMap.insert(std::make_pair( 401, "Unauthorized" ));
		httpStatusMap.insert(std::make_pair( 403, "Forbidden" ));
		httpStatusMap.insert(std::make_pair( 404, "Not Found" ));
		httpStatusMap.insert(std::make_pair( 405, "Method Not Allowed" ));
		httpStatusMap.insert(std::make_pair( 413, "Request Entity Too Large" ));
		httpStatusMap.insert(std::make_pair( 500, "Internal Server Error" ));
		httpStatusMap.insert(std::make_pair( 502, "Bad Gateway" ));
		httpStatusMap.insert(std::make_pair( 503, "Service Unavailable" ));
		httpStatusMap.insert(std::make_pair( 505, "HTTP Version Not Supported" ));
	}
	return (httpStatusMap);
}

std::string	HttpStatus::getString()
{
	return (itos(this->_statusCode) + " " + this->_reason); 
}

/* print */
void	HttpStatus::printStatus()
{
	std::cout << "[HttpStatus 출력]" << std::endl;
	std::cout << "- statusCode : " << this->_statusCode << std::endl;
	std::cout << "- reason : " << this->_reason << std::endl;
}