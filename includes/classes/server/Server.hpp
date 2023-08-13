#ifndef SERVER_HPP
# define SERVER_HPP

# include "webserv.hpp"
# include "Config.hpp"
# include "KqHandler.hpp"
# include "SockInfo.hpp"

class	Server
{
	private :
		const ServerInfoList			&_serverInfoList;
		const std::set<int>				&_serverPortList;
		KqHandler						kq;

	public :
		// constructor
		Server(const Config &);

		// method
		void	run();
		void	processEvent();
		void	processReadEvent(SockInfo *sockInfo);
		// void	addServer(std::ifstream&);
		// void	initListenSocket(KqueueHandler&);
		// bool	isListenSocketEvent(uintptr_t&);

};

#endif