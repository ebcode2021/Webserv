#ifndef	UTILS_HPP
# define UTILS_HPP

# include "webserv.hpp"
# include "KqHandler.hpp"
//# include "SockInfo.hpp"

/* utils */
std::vector<std::string> split(const std::string &, const std::string&);

/* sockUtils.cpp */
int 		createSocket();
void		setSocketLingerOption(int clientSock);
void		changeFdOpt(int fd, int option);

/* serverUtils.cpp */
void		createListenSocketForPorts(const std::set<int> & serverPortList, KqHandler &kq);

/* parseUtils */
std::string	extractRequestLine(std::string &data);
std::string	extractQueryString(std::string &data);

#endif