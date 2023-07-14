#include "Server.hpp"
#include "Config.hpp"

int main(int argc, char **argv)
{
	(void)argc;

	// config파일 체크
	//Config::fileCheck(argc, argv);

	// 설정파일 생성
	Config	config(argv[1]);
	config.printConfig();

	Server	server(config);
	std::cout << "========Server Start==========" << std::endl;
	server.run();
	
	
	// 설정파일을 기반으로 서버 생성
	//Server	server(config);
}