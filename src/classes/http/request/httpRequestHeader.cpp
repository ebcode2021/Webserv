#include "HttpRequestHeader.hpp"

/* constructor */

HttpRequestHeader::HttpRequestHeader() {};

// getter
std::string HttpRequestHeader::getHeaderByKey(std::string key) const
{
	std::map<std::string, std::string>::const_iterator it;

	it = this->_requestHeader.find(key);
	if (it == this->_requestHeader.end())
		return ("");
	return ((*it).second);
}

// setter
void	HttpRequestHeader::setRequestHeader(std::map<std::string, std::string> header)
{
	this->_requestHeader = header;
}


void	HttpRequestHeader::print()
{
	std::map<std::string, std::string>::iterator it;

	for (it = this->_requestHeader.begin(); it != this->_requestHeader.end(); it++)
	{
		std::cout << it->first << ": " << it->second << std::endl;
	}
	
}
