#include "LimitExcept.hpp"
#include "validate.hpp"

/* constructor */
LimitExcept::LimitExcept() {}

LimitExcept::LimitExcept(const std::vector<std::string> &exceptBlock) {
	std::vector<std::string> splittedLine;
	for (size_t i = 0; i < exceptBlock.size(); i++)
	{
		splittedLine = split(exceptBlock[i], static_cast<std::string>(WHITESPACE) + ";");
		if (splittedLine[0].compare("limit_except"))
			this->setMethodList(splittedLine);
		else if (splittedLine[0].compare("allow"))
			this->setAllow(splittedLine);
		else if (splittedLine[0].compare("deny"))
			this->setDeny(splittedLine);
	}
} 

/* getter, setter */
std::vector<std::string>	LimitExcept::getMethodList() const {
	return (this->_methodList);
}

std::string					LimitExcept::getAllow() const {
	return (this->_allow);
}

std::string					LimitExcept::getDeny() const {
	return (this->_deny);
}
std::map<std::string, std::string>	LimitExcept::getAccessDirectiveList() const {
	return (this->_accessDirectiveList);
}

void	LimitExcept::setMethodList(const std::vector<std::string> &value) {
	for (size_t i = 1; i < value.size(); i++)
	{
		if (value[i].compare("{") == 0)
			this->_methodList.push_back(value[i]);
	}
}

void	LimitExcept::setAllow(const std::vector<std::string> &value) {
	this->_allow = value[1];
}

void	LimitExcept::setDeny(const std::vector<std::string> &value) {
	this->_allow = value[1];
}

/* block check */
void	LimitExcept::blockCheck(std::ifstream& infile, Validate& dataset)
{
	std::string					line;
	std::vector<std::string>	splitted;

	// Check open Brace
	std::getline(infile, line);
	splitted = split(line, WHITESPACE);
	if (Validate::braceCheck(splitted, OPEN_BRACE) == false)
		fileErrorWithExit(BRACE_ERROR, infile);
	dataset.resetLimitExceptIndicationList();
	
	// Read Config file
	while (std::getline(infile, line))
	{
		// Check splitted data
		splitted = split(line, WHITESPACE);
		if (splitted.size() == 0)
			continue ;
		else if (Validate::braceCheck(splitted, CLOSE_BRACE) == true)
			break ;
		
		// Validate Keyword
		limitExceptIndications indications = dataset.findLimitExceptIndication(splitted);
		switch (indications)
		{
			case e_allow :
			case e_deny :
			case e_none :
				break ;
			default :
				fileErrorWithExit(NO_INDICATION, infile);
		}
		if (endsWithSemicolon(splitted.back()) == false)
			fileErrorWithExit(I_SEMICOLON, infile);
		
		if (dataset.decrementLimitExceptCounter(splitted[0]) == false)
			fileErrorWithExit(I_NO_SPACE, infile);
	}
}

// 나중에 util로 뺄거
bool	LimitExcept::isMethodInList(const std::string& method) const
{
	size_t	size = this->_methodList.size();

	for (size_t i = 0; i < size; i++)
	{
		if (this->_methodList[i] == method)
			return (true);
	}
	return (false);
}

bool	LimitExcept::isAllValue(const std::string& value) const
{
	return (value == "all");
}

bool	LimitExcept::isValidClientAddr(const std::string& value, const std::string& addr) const
{
	return (value == addr);
}

bool	LimitExcept::isValidMethod(const std::string& method, const std::string& clientAddr) const
{
	bool	hasMethod = this->isMethodInList(method);
	
	std::map<std::string, std::string>::const_iterator it;
	for (it = this->_accessDirectiveList.begin(); it != this->_accessDirectiveList.end(); it++)
	{
		std::string	field = (*it).first;
		std::string	value = (*it).second;

		if (field == "allow" && isAllValue(value) == true)
			break ;

		if (hasMethod == true)
		{
			if (field == "allow" && isValidClientAddr(value, clientAddr) == true)
				break ;
		}
		else
		{
			if (field == "deny" && (isAllValue(value) == true || isValidClientAddr(value, clientAddr) == true))
				return (false);
		}
	}
	return (true);
}

/* print */
void	LimitExcept::printInfo()
{
	for (size_t i = 0; i < this->_methodList.size(); i++)
	{
		std::cout << "method :" << _methodList[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "allow : " << this->_allow << std::endl;
	std::cout << "deny : " << this->_deny << std::endl;
}
