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

	public :
		TcpSocket();
		TcpSocket(int);
		
		void			changeToNonblocking();
		void			bufJoin(char *);
		// getter, setter
		int	 			getSockFd();
		int	 			getSendByte();
		size_t 			getRecvByte();
		char*			getBuf();
		std::string 	getString();
		void			setBuf(std::string&);

		//
		HttpRequest&	getRequest();
		HttpResponse	getResponse();
		void			setRequest(HttpRequest&);
		void			setResponse(HttpResponse&);
		
		void			setRequestHeader();
		void			setRequestBody();

		void			setReadMode(int);
		//
		void	bufClear();

		int		getReadMode();

		void	addReadSize(size_t);
		
		void	setBufbyIndex(int, char);


		void	changeReadMode();

		std::string chunkedEncoding();

		


		//test
		const char *getStringToCStr();
		size_t	getStringSzie();
		void stringClear();
		void printRequestInfo();
};

#endif