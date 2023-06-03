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

	public :
		TcpSocket();
		TcpSocket(int);
		
		void			changeToNonblocking();
		// getter, setter
		int	 			getSockFd();
		int	 			getSendByte();
		size_t 			getRecvByte();
		void			setBuf(const std::string&);

		//
		HttpRequest&	getRequest();
		HttpResponse	getResponse();
		void			setRequest(HttpRequest&);
		void			setResponse(HttpResponse&);
		std::string		getBuf();
		void			addBuf(const std::string&);
		
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
		const char *getBufToCStr();
		size_t	getBufSzie();
		void printRequestInfo();
};

#endif