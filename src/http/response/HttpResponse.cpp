#include "HttpResponse.hpp"

HttpResponse::HttpResponse(){};

/* setter */
void	HttpResponse::setResponseLine(HttpStatus& httpStatus)
{
	HttpResponseLine httpResponseLine(httpStatus);
}

void	HttpResponse::setResponseField()
{

}

void	HttpResponse::setBody()
{
	// 어떤 바디를 줘야할까?
}