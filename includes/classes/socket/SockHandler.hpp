#ifndef SOCKHANDLER_HPP
# define SOCKHANDLER_HPP

# include "webserv.hpp"
# include "SockInfo.hpp"

class SockHandler
{
	private :
		SockInfo*	_socket;

	public :
		// constructor
		//SocketHandler();

		//socketConnect

		// socketFunction
		int		socketAccept();
		int		sockAccept();
		int		sockBind(int);
		int		sockListen();
		int		dataRecv();
		int		dataSend();
		void	closeSocket();

		

		// setter
		void	setSocket(SockInfo *);

		// 은비 추가
		void	setSocketLingerOption(int);

		// test_print
		void printSockBuf();
		void printSockFd();
};

#endif