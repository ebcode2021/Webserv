#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include "webserv.hpp"
# include "Config.hpp"
# include "HttpParser.hpp"

// char request[] = "GET /index.html HTTP/1.1\r\nHost: example.com\r\nConnection: keep-alive\r\n\r\nHello, world!";
// Request = Request-Line (Method SP Request-URI SP HTTP-Version CRLF)
// Request-Header
// Request-Body

class	HttpRequest
{
	private :
		// request-line
		Method		_method;
		std::string	_requestURI;

		// request-header
		std::string	_host;
		std::string	_contentType;
		size_t		_contentLength;

		// request-body
		char*		_body; // 동적 배열

	public :
		// constructor
		HttpRequest(); // HttpParser
		HttpRequest(HttpRequest &);
		HttpRequest(char *);

		// getter
		// void	setRequestLine(std::vector<std::string>);
		// void	setRequestHeader(std::vector<std::string>);
		// void	setRequestBody(std::vector<std::string>);

		void	getMethod();
		void	getRequestURI();
		void	getHost();
};

#endif
