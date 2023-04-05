#ifndef HTTP_HPP
# define HTTP_HPP

# include "Webserv.hpp"

class	Http {
	private :
		std::vector<Server>	_server;
	protected :
		
	public :
		Http();
		~Http();
};

#endif