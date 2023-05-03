#ifndef STRUCT_HPP
# define STRUCT_HPP

# include "webserv.hpp"

typedef struct errorPage
{
	std::vector<int>	statusCode;
	std::string			path;
}						errorPage;

typedef struct SocketInfo
{
	int		sock;
	char	buf[BUFSIZE + 1];
	int		sendbyte;
	int		recvbyte;
}			SocketInfo;

#endif