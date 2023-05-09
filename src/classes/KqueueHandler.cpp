#include "KqueueHandler.hpp"

KqueueHandler::KqueueHandler() {
	this->kq = kqueue();
	eventCnt = 0;
}

const struct kevent *KqueueHandler::getEventList() {
	return this->eventList;
}