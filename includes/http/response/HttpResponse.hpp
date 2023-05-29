#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP

# include "webserv.hpp"
# include "HttpResponseLine.hpp"
# include "HttpResponseHeader.hpp"
# include "HttpBody.hpp"

# include "Config.hpp"
# include "HttpRequest.hpp"
# include "ServerInfo.hpp"
# include "PathInfo.hpp"

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
		HttpResponse(HttpRequest&, PathInfo&, HttpStatus&);


		// getter, setter
		HttpResponse				getResponse();
		void						setResponse(HttpResponse&);
		void						setResponseLine(const HttpResponseLine&);
		void						setResponseHeader(const HttpResponseHeader&);
		void						setBody(const std::string&);

		/* method */
		std::string					getResponseToString();

		// create method
		static HttpResponse			createResponse(Config&, HttpRequest&);
 		std::string					createResponseBody(PathInfo&);

		// print
		void						printHttpResponse();

};
#endif