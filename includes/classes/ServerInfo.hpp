#ifndef SERVERINFO_HPP
# define SERVERINFO_HPP

# include "LocationBlock.hpp"
# include "ServerBlock.hpp"
# include "HttpRequestHeader.hpp"

class ServerInfo {
	private :
		ServerBlock _serverBlock;
		std::vector<LocationBlock> locationList;

	public :
		ServerInfo() {};
		ServerInfo(ServerBlock&, std::vector<LocationBlock>&);

		// test
		void printServerInfo();

		///////
		ServerBlock&	getServerBlock();
		
		// static
		//ServerInfo&	findServerInfo(const HttpRequestHeader&);

};

#endif