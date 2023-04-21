#include "LocationBlock.hpp"
#include "webserv.hpp"

LocationBlock::LocationBlock(const ServerBlock& serverBlock, const std::string &locationBlock) : ServerBlock(serverBlock) {
	std::vector<std::string> line = split(locationBlock, "\n");
	std::vector<std::string> splitedLine;

	for (size_t i = 0; i < line.size(); i++)
	{
		splitedLine = split(line[i], static_cast<std::string>(WHITESPACE) + ";");
		if (splitedLine[0].compare("location") == 0) {
			setLocationPath(splitedLine);
		}
		else if (splitedLine[0].compare("limit_except")) {
			setLimitExcept(line, &i);
		}
		else {
			this->configsetting(splitedLine);
		}

	}
		
}

void	LocationBlock::setLocationPath(const std::vector<std::string>& value) {
	if (value.size() < 2)
		this->_path = "/";
	else
		this->_path = value[1];
}

void	LocationBlock::setLimitExcept(const std::vector<std::string> &line, size_t *idx) {
	
}

void LocationBlock::blockCheck(std::ifstream& infile)
{
	std::string					line;
	std::vector<std::string>	splitted;

	while (std::getline(infile, line))
	{
			// 지시어, 밸류 확인
	}
}