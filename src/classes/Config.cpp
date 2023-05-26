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
		if (splitedLine[0].compare("server") == 0)
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
	
	for (size_t i = 0; i < locationBlockInfo.size(); i++) {
		locationBlock.push_back(LocationBlock(serverBlock, locationBlockInfo[i]));
	}	

	std::cout << "로케이션 클래스 저장 완료" << std::endl;
	this->_serverList.push_back(ServerInfo(serverBlock, locationBlock));

	
	///
}



////////////////////

//size_t	Config::getServerListSize() { return(this->_serverList.size()); }

std::vector<ServerInfo>&	Config::getServerList() { return(this->_serverList); }

# define HOST_N_PORT 100
# define ONLY_PORT 	 101

ServerInfo&	Config::findServerInfoByHost(const std::string& host)
{
	// 127.0.0.1:8080 도 처리

	// request inform
	std::vector<std::string>	splittedHost = split(host, ":");
	std::string					serverName   = splittedHost[0];
	size_t						port         = std::atoi(splittedHost[1].c_str());

	// config inform
	std::vector<ServerInfo>		serverList = this->_serverList;
	size_t						serverListSize = this->_serverList.size();
	ServerInfo					defaultServer = serverList[0];

	// each data from ServerInfo
	std::vector<std::string>	serverNameList;
	size_t						serverNameListSize;
	std::vector<int>			listenList;
	size_t			 			listenListeSize;

	return (findServerInfoByParamter(serverName, port));
}
	// 1. port가 일치하는 서버 블럭 저장
		// 하나도 없으면 default server
	// 2. compare 'host name'

	// 1. compare 'server_list' and 'host' && compare 'listen' and 'port'
	// for (size_t i = 0; i < serverListSize; i++)
	// {
	// 	ServerBlock serverBlock = serverList[i].getServerBlock();

	// 	serverNameList = serverBlock.getServerNameList();
	// 	serverNameListSize = serverNameList.size();

	// 	listenList = serverBlock.getListenList();
	// 	listenListeSize = listenList.size();

	// 	for (size_t j = 0; j < serverNameListSize; j++)
	// 	{
	// 		if (serverNameList[j].compare(serverName) == 0)
	// 		{
	// 			for (size_t k = 1; k < listenListeSize; k++)
	// 			{
	// 				if (port == (size_t)listenList[k])
	// 					return (serverList[i]);
	// 			}
	// 		}
	// 	}
	// }
	// server_name naver, google;
	// listen 8080;
	// listen 9090;

	// // 2. compare port
	// for (size_t i = 0; i < serverListSize; i++)
	// {
	// 	ServerBlock serverBlock = serverList[i].getServerBlock();

	// 	serverNameList = serverBlock.getServerNameList();
	// 	serverNameListSize = serverNameList.size();

	// 	listenList = serverBlock.getListenList();
	// 	listenListeSize = listenList.size();

	// 	for (size_t j = 0; j < serverNameListSize; j++)
	// 	{
	// 		for (size_t k = 1; k < listenListeSize; k++)
	// 		{
	// 			if (port == (size_t)listenList[k])
	// 				return (serverList[i]);
	// 		}
	// 	}
	// }

// 	// 3. default Server
// 	return (defaultServer);
// }