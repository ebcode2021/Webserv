#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# define WHITESPACE " \t\n\v\f\r"

/* extern library */
# include <iostream>
# include <string>
# include <vector>
# include <fstream>
# include <sstream>

/* common */
# include "error.hpp"

/* src */
void		printErrorWithExit(std::string msg);
bool		validateArgument(int argc, char *argv[]);

/* src - [utils] */
std::vector<std::string> split(const std::string& str, const std::string& delims);

#endif