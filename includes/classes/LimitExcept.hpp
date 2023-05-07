#ifndef LIMITEXCEPT_HPP
# define LIMITEXCEPT_HPP

# include "webserv.hpp"
# include "validate.hpp"

class LimitExcept {
	private :
		std::vector<std::string>	_methodList;
		std::string					_allow;
		std::string					_deny;

	public :
		LimitExcept() {};;
		LimitExcept(const std::vector<std::string> &);

		// check
		static void blockCheck(std::ifstream&, Validate&);
		
		// getter, setter
		void	setMethodList(const std::vector<std::string> &);
		void	setAllow(const std::vector<std::string> &);
		void	setDeny(const std::vector<std::string> &);

		//test
		void	printInfo();

};

# endif
