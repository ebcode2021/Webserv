#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include "webserv.hpp"
# include "Config.hpp"
# include "HttpRequestLine.hpp"
# include "HttpRequestHeader.hpp"
# include "HttpBody.hpp"

// char request[] = "GET /index.html HTTP/1.1\r\nHost: example.com\r\nConnection: keep-alive\r\n\r\nHello, world!";
// Request-Header
	// Request-Line (Method SP Request-URI SP HTTP-Version CRLF)
	// Request-Header-Field (FiledName, FiledValue)
// Request-Body

// validate (cgi-> .py, .php 버튼의 경로..? cgi로 경로설정??)



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

		// setter
		void	setRequestLine(std::vector<std::string>);
		void	setHeaderField(std::map<std::string, std::string>);
		void	setBody(std::string);

		// print
		std::string	toString()
		{
			const std::string tab = "\n\t ";

			std::string requestLine = "request-line" + tab + \
										"method : " + this->_httpRequestLine.getMethod() + tab + \
										"uri : " + this->_httpRequestLine.getRequestURI() + tab + \
										"version : " + this->_httpRequestLine.getVersion() + "\n";
			std::string requestHeader = "request-header" + tab + \
										"host : " + this->_httpRequestHeader.getHost() + tab + \
										"User-Agent : " + this->_httpRequestHeader.getUserAgent() + tab + \
										"Connection : " + this->_httpRequestHeader.getConnection() + tab + \
										"Content-Type : " + this->_httpRequestHeader.getContentType() + tab + \
										"Content-Length : " + std::to_string(this->_httpRequestHeader.getContentLength()) + tab + \
										"Transfer-Encoding : " + this->_httpRequestHeader.getTransferEncoding() + tab + \
										"Cookie : " + this->_httpRequestHeader.getCookie() + "\n"; 
			std::string requestBody = "request-body" + tab + this->_httpBody.getBody() + "\n";
			
			return (requestLine + requestHeader + requestBody);
		};
};

// 요청라인 먼저 갖고있고, 해당 소켓이 갖고있자고?
// header 분석하고. unchunked.
// get이면 한번에 파싱. post면 모아서 쏘자.
// get이면 한번에 들어왔으니까 넘기고
// post면 chunked 된거 한번에 모아서 넘기고.

#endif
