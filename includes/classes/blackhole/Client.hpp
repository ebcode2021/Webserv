#ifndef	CLIENT_HPP
# define CLIENT_HPP

# include "webserv.hpp"
# include "HttpRequest.hpp"

class	Client
{
	private :
		SocketInfo	_socketInfo;
		HttpRequest	_request;
		int			_readMode;
		std::string	_clientAddr;
	
	public :
		
};

#endif