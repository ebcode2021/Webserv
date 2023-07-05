# include "ResponseException.hpp"

ResponseException::ResponseException(const int statusCode): _httpStatus(statusCode) {}

HttpStatus	ResponseException::getHttpStatus() const {
	return (this->_httpStatus);
}
