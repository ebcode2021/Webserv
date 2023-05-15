#ifndef HTTPARSER_HPP
# define HTTPARSER_HPP

# include "webserv.hpp"
# include "HttpRequest.hpp"

# define BUFFER_SIZE 1024

namespace	HttpParser
{
	void								parseHeaderAndBody(std::string, std::vector<std::string>&, std::string&);
	void								parseRequest(HttpRequest&, std::string&);
	std::map<std::string, std::string>	createHeaderField(std::vector<std::string>&);

};

// "GET /index.html HTTP/1.1\r\nHost: example.com\r\nConnection: keep-alive\r\n\r\nHello, world!";


// if(this->_httprequest.header에 아무 것도  없다면)
//	HttpParser::parseHttpRequest(httprequest);
// else
//	this->_httpRequest.setBody(body);

// catch(const std::exception& e)
// {
// 	std::cerr << e.what() << '\n';
// }

#endif