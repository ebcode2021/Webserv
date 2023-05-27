#include "HttpStatus.hpp"

/* constructor */
HttpStatus::HttpStatus()
{
	std::map<int, std::string>::const_iterator it = getStatusMap().find(200);

	this->_statusCode = it->first;
	this->_reason = it->second;
}

HttpStatus::HttpStatus(const int statusCode)
{
	std::map<int, std::string>::const_iterator it = getStatusMap().find(statusCode);

	this->_statusCode = it->first;
	this->_reason = it->second;
}

int	HttpStatus::getStatusCode() const
{
	return (this->_statusCode);
}

std::string	HttpStatus::getReason() const
{
	return (this->_reason);
}
HttpStatus&	HttpStatus::operator=(const HttpStatus& prev)
{
	this->_statusCode = prev.getStatusCode();
	this->_reason = prev.getReason();
	return (*this);
}

/* method */
std::map<int, std::string>&	HttpStatus::getStatusMap()
{
	static std::map<int, std::string> httpStatusMap;

	if (httpStatusMap.empty())
	{
		httpStatusMap.insert(std::make_pair( 200, "OK" ));
		httpStatusMap.insert(std::make_pair( 201, "Created" ));
		httpStatusMap.insert(std::make_pair( 202, "Accepted" ));
		httpStatusMap.insert(std::make_pair( 400, "Bad Request" ));
		httpStatusMap.insert(std::make_pair( 401, "Unauthorized" ));
		httpStatusMap.insert(std::make_pair( 403, "Forbidden" ));
		httpStatusMap.insert(std::make_pair( 404, "Not Found" ));
		httpStatusMap.insert(std::make_pair( 405, "Method Not Allowed" ));
		httpStatusMap.insert(std::make_pair( 500, "Internal Server Error" ));
		httpStatusMap.insert(std::make_pair( 502, "Bad Gateway" ));
		httpStatusMap.insert(std::make_pair( 503, "Service Unavailable" ));
		httpStatusMap.insert(std::make_pair( 505, "HTTP Version Not Supported" ));
	}
	return (httpStatusMap);
}