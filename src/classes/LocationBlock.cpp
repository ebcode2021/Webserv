#include "LocationBlock.hpp"
#include "webserv.hpp"

LocationBlock::LocationBlock(const ServerBlock& serverBlock, const std::vector<std::string> &locationBlock) : ServerBlock(serverBlock) {
	std::vector<std::string> splittedLine;

	
	for (size_t i = 0; i < locationBlock.size(); i++)
	{
		std::cout << i << " = " << locationBlock[i] << std::endl;
	}
	std::cout << "출력 끝" << std::endl;


	for (size_t i = 0; i < locationBlock.size(); i++)
	{
		// ///
		// std::cout << locationBlock[i] << std::endl;
		// ///
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

	// check open Brace
	std::getline(infile, line);
	splitted = split(line, WHITESPACE);
	if (Validate::braceCheck(splitted, OPEN_BRACE) == false)
		fileErrorWithExit(BRACE_ERROR, infile);
	dataset.resetLocationIndicationList();

	// Read Config file
	while (std::getline(infile, line))
	{
		// Check splitted data
		splitted = split(line, WHITESPACE);
		if (splitted.size() == 0)
			continue ;
		else if (Validate::braceCheck(splitted, CLOSE_BRACE) == true)
			break ;
		//Validate::propertyCntCheck(infile, splitted);
		// Validate Keyword
		locationIndications indication = dataset.findLocationIndication(splitted);
		switch (indication)
		{
			case l_limit_except :
				LimitExcept::blockCheck(infile, dataset);
				break ;
			case l_client_max_body_size :
				if (isNumeric(splitted) == false)
					fileErrorWithExit(I_NUMERIC_ERROR, infile);
				break ;
			case l_root :
			case l_client_body_temp_path :
				if (isPathList(splitted, single) == false)
					fileErrorWithExit(I_NOT_MULTIPLE, infile);
				break ;
			case l_index :
				if (isPathList(splitted, multiple) == false)
					fileErrorWithExit(I_PROPERTIES, infile);
				break ;
			case l_autoindex :
				if (isStatus(splitted) == false)
					fileErrorWithExit(I_PROPERTIES, infile);
				break ;
			case l_error_page :
				if (isErrorPageForm(splitted) == false)
					fileErrorWithExit(I_PROPERTIES, infile);
				break ;
			case l_none :
				break ;
			default :
				fileErrorWithExit(NO_INDICATION, infile);
		}
		if (indication != l_limit_except && endsWithSemicolon(splitted.back()) == false)
			fileErrorWithExit(I_SEMICOLON, infile);
		if (dataset.decrementLocationCounter(splitted[0]) == false)
			fileErrorWithExit(I_NO_SPACE, infile);
	}
}

//test utils
using namespace std;

void	LocationBlock::printLocationBlock() {
	std::cout << "path : " << this->_path << std::endl;
	this->_limitExcept.printInfo();
}