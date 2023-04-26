#include "validate.hpp"

std::map<std::string, unsigned short> fileDataToMap(std::ifstream &file)
{
	std::map<std::string, unsigned short>	newMap;
	std::string								line;
	std::vector<std::string>				splitted;

	(void)file;
	//return (newMap);
	// while (std::getline(file, line))
	// {
	// 	splitted = split(line, ' ');
	// 	if (splitted.size() != 2)
	// 		printErrorWithExit(CHECK_INDICATION_FILE);
	// 	newMap.insert(std::make_pair(splitted[0], std::stoi(splitted[1]))); 
	// }
	// stoi는 직접 구현해야함. 11문법.

	return (newMap);
}

/* constructor */
Validate::Validate()
{
	std::ifstream	serverFile;
	std::ifstream	locationFile;

	serverFile.open(INDICATION_PATH + SERVER);
	this->_originServerIndications = fileDataToMap(serverFile);
	locationFile.open(INDICATION_PATH + LOCATION);
	this->_originLocationIndications = fileDataToMap(locationFile);
}

void	Validate::extensionCheck(char *name)
{
	std::string	fileName = std::string(name);
	int			index = fileName.find('.');

	if (index < 1 || EXTENSION.compare(std::string(fileName).substr(index)))
		printErrorWithExit(INVALID_ARGC);
}

bool	Validate::argumentCheck(int argc, char *argv[])
{
	if (argc == 1)
		printErrorWithExit(INVALID_ARGC);
	else if (argc == 2 || (argc == 3 && strcmp(argv[2], "-t") == 0))
	{
		Validate::extensionCheck(argv[1]);
		if (argc == 2)
			return true;
		else
			notice::printMessage(TEST_SUCCESS);
	}
	else
		printErrorWithExit(INVALID_ARGC);
	return false;
}
