#ifndef SERVERINFO_HPP
# define SERVERINFO_HPP

# include "LocationBlock.hpp"
# include "ServerBlock.hpp"
# include "HttpRequestHeader.hpp"

class ServerInfo {
	private :
		ServerBlock _serverBlock;
		std::vector<LocationBlock> _locationList;

	public :
		ServerInfo();
		ServerInfo(ServerBlock&, std::vector<LocationBlock>&);

		// test
		void printServerInfo();

		///////
		ServerBlock&	getServerBlock();
		std::vector<LocationBlock>	getLocationList();
		
		LocationBlock&		findLocationBlockByURL(const std::string&);

		// static
		//ServerInfo&	findServerInfo(const HttpRequestHeader&);

		// bool	operator==(const ServerInfo& other) const
		// {
		// 	const std::vector<std::string>	serverNameList = this->_serverBlock.getServerNameList();
		// 	const std::vector<std::string>	otherServerNameList = other._serverBlock.getServerNameList();
		// 	size_t	listSize = serverNameList.size();

		// 	if (listSize != otherServerNameList.size())
		// 		return (false);
			
		// 	for (size_t i = 0; i < listSize; ++i)
		// 	{
		// 		if (serverNameList[i] != otherServerNameList[i])
		// 			return (false);
		// 	}
		// 	return (true);
		// }
};

#endif