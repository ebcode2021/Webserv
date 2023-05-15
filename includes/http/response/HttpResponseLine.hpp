#ifndef HTTP_RESPONSE_LINE_HPP
# define HTTP_RESPONSE_LINE_HPP

# include "webserv.hpp"
# include "HttpStatus.hpp"

class	HttpResponseLine
{
	private :
		const std::string	_version = "HTTP/1.1";
		HttpStatus	_httpStatus;

	public :
		// getter, setter
		std::string	getVersion();
		HttpStatus	getHttpStatus();

		void		setHttpStatus(HttpStatus&);
};
#endif