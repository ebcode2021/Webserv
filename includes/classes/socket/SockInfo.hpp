#ifndef SOCKINFO_HPP
# define SOCKINFO_HPP

# include "webserv.hpp"
# include "SockData.hpp"
# include "ModeInfo.hpp"
# include "HttpRequest.hpp"
# include "HttpResponse.hpp"
# include "CgiInfo.hpp"

class SockInfo
{
	private :
		int				_sockFd;
		HttpStatus		_status;
		int				_clientport;
		int				_serverPort;
		std::string		_ip;
		ModeInfo		_modeInfo;
		SockData		_sockData;
		HttpRequest		_request;
		HttpResponse	_response;
		CgiInfo			*_cgiInfo;

	public :
		// constructor
		SockInfo(int, std::string, int, int, SockMode);
		SockInfo(int, int, SockMode);

		// getter
		int	 			getSockFd() const;
		HttpStatus		&getStatus();
		ModeInfo		&getModeInfo();
		SockData		&getSockData();
		HttpRequest		&getRequest();
		HttpResponse	&getResponse();
		int				getClientPort();
		int				getServerPort();
		std::string		getClientIp();
		CgiInfo			*getCgiInfo();

		// setter
		void			setResponse(HttpResponse);
		void			setCgiInfo(CgiInfo	*cgiInfo);
		void			reset();
};

#endif