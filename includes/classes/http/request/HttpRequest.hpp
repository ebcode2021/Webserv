#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include "webserv.hpp"
# include "HttpRequestLine.hpp"
# include "HttpRequestHeader.hpp"
# include "HttpBody.hpp"

class	HttpRequest
{
	private :
		HttpRequestLine		_httpRequestLine;
		HttpRequestHeader	_httpRequestHeader;
		HttpBody			_httpBody;

	public :
		// constructor
		HttpRequest();

		// getter
		HttpRequestLine				&getHttpRequestLine();
		const HttpRequestHeader		&getHttpRequestHeader() const;
		HttpBody					&getHttpBody();

		// method
		int						createRequest(std::string &, ReadPhase &);

		// print
		void	print();
};

#endif
