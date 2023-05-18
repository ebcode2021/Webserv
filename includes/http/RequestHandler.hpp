#ifndef REQUEST_HANDLER_HPP
# define REQUEST_HANDLER_HPP

// 요청이 규격에 맞는지 확인하는 작업을 수행
// 유효성 검사, URL 파싱 등을 수행
# include "webserv.hpp"

class	RequestHandler
{
	private :
		
	public : 
		
		
};

/*
	if (tcpScocket->어떤거) // 처음이라면
	{
		HttpParser::parseHttpRequest(tcpSocket.request, "받은 데이터");
		// httpHeader-line , httpHeader-requestField, httpBody
	}
	else 
	{
		tcpSocket->_request.setBody("받은 데이터");
	}

	// if(더 읽을게 없나?) -> content_lenght == bodysize || <0x0> chunked.
	

	if (tcpsocket.->request.done) // default 일때, chunked 될때.
	{
		// kqueue에서 이벤트 더이상 읽을 필요 없다고 작성하는 부분
		write event 로 등록 해달라고.
	}
	else
		// read event더 주세요.
*/

//	HttpParser::parseHttpRequest(httprequest);
// else
//	this->_httpRequest.setBody(body);

// catch(const std::exception& e)
// {
// 	std::cerr << e.what() << '\n';
// }
#endif