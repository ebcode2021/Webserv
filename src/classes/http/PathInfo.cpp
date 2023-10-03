#include "PathInfo.hpp"
#include "LocationBlock.hpp"
#include "utils.hpp"

/* constructor */
PathInfo::PathInfo(){}

PathInfo::PathInfo(std::string url, LocationBlock& locationBlock)
{
	this->_path = createPath(url, locationBlock.getRoot());
	this->_pathType = determinePathType(this->_path);
	this->_autoIndex = locationBlock.getAutoIndex();
	this->_fileType = searchFileType(this->_path);
	this->_access = isAccess(this->_path);
}

PathInfo::PathInfo(std::string path)
{
	this->_path = path;
	this->_pathType = determinePathType(path);
	this->_autoIndex = false;
	this->_fileType = searchFileType(path);
	this->_access = isAccess(path);
}

/* getter, setter */
std::string	PathInfo::getPath() const {
	return(this->_path);
}

PathType	PathInfo::getPathType() const {
	return(this->_pathType);
}

std::string	PathInfo::getFileType() const {
	return(this->_fileType);
}

bool		PathInfo::getAccess() const {
	return(this->_access);
}

bool		PathInfo::getAutoIndex() const {
	return (this->_autoIndex);
}


void		PathInfo::setAutoIndex(bool value) {
	this->_autoIndex = value;
}

void	PathInfo::setFileType(std::string type) {
	this->_fileType = type;
}

/* print */
void	PathInfo::print()
{
	
	std::cout << "\n---- [PathInfo] ----" << std::endl;
	std::cout << "- path : " << this->_path << std::endl;
	std::cout << "- pathType : ";
	switch (_pathType)
	{
		case P_FILE:
			std::cout << "file\n";
			break;
		case P_DIR:
			std::cout << "directory\n";
			break;
		case P_NONE:
			std::cout << "NONE\n";
			break;
	}
	std::cout << "- fileType : " << this->_fileType << std::endl;
	std::cout << "- access : ";
	if (this->_access)
		std::cout << "allow\n";
	else 
		std::cout << "deny\n";
	std::cout << "- autoIndex : ";
	if (this->_autoIndex)
		std::cout << "on\n";
	else
		std::cout << "off\n";
	std::cout << "--------------------\n" << std::endl;
}
