#ifndef LIMITEXCEPT_HPP
# define LIMITEXCEPT_HPP

# include "webserv.hpp"
# include "validate.hpp"

class LimitExcept {
	private :
		std::vector<std::string>			_methodList;
		std::map<std::string, std::string>	_accessDirectiveList;
		std::string					_allow;
		std::string					_deny;

	public :
		/* constructor */
		LimitExcept();
		LimitExcept(const std::vector<std::string> &);

		/* setter */
		std::map<std::string, std::string>	getAccessDirectiveList() const;
		std::vector<std::string>	getMethodList() const;
		std::string					getAllow() const;
		std::string					getDeny() const;
		void					setMethodList(const std::vector<std::string> &);
		void		setAllow(const std::vector<std::string> &);
		void		setDeny(const std::vector<std::string> &);

		// method
		bool		isValidMethod(const std::string&, const std::string&) const;
		bool		isMethodInList(const std::string&) const;
		bool		isValidClientAddr(const std::string&, const std::string&) const;
		bool		isAllValue(const std::string&) const;
		

		// check */
		static void	blockCheck(std::ifstream&, Validate&);

		// print */
		void		printInfo();

};

# endif
