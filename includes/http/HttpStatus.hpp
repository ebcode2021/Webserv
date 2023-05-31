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
		HttpStatus(const HttpStatus&);
		HttpStatus(const int);
		HttpStatus& operator=(const HttpStatus&);
		
		// getter, setter
		std::map<int, std::string>& getStatusMap() const;
		int							getStatusCode() const;
		std::string					getReason() const;
		void						setHttpStatus(const int);

		// print
		void						printStatus();
};


#endif