#include "Server.hpp"
#include "Config.hpp"

int main(int argc, char **argv)
{
	(void)argc;

	// config파일 체크
	Config::fileCheck(argc, argv);

	Config	config(argv[1]);

	//test print
	//config.printConfig();

	Server	server(config);
	std::cout << "========Server Start==========" << std::endl;
	server.run();
}