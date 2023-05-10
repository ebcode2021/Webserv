#include "KqueueHandler.hpp"

KqueueHandler::KqueueHandler() {
	this->kq = kqueue();
	eventCnt = 0;
}

const struct kevent *KqueueHandler::getEventList() {
	return this->eventList;
}

void	KqueueHandler::changeEvent(uintptr_t ident, short filter, unsigned short flags, unsigned int fflags, intptr_t data, void *udata) {
	struct kevent kev;
	EV_SET(&kev, ident, filter, flags, fflags, data, udata);
	changeList.push_back(kev);
}

int	KqueueHandler::kevent() {
	
}