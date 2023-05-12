#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "ServerInfo.hpp"


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
};

#endif