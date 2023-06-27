#include "HttpResponse.hpp"
#include "ResponseException.hpp"

/* constructor */
HttpResponse::HttpResponse(){}

HttpResponse::HttpResponse(HttpResponseLine& responseLine, HttpResponseHeader& responseHeader, HttpBody& responseBody)
{
	this->_httpResponseLine = responseLine;
	this->_httpResponseHeader = responseHeader;
	this->_httpBody= responseBody;
}

/* setter */
void	HttpResponse::setBody(const std::string& body) {
	this->_httpBody.setBody(body);
}

HttpResponseHeader&	HttpResponse::getResponseHeader() {
	return (this->_httpResponseHeader);
}

std::string			HttpResponse::getBody() const {
	return (this->_httpBody.getBody());
}

/* method */
HttpResponse HttpResponse::createResponse(Config& config, HttpRequest& request, const std::string& clientAddr, SessionStorage& sessionStorage)
{
	// request
	HttpRequestLine		requestLine = request.getHttpRequestLine();
	HttpRequestHeader	requestHeader = request.getHttpRequestHeader();
	std::string			method = requestLine.getMethod();

	// response
	HttpResponseLine	responseLine(method);
	HttpResponseHeader	responseHeader;
	HttpBody			responseBody;

	// 1. find server block and location block
	ServerInfo		serverInfo    = config.findServerInfoByHost(requestHeader.getHost());
	LocationBlock	locationBlock = serverInfo.findLocationBlockByURL(requestLine.getRequestURI());

	PathInfo 	pathInfo(locationBlock.getFullPath());
	std::string	sessionId = requestHeader.getSessionIdByCookie();

	try
	{
		requestLine.validateRequestLine(locationBlock.getLimitExcept(), clientAddr);
		requestHeader.validateRequestHeader(locationBlock);
		
		pathInfo.validatePath();
		//(void)sessionStorage;
		sessionStorage.validateSession(sessionId, requestLine.getRequestURI());

		if (method == "GET")
			pathInfo.processGetRequest(locationBlock);
		else if (method == "DELETE")
			pathInfo.processDeleteRequest();
	}
	catch(const ResponseException &ex)
	{
		std::cout << "************** error 발생!" << ex.statusCode() << std::endl;
		responseLine.setHttpStatus(ex.httpStatus());
		pathInfo.setReturnPageByError(locationBlock.getErrorPage(), ex.statusCode());
	}
	catch (const SessionException &ex)
	{
		std::cout << " ************* 304 발생!" << ex.statusCode() << std::endl;
		responseLine.setHttpStatus(ex.httpStatus());
	}
	// post나 delete일때, body 넘겨줄지?
	if (method == "GET" && responseLine.getHttpStatus().getStatusCode() != 304)
		responseBody = makeResponseBody(pathInfo, responseLine.getHttpStatus());
	responseHeader = makeResponseHeader(pathInfo, responseBody.getBodySize());
	return (HttpResponse(responseLine, responseHeader, responseBody));
}


void	HttpResponse::printHttpResponse()
{
	HttpResponseLine line = this->_httpResponseLine;
	HttpResponseHeader header = this->_httpResponseHeader;
	HttpBody body = this->_httpBody;
	std::string	cookieString = header.getCookieString();

	std::cout << "\n---- [response 출력] ----" << std::endl;
	std::cout << "\n---- [response 출력] ----" << std::endl;
	std::cout << " -- response-line" << std::endl;
	std::cout << "\t httpStatus : " << line.getHttpStatus().getStatusCode() << " " << line.getHttpStatus().getReason() << std::endl;
	std::cout << "\t version : " << line.getVersion() << std::endl;
	std::cout << " -- response-header" << std::endl;
	std::cout << "\t date : " << header.getDate() << std::endl;
	std::cout << "\t server : " << header.getServer() << std::endl;
	std::cout << "\t transfer-encoding : " << header.getTransferEncoding() << std::endl;
	std::cout << "\t content-length : " << header.getContentLength() << std::endl;
	std::cout << "\t content-type : " << header.getContentType() << std::endl;
	std::cout << "\t set-cookie : " << cookieString << std::endl;
	std::cout << " -- response-body" << std::endl;
	//std::cout << body.getBody() << std::endl;

	std::cout << "---- response 출력 끝 ----\n" << std::endl;
}


std::string	HttpResponse::getResponseToString() {
	std::string response = "";

	response += this->_httpResponseLine.getResponseLineToString();
	response += this->_httpResponseHeader.getResponseHeaderToString();
	response += this->_httpBody.getBody();

	return (response);
}

std::string		getCurrentTime()
{
	char buffer[100];
	
	std::time_t	currentTime = std::time(NULL);
	std::tm* 	timeInfo = std::localtime(&currentTime);

	std::strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", timeInfo);

	return buffer;
}

HttpResponseHeader	HttpResponse::makeResponseHeader(const PathInfo& pathInfo, const size_t bodySize)
{
	HttpResponseHeader	header;
	
	header.setDate(getCurrentTime());
	header.setServer(SERVER_NAME);
	header.setContentType(pathInfo.getFileType());
	header.setTransferEncoding("identity");
	header.setContentLength(bodySize);
	
	return (header); 
}

HttpBody	HttpResponse::makeResponseBody(const PathInfo& pathInfo, const HttpStatus& httpStatus)
{
	HttpBody	httpBody;
	std::string	path = pathInfo.getReturnPage();

	//std::cout << "return path : " << path << std::endl;

	if (path.empty() == true)// 1. Return error page
		httpBody.createErrorBody(httpStatus);
	else if (pathInfo.getAutoIndex() == true) // 2. Return autoIndex page
		httpBody.createAutoIndexBody(path);
	else // 3. Return normal page
		httpBody.createGenericBody(path);

	return (httpBody);
}

int		HttpResponse::getStatusCode()
{
	return (this->_httpResponseLine.getHttpStatus().getStatusCode());
}