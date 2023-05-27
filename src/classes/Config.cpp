#include "Config.hpp"
#include "indication.hpp"
#include "enum.hpp"
#include "notice.hpp"

Config::Config(std::string fileName)
{
	std::string					line;
	std::ifstream				confFile(fileName);
	std::vector<std::string>	splitedLine;
	///
	std::cout << "설정 파일 시작 지점" << std::endl;
	///
	if (!confFile.is_open())
		printErrorWithExit("Invaild FileName");
	while (std::getline(confFile, line))
	{
		splitedLine = split(line, WHITESPACE);
		if (splitedLine.size() && splitedLine[0].compare("server") == 0)
			addServer(confFile);
	}
	std::cout << "설정 끝" << std::endl;
}

bool Config::fileCheck(int argc, char *argv[])
{
	std::ifstream				infile;
	std::string					line;
	std::vector<std::string>	splitted;

	// fileMode를 int로
	fileMode mode = Validate::argumentCheck(argc, argv);
	if (mode)
	{
		Validate dataset;
		infile.open(std::string(argv[1]));
		if (infile.fail())
			printErrorWithExit(CHECK_CONFIG_FILE);
		while (std::getline(infile, line))
		{
			splitted = split(line, WHITESPACE);
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
		if (mode == test)
			notice::printMessage(TEST_SUCCESS);
		else
			return true;
	}
	return false;
}

// void	Config::printServerList() {
// 	this->_serverList.printserverList();
// }

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
			//std::cout << "백업 = " << backup << std::endl;
			backup = "";
		}
		else if (splittedLine[0].compare("{") != 0)
			locationBlock.push_back(line);
	}
	return (locationBlock);
}

void	Config::addServer(std::ifstream & confFile) {
	std::string line;
	std::vector<std::string> splittedLine;
	std::vector<std::vector<std::string> > locationBlockInfo;
	std::vector<LocationBlock> locationBlock;
	ServerBlock	serverBlock;
	
	///
	std::cout << "\n";
	std::cout << "서버 클래스 저장 시작" << std::endl;
	///

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

	//serverBlock.printInfo();
	/// 로케이션 생성해야됨!

	std::cout << "\n";
	std::cout << "로케이션 클래스 저장 시작" << std::endl;
	
	locationBlock.push_back(LocationBlock(serverBlock));
	
	for (size_t i = 0; i < locationBlockInfo.size(); i++) {
		locationBlock.push_back(LocationBlock(serverBlock, locationBlockInfo[i]));
	}	

	std::cout << "로케이션 클래스 저장 완료" << std::endl;
	this->_serverList.push_back(ServerInfo(serverBlock, locationBlock));
}



////////////////////

std::vector<ServerInfo>&	Config::getServerList() { return(this->_serverList); }

ServerInfo	Config::findServerInfoByHost(const std::string& host)
{
	// 127.0.0.1:8080 도 처리

	// request inform
	std::vector<std::string>	splittedHost = split(host, ":");
	std::string					serverName   = splittedHost[0];
	size_t						port         = std::atoi(splittedHost[1].c_str());

	return (findServerInfoByParameter(serverName, port));
}

ServerInfo	Config::findServerInfoByParameter(std::string& serverName, size_t port)
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
	std::cout << portListSize << std::endl;
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