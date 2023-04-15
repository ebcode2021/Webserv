#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# define WHITESPACE " \t\n\v\f\r"

/* extern library */
# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <fstream>
# include <sstream>

/* class hpp */
# include "Config.hpp"
# include "LocationBlock.hpp"
# include "ServerBlock.hpp"
# include "ServerInfo.hpp"
# include "ServerList.hpp"

/* common hpp*/
# include "enum.hpp"
# include "file.hpp"
# include "message.hpp"
# include "struct.hpp"

/* utility hpp*/
#include	"notice.hpp"
#include	"validate.hpp"

/* src */
void		printErrorWithExit(std::string msg);

/* src - [utils] */
std::vector<std::string> split(const std::string& str, const std::string& delims);

#endif