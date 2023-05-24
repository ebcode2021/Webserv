#include "ServerInfo.hpp"

ServerInfo::ServerInfo(ServerBlock &serverBlcok, std::vector<LocationBlock> &locationBlock) {
	this->_serverBlock = serverBlcok;
	this->_locationList = locationBlock;
}


///////////
ServerBlock&	ServerInfo::getServerBlock() { return(this->_serverBlock); }
std::vector<LocationBlock>	ServerInfo::getLocationList() { return(this->_locationList);};



// test
using namespace std;
void	ServerInfo::printServerInfo() {
	this->_serverBlock.printInfo();
	cout << "\n";
	for (size_t i = 0; i < this->_locationList.size(); i++)
	{
		this->_locationList[i].printLocationBlock();
	}
	cout << "------------------------\n";
}
