#include "PathInfo.hpp"
#include "LocationBlock.hpp"

/* constructor */
PathInfo::PathInfo(){}

PathInfo::PathInfo(const std::string &path)
{
	this->_path = path;
	this->_pathType = determinePathType();
	this->_fileType = determineFileType();
	this->_access = isAccess();
	this->_autoIndex = false;
	this->_returnPage = "";
}

/* getter, setter */
PathType	PathInfo::getPathType() const {
	return(this->_pathType);
}

std::string	PathInfo::getFileType() const {
	return(this->_fileType);
}

std::string	PathInfo::getPath() const {
	return(this->_path);
}

bool		PathInfo::getAccess() const {
	return(this->_access);
}

bool		PathInfo::getAutoIndex() const {
	return (this->_autoIndex);
}

std::string	PathInfo::getReturnPage() const {
	return (this->_returnPage);
}

void		PathInfo::setAutoIndex(bool value) {
	this->_autoIndex = value;
}

void	PathInfo::setReturnPage(const std::string& path) {
	this->_returnPage = path;
}

/* method */
PathType	PathInfo::determinePathType()
{
	struct stat pathStat;

	if (stat(this->_path.c_str(), &pathStat) == 0)
	{
		if (S_ISREG(pathStat.st_mode))
			return P_FILE;
		else if (S_ISDIR(pathStat.st_mode))
			return P_DIRECTORY;
	}
	return P_NONE;
}

std::map<std::string, std::string> createTypeTable()
{
	std::map<std::string, std::string>	typeTable;
	std::vector<std::string> 			splittedLine;

	std::ifstream						file(FILE_TYPE_PATH);
	std::string							line;

	while (std::getline(file, line, ';'))
	{
		splittedLine = split(line, WHITESPACE);
		if (splittedLine.size() > 0)
		{
			for (size_t i = 1; i < splittedLine.size(); i++)
				typeTable.insert(make_pair(splittedLine[i], splittedLine[0]));
		}
	}
	return (typeTable);
}

std::string getFileExtension(const std::string &path)
{
	size_t dotIndex = path.find_last_of(".");

	if (dotIndex != std::string::npos && dotIndex < path.length() - 1)
		return path.substr(dotIndex + 1);

	return "";
}

std::string searchFileType(const std::string &path)
{
	static std::map<std::string, std::string> typeTable = createTypeTable();
	std::string fileExtension = getFileExtension(path);
	std::map<std::string, std::string>::iterator iter = typeTable.find(fileExtension);
	std::cout << iter->second << std::endl;
	if (iter == typeTable.end())
		return (DEFAULT_FILE_TYPE);
	else
		return (iter->second);
	
}

std::string	PathInfo::determineFileType()
{
	if (this->_pathType != P_FILE)
		return "";
	return (searchFileType(this->_path));
}

bool		PathInfo::isAccess()
{
	if (access(this->_path.c_str(), R_OK | W_OK) == 0)
		return (true);
	return (false);
}

bool		PathInfo::isFile(std::string& path)
{
	struct stat fileStat;

	return (stat(path.c_str(), &fileStat) == 0);
}

/* method */
bool	PathInfo::isValidDirectory()
{
	return (this->_pathType == P_DIRECTORY && this->_access == true);
}

/////////////
void	PathInfo::printPathInfo()
{
	std::cout << "\n---- [PathInfo] ----" << std::endl;
	std::cout << "- path : " << this->_path << std::endl;
	std::cout << "- pathType : " << this->_pathType << std::endl;
	std::cout << "- fileType : " << this->_fileType << std::endl;
	std::cout << "- access : " << this->_access << std::endl;
	std::cout << "- autoIndex : " << this->_autoIndex << std::endl;
	std::cout << "- returnPage : " << this->_returnPage << std::endl;
	std::cout << "--------------------\n" << std::endl;
}

/////


bool	PathInfo::isAccess(std::string&	path)
{
	if (access(path.c_str(), R_OK | W_OK) == 0)
		return (true);
	return (false);
}

void	PathInfo::processGetRequest(LocationBlock& block)
{
	std::cout << "[validatePathInfo] 입장!" << std::endl;

	block.printInfo();
	try
	{
		if (this->_pathType == P_NONE)
			throw ResponseException(404);
		if (this->_access == false)
			throw ResponseException(403);

		if (this->_pathType == P_FILE)
			this->_returnPage = this->_path;
		else
		{
			std::vector<std::string>	indexList = block.getIndexList();
			size_t						indexListSize = indexList.size();
			std::string					addIndexPath;

			if (indexListSize > 1)
			{
				for (size_t i = 1; i < indexListSize; i++)
				{
					addIndexPath = this->_path + indexList[i];
					if (this->isFile(addIndexPath) == true)
					{
						if (this->isAccess(addIndexPath) == false)
							throw ResponseException(403);
						this->_returnPage = addIndexPath;
						return ;
					}
				}
				if (block.getAutoIndex() == true)
				{
					this->_returnPage = this->_path;
					this->setAutoIndex(true);
				}
				else
					throw ResponseException(403);
			}
			else
			{
				addIndexPath = this->_path + indexList[0];
				if (this->isAccess(addIndexPath) == false)
					throw ResponseException(403);
				this->_returnPage = addIndexPath;
			}
		}
	}
	catch (const ResponseException &ex)
	{
		throw ResponseException(ex.statusCode());
	}
		this->printPathInfo();
}

void	PathInfo::processDeleteRequest()
{
	std::string		path = this->_returnPage;

	// if (this->_access == false)
	// 	throw ResponseException(500);
	if (this->_pathType == P_FILE)
		std::remove(path.c_str());
	else // 경로인 경우
	{
		DIR* dir = opendir(path.c_str());

		if (dir)
		{
			dirent*	entry;

			while ((entry = readdir(dir)) != NULL)
			{
				if (entry->d_type == DT_REG)
				{
					std::string	filePath = path + "/" + entry->d_name;
					if (remove(filePath.c_str()) != 0)
						throw ResponseException(500);
				}
			}
			closedir(dir);
		}
	}
}

void			PathInfo::setReturnPageByError(const std::vector<ErrorPage>& errorPageList, const int statusCode)
{
	size_t	errorPageListSize	= errorPageList.size();

	for (size_t i = 0; i < errorPageListSize; i++)
	{
		std::string			errorPagepath = this->_path + errorPageList[i].getPath();
		std::vector<int>	statusCodeList = errorPageList[i].getStatusCodeList();
		size_t				statusCodeListSize = statusCodeList.size();

		for (size_t j = 0; j < statusCodeListSize; j++)
		{
			if (statusCode == statusCodeList[j] && PathInfo::isFile(errorPagepath) == true)
			{
				this->_returnPage = errorPagepath;
				break ;
			}
		}
	}
}