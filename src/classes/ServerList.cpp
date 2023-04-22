# include "ServerList.hpp"
# include "webserv.hpp"

static std::vector<std::string> LocationBlockBackup(std::ifstream& confFile, std::string line) {
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
			// std::cout << "백업 = " << backup << std::endl;
			backup = "";
		}
		else if (splittedLine[0].compare("{") != 0)
			locationBlock.push_back(line);
	}
	return (locationBlock);
}

void	ServerList::addServer(std::ifstream & confFile) {
	std::string line;
	std::vector<std::string> splittedLine;
	std::vector<std::vector<std::string> > locationBlockInfo;
	std::vector<LocationBlock> locationBlock;
	ServerBlock	serverBlock;
	
	///
	std::cout << "서버 블록 입장" << std::endl;
	///

	while (std::getline(confFile, line))
	{
		splittedLine = split(line, static_cast<std::string>(WHITESPACE) + ";");
		if (splittedLine[0].compare("location") == 0)
			locationBlockInfo.push_back(LocationBlockBackup(confFile, line));
		else if (splittedLine[0].compare("}") == 0)
			break ;
		else
			serverBlock.configsetting(splittedLine);
	}
	//serverBlock.printInfo();
	/// 로케이션 생성해야됨!
	for (size_t i = 0; i < locationBlockInfo.size(); i++) {
		locationBlock.push_back(LocationBlock(serverBlock, locationBlockInfo[i]));
	}	
	///
}


void	ServerList::printserverList() {
	for (size_t i = 0; i < this->_serverList.size(); i++)
	{
		this->_serverList[i].printServerInfo();
	}
	
}