#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include "webserv.hpp"
# include "Config.hpp"
# include "HttpParser.hpp"
# include "HttpRequestLine.hpp"
# include "HttpRequestHeader.hpp"
# include "HttpBody.hpp"

// char request[] = "GET /index.html HTTP/1.1\r\nHost: example.com\r\nConnection: keep-alive\r\n\r\nHello, world!";
// Request-Header
	// Request-Line (Method SP Request-URI SP HTTP-Version CRLF)
	// Request-Header-Field (FiledName, FiledValue)
// Request-Body

class	HttpRequest
{
	private :
		HttpRequestLine		_httpRequestLine;
		HttpRequestHeader	_httpRequestHeader;
		HttpBody			_httpBody;

	public :
		// constructor
		HttpRequest();
		HttpRequest& operator=(const HttpRequest&);

		void	setRequestLine(std::vector<std::string>);
		void	setHeaderField(std::map<std::string, std::string>);
		void	setBody(std::string);
};


#endif
