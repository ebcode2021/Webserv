#include "HttpParser.hpp"

char request[] = "GET /index.html HTTP/1.1\r\nHost: example.com\r\nConnection: keep-alive\r\n\r\nHello, world!";
#define PARSE_ERROR -1

std::vector<std::string>	HttpParser::getRequestLine(char *request)
{
	char*	location = strstr(request, CRLF.c_str());

	if (location == NULL)
		return ;
}

std::vector<std::string>	HttpParser::getHeader(char *request)
{
	char* location = strstr(request, DOUBLE_CRLF.c_str());

	if (location == NULL)
		return ;
	
	
}

std::vector<std::string>	HttpParser::getBody(char *request)
{

}


// test code
int main()
{
    char *p = strstr(request, "\r\n\r\n");

    if (p == NULL) {
        // "\r\n\r\n" 구분자가 없는 경우
        return -1;
    }

    // 헤더 부분을 저장할 버퍼 생성
    char header[1024] = {0};
    strncpy(header, request, p - request + 4);
    printf("Header: %s\n", header);

    // 바디 부분을 저장할 버퍼 생성
    char body[1024] = {0};
    strncpy(body, p + 4, strlen(request) - (p - request) - 4);
    printf("Body: %s\n", body);

    return 0;
}