#include "webserv.hpp"
#include "utils.hpp"
#include "KqueueHandler.hpp"

std::set<int> createListenSocketForPorts(const std::set<int> & serverPortList)
{
	std::set<int> serverSockList;
	std::set<int>::const_iterator constIt;

	for (constIt = serverPortList.begin(); constIt != serverPortList.end(); constIt++)
	{
		int serverSockfd = createSocket();
		if (serverSockfd == INVALID_SOCKET) {
			printErrorWithExit(strerror(errno));
		}
	}
	
}

