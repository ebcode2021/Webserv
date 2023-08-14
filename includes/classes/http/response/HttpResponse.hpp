#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP

# include "webserv.hpp"
# include "HttpResponseLine.hpp"
# include "HttpResponseHeader.hpp"
# include "HttpBody.hpp"


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


		// setter
		HttpBody			&getBody();
		HttpResponseLine	&getResponseLine();
		HttpResponseHeader	&getResponseHeader();



		// print
		void						printHttpResponse();
};

#endif