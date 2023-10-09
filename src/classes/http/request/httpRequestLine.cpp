# include "HttpRequestLine.hpp"


/* getter */
std::string	HttpRequestLine::getMethod() const {
	return (this->_method);
}

std::string	HttpRequestLine::getRequestURI() const {
	return (this->_requestURI);
}

std::string	HttpRequestLine::getVersion() const {
	return (this->_version);
}

std::string	HttpRequestLine::getQueryString() const {
	return (this->_queryString);
}

/* setter */
void	HttpRequestLine::setMethod(const std::string& method) {
	this->_method = method;
}

void	HttpRequestLine::setRequestURI(const std::string& requestURI) {
	this->_requestURI = requestURI;
}

void	HttpRequestLine::setVersion(const std::string& version) {
	this->_version = version;
}

void	HttpRequestLine::setQueryString(const std::string& query)
{
	this->_queryString = query;
}



void	HttpRequestLine::initRequestLine(std::string line)
{
	std::vector<std::string> splittedLine = split(line, WHITESPACE);
	if (splittedLine.size() != 3)
		throw 400;
	this->setMethod(splittedLine[0]);
	this->setQueryString(extractQueryString(splittedLine[1]));
	this->setRequestURI(splittedLine[1]);
	this->setVersion(splittedLine[2]);
}


void	HttpRequestLine::print()
{
	std::cout << "METHOD: " << this->_method
			<< "\nURL: " << this->_requestURI
			<< "\nQURTYSTRING: " << this->_queryString
			<< "\nVERSION: " << this->_version << std::endl;
}
