#include "Config.hpp"

Config::Config(std::string fileName)
{

}

enum	blockType
{
	event =	0,
	http = 1,
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
			HttpBlock::fileCheck(infile);
		}
		else if (s)
		while (1) //server
		{
			
		}
		// server, location block 생성자 호출
		// server 
		
	}
	infile.close();
}