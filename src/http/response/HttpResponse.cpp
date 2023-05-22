#include "HttpResponse.hpp"
#include "HttpValidator.hpp"
#include "HttpException.hpp"

/* constructor */
HttpResponse::HttpResponse(){}

HttpResponse::HttpResponse(Config& config, HttpRequest& request)
{

	try
	{
		// HttpRequestLine		requestLine = request.getRequestLine();
		// HttpRequestHeader	requestHeader = request.getHttpRequestHeader();
		// std::string			method = requestLine.getMethod();

		// // 1) Syntax Check
		// HttpValidator::CheckRequestLineSyntax(requestLine);
		// HttpValidator::CheckRequestHeaderSyntax(requestHeader); // default value 생각

		// // 2) find Server
		// ServerInfo serverInfo = HttpHandler::findServerInfo(config, requestHeader);

		// // 3) validate Location
		// LocationBlock location = HttpHandler::findLocation(serverInfo, requestLine.getRequestURI());
		// 3-1) location block과 일치하는 url가 있나없나 확인. 
		// 	-> 있으면 location block의 설정 참고 (index가 안되면 autoindex 확인)
		//	-> location block에 없으면 -> server block 설정 참고(초기화 리스트 default root 추가)

		// 어쨋거나, setBOdy() 에서 오픈할 파일경로전달.
		// // 4) limit_except Check
		// HttpValidator::MethodPermitted(location, method);
		// 	// 메서드가 허용된지 확인하는 로직
		// 	// 허용되지 않으면 예외를 던질 수 있음

		HttpValidator::validateRequest(config, request);
		// fielUploade or fileDelete();
		setResponse(request, 200);
		
		// 5) method별 response 생성
		if (method == "GET")
		{
			// setResponse
			// auto-index?
			// get(o) , 
			this->setResponseLine(HttpStatus(200));
			// auto-index
			this->setBody(HttpHandler::generateResponseBody(serverInfo.getServerBlock(), location));
			this->setResponseHeader(requestHeader);
		}
		else if (method == "POST")
		{
			
		}
		else if (method == "DELETE")
		{

		}
	}
	catch (ResponseException &e)
	{
		setResponse(request, e.httpStatus()); // 400
		//setResponse(request, 200);
	}
	catch () // 500?
	{

	}
	
	setResponse(config, request, 200);
	// default-error-page
		// ** auto-index
	// 4) 맞다면 -> 맞춰서 

}

HttpResponse&	HttpResponse::operator=(const HttpResponse& prev)
{
	(void)prev;
	return (*this);
}

void	HttpResponse::setResponseLine(const HttpStatus& httpStatus)
{
	this->_httpResponseLine.setHttpStatus(httpStatus);
}

void	HttpResponse::setResponseHeader(const HttpRequestHeader& requestHeader)
{
	//this->_httpResponseHeader.setContentLength(this->_httpBody.getBodySize());
}

void	HttpResponse::setBody(const std::string& body)
{
	this->_httpBody.setBody(body);
}




// std::string responseBody = "This is the response body.";
// std::string contentLength = std::to_string(responseBody.length());


//

	// HttpResponseLine
	// HttpStatus httpStatus(setDefaultStatusCode(request.getHttpRequestLine().getMethod()));
	
	// try
	// {
	// 	HttpHandler::ValidateRequestLine(config, request.getHttpRequestLine());
	// }
	// catch (ResponseException &ex)
	// {
	// 	this->_httpResponseLine.setHttpStatus(ex.httpStatus());
	// }
	
	// this->_httpResponseLine.setHttpStatus(httpStatus);
	// std::cout << "ResponseLine처리 완료" << std::endl;
	// 
	// 순서
	// a) request-line에서 http/1.1, 유효한 method인지 체크 (validateRequestLine)
	// b) request-header의 server_name과 일치하는 server_block->server_name찾아서 갖고있기. (ServerBlock serverBlock)
	// c) config.serverblock과 request 비교
		// [compareValuewithConfig]
		// c-3) 유효한 root + index(전체 경로) == 인가?
		// [request value 분석]
		// c-4) 유효한 content-type 인가?
	// d) get 요청은 get요청 처리로. (단순 경로 주기)
	// e) post 요청은 post 요청으로 (upload를 원할 경우..? cgi..?)
	// f) delete 요청은 delete 요청으로 (cgi)