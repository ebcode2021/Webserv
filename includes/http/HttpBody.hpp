#ifndef HTTPBODY_HPP
# define HTTPBODY_HPP

# include "webserv.hpp"

class	HttpBody
{
	private :
		std::string	_body;

	public :
		// getter, setter
		std::string	getBody() const;
		void		setBody(const std::string&);

		// method
		size_t		getBodySize() const;
};

#endif