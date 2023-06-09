# include "SessionStorage.hpp"

// constructor
SessionStorage::SessionStorage(){}

// method
void		SessionStorage::addSession(HttpSession& session)
{
	this->_sessionList.insert(std::make_pair(session.getSessionId(), session));
}

HttpSession SessionStorage::generateSession(const std::string& data)
{
	return (HttpSession(data));
}

bool		SessionStorage::isSession(const std::string& id)
{
	if (this->_sessionList.find(id) != this->_sessionList.end())
		return (true);
	return (false);
}
HttpSession	SessionStorage::getSession(std::string& id)
{
	return (this->_sessionList[id]);
}

// void		SessionStorage::createCacheDirectory()
// {
// 	struct stat	st;
// 	std::string	folder = CACHE_ROOT;

// 	try
// 	{
// 		// delete cache directory
// 		if (stat(folder.c_str(), &st) == 0)
// 		{
// 			if (S_ISDIR(st.st_mode))
// 			{
// 				if (remove(folder.c_str()) != 0)
// 					system(("rm -rf " + folder).c_str());
// 			}
// 		}
// 		else
// 			throw std::runtime_error("Already Exist Cache Folder");
		
// 		// create cache directory
// 		if (mkdir(folder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0)
// 			throw std::runtime_error("Failed to create cache folder");
// 	}
// 	catch (const std::exception &e)
// 	{
// 		std::cerr << "Exception occurs : " << e.what() << std::endl;
// 	}
// }

void	SessionStorage::validateSession(const std::string& id, const std::string& url)
{
	std::map<std::string, HttpSession>::const_iterator	it =  this->_sessionList.find(id);

	if (url == "/favicon.ico")
		return ;
	//std::cout << this->_sessionList.size() << std::endl;
	
	if (it != this->_sessionList.end())
	{
		if ((*it).second.getExpiration() > std::time(nullptr) && (*it).second.getPreviousURL() == url)
			throw SessionException(304);
		else
			deleteSession(id);
	}
}

void	SessionStorage::deleteSession(const std::string& id)
{
	std::map<std::string, HttpSession>::const_iterator it = this->_sessionList.find(id);
	
	if (it != this->_sessionList.end())
		this->_sessionList.erase(it);
}


bool			SessionStorage::isEqulSessionAndURL(const std::string& sessionId, const std::string& url)
{
	std::map<std::string, HttpSession>::const_iterator	it =  this->_sessionList.find(sessionId);

	if (it != this->_sessionList.end())
	{
		if ((*it).second.getPreviousURL() == url && (*it).first == sessionId)
			return (true);
	}
	return (false);
}

// print
void	SessionStorage::printInfo()
{
	std::map<std::string, HttpSession>::const_iterator	it;

	std::cout << "---- [SessionStorage] ----" << std::endl;
	std::cout << "	- sessionList" << std::endl;
	for (it = this->_sessionList.begin(); it != this->_sessionList.end(); it++)
	{
		std::cout << "		sessionId : " << (*it).second.getSessionId() << std::endl;
		std::cout << "		expiration : " << (*it).second.getExpiration() << std::endl;
		//std::cout << "		data : " << (*it).second.getData() << std::endl;
		std::cout << "-----------------------------------------" << std::endl;
	}
}