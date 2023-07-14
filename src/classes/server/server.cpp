# include "Server.hpp"

Server::Server(const Config &config) :
	_serverList(config.getServerList()),
	_serverPortList(config.getServerPortList())
{
	
}

void	Server::run()
{
	KqueueHandler kq;
	
	
}