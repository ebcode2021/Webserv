#ifndef SERVER_HPP
# define SERVER_HPP

# include "webserv.hpp"
# include "Config.hpp"
# include "KqueueHandler.hpp"

class	Server
{
	private :
		const std::vector<ServerInfo>	&_serverList;
		const std::set<int>				&_serverPortList;

	public :
		// constructor
		Server(const Config &);

		// method
		void	run();
		// void	addServer(std::ifstream&);
		// void	initListenSocket(KqueueHandler&);
		// bool	isListenSocketEvent(uintptr_t&);

};

#endif