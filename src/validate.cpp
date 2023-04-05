#include "Webserv.hpp"

void	validateConfig(char *configName)
{
	//readline으로 한줄씩 읽어들이기
}

void	printa()
{
	std::cout << "hi?" << std::endl;
}

int	validateArgument(int argc, char *argv[])
{
	if (argc == 1)
		printa();
	else if (argc == 2 || argc == 3 && strcmp(argv[2], "-t") == 0)
	{
		validateConfig(argv[1]);
		if (argc == 2)
			return 1;
	}
	else
		printErrorWithExit(INVALID_ARGC);
	return 0;
}