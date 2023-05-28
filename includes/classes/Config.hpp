#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "ServerInfo.hpp"
# include "HttpRequestHeader.hpp"

class	Config {
	private :
		std::vector<ServerInfo>	_serverList;
		std::set<int>			_listenSockList;

	public :
		Config(std::string);

		//test
		static bool	fileCheck(int, char *[]);
		//void	printServerList();

		void	addServer(std::ifstream &);
		std::set<int>	getListenSockList();

		std::vector<ServerInfo>&	getServerList();

		// 추가추가
		ServerInfo		findServerInfoByHost(const std::string&);
		ServerInfo		findServerInfoByParameter(std::string&, size_t);
};

#endif