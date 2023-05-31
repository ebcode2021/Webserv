#include "HttpResponse.hpp"
#include "HttpValidator.hpp"
#include "HttpException.hpp"


/* constructor */
HttpResponse::HttpResponse(){}

HttpResponse::HttpResponse(HttpRequest& httpRequest, PathInfo& pathInfo, HttpStatus& httpStatus)
{
	// response-line
	this->_httpResponseLine.setHttpResponseLine(httpStatus);
	// response-body
	this->_httpBody.setResponseBody(createResponseBody(pathInfo, httpStatus));
	// response-header
	this->_httpResponseHeader.setHttpResponseHeader(httpRequest, this->_httpBody.getBodySize());

	//std::cout << "asdf?????????????????" << std::endl;
	//std::cout << this->getResponseToString() << std::endl;
	//exit(1);
	//this->printHttpResponse();
}

HttpResponse HttpResponse::createResponse(Config& config, HttpRequest& httpRequest)
{
	std::cout << "createResponse 입장! " << std::endl;

	HttpRequestLine		requestLine   = httpRequest.getHttpRequestLine();
	HttpRequestHeader	requestHeader = httpRequest.getHttpRequestHeader();
	HttpBody			requestBody   = httpRequest.getBody();

	// 1. find server block and location block
	ServerInfo		serverInfo  = config.findServerInfoByHost(requestHeader.getHost());
	LocationBlock	locationBlock =  serverInfo.findLocationBlockByURL(requestLine.getRequestURI());
	locationBlock.printInfo();
	std::string		path = locationBlock.getRoot() + locationBlock.getPath();


	//std::cout << "locationBlock root: " << locationBlock.getRoot() << std::endl;
	//std::cout << "locationBlock path : " << locationBlock.getPath() << std::endl;
	
	HttpStatus	httpStatus;
	PathInfo 	pathInfo(path);
	try
	{
		// 1. validate request-line
		requestLine.validateRequestLine(locationBlock);
		// 2. validate request-Header
		requestHeader.validateRequestHeader(locationBlock);
		std::cout << "---- [success] request-line validate!" << std::endl;

		// 3. post나 delete일 경우 뭐 처리하는 함수 하나 추가
		
		// 4. validate Path or File
		pathInfo.validatePathInfo(locationBlock);
		std::cout << "---- [success] PathInfo validate! " << std::endl;
		//pathInfo.printPathInfo();
	}
	catch(const ResponseException &ex)
	{
		httpStatus = ex.httpStatus();
		std::cout << "error 발생! " << httpStatus.getStatusCode() << std::endl;
		
		std::string	selectPage = locationBlock.selectErrorPage(httpStatus);
		if (selectPage.empty() == false)
		{
			path += locationBlock.selectErrorPage(httpStatus);
			pathInfo.setReturnPage(path);
		}
		std::cout << "실제 에러 페이지 : " << path << std::endl;
	}
	return (HttpResponse(httpRequest, pathInfo, httpStatus));
}

std::string	HttpResponse::createResponseBody(PathInfo& pathInfo, HttpStatus &httpStatus)
{
	std::stringstream	response;
	std::ifstream		file(pathInfo.getReturnPage());

	// 1. Return error page
	if (pathInfo.getReturnPage().empty())
		return (createErrorBody(httpStatus));
	// 2. Return autoIndex page
	if (pathInfo.getAutoIndex() == true)
		return (createAutoIndexBody(pathInfo.getReturnPage()));
	else // 3. Return normal page
	{
		if (file.is_open())
		{
			response << file.rdbuf();
			file.close();
		}
	}
	return (response.str());
}

void	HttpResponse::setBody(const std::string& body)
{
	this->_httpBody.setBody(body);
}

void	HttpResponse::printHttpResponse()
{
	HttpResponseLine line = this->_httpResponseLine;
	HttpResponseHeader header = this->_httpResponseHeader;
	HttpBody body = this->_httpBody;

	std::cout << "\n---- [response 출력] ----" << std::endl;
	std::cout << " -- response-line" << std::endl;
	std::cout << "\t httpStatus : " << line.getHttpStatus().getStatusCode() << " " << line.getHttpStatus().getReason() << std::endl;
	std::cout << "\t version : " << line.getVersion() << std::endl;
	std::cout << " -- response-header" << std::endl;
	std::cout << "\t date : " << header.getDate() << std::endl;
	std::cout << "\t server : " << header.getServer() << std::endl;
	std::cout << "\t transfer-encoding : " << header.getTransferEncoding() << std::endl;
	std::cout << "\t content-length : " << header.getContentLength() << std::endl;
	std::cout << "\t content-type : " << header.getContentType() << std::endl;
	std::cout << " -- response-body" << std::endl;
	std::cout << body.getBody() << std::endl;

	std::cout << "---- [response 출력 끝] ----\n" << std::endl;
}


std::string	HttpResponse::getResponseToString() {
	std::string response = "";

	response += this->_httpResponseLine.getResponseLineToString();
	response += this->_httpResponseHeader.getResponseHeaderToString();
	response += this->_httpBody.getBody();

	return (response);
}

std::string					HttpResponse::createErrorBody(HttpStatus& httpStatus)
{
	std::stringstream	body;

	body << "<!DOCTYPE html>\n";
	body << "<html>\n";
	body << "<head><title>" << httpStatus.getStatusCode() << SP << httpStatus.getReason() << "</title>\n";
	body << "<meta charset=\"UTF-8\">\n";
	body << "</head>\n";
	body << "<body>\n";
	body << "<center><h1>" << httpStatus.getStatusCode() << SP << httpStatus.getReason() << "</h1></center>\n";
	body << "<hr><center>" << SERVER_NAME << "</center>\n";
	body << "</body>\n";
	body << "</html>\n";
	
	return (body.str());
}

std::vector<std::string> HttpResponse::getFileNameByPath(const std::string &path)
{
	std::vector<std::string>	filename;
	struct dirent				*entry;
	DIR							*dir;

	dir = opendir(path.c_str());
	if (dir == nullptr) {
		return (filename);
	}

	entry = readdir(dir);
	while ((entry = readdir(dir)) != nullptr)
	{
		filename.push_back(entry->d_name);
	}
	closedir(dir);
	return (filename);
}

std::string					HttpResponse::createAutoIndexBody(const std::string&path)
{
	std::stringstream	body;
	std::vector<std::string> fileName = getFileNameByPath(path);

	std::cout << "pathj!!!! " << path << std::endl;

	body << "<!DOCTYPE html>\n";
	body << "<html>\n";
	body << "<title>" << path << "</title>\n";
	body << "<meta charset=\"UTF-8\">\n";
	body << "</head>\n";
	body << "<body>\n";
	body << "<h1>" << path << "</h1>\n";
	body << "<hr>\n";
	body << "<pre>\n";
	for (size_t i = 0; i < fileName.size(); i++) {
		body << "<a href=\"" << fileName[i] << "\">" << fileName[i] << "</a>\n";
	}
	body << "</pre>\n";
	body << "<hr>\n";
	body << "</body>\n";
	body << "</html>\n";
	
	return (body.str());
}