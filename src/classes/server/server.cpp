#include "Server.hpp"
#include "utils.hpp"
#include "event.hpp"

Server::Server(const Config &config) :
	_serverInfoList(config.getServerInfoList()),
	_serverPortList(config.getServerPortList())
{}

void	Server::processReadEvent(SockInfo *sockInfo)
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
				int status = sockInfo->getRequest().createRequest(sockInfo->getSockData().getBuf(), sockInfo->getModeInfo().getReadMode());
				sockInfo->getStatus().setHttpStatus(status);
				processRequest(sockInfo, this->_serverInfoList, this->kq);
			}
			else {
				closeSock(sockInfo);
			}
			break;
	}
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
			case EVFILT_WRITE:
				// processWriteEvent(sockInfo, kq);
				break;
			case EVFILT_PROC:
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