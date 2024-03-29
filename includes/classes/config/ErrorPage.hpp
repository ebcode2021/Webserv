#ifndef ERRORPAGE_HPP
# define ERRORPAGE_HPP

# include "webserv.hpp"

class ErrorPage {
	private :
		std::vector<int>	statusCode;
		std::string			path;

	public :
		// constructor
		ErrorPage(std::vector<std::string>&);

		// getter
		std::vector<int>	getStatusCodeList() const;
		std::string			getPath() const;

		// method
		bool				compareCode(int);

		// print
		void PrintInfo() const;
};

# endif