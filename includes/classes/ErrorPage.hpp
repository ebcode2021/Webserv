#ifndef ERRORPAGE_HPP
# define ERRORPAGE_HPP

# include "webserv.hpp"

class ErrorPage {
	private :
		std::vector<int>	statusCode;
		std::string			path;
	public :
		ErrorPage(std::vector<std::string>&);
		void PrintInfo();

};

# endif