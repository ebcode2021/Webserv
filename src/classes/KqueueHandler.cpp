#include "KqueueHandler.hpp"

KqueueHandler::KqueueHandler() {
	this->kq = kqueue();
}

const struct kevent *KqueueHandler::getEventList() {
	return this->eventList;
}

void	KqueueHandler::changeEvent(uintptr_t ident, short filter, unsigned short flags, unsigned int fflags, intptr_t data, void *udata) {
	struct kevent kev;
	EV_SET(&kev, ident, filter, flags, fflags, data, udata);
	changeList.push_back(kev);
}

int	KqueueHandler::waitEvent() {
	int eventCnt = kevent(this->kq, &this->changeList[0], this->changeList.size(), this->eventList, 256, NULL);
	this->eventCnt = eventCnt;
	return (eventCnt);
}

struct kevent KqueueHandler::getCurEventByIndex(int i) {
	return this->eventList[i];
}

void	KqueueHandler::changeListClear() {
	this->changeList.clear();
}

void	KqueueHandler::eventListReset() {
	this->eventCnt = 0;
	memset(this->eventList, 0, sizeof(struct kevent) * 256);
}

void	KqueueHandler::eventUpdate() {
	int ret = kevent(this->kq, &this->changeList[0], this->changeList.size(), NULL, 0, NULL);
	if (ret == -1) {
		std::cout << "등록 실패" << std::endl;
		printErrorWithExit(strerror(errno));
	}
	this->changeListClear();
}

int		KqueueHandler::getEventCnt() {
	return this->eventCnt;
}

int		KqueueHandler::getKqFd() {
	return this->kq;
}

void	KqueueHandler::printEvent() {
	std::cout << "\n===============Event List===============\n";
	for (size_t i = 0; i < this->eventCnt; i++)
	{
		std::cout << "sockfd = " << this->eventList[i].ident << std::endl;
		std::cout << "event = ";
		if (this->eventList[i].filter == EVFILT_READ)
			std::cout << "Read" << std::endl;
		else if (this->eventList[i].filter == EVFILT_WRITE)
			std::cout << "Write" << std::endl;
	}
	std::cout << "============================================\n";
}