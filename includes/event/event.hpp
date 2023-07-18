#ifndef EVENT_HPP
# define EVENT_HPP

# include "webserv.hpp"
# include "KqHandler.hpp"
# include "SockInfo.hpp"

/* event */
void	processEvent(KqHandler &);

/* eventUtils */
void	acceptConnection(SockInfo *, KqHandler &);
void	closeSock(SockInfo	*);
int		recvData(int , SockData &);
void	sockBindAndListen(int , int);

#endif