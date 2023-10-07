#include "HttpSession.hpp"

/* constructor */
HttpSession::HttpSession()
{
	this->_sessionId = createSessionId();
	this->_expiration = createExpirationTime();
	this->_data = "";
}

HttpSession::HttpSession(const std::string& previousURL)
{
	this->_sessionId = createSessionId();
	this->_expiration = createExpirationTime();
	this->_previousURL = previousURL;
	
}

/* getter, setter */
std::string	HttpSession::getSessionId() const {
	return (this->_sessionId);
}

std::string	HttpSession::getPreviousURL() const {
	return (this->_previousURL);
}

time_t		HttpSession::getExpiration() const {
	return (this->_expiration);
}

std::string	HttpSession::getData() const {
	return (this->_data);
}

void		HttpSession::setData(const std::string& data) {
	this->_data = data;
}

void		HttpSession::setPreviousURL(const std::string& url) {
	this->_previousURL = url;
}

/* method */
bool		HttpSession::isCacheDirectory()
{
	struct stat st;

	return(stat(CACHE_ROOT.c_str(), &st) == 0 && S_ISDIR(st.st_mode));
}


void		HttpSession::createSessionFile()
{
	std::string	fileName = CACHE_ROOT + this->_sessionId;

	std::ofstream	file(fileName.c_str());

	if (file)
	{
		file << this->_data;
		file.close();
	}
}

std::string HttpSession::createSessionId()
{
	std::stringstream	sessionIdStream;
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	for (size_t i = 0; i < SESSION_ID_LENGTH; i++)
		sessionIdStream << SESSION_CHARS[std::rand() % SESSION_CHARS_LENGTH];

	return (sessionIdStream.str());
}

time_t	HttpSession::createExpirationTime()
{
	time_t		currentTime = std::time(nullptr);
	time_t		expirationTime = currentTime + DEFAULT_SESSION_DURATION;

	return (expirationTime);
}

void	HttpSession::printInfo()
{
	std::cout << "----[session]----" << std::endl;
	std::cout << "sessionId : " << this->_sessionId << std::endl;
	std::cout << "previousURL : " << this->_previousURL << std::endl;
}