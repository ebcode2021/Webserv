#ifndef KQUEUEHANDLER_HPP
# define KQUEUEHANDLER_HPP

# include "webserv.hpp"

class KqueueHandler {
	private :
		int				kq;
		struct kevent	eventList[FD_SETSIZE];
		int				eventCnt;

	public :
		KqueueHandler();
		const struct kevent *getEventList();
};

# endif