# include "event.hpp"
# include "HttpRequest.hpp"

bool	clientReadEvent(SockInfo *sockInfo, KqHandler &kq)
{
	(void)kq;
	int	recvRef = recvData(sockInfo->getSockFd(), sockInfo->getSockData());

	if (recvRef == -1)
	{
		closeSock(sockInfo);
		return (false);
	}
	//sockInfo->getSockData().printBuf();
	return (true);
}

// void	parseData(SockInfo *sockInfo)
// {
	
// }

static void	processReadEvent(SockInfo *sockInfo, KqHandler &kq)
{
	const SockMode sockMode = sockInfo->getModeInfo().getSockMode();

	switch (sockMode)
	{
		case M_SERVER:
			acceptConnection(sockInfo, kq);
			break;
		case M_CLIENT:
			if (clientReadEvent(sockInfo, kq))
			{
				sockInfo->getRequest().createRequest(sockInfo->getSockData().getBuf(), sockInfo->getModeInfo().getReadMode());
				sockInfo->getRequest().getHttpRequestLine().print();
			}
			break;
	}
}

void	processEvent(KqHandler &kq)
{
	struct kevent	curEvent;
	SockInfo		*sockInfo;

	for (int i = 0; i < kq.getEventCnt(); i++)
	{
		curEvent = kq.getCurEventByIndex(i);
		sockInfo = (SockInfo *)curEvent.udata;

		switch (curEvent.filter)
		{
			case EVFILT_READ:
				processReadEvent(sockInfo, kq);
			case EVFILT_WRITE:
				break;
			case EVFILT_PROC:
				break;
		}
	}
	
}