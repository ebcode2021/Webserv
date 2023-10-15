#ifndef MODEINFO_HPP
# define MODEINFO_HPP

# include "enum.hpp"

class ModeInfo
{
	private:
		SockMode	_sockMode;
		SendMode	_sendMode;
		ReadPhase	_readPhase;
		SendPhase	_sendPhase;

	public:
		ModeInfo(SockMode);

		// getter
		SockMode&	getSockMode();
		ReadPhase&	getReadPhase();
		SendMode&	getSendMode();
		SendPhase&	getSendPhase();
		
		// setter
		void	setSockMode(SockMode);
		void	setReadPhase(ReadPhase);
		void	setSendMode(SendMode);
		void	setSendPhase(SendPhase);

		// method
		void	initialization();
};

#endif