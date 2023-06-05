#include "validate.hpp"
#include "webserv.hpp"

/* constructor */
Validate::Validate()
{
	std::ifstream	serverFile;
	std::ifstream	locationFile;
	std::ifstream	limitExceptFile;

	initBlockType();

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

	limitExceptFile.open(INDICATION_PATH + LIMIT_EXCEPT);
	if (limitExceptFile.fail())
		printErrorWithExit(CHECK_INDICATION_FILE);
	this->_originLimitExceptMap = fileDataToMap(limitExceptFile);
	this->_limitExceptMap = this->_originLimitExceptMap;
	this->_limitExceptIndications = mappingLimitExceptIndications(this->_limitExceptMap);
	limitExceptFile.close();
}

/* initialize */
void	Validate::initBlockType()
{
	setServerType();
	setLocationType();
	setLimitExceptType();
}
/* getter */

serverIndications	Validate::getServerType(const std::string& indication)
{
	if (this->_ServerType.count(indication) == 0)
		return this->_ServerType.at("s_none");
	return this->_ServerType.at(indication);
}

locationIndications	Validate::getLocationType(const std::string& indication)
{
	if (this->_LocationType.count(indication) == 0)
		return this->_LocationType.at("l_none");
	return this->_LocationType.at(indication);
}

limitExceptIndications	Validate::getLimitExceptType(const std::string& indication)
{
	if (this->_LimitExceptType.find(indication) == this->_LimitExceptType.end())
		return this->_LimitExceptType.at("e_none");
	return this->_LimitExceptType.at(indication);
}

/* setter */
void	Validate::setServerType()
{
	this->_ServerType.insert(std::make_pair("location", s_location));
	this->_ServerType.insert(std::make_pair("listen", s_listen));
	this->_ServerType.insert(std::make_pair("server_name", s_server_name));
	this->_ServerType.insert(std::make_pair("error_page", s_error_page));
	this->_ServerType.insert(std::make_pair("client_max_body_size", s_client_max_body_size));
	this->_ServerType.insert(std::make_pair("client_body_temp_path", s_client_body_temp_path));
	this->_ServerType.insert(std::make_pair("autoindex", s_autoindex));
	this->_ServerType.insert(std::make_pair("index", s_index));
	this->_ServerType.insert(std::make_pair("root", s_root));
}

void	Validate::setLocationType()
{
	this->_LocationType.insert(std::make_pair("limit_except", l_limit_except));
	this->_LocationType.insert(std::make_pair("autoindex", l_autoindex));
	this->_LocationType.insert(std::make_pair("client_max_body_size", l_client_max_body_size));
	this->_LocationType.insert(std::make_pair("client_body_temp_path", l_client_body_temp_path));
	this->_LocationType.insert(std::make_pair("error_page", l_error_page));
	this->_LocationType.insert(std::make_pair("index", l_index));
	this->_LocationType.insert(std::make_pair("root", l_root));
}

void	Validate::setLimitExceptType()
{
	this->_LimitExceptType.insert(std::make_pair("allow", e_allow));
	this->_LimitExceptType.insert(std::make_pair("deny", e_deny));
}


/* checker */
void	Validate::argumentCheck(int argc, char *argv[])
{
	if (argc == 2 || (argc == 3 && strcmp(argv[2], "-t") == 0))
		Validate::extensionCheck(argv[1]);
	else
		printErrorWithExit(INVALID_ARGC);

}

bool	Validate::braceCheck(std::vector<std::string> data, std::string braceType)
{
	if (data.size() == 1 && data[0].compare(braceType) == 0)
		return true;
	return false;
}

void	Validate::extensionCheck(char *name)
{
	std::string	fileName = std::string(name);
	int			index = fileName.find('.');

	if (index < 1 || EXTENSION.compare(std::string(fileName).substr(index)))
		printErrorWithExit(INVALID_ARGC);
}


/* decrement properties */
bool	Validate::decrementServerCounter(std::string key)
{
	unsigned short& remainingNumer = this->_serverMap[key];

	if (remainingNumer == 0)
		return false;
	remainingNumer--;
	return true;
}

bool	Validate::decrementLocationCounter(std::string key)
{
	unsigned short& remainingNumer = this->_locationMap[key];

	if (remainingNumer == 0)
		return false;
	remainingNumer--;
	return true;
}

bool	Validate::decrementLimitExceptCounter(std::string key)
{
	unsigned short& remainingNumer = this->_limitExceptMap[key];

	if (remainingNumer == 0)
		return false;
	remainingNumer--;
	return true;
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

limitExceptIndications	Validate::findLimitExceptIndication(std::vector<std::string> splitted)
{
	std::map<std::string, limitExceptIndications>::iterator it = _limitExceptIndications.find(splitted[0]);

	if (it != _limitExceptIndications.end())
		return it->second;
	return e_not_found;
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

void	Validate::resetLimitExceptIndicationList()
{
	this->_limitExceptMap = this->_originLimitExceptMap;
}


/* mapping */
std::map<std::string, serverIndications>	Validate::mappingServerIndications(std::map<std::string, unsigned short>& myMap)
{
	std::map<std::string, serverIndications> mappingMap;

	for (std::map<std::string, unsigned short>::iterator it = myMap.begin(); it != myMap.end(); ++it)
		mappingMap.insert(std::make_pair(it->first, getServerType(it->first)));
	return mappingMap;
}

std::map<std::string, locationIndications>	Validate::mappingLocationIndications(std::map<std::string, unsigned short>& myMap)
{
	std::map<std::string, locationIndications> mappingMap;

	for (std::map<std::string, unsigned short>::iterator it = myMap.begin(); it != myMap.end(); ++it)
		mappingMap.insert(std::make_pair(it->first, getLocationType(it->first)));
	return mappingMap;
}

std::map<std::string, limitExceptIndications>	Validate::mappingLimitExceptIndications(std::map<std::string, unsigned short>& myMap)
{
	std::map<std::string, limitExceptIndications> mappingMap;

	for (std::map<std::string, unsigned short>::iterator it = myMap.begin(); it != myMap.end(); ++it)
		mappingMap.insert(std::make_pair(it->first, getLimitExceptType(it->first)));
	return mappingMap;
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
