#ifndef KQUEUEHANDLER_HPP
# define KQUEUEHANDLER_HPP

# include "webserv.hpp"

class KqueueHandler {
	private :
		int							kq;
		std::vector<struct kevent>	changeList;
		struct kevent				eventList[FD_SETSIZE];

	public :
		KqueueHandler();
		const struct kevent *getEventList();
		void	changeEvent(uintptr_t ident, short filter, unsigned short flags, unsigned int fflags, intptr_t data, void *udata);
		int		waitEvent();
		void	changeListClear();

		struct kevent getCurEventByIndex(int);
};

# endif