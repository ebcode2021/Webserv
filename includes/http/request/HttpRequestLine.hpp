#ifndef HTTPREQUESTLINE_HPP
# define HTTPREQUESTLINE_HPP

#include "webserv.hpp"
#include "LocationBlock.hpp"
#include "ResponseException.hpp"

class	HttpRequestLine
{
	private :
		std::string	_method;
		std::string	_requestURI;
		std::string	_version;

	public :
		// getter, setter
		std::string	getMethod() const;
		std::string	getRequestURI() const;
		std::string getVersion() const;

		void		setMethod(const std::string&);
		void		setRequestURI(const std::string&);
		void		setVersion(const std::string&);

		// exception
		void		validateRequestLine(LocationBlock& locationBlock);
};

#endif