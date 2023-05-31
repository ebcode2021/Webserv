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
		size_t						_contentLength;
		std::string					_transferEncoding;
		std::vector<std::string>	_setCookie;

	public :
		/* constructor */
		HttpResponseHeader();

		/* getter, setter */
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

		/* method */
		void						setHttpResponseHeader(PathInfo&, size_t);
		std::string					getCurrentTime();
		std::string					getResponseHeaderToString();

};

#endif