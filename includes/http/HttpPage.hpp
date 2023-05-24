#ifndef DEFAULT_PAGE_HPP
# define DEFAULT_PAGE_HPP

# include "webserv.hpp"
# include "ServerInfo.hpp"
# include "ErrorPage.hpp"

class	HttpPage
{
	private :
		// status
		HttpStatus					_httpStatus;

		// default page set
		std::string					_defaultRoot;
		std::string					_defaultPath; //index
		std::string					_default40xPath; 
		std::string					_default50xPath;

		// "error_page" keyword in server_block
		ErrorPage					_40xErrorPage;
		ErrorPage					_50xErrorPage;

		// "root", "index" keyword (priority : location block > server block)
		std::string					_serverRoot;
		std::string					_locationRoot;
		std::vector<std::string>	_index;

		std::string					_returnPage;

		// auto_index
		bool						_isAutoIndex; // on을 줄 경우에는 무조건 보이게

	public :
		// constructor
		HttpPage(ServerInfo&);

		// methods
		HttpPage	saveLocationBlockData();

};

#endif