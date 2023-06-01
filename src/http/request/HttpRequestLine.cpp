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
			return ;
		}
	}
	this->_method = "ERROR";
}

void	HttpRequestLine::setRequestURI(const std::string& requestURI) { this->_requestURI = requestURI; }

void	HttpRequestLine::setVersion(const std::string& version) { this->_version = version; }

void	HttpRequestLine::validateRequestLine(LocationBlock& locationBlock)
{
	(void)locationBlock;

	// check http-version
	if (this->_version != HTTP_VERSION)
		throw ResponseException(505);

	//std::cout << "*" << this->_method << "*" <<std::endl;
	//std::cout << "*" << METHODS[2] << "*" <<std::endl;
	// check Method
	//locationBlock.isValidMethodByLimitExcept(this->_method) == false
	//if (METHODS->find(this->_method) == std::string::npos)
	if ((this->_method == "GET" || this->_method == "DELETE" || this->_method == "POST") == false)
		throw ResponseException(405);
	

}