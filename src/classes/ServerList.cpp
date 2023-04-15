# include "ServerList.hpp"
# include "webserv.hpp"

static std::string LocationBlockBackup(std::ifstream& confFile, std::string line) {
	std::string ret;
	std::vector<std::string> splitedLine;
	
	ret += line + '\n';
	while (std::getline(confFile, line))
	{
		splitedLine = split(line, WHITESPACE);
		if (splitedLine[0].compare("}") == 0)
			break ;
		else if (splitedLine[0].compare("{") != 0)
			ret += line + '\n';
	}
	return (ret);
}

void	ServerList::addServer(std::ifstream & confFile) {
	std::string line;
	std::vector<std::string> splitedLine;
	std::vector<std::string> LocationBlock;
	ServerBlock	serverBlock;
	
	///
	std::cout << "서버 블록 입장" << std::endl;
	///

	while (std::getline(confFile, line))
	{
		splitedLine = split(line, WHITESPACE);
		if (splitedLine[0].compare("location") == 0)
			LocationBlock.push_back(LocationBlockBackup(confFile, line));
		if (splitedLine[0].compare("}") == true)
			break ;
		else
			serverBlock.configsetting(splitedLine);
	}

	// 생성된 서버 체크
	serverBlock.printInfo();

	/// 로케이션 생성해야됨!
	for(int i = 0; i < static_cast<int>(LocationBlock.size()); i++) {
		std::cout << LocationBlock[i] << std::endl;
	}
	///
}