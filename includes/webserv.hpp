#ifndef WEBSERV_HPP
# define WEBSERV_HPP

/* extern library */
# include <iostream>
# include <string>
# include <vector>
# include <fstream>

/* class hpp*/
# include "Config.hpp"
# include "Http.hpp"
# include "Location.hpp"
# include "Server.hpp"

/* common */
# include "error.hpp"

/* src */
void	printErrorWithExit(std::string msg);
int		validateArgument(int argc, char *argv[]);

#endif