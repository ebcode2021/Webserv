#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "ServerInfo.hpp"
# include "ServerInfoList.hpp"
# include "indication.hpp"
# include "enum.hpp"

class	Config {
	private :
		ServerInfoList			_serverInfoList;
		std::set<int>			_serverPortList;

	public :
		// constructor
		Config(const std::string &);

		// getter
		const ServerInfoList	&getServerInfoList() const;
		const std::set<int>		&getServerPortList() const;
		
		// checker
		static bool				fileCheck(int, char *[]);

		// print
		void	printConfig();
};

#endif