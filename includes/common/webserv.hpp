#ifndef WEBSERV_HPP
# define WEBSERV_HPP

/* extern library */
# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <set>
# include <fstream>
# include <sstream>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/event.h>
# include <sys/socket.h>
# include <arpa/inet.h> 
# include <netdb.h>
# include <sys/stat.h>
# include <dirent.h>

/* common hpp*/
# include "const.hpp"
# include "enum.hpp"
# include "indication.hpp"
# include "message.hpp"
# include "path.hpp"
# include "setting.hpp"
# include "struct.hpp"

/* utils hpp*/

/* src */
void						printErrorWithExit(std::string msg);
int							getErrorLine(std::ifstream& file);
void						fileErrorWithExit(std::string msg, std::ifstream& file);
void						endsWithSemicolon(std::ifstream&, std::string);

/* src - [utils] */
std::vector<std::string>				split(const std::string& str, const std::string& delims);
bool									endsWithSemicolon(std::string &str);
std::string								itos(int);
std::map<std::string, int>				create_directivemap(const std::string &);

/* validateUtils */
std::map<std::string, unsigned short>	fileDataToMap(std::ifstream &file);
bool									isNumber(const std::string& str);
bool									isNumeric(std::vector<std::string> data);
bool									isPathList(std::vector<std::string> data, multiplicityOption option);
bool									isStatus(std::vector<std::string> data);
bool									isErrorPageForm(std::vector<std::string> data);

#endif