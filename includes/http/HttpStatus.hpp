#ifndef HTTP_STATUS_HPP
# define HTTP_STATUS_HPP

# include "webserv.hpp"

class	HttpStatus
{
	private :
		int			_statusCode;
		std::string	_reason;

	public :
		// constructor
		HttpStatus();
		HttpStatus(int);
		
		// getter, setter
		std::map<int, std::string>& getStatusMap();
		int							getStatusCode() const;
		std::string					getReason() const;
		HttpStatus& operator=(const HttpStatus&);
};


#endif