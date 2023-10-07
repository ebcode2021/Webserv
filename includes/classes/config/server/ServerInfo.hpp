#ifndef SERVERINFO_HPP
# define SERVERINFO_HPP

# include "LocationBlock.hpp"
# include "ServerBlock.hpp"
# include "SessionStorage.hpp"

class ServerInfo {
	private :
		ServerBlock								_serverBlock;
		std::map<std::string, LocationBlock>	_locationMap;

	public :
		// constructor
		ServerInfo();
		ServerInfo(std::ifstream &);

		// getter, setter
		ServerBlock&							getServerBlock();
		std::map<std::string, LocationBlock>	getLocationMap();
		
		// method
		LocationBlock		getLocationBlockByURL(const std::string&);

		// print
		void printServerInfo() const;

};

#endif