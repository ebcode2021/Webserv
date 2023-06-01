#ifndef HTTPBODY_HPP
# define HTTPBODY_HPP

# include "webserv.hpp"
# include "PathInfo.hpp"
# include "HttpStatus.hpp"

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
		void		createResponseBody(const PathInfo&, const HttpStatus&);
		void	createErrorBody(const HttpStatus&);
		void createAutoIndexBody(const std::string&);
		void createGenericBody(const std::string&);
		std::vector<std::string>	getFileNameByPath(const std::string&);
};

#endif