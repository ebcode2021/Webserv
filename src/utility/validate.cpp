#include "validate.hpp"
#include "webserv.hpp"
#include <unistd.h>

std::map<std::string, serverIndications> ServerType;
std::map<std::string, locationIndications> LocationType;

void	init_type()
{
	LocationType.insert(std::make_pair("limit_except", l_limit_except));
	LocationType.insert(std::make_pair("autoindex", l_autoindex));
	LocationType.insert(std::make_pair("client_max_body_size", l_client_max_body_size));
	LocationType.insert(std::make_pair("client_body_temp_path", l_client_body_temp_path));
	LocationType.insert(std::make_pair("error_page", l_error_page));
	LocationType.insert(std::make_pair("index", l_index));
	LocationType.insert(std::make_pair("root", l_root));

	ServerType.insert(std::make_pair("location", s_location));
	ServerType.insert(std::make_pair("listen", s_listen));
	ServerType.insert(std::make_pair("server_name", s_server_name));
	ServerType.insert(std::make_pair("error_page", s_error_page));
	ServerType.insert(std::make_pair("client_max_body_size", s_client_max_body_size));
	ServerType.insert(std::make_pair("client_body_temp_path", s_client_body_temp_path));
	ServerType.insert(std::make_pair("autoindex", s_autoindex));
	ServerType.insert(std::make_pair("index", s_index));
	ServerType.insert(std::make_pair("root", s_root));
}

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

serverIndications	getServerType(const std::string& indication)
{
	if (ServerType.count(indication) == 0)
		return ServerType.at("s_none");
	return ServerType.at(indication);
}

locationIndications	getLocationType(const std::string& indication)
{
	if (LocationType.count(indication) == 0)
		return LocationType.at("l_none");
	return LocationType.at(indication);
}

std::map<std::string, serverIndications>	mappingServerIndications(std::map<std::string, unsigned short>& myMap)
{
	std::map<std::string, serverIndications> mappingMap;

	for (std::map<std::string, unsigned short>::iterator it = myMap.begin(); it != myMap.end(); ++it)
		mappingMap.insert(std::make_pair(it->first, getServerType(it->first)));
	return mappingMap;
}

std::map<std::string, locationIndications>	mappingLocationIndications(std::map<std::string, unsigned short>& myMap)
{
	std::map<std::string, locationIndications> mappingMap;

	for (std::map<std::string, unsigned short>::iterator it = myMap.begin(); it != myMap.end(); ++it)
		mappingMap.insert(std::make_pair(it->first, getLocationType(it->first)));
	return mappingMap;
}

/* constructor */
Validate::Validate()
{
	std::ifstream	serverFile;
	std::ifstream	locationFile;
	init_type();

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
fileMode	Validate::argumentCheck(int argc, char *argv[])
{
	if (argc == 1)
		printErrorWithExit(INVALID_ARGC);
	else if (argc == 2 || (argc == 3 && strcmp(argv[2], "-t") == 0))
	{
		Validate::extensionCheck(argv[1]);
		if (argc == 2)
			return success;
		else
			return test;
	}
	else
		printErrorWithExit(INVALID_ARGC);
	return fail;
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

void		Validate::propertyCntCheck(std::ifstream& infile, std::vector<std::string> data)
{
	static std::vector<std::string> blocks;
	blocks.push_back("location");
    blocks.push_back("server");
    blocks.push_back("limit_except");

	bool	blockExist = (std::find(blocks.begin(), blocks.end(), data[0]) != blocks.end());
	
	if (blockExist && data.size() != 2)
		fileErrorWithExit(BLOCK_NAME, infile);
	else if (data.size() == 1)
		fileErrorWithExit(I_PROPERTIES, infile);
}

/* decrement properties */
void	Validate::decrementServerCounter(std::ifstream& infile, std::string key)
{
	unsigned short& remainingNumer = this->_serverMap[key];

	if (remainingNumer == 0)
		fileErrorWithExit(I_NO_SPACE, infile);
	remainingNumer--;
}

void	Validate::decrementLocationCounter(std::ifstream& infile, std::string key)
{
	unsigned short& remainingNumer = this->_locationMap[key];

	if (remainingNumer == 0)
		fileErrorWithExit(I_NO_SPACE, infile);
	remainingNumer--;
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

void	Validate::endsWithSemicolon(std::ifstream& infile, std::string str)
{
	char	lastChar = str.back();

	if (lastChar != ';')
		fileErrorWithExit(I_SEMICOLON, infile);
}

void	Validate::isNumeric(std::ifstream& infile, std::vector<std::string> data)
{
	if (data.size() != 2)
		fileErrorWithExit(I_NOT_MULTIPLE, infile);
	if (isNumber(data[1]) == false)
		fileErrorWithExit(I_NUMERIC_ERROR, infile);
	endsWithSemicolon(infile, data.back());
}

void	Validate::isPathList(std::ifstream& infile, std::vector<std::string> data, multiplicityOption option)
{
	if (option == single && data.size() != 2)
		fileErrorWithExit(I_NOT_MULTIPLE, infile);
	endsWithSemicolon(infile, data.back());
}

void	Validate::isStatus(std::ifstream &infile, std::vector<std::string> data)
{
	if (data.size() != 2)
		fileErrorWithExit(I_NOT_MULTIPLE, infile);
	if (!(data[1].compare("off") == 0  || data[1].compare("on") == 0))
		fileErrorWithExit(I_PROPERTIES, infile);
	endsWithSemicolon(infile, data.back());
}

void	Validate::isStringList(std::ifstream &infile, std::vector<std::string> data)
{
	endsWithSemicolon(infile, data.back());
}

void	Validate::isErrorPageForm(std::ifstream &infile, std::vector<std::string> data)
{
	for (std::vector<std::string>::iterator it = data.begin() + 1; it != (data.end() - 1); ++it)
	{
		if (isNumber(*it) == false)
			fileErrorWithExit(I_PROPERTIES, infile);
	}
	endsWithSemicolon(infile, data.back());
}

/* find */
serverIndications	Validate::findServerIndication(std::vector<std::string> splitted)
{
	std::map<std::string, serverIndications>::iterator it = _serverIndications.find(splitted[0]);

	if (it != _serverIndications.end())
		return it->second;
	return s_not_found;
}

locationIndications	Validate::findLocationIndication(std::vector<std::string> splitted)
{
	std::map<std::string, locationIndications>::iterator it = _locationIndications.find(splitted[0]);

	if (it != _locationIndications.end())
		return it->second;
	return l_not_found;
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