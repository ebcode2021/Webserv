# include "event.hpp"
# include "CgiMetadata.hpp"
# include "LimitExcept.hpp"

std::string	createGenericBody(std::string path)
{
	std::ifstream		file(path);
	std::stringstream	body;

	//std::cout << "렌더링 할 페이지 경로 : " <<  path << std::endl;
	if (!isAccess(path))
		throw 403;

	// 은비
	//std::vector<std::string>
	// 만약 index 
	//std::vector<std::string> indexList = locationBlock.getIndexList();
	//if (indexList.size() > 0)
	//{

	//}


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
		throw 403;
	for (size_t i = 1; i < indexList.size(); i++)
	{
		std::string path = createPath(indexList[i], pathInfo.getPath());
		PathInfo newPathInfo(path);
		if (newPathInfo.getPathType() == P_FILE)
		{
			pathInfo = newPathInfo;
			return createGenericBody(path);
		}
	}
	if (pathInfo.getAutoIndex()) {
		pathInfo.setFileType(HTML);
		return createAutoIndexBody(pathInfo.getPath());
	}
	throw 403;
}

void	processCgi(SockInfo *sockInfo, PathInfo &pathInfo, LocationBlock &location, KqHandler &kq)
{
	(void)location;
	(void)kq;
	CgiMetadata data(sockInfo->getRequest(), pathInfo);
	if (!pathInfo.getAccess())
		throw 403;
	int pipefd[2];
	pipe(pipefd);
	pid_t pid = fork();
	if (pid == 0) {
		dup2(pipefd[0], STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		std::string path = pathInfo.getPath();

		char *argv[] = {strdup(CGI_PATH.c_str()), strdup(path.c_str()), NULL};
		execve(argv[0], argv, data.createEnvp());
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

bool isCgi(std::string cgiPath)
{
	if (cgiPath.size() != 0)
		return (true);
	return (false);
}

static HttpResponse	processGetRequest(SockInfo *sockInfo, LocationBlock &locationBlock, KqHandler &kq)
{
	HttpResponse	response;
	HttpRequestLine	requestLine = sockInfo->getRequest().getHttpRequestLine();
	PathInfo 		pathInfo(requestLine.getRequestURI(), locationBlock);
	std::string		body;
	
	// 은비 추가 코드
	if (locationBlock.getLimitExcept().isValidMethod(requestLine.getMethod()) == false)
		throw 403;
	if (isCgi(locationBlock.getCgiPass()))
	{
		processCgi(sockInfo, pathInfo, locationBlock, kq);
		return HttpResponse();
	}
	switch (pathInfo.getPathType())
	{
		// 은비.
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
	response.createResponse(sockInfo->getStatus(), pathInfo, body);
	return (response);
}

void	processPostRequest(SockInfo *sockInfo, LocationBlock &location, KqHandler &kq)
{
	PathInfo 	pathInfo(sockInfo->getRequest().getHttpRequestLine().getRequestURI(), location);

	if (!isCgi(location.getCgiPass()))
		throw 403;
	if (sockInfo->getRequest().getHttpBody().getBodySize() > location.getClientMaxBodySize())
		throw 413;
	if (pathInfo.getPathType() == P_NONE)
	{
		std::cout << "여기들어오니?" << std::endl;
		throw 404;
	}
	processCgi(sockInfo, pathInfo, location, kq);
}

std::string	deletesuccessBody()
{
	std::stringstream body;

	body << "<html>";
	body << "<head><meta charset=\"UTF-8\"><title>CGI Example</title></head>";
	body << "<body>";
	body << "<h1>파일 삭제 완료</h1>";
    body << "</body>";
	body << "</html>";

	return (body.str());
}

HttpResponse	processDeleteRequest(SockInfo *sockInfo, LocationBlock &location, KqHandler &kq)
{
	PathInfo		pathInfo(sockInfo->getRequest().getHttpRequestLine().getRequestURI(), location);
	HttpResponse	response;

	(void)kq;
	if (pathInfo.getPathType() == P_NONE)
		throw 404;
	if (!pathInfo.getAccess())
		throw 403; 
	int ret = remove(pathInfo.getPath().c_str());
	if (!ret) {
		sockInfo->getStatus().setHttpStatus(204);
		std::string body = deletesuccessBody();
		response.createResponse(sockInfo->getStatus(), pathInfo, body);
	}
	else
		throw 500;
	return (response);
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
				processPostRequest(sockInfo, curLocation, kq);
				break;
			case DELETE:
				response = processDeleteRequest(sockInfo, curLocation, kq);
				break;
			case OTHER:
				throw 405;
		}
	}
	catch(int code)
	{
		std::cout << code << std::endl;
		if (code == 301) {
			response.createRedirect(curLocation.getReturn());
		}
		sockInfo->getStatus().setHttpStatus(code);
		response.createErrorPage(sockInfo->getStatus(), curLocation);
		kq.changeEvent(sockInfo->getSockFd(), EVFILT_WRITE, EV_ADD, 0, 0, sockInfo);
	}
	sockInfo->setResponse(response);
	return (true);
}