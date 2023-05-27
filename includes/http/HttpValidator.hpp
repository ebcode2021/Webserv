#ifndef HTTP_VALIDATOR_HPP
# define HTTP_VALIDATOR_HPP

# include "TcpSocket.hpp"
# include "webserv.hpp"
# include "HttpRequest.hpp"
# include "Config.hpp"
# include "HttpException.hpp"
# include "HttpPage.hpp"


namespace	HttpValidator
{
	// Validate request
	void		validateRequest(const HttpRequest&, ServerBlock&, LocationBlock&);

	// check request-line 'method' and 'http-version'
	void		CheckRequestLineSyntax(const HttpRequestLine&);
	void		CheckRequestHeaderSyntax(const HttpRequestHeader&);

	// check url path
	void		validateURI(Config&, const HttpRequest&);

	void		MethodPermitted(LocationBlock&, const std::string&);
}

#endif
