#ifndef CGIINFO_HPP
# define CGIINFO_HPP

# 

class CgiInfo
{
	private :
		int pid;
		int readFd;
		int writeFd;
	public :
		CgiInfo(int, int, int);

		// getter, setter
		int		getReadFd();
		void	SetReadFd(int);
		int		getWriteFd();
		void	SetWriteFd(int);
		int		getPid();
		void	SetPid(int);

};


#endif