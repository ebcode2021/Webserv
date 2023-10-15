# include "SockInfo.hpp"

/* constructor*/
SockInfo::SockInfo(int fd, std::string ip, int clientport, int serverPort, SockMode sockMode): _modeInfo(ModeInfo(sockMode)) {
	this->_sockFd = fd;
	this->_clientport = clientport;
	this->_serverPort = serverPort;
	this->_ip = ip;
	this->_cgiInfo = NULL;
}

SockInfo::SockInfo(int fd, int serverPort, SockMode sockMode): _modeInfo(ModeInfo(sockMode))
{
	this->_sockFd = fd;
	this->_clientport = 0;
	this->_serverPort = serverPort;
	this->_ip = "";
	this->_cgiInfo = NULL;
}

int	SockInfo::getSockFd() const
{
	return (this->_sockFd);
}

HttpStatus	&SockInfo::getStatus()
{
	return (this->_status);
}

ModeInfo	&SockInfo::getModeInfo()
{
	return (this->_modeInfo);
}

SockData	&SockInfo::getSockData()
{
	return (this->_sockData);
}

HttpRequest	&SockInfo::getRequest()
{
	return (this->_request);
}

int	SockInfo::getClientPort()
{
	return (this->_clientport);
}

int	SockInfo::getServerPort()
{
	return (this->_serverPort);
}

std::string	SockInfo::getClientIp()
{
	return (this->_ip);
}

HttpResponse	&SockInfo::getResponse()
{
	return (this->_response);
}

CgiInfo	*SockInfo::getCgiInfo()
{
	return (this->_cgiInfo);
}

// setter
void	SockInfo::setResponse(HttpResponse response)
{
	this->_response = response;
}

void	SockInfo::setCgiInfo(CgiInfo *cgiInfo)
{
	this->_cgiInfo = cgiInfo;
}

void	SockInfo::reset()
{
	this->_modeInfo.initialization();
	this->_status.setHttpStatus(0);
} 