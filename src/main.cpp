#include "Server.hpp"
#include "Config.hpp"

int main(int argc, char **argv)
{
	Config::fileCheck(argc, argv);
	Config	config(argv[1]);
	Server	server(config);
	std::cout << "========Server Run==========" << std::endl;
	server.run();
}