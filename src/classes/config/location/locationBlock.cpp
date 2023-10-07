#include "LocationBlock.hpp"
#include "webserv.hpp"

/* constructor */
LocationBlock::LocationBlock(){}

LocationBlock::LocationBlock(const ServerBlock &origin) : ServerBlock(origin) {
	this->_path = "";
}

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
		else if (splittedLine[0].compare("cgi_pass") == 0) {
			setCgiPass(splittedLine[i]);
		}
		else if (splittedLine[0].compare("return") == 0) {
			this->_return = splittedLine[1];
		}
		else {
			this->configsetting(splittedLine);
		}
	}
}

/* getter */
LimitExcept	LocationBlock::getLimitExcept() const {
	return (this->_limitExcept);
}

std::string	LocationBlock::getPath() const {
	return (this->_path);
}

std::string LocationBlock::getReturn() const {
	return (this->_return);
}


/* setter */
void	LocationBlock::setLimitExcept(const std::string &line) {
	this->_limitExcept = LimitExcept(split(line, "\n"));
}

void	LocationBlock::setPath(const std::string& path) { 
	this->_path = path; 
}

void	LocationBlock::setCgiPass(const std::string& cgiPass) {
	this->_cgi_pass = cgiPass;
}

void	LocationBlock::setReturn(const std::string& value) {
	this->_return = value;
} 

std::string LocationBlock::getCgiPass() const {
	return (this->_cgi_pass);
}


/* checker */
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
		if (endsWithSemicolon(splitted.back()) == false)
			fileErrorWithExit(I_SEMICOLON, infile);
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
				if (isStatus(splitted) == false) {
					std::cout << "여기?" << std::endl;
					fileErrorWithExit(I_PROPERTIES, infile);
				}
				break ;
			case l_error_page :
				if (isErrorPageForm(splitted) == false)
					fileErrorWithExit(I_PROPERTIES, infile);
				break ;
			case l_return :
				if (splitted.size() != 2)
					fileErrorWithExit(I_PROPERTIES, infile);
			case l_cgi_pass :

			case l_none :
				break ;
			default :
				fileErrorWithExit(NO_INDICATION, infile);
		}
		
		if (dataset.decrementLocationCounter(splitted[0]) == false)
			fileErrorWithExit(I_NO_SPACE, infile);
	}
}

/* method */
std::string	LocationBlock::getFullPath() const {
	if (this->_path != "/")
		return (this->_root + this->_path);
	return (this->_root);
}

void	LocationBlock::setLocationPath(const std::vector<std::string>& value) {
	if (value.size() < 2)
		this->_path = "/";
	else
		this->_path = value[1];
}

/* print */
void	LocationBlock::printInfo() const {
	std::cout << "path : " << this->_path << std::endl;
	this->_limitExcept.printInfo();
}
