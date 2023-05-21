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
	void		CheckRequestSyntax(const HttpRequestLine&);
	void		CheckRequestHeaderSyntax(const HttpRequestHeader&);

	void		MethodPermitted(LocationBlock&, std::string&);
}

namespace	HttpHandler
{
	ServerInfo&		findServerInfo(Config&, const HttpRequestHeader&);
	LocationBlock&	findLocation(ServerInfo&, const std::string&);

	// autoIndex 처리
	std::string		generateResponseBody(ServerBlock&, LocationBlock&);
}

#endif
