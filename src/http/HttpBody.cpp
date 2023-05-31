#include "HttpBody.hpp"

/* getter, setter */
std::string	HttpBody::getBody() const {
	return (this->_body);
}

void		HttpBody::setBody(const std::string& body) {
	this->_body += body;
}

/* method */
size_t		HttpBody::getBodySize() const {
	return (this->_body.size());
}
