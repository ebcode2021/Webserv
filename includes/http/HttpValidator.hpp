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
	void		validateRequest(HttpRequest&, ServerBlock&, LocationBlock&);

	// check request-line 'method' and 'http-version'
	void		checkRequestLineSyntax(const HttpRequestLine&);
	void		CheckRequestHeaderSyntax(const HttpRequestHeader&);

	void		validatePath(PathInfo& pathInfo);
}

#endif
