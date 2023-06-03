#ifndef TCPSOCKET_HPP
# define TCPSOCKET_HPP

# include "webserv.hpp"
# include "HttpRequest.hpp"
# include "HttpResponse.hpp"

class TcpSocket
{
	private :
		SocketInfo		_socketInfo;
		HttpRequest		_request;
		HttpResponse	_response;
		std::string		_buf;
		int				_readMode;
		std::string		_clientAddr;

	public :
		// constructor
		TcpSocket();
		TcpSocket(int);
		
		// getter, setter
		int	 			getSockFd();
		int	 			getSendByte();
		size_t 			getRecvByte();
		int				getReadMode();
		char*			getBuf();
		std::string 	getString();
		HttpRequest&	getRequest();
		HttpResponse	getResponse();
		std::string		getClientAddr();
		void			setBuf(std::string&);
		void			setRequest(HttpRequest&);
		void			setResponse(HttpResponse&);

		// method
		std::string		getClientAddrBySocket();
		void			setRequestHeader();
		void			setRequestBody();
		void			changeToNonblocking();
		void			bufJoin(char *);
		void			setReadMode(int);
		void			addReadSize(size_t);
		void			setBufbyIndex(int, char);
		void			changeReadMode();
		std::string 	chunkedEncoding();
		void 			stringClear();

		// print
		void printRequestInfo();
};

#endif