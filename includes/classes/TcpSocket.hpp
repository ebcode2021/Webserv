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
		void			setBuf(const std::string&);

		//
		HttpRequest&	getRequest();
		HttpResponse	getResponse();
		std::string		getClientAddr();
		void			setBuf(std::string&);
		void			setRequest(HttpRequest&);
		void			setResponse(HttpResponse&);

		void			changeToNonblocking();
		// method
		std::string		getClientAddrBySocket();
		std::string		getBuf();
		void			addBuf(const std::string&);
		
		void			setRequestHeader();
		void			setRequestBody();
		void			changeToNonblocking();
		void			setReadMode(int);
		void			addReadSize(size_t);
		void			setBufbyIndex(int, char);
		void			changeReadMode();
		std::string 	chunkedEncoding();
		void 			bufClear();

		// print
		//test
		const char *getBufToCStr();
		size_t	getBufSzie();
		void printRequestInfo();
};

#endif