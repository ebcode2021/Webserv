#ifndef SESSION_STORAGE_HPP
# define SESSION_STORAGE_HPP

# include "webserv.hpp"
# include "HttpSession.hpp"

class	SessionStorage
{
	private :
		std::map<std::string, HttpSession>	_sessionList;
		std::string							_storagePath;

	public :
		

};
#endif