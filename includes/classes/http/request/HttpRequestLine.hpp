#ifndef HTTPREQUESTLINE_HPP
# define HTTPREQUESTLINE_HPP

# include "webserv.hpp"
# include "utils.hpp"

class	HttpRequestLine
{
	private :
		std::string	_method;
		std::string	_requestURI;
		std::string _queryString;
		std::string	_version;

	public :
		// getter
		std::string	getMethod() const;
		std::string	getRequestURI() const;
		std::string getVersion() const;
		std::string getQueryString() const;

		// setter
		void		setMethod(const std::string&);
		void		setRequestURI(const std::string&);
		void		setVersion(const std::string&);
		void		setQueryString(const std::string &);

		void		initRequestLine(std::string line);

		// method
		//static bool		isRecognizedMethod(const std::string&);
		//std::string		getQueryString() const;
		//std::string		extractURL() const;

		// exception
		//void		validateRequestLine(const LimitExcept&, const std::string&);

		// test
		void	print();
};

#endif