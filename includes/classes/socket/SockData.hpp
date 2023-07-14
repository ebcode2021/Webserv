#ifndef SOCKDATA_HPP
# define SOCKDATA_HPP

# include "webserv.hpp"

class SockData
{
	private :
		std::string _buf;
		int			_recvByte;
		int			_sendByte;
	public :
		// constructor
		SockData();

		// operator
		void	operator+(const std::string &);

		// getter
		const std::string	&getBuf() const;
		int					getRecvByte() const;
		int					getSendByte() const;

		// setter
		void	setBuf(const std::string &);
		void	setRecvByte(int);
		void	setSendByte(int);

		// method
		void	updateSendByte(int);
		void	updateRecvByte(int);
};

#endif