#ifndef RESPONSE_EXCEPTION_HPP
# define RESPONSE_EXCEPTION_HPP

# include "webserv.hpp"
# include "HttpStatus.hpp"

class	ResponseException
{
	private :
		HttpStatus	_httpStatus;
		

	public :
		explicit	ResponseException(const int statusCode);

		HttpStatus	getHttpStatus() const;
};

#endif
