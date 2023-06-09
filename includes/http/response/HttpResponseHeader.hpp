#ifndef HTTP_RESPONSE_HEADER_HPP
# define HTTP_RESPONSE_HEADER_HPP

# include "webserv.hpp"
# include "HttpRequest.hpp"
# include "PathInfo.hpp"

class	HttpResponseHeader
{
	private :
		std::string					_date;
		std::string					_server;
		std::string					_contentType;
		size_t						_contentLength;
		std::string					_transferEncoding;
		std::vector<std::string>	_setCookie;

	public :
		// constructor
		HttpResponseHeader();

		// getter, setter
		std::string					getDate() const;
		std::string					getServer() const;
		std::string					getContentType() const;
		size_t						getContentLength() const;
		std::string					getTransferEncoding() const;
		std::vector<std::string>	getSetCookie() const;

		void						setDate(const std::string&);
		void						setServer(const std::string&);
		void						setContentType(const std::string&);
		void						setContentLength(const size_t);
		void						setTransferEncoding(const std::string&);
		void						setSetCookie(const std::string&);

		// method
		std::string					getResponseHeaderToString();
		std::string					getCookieString();

		// print
		void						printCookie();
};

#endif