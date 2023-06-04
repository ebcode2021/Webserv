#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "ServerInfo.hpp"
# include "HttpRequestHeader.hpp"

class	Config {
	private :
		std::vector<ServerInfo>	_serverList;
		std::set<int>			_listenSockList;

	public :
		// constructor
		Config(std::string);

		// getter
		std::vector<ServerInfo>&	getServerList();
		std::set<int>				getListenSockList();

		// checker
		static bool	fileCheck(int, char *[]);

		// method
		void			addServer(std::ifstream &);
		ServerInfo		findServerInfoByHost(const std::string&);
		ServerInfo		findServerInfoByParameter(const std::string&, const size_t);
};

#endif