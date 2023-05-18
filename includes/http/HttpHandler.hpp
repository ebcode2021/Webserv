#ifndef HTTP_HANDLER_HPP
# define HTTP_HANDLER_HPP

#include "TcpSocket.hpp"


namespace	RequestHandler
{
	bool	isEndOfRead(TcpSocket* tcpSocket);
};

namespace	ResponseHandler
{

};


	// try // 여기서 예외는 무조건 생길텐데 이걸 흠냐..여기서 트라이를..훔..
							// if (RequestHandler::isEndOfRead(curSock) == true)
								//kqHandler.changeEvent(curSock->getSockFd(), EVFILT_WRITE, EV_ADD, 0, 0, curSock);
							//////////////
#endif