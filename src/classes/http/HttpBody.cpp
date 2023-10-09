#include "HttpBody.hpp"

/* constructor */
HttpBody::HttpBody() {
	this->_body = "";
}

HttpBody::HttpBody(std::string body) {
	this->_body = body;
}

/* getter, setter */
std::string	&HttpBody::getBody() {
	return (this->_body);
}

void	HttpBody::setBody(const std::string &body) {
	this->_body = body;
}

/* operator */
void	HttpBody::operator+=(const std::string &body) {
	this->_body += body;
}


/* method */
size_t	HttpBody::getBodySize() const {
	return (this->_body.size());
}

void	HttpBody::trimBody(int index) {
	this->_body.erase(0, index);
}

/* print */
void	HttpBody::print()
{
	std::cout << this->_body << std::endl;
}


