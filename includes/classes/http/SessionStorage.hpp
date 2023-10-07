#ifndef SESSION_STORAGE_HPP
# define SESSION_STORAGE_HPP

# include "webserv.hpp"
# include "HttpSession.hpp"

class	SessionStorage
{
	private :
		std::map<std::string, HttpSession>	_sessionList;

	public :
		// constructor
		SessionStorage();

		// method
		void			addSession(HttpSession&);
		void			deleteSession(const std::string&);
		bool			isSession(const std::string&);
		HttpSession		getSession(std::string&);
		//std::string		getStoragePath() const;
		void			createCacheDirectory();

		// validate
		bool			validateSession(const std::string&, const std::string&);


		// print
		void			printInfo();

};
#endif