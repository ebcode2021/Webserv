#ifndef CGIMETADATA_HPP
# define CGIMETADATA_HPP

# include "iostream"
# include "HttpRequest.hpp"
# include "PathInfo.hpp"

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
		std::string _uploadPath;

	public :
		/* constructor */
		CgiMetadata(HttpRequest &, PathInfo &);
		
		void	setUploadPathInfo(std::string);

		char	**createEnvp();
		
		void	print();


};

#endif
