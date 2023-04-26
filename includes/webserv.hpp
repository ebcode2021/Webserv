#ifndef WEBSERV_HPP
# define WEBSERV_HPP

/* extern library */
# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <fstream>
# include <sstream>
# include <unistd.h>

/* common hpp*/
# include "const.hpp"
# include "enum.hpp"
# include "indication.hpp"
# include "message.hpp"
# include "struct.hpp"

/* utility hpp*/

/* src */
void		printErrorWithExit(std::string msg);
int			getErrorLine(std::ifstream& file);
void		fileErrorWithExit(std::string msg, std::ifstream& file);
void		endsWithSemicolon(std::ifstream&, std::string);

/* src - [utils] */
std::vector<std::string> split(const std::string& str, const std::string& delims);
bool	isNumber(const std::string& str);

#endif