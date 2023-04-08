#ifndef HTTP_HPP
# define HTTP_HPP

# include "Webserv.hpp"

class	HttpBlock {
	private :
		std::vector<ServerBlock>	_serverList;
	protected :
		
	public :
		HttpBlock();
		~HttpBlock();
};

#endif