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
			ret = send(clientFd, line.c_str(), line.size(), 0);
			sockInfo->getModeInfo().setSendPhase(S_HEADER);
			break;
		}
		case S_HEADER:
		{
			std::string header = response.getResponseHeader().getResponseHeaderToString();
			ret = send(clientFd, header.c_str(), header.size(), 0);
			sockInfo->getModeInfo().setSendPhase(S_BODY);
			break;
		}
		case S_BODY:
		{
			HttpBody &body = response.getBody();
			ret = send(clientFd, body.getBody().c_str(), body.getBodySize(), 0);
			if (ret < (int)body.getBodySize())
				body.trimBody(ret);
			else {
				kq.changeEvent(sockInfo->getSockFd(), EVFILT_WRITE, EV_DELETE, 0, 0, sockInfo);
				if (sockInfo->getRequest().getHttpRequestHeader().getHeaderByKey("connection") != KEEPALIVE) {
					closeSock(sockInfo);
				}
			}
			break;
		}
		case S_END:
			break;
	}
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