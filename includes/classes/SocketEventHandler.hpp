#ifndef SOCKETEVENTHANDLER_HPP
# define SOCKETEVENTHANDLER_HPP

# include "webserv.hpp"
# include "TcpSocket.hpp"

class SocketEventHandler
{
	private :
		TcpSocket *_socket;
	public :
		SocketEventHandler();

		int socketAccept();
		//socketConnect


		// Event Processing
		int		dataRecv();
		int		dataSend();
		void closeSocket();

		// setter
		void	setSocket(TcpSocket *);

		// test_print
		void printSockBuf();
};

#endif