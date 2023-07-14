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