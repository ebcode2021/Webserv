#ifndef SERVER_HPP
# define SERVER_HPP

# include "ServerBlock.hpp"
# include "webserv.hpp"
# include "ServerInfo.hpp"
# include "SessionStorage.hpp"
# include "TcpSocket.hpp"
# include "Config.hpp"
# include "KqueueHandler.hpp"
# include "SocketEventHandler.hpp"
# include "HttpResponse.hpp"

class	Server
{
	private :
		const std::vector<ServerInfo>	_serverList;
		std::set<int>			_listenportList;
		std::set<int>			_listenSockList;
		SessionStorage			_sessionStorage;

	public :
		// constructor
		Server(const Config &);

		// method
		void	run();
		void	addServer(std::ifstream&);
		void	initListenSocket(KqueueHandler&);
		bool	isListenSocketEvent(uintptr_t&);

};

#endif