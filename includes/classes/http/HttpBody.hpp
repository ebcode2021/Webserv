#ifndef HTTPBODY_HPP
# define HTTPBODY_HPP

# include "webserv.hpp"

class	HttpBody
{
	private :
		std::string	_body;

	public :
		// constructor
		HttpBody();
		HttpBody(std::string);

		// getter
		std::string	&getBody();

		// setter
		void		setBody(const std::string &);

		// operator
		void		operator+=(const std::string &);

		// method
		size_t						getBodySize() const;
		void						trimBody(int);

		// print
		void		print();
};

#endif