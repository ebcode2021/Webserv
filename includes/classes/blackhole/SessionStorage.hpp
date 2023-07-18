#ifndef SESSION_STORAGE_HPP
# define SESSION_STORAGE_HPP

# include "webserv.hpp"
# include "HttpSession.hpp"
# include "ResponseException.hpp"

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
		HttpSession		generateSession(const std::string&);
		bool			isSession(const std::string&);
		HttpSession		getSession(std::string&);
		bool			isEqulSessionAndURL(const std::string&, const std::string&);
		//std::string		getStoragePath() const;
		//void			createCacheDirectory();

		// validate
		void			validateSession(const std::string&, const std::string&);


		// print
		void			printInfo();

};
#endif