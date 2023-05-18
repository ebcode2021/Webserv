#ifndef HTTPREQUESTHEADER_HPP
# define HTTPREQUESTHEADER_HPP

#include "webserv.hpp"

class	HttpRequestHeader
{
	private :
		std::string					_host;
		std::string					_userAgent;
		std::string					_connection;
		std::string					_contentType;
		size_t						_contentLength;
		std::string					_transferEncoding;
		std::string	_cookie;
		std::string					_sessionID;

	public :
		// getter, setter
		std::string					getHost();
		std::string					getUserAgent();
		std::string					getConnection();
		std::string					getContentType();
		size_t						getContentLength();
		std::string					getTransferEncoding() const;
		std::string	getCookie();
		std::string					getSessionID();

		void	setHost(std::string&);
		void	setUserAgent(std::string&);
		void	setConnection(std::string&);
		void	setContentType(std::string&);
		void	setContentLength(size_t);
		void	setTransferEncoding(std::string&);
		void	setCookie(std::string&);
		void	setSessionID(std::string&);
};

#endif