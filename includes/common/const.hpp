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

/* extension */
const std::string EXTENSION = ".conf";

/* path */
const std::string INDICATION_PATH = "/Users/eunson/Desktop/webserv/indication/";

const std::string KEYWORD_PATH = "/Users/eunson/Desktop/webserv/keywords/.server_keywords";

# define BUFSIZE 10

#endif