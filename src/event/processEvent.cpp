# include "event.hpp"

bool	clientReadEvent(SockInfo *sockInfo, KqHandler &kq)
{
	(void)kq;
	int	recvRef = recvData(sockInfo->getSockFd(), sockInfo->getSockData());
	if (recvRef <= 0)
		return (false);
	return (true);
}

bool	clientWriteEvent(SockInfo *sockInfo, KqHandler &kq)
{
	SendPhase		phase = sockInfo->getModeInfo().getSendPhase();
	int				clientFd = sockInfo->getSockFd();
	HttpResponse	&response = sockInfo->getResponse();

	switch (phase)
	{
		int ret;
		case S_LINE: 
		{
			std::string line = response.getResponseLine().getResponseLineToString();
			std::cout << line << std::endl;
			ret = send(clientFd, line.c_str(), line.size(), 0);
			sockInfo->getModeInfo().setSendPhase(S_HEADER);
			break;
		}
		case S_HEADER:
		{
			std::string header = response.getResponseHeader().getResponseHeaderToString();
			std::cout << header << std::endl;
			ret = send(clientFd, header.c_str(), header.size(), 0);
			sockInfo->getModeInfo().setSendPhase(S_BODY);
			break;
		}
		case S_BODY:
		{
			HttpBody &body = response.getBody();
			std::cout << body.getBody() << std::endl;
			ret = send(clientFd, body.getBody().c_str(), body.getBodySize(), 0);
			if ((ret > 0) && (ret < (int)body.getBodySize()))
				body.trimBody(ret);
			else {
				if (sockInfo->getRequest().getHttpRequestHeader().getHeaderByKey("connection") != KEEPALIVE) {
					std::cout << "종료" << std::endl;
					closeSock(sockInfo);
				}
				else {
					kq.changeEvent(sockInfo->getSockFd(), EVFILT_WRITE, EV_DELETE, 0, 0, sockInfo);
					sockInfo->reset();
				}
			}
			break;
		}
		case S_END:
			break;
	}
	return (true);
}