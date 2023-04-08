#ifndef SERVER_HPP
# define SERVER_HPP

# include "Webserv.hpp"

typedef struct errorPage
{
	std::vector<int>	statusCode;
	std::string			path;
}						errorPage;

class ServerBlock : public HttpBlock {
	private :
		std::vector<std::string>		_serverNameList;
		std::vector<LocationBlock>		_locationList;
		std::vector<int>				_listenList;
		std::vector<errorPage>			_errorPage;
		bool							_tcpNodelay;
		//bool							_sendfile;
	public :
		ServerBlock();
		~ServerBlock();

};

#endif

