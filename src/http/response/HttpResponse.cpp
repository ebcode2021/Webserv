#include "HttpResponse.hpp"
#include "HttpValidator.hpp"
#include "HttpException.hpp"

/* constructor */
HttpResponse::HttpResponse(){}

HttpResponse::HttpResponse(Config& config, HttpRequest& request)
{
	try
	{
		HttpRequestLine		requestLine = request.getRequestLine();
		HttpRequestHeader	requestHeader = request.getHttpRequestHeader();
		std::string			method = requestLine.getMethod();

		// 1) Syntax Check
		HttpValidator::CheckRequestSyntax(requestLine);
		HttpValidator::CheckRequestHeaderSyntax(requestHeader);

		// 2) find Server
		ServerInfo serverInfo = HttpHandler::findServerInfo(config, requestHeader);

		// 3) find Location
		LocationBlock location = HttpHandler::findLocation(serverInfo, requestLine.getRequestURI());

		// 4) limit_except Check
		HttpValidator::MethodPermitted(location, method);
			// 메서드가 허용된지 확인하는 로직
			// 허용되지 않으면 예외를 던질 수 있음

		// 5) method별 response 생성
		if (method == "GET")
		{
			this->setResponseLine(HttpStatus(200));
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
	catch(ResponseException &e)
	{
		this->setResponseLine(e.httpStatus());
	}
	

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