#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "ServerInfo.hpp"
//# include "HttpRequestHeader.hpp"
# include "indication.hpp"
# include "enum.hpp"

class	Config {
	private :
		std::vector<ServerInfo>	_serverList;
		std::set<int>			_serverPortList;

	public :
		// constructor
		Config(const std::string &);

		// getter
		const std::vector<ServerInfo>	&getServerList() const;
		const std::set<int>				&getServerPortList() const;

		// method
		void					addServer(const ServerInfo &);
		ServerInfo				findServerInfoByHost(const std::string&);
		ServerInfo				findServerInfoByParameter(const std::string&, const size_t);
		
		// checker
		static bool				fileCheck(int, char *[]);

		// print
		void	printConfig() const;
};

#endif