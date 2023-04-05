#ifndef SERVER_HPP
# define SERVER_HPP

# include "Webserv.hpp"

typedef struct errorPage
{
	std::vector<int>	statusCode;
	std::string			path;
}						errorPage;

class Server {
	private :
		std::vector<Location>		_locationList;
		std::vector<int>			_listenList;
		std::vector<std::string>	_serverNameList;
		bool						_tcpNodelay;
		std::vector<errorPage>		_errorPage;
		//bool						_sendfile;
	public :
		Server();
		~Server();

};

#endif

