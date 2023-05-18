#ifndef TCPSOCKET_HPP
# define TCPSOCKET_HPP

# include "webserv.hpp"
# include "HttpRequest.hpp"
# include "HttpResponse.hpp"

class TcpSocket
{
	private :
		SocketInfo	_socketInfo;
		HttpRequest		_request;
		//HttpResponse _response;
		std::string	_buf;
		int			_readMode;

	public :
		TcpSocket();
		TcpSocket(int);
		
		int		socketAccept();
		void	socketBind(int);
		void	socketListen();


		void	changeToNonblocking();
		void	bufJoin(char *);

		// getter, setter
		int	 getSockFd();
		int	 getSendByte();
		int 	getRecvByte();
		char	*getBuf();
		std::string getString();

		//
		void	setRequest(HttpRequest& httpRequest){this->_request = httpRequest;};
		//
		void	bufClear();

		int		getReadMode();
		
		void	setBufbyIndex(int, char);

		void	setRequest();

		void	changeReadMode();


		//test
		const char *getStringToCStr();
		size_t	getStringSzie();
		void stringClear();
		void printRequestInfo();
};

#endif