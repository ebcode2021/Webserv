#ifndef SERVER_HPP
# define SERVER_HPP

# include "Webserv.hpp"



class ServerBlock {
	protected :
		unsigned int					_clientMaxBodySize;
		std::vector<std::string>		_serverNameList;
		std::vector<int>				_listenList;
		std::vector<errorPage>			_errorPage;
		bool							_autoindex;
		std::vector<std::string>		_index;
		std::string						_clientBodyTempPath;
		std::string						_root;

	public :
		ServerBlock();
		~ServerBlock();

		static void blockCheck( std::ifstream );
};

#endif

