#include "CgiMetadata.hpp"

CgiMetadata::CgiMetadata(HttpRequest &request) {
	//this->_pathInfo = std::string("PATH_INFO=") + "/Users/minsukan/Desktop/42/webserv/Webserv/resources/upload";
	this->_requestMethod = "REQUEST_METHOD=" + request.getHttpRequestLine().getMethod();
	this->_contentLength = "CONTENT_LENGTH=" + itos(request.getHttpRequestHeader().getContentLength());
	this->_contentType = "CONTENT_TYPE=" + request.getHttpRequestHeader().getContentType();
	//std::cout << _contentType << std::endl;
	std::cout << "____________________" << std::endl;
	//this->_gatewayInterface = std::string("GATEWAY_INTERFACE=") + "CGI/1.1";
	//this->_httpAcceptCharset = std::string("HTTP_ACCEPT_CHARSET") + "utf-8";
	this->_queryString = request.getHttpRequestLine().getQueryString();
	this->_serverProtocol = std::string("SERVER_PROTOCOL=") + "HTTP/1.1";
}

char **CgiMetadata::createEnvp() {
	char **envp = new char*[9];
	//envp[0] = strdup(_pathInfo.c_str());
	envp[0] = strdup(_requestMethod.c_str());
	envp[1] = strdup(_contentLength.c_str());
	envp[2] = strdup(_contentType.c_str());
	//envp[3] = strdup(_gatewayInterface.c_str());
	//envp[5] = strdup(_httpAcceptCharset.c_str());
	//envp[6] = strdup(_queryString.c_str());
	envp[3] = strdup(_serverProtocol.c_str());
	envp[4] = NULL;
	return (envp);
}