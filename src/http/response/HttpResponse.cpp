#include "HttpResponse.hpp"
#include "HttpValidator.hpp"
#include "HttpException.hpp"


/* constructor */
HttpResponse::HttpResponse(){}

HttpResponse::HttpResponse(HttpRequest& httpRequest, PathInfo& pathInfo, HttpStatus& httpStatus)
{
	// response-line
	this->_httpResponseLine.setHttpResponseLine(httpStatus);
	// response-body
	this->_httpBody.setResponseBody(createResponseBody(pathInfo));
	// response-header
	this->_httpResponseHeader.setHttpResponseHeader(httpRequest, this->_httpBody.getBodySize());
}

HttpResponse HttpResponse::createResponse(Config& config, HttpRequest& httpRequest)
{
	std::cout << "createResponse 입장! " << std::endl;

	HttpRequestLine		requestLine   = httpRequest.getHttpRequestLine();
	HttpRequestHeader	requestHeader = httpRequest.getHttpRequestHeader();
	HttpBody			requestBody   = httpRequest.getBody();

	// 1. find server block and location block
	ServerInfo		serverInfo  = config.findServerInfoByHost(requestHeader.getHost());
	LocationBlock	locationBlock =  serverInfo.findLocationBlockByURL(requestLine.getRequestURI());
	//locationBlock.printInfo();
	std::string		path = locationBlock.getRoot() + locationBlock.getPath();


	std::cout << "locationBlock root: " << locationBlock.getRoot() << std::endl;
	//std::cout << "locationBlock path : " << locationBlock.getPath() << std::endl;
	
	HttpStatus	httpStatus;
	PathInfo 	pathInfo(path);
	try
	{
		// 1. validate request-line
		requestLine.validateRequestLine(locationBlock);
		// 2. validate request-Header
		requestHeader.validateRequestHeader(locationBlock);
		std::cout << "---- [success] request-line validate!" << std::endl;

		// 3. post나 delete일 경우 뭐 처리하는 함수 하나 추가
		
		// 4. validate Path or File
		pathInfo.printPathInfo();
		pathInfo.validatePathInfo(locationBlock);
		std::cout << "---- [success] PathInfo validate! " << std::endl;
	}
	catch(const ResponseException &ex)
	{
		httpStatus = ex.httpStatus();
		std::cout << "error 발생! " << httpStatus.getStatusCode() << std::endl;
		//pathInfo.setReturnPage(pathInfo.selectErrorPage(httpStatus, locationBlock.getErrorPage()));
	}
	return (HttpResponse(httpRequest, pathInfo, httpStatus));
}

std::string	HttpResponse::createResponseBody(PathInfo& pathInfo)
{
	(void)pathInfo;
	std::string a = "붙일곳";
	return(a);
}
HttpResponse&	HttpResponse::operator=(const HttpResponse& prev)
{
	(void)prev;
	return (*this);
}

// void	HttpResponse::setResponseLine(const HttpResponseLine& httpResponseLine)
// {
// 	//(void)httpStatus;
// 	//this->_httpResponseLine.setHttpStatus(httpStatus);
// }

// void	HttpResponse::setResponseHeader(const HttpResponseHeader& responseHeader)
// {
// 	//this->_httpResponseHeader.setContentLength(this->_httpBody.getBodySize());
// }

void	HttpResponse::setBody(const std::string& body)
{
	this->_httpBody.setBody(body);
}

	// 1. block의 root + location 조합해서, 파일인지 아닌지 검사

	// 2. file인 경우 -> 파일 오픈. (정상적으로 열리는지, 없으면 404)

	// 3. 경로인 경우 ** path가 null인 경우와 아닌 경우에 따라 또 나누고.

	// 3-1. index가 있는가?
		// 있으면 -> 파일 오픈
		// 있는데 존재하지 않음 -> auto-index가 있는가? -> 있으면 auto-indexing, 없으면 403
		// 없음 -> 403 not found
	// 4. 에러인 경우, error_page 탐색
	// std::string returnPage() 를 createResponseBody()인자로.

void	HttpResponse::printHttpResponse()
{
	HttpResponseLine line = this->_httpResponseLine;
	HttpResponseHeader header = this->_httpResponseHeader;
	HttpBody body = this->_httpBody;

	std::cout << "\n---- [response 출력] ----" << std::endl;
	std::cout << "\t response-line" << std::endl;
	std::cout << "\2t httpStatus : " << line.getHttpStatus().getStatusCode() << " " << line.getHttpStatus().getReason() << std::endl;
	std::cout << "\2t version : " << line.getVersion() << std::endl;
	std::cout << "\t response-header" << std::endl;
	std::cout << "\2t date : " << header.getDate() << std::endl;
	std::cout << "\2t server : " << header.getServer() << std::endl;
	std::cout << "\2t transfer-encoding : " << header.getTransferEncoding() << std::endl;
	std::cout << "\2t content-length" << header.getContentLength() << std::endl;
	std::cout << "\2t contnet-type" << header.getContentType() << std::endl;
	std::cout << "---- [response 출력 끝] ----\n" << std::endl;
}