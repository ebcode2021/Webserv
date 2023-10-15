#ifndef SERVERINFOLIST_HPP
# define SERVERINFOLIST_HPP

# include "ServerInfo.hpp"

class ServerInfoList
{
	private :
		std::vector<ServerInfo>	_serverInfoList;

	public :
		//	constructor
		ServerInfoList();
		ServerInfoList(std::vector<ServerInfo> &);

		//	getter
		ServerInfo	getServerInfoByPortAndHost(int, std::string);

		//	method
		void	insert(ServerInfo);
		size_t	size();

		//	Operator Overloading
		ServerInfo	&operator[](int);
};

#endif