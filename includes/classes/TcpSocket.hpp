#ifndef TCPSOCKET_HPP
# define TCPSOCKET_HPP

# include "webserv.hpp"

class TcpSocket
{
	private :
		SocketInfo	_socketInfo;
		std::string	buf;

	public :
		TcpSocket();
		TcpSocket(int);
		
		void	socketSend();
		void	socketRecv();

		int		socketAccept();
		void	socketBind(int);
		void	socketListen();


		void	changeToNonblocking();
		void	bufJoin(char *);

		// getter, setter
		int	 getSockFd();
		int	 getSendByte();
		int 	getRecvByte();
		char	*getBuf();
		std::string getString();

		void	bufClear();
		
		void	setBufbyIndex(int, char);

		//test
		const char *getStringToCStr();
		size_t	getStringSzie();
};

#endif