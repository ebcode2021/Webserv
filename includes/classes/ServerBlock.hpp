#ifndef SERVER_HPP
# define SERVER_HPP

# include "ErrorPage.hpp"
# include "webserv.hpp"

class ServerBlock {
	protected :
		unsigned int					_clientMaxBodySize;
		std::vector<std::string>		_serverNameList;
		std::vector<int>				_listenList;
		std::vector<ErrorPage>			_errorPage;
		bool							_autoindex;
		std::vector<std::string>		_index;
		std::string						_clientBodyTempPath;
		std::string						_root;

	public :
		ServerBlock();

		static void blockCheck(std::ifstream&, Validate&);
		void		configsetting(std::vector<std::string>&);
		void		setListenPort(std::vector<std::string>&);
		void		setServerName(std::vector<std::string>&);
		void		setErrorPage(std::vector<std::string>&);
		void		setClientMaxBodySize(std::vector<std::string>&);
		void		setAutoIndex(std::vector<std::string>&);
		void		setIndex(std::vector<std::string>&);
		void		setClientBodyTempPath(std::vector<std::string>&);
		void		setRoot(std::vector<std::string>&);

		//test
		void		printInfo();
};

#endif

