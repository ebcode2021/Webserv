#include "ModeInfo.hpp"

// constructor
ModeInfo::ModeInfo(SockMode sockMode)
{
	this->_sockMode = sockMode;
	this->_readMode = R_HEADER;
	this->_sendMode = S_CLIENT;
}

// getter
SockMode	ModeInfo::getSockMode()
{
	return (this->_sockMode);
}

ReadMode	ModeInfo::getReadMode()
{
	return (this->_readMode);
}

SendMode	ModeInfo::getSendMode()
{
	return (this->_sendMode);
}

// setter
void	ModeInfo::setSockMode(SockMode mode)
{
	this->_sockMode = mode;
}

void	ModeInfo::setReadMode(ReadMode mode)
{
	this->_readMode = mode;
}

void	ModeInfo::setSendMode(SendMode mode)
{
	this->_sendMode = mode;
}

// method
void	ModeInfo::initialization()
{
	this->_readMode = R_HEADER;
	this->_sendMode = S_CLIENT;
}