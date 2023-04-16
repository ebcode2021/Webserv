#include "validate.hpp"

std::map<std::string, unsigned short> fileDataToMap(std::ifstream &file)
{
	std::map<std::string, unsigned short>	newMap;
	std::string								line;
	std::vector<std::string>				splitted;

	while (std::getline(file, line))
	{
		splitted = split(line, WHITESPACE);
		if (splitted.size() != 2)
			printErrorWithExit(CHECK_INDICATION_FILE);
		newMap.insert(std::make_pair(splitted[0], std::stoi(splitted[1]))); 
	}
	//stoi는 직접 구현해야함. 11문법.

	return (newMap);
}

serverIndications	getServerType(const std::string& indication)
{
	if (ServerType.count(indication) == 0)
		return ServerType.at(0);
	return ServerType.at(indication);
}

locationIndications	getLocationType(const std::string& indication)
{
	if (LocationType.count(indication) == 0)
		return LocationType.at(0);
	return LocationType.at(indication);
}

std::unordered_map<std::string, serverIndications>	mappingServerIndications(std::map<std::string, unsigned short>& myMap)
{
	std::unordered_map<std::string, serverIndications> mappingMap;

	for (std::map<std::string, unsigned short>::iterator it = myMap.begin(); it != myMap.end(); ++it)
		mappingMap.insert(std::make_pair(it->first, getServerType(it->first)));
	return mappingMap;
}

std::unordered_map<std::string, locationIndications>	mappingLocationIndications(std::map<std::string, unsigned short>& myMap)
{
	std::unordered_map<std::string, locationIndications> mappingMap;

	for (std::map<std::string, unsigned short>::iterator it = myMap.begin(); it != myMap.end(); ++it)
		mappingMap.insert(std::make_pair(it->first, getLocationType(it->first)));
	return mappingMap;
}

/* constructor */
Validate::Validate()
{
	std::ifstream	serverFile;
	std::ifstream	locationFile;

	serverFile.open(INDICATION_PATH + SERVER);
	if (serverFile.fail())
		printErrorWithExit(CHECK_INDICATION_FILE);
	this->_originServerMap = fileDataToMap(serverFile);
	this->_serverMap = this->_originServerMap;
	this->_serverIndications = mappingServerIndications(this->_originServerMap);
	serverFile.close();

	locationFile.open(INDICATION_PATH + LOCATION);
	if (locationFile.fail())
		printErrorWithExit(CHECK_INDICATION_FILE);
	this->_originLocationMap = fileDataToMap(locationFile);
	this->_locationMap = this->_originLocationMap;
	this->_locationIndications = mappingLocationIndications(this->_originLocationMap);
	locationFile.close();
}

/* checker */
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

void	Validate::braceCheck(std::ifstream &infile, std::string braceType)
{
	std::string					line;
	std::vector<std::string>	splitted;

	std::getline(infile, line);
	splitted = split(line, WHITESPACE);
	if (splitted.size() != 1 || splitted[0].compare(braceType))
		fileErrorWithExit(BRACE_ERROR, infile);
}

void	Validate::extensionCheck(char *name)
{
	std::string	fileName = std::string(name);
	int			index = fileName.find('.');

	if (index < 1 || EXTENSION.compare(std::string(fileName).substr(index)))
		printErrorWithExit(INVALID_ARGC);
}

/* find */
serverIndications	Validate::findServerIndication(std::vector<std::string> splitted)
{
	std::unordered_map<std::string, serverIndications>::iterator it = _serverIndications.find(splitted[0]);

	if (it != _serverIndications.end())
		return it->second;
	return serverIndications::not_found;
}

/* reset */
void	Validate::resetServerIndicationList()
{
	this->_serverMap = this->_originServerMap;
}

void	Validate::resetLocationIndicationList()
{
	this->_locationMap = this->_originLocationMap;
}