#ifndef HTTP_SESSION_HPP
# define HTTP_SESSION_HPP

# include "webserv.hpp"

class	HttpSession
{
	private :
		std::string	_sessionId;
		std::string	_previousURL;
		time_t		_expiration;
		std::string	_data;

	public :
		// constructor
		HttpSession();
		HttpSession(const std::string&);

		// getter, setter
		std::string	getSessionId() const;
		time_t		getExpiration() const;
		std::string	getPreviousURL() const;
		std::string	getData() const;
		void		setData(const std::string&);
		void		setPreviousURL(const std::string&);

		// method
		void		createSessionFile();
		std::string	createSessionId();
		time_t		createExpirationTime();
		bool		isCacheDirectory();

		// print
		void		printInfo();
};

#endif