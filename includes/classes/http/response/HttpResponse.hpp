#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP

# include "webserv.hpp"
# include "HttpResponseLine.hpp"
# include "HttpResponseHeader.hpp"
# include "HttpBody.hpp"
# include "PathInfo.hpp"

class SockInfo;

class	HttpResponse
{
	private :
		HttpResponseLine	_httpResponseLine; 
		HttpResponseHeader	_httpResponseHeader;
		HttpBody			_httpBody;

	public :
		// constructor
		HttpResponse();
		HttpResponse(HttpStatus);

		// getter
		HttpBody			&getBody();
		HttpResponseLine	&getResponseLine();
		HttpResponseHeader	&getResponseHeader();

		// method
		void	createResponse(HttpStatus &, PathInfo &);
		void	createResponse(HttpStatus &, PathInfo &, std::string &);
		void	createErrorPage(HttpStatus &, LocationBlock &);
		void	createRedirect(const std::string &path);
		void	createNotModified();

		// print
		void	printHttpResponse();
};

#endif