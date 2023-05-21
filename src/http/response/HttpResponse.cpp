#include "HttpResponse.hpp"
#include "HttpValidator.hpp"
#include "HttpException.hpp"

// 나중에 옮길 utils
int	setSuccessStatusCode(std::string method)
{
	if (method.compare("GET") == 0)
		return (200);
	else if (method.compare("POST") == 0)
		return (201);
	else if (method.compare("DELETE") == 0)
		return (204);
	return (600);
}

HttpResponse::HttpResponse(){}

HttpResponse::HttpResponse(Config& config, HttpRequest& request)
{
	try
	{
		HttpValidator::ValidateRequestLine(config, request.getHttpRequestLine());
		//HttpHandler::validateRequest
	}
	catch(ResponseException &e)
	{
		
	}
	
	// 
	// 순서
	// a) request-line에서 http/1.1, 유효한 method인지 체크 (validateRequestLine)
	// b) request-header의 server_name과 일치하는 server_block->server_name찾아서 갖고있기. (ServerBlock serverBlock)
	// c) config.serverblock과 request 비교
		// [compareValuewithConfig]
		// c-1) 유효한 server_name == host인가?(request-header)
		// c-2) 유효한 listen == port인가?
		// c-3) 유효한 root + index(전체 경로) == 인가?
		// [request value 분석]
		// c-4) 유효한 content-type 인가?
	// d) get 요청은 get요청 처리로. (단순 경로 주기)
	// e) post 요청은 post 요청으로 (upload를 원할 경우..? cgi..?)
	// f) delete 요청은 delete 요청으로 (cgi)

	// default-error-page
		// ** auto-index
	// 4) 맞다면 -> 맞춰서 

	//setResponseLine(config, request.getHttpRequestLine());
	

	// HttpResponseHeader

}

HttpResponse&	HttpResponse::operator=(const HttpResponse& prev)
{
	(void)prev;
	return (*this);
}


/* setter */
// void	HttpResponse::setResponseLine(Config& config, const HttpRequestLine& requestLine)
// {
// 	// set default statusCode
// 	int	success = setSuccessStatusCode(requestLine.getMethod());

// 	HttpStatus	httpStatus(success);

// 	try
// 	{
// 		HttpHandler::ValidateRequestLine(config, requestLine);
// 	}
// 	catch(const ResponseException &e)
// 	{
// 		this->_httpResponseLine.setHttpStatus(e.httpStatus());
// 	}
// 	this->_httpResponseLine.setHttpStatus(httpStatus);
	
// 	std::cout << "ResponseLine처리 완료" << std::endl;
// }

void	HttpResponse::setResponseField()
{

}

void	HttpResponse::setBody()
{
	// 어떤 바디를 줘야할까?
}







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