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

		// test
		void	printStatus()
		{
			std::cout << "[HttpStatus 출력]" << std::endl;
			std::cout << "- statusCode : " << this->_statusCode << std::endl;
			std::cout << "- reason : " << this->_reason << std::endl;
		};
};


#endif