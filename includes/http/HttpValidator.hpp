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
	void		validateRequest(Config&, HttpRequest&);

	// check method and http-version
	void		CheckRequestLineSyntax(const HttpRequestLine&);
	void		CheckRequestHeaderSyntax(const HttpRequestHeader&);

	void		validateURI(Config&, const HttpRequest&);

	void		validateServer(Config&, const HttpRequestHeader&);
	void		validateLocation(HttpPage&, const std::string&);


	void		MethodPermitted(LocationBlock&, std::string&);
}


namespace	HttpHandler
{
	ServerInfo		findServerInfo(Config&, const std::string&);
	LocationBlock	findLocation(ServerInfo&, const std::string&);

	//ServerInfo		compareServerData(std::vector<ServerInfo>&, std::string&, size_t);


	// autoIndex 처리
	std::string		generateResponseBody(ServerBlock&, LocationBlock&);
	void			processRequest();

	HttpPage		requestHandler(Config&, HttpRequest&);
	HttpPage		setPageFromConfigAndRequest(Config&, HttpRequest&);


}

#endif
