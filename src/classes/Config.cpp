#include "webserv.hpp"
#include "Config.hpp"

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
			this->_serverList.addServer(confFile);
	}
}

enum	blockType
{
	server = 0,
	location = 1,
	other = 2,
};

bool Config::fileCheck(std::string fileName)
{
	std::ifstream				infile;
	std::string					line;
	std::vector<std::string>	splitted;

	infile.open(fileName);
	while (std::getline(infile, line))
	{
		splitted = split(line, " ");

		if (splitted[0].compare("http") == 0) {
			ServerBlock::blockCheck(infile);
		}
		else {
			// 지시어, 밸류 확인, 중복 확인
		}
	}
	infile.close();
	return (true);
}


// test print
void	Config::printServerList() {
	this->_serverList.
}