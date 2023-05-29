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

	//std::cout << "asdf?????????????????" << std::endl;
	//std::cout << this->getResponseToString() << std::endl;
	//exit(1);
	//this->printHttpResponse();
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
	locationBlock.printInfo();
	std::string		path = locationBlock.getRoot() + locationBlock.getPath();


	//std::cout << "locationBlock root: " << locationBlock.getRoot() << std::endl;
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
		//pathInfo.printPathInfo();
		pathInfo.validatePathInfo(locationBlock);
		std::cout << "---- [success] PathInfo validate! " << std::endl;
	}
	catch(const ResponseException &ex)
	{
		httpStatus = ex.httpStatus();
		std::cout << "error 발생! " << httpStatus.getStatusCode() << std::endl;
		
		std::string	selectPage = locationBlock.selectErrorPage(httpStatus);
		if (selectPage.empty() == false)
		{
			path += locationBlock.selectErrorPage(httpStatus);
			pathInfo.setReturnPage(path);
		}
		std::cout << "실제 에러 페이지 : " << path << std::endl;
	}
	return (HttpResponse(httpRequest, pathInfo, httpStatus));
}

std::string	HttpResponse::createResponseBody(PathInfo& pathInfo)
{
	std::stringstream	response;
	std::ifstream		file(pathInfo.getReturnPage());

	if (file.is_open())
	{
		response << file.rdbuf();
		file.close();
	}
	return (response.str());
}

void	HttpResponse::setBody(const std::string& body)
{
	this->_httpBody.setBody(body);
}

void	HttpResponse::printHttpResponse()
{
	HttpResponseLine line = this->_httpResponseLine;
	HttpResponseHeader header = this->_httpResponseHeader;
	HttpBody body = this->_httpBody;

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
	std::cout << " -- response-body" << std::endl;
	std::cout << body.getBody() << std::endl;

	std::cout << "---- [response 출력 끝] ----\n" << std::endl;
}


std::string	HttpResponse::getResponseToString() {
	std::string response = "";

	response += this->_httpResponseLine.getResponseLineToString();
	response += this->_httpResponseHeader.getResponseHeaderToString();
	response += this->_httpBody.getBody();

	return (response);
}
