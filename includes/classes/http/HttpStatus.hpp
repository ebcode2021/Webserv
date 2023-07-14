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
		HttpStatus(const int);
		HttpStatus(const HttpStatus&);
		HttpStatus& operator=(const HttpStatus&);
		
		// getter, setter
		int							getStatusCode() const;
		std::string					getReason() const;
		void						setHttpStatus(const int);

		// method
		std::map<int, std::string>& getStatusMap() const;

		// print
		void						printStatus();
};


#endif