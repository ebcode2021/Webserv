#ifndef EVENTHANDLER_HPP
# define EVENTHANDLER_HPP

# include "webserv.hpp"
# include "SockInfo.hpp"
# include "KqHandler.hpp"

class EventHandler
{
	private :

	public :
		// constructor
		SockHandler();

		// setter
		void	setSockInfo(SockInfo *);

		// socketFunction
		int		sockAccept();
		int		sockBind(int);
		int		sockListen();
		//int		sockRecv();
		//int		sockSend();
		void	closeSock();

		



};

#endif