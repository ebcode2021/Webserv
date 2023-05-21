#include "HttpValidator.hpp"
#include "HttpException.hpp"

void	HttpValidator::ValidateRequestLine(Config& config, const HttpRequestLine& requestLine)
{
	(void)config;
	// check method
	if (METHODS->find(requestLine.getMethod()) == std::string::npos)
		throw ResponseException(400);

	// check http-version
	if (requestLine.getVersion() != "HTTP/1.1")
		throw ResponseException(400);
}
