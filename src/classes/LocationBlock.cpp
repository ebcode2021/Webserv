#include "LocationBlock.hpp"
#include "webserv.hpp"

LocationBlock::LocationBlock(const ServerBlock& serverBlock, const std::vector<std::string> &locationBlock) : ServerBlock(serverBlock) {
	std::vector<std::string> splittedLine;

	for (size_t i = 0; i < locationBlock.size(); i++)
	{
		splittedLine = split(locationBlock[i], static_cast<std::string>(WHITESPACE) + ";");
		if (splittedLine[0].compare("location") == 0) {
			setLocationPath(splittedLine);
		}
		else if (splittedLine[0].compare("limit_except") == 0) {
			setLimitExcept(locationBlock[i]);
		}
		else {
			this->configsetting(splittedLine);
		}
	}
		
}

void	LocationBlock::setLocationPath(const std::vector<std::string>& value) {
	if (value.size() < 2)
		this->_path = "/";
	else
		this->_path = value[1];
}

void	LocationBlock::setLimitExcept(const std::string &line) {
	this->_limittExcept = LimitExcept(split(line, "\n"));
}

void LocationBlock::blockCheck(std::ifstream& infile)
void LocationBlock::blockCheck(std::ifstream &infile)
{
	std::string					line;
	std::vector<std::string>	splitted;

	while (std::getline(infile, line))
	{
			// 지시어, 밸류 확인
	}
}

//test utils
using namespace std;

void	LocationBlock::printLocationBlock() {
	std::cout << "path : " << this->_path << std::endl;
	this->_limittExcept.printInfo();
}