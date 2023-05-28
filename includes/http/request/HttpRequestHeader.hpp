#ifndef HTTPREQUESTHEADER_HPP
# define HTTPREQUESTHEADER_HPP

#include "webserv.hpp"
#include "LocationBlock.hpp"
#include "HttpException.hpp"

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
		std::string			getUserAgent();
		std::string			getConnection();
		std::string			getContentType();
		size_t				getContentLength();
		std::string			getTransferEncoding();
		std::string			getCookie();
		std::string			getSessionID();

		std::string			getServerNameToHost()
		{
			std::vector<std::string>	splittedHost = split(this->_host, ":");
			std::string					serverName   = splittedHost[0];
			return (serverName);
		};

		void				setHost(std::string&);
		void				setUserAgent(std::string&);
		void				setConnection(std::string&);
		void				setContentType(std::string&);
		void				setContentLength(size_t);
		void				setTransferEncoding(std::string&);
		void				setCookie(std::string&);
		void				setSessionID(std::string&);

		////
		void	validateRequestHeader(LocationBlock& locationBlock);
};

#endif