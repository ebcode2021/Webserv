# include "SessionStorage.hpp"

// constructor
SessionStorage::SessionStorage(){
	this->createCacheDirectory();
}

// method
void		SessionStorage::addSession(HttpSession& session)
{
	this->_sessionList.insert(std::make_pair(session.getSessionId(), session));
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

 void		SessionStorage::createCacheDirectory()
 {
 	std::string	folder = CACHE_ROOT;

 	try
 	{
 		if (mkdir(folder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0)
 			throw std::runtime_error("Check Cache Folder. Already Exist or Permission");
 	}
 	catch (const std::exception &e)
 	{
 		std::cerr << "Exception occurs : " << e.what() << std::endl;
 	}
}

static std::string	extractSessionId(const std::string& cookies)
{
	std::vector<std::string> splittedCookies = split(cookies, ";");
		for (size_t i = 0; i < splittedCookies.size(); ++i) {
			size_t pos = splittedCookies[i].find("sessionId=");
			if (pos != std::string::npos) {
				return splittedCookies[i].substr(pos + 10);
			}
		}
		return "";
}

bool	SessionStorage::validateSession(const std::string& cookies, const std::string& url)
{
	const std::string sessionId = extractSessionId(cookies);
	std::map<std::string, HttpSession>::const_iterator	it =  this->_sessionList.find(sessionId);

	//if (url == "/favicon.ico")
	//	return true;
	if (it != this->_sessionList.end()) 
	{
		if ((*it).second.getExpiration() > std::time(nullptr) && (*it).second.getPreviousURL() == url)
			return true;
		else
			deleteSession(sessionId);
	}
	return false;
}

void	SessionStorage::deleteSession(const std::string& id)
{
	std::map<std::string, HttpSession>::const_iterator it = this->_sessionList.find(id);
	
	if (it != this->_sessionList.end())
		this->_sessionList.erase(it);
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
		std::cout << "-----------------------------------------" << std::endl;
	}
} 		
