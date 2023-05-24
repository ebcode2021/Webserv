#ifndef HTTP_STATUS_HPP
# define HTTP_STATUS_HPP

# include "webserv.hpp"

static const std::map<int, std::string> httpStatusMap;

// static const std::map<int, std::string> httpStatusMap = {
// 	{ 200, "OK" },
// 	{ 201, "Created" },
// 	{ 202, "Accepted" },
// 
// 	{ 401, "Unauthorized" },	{ 400, "Bad Request" },
// 	{ 403, "Forbidden" },
// 	{ 404, "Not Found" },
// 	{ 405, "Method Not Allowed" },
// 	{ 500, "Internal Server Error" },
// 	{ 502, "Bad Gateway" },
// 	{ 503, "Service Unavailable" },
// 	{ 505, "HTTP Version Not Supported" }
// };

// std::map<int, std::string>	init()
// {
// 	std::map<int, std::string> a;

// 	return(a);
// }

class	HttpStatus
{
	private :
		int			_statusCode;
		std::string	_reason;
		//static const std::map<int, std::string>	_httpStatusMap;

	public :
		// constructor
		HttpStatus();
		HttpStatus(int);
		
		// getter, setter
		std::map<int, std::string>& getmap();
		int			getStatusCode() const;
		std::string	getReason() const;
};

#endif