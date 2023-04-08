#ifndef WEBSERV_HPP
# define WEBSERV_HPP

/* extern library */
# include <iostream>
# include <string>
# include <vector>
# include <fstream>
# include <sstream>

/* class hpp*/
# include "Config.hpp"
# include "HttpBlock.hpp"
# include "LocationBlock.hpp"
# include "ServerBlock.hpp"

/* common */
# include "error.hpp"

/* src */
void		printErrorWithExit(std::string msg);
bool		validateArgument(int argc, char *argv[]);

/* src - [utils] */
std::vector<std::string> split(std::string input, char delimiter);

#endif