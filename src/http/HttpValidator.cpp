#include "HttpValidator.hpp"
#include "HttpException.hpp"

void	HttpValidator::CheckRequestSyntax(const HttpRequestLine& requestLine)
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