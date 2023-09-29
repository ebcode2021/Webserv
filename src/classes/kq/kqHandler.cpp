#include "KqHandler.hpp"

KqHandler::KqHandler() {
	this->_kq = kqueue();
}

struct kevent *KqHandler::getEventList() {
	return (this->_eventList);
}

void	KqHandler::changeEvent(uintptr_t ident, short filter, unsigned short flags, unsigned int fflags, intptr_t data, void *udata) {
	struct kevent kev;
	EV_SET(&kev, ident, filter, flags, fflags, data, udata);
	_changeList.push_back(kev);
}

void	KqHandler::eventUpdate() {
	struct timespec timeout;
    timeout.tv_sec = 5;  // 타임아웃 시간 (초)
    timeout.tv_nsec = 0;

	int eventCnt = kevent(this->_kq, &this->_changeList[0], this->_changeList.size(), this->_eventList, EVENT_SIZE, &timeout);
	this->_eventCnt = eventCnt;
}

struct kevent KqHandler::getCurEventByIndex(int i) {
	return this->_eventList[i];
}

void	KqHandler::changeListClear() {
	this->_changeList.clear();
}

void	KqHandler::eventListClear() {
	this->_eventCnt = 0;
	memset(this->_eventList, 0, sizeof(struct kevent) * 256);
}

// void	KqHandler::eventUpdate() {
// 	int ret = kevent(this->_kq, &this->_changeList[0], this->_changeList.size(), NULL, 0, NULL);
// 	if (ret == -1) {
// 	//	std::cout << "등록 실패" << std::endl;
// 		printErrorWithExit(strerror(errno));
// 	}
// 	this->changeListClear();
// }

int		KqHandler::getEventCnt() {
	return this->_eventCnt;
}

int		KqHandler::getKqFd() {
	return this->_kq;
}

/* print */
void	KqHandler::printEvent() {
	std::cout << "\n===============Event List===============\n";
	for (size_t i = 0; i < this->_eventCnt; i++)
	{
		std::cout << "sockfd = " << this->_eventList[i].ident << std::endl;
		std::cout << "event = ";
		if (this->_eventList[i].filter == EVFILT_READ)
			std::cout << "Read" << std::endl;
		else if (this->_eventList[i].filter == EVFILT_WRITE)
			std::cout << "Write" << std::endl;
	}
	std::cout << "============================================\n";
}