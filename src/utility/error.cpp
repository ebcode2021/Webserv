#include "webserv.hpp"

void	printErrorWithExit(std::string msg)
{
	std::cerr << msg << std::endl;
	exit(EXIT_FAILURE);
}

int	getErrorLine(std::ifstream& file)
{
	std::streampos	position = file.tellg();
	int lineNum = 1;
	std::string line;

	file.seekg(0, std::ios::beg);
	while (std::getline(file, line))
	{
		if (position <= file.tellg())
			break;
		++lineNum;
	}	

	file.seekg(position);
	return lineNum;
}

void	fileErrorWithExit(std::string msg, std::ifstream& file)
{
	std::cerr << msg << getErrorLine(file) << std::endl;
	file.close();
	exit(EXIT_FAILURE);
}
