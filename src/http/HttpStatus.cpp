#include "HttpStatus.hpp"

/* constructor */
HttpStatus::HttpStatus(){}

HttpStatus::HttpStatus(const int statusCode)
{
	std::map<int, std::string>::const_iterator it = httpStatusMap.find(statusCode);

	this->_statusCode = it->first;
	this->_reason = it->second;
}