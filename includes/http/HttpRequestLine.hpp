#ifndef HTTPREQUESTLINE_HPP
# define HTTPREQUESTLINE_HPP

#include "webserv.hpp"

class	HttpRequestLine
{
	private :
		Method		_method;
		std::string	_requestURI;

	public :
		// getter, setter
		Method		getMethod();
		std::string	getRequestURI();
		void		setMethod();
		void		setRequestURI();

		// validate
		void		validateHttpVersion();
};

#endif