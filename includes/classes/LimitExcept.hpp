#ifndef LIMITEXCEPT_HPP
# define LIMITEXCEPT_HPP

#include "webserv.hpp"

class LimitExcept {
	private :
		std::vector<std::string>	_methodList;
		std::string					_allow;
		std::string					_deny;

	public :
		static void limitExceptCheck(std::ifstream&, Validate&);
};

#endif