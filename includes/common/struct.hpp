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
	size_t	sendbyte;
	size_t	recvbyte;
}			SocketInfo;

#endif