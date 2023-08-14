# include "event.hpp"

PathType	determinePathType(std::string path)
{
	struct stat pathStat;
	std::cout << path << std::endl;
	if (stat(path.c_str(), &pathStat) == 0)
	{
		if (S_ISREG(pathStat.st_mode))
			return P_FILE;
		else if (S_ISDIR(pathStat.st_mode))
			return P_DIR;
	}
	return P_NONE;
}

bool	isAccess(std::string&	path)
{
	if (access(path.c_str(), R_OK | W_OK) == 0)
		return (true);
	return (false);
}

std::string createPath(HttpRequestLine line, std::string root)
{
	return (root + line.getRequestURI());
}


std::string	createGenericBody(const std::string& path)
{
	std::ifstream		file(path);
	std::stringstream	body;

	if (file.is_open())
	{
		body << file.rdbuf();
		file.close();
	}

	return (std::string(body.str()));
}

static HttpBody	processGetRequest(SockInfo *sockInfo, LocationBlock &locationBlock)
{
	// limit except확인 걸리면 403
	// if (checkBlocked(sockInfo->getClientIp(), locationBlock.getLimitExcept())) {
	// 	sockInfo->setErrorCode(); 
	// }
	HttpBody responsBody;
	std::string path = createPath(sockInfo->getRequest().getHttpRequestLine(), locationBlock.getRoot());
	PathType pathType = determinePathType(path);
	
	switch (pathType)
	{
		case P_FILE:
			if (!isAccess(path))
				throw 403;
			return (HttpBody(createGenericBody(path)));
			break;
		case P_DIR:
			
			break;
		case P_NONE:
			throw 404;
	}
	return (responsBody);
}

int	processRequest(SockInfo *sockInfo, ServerInfoList serverInfoList, KqHandler &kq)
{
	(void)kq;
	//request info
	HttpRequestLine		requestLine = sockInfo->getRequest().getHttpRequestLine() ;
	HttpRequestHeader	requestHeader = sockInfo->getRequest().getHttpRequestHeader();
	ServerInfo			curServerInfo = serverInfoList.getServerInfoByPortAndHost(sockInfo->getServerPort(), requestHeader.getHeaderByKey("Host"));
	LocationBlock		curLocation = curServerInfo.getLocationBlockByURL(requestLine.getRequestURI());

	if (sockInfo->getStatus().getStatusCode() != 0) {
		return (false);
	}
	// location 블록에 return 지시어가 있으면 redirect
	try
	{
		MethodType type = findMethodType(requestLine.getMethod());
		HttpBody	responseBody;
		std::cout << type << std::endl;
		switch (type)
		{
			case GET:
				responseBody = processGetRequest(sockInfo, curLocation);
				kq.changeEvent(sockInfo->getSockFd(), EVFILT_WRITE, EV_ADD, 0, 0, sockInfo);
				break;
			case POST:
				break;
			case DELETE:
				break;
			case OTHER:
				throw 405;
		}
	}
	catch(int code)
	{
		std::cout << code << std::endl;
		sockInfo->getStatus().setHttpStatus(code);
	}
	
	
	return (true);
}