#include "webserv.hpp"
#include "Config.hpp"


int main(int argc, char *argv[])
{
	if (Config::fileCheck(argc, argv))
	{
		std::cout << "컨피그 저장 시작" << std::endl;
		Config config(argv[1]);
		std::cout << "컨피그 저장 완료" << std::endl;
		config.printServerList();
		// 통신 시작 함수
	}
	return 0;
}
