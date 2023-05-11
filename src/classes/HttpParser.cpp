#include "HttpParser.hpp"
#include "webserv.hpp"

char request[] = "GET /index.html HTTP/1.1\r\nHost: example.com\r\nConnection: keep-alive\r\n\r\nHello, world!";
#define PARSE_ERROR -1

void	HttpParser::parseHeaderAndBody(std::string request, std::vector<std::string>& header, std::string& body)
{
	size_t	doubleCRLFIndex = request.find(DOUBLE_CRLF);
	std::vector<std::string>	data;

	// header, body
	data.push_back(request.substr(0, doubleCRLFIndex));
	data.push_back(request.substr(doubleCRLFIndex + DOUBLE_CRLF.size(), request.size()));

	int start, end = 0;
	while ((end = data[0].find(CRLF)) != -1)
	{
		header.push_back(data[0].substr(start, end));
		start = end + CRLF.size();
	}
	body = data[1];
}

void	HttpParser::parseHttpRequest(HttpRequest& httpRequest, char *request)
{
	std::vector<std::string>	header;
	std::string					body;

	parseHeaderAndBody(request, header, body);

	std::vector<std::string>			requestLine = split(header[0], " ");
	std::map<std::string, std::string>	requestHeaderField = HttpParser::createHeaderField(header);

	httpRequest.setRequestLine(requestLine);
	httpRequest.setHeaderField(requestHeaderField);
	httpRequest.setBody(body);
}

std::map<std::string, std::string>	HttpParser::createHeaderField(std::vector<std::string>& headerField)
{
	// 오늘 구현할거
}