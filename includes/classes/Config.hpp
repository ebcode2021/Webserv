#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "Webserv.hpp"

class	Config {
	private :
		ServerInfo _serverInfo;
		
	public :
		Config(std::string);

		static bool fileCheck(std::string);
};

#endif