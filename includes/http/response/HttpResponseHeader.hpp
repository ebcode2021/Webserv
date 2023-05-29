#ifndef HTTP_RESPONSE_HEADER_HPP
# define HTTP_RESPONSE_HEADER_HPP

# include "webserv.hpp"
# include "HttpRequest.hpp"

class	HttpResponseHeader
{
	private :
		std::string					_date; // 응답이 생성된 날짜와 시간
		std::string					_server; // 요청을 처리하는 서버의 이름과 버전
		std::string					_contentType; // 응답이 본문을 포함하는 경우 반드시 포함
		size_t						_contentLength; // 응답이 본문을 포함하는 경우 반드시 포함
		std::string					_transferEncoding;
		std::vector<std::string>	_setCookie;	//Cookie 관련

	public :
		// constructor
		HttpResponseHeader();

		// getter, setter
		std::string					getDate() const;
		std::string					getServer() const;
		std::string					getContentType() const;
		size_t						getContentLength() const;
		std::string					getTransferEncoding() const;
		std::vector<std::string>	getSetCookie() const;

		void						setDate(std::string&);
		void						setServer(std::string&);
		void						setContentType(std::string&);
		void						setContentLength(size_t);
		void						setTransferEncoding(std::string&);
		void						setSetCookie(std::string&);

		// method
		void						setHttpResponseHeader(HttpRequest&, size_t);
		std::string					getCurrentTime();
		std::string					getResponseHeaderToString();

};

#endif