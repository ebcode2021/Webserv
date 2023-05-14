#ifndef HTTPBODY_HPP
# define HTTPBODY_HPP

class	HttpBody
{
	private :
		std::string	_body;

	public :
		// getter, setter
		std::string	getBody() { return (this->_body);};
		void		setBody(std::string body) {this->_body += body;};
};

#endif