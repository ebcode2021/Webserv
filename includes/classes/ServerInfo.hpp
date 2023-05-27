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
		
		LocationBlock		findLocationBlockByURL(const std::string&);

		// static
		//ServerInfo&	findServerInfo(const HttpRequestHeader&);
};

#endif