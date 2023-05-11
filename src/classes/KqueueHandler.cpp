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
	int eventCnt = kevent(this->kq, &this->changeList[0], this->changeList.size(), this->eventList, FD_SETSIZE, NULL);
	return eventCnt;
}

struct kevent KqueueHandler::getCurEventByIndex(int i) {
	return this->eventList[i];
}

void	KqueueHandler::changeListClear() {
	this->changeList.clear();
}