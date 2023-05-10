#include "webserv.hpp"
#include "validate.hpp"

void		Validate::propertyCntCheck(std::ifstream& infile, std::vector<std::string> data)
{
	static std::vector<std::string> blocks;
	blocks.push_back("location");
	blocks.push_back("server");
	blocks.push_back("limit_except");

	bool	blockExist = (std::find(blocks.begin(), blocks.end(), data[0]) != blocks.end());
	
	if (blockExist && data.size() != 2)
		fileErrorWithExit(BLOCK_NAME, infile);
	else if (data.size() == 1)
		fileErrorWithExit(I_PROPERTIES, infile);
}


// http practice

// 연결된 소켓으로부터 데이터 읽기
int n = read(events[i].ident, buffer, BUFFER_SIZE);
if (n == -1)
{
	perror("read");
	continue;
}

// 읽은 데이터에서 헤더 추출
char *p = strstr(buffer, "\r\n\r\n"); // \r\n\r\n은 헤더와 바디를 구분하는 구분자
if (p != NULL)
{
	// 헤더를 모두 읽은 경우
	*p = '\0';
	printf("Header : %s\n", buffer);
}

