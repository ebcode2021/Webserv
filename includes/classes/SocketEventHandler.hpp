#ifndef SOCKETEVENTHANDLER_HPP
# define SOCKETEVENTHANDLER_HPP

# include "webserv.hpp"
# include "TcpSocket.hpp"

class SocketEventHandler
{
	private :
		TcpSocket *_socket;
	public :
		int socketAccept();
		//socketConnect


		// Event Processing
		int dataRecv();
		int dataSend();
		int closeSocket();

		// setter
		void	setSocket(TcpSocket *);

		// test_print
		void printSockBuf();
};

#endif