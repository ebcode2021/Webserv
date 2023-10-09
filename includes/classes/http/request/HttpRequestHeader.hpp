#ifndef HTTPREQUESTHEADER_HPP
# define HTTPREQUESTHEADER_HPP

#include "webserv.hpp"

class	HttpRequestHeader
{
	private :
		std::map<std::string, std::string> _requestHeader;

	public :
		HttpRequestHeader();

		// getter
		std::string getHeaderByKey(std::string) const;

		//setter
		void	setRequestHeader(std::map<std::string, std::string>);

		// test
		void	print();
};

#endif