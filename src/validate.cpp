#include "webserv.hpp"
#include "Config.hpp"

void	validateConfig(char *configName)
{
	(void)configName;
	//readline으로 한줄씩 읽어들이기
}

void	printa()
{
	std::cout << "hi?" << std::endl;
}

bool	validateArgument(int argc, char *argv[])
{
	if (argc == 1)
		printa();
	else if (argc == 2 || (argc == 3 && strcmp(argv[2], "-t") == 0))
	{
		if (Config::fileCheck(argv[1]) == false)
			return false;
		if (argc == 2)
			return true;
	}
	else
		printErrorWithExit(INVALID_ARGC);
	return true;
}