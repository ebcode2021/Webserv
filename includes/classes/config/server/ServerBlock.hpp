#ifndef SERVER_BLOCK_HPP
# define SERVER_BLOCK_HPP

# include "ErrorPage.hpp"
# include "validate.hpp"
# include "webserv.hpp"

class ServerBlock {
	protected :
		unsigned int					_clientMaxBodySize;
		std::vector<std::string>		_serverNameList;
		std::vector<int>				_listenPortList;
		std::vector<ErrorPage>			_errorPage;
		bool							_autoindex;
		std::vector<std::string>		_index;
		std::string						_clientBodyTempPath;
		std::string						_root;

	public :
		// constructor
		ServerBlock();

		// getter
		std::vector<ErrorPage>		getErrorPage() const;
		std::vector<int>			getListenPortList() const;
		std::string					getRoot() const;
		std::vector<std::string>	getServerNameList() const;
		std::vector<std::string>	getIndexList() const;
		bool						getAutoIndex() const;
		unsigned int				getClientMaxBodySize() const;

		// setter
		void						setListenPort(std::vector<std::string>&);
		void						setServerName(std::vector<std::string>&);
		void						setErrorPage(std::vector<std::string>&);
		void						setClientMaxBodySize(std::vector<std::string>&);
		void						setAutoIndex(std::vector<std::string>&);
		void						setIndex(std::vector<std::string>&);
		void						setClientBodyTempPath(std::vector<std::string>&);
		void						setRoot(std::vector<std::string>&);
		
		// method
		static void blockCheck(std::ifstream&, Validate&);
		void		configsetting(std::vector<std::string>&);

		// print
		void		printInfo() const;

};

#endif

