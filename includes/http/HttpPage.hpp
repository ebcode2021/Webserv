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
		bool						defaultSwitch;
		// default

		// "error_page" keyword in server_block
		std::vector<ErrorPage>					_ServerErrorPage;
		std::vector<ErrorPage>					_locationErrorPage;
		//index index.html
		ServerBlock					_serverBlock;
		LocationBlock				_locationBlock;

		// 40x, 50x -> 생성하는 함수
		// index.html


		// location error_page

		// "root", "index" keyword (priority : location block > server block)
		std::string					_serverRoot;
		std::string					_locationRoot;
		std::vector<std::string>	_index;

		std::string					_returnPage;

		// auto_index
		bool						_isAutoIndex; // on을 줄 경우에는 무조건 보이게 "on"
		
		
	public :
		// constructor
		HttpPage();
		HttpPage(ServerInfo&);

		// methods
		HttpPage	saveLocationBlockData();
		void		setServerData(ServerBlock&);
		void		setLocationData(LocationBlock&);

};

#endif