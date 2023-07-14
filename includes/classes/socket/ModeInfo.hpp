#ifndef MODEINFO_HPP
# define MODEINFO_HPP

# include "enum.hpp"

class ModeInfo
{
	private:
		SockMode	_sockMode;
		ReadMode	_readMode;
		SendMode	_sendMode;

	public:
		ModeInfo(SockMode);

		// getter
		SockMode	getSockMode();
		ReadMode	getReadMode();
		SendMode	getSendMode();
		
		// setter
		void	setSockMode(SockMode);
		void	setReadMode(ReadMode);
		void	setSendMode(SendMode);

		// method
		void	initialization();
};

#endif