#include "CgiMetadata.hpp"

CgiMetadata::CgiMetadata(HttpRequest &request, PathInfo &path) {
	(void)path;
	this->_pathInfo = "PATH_INFO=" + request.getHttpRequestLine().getRequestURI();
	this->_requestMethod = "REQUEST_METHOD=" + request.getHttpRequestLine().getMethod();
	this->_contentLength = "CONTENT_LENGTH=" + request.getHttpRequestHeader().getHeaderByKey(CONTENT_LENGTH);
	this->_contentType = "CONTENT_TYPE=" + request.getHttpRequestHeader().getHeaderByKey("Content-Type");
	this->_gatewayInterface = std::string("GATEWAY_INTERFACE=") + "CGI/1.1";
	this->_httpAcceptCharset = std::string("HTTP_ACCEPT_CHARSET=") + "utf-8";
	this->_queryString = "QUERY_STRING=" + request.getHttpRequestLine().getQueryString();
	this->_serverProtocol = std::string("SERVER_PROTOCOL=") + "HTTP/1.1";
}

void	CgiMetadata::setUploadPathInfo(std::string path) {
	this->_pathInfo = "UPLOAD_DIR=" + path;
}

char **CgiMetadata::createEnvp() {
	char **envp = new char*[9];
	envp[0] = strdup(_pathInfo.c_str());
	envp[1] = strdup(_requestMethod.c_str());
	envp[2] = strdup(_contentLength.c_str());
	envp[3] = strdup(_contentType.c_str());
	envp[4] = strdup(_gatewayInterface.c_str());
	envp[5] = strdup(_httpAcceptCharset.c_str());
	envp[6] = strdup(_queryString.c_str());
	envp[7] = strdup(_serverProtocol.c_str());
	envp[8] = NULL;
	return (envp);
}

void	CgiMetadata::print()
{
	std::cout << this->_pathInfo << "\n"
		<< this->_contentLength << "\n"
		<< this->_contentType << "\n"
		<< this->_gatewayInterface << "\n"
		<< this->_httpAcceptCharset << "\n"
		<< this->_requestMethod << "\n"
		<< this->_serverProtocol << "\n"
		<< this->_queryString << std::endl;
}