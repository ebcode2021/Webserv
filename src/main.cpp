#include "webserv.hpp"
#include "Config.hpp"


int main(int argc, char *argv[])
{
	(void)argc;
	std::cout << "드디어 시작!!" << std::endl;
	///	임시
	if (argc == 1) {
		std::cout << "인자 넣어주세요!" << std::endl;
		return (1);
	}
	///
	// if (validateArgument(argc, argv))
	// {
		std::cout << "컨피그 저장 시작" << std::endl;
		Config config(argv[1]);
		std::cout << "컨피그 저장 완료" << std::endl;
		config.printServerList();
		// 통신 시작 함수
	//}
	return 0;
}
