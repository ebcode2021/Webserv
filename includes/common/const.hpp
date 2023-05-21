#ifndef CONST_HPP
# define CONST_HPP

#include "webserv.hpp"

#define SOCKET_ERROR   -1
#define INVALID_SOCKET -1

/* const string */
const std::string WHITESPACE = " \t\n\v\f\r";
const std::string OPEN_BRACE = "{";
const std::string CLOSE_BRACE = "}";
const std::string SEMICOLON = ";";

/* file name */
const std::string LOCATION = ".location_indications";
const std::string SERVER = ".server_indications";
const std::string LIMIT_EXCEPT = ".limit_except_indications";

/* extension */
const std::string EXTENSION = ".conf";

/* path */
const std::string INDICATION_PATH = "/Users/eunson/Desktop/webserv/indication/";

const std::string KEYWORD_PATH = "/Users/eunson/Desktop/webserv/keywords/.server_keywords";

/* http */
const std::string CRLF =  "\r\n";
const std::string DOUBLE_CRLF = "\r\n\r\n";

const std::size_t BUFSIZE = 512;

const std::size_t CLIENT_BODY_SIZE = 1048576;

static const std::string METHODS[] = {
	"GET", "POST", "DELETE"
};

static const std::string REQUEST_HEADERS[] = {
	  "Host", "User-Agent", "Connection", "Content-Type", "Content-Length", "Transfer-Encoding", "Cookie"
};

const size_t REQUEST_HEADER_SIZE = sizeof(REQUEST_HEADERS) / sizeof(std::string);

static const std::string RESPONSE_HEADERS[] = {
	"Date", "Server", "Content-Length", "Content-Type", "Set-Cookie", "Transfer-Encoding"
};

const size_t RESPONSE_HEADER_SIZE = sizeof(RESPONSE_HEADERS) / sizeof(std::string);

const std::string HTTP_VERSION = "HTTP/1.1";

const std::string SP = " ";

const std::string SERVER_NAME = "webserv/1.0.0";

#endif