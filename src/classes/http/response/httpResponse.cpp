#include "HttpResponse.hpp"

/* constructor */
HttpResponse::HttpResponse(){}

HttpBody	&HttpResponse::getBody()
{
	return (this->_httpBody);
}

HttpResponseLine	&HttpResponse::getResponseLine()
{
	return (this->_httpResponseLine);
}

HttpResponseHeader	&HttpResponse::getResponseHeader()
{
	return (this->_httpResponseHeader);
}

// method
static	std::string	errorPageGenerator(HttpStatus &status)
{
	std::stringstream page;
	
	page << "<html>	\
	<head><title>" + status.getString() + "</title></head>	\
	<body>	\
	<center><h1>" + status.getString() + "</h1></center>	\
	<hr><center>" + SERVER_NAME + "</center>	\
	</body>	\
	</html>";
	return (page.str());
}

std::string	getFileResource(std::string path)
{
	std::ifstream file(path.c_str()); // 파일 열기
    if (!file.is_open()) {
        throw 500;
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close(); // 파일 닫기
    return content;
}

std::string getPageResource(PathInfo &pathInfo, LocationBlock &location)
{
	(void)location;
	if (!pathInfo.getAccess())
		throw 403;
	switch (pathInfo.getPathType())
	{
		case P_FILE:
			return (getFileResource(pathInfo.getPath()));
		case P_DIR:
			break;
		case P_NONE:
			throw 404;
	}
	return "minsu";
}

void	HttpResponse::createErrorPage(HttpStatus &status, LocationBlock &locationBlock)
{
	std::vector<ErrorPage>	errorPageList = locationBlock.getErrorPage();
	HttpBody				body;

	body.setBody(errorPageGenerator(status));
	try
	{
		for (size_t i = 0; i < errorPageList.size(); i++)
		{
			if (errorPageList[i].compareCode(status.getStatusCode()))
			{
				PathInfo	pathInfo(errorPageList[i].getPath(), locationBlock);
				body.setBody(getPageResource(pathInfo, locationBlock));
				break ;
			}
		}
	}
	catch(int code)
	{
		status.setHttpStatus(code);
		body.setBody(errorPageGenerator(status));
	}
	this->_httpResponseLine.setHttpStatus(status);
	this->_httpBody = body;
	this->_httpResponseHeader.setHeader(this->_httpBody);
}

void	HttpResponse::createRedirect(const std::string &path)
{
	this->_httpResponseLine.setHttpStatus(HttpStatus(301));
	this->_httpResponseHeader.setLocation(path);
}

void	HttpResponse::createResponse(HttpStatus &status, PathInfo &pathInfo)
{
	(void)status;
	switch (pathInfo.getPathType())
	{
		case P_FILE:
			break;
		case P_DIR:
			break;
		case P_NONE:
			throw 404;
	}
}

void	HttpResponse::createResponse(HttpStatus &status, PathInfo &pathInfo, std::string &body)
{
	this->_httpResponseLine.setHttpStatus(status);
	this->_httpBody.setBody(body);
	this->_httpResponseHeader.setHeader(pathInfo, this->_httpBody);
}

void	HttpResponse::createNotModified()
{
	this->_httpResponseLine.setHttpStatus(HttpStatus(304));
}

void	HttpResponse::printHttpResponse()
{
	this->_httpResponseLine.print();
	std::cout << this->_httpResponseHeader.getResponseHeaderToString();
	this->_httpBody.print();
}
