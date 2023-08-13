# include "event.hpp"

bool	clientReadEvent(SockInfo *sockInfo, KqHandler &kq)
{
	(void)kq;
	int	recvRef = recvData(sockInfo->getSockFd(), sockInfo->getSockData());

	if (recvRef <= 0)
		return (false);
	return (true);
}

// void	parseData(SockInfo *sockInfo)
// {
	
// }

// static void	processReadEvent(SockInfo *sockInfo, KqHandler &kq)
// {
// 	const SockMode sockMode = sockInfo->getModeInfo().getSockMode();

// 	switch (sockMode)
// 	{
// 		case M_SERVER:
// 			acceptConnection(sockInfo, kq);
// 			break;
// 		case M_CLIENT:
// 			if (clientReadEvent(sockInfo, kq))
// 			{
// 				sockInfo->getRequest().createRequest(sockInfo->getSockData().getBuf(), sockInfo->getModeInfo().getReadMode());
// 				// 리스폰스 만들기전에 확인
// 			}
// 			break;
// 	}
// }

// void	processEvent(KqHandler &kq, Config	&serverConfig)
// {
// 	struct kevent	curEvent;
// 	SockInfo		*sockInfo;

// 	for (int i = 0; i < kq.getEventCnt(); i++)
// 	{
// 		curEvent = kq.getCurEventByIndex(i);
// 		sockInfo = (SockInfo *)curEvent.udata;

// 		switch (curEvent.filter)
// 		{
// 			case EVFILT_READ:
// 				processReadEvent(sockInfo, kq);
// 			case EVFILT_WRITE:
// 				// processWriteEvent(sockInfo, kq);
// 				break;
// 			case EVFILT_PROC:
// 				break;
// 		}
// 	}
	
// }