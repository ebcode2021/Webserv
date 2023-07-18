#ifndef SOCKINFO_HPP
# define SOCKINFO_HPP

# include "webserv.hpp"
# include "SockData.hpp"
# include "ModeInfo.hpp"
# include "HttpRequest.hpp"
//# include "CgiInfo.hpp"
//# include "HttpResponse.hpp"
//# include "PathInfo.hpp"

class SockInfo
{
	private :
		int				_sockFd;
		bool			_errorCode;
		ModeInfo		_modeInfo;
		SockData		_sockData;
		HttpRequest		_request;
		//HttpResponse	_response;
		//CgiInfo			*_cgiInfo;
		//PathInfo		_pathInfo;
		//std::string		_clientAddr;
		//int				_readMode;
		//int				_sendMode;
		

	public :
		// constructor
		SockInfo(int, SockMode);

		// getter
		int	 		getSockFd() const;
		int			getErrorCode();
		ModeInfo	&getModeInfo();
		SockData	&getSockData();
		HttpRequest	&getRequest();

		// setter
		void		setErrorCode(int);
		
		// getter
		//HttpRequest&	getRequest();
		//HttpResponse	getResponse();
		//std::string		getClientAddr();
		//CgiInfo			*getCgiInfo();
		//const PathInfo		&getPathInfo() const;

		// setter
		//void			setRequest(HttpRequest&);
		//void			setResponse(HttpResponse&);
		//void			setRequestHeader();
		//void			setRequestBody();
		//void			setCgiInfo(CgiInfo *);
		//void			setPathInfo(PathInfo &);
		
		// method
		std::string 	chunkedEncoding();

		// new 추가

		// print
		void 			printRequestInfo();
};

#endif