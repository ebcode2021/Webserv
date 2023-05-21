#include "HttpStatus.hpp"

/* constructor */
HttpStatus::HttpStatus(){}

HttpStatus::HttpStatus(const int statusCode)
{
	// /this->httpStatusMap.find();
	std::map<int, std::string>::const_iterator it = httpStatusMap.find(statusCode);

	this->_statusCode = it->first;
	this->_reason = it->second;
}

std::map<int, std::string>& HttpStatus::getmap()
{
	static std::map<int, std::string> statusMap = init();
	return (statusMap);
}