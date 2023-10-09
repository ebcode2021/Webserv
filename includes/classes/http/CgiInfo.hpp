#ifndef CGIINFO_HPP
# define CGIINFO_HPP

# include "webserv.hpp"
# include "HttpBody.hpp"

class CgiInfo
{
	private :
		int 		_pid;
		int 		_readFd;
		int 		_writeFd;
		HttpBody	_data;

	public :
		CgiInfo(int, int, int);

		// getter
		int			getReadFd();
		int			getWriteFd();
		int			getPid();
		HttpBody	&getData();
		
		// setter
		void	SetReadFd(int);
		void	SetWriteFd(int);
		void	SetPid(int);

};


#endif