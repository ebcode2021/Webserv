#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include "webserv.hpp"
# include "HttpRequestLine.hpp"
# include "HttpRequestHeader.hpp"
# include "HttpBody.hpp"

// char request[] = "GET /index.html HTTP/1.1\r\nHost: example.com\r\nConnection: keep-alive\r\n\r\nHello, world!";
// Request-Header
	// Request-Line (Method SP Request-URI SP HTTP-Version CRLF)
	// Request-Header-Field (FiledName, FiledValue)
// Request-Body

class TcpSocket;

class	HttpRequest
{
	private :
		HttpRequestLine		_httpRequestLine;
		HttpRequestHeader	_httpRequestHeader;
		HttpBody			_httpBody;

	public :
		// constructor
		HttpRequest();
		//HttpRequest& operator=(const HttpRequest&);

		// getter, setter
		HttpRequestLine&						getRequestLine() ;
		HttpRequestHeader&					getRequestField() ;
		HttpBody&								getBody() ;

		void										setHeader(std::vector<std::string>&);
		void										setBody(const std::string&);

		void										setRequestLine(std::vector<std::string>);
		void										setHeaderField(std::map<std::string, std::string>);

		// parser
		static void 								parseHeaderAndBody(const std::string&, std::vector<std::string>&, std::string&);
		const HttpRequestLine&		getHttpRequestLine();
		HttpRequestHeader&	getHttpRequestHeader();

		// static
		// static void parseHeaderAndBody(const std::string&, std::vector<std::string>&, std::string&);
		static std::map<std::string, std::string>	createHeaderField(std::vector<std::string>&);


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

#endif
