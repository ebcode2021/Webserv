#include "Config.hpp"


/* constructor */
Config::Config(const std::string &fileName)
{
	std::string					line;
	std::ifstream				confFile(fileName);
	std::vector<std::string>	splitedLine;

	if (!confFile.is_open())
		printErrorWithExit(CHECK_CONFIG_FILE);
	while (std::getline(confFile, line))
	{
		splitedLine = split(line, WHITESPACE);
		if (splitedLine.size() == 0)
			continue ;
		if (splitedLine.size() && splitedLine[0].compare("server") == 0)
			this->_serverInfoList.insert(ServerInfo(confFile));
	}
	
	for (size_t i = 0; i < this->_serverInfoList.size(); i++)
	{
		ServerBlock server = this->_serverInfoList[i].getServerBlock();
		std::vector<int> listenSockList = server.getListenPortList();

		for (size_t j = 0; j < listenSockList.size(); j++) {
			this->_serverPortList.insert(listenSockList[j]);
		}
	}
	
}

/* getter, setter */
const std::set<int>	&Config::getServerPortList() const {
	return (this->_serverPortList);
}

const ServerInfoList	&Config::getServerInfoList() const {
	return(this->_serverInfoList);
}

/* checker */
bool	Config::fileCheck(int argc, char *argv[])
{
	std::ifstream				infile(argv[1]);
	std::string					line;
	std::vector<std::string>	splitted;

	Validate::argumentCheck(argc, argv);
	Validate dataset;
	if (infile.is_open())
	{
		while (std::getline(infile, line))
		{
			splitted = split(line, WHITESPACE);
			if (splitted.size() == 0)
				continue;
			if (splitted[0].compare("server") == 0)
			{
				if (splitted.size() != 1)
					fileErrorWithExit(BLOCK_NAME, infile);
				ServerBlock::blockCheck(infile, dataset);
			}
			else
				fileErrorWithExit(UNDEFINED_LINE, infile);
		} 
		infile.close();
	}
	else
		printErrorWithExit(CHECK_CONFIG_FILE);

	if (argc == 2)
		return (true);
	else
	{
		return (false);
	}
}

void	Config::printConfig()
{
	std::cout << "---------Port List----------" << std::endl;

	for (std::set<int>::const_iterator it = this->_serverPortList.begin(); it != _serverPortList.end(); it++)
	{
		std::cout << *it << std::endl;
	}

	for (size_t i = 0; i < this->_serverInfoList.size(); i++)
	{
		std::cout << "-----server " << i << "----------" << std::endl;
		_serverInfoList[i].printServerInfo();
	}
	
}
