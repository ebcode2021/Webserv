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
const std::string DOUBLE_CRLF = "\r\n";

const std::size_t BUFSIZE = 512;

const std::size_t CLIENT_BODY_SIZE = 1048576;

#endif