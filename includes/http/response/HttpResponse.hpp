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
		HttpResponse(Config&, HttpRequest&);
		HttpResponse& operator=(const HttpResponse&);

		// setter
		void	setResponseLine(const HttpStatus&);
		void	setResponseHeader(const HttpRequestHeader&);
		void	setBody(const std::string&);

		// getter, setter
		const char*	getResponse();
		void		setResponse(const HttpRequest&, int);
};
#endif