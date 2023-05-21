#ifndef HTTP_VALIDATOR_HPP
# define HTTP_VALIDATOR_HPP

# include "TcpSocket.hpp"
# include "webserv.hpp"
# include "HttpRequestLine.hpp"
# include "HttpRequestHeader.hpp"
# include "HttpBody.hpp"
# include "Config.hpp"

namespace	HttpValidator
{
	// check method and http-version
	void	ValidateRequestLine(Config&, const HttpRequestLine&);
}

namespace	HttpHandler
{
	// void	ValidateRequestLine(Config&, const HttpRequestLine&);
	//void	ValidateRequestHeader(Config&, const HttpRequestHeader&);
	//void	ValidateRequestBody(Config&, const HttpBody&);
}

namespace	ResponseHandler
{
	void	setSuccessStatas();
}

// namespace	ResponseHandler
// {

// }

#endif
