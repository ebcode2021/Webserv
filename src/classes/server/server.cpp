#include "Server.hpp"
#include "utils.hpp"
#include "event.hpp"

/* constructor */
Server::Server(const Config &config) :
	_serverInfoList(config.getServerInfoList()),
	_serverPortList(config.getServerPortList())
{}

/* getter */
ServerInfoList		Server::getServerInfoList() {
	return (this->_serverInfoList);
};

/* method */
void	cgiReadEvent(SockInfo *sockInfo, KqHandler &kq)
{
	char save[BUFSIZE];
	CgiInfo *cgiInfo = sockInfo->getCgiInfo();
	int ret = read(cgiInfo->getReadFd(), save, BUFSIZ);
	if (ret <= 0)
	{
		close(cgiInfo->getReadFd());
		sockInfo->getModeInfo().setSendMode(S_CGI);
		kq.changeEvent(sockInfo->getSockFd(), EVFILT_WRITE, EV_ADD, 0, 0, sockInfo);
	}
	else
	{
		save[ret] = 0;
		cgiInfo->getData() += save;
	}
}

void	Server::processReadEvent(SockInfo *sockInfo)
{
	SockMode sockMode = sockInfo->getModeInfo().getSockMode();

	switch (sockMode)
	{
		case M_SERVER:
			acceptConnection(sockInfo, kq);
			break;
		case M_CLIENT:
			if (clientReadEvent(sockInfo, kq))
			{
				int status = sockInfo->getRequest().createRequest(sockInfo->getSockData().getBuf(), sockInfo->getModeInfo().getReadPhase());
				if (sockInfo->getModeInfo().getReadPhase() == R_END) {
					sockInfo->getStatus().setHttpStatus(status);
					processRequest(sockInfo, this->_sessionStorage, this->_serverInfoList, this->kq);
				}
			}
			else 
				closeSock(sockInfo);
			break;
		case M_CGI:
			cgiReadEvent(sockInfo, kq);
			break;
	}
}

void	cgiWriteEvent(SockInfo *sockInfo, KqHandler &kq)
{
	CgiInfo *cgiInfo = sockInfo->getCgiInfo();
	HttpBody	&body = sockInfo->getRequest().getHttpBody();
	(void)kq;
	int ret = write(cgiInfo->getWriteFd(), body.getBody().c_str(), body.getBodySize());
	if (ret < 0)
	{
		close(cgiInfo->getWriteFd());
	}
	if (ret < (int)body.getBodySize())
		body.trimBody(ret);
	else {
		close(cgiInfo->getWriteFd());
	}
}

void cgiDataSend(SockInfo *sockInfo, KqHandler &kq)
{
	HttpBody &body = sockInfo->getCgiInfo()->getData();
	int ret = send(sockInfo->getSockFd(), body.getBody().c_str(), body.getBodySize(), 0);
	if (ret < (int)body.getBodySize())
		body.trimBody(ret);
	else {
		kq.changeEvent(sockInfo->getSockFd(), EVFILT_WRITE, EV_DELETE, 0, 0, sockInfo);
		delete sockInfo->getCgiInfo();
		if (sockInfo->getRequest().getHttpRequestHeader().getHeaderByKey("connection") == KEEPALIVE)
			sockInfo->reset();
		else
			closeSock(sockInfo);

	}
}

void	Server::processWriteEvent(SockInfo *sockInfo, KqHandler &kq)
{
	SendMode sendMode = sockInfo->getModeInfo().getSendMode();
	
	switch (sendMode)
	{
		case S_PROCESS:
			cgiWriteEvent(sockInfo, kq);
			break ;
		case S_CLIENT:
			clientWriteEvent(sockInfo, kq, this->_sessionStorage);
			break ;
		case S_CGI:
			cgiDataSend(sockInfo, kq);
			break ;
	}
}

void	processTerminated(SockInfo *sockInfo, KqHandler &kq)
{	
	kq.changeEvent(sockInfo->getCgiInfo()->getReadFd() , EVFILT_READ, EV_ADD, 0, 0, sockInfo);
}

void	Server::processEvent()
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
				processReadEvent(sockInfo);
				break ;
			case EVFILT_WRITE:
				processWriteEvent(sockInfo, kq);
				break;
			case EVFILT_PROC:
				processTerminated(sockInfo, kq);
				break;
		}
	}
}

void	Server::run()
{
	createListenSocketForPorts(this->_serverPortList, this->kq);
	while (true)
	{
		kq.eventUpdate();
		kq.changeListClear();
		processEvent();
		kq.eventListClear();
	}
}
