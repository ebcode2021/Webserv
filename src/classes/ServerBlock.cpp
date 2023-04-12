#include "ServerBlock.hpp"

void ServerBlock::blockCheck(std::ifstream infile)
{
	std::string					line;
	std::vector<std::string>	splitted;

	while (std::getline(infile, line))
	{
		splitted = split(line, ' ');

		if (splitted[0].compare("Location") == 0) {
			LocationBlock::blockCheck(infile);
		}
		else {
			// 지시어, 밸류 확인, 중복 확인
		}
	}

}