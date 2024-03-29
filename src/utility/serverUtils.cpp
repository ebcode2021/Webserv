#include "webserv.hpp"
#include "utils.hpp"
#include "event.hpp"

void	createListenSocketForPorts(const std::set<int> & serverPortList, KqHandler &kq)
{
	std::set<int> serverSockList;
	std::set<int>::const_iterator constIt;

	for (constIt = serverPortList.begin(); constIt != serverPortList.end(); constIt++)
	{
		int serverSockfd = createSocket();
		if (serverSockfd == INVALID_SOCKET) {
			printErrorWithExit(SOCKET_ERROR_MSG);
		}
		SockInfo	*serverSock = new SockInfo(serverSockfd, *constIt, M_SERVER);
		sockBindAndListen(serverSockfd, *constIt);
		changeFdOpt(serverSockfd, O_NONBLOCK);
		kq.changeEvent(serverSockfd, EVFILT_READ, EV_ADD, 0, 0, serverSock);
	}
}

bool	isReturn(LocationBlock &block)
{
	if (block.getReturn().size() != 0)
		return (true);
	return (false);
}