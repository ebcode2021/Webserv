#ifndef HTTP_STATUS_HPP
# define HTTP_STATUS_HPP

# include "webserv.hpp"

class	HttpStatus
{
	private :
		int			_statusCode;
		std::string	_reason;

	public :
		// getter, setter
		int			getStatusCode();
		std::string	getReason();

		void		setStatusCode();
		void		setReason();
};

#endif