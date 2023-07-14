#include "ServerInfo.hpp"

static std::vector<std::string> locationBlockBackup(std::ifstream& confFile, std::string line);

/* constructor */
ServerInfo::ServerInfo(std::ifstream &file)
{
	std::string								line;
	std::vector<std::string>				splittedLine;
	std::vector<std::vector<std::string> >	backupLocation;

	while (std::getline(file, line))
	{
		splittedLine = split(line, WHITESPACE + ";");
		if (splittedLine.size() == 0)
			continue ;
		else if (splittedLine[0].compare("location"))
			backupLocation.push_back(locationBlockBackup(file, line));
		else if (splittedLine[0].compare("}") == 0)
			break ;
		else
			this->_serverBlock.configsetting(splittedLine);
	}
	this->_locationList.push_back(LocationBlock(this->_serverBlock));
	for (size_t i = 0; i < backupLocation.size(); i++)
		this->_locationList.push_back(LocationBlock(this->_serverBlock, backupLocation[i]));
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

static std::vector<std::string> locationBlockBackup(std::ifstream& confFile, std::string line)
{
	std::vector<std::string>	locationBlock;
	std::vector<std::string>	splittedLine;
	std::string					backup;
	
	locationBlock.push_back(line);
	while (std::getline(confFile, line))
	{
		splittedLine = split(line, WHITESPACE);
		if (splittedLine[0].compare("}") == 0)
			break ;
		else if (splittedLine[0].compare("limit_except") == 0) {
			backup += line + "\n";
			while (std::getline(confFile, line))
			{
				splittedLine = split(line, WHITESPACE);
				if (splittedLine[0] == "}")
					break;
				backup += line + "\n";
			}
			locationBlock.push_back(backup);
			backup = "";
		}
		else if (splittedLine[0].compare("{") != 0)
			locationBlock.push_back(line);
	}
	return (locationBlock);
}

/* print */
void	ServerInfo::printServerInfo() const {
	this->_serverBlock.printInfo();
	std::cout << "\n";
	for (size_t i = 0; i < this->_locationList.size(); i++)
	{
		this->_locationList[i].printInfo();
	}
	std::cout << "------------------------" << std::endl;
}
