#ifndef HTTPBODY_HPP
# define HTTPBODY_HPP

class	HttpBody
{
	private :
		std::string	_body;

	public :
		// getter, setter
		std::string	getBody();
		void		setBody(std::string);
};

#endif