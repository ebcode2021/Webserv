#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include "webserv.hpp"
# include "HttpRequestLine.hpp"
# include "HttpRequestHeader.hpp"
# include "HttpBody.hpp"

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
		/* constructor */
		HttpRequest();

		/* getter, setter */
		HttpRequestLine&			getRequestLine() ;
		HttpBody&					getBody() ;

		void								setHeader(std::vector<std::string>&);
		void								setBody(const std::string&);

		void								setRequestLine(std::vector<std::string>);
		void								setHeaderField(std::map<std::string, std::string>);

		// parser
		static void 						parseHeaderAndBody(const std::string&, std::vector<std::string>&, std::string&);
		
		
		const HttpRequestLine&		getHttpRequestLine();
		HttpRequestHeader&			getHttpRequestHeader();

		// static
		static std::map<std::string, std::string>	createHeaderField(std::vector<std::string>&);


		// print
		void	printInfo();
};

#endif
