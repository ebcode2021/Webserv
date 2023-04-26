#include "LocationBlock.hpp"
#include "webserv.hpp"

LocationBlock::LocationBlock(const ServerBlock& serverBlock, const std::vector<std::string> &locationBlock) : ServerBlock(serverBlock) {
	std::vector<std::string> splittedLine;

	///
	// for (size_t i = 0; i < locationBlock.size(); i++)
	// {
	// 	std::cout << i << " = " << locationBlock[i] << std::endl;
	// }
	// std::cout << "출력 끝" << std::endl;
	///

	for (size_t i = 0; i < locationBlock.size(); i++)
	{
		///
		std::cout << locationBlock[i] << std::endl;
		///
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
	this->_limitExcept = LimitExcept(split(line, "\n"));
}

void LocationBlock::blockCheck(std::ifstream &infile, Validate& dataset)
{
	std::string					line;
	std::vector<std::string>	splitted;

	Validate::braceCheck(infile, OPEN_BRACE);
	dataset.resetLocationIndicationList();
	while (std::getline(infile, line))
	{
		splitted = split(line, WHITESPACE);
		if (splitted.size() == 0)
			continue ;
		if (splitted.size() == 1 && splitted[0].compare(CLOSE_BRACE) == 0)
			break ;
		Validate::propertyCntCheck(infile, splitted);
		locationIndications indication = dataset.findLocationIndication(splitted);
		switch (indication)
		{
			case l_limit_except :
				//LimitExcept::limitExceptCheck(infile, dataset);
				break ;
			case l_client_max_body_size :
				Validate::isNumeric(infile, splitted);
				break ;
			case l_root :
			case l_client_body_temp_path :
				Validate::isPathList(infile, splitted, single);
				break ;
			case l_index :
				Validate::isPathList(infile, splitted, multiple);
				break ;
			case l_autoindex :
				Validate::isStatus(infile, splitted);
				break ;
			case l_error_page :
				Validate::isErrorPageForm(infile, splitted);
				break ;
			case l_none :
				break ;
			default :
				fileErrorWithExit(NO_INDICATION, infile);
		}
		dataset.decrementLocationCounter(infile, splitted[0]);
	}
}

//test utils
using namespace std;

void	LocationBlock::printLocationBlock() {
	std::cout << "path : " << this->_path << std::endl;
	this->_limitExcept.printInfo();
}