#include "HttpParser.hpp"
#include "webserv.hpp"

char request[] = "GET /index.html HTTP/1.1\r\nHost: example.com\r\nConnection: keep-alive\r\n\r\nHello, world!";

void	HttpParser::parseHeaderAndBody(std::string request, std::vector<std::string>& header, std::string& body)
{
	std::vector<std::string>	data;
	size_t						doubleCRLFIndex = request.find(DOUBLE_CRLF);

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

void	HttpParser::parseRequest(HttpRequest& httpRequest, std::string& request)
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
	std::map<std::string, std::string>	headerMap;

	std::vector<std::string>::iterator it;

	for (it = headerField.begin() + 1; it != headerField.end(); ++it)
	{
		std::string	delimiter = ": ";
		std::string	header = *it;
		size_t 		pos = header.find(delimiter);

		if (pos != std::string::npos)
		{
			std::string	key	= header.substr(0, pos);
			std::string	value = header.substr(pos + delimiter.size());
			headerMap.insert(std::make_pair(key, value));
		}
	}
	return (headerMap);
}