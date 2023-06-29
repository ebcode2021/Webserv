#ifndef CGIMETADATA_HPP
# define CGIMETADATA_HPP

# include "iostream"
# include "HttpRequest.hpp"

class CgiMetadata {
	private :
		std::string _pathInfo;
		std::string _requestMethod;
		std::string _contentLength;
		std::string _contentType;
		std::string _gatewayInterface;
		std::string _httpAcceptCharset;
		std::string _queryString;
		std::string _serverProtocol;
	public :
		CgiMetadata(HttpRequest &);
		char **createEnvp();
		std::string getServerProtocol;

};

#endif