#include "webserv.hpp"
#include "Config.hpp"
#include "KqueueHandler.hpp"
#include "SocketEventHandler.hpp"
#include "HttpResponse.hpp"
#include "SessionStorage.hpp"
#include "CgiMetadata.hpp"
#include "utils.hpp"


#include "server.hpp"


/*
	https일경우 리퀘스트 요청이 암호화되서 전송되기때문에 header파싱 부분에서 segfault에러
	send데이터가 큰경우 처리
	send udata확인해서 cgi에 데이터보내기
	포트 적용잘안되는거 확인
	썬더브라우저에서 connection 요청 보냈을경우
	content type 파싱 다시
*/



void initListenSocket(KqueueHandler &kqHandler, Config &config, std::set<int> &listenSockFdList) 
{
	SocketEventHandler		sockEventHandler;
	std::set<int>			listenSockList = config.getListenSockList(); 
	std::set<int>::iterator	it;

	for (it = listenSockList.begin(); it != listenSockList.end(); it++)
	{
		int listenSockFd = createSocket();
		if (listenSockFd == INVALID_SOCKET) {
			printErrorWithExit(strerror(errno));
		}
		TcpSocket *listenSock = new TcpSocket(listenSockFd);
		sockEventHandler.setSocket(listenSock);

		if (sockEventHandler.sockBind(*it) < 0)
			printErrorWithExit(strerror(errno));
		
		if (sockEventHandler.sockListen())
			printErrorWithExit(strerror(errno));
		
		listenSock->changeToNonblocking();
		kqHandler.changeEvent(listenSockFd, EVFILT_READ, EV_ADD, 0, 0, listenSock);
		listenSockFdList.insert(listenSockFd);
	}
}

bool	isListenSocketEvent(std::set<int>&	list, uintptr_t& event)
{
	return (list.find(event) != list.end());
}

bool	isReadEvent(int16_t& event)
{
	return (event == EVFILT_READ);
}

bool	isWriteEvent(int16_t& event)
{
	return (event == EVFILT_WRITE);
}

bool	isProcEvent(int16_t& event)
{
	return (event == EVFILT_PROC);
}

void	changeOpt(int fd, int option) {
	int flags = fcntl(fd, F_GETFL, 0);
	flags |= option;
	fcntl(fd, F_SETFL, flags);
}

void cgi_test(TcpSocket* sock, KqueueHandler &kq) {
	std::cout << "cig_test 입장" << std::endl;
	HttpRequest request = sock->getRequest();
	CgiMetadata data(request);
	//char **envp = data.createEnvp();

	int pipefd[2];
	pipe(pipefd);
	pid_t pid = fork();

	if (pid == 0) {
		dup2(pipefd[0], STDIN_FILENO);
		//dup2(pipefd[1], STDOUT_FILENO);
		std::string requestUrl = request.getHttpRequestLine().getRequestURI();
		std::string path = DEFAULT_ROOT + requestUrl;

		char *argv[] = {strdup(CGI_PATH.c_str()), strdup(path.c_str()), NULL};
		std::cout << "execve 직전" << std::endl;
		execve(argv[0], argv, data.createEnvp());
		std::cout << "실패하면 뜨는 경로 : path "<< std::endl;
		exit(1);
	}
	else {
		// waitpid로 병렬. 다시 끝날때까지 다시.
		changeOpt(pipefd[0], O_NONBLOCK);
		changeOpt(pipefd[1], O_NONBLOCK);
		sock->setCgiInfo(new CgiInfo(pid, pipefd[0], pipefd[1]));
		sock->setSendMode(PROCESS);
		kq.changeEvent(pipefd[1] , EVFILT_WRITE, EV_ADD, 0, 0, sock);
		kq.changeEvent(sock->getCgiInfo()->getPid(), EVFILT_PROC, EV_ADD, NOTE_EXIT, 0, sock);
	}
}

bool	isCgiRequest(LocationBlock &locationBlock)
{
	if (locationBlock.getCgiPass() == "")
		return (false);
	return (true);
}

void	processGetRequest(PathInfo &pathInfo, LocationBlock& block)
{
	
}

void	validate(TcpSocket *curSock, SessionStorage &sessionStorage, KqueueHandler &kqueue)
{
	HttpRequest 		request = curSock->getRequest();
	HttpRequestLine		requestLine = request.getHttpRequestLine();
	HttpRequestHeader	requestHeader = request.getHttpRequestHeader();
	PathInfo 			&pathInfo = curSock->getPathInfo();
	LocationBlock		locationBlock = pathInfo.getLocationBlock();
	std::string			method = requestLine.getMethod();
	
	try
	{
		requestLine.validateRequestLine(locationBlock.getLimitExcept(), curSock->getClientAddr());
		requestHeader.validateRequestHeader(locationBlock);
	
		pathInfo.validatePath();
		sessionStorage.validateSession(requestHeader.getSessionIdByCookie(), requestLine.getRequestURI());
		if (isCgiRequest(locationBlock))
			//processCgiRequest();
		if (method == "GET")
			//processGetRequest();
			pathInfo.processGetRequest(locationBlock);
		else if (method == "DELETE")
			pathInfo.processDeleteRequest();
		else if (method == "POST")
			cgi_test(curSock, kqueue);
	}
	catch(const ResponseException &ex)
	{
		curSock->getResponse().getResponseLine().setHttpStatus(ex.getHttpStatus());
		pathInfo.setReturnPageByError(locationBlock.getErrorPage(), ex.getHttpStatus().getStatusCode());
	}
	

}

int main(int argc, char *argv[])
{
	(void)argc;
	//Config::fileCheck(argc, argv);

	Config	config(argv[1]);

	
	std::cout << "server start" << std::endl;



	std::set<int>				listenSockFdList;
	KqueueHandler				kqHandler;
	SocketEventHandler			sockEventHandler;
	SessionStorage				sessionStorage;
	
	initListenSocket(kqHandler, config, listenSockFdList);

	while(1)
	{
		kqHandler.initialize();

		for (int i = 0; i < kqHandler.getEventCnt(); i++)
		{
			struct kevent curEvent = kqHandler.getCurEventByIndex(i);
			
			TcpSocket *curSock = (TcpSocket *)curEvent.udata;
			sockEventHandler.setSocket(curSock);
			HttpRequest	request = curSock->getRequest();

			if (isReadEvent(curEvent.filter) == true)
			{
				if (isListenSocketEvent(listenSockFdList, curEvent.ident) == true)
				{
					int clientSock = sockEventHandler.sockAccept();
					if (clientSock == INVALID_SOCKET)
						continue;
					TcpSocket *clientSocket = new TcpSocket(clientSock);
					kqHandler.changeEvent(clientSock, EVFILT_READ, EV_ADD, 0, 0, clientSocket);
				}
				else
				{
					if (sockEventHandler.dataRecv() > 0)
					{
						if (curSock->getReadMode() == HEADER) 
						{
							if (curSock->isHttpRequest() == true)
							{
								curSock->setRequestHeader();
							}
							else
							{
								sockEventHandler.closeSocket();
							}
						}

						if (curSock->getReadMode() != END){
							curSock->setRequestBody();
						}
						if (curSock->getReadMode() == END)
						{
							ServerInfo		serverInfo = config.findServerInfoByHost(request.getHttpRequestHeader().getHost());
							PathInfo		pathInfo(serverInfo.findLocationBlockByURL(request.getHttpRequestLine().getRequestURI()));
							
							curSock->setPathInfo(pathInfo);
							validate(curSock, sessionStorage, kqHandler);
							kqHandler.changeEvent(curSock->getSockFd(), EVFILT_WRITE, EV_ADD, 0, 0, curSock);
							
							// response 만들기
							// 함수 분리 (validate)
							// curSock->pathInfo
							// response(errorStatus) + pathInfo.
							
						}
					}
					else
					{
						std::cout << "설마 여기 들어오나? "<< std::endl;
						sockEventHandler.closeSocket();
						std::cout << "흠냐" << std::endl;

					}
				}
			}
			else if (isProcEvent(curEvent.filter) == true)
			{
				std::cout << "자식 종료 감지 성공" << std::endl;
				//kqHandler.changeEvent(curSock->getSockFd(), EVFILT_WRITE, EV_ADD, 0, 0, curSock);
				kqHandler.changeEvent(curSock->getCgiInfo()->getReadFd(), EVFILT_READ, EV_ADD, 0, 0, curSock);
				
				curSock->setSendMode(WAIT);
			}
			else if (isWriteEvent(curEvent.filter) == true)
			{
				std::cout << "Write event 입장 " << std::endl;

				if (curSock->getSendMode() == WAIT)
				{
					HttpResponse response = HttpResponse::createResponse(curSock->getPathInfo(), request, curSock->getClientAddr(), sessionStorage);
					response.printHttpResponse();
					
					std::string		reqURL = request.getHttpRequestLine().getRequestURI();
					std::string		sessionId = request.getHttpRequestHeader().getSessionIdByCookie();
			
					response.getResponseHeader().handleSession(sessionStorage, reqURL, sessionId);
					
					curSock->setResponse(response);
					curSock->setBuf(curSock->getResponse().getResponseToString());
					curSock->setSendMode(CLIENT);
				}	
				int sendbyte = 0;
				if (curSock->getSendMode() == CLIENT)
					sendbyte = sockEventHandler.dataSend();
				else if (curSock->getSendMode() == PROCESS) {
					sendbyte = write(curSock->getCgiInfo()->getWriteFd(), curSock->getBufToCStr(), curSock->getBufSize());
					std::cout << sendbyte << std::endl;
					// cgi -> pipe
					// cgi -> header, body
					std::cout << "여기서 read event로 바꾸면 되지? " << std::endl;
				}
			// wait.
				if (sendbyte == -1) {
					//std::cout << "error?" << std::endl;
					sockEventHandler.closeSocket();
				}
				else if (curSock->getBufSize() > static_cast<size_t>(sendbyte)) {
					//std::cout << curSock->getBuf() << std::endl;
					curSock->bufTrim(sendbyte);
				}
				else {
					if (curSock->getSendMode() == CLIENT) {
						if (curSock->getRequest().getHttpRequestHeader().getConnection() != KEEPALIVE)
							sockEventHandler.closeSocket();
						else {
							curSock->resetInfo();
							kqHandler.changeEvent(curSock->getSockFd(), EVFILT_WRITE, EV_DELETE, 0, 0, curSock);
						}
					}
					else if (curSock->getSendMode() == PROCESS) {
						close(curSock->getCgiInfo()->getWriteFd());
					}

				}
			}
		}
	}
	return (0);
}
