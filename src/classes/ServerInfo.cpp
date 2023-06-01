#include "ServerInfo.hpp"

/* constructor */
ServerInfo::ServerInfo(ServerBlock &serverBlcok, std::vector<LocationBlock> &locationBlock) {
	this->_serverBlock = serverBlcok;
	this->_locationList = locationBlock;
}

/* getter, setter */
ServerBlock&	ServerInfo::getServerBlock() {
	return(this->_serverBlock);
}

std::vector<LocationBlock>	ServerInfo::getLocationList() {
	return(this->_locationList);
}

/* method */
LocationBlock	ServerInfo::findLocationBlockByURL(const std::string& requestURL)
{
	std::vector<LocationBlock>	locationList = this->_locationList;
	size_t						locationListSize = locationList.size();
	//std::cout << "input url : " << requestURL << std::endl;
	for (size_t i = 1; i < locationListSize; i++)
	{
		LocationBlock	locationBlock = locationList[i];
		//std::cout << "--- location : " << locationBlock.getPath() << std::endl;
		if (locationBlock.getPath() == requestURL)
			return (locationBlock);
	}
	std::cout << "default location setting " << std::endl;
	locationList[0].setPath(requestURL);
	return (locationList[0]);
}

/* print */
void	ServerInfo::printServerInfo() {
	this->_serverBlock.printInfo();
	std::cout << "\n";
	for (size_t i = 0; i < this->_locationList.size(); i++)
	{
		this->_locationList[i].printInfo();
	}
	std::cout << "------------------------" << std::endl;
}
