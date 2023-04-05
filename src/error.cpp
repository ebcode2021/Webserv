#include "Webserv.hpp"

void	printErrorWithExit(std::string msg)
{
	std::cerr << msg << std::endl;
	exit(EXIT_FAILURE);
}