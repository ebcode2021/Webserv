# include "event.hpp"
# include "CgiMetadata.hpp"

std::string	createGenericBody(std::string path)
{
	std::ifstream		file(path);
	std::stringstream	body;

	if (!isAccess(path))
		throw 304;
	if (file.is_open())
	{
		body << file.rdbuf();
		file.close();
	}

	return (std::string(body.str()));
}


std::string	dirType(PathInfo &pathInfo, LocationBlock &location)
{
	std::vector<std::string> indexList = location.getIndexList();

	if (!pathInfo.getAccess())
		throw 304;
	for (size_t i = 0; i < indexList.size(); i++)
	{
		std::string path = createPath(indexList[i], pathInfo.getPath());
		PathInfo newPathInfo(path);
		if (newPathInfo.getPathType() == P_FILE)
		{
			pathInfo = newPathInfo;
			return createGenericBody(path);
		}
	}
	if (pathInfo.getAutoIndex())
		return createAutoIndexBody(pathInfo.getPath());
	throw 403;
}

void	processCgi(SockInfo *sockInfo, PathInfo &pathInfo, LocationBlock &location, KqHandler &kq)
{
	(void)location;
	(void)kq;
	CgiMetadata data(sockInfo->getRequest(), pathInfo);

	int pipefd[2];
	pipe(pipefd);
	pid_t pid = fork();
	if (pid == 0) {
		dup2(pipefd[0], STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		std::string path = pathInfo.getPath();

		char *argv[] = {strdup(CGI_PATH.c_str()), strdup(path.c_str()), NULL};
		execve(argv[0], argv, data.createEnvp());
		std::cout << "실패하면 뜨는 경로 : path "<< std::endl;
		exit(1);
	}
	else {
		//waitpid로 병렬. 다시 끝날때까지 다시.
		changeFdOpt(pipefd[0], O_NONBLOCK);
		changeFdOpt(pipefd[1], O_NONBLOCK);
		sockInfo->setCgiInfo(new CgiInfo(pid, pipefd[0], pipefd[1]));
		sockInfo->getModeInfo().setSendMode(S_PROCESS);
		sockInfo->getModeInfo().setSockMode(M_CGI);
		kq.changeEvent(pipefd[1] , EVFILT_WRITE, EV_ADD, 0, 0, sockInfo);
		kq.changeEvent(pid, EVFILT_PROC, EV_ADD, NOTE_EXIT, 0, sockInfo);
	}
}


static HttpResponse	processGetRequest(SockInfo *sockInfo, LocationBlock &locationBlock, KqHandler &kq)
{
	HttpResponse	respons;
	std::string		body;
	PathInfo 		pathInfo(sockInfo->getRequest().getHttpRequestLine().getRequestURI(), locationBlock);

	// limit except확인 걸리면 403
	// if (checkBlocked(sockInfo->getClientIp(), locationBlock.getLimitExcept())) {
	// 	throw 403 
	// } 

	if (pathInfo.getFileType() == "cgi")
	{
		processCgi(sockInfo, pathInfo, locationBlock, kq);
		return HttpResponse();
	}
	switch (pathInfo.getPathType())
	{
		case P_FILE:
			body = createGenericBody(pathInfo.getPath());
			break;
		case P_DIR:
			body = dirType(pathInfo, locationBlock);
			break;
		case P_NONE:
			throw 404;
	}
	sockInfo->getStatus().setHttpStatus(200);
	kq.changeEvent(sockInfo->getSockFd(), EVFILT_WRITE, EV_ADD, 0, 0, sockInfo);
	respons.createResponse(sockInfo->getStatus(), pathInfo, body);
	return (respons);
}

int	processRequest(SockInfo *sockInfo, ServerInfoList serverInfoList, KqHandler &kq)
{
	HttpRequestLine		requestLine = sockInfo->getRequest().getHttpRequestLine() ;
	HttpRequestHeader	requestHeader = sockInfo->getRequest().getHttpRequestHeader();
	ServerInfo			curServerInfo = serverInfoList.getServerInfoByPortAndHost(sockInfo->getServerPort(), requestHeader.getHeaderByKey("Host"));
	LocationBlock		curLocation = curServerInfo.getLocationBlockByURL(requestLine.getRequestURI());
	HttpResponse		response;
	
	try
	{
		if (isReturn(curLocation))
			throw 301;
		if (sockInfo->getStatus().getStatusCode() != 0)
			throw sockInfo->getStatus().getStatusCode();
		MethodType type = findMethodType(requestLine.getMethod());
		switch (type)
		{
			case GET:
				response = processGetRequest(sockInfo, curLocation, kq);
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
		if (code == 301) {
			response.createRedirectMessage(curLocation.getReturn());
		}
		sockInfo->getStatus().setHttpStatus(code);
		response.createErrorPage(sockInfo->getStatus(), curLocation);
		kq.changeEvent(sockInfo->getSockFd(), EVFILT_WRITE, EV_ADD, 0, 0, sockInfo);
	}
	sockInfo->setResponse(response);
	return (true);
}