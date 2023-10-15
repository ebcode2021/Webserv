#include "ModeInfo.hpp"

// constructor
ModeInfo::ModeInfo(SockMode sockMode)
{
	this->_sockMode = sockMode;
	this->_readPhase = R_LINE;
	this->_sendMode = S_CLIENT;
	this->_sendPhase = S_LINE;
}

// getter
SockMode	&ModeInfo::getSockMode()
{
	return (this->_sockMode);
}

ReadPhase	&ModeInfo::getReadPhase()
{
	return (this->_readPhase);
}

SendMode	&ModeInfo::getSendMode()
{
	return (this->_sendMode);
}

SendPhase	&ModeInfo::getSendPhase()
{
	return (this->_sendPhase);
}

// setter
void	ModeInfo::setSockMode(SockMode mode)
{
	this->_sockMode = mode;
}

void	ModeInfo::setReadPhase(ReadPhase phase)
{
	this->_readPhase = phase;
}

void	ModeInfo::setSendMode(SendMode mode)
{
	this->_sendMode = mode;
}

void	ModeInfo::setSendPhase(SendPhase phase)
{
	this->_sendPhase = phase;
}

// method
void	ModeInfo::initialization()
{
	this->_readPhase = R_LINE;
	this->_sendPhase = S_LINE;
	this->_sendMode = S_CLIENT;
}