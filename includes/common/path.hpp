#ifndef PATH_HPP
# define PATH_HPP

# include "webserv.hpp"

/* Path */
//const std::string	ROOT_PATH = "/Users/eunson/Desktop/webserv/";
//const std::string	ROOT_PATH = "/Users/eunson/Desktop/webserv/";
//const std::string	ROOT_PATH = "/Users/eunbison/Desktop/42seoul/webserv/";  
const std::string	ROOT_PATH = "/Users/minsu/Desktop/42seoul/webserv/";  
/* Indications */
const std::string INDICATION_PATH = ROOT_PATH + "indication/";
const std::string KEYWORD_PATH = ROOT_PATH + "keywords/.server_keywords";
const std::string LOCATION = ".location_indications";
const std::string SERVER = ".server_indications";
const std::string LIMIT_EXCEPT = ".limit_except_indications";

const std::string CGI_PATH = "/usr/bin/python3";

/* File Type */
const std::string FILE_TYPE_PATH = ROOT_PATH + "filetype/mime.types";


#endif