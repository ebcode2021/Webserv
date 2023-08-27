#include "HttpResponse.hpp"

/* constructor */
HttpResponse::HttpResponse(){}

HttpBody	&HttpResponse::getBody()
{
	return (this->_httpBody);
}

HttpResponseLine	&HttpResponse::getResponseLine()
{
	return (this->_httpResponseLine);
}

HttpResponseHeader	&HttpResponse::getResponseHeader()
{
	return (this->_httpResponseHeader);
}

// method

static	std::string	errorPageGenerator(HttpStatus &status)
{
	std::stringstream page;
	
	page << "<html>	\
	<head><title>" + status.getString() + "</title></head>	\
	<body>	\
	<center><h1>" + status.getString() + "</h1></center>	\
	<hr><center>" + SERVER_NAME + "</center>	\
	</body>	\
	</html>";
	return (page.str());
}

std::string	getFileResource(std::string path)
{
	std::ifstream file(path.c_str()); // 파일 열기
    if (!file.is_open()) {
        throw 500;
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close(); // 파일 닫기
    return content;
}

std::string getPageResource(PathInfo &pathInfo, LocationBlock &location)
{
	(void)location;
	if (!pathInfo.getAccess())
		throw 403;
	switch (pathInfo.getPathType())
	{
		case P_FILE:
			return (getFileResource(pathInfo.getPath()));
		case P_DIR:
			break;
		case P_NONE:
			throw 404;
	}
	return "minsu";
}

void	HttpResponse::createErrorPage(HttpStatus &status, LocationBlock &locationBlock)
{
	std::vector<ErrorPage>	errorPageList = locationBlock.getErrorPage();
	HttpBody				body;

	body.setBody(errorPageGenerator(status));
	try
	{
		for (size_t i = 0; i < errorPageList.size(); i++)
		{
			if (errorPageList[i].compareCode(status.getStatusCode()))
			{
				PathInfo	pathInfo(errorPageList[i].getPath(), locationBlock);
				body.setBody(getPageResource(pathInfo, locationBlock));
				break ;
			}
		}
	}
	catch(int code)
	{
		status.setHttpStatus(code);
		body.setBody(errorPageGenerator(status));
	}
	this->_httpResponseLine.setHttpStatus(status);
	this->_httpBody = body;
	this->_httpResponseHeader.setHeader(this->_httpBody);
}

void	HttpResponse::createResponse(HttpStatus &status, PathInfo &pathInfo)
{
	(void)status;
	switch (pathInfo.getPathType())
	{
		case P_FILE:
			//this->_httpBody(getFileResource(status, pathInfo));
			break;
		case P_DIR:
			break;
		case P_NONE:
			throw 404;
	}
}

void	HttpResponse::createResponse(HttpStatus &status, PathInfo &pathInfo, std::string &body)
{
	this->_httpResponseLine.setHttpStatus(status);
	this->_httpBody.setBody(body);
	this->_httpResponseHeader.setHeader(pathInfo, this->_httpBody);
}

void	HttpResponse::printHttpResponse()
{
	this->_httpResponseLine.print();
	std::cout << this->_httpResponseHeader.getResponseHeaderToString();
	this->_httpBody.print();
}


// HttpResponse::HttpResponse(HttpResponseLine& responseLine, HttpResponseHeader& responseHeader, HttpBody& responseBody)
// {
// 	this->_httpResponseLine = responseLine;
// 	this->_httpResponseHeader = responseHeader;
// 	this->_httpBody= responseBody;
// }

// /* setter */
// void	HttpResponse::setBody(const std::string& body) {
// 	this->_httpBody.setBody(body);
// }

// HttpResponseHeader&	HttpResponse::getResponseHeader() {
// 	return (this->_httpResponseHeader);
// }

// std::string			HttpResponse::getBody() const {
// 	return (this->_httpBody.getBody());
// }

// /* method */
// HttpResponse HttpResponse::createResponse(PathInfo& pathInfo, HttpRequest& request, const std::string& clientAddr, SessionStorage& sessionStorage)
// {
// 	// request
// 	HttpRequestLine		requestLine = request.getHttpRequestLine();
// 	HttpRequestHeader	requestHeader = request.getHttpRequestHeader();
// 	std::string			method = requestLine.getMethod();

// 	request.printInfo();
// 	pathInfo.printPathInfo();
// 	// response
// 	HttpResponseLine	responseLine(method);
// 	HttpResponseHeader	responseHeader;
// 	HttpBody			responseBody;

// 	LocationBlock		locationBlock = pathInfo.getLocationBlock();
// 	std::string			sessionId = requestHeader.getSessionIdByCookie();

// 	try
// 	{
		
// 	}
// 	catch(const ResponseException &ex)
// 	{
// 		std::cout << "************** error 발생!" << ex.statusCode() << std::endl;
// 		responseLine.setHttpStatus(ex.httpStatus());
// 		pathInfo.setReturnPageByError(locationBlock.getErrorPage(), ex.statusCode());
// 	}

// 	// post나 delete일때, body 넘겨줄지?
// 	if (method == "GET" && responseLine.getHttpStatus().getStatusCode() != 304)
// 		responseBody = makeResponseBody(pathInfo, responseLine.getHttpStatus());
// 	if (method == "POST")
// 		pathInfo.setPostFileType();
// 	// else if (method == "POST")
// 	// 	responseBody = makeResponseBody(pathInfo, responseLine.getHttpStatus());
// 	responseHeader = makeResponseHeader(pathInfo, responseBody.getBodySize());
// 	return (HttpResponse(responseLine, responseHeader, responseBody));
// }
// HttpResponse HttpResponse::createResponse(Config& config, HttpRequest& request, const std::string& clientAddr, SessionStorage& sessionStorage)
// {
// 	// request
// 	HttpRequestLine		requestLine = request.getHttpRequestLine();
// 	HttpRequestHeader	requestHeader = request.getHttpRequestHeader();
// 	std::string			method = requestLine.getMethod();

// 	// response
// 	HttpResponseLine	responseLine(method);
// 	HttpResponseHeader	responseHeader;
// 	HttpBody			responseBody;

// 	// 1. find server block and location block
// 	ServerInfo		serverInfo    = config.findServerInfoByHost(requestHeader.getHost());
// 	LocationBlock	locationBlock = serverInfo.findLocationBlockByURL(requestLine.getRequestURI());

// 	PathInfo 	pathInfo(locationBlock.getFullPath());
// 	std::string	sessionId = requestHeader.getSessionIdByCookie();

// 	try
// 	{
// 		requestLine.validateRequestLine(locationBlock.getLimitExcept(), clientAddr);
// 		requestHeader.validateRequestHeader(locationBlock);
		
// 		pathInfo.validatePath();
// 		//(void)sessionStorage;
// 		sessionStorage.validateSession(sessionId, requestLine.getRequestURI());

// 		if (method == "GET")
// 			pathInfo.processGetRequest(locationBlock);
// 		else if (method == "DELETE")
// 			pathInfo.processDeleteRequest();
// 	}
// 	catch(const ResponseException &ex)
// 	{
// 		std::cout << "************** error 발생!" << ex.statusCode() << std::endl;
// 		responseLine.setHttpStatus(ex.httpStatus());
// 		pathInfo.setReturnPageByError(locationBlock.getErrorPage(), ex.statusCode());
// 	}
// 	catch (const SessionException &ex)
// 	{
// 		std::cout << " ************* 304 발생!" << ex.statusCode() << std::endl;
// 		responseLine.setHttpStatus(ex.httpStatus());
// 	}
// 	// post나 delete일때, body 넘겨줄지?
// 	if (method == "GET" && responseLine.getHttpStatus().getStatusCode() != 304)
// 		responseBody = makeResponseBody(pathInfo, responseLine.getHttpStatus());
// 	responseHeader = makeResponseHeader(pathInfo, responseBody.getBodySize());
// 	return (HttpResponse(responseLine, responseHeader, responseBody));
// }


// void	HttpResponse::printHttpResponse()
// {
// 	HttpResponseLine line = this->_httpResponseLine;
// 	HttpResponseHeader header = this->_httpResponseHeader;
// 	HttpBody body = this->_httpBody;
// 	std::string	cookieString = header.getCookieString();

// 	std::cout << "\n---- [response 출력] ----" << std::endl;
// 	std::cout << " -- response-line" << std::endl;
// 	std::cout << "\t httpStatus : " << line.getHttpStatus().getStatusCode() << " " << line.getHttpStatus().getReason() << std::endl;
// 	std::cout << "\t version : " << line.getVersion() << std::endl;
// 	std::cout << " -- response-header" << std::endl;
// 	std::cout << "\t date : " << header.getDate() << std::endl;
// 	std::cout << "\t server : " << header.getServer() << std::endl;
// 	std::cout << "\t transfer-encoding : " << header.getTransferEncoding() << std::endl;
// 	std::cout << "\t content-length : " << header.getContentLength() << std::endl;
// 	std::cout << "\t content-type : " << header.getContentType() << std::endl;
// 	std::cout << "\t set-cookie : " << cookieString << std::endl;
// 	std::cout << " -- response-body" << std::endl;
// 	//std::cout << body.getBody() << std::endl;

// 	std::cout << "---- response 출력 끝 ----\n" << std::endl;
// }


// std::string	HttpResponse::getResponseToString() {
// 	std::string response = "";

// 	response += this->_httpResponseLine.getResponseLineToString();
// 	response += this->_httpResponseHeader.getResponseHeaderToString();
// 	response += this->_httpBody.getBody();

// 	return (response);
// }

// std::string		getCurrentTime()
// {
// 	char buffer[100];
	
// 	std::time_t	currentTime = std::time(NULL);
// 	std::tm* 	timeInfo = std::localtime(&currentTime);

// 	std::strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", timeInfo);

// 	return buffer;
// }

// HttpResponseHeader	HttpResponse::makeResponseHeader(const PathInfo& pathInfo, const size_t bodySize)
// {
// 	HttpResponseHeader	header;
	
// 	header.setDate(getCurrentTime());
// 	header.setServer(SERVER_NAME);
// 	header.setContentType(pathInfo.getFileType());
// 	header.setTransferEncoding("identity");
// 	header.setContentLength(bodySize);
	
// 	return (header); 
// }

// HttpBody	HttpResponse::makeResponseBody(const PathInfo& pathInfo, const HttpStatus& httpStatus)
// {
// 	HttpBody	httpBody;
// 	std::string	path = pathInfo.getReturnPage();

// 	//std::cout << "return path : " << path << std::endl;

// 	if (path.empty() == true)// 1. Return error page
// 		httpBody.createErrorBody(httpStatus);
// 	else if (pathInfo.getAutoIndex() == true) // 2. Return autoIndex page
// 		httpBody.createAutoIndexBody(path);
// 	else // 3. Return normal page
// 		httpBody.createGenericBody(path);

// 	return (httpBody);
// }

// int		HttpResponse::getStatusCode()
// {
// 	return (this->_httpResponseLine.getHttpStatus().getStatusCode());
// }

// HttpResponseLine	&HttpResponse::getResponseLine()
// {
// 	return (this->_httpResponseLine);
// }