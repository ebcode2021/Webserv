#include "ServerInfoList.hpp"

// constructor
ServerInfoList::ServerInfoList() {}

ServerInfoList::ServerInfoList(std::vector<ServerInfo> &serverInfoList)
{
	_serverInfoList = serverInfoList;
}

static bool	comparePort(int port, ServerBlock& serverBlock)
{
	const std::vector<int> &portList = serverBlock.getListenPortList();

	for (size_t i = 0; i < portList.size(); i++)
	{
		if (port == portList[i])
			return (true);
	}
	return (false);
}

static bool compareHost(std::string &host, ServerBlock& serverBlock)
{
	const std::vector<std::string> &hostList = serverBlock.getServerNameList();

	for (size_t i = 0; i < hostList.size(); i++)
	{
		if (host == hostList[i])
			return (true);
	}
	return (false);
}

// getter
ServerInfo ServerInfoList::getServerInfoByPortAndHost(int port, std::string host)
{
	std::vector<ServerInfo> tempServerInfo;

	for (size_t i = 1; i < this->_serverInfoList.size(); i++)
	{
		if (comparePort(port, _serverInfoList[i].getServerBlock()))
			tempServerInfo.push_back(_serverInfoList[i]);
	}

	if (tempServerInfo.empty())
		return (this->_serverInfoList[0]);

	for(size_t i = 1; i < tempServerInfo.size(); i++)
	{
		if (compareHost(host, tempServerInfo[i].getServerBlock()))
			return tempServerInfo[i];
	}
	return (tempServerInfo[0]);
}

// method
void	ServerInfoList::insert(ServerInfo serverInfo)
{
	this->_serverInfoList.push_back(serverInfo);
}

size_t	ServerInfoList::size()
{
	return	this->_serverInfoList.size();
}

// Operator Overloading
ServerInfo	&ServerInfoList::operator[](int index)
{
	return (this->_serverInfoList[index]);
}