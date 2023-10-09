#ifndef EVENT_HPP
# define EVENT_HPP

# include "webserv.hpp"
# include "KqHandler.hpp"
# include "SockInfo.hpp"
# include "ServerInfo.hpp"
# include "HttpRequest.hpp"
# include "Config.hpp"
# include "PathInfo.hpp"


/* event */
void		processEvent(KqHandler &, Config &);
bool		clientReadEvent(SockInfo *sockInfo, KqHandler &kq);
bool		clientWriteEvent(SockInfo *sockInfo, KqHandler &kq, SessionStorage&);

/* eventUtils */
void		acceptConnection(SockInfo *, KqHandler &);
void		closeSock(SockInfo	*);
int			recvData(int , SockData &);
void		sockBindAndListen(int , int);
MethodType	findMethodType(std::string);

/* request */
int			processRequest(SockInfo *, SessionStorage&, ServerInfoList, KqHandler &);

#endif