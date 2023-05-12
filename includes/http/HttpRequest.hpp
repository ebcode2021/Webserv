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

// validate (cgi-> .py, .php 버튼의 경로..? cgi로 경로설정??)


#define DEFULAT_REQUESTURI;

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

// 요청라인 먼저 갖고있고, 해당 소켓이 갖고있자고?
// header 분석하고. unchunked.
// get이면 한번에 파싱. post면 모아서 쏘자.
// get이면 한번에 들어왔으니까 넘기고
// post면 chunked 된거 한번에 모아서 넘기고.

#endif
