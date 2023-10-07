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

// 여기에서의 response랑 무슨차이야? 그럼 여기는 출력을 위한 로직이네??
	switch (phase)
	{
		int ret;
		case S_LINE: 
		{
			std::cout << response.getResponseLine().getHttpStatus().getStatusCode() << std::endl;
			std::string line = response.getResponseLine().getResponseLineToString();
			ret = send(clientFd, line.c_str(), line.size(), 0);
			sockInfo->getModeInfo().setSendPhase(S_HEADER);
			break;
		}
		case S_HEADER: //근데 궁금한거 있어 
		{
			//여기가 문제
			
			response.getResponseHeader().handleSession(sessionStorage, request.getHttpRequestLine().getRequestURI(), request.getHttpRequestHeader().getHeaderByKey("sessionId"));
			std::cout << "문제 지점" << std::endl;
			sessionStorage.printInfo();
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