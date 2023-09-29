#ifndef HTTP_RESPONSE_HEADER_HPP
# define HTTP_RESPONSE_HEADER_HPP

# include "webserv.hpp"
# include "HttpRequest.hpp"
# include "PathInfo.hpp"

class	HttpResponseHeader
{
	private :
		std::string					_date;
		std::string					_server;
		std::string					_contentType;
		std::string					_loaction;
		size_t						_contentLength;
		//std::vector<std::string>	_setCookie;

	public :
		// constructor
		HttpResponseHeader();

		// getter, setter
		std::string					getDate() const;
		std::string					getServer() const;
		std::string					getContentType() const;
		std::string					getLocation() const;
		size_t						getContentLength() const;
// 		std::vector<std::string>	getSetCookie() const;

		void						setDate(const std::string&);
		void						setServer(const std::string&);
		void						setContentType(const std::string&);
		void						setContentLength(const size_t);
		void						setLocation(const std::string&);
		void						setHeader(HttpBody	&);
		void						setHeader(PathInfo &, HttpBody &);
// 		void						setSetCookie(const std::string&);

// 		// method
		std::string					getResponseHeaderToString();
// 		std::string					getCookieString();
// 		//void						handleSession(SessionStorage&, std::string&, const std::string&);

// 		// print
// 		void						printCookie();
};

#endif