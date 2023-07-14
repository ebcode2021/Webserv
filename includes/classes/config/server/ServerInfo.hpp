#ifndef SERVERINFO_HPP
# define SERVERINFO_HPP

# include "LocationBlock.hpp"
# include "ServerBlock.hpp"
//# include "HttpRequestHeader.hpp"

class ServerInfo {
	private :
		ServerBlock					_serverBlock;
		std::vector<LocationBlock>	_locationList;

	public :
		// constructor
		ServerInfo(std::ifstream &);

		// getter, setter
		ServerBlock&				getServerBlock();
		std::vector<LocationBlock>	getLocationList();
		
		// method
		LocationBlock		findLocationBlockByURL(const std::string&);

		// print
		void printServerInfo() const;

};

#endif