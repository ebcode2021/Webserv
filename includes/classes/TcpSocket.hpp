#ifndef TCPSOCKET_HPP
# define TCPSOCKET_HPP

# include "webserv.hpp"

class TcpSocket
{
	private :
		SocketInfo	_socketInfo;

	public :
		TcpSocket();
		TcpSocket(int);
		
		void	socketSend();
		void	socketRecv();

		int		socketAccept();
		void	socketBind(int);
		void	socketListen();


		void	changeToNonblocking();

		// getter, setter
		int	 getSockFd();
		int	 getSendByte();
		int 	getRecvByte();
		char	*getBuf();

		void	bufClear();
};

#endif