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
}

bool Config::fileCheck(int argc, char *argv[])
{
	std::ifstream				infile;
	std::string					line;
	std::vector<std::string>	splitted;

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
			// std::cout << "백업 = " << backup << std::endl;
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
		splittedLine = split(line, static_cast<std::string>(WHITESPACE) + ";");
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


