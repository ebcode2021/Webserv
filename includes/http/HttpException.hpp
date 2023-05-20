#ifndef HTTPEXCETPION_HPP
# define HTTPEXCETPION_HPP

# include "webserv.hpp"
# include "HttpStatus.hpp"

class	ResponseException
{
	private :
		HttpStatus	_httpStatus;
		

	public :
		explicit	ResponseException(const int statusCode)
			:_httpStatus(statusCode){}
		
		HttpStatus httpStatus() const { return(_httpStatus); }
};

// try
// {
// 	validateRequest(Config, curSock->request);
// 	{
// 		index.location.
// 		throw ResponseException(404);

// 		throw ResponseException(401);

// 	}
// }
// catch(ResponseException &e)
// {
// 	getResponse();
// }
// catch(exception &e)
// {
// 	// server 문제..?
// }
#endif

		// std::string	getReason(const int index)
		// {
		// 	std::map<int, std::string>::const_iterator it = httpStatusMap.find(index);

		// 	if (it != httpStatusMap.end())
		// 		return(it->second);
		// 	else
		// 		std::cerr << "여기 들어오면 진짜 잘못된거임. 이럴때 어찌 처리할까" << std::endl;
		// }