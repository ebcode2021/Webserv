#include "HttpResponseHeader.hpp"
#include "PathInfo.hpp"

/* constructor */
HttpResponseHeader::HttpResponseHeader()
{
	this->_contentLength = 0;
}

/* getter */
std::string		HttpResponseHeader::getDate() const {
	return (this->_date);
}

std::string		HttpResponseHeader::getServer() const {
	return (this->_server);
}

std::string		HttpResponseHeader::getContentType()const {
	 return( this->_contentType);
}

size_t			HttpResponseHeader::getContentLength() const {
	return (this->_contentLength);
}

std::string	HttpResponseHeader::getLocation() const {
	return (this->_loaction);
}

// std::vector<std::string>	HttpResponseHeader::getSetCookie() const {
// 	return(this->_setCookie);
// }

/* setter */

// void			HttpResponseHeader::setSetCookie(const std::string& cookie) {
// 	this->_setCookie.push_back(cookie);
// }

void			HttpResponseHeader::setDate(const std::string& date) {
	this->_date = date;
}

void			HttpResponseHeader::setServer(const std::string& server) {
	this->_server = server;
}

void			HttpResponseHeader::setContentType(const std::string& contentType) {
	this->_contentType = contentType;
}

void			HttpResponseHeader::setContentLength(const size_t contentLength) {
	this->_contentLength = contentLength;
}

void	HttpResponseHeader::setLocation(const std::string &path)
{
	this->_loaction = path;
}


std::string Date()
{
	std::time_t currentTime;
    std::time(&currentTime); // 현재 시간을 얻어옴
	std::string timeString = std::ctime(&currentTime);
	timeString.resize(timeString.length() - 1);
	return (timeString);
}

void	HttpResponseHeader::setHeader(HttpBody &body)
{
	this->_date = Date();
	this->_server = SERVER_NAME;
	this->_contentType = HTML;
	this->_contentLength = body.getBodySize(); 
}

void	HttpResponseHeader::setHeader(PathInfo &pathInfo, HttpBody &body)
{
	this->_date = Date();
	this->_server = SERVER_NAME;
	this->_contentType = pathInfo.getFileType();
	this->_contentLength = body.getBodySize();
}


// /* method */
// std::string		HttpResponseHeader::getCookieString()
// {
// 	std::string	cookieHeader;
// 	std::vector<std::string>		cookies = getSetCookie();
// 	std::vector<std::string>::const_iterator	it;

// 	for (it = cookies.begin(); it != cookies.end(); ++it)
// 	{
// 		if (cookieHeader.empty() == false)
// 			cookieHeader += "; ";
// 		cookieHeader += *it;
// 	}
// 	return (cookieHeader);
// }

// void		HttpResponseHeader::printCookie()
// {
// 	std::cout << "cookie는 잘 들어갔는가?" << std::endl;
// 	for (size_t i = 0; i < this->_setCookie.size(); i++)
// 		std::cout << "cookie : " << this->_setCookie[i] << std::endl;
// }

std::string		HttpResponseHeader::getResponseHeaderToString()
{
	std::string	responseHeader;
	//std::string	cookieHeader = getCookieString();

	responseHeader += ("Server:" + SP + this->_server + CRLF);
	responseHeader += ("Date:" + SP + this->_date + CRLF);
	//responseHeader += "Content-Type: text/html; charset=utf-8" + CRLF;
	responseHeader += ("Content-Type:" + SP + this->_contentType + CRLF);
	if (this->_contentLength > 0)
		responseHeader += ("Content-Length:" + SP + itos(this->_contentLength) + CRLF);
	if (this->_loaction.length() > 0)
		responseHeader += ("Location:" + SP + this->_loaction + CRLF);
	// if (cookieHeader.empty() == false)
	// 	responseHeader += ("Set-Cookie:" + SP + cookieHeader + CRLF);
	// responseHeader += ("Cache-Control: max-age=3600" + CRLF);
	responseHeader += CRLF;

	return (responseHeader);
}

// void	HttpResponseHeader::handleSession(SessionStorage& sessionStorage, std::string& reqURL, const std::string& sessionId)
// {
// 	if (reqURL != FAVICON_URL)
// 	{
// 		if (sessionStorage.isSession(sessionId) == true)
// 			setSetCookie("sessionId=" + sessionId);
// 		else
// 		{
// 			HttpSession	session(reqURL);
// 			sessionStorage.addSession(session);
// 			setSetCookie("sessionId=" + session.getSessionId());
// 		}
// 	}
// }