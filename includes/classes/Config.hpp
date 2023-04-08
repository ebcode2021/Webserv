#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "Webserv.hpp"

class	Config {
	private :
		// event block 추가
		HttpBlock	_httpBlock;
	public :
		Config(std::string);

		static bool fileCheck(std::string);
};

#endif