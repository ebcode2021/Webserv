#ifndef CGIINFO_HPP
# define CGIINFO_HPP

# include "webserv.hpp"

class CgiInfo
{
	private :
		int _pid;
		int _readFd;
		int _writeFd;
	public :
		CgiInfo(int, int, int);

		// getter
		int		getReadFd();
		int		getWriteFd();
		int		getPid();
		
		// setter
		void	SetReadFd(int);
		void	SetWriteFd(int);
		void	SetPid(int);

};


#endif