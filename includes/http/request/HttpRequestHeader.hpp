#ifndef HTTPREQUESTHEADER_HPP
# define HTTPREQUESTHEADER_HPP

#include "webserv.hpp"
#include "LocationBlock.hpp"
#include "ResponseException.hpp"

class	HttpRequestHeader
{
	private :
		std::string			_host;
		std::string			_userAgent;
		std::string			_connection;
		std::string			_contentType;
		size_t				_contentLength;
		std::string			_transferEncoding;
		std::string			_cookie;
		std::string			_sessionID;

	public :
		HttpRequestHeader();
	
		// getter, setter
		std::string			getHost() const;
		std::string			getUserAgent() const;
		std::string			getConnection() const;
		std::string			getContentType() const;
		size_t				getContentLength() const;
		std::string			getTransferEncoding() const;
		std::string			getCookie() const;
		std::string			getSessionID() const;

		void				setHost(std::string&);
		void				setUserAgent(std::string&);
		void				setConnection(std::string&);
		void				setContentType(std::string&);
		void				setContentLength(size_t);
		void				setTransferEncoding(std::string&);
		void				setCookie(std::string&);

		/* method */
		std::string			getServerNameToHost();
		
		/* exception */
		void				validateRequestHeader(LocationBlock& locationBlock);
};

#endif