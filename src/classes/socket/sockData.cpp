#include "SockData.hpp"

SockData::SockData()
{
	this->_buf = "";
	this->_recvByte = 0;
	this->_sendByte = 0;
}

void	SockData::operator+(const std::string &data)
{
	this->_buf += data;
}

// getter
const std::string	&SockData::getBuf() const 
{
	return (this->_buf);
}

int	SockData::getRecvByte() const
{
	return (this->_recvByte);
}

int SockData::getSendByte() const
{
	return (this->_sendByte);
}

// setter
void	SockData::setBuf(const std::string &buf)
{
	this->_buf = buf;
}

void	SockData::setRecvByte(int recvByte)
{
	this->_recvByte = recvByte;
}

void	SockData::setSendByte(int sendByte)
{
	this->_sendByte = sendByte;
}

// method
void	SockData::updateSendByte(int sendByte)
{
	this->_sendByte += sendByte;
}

void	SockData::updateRecvByte(int recvByte)
{
	this->_recvByte += recvByte;
}


