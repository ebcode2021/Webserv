#include "utils.hpp"

int createSocket()
{
	int	sock = socket(AF_INET, SOCK_STREAM, 0);
	int option = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) < 0) {
        printErrorWithExit(strerror(errno));
    }
	if (sock == INVALID_SOCKET)
		printErrorWithExit(strerror(errno));
	return (sock);
}

void	setSocketLingerOption(int clientSock)
{
	struct linger lingerOpt;

	lingerOpt.l_onoff = 1; //1이면 TIME_WAIT 사용
	lingerOpt.l_linger = 0; // TIME_WAIT 상태를 0초로 설정

	if (setsockopt(clientSock, SOL_SOCKET, SO_LINGER, &lingerOpt, sizeof(lingerOpt)) < 0)
		std::cout << "setsockopt error" << std::endl;
}

void	changeFdOpt(int fd, int option)
{
	int flags = fcntl(fd, F_GETFL, 0);
	flags |= option;
	fcntl(fd, F_SETFL, flags);
}
