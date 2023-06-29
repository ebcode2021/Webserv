#include "CgiInfo.hpp"

CgiInfo::CgiInfo(int pid, int readFd, int writeFd) {
	this->_pid = pid;
	this->_readFd = readFd;
	this->_writeFd = writeFd;
}

int	CgiInfo::getReadFd() {
	return (this->_readFd);
}

int CgiInfo::getWriteFd() {
	return (this->_writeFd);
}

int CgiInfo::getPid() {
	return (this->_pid);
}

void CgiInfo::SetPid(int pid) {
	this->_pid = pid;
}

void CgiInfo::SetWriteFd(int writeFd) {
	this->_writeFd = writeFd;
}

void CgiInfo::SetReadFd(int readFd) {
	this->_readFd = readFd;
}

