#include "Server.hpp"
#include "utils.hpp"
#include "event.hpp"

Server::Server(const Config &config) :
	_serverList(config.getServerList()),
	_serverPortList(config.getServerPortList())
{}

void	Server::run()
{
	KqHandler kq;

	createListenSocketForPorts(this->_serverPortList, kq);
	while (true)
	{
		kq.eventUpdate();
		kq.changeListClear();
		processEvent(kq);
		kq.eventListClear();
	}
}