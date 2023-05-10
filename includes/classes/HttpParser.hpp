#ifndef HTTPARSER_HPP
# define HTTPARSER_HPP

# include "webserv.hpp"

# define BUFFER_SIZE 1024

namespace	HttpParser
{
	std::vector<std::string>	getRequestLine(char *);
	std::vector<std::string>	getHeader(char *);
	std::vector<std::string>	getBody(char *);
};

// \r\n\r\n -> 헤더와 바디를 분리

#endif