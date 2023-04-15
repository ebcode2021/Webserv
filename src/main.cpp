#include "Config.hpp"

int main(int argc, char *argv[])
{
	if (Config::fileCheck(argc, argv))
	{
		std::cout << "드디어 시작!!" << std::endl;
		Config config(argv[1]);
		// 통신 시작 함수
	}
		return 0;
}
