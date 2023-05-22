#include "HttpValidator.hpp"
#include "HttpException.hpp"

void	HttpValidator::CheckRequestLineSyntax(const HttpRequestLine& requestLine)
{
	// check method
	if (METHODS->find(requestLine.getMethod()) == std::string::npos)
		throw ResponseException(400);

	// check http-version
	if (requestLine.getVersion() != HTTP_VERSION)
		throw ResponseException(400);
}

void	HttpValidator::CheckRequestHeaderSyntax(const HttpRequestHeader& requestHeader)
{

}

ServerInfo&	HttpHandler::findServerInfo(Config& config, const HttpRequestHeader& requestHeader)
{
	std::string				host = requestHeader.getHost();

	std::vector<ServerInfo>	serverList = config.getServerList();
	size_t					serverListSize = serverList.size();

	for (size_t	i = 0; i < serverListSize; i++)
	{
		ServerBlock serverBlock = serverList[i].getServerBlock();

		std::vector<std::string>	serverNameList = serverBlock.getServerNameList();
		size_t						serverNameListSize = serverNameList.size();

		for (size_t j = 0; j < serverNameListSize; j++)
		{
			if (serverNameList[j].compare(host) == 0)
				return (serverList[i]);
		}
	}
	throw ResponseException(404);
}

void		validateRequest(Config& config, HttpRequest& request)
{
	HttpRequestLine		requestLine = request.getRequestLine();
	HttpRequestHeader	requestHeader = request.getHttpRequestHeader();
	std::string			method = requestLine.getMethod();

	// 1) Syntax Check
	HttpValidator::CheckRequestLineSyntax(requestLine);
	HttpValidator::CheckRequestHeaderSyntax(requestHeader);

	// 2) find Server
	ServerInfo serverInfo = HttpHandler::findServerInfo(config, requestHeader);

	// 3) find Location
	LocationBlock location = HttpHandler::findLocation(serverInfo, requestLine.getRequestURI());

	// 4) limit_except Check
	HttpValidator::MethodPermitted(location, method);
		// 메서드가 허용된지 확인하는 로직
		// 허용되지 않으면 예외를 던질 수 있음
}