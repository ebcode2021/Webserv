#include "HttpRequestLine.hpp"

/* getter */
std::string	HttpRequestLine::getMethod() const { return(this->_method); }

std::string	HttpRequestLine::getRequestURI() const { return(this->_requestURI); }

std::string	HttpRequestLine::getVersion() const { return(this->_version); }


/* setter */
void	HttpRequestLine::setMethod(const std::string& method)
{
	size_t	size = sizeof(METHODS) / sizeof(std::string);

	for (size_t idx = 0; idx < size; idx++)
	{
		if (METHODS[idx].compare(method) == 0)
		{
			this->_method = METHODS[idx];
			break ;
		}
	}
	this->_method = "ERROR";
}

void	HttpRequestLine::setRequestURI(const std::string& requestURI) { this->_requestURI = requestURI; }

void	HttpRequestLine::setVersion(const std::string& version) { this->_version = version; }