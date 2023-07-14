#ifndef STRUCT_HPP
# define STRUCT_HPP

# include "webserv.hpp"

typedef struct errorPage
{
	std::vector<int>	statusCode;
	std::string			path;
}						errorPage;

#endif