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

		// getter, setter
		HttpRequestLine				&getHttpRequestLine();
		const HttpRequestHeader		&getHttpRequestHeader() const;
		HttpBody					&getHttpBody();
		//void					setRequestLine(std::vector<std::string>);
		//void					setHeaderField(std::map<std::string, std::string>);
		//void					setBody(const std::string&);

		int						createRequest(std::string &, ReadPhase &);

		// parser
		//static void 			parseHeaderAndBody(const std::string&, std::vector<std::string>&, std::string&);
		
		// method
		//void					splitHeader(std::vector<std::string>&);
		//static std::map<std::string, std::string>	createHeaderField(std::vector<std::string>&);
		
		// print
		void	print();
};

#endif