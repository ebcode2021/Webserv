#ifndef HTTPARSER_HPP
# define HTTPARSER_HPP

# include "webserv.hpp"
# include "HttpRequest.hpp"

# define BUFFER_SIZE 1024

namespace	HttpParser
{
	void								parseHeaderAndBody(std::string, std::vector<std::string>&, std::string&);
	void								parseHttpRequest(HttpRequest&, char*);
	std::map<std::string, std::string>	createHeaderField(std::vector<std::string>&);

};

#endif