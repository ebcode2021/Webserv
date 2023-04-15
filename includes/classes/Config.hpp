#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "ServerList.hpp"


class	Config {
	private :
		ServerList	_serverList;
	public :
		Config(std::string);

		static bool	fileCheck(int, char *[]);
		static void	setEnv(std::string, std::string);
};

#endif