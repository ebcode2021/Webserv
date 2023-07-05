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

# include "SessionStorage.hpp"


class	HttpResponse
{
	private :
		HttpResponseLine	_httpResponseLine; 
		HttpResponseHeader	_httpResponseHeader;
		HttpBody			_httpBody;

	public :
		// constructor
		HttpResponse();
		HttpResponse(HttpResponseLine&, HttpResponseHeader&, HttpBody&);

		// setter
		void						setBody(const std::string&);
		std::string					getBody() const;
		HttpResponseHeader&			getResponseHeader();
		HttpResponseLine&			getResponseLine();

		// method
		static HttpResponse			createResponse(PathInfo&, HttpRequest&, const std::string&, SessionStorage&);
		static HttpResponse			createResponse(Config&, HttpRequest&, const std::string&, SessionStorage&);
		static HttpBody				makeResponseBody(const PathInfo&, const HttpStatus&);
		static HttpResponseHeader	makeResponseHeader(const PathInfo&, const size_t);
		std::string					getResponseToString();
		int							getStatusCode();


		// print
		void						printHttpResponse();
};
#endif