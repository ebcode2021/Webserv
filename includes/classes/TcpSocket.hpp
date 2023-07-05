#ifndef TCPSOCKET_HPP
# define TCPSOCKET_HPP

# include "webserv.hpp"
# include "CgiInfo.hpp"
# include "HttpRequest.hpp"
# include "HttpResponse.hpp"
# include "PathInfo.hpp"

class TcpSocket
{
	private :
		SocketInfo		_socketInfo;
		HttpRequest		_request;
		HttpResponse	_response;
		PathInfo		_pathInfo;
		int				_readMode;
		int				_sendMode;
		CgiInfo			*_cgiInfo;
		std::string		_clientAddr;
		

	public :
		// constructor
		TcpSocket();
		TcpSocket(int);
		
		// getter
		int	 			getSockFd();
		int	 			getSendByte();
		size_t 			getRecvByte();
		int				getReadMode();
		std::string		getBuf();
		HttpRequest&	getRequest();
		HttpResponse	getResponse();
		std::string		getClientAddr();
		int				getSendMode();
		std::string		getClientAddrBySocket();
		const char*		getBufToCStr();
		size_t			getBufSize();
		CgiInfo			*getCgiInfo();
		PathInfo		&getPathInfo() const;

		// setter
		void			setBuf(const std::string&);
		void			setReadMode(int);
		void			setSendMode(int);
		void			setRequest(HttpRequest&);
		void			setResponse(HttpResponse&);
		void			setRequestHeader();
		void			setRequestBody();
		void			setBufbyIndex(int, char);
		void			setCgiInfo(CgiInfo *);
		void			setPathInfo(PathInfo &);
		
		// method
		void			changeToNonblocking();
		void			addBuf(const std::string&);
		void			addReadSize(size_t);
		void			changeReadMode();
		std::string 	chunkedEncoding();
		void 			bufClear();
		void			addSendByte(int);
		void			bufTrim(int);
		void			resetInfo();

		// new 추가
		bool			isHttpRequest();

		// print
		void 			printRequestInfo();
};

#endif