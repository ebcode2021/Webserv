#ifndef SERVER_HPP
# define SERVER_HPP

# include "webserv.hpp"
# include "Config.hpp"
# include "KqHandler.hpp"
# include "SessionStorage.hpp"
# include "SockInfo.hpp"

class	Server
{
	private :
		const ServerInfoList		&_serverInfoList;
		const std::set<int>			&_serverPortList;
		SessionStorage		_sessionStorage;
		KqHandler					kq;

	public :
		// constructor
		Server(const Config &);

		// getter
		ServerInfoList		getServerInfoList();

		// method
		void	run();
		void	processEvent();
		void	processWriteEvent(SockInfo *sockInfo, KqHandler&);
		void	processReadEvent(SockInfo *sockInfo);
};

#endif