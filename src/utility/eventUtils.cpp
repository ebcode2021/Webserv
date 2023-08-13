#include "event.hpp"

void	acceptConnection(SockInfo *sockInfo, KqHandler &kq)
{
	int			clientFd;
	sockaddr_in	clientAddress;
	socklen_t	clientAddressSize = sizeof(clientAddress);

	clientFd = accept(sockInfo->getSockFd(), (struct sockaddr *)&clientAddress, &clientAddressSize);
	if (clientFd <= 0)
		std::cout << "클라이언트 접속 실패" << std::endl;
	else {
		char	clientIp[INET_ADDRSTRLEN];
		int		clientPort;	
		inet_ntop(AF_INET, &clientAddress.sin_addr, clientIp, sizeof(clientIp));
		clientPort = clientAddress.sin_port;
		std::cout << "Client Ip: " << clientIp
				<< "\nClient Port: " << clientPort << std::endl;
		kq.changeEvent(clientFd, EVFILT_READ, EV_ADD, 0, 0, new SockInfo(clientFd, std::string(clientIp), clientPort, sockInfo->getServerPort(), M_CLIENT));
	}
}

int	recvData(int sockFd, SockData &curData)
{
	int			readByte = 0;
	char		buf[BUFSIZE + 1];

	std::memset(buf, 0, BUFSIZE);
	while (true)
	{
		readByte = recv(sockFd, buf, BUFSIZE, 0);
		if (readByte > 0) {
			curData += buf;
			curData.updateRecvByte(readByte);
			std::memset(buf, 0, BUFSIZE);
			if (readByte < (int)BUFSIZE)
				return (1);
		}
		else
			return (readByte);
	}
}

void	sockBindAndListen(int fd, int port)
{
	struct sockaddr_in	serverAddr;

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(port);

	if (bind(fd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
		printErrorWithExit(strerror(errno));
	if (listen(fd, FD_SETSIZE))
		printErrorWithExit(strerror(errno));
}

void	closeSock(SockInfo	*sockInfo)
{
	close(sockInfo->getSockFd());
	delete(sockInfo);
}