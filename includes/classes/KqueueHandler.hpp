#ifndef KQUEUEHANDLER_HPP
# define KQUEUEHANDLER_HPP

# include "webserv.hpp"

class KqueueHandler {
	private :
		int							kq;
		size_t						eventCnt;
		std::vector<struct kevent>	changeList;
		struct kevent				eventList[EVENT_SIZE];

	public :
		/* constructor */
		KqueueHandler();

		/* getter */
		const struct kevent	*getEventList();
		struct kevent		getCurEventByIndex(int);
		int					getEventCnt();
		int					getKqFd();

		/* method */
		void	changeEvent(uintptr_t ident, short filter, unsigned short flags, unsigned int fflags, intptr_t data, void *udata);
		void	changeListClear();
		void	eventListReset();
		void	eventUpdate();
		int		waitEvent();

		/* print */
		void printEvent();
};

# endif