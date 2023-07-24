#ifndef	UTILS_HPP
# define UTILS_HPP

# include "webserv.hpp"
# include "KqHandler.hpp"
//# include "SockInfo.hpp"

/* utils */
std::vector<std::string>	split(const std::string &, const std::string&);
bool 						compareContentLengthAndBodySize(const std::string&, size_t);

/* sockUtils.cpp */
int 		createSocket();
void		setSocketLingerOption(int);
void		changeFdOpt(int, int);

/* serverUtils.cpp */
void		createListenSocketForPorts(const std::set<int> &, KqHandler &);

/* parseUtils */
std::string							extractRequestLine(std::string &);
std::string							extractQueryString(std::string &);
std::map<std::string, std::string>	extractHeaderField(std::string &);
std::string							trimString(const std::string &, const std::string &);

/* encodingData.cpp */
std::string encodingData(std::string &, std::string, ReadMode &);

#endif