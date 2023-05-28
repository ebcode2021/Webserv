#include "LocationBlock.hpp"
#include "ServerBlock.hpp"
#include "webserv.hpp"
#include "map"


ServerBlock::ServerBlock() {
	this->_clientMaxBodySize = 1000000; //1MB
	this->_listenList.push_back(DEFAULT_PORT);
	this->_root = DEFAULT_ROOT;
	this->_index.push_back(DEFAULT_INDEX);
}

std::map<std::string, int> create_directivemap() {
	std::map<std::string, int> ret;
	std::ifstream server_keywords(KEYWORD_PATH);
	std::string line;
	std::vector<std::string> splittedLine;
	size_t	i = 0;
	while (std::getline(server_keywords, line))
	{
		splittedLine = split(line, WHITESPACE);
		ret.insert(make_pair(splittedLine[0], i++));
	}
	return (ret);
}

void	ServerBlock::configsetting(std::vector<std::string>& config) {
	static std::map<std::string, int> directivemap = create_directivemap();
	static void (ServerBlock::*setFunc[])(std::vector<std::string>&) = {
		&ServerBlock::setListenPort,
		&ServerBlock::setServerName,
		&ServerBlock::setErrorPage,
		&ServerBlock::setClientMaxBodySize,
		&ServerBlock::setAutoIndex,
		&ServerBlock::setIndex,
		&ServerBlock::setClientBodyTempPath,
		&ServerBlock::setRoot
	};
	(this->*setFunc[directivemap[config[0]]])(config);
}

/// setconfig

void	ServerBlock::setListenPort(std::vector<std::string>& value) {
	for (size_t i = 1; i < value.size(); i++) {
		this->_listenList.push_back(std::atoi(value[i].c_str()));
	}
}

void	ServerBlock::setServerName(std::vector<std::string>& value) {
	for (size_t i = 1; i < value.size(); i++) {
		this->_serverNameList.push_back(value[i]);
	}
}

void	ServerBlock::setErrorPage(std::vector<std::string>& value) {
	ErrorPage errorPage(value);
	this->_errorPage.push_back(errorPage);
}

void	ServerBlock::setClientMaxBodySize(std::vector<std::string>& value) {
	this->_clientMaxBodySize = atoi(value[1].c_str());
}

void	ServerBlock::setAutoIndex(std::vector<std::string>& value) {
	if (value[1].compare("on") == 0)
		this->_autoindex = true;
	else
		this->_autoindex = false;
}

void	ServerBlock::setIndex(std::vector<std::string>& value) {
	std::vector<std::string> index;
    index.push_back("index.html");
    for(size_t i = 1; i < value.size(); i++) {
        index.push_back(value[i]);
    }
    this->_index = index;
}

void	ServerBlock::setClientBodyTempPath(std::vector<std::string>& value) {
	this->_clientBodyTempPath = value[1];
}

void	ServerBlock::setRoot(std::vector<std::string>& value) {
	this->_root = value[1];
}


//

void ServerBlock::blockCheck(std::ifstream& infile, Validate &dataset)
{
	std::string					line;
	std::vector<std::string>	splitted;

	// check open Brace
	std::getline(infile, line);
	splitted = split(line, WHITESPACE);
	if (Validate::braceCheck(splitted, OPEN_BRACE) == false)
		fileErrorWithExit(BRACE_ERROR, infile);
	dataset.resetServerIndicationList();

	// Read Config file
	while (std::getline(infile, line))
	{
		// Check splitted data
		splitted = split(line, WHITESPACE);
		if (splitted.size() == 0)
			continue ;
		else if (Validate::braceCheck(splitted, CLOSE_BRACE) == true)
			break ;
		Validate::propertyCntCheck(infile, splitted);
		// Validate Keyword
		serverIndications indication = dataset.findServerIndication(splitted);
		switch(indication)
		{
			case s_location :
				LocationBlock::blockCheck(infile, dataset);
				break ;
			case s_listen :
			case s_client_max_body_size :
				if (isNumeric(splitted) == false)
					fileErrorWithExit(I_NUMERIC_ERROR, infile);
				break ;
			case s_root :
			case s_client_body_temp_path :
				if (isPathList(splitted, single) == false)
					fileErrorWithExit(I_NOT_MULTIPLE, infile);
				break ;
			case s_index :
				if (isPathList(splitted, multiple) == false)
					fileErrorWithExit(I_PROPERTIES, infile);
				break ;
			case s_autoindex :
				if (isStatus(splitted) == false)
					fileErrorWithExit(I_PROPERTIES, infile);
				break ;
			case s_error_page :
				if (isErrorPageForm(splitted) == false)
					fileErrorWithExit(I_PROPERTIES, infile);
				break ;
			case s_none :
			case s_server_name :
				break ;
			default :
				fileErrorWithExit(NO_INDICATION, infile);
		}
		if (indication != s_location && endsWithSemicolon(splitted.back()) == false)
			fileErrorWithExit(I_SEMICOLON, infile);

		if (dataset.decrementServerCounter(splitted[0]) == false)
			fileErrorWithExit(I_NO_SPACE, infile);
	}
}


// testPrint
using namespace std;
void	ServerBlock::printInfo() {
	cout << "root : " << this->_root << endl;

	cout << "server_name : ";
	for(size_t i = 0; i < this->_serverNameList.size(); i++) {
		cout << _serverNameList[i] << " ";
	}
	cout << "\n";

	cout << "listen : ";
	for(size_t i = 0; i < this->_listenList.size(); i++) {
		cout << _listenList[i] << " ";
	}
	cout << "\n";

	cout << "index : ";
	for(size_t i = 0; i < this->_index.size(); i++) {
		cout << _index[i] << " ";
	}
	cout << endl;

	for(size_t i = 0; i < this->_errorPage.size(); i++) {
		_errorPage[i].PrintInfo();
	}
	cout << endl;

	cout << "autoindex : ";
	if (this->_autoindex == true)
		cout << "on\n";
	else
		cout << "off\n";
	
	cout << "client_max_body_size : " << this->_clientMaxBodySize << endl;
	
	cout << "client_body_temp_path : " << this->_clientBodyTempPath << endl;
}

////

std::vector<std::string>	ServerBlock::getServerNameList() const{ return(this->_serverNameList); }

std::vector<int>	ServerBlock::getListenList() { return(this->_listenList); }

