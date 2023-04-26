#include "LimitExcept.hpp"

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

// test
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