#include "ServerInfo.hpp"

ServerInfo::ServerInfo(ServerBlock &serverBlcok, std::vector<LocationBlock> &locationBlock) {
	this->_serverBlock = serverBlcok;
	this->locationList = locationBlock;
}


///////////
ServerBlock&	ServerInfo::getServerBlock() { return(this->_serverBlock); }




// test
using namespace std;
void	ServerInfo::printServerInfo() {
	this->_serverBlock.printInfo();
	cout << "\n";
	for (size_t i = 0; i < this->locationList.size(); i++)
	{
		this->locationList[i].printLocationBlock();
	}
	cout << "------------------------\n";
}
