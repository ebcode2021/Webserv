#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP

# include "webserv.hpp"
# include "HttpResponseLine.hpp"
# include "HttpResponseHeader.hpp"
# include "HttpBody.hpp"

# include "Config.hpp"
# include "HttpRequest.hpp"

// Response-Header
	// Response-Line
		// HTTP/1.1 <status code> <reason phrase>
	// Response-Header-Field
// Reasponse-Body

class	HttpResponse
{
	private :
		HttpResponseLine	_httpResponseLine;
		HttpResponseHeader	_httpResponseHeader;
		HttpBody			_httpBody;

	public :
		// constructor
		HttpResponse();
		//HttpResponse(Config&, HttpRequest&);

		HttpResponse& operator=(const HttpResponse&);

		// setter
		void	setResponseLine(const HttpResponseLine&);
		void	setResponseHeader(const HttpResponseHeader&);
		void	setBody(const std::string&);

		HttpResponseLine&	getResponseLine();
		HttpResponseHeader&	getResponseHeader();
		HttpBody&			getBody();

		// getter, setter
		//const char*	getResponse();
		//void		setResponse(const HttpRequest&, int);

		// create
		static HttpResponse&	createResponse(Config&, HttpRequest&);

		// compose
		static const HttpResponse&			composeResponse();
		static const HttpResponseLine&		composeResponseLine();
		static const HttpResponseHeader&	composeResponseHeader() ;
		static const std::string&			composeBody();
};
#endif