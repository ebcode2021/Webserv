#ifndef KQHANDLER_HPP
# define KQHANDLER_HPP

# include "webserv.hpp"

class KqHandler {
	private :
		int							_kq;
		size_t						_eventCnt;
		std::vector<struct kevent>	_changeList;
		struct kevent				_eventList[EVENT_SIZE];

	public :
		/* constructor */
		KqHandler();

		/* getter */
		struct kevent		*getEventList();
		struct kevent		getCurEventByIndex(int);
		int					getEventCnt();
		int					getKqFd();

		/* method */
		void	changeEvent(uintptr_t ident, short filter, unsigned short flags, unsigned int fflags, intptr_t data, void *udata);
		void	changeListClear();
		void	eventListClear();
		void	eventUpdate();

		/* print */
		void printEvent();
};

# endif