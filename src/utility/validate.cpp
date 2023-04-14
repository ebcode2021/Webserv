#include "validate.hpp"

void	Validate::extensionCheck(char *name)
{
	std::string	extension = ".conf";
	std::string	fileName = std::string(name);
	int			index = fileName.find('.');

	if (index < 1 || extension.compare(std::string(fileName).substr(index)));
		printErrorWithExit(INVALID_ARGC);
}

bool	Validate::argumentCheck(int argc, char *argv[])
{
	if (argc == 1)
		printErrorWithExit(INVALID_ARGC);
	else if (argc == 2 || (argc == 3 && strcmp(argv[2], "-t") == 0))
	{
		Validate::extensionCheck(argv[1]);
		if (argc == 2)
			return true;
		else
			notice::printMessage(TEST_SUCCESS);
	}
	else
		printErrorWithExit(INVALID_ARGC);
	return false;
}
