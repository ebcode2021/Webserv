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

		// getter, setter
		std::vector<int>	getStatusCodeList() const;
		std::string			getPath() const;
};

# endif