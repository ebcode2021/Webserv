#include "Server.hpp"
#include "Config.hpp"

std::string ROOT_PATH;

void	currentPwd() {
	char currentDir[FILENAME_MAX];

	 if (getcwd(currentDir, sizeof(currentDir)) != NULL) {
		ROOT_PATH = currentDir;
	} else {
		printErrorWithExit(FAIL_TO_GET_PWD);
	}
}

int main(int argc, char **argv)
{
	std::cout << ROOT_PATH << std::endl;

	Config::fileCheck(argc, argv);
	Config	config(argv[1]);
	Server	server(config);
	std::cout << "========Server Run==========" << std::endl;
	server.run();
}