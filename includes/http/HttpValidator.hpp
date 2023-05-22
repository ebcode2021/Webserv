#ifndef HTTP_VALIDATOR_HPP
# define HTTP_VALIDATOR_HPP

# include "TcpSocket.hpp"
# include "webserv.hpp"
# include "HttpRequestLine.hpp"
# include "HttpRequestHeader.hpp"
# include "HttpBody.hpp"
# include "Config.hpp"
# include "ServerInfo.hpp"
# include "LocationBlock.hpp"

namespace	HttpValidator
{
	// check method and http-version
	void		CheckRequestLineSyntax(const HttpRequestLine&);
	void		CheckRequestHeaderSyntax(const HttpRequestHeader&);

	void		validateURI(Config&, const HttpRequest&);

	void		validateServer(Config&, const HttpRequestHeader&);
	void		validateLocation(ServerInfo&, const std::string&);
	void		MethodPermitted(LocationBlock&, std::string&);

	// Validate request
	void		validateRequest(Config&, HttpRequest&);
}

namespace	HttpHandler
{
	ServerInfo&		findServerInfo(Config&, const HttpRequestHeader&);
	LocationBlock&	findLocation(ServerInfo&, const std::string&);

	// autoIndex 처리
	std::string		generateResponseBody(ServerBlock&, LocationBlock&);
}

#endif
