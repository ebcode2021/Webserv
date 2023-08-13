#include "ServerInfo.hpp"

static std::vector<std::string> locationBlockBackup(std::ifstream& confFile, std::string line);

/* constructor */

ServerInfo::ServerInfo() {}

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
		else if (splittedLine[0].compare("location") == 0)
		{	
			backupLocation.push_back(locationBlockBackup(file, line));
		}
		else if (splittedLine[0].compare("}") == 0)
			break ;
		else {
			this->_serverBlock.configsetting(splittedLine);
		}
	}
	this->_locationMap.insert(std::make_pair("default", LocationBlock(this->_serverBlock)));
	for (size_t i = 0; i < backupLocation.size(); i++) {
		LocationBlock locationBlock(this->_serverBlock, backupLocation[i]);
		this->_locationMap.insert(std::make_pair(locationBlock.getPath(), locationBlock));
	}
}

/* getter, setter */

ServerBlock&	ServerInfo::getServerBlock() {
	return(this->_serverBlock);
}

std::map<std::string, LocationBlock>	ServerInfo::getLocationMap() {
	return (this->_locationMap);
}

/* method */
LocationBlock	ServerInfo::getLocationBlockByURL(const std::string& requestURL)
{
	std::map<std::string, LocationBlock>::iterator it;

	it = this->_locationMap.find(requestURL);
	if (it == _locationMap.end())
		return (this->_locationMap["default"]);
	return it->second;
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

	std::map<std::string, LocationBlock>::const_iterator it;

	this->_serverBlock.printInfo();
	
	std::cout << "\n";
	for (it = this->_locationMap.begin(); it != this->_locationMap.end(); it++)
	{
		it->second.printInfo();
	}
	std::cout << "------------------------" << std::endl;
}
