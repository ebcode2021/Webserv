# include "event.hpp"

bool	clientReadEvent(SockInfo *sockInfo, KqHandler &kq)
{
	(void)kq;
	int	recvRef = recvData(sockInfo->getSockFd(), sockInfo->getSockData());
	if (recvRef <= 0)
		return (false);
	return (true);
}

bool	clientWriteEvent(SockInfo *sockInfo, KqHandler &kq, SessionStorage &sessionStorage)
{
	SendPhase		phase = sockInfo->getModeInfo().getSendPhase();
	int				clientFd = sockInfo->getSockFd();
	HttpRequest		&request = sockInfo->getRequest();
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
			response.getResponseHeader().handleSession(sessionStorage, request.getHttpRequestLine().getRequestURI(), request.getHttpRequestHeader().getHeaderByKey("sessionId"));
			std::string header = response.getResponseHeader().getResponseHeaderToString();
			ret = send(clientFd, header.c_str(), header.size(), 0);
			sockInfo->getModeInfo().setSendPhase(S_BODY);
			break;
		}
		case S_BODY:
		{
			HttpBody &body = response.getBody();
			ret = send(clientFd, body.getBody().c_str(), body.getBodySize(), 0);
			if ((ret > 0) && (ret < (int)body.getBodySize()))
				body.trimBody(ret);
			else {
				if (sockInfo->getRequest().getHttpRequestHeader().getHeaderByKey("connection") != KEEPALIVE) {
					closeSock(sockInfo);
				}
				else {
					kq.changeEvent(sockInfo->getSockFd(), EVFILT_WRITE, EV_DELETE, 0, 0, sockInfo);
					kq.changeEvent(sockInfo->getSockFd(), EVFILT_READ, EV_ADD, 0, 0, sockInfo);
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