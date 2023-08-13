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
		HttpResponse(int, HttpBody &);

		// getter


		// setter
		std::string					getBody() const;
		HttpResponseHeader&			getResponseHeader();
		HttpResponseLine&			getResponseLine();



		// print
		void						printHttpResponse();
};
#endif