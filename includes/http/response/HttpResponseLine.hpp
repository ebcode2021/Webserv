#ifndef HTTP_RESPONSE_LINE_HPP
# define HTTP_RESPONSE_LINE_HPP

# include "webserv.hpp"
# include "HttpStatus.hpp"

class	HttpResponseLine
{
	private :
		std::string			_version;
		HttpStatus			_httpStatus;

	public :
		// constructor
		HttpResponseLine() : _version("HTTP/1.1"){};
		HttpResponseLine(const HttpStatus&);

		// getter, setter
		std::string		getVersion() const;
		HttpStatus		getHttpStatus() const;
		void			setHttpStatus(const HttpStatus&);

		// method
		void			setHttpResponseLine(HttpStatus&);
		std::string		getResponseLineToString();
};
#endif