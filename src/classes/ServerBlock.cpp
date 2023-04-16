#include "LocationBlock.hpp"
#include "ServerBlock.hpp"
#include "webserv.hpp"
#include "map"

ServerBlock::ServerBlock() {
	this->_clientMaxBodySize = 1;
	this->_listenList.push_back(8080);
	this->_root = "html";
}

std::map<std::string, int> create_directivemap() {
	std::map<std::string, int> ret;
	std::ifstream server_keywords("keywords/.server_keyword");
	std::string line;
	std::vector<std::string> splitedLine;
	size_t	i = 0;
	while (std::getline(server_keywords, line))
	{
		splitedLine = split(line, WHITESPACE);
		ret.insert(make_pair(splitedLine[0], i++));
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
		&ServerBlock::setClientBodyTempPath
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
	for(size_t i = 1; i < value.size(); i++) {
		this->_index.push_back(value[i]);
	}
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

	Validate::braceCheck(infile, OPEN_BRACE);
	dataset.resetServerIndicationList();
	while (std::getline(infile, line))
	{
		splitted = split(line, WHITESPACE);
		if (splitted.size() == 0)
			continue ;
		serverIndications indication = dataset.findServerIndication(splitted);
		switch(indication)
		{
			case serverIndications::location :
				LocationBlock::blockCheck(infile);
				break;
			case serverIndications::server_name :
			case serverIndications::client_body_temp_path :
			case serverIndications::client_max_body_size :
				std::cout << "이런식으로 한 번에?" << std::endl;
				break ;
			default :
				fileErrorWithExit(NO_INDICATION, infile);
		}
	}
	Validate::braceCheck(infile, CLOSE_BRACE);
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