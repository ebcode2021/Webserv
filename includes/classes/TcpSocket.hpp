#ifndef TCPSOCKET_HPP
# define TCPSOCKET_HPP

# include "webserv.hpp"
# include "HttpRequest.hpp"

class TcpSocket
{
	private :
		SocketInfo	_socketInfo;
		HttpRequest	_request;
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

		void	setRequest();


		//test
		const char *getStringToCStr();
		size_t	getStringSzie();
		void stringClear();
};

#endif