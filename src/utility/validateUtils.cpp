#include "webserv.hpp"
#include "validate.hpp"

std::map<std::string, unsigned short> fileDataToMap(std::ifstream &file)
{
	std::map<std::string, unsigned short>	newMap;
	std::string								line;
	std::vector<std::string>				splitted;

	while (std::getline(file, line))
	{
		splitted = split(line, WHITESPACE);
		if (splitted.size() == 0)
			continue ;
		if (splitted.size() != 2)
			printErrorWithExit(CHECK_INDICATION_FILE);
		newMap.insert(std::make_pair(splitted[0], std::atoi(splitted[1].c_str())));
	}
	return (newMap);
}

bool	isNumber(const std::string& str)
{
	for (std::string::const_iterator it = str.begin(); it != (str.end() - 1); ++it)
	{
		if (std::isdigit(*it) == 0)
			return false;
	}
	return true;
}

bool	isNumeric(std::vector<std::string> data)
{
	if (data.size() != 2 || isNumber(data[1]) == false)
		return false;
	return true;
}

bool	isPathList(std::vector<std::string> data, multiplicityOption option)
{
	if (option == single && data.size() != 2)
		return false;
	return true;
}

bool	isStatus(std::vector<std::string> data)
{
	if (data.size() != 2)
		return false;
	else if (!(data[1].compare("off") == 0  || data[1].compare("on") == 0)) {
		return false;
	}
	return true;
}

bool	isErrorPageForm(std::vector<std::string> data)
{
	for (std::vector<std::string>::iterator it = data.begin() + 1; it != (data.end() - 1); ++it)
	{
		if (isNumber(*it) == false)
			return false;
	}
	return true;
}

