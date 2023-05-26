#include "HttpResponse.hpp"
#include "HttpValidator.hpp"
#include "HttpException.hpp"

/* constructor */
HttpResponse::HttpResponse(){}

HttpResponse& HttpResponse::createResponse(Config& config, HttpRequest& httpRequest)
{
	HttpRequestLine		requestLine   = httpRequest.getHttpRequestLine();
	HttpRequestHeader	requestHeader = httpRequest.getHttpRequestHeader();
	HttpBody			requestBody   = httpRequest.getBody();

	std::string			method = requestLine.getMethod();

	// create response
	HttpResponse	response; // x

	// find server block and location block
	ServerInfo		serverInfo  = config.findServerInfoByHost(requestHeader.getHost());
	ServerBlock		serverBlock = serverInfo.getServerBlock();

	// std::Vector<LocationBlock>의 0번째 index가 default
	LocationBlock	locationBlock =  serverInfo.findLocationBlockByURL(requestLine.getRequestURI());

	exit(1);
	try
	{
		HttpValidator::validateRequest(httpRequest, serverBlock, locationBlock);
		if (method == "POST")
			;
		else if (method == "DELETE")
			; // unset
	}
	catch(const ResponseException &ex)
	{
		// status 저장 해야댐
		//response.getResponseLine().setHttpStatus(ex.httpStatus());
	}
	return (HttpResponse());
}

// response.setResponseLine(HttpResponse::createResponseLine());
// response.setResponseHeader(HttpResponse::composeResponseHeader());
// response.setBody(HttpResponse::composeBody());

// 	// 	// // 1) Syntax Check
// 	// 	// HttpValidator::CheckRequestLineSyntax(requestLine);
// 	// 	// HttpValidator::CheckRequestHeaderSyntax(requestHeader); // default value 생각

// 	// 	// // 2) find Server
// 	// 	// ServerInfo serverInfo = HttpHandler::findServerInfo(config, requestHeader);

// 	// 	// // 3) validate Location
// 	// 	// LocationBlock location = HttpHandler::findLocation(serverInfo, requestLine.getRequestURI());
// 	// 	// 3-1) location block과 일치하는 url가 있나없나 확인. 
// 	// 	// 	-> 있으면 location block의 설정 참고 (index가 안되면 autoindex 확인)
// 	// 	//	-> location block에 없으면 -> server block 설정 참고(초기화 리스트 default root 추가)

// 	// 	// 어쨋거나, setBOdy() 에서 오픈할 파일경로전달.
// 	// 	// // 4) limit_except Check
// 	// 	// HttpValidator::MethodPermitted(location, method);
// 	// 	// 	// 메서드가 허용된지 확인하는 로직
// 	// 	// 	// 허용되지 않으면 예외를 던질 수 있음


HttpResponse&	HttpResponse::operator=(const HttpResponse& prev)
{
	(void)prev;
	return (*this);
}

void	HttpResponse::setResponseLine(const HttpResponseLine& httpResponseLine)
{
	//(void)httpStatus;
	//this->_httpResponseLine.setHttpStatus(httpStatus);
}

void	HttpResponse::setResponseHeader(const HttpResponseHeader& responseHeader)
{
	//this->_httpResponseHeader.setContentLength(this->_httpBody.getBodySize());
}

void	HttpResponse::setBody(const std::string& body)
{
	this->_httpBody.setBody(body);
}
