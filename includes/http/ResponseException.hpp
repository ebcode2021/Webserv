#ifndef RESPONSE_EXCEPTION_HPP
# define RESPONSE_EXCEPTION_HPP

# include "webserv.hpp"
# include "HttpStatus.hpp"

class	ResponseException
{
	private :
		HttpStatus	_httpStatus;
		

	public :
		explicit	ResponseException(const int statusCode)
			:_httpStatus(statusCode){}

		HttpStatus	httpStatus() const { return(_httpStatus); }
		int			statusCode() const { return(_httpStatus.getStatusCode());}
};

class	SessionException
{
	private :
		HttpStatus	_httpStatus;
		

	public :
		explicit	SessionException(const int statusCode)
			:_httpStatus(statusCode){}

		HttpStatus	httpStatus() const { return(_httpStatus); }
		int			statusCode() const { return(_httpStatus.getStatusCode());}
};

#endif
