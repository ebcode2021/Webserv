#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "ServerInfo.hpp"
# include "HttpRequestHeader.hpp"

class	Config {
	private :
		std::vector<ServerInfo>	_serverList;

	public :
		Config(std::string);

		static bool fileCheck(std::string);
		//test
		static bool	fileCheck(int, char *[]);
		//void	printServerList();

		void	addServer(std::ifstream &);

		//ServerInfo&	getServer(const HttpRequestHeader&);
		//size_t	getServerListSize();
		std::vector<ServerInfo>&	getServerList();

		// 추가추가
		ServerInfo&		findServerInfoByHost(const std::string&);
};

#endif