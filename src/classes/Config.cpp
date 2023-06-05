#include "Config.hpp"

static std::vector<std::string> LocationBlockBackup(std::ifstream& confFile, std::string line);

/* constructor */
Config::Config(std::string fileName)
{
	std::string					line;
	std::ifstream				confFile(fileName);
	std::vector<std::string>	splitedLine;

	if (!confFile.is_open())
		printErrorWithExit(CHECK_CONFIG_FILE);

	while (std::getline(confFile, line))
	{
		splitedLine = split(line, WHITESPACE);
		if (splitedLine.size() && splitedLine[0].compare("server") == 0)
			addServer(confFile);
	}
	
	for (size_t i = 0; i < this->_serverList.size(); i++)
	{
		ServerBlock server = this->_serverList[i].getServerBlock();
		std::vector<int> listenSockList = server.getListenList();

		for (size_t j = 0; j < listenSockList.size(); j++)
			this->_listenSockList.insert(listenSockList[i]);
	}
	std::cout << "설정 끝" << std::endl;
}

/* getter, setter */
std::set<int>	Config::getListenSockList() {
	return (this->_listenSockList);
}

std::vector<ServerInfo>	Config::getServerList() {
	return(this->_serverList);
}

/* checker */
void	Config::fileCheck(int argc, char *argv[])
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

	if (argc == 3)
	{
		std::cout << TEST_SUCCESS << std::endl;
		exit(0);
	}
}

/* method */
void	Config::addServer(std::ifstream & confFile)
{
	std::string 							line;
	std::vector<std::string>				splittedLine;
	std::vector<std::vector<std::string> >	locationBlockInfo;
	std::vector<LocationBlock>				locationBlock;
	
	ServerBlock	serverBlock;
	
	std::cout << "\n";
	std::cout << "서버 클래스 저장 시작" << std::endl;

	while (std::getline(confFile, line))
	{
		std::cout << line << std::endl;
		splittedLine = split(line, WHITESPACE + ";");
		if (splittedLine[0].compare("location") == 0)
			locationBlockInfo.push_back(LocationBlockBackup(confFile, line));
		else if (splittedLine[0].compare("}") == 0)
			break ;
		else
			serverBlock.configsetting(splittedLine);
	}

	std::cout << "서버 클래스 저장 완료" << std::endl;

	std::cout << "\n";
	std::cout << "로케이션 클래스 저장 시작" << std::endl;
	
	locationBlock.push_back(LocationBlock(serverBlock));
	
	for (size_t i = 0; i < locationBlockInfo.size(); i++)
		locationBlock.push_back(LocationBlock(serverBlock, locationBlockInfo[i]));

	std::cout << "로케이션 클래스 저장 완료" << std::endl;
	this->_serverList.push_back(ServerInfo(serverBlock, locationBlock));
}

ServerInfo	Config::findServerInfoByHost(const std::string& host)
{
	// request inform
	std::vector<std::string>	splittedHost = split(host, ":");
	std::string					serverName   = splittedHost[0];
	size_t						port         = std::atoi(splittedHost[1].c_str());

	return (findServerInfoByParameter(serverName, port));
}

ServerInfo	Config::findServerInfoByParameter(const std::string& serverName, const size_t port)
{
	// config inform
	std::vector<ServerInfo>		serverList = this->_serverList;
	size_t						serverListSize = this->_serverList.size();
	ServerInfo					defaultServer = serverList[0];

	// each data from ServerInfo
	std::vector<int>			listenList;
	size_t			 			listenListeSize;

	// 1. save ServerInfo matching port
	std::vector<ServerInfo>	 portList;
	for (size_t i = 0; i < serverListSize; i++)
	{
		ServerBlock serverBlock = serverList[i].getServerBlock();

		listenList = serverBlock.getListenList();
		listenListeSize = listenList.size();

		for (size_t j = 1; j < listenListeSize; j++)
		{
			if ((size_t)listenList[j] == port)
			 portList.push_back(serverList[i]);
		}
	}

	if (portList.empty())
		return (defaultServer);


	// 2. compare server_name
	std::vector<std::string>	serverNameList;
	size_t						serverNameListSize;

	size_t	portListSize = portList.size();
	for (size_t i = 0; i < portListSize; i++)
	{
		ServerBlock serverBlock  = portList[i].getServerBlock();

		serverNameList = serverBlock.getServerNameList();
		serverNameListSize = serverNameList.size();
		for (size_t j = 0; j < serverNameListSize; j++)
		{
			if (serverNameList[j] == serverName)
				return (portList[i]);
		}
	}
	return (portList[0]);
}

static std::vector<std::string> LocationBlockBackup(std::ifstream& confFile, std::string line)
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