#include "webserv.hpp"

int main(int argc, char *argv[])
{
	if (Config::fileCheck(argc, argv))
	{
		Config config(argv[1]);
		// 통신 시작 함수
	}
	return 0;
}
