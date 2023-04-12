#include "Config.hpp"

Config::Config(std::string fileName)
{
	
}

enum	blockType
{
	server = 2,
	location = 3,
	other = 4,
};

bool Config::fileCheck(std::string fileName)
{
	std::ifstream				infile;
	std::string					line;
	std::vector<std::string>	splitted;

	infile.open(fileName);
	while (std::getline(infile, line))
	{
		splitted = split(line, ' ');

		if (splitted[0].compare("http") == 0) {
			ServerBlock::blockCheck(infile);
		}
		else {
			// 지시어, 밸류 확인, 중복 확인
		}
	}
	infile.close();
}