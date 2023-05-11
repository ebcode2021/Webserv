#ifndef EVENT_HPP
# define EVENT_HPP

# include "webserv.hpp"
# include "TCPSocket.hpp"

class EventHandler
{
	private :
		TcpSocket *socket;
	public :
		EventHandler(TcpSocket &);
};

#endif