#ifndef STRUCT_HPP
# define STRUCT_HPP

# include <iostream>
# include <vector>

typedef struct errorPage
{
	std::vector<int>	statusCode;
	std::string			path;
}						errorPage;

#endif