#ifndef SETTING_HPP
# define SETTING_HPP

#include "webserv.hpp"

/* Default config setting */

const size_t		DEFAULT_PORT = 4242;
const std::string	SERVER_NAME = "webserv/1.0.0";
const std::string	DEFAULT_ROOT = ROOT_PATH + "resources/html";
const std::string	DEFAULT_INDEX = "index.html";

/* Default response file type */
const std::string	DEFAULT_FILE_TYPE = "application/octet-stream";

/* Cache folder */
const std::string	CACHE_ROOT = ROOT_PATH + ".caches/";

/* Extension */
const std::string	EXTENSION = ".conf";
const std::string	CACHE_FILE_EXTENSION = ".txt";


#endif