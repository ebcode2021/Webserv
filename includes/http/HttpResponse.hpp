#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP

#include "webserv.hpp"
#include "ResponseStatus.hpp"
#include "HttpRequest.hpp"


// Response-Header
	// Response-Line
		// HTTP/1.1 <status code> <reason phrase>
	// Response-Header-Field
// Reasponse-Body

class	HttpResponse
{
	private :
		// response-line
		ResponseStatus	_responseStatus;

		// response-header
		std::string	_date; // 응답이 생성된 날짜와 시간
		std::string	_server; // 요청을 처리하는 서버의 이름과 버전
		std::string	_contentLength; // 응답이 본문을 포함하는 경우 반드시 포함
		std::string	_contentType; // 응답이 본문을 포함하는 경우 반드시 포함
		std::string	_setCookie;	//Cookie 관련

		// response-body
		std::string		_body;

	public :
		// constructor
		HttpResponse(); // Config도 필요하지않나????

		// method
		std::string	getResponse(); // 내부에 getHeader(), getBody()

		// member field's getter, setter
		std::string	getDate();
		std::string	getServer();
		std::string	getContentLength();
		std::string	getContentType();
		std::string	getCookie();
		// setter
		//validate

};
#endif