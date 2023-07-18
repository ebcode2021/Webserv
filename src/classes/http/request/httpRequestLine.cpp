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

/* method */
// bool	HttpRequestLine::isRecognizedMethod(const std::string& method)
// {
// 	for (size_t	i = 0; i < METHODS_SIZE; i++)
// 	{
// 		if (METHODS[i] == method)
// 			return (true);
// 	}
// 	return (false);
// }

// std::string	HttpRequestLine::getQueryString() const
// {
// 	size_t	pos = this->_requestURI.find('?');

// 	if (pos == std::string::npos)
// 		return "";
// 	return (this->_requestURI.substr(pos + 1));
// }

// std::string	HttpRequestLine::extractURL() const
// {
// 	size_t	pos = this->_requestURI.find('?');
	
// 	if (pos != std::string::npos)
// 		return (this->_requestURI.substr(0, pos));
// 	else
// 		return (this->_requestURI);
// }

/* exception */
// void	HttpRequestLine::validateRequestLine(const LimitExcept& limitExcept, const std::string& clientAddr)
// {
// 	// check http-version
// 	if (this->_version != HTTP_VERSION)
// 		throw ResponseException(505);

// 	// check Method
// 	if (this->isRecognizedMethod(this->_method) == false)
// 		throw ResponseException(405);

// 	// check limit_except
// 	if (limitExcept.isValidMethod(this->_method, clientAddr) == false)
// 		throw ResponseException(403);
// }