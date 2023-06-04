#ifndef SOCKETEVENTHANDLER_HPP
# define SOCKETEVENTHANDLER_HPP

# include "webserv.hpp"
# include "TcpSocket.hpp"

class SocketEventHandler
{
	private :
		TcpSocket*	_socket;

	public :
		// constructor
		SocketEventHandler();

		int socketAccept();
		//socketConnect

		// socketFunction
		int		sockAccept();
		int		sockBind(int);
		int		sockListen();

		// Event Processing
		int		dataRecv();
		int		dataSend();
		void	closeSocket();

		// setter
		void	setSocket(TcpSocket *);

		// 은비 추가
		void	setSocketLingerOption(int);

		// test_print
		void printSockBuf();
		void printSockFd();
};

#endif