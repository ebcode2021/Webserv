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



int	setSuccessStatusCode(std::string method)
{
	if (method.compare("GET") == 0)
		return (200);
	else if (method.compare("POST") == 0)
		return (201);
	else if (method.compare("DELETE") == 0)
		return (204);
	return (600);
}

HttpResponse::HttpResponse(HttpRequest& httpRequest, LocationBlock& block, HttpStatus& httpStatus)
{
	std::string	path = block.getRoot() + block.getPath();
	std::string method = httpRequest.getHttpRequestLine().getMethod();
	std::string host = httpRequest.getHttpRequestHeader().getServerNameToHost();

	PathInfo pathInfo(path);

	//if (httpStatus == 200)
	// 1. validate Path
	if (pathInfo.getPathType() != P_NONE)
	{
		if (pathInfo.getAccess() == false)
			httpStatus = HttpStatus(403);
	}
	else
		httpStatus = HttpStatus(404);
	
	// 2. validate directory Path
	if (pathInfo.isValidDirectory() == true)
	{
		std::vector<std::string>	indexList = block.getIndexList();
		size_t						indexListSize = indexList.size();

		if (indexListSize > 1)
		{
			for (size_t	i = 1; i < indexListSize; i++)
			{
				std::string addIndexpath = pathInfo.getPath() + indexList[i];
				if (pathInfo.isFile(addIndexpath) == true)
				{
					if (pathInfo.isAccess() == false)
						httpStatus = HttpStatus(403);
					break ;
				}
			}
			if (block.getAutoIndex() == true)
				pathInfo.autoIndexOn();
		}
		else
		{
			std::string addIndexpath = pathInfo.getPath() + indexList[0];
			if (pathInfo.isFile(addIndexpath) == false || pathInfo.isAccess() == false)
				httpStatus = HttpStatus(403);
		}
	}
}