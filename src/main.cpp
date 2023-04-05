#include "Webserv.hpp"

void	config(std::string fileName)
{
	// open 하면서 readline으로 한줄씩 읽겠지.

	// 1. 한번에 에러 + 객체 생성
	// 2. 함수로 뺄지, 클래스로 보관할지?
	// error check
	// block 3개 

	// 라이브러리..?
}

int main(int argc, char *argv[])
{
	if (validateArgument(argc, argv))
	{
		// serverList 반환
		config(argv[1]); // conf 파싱
		// 통신 시작 함수
	}
	return 0;
}
