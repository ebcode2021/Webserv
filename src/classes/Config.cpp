#include "Config.hpp"

Config::Config(std::string fileName)
{
	
}

bool Config::fileCheck(int argc, char *argv[])
{
	std::ifstream				infile;
	std::string					line;
	std::vector<std::string>	splitted;

	if (Validate::argumentCheck(argc, argv))
	{
		Validate dataset;
		infile.open(std::string(argv[1]));
		while (std::getline(infile, line))
		{
			splitted = split(line, ' ');
			if (splitted[0].compare("server") == 0)
			{
				if (splitted.size() != 1)
					printErrorWithExit(BLOCK_NAME);
				ServerBlock::blockCheck(infile);
			}
		}
		infile.close();
		return (dataset.requiredDataCheck());
	}
	else
		return false;
}

// bool Config::fileCheck(int argc, char *argv[])
// {
// 	std::ifstream				infile;
// 	std::string					line;
// 	std::vector<std::string>	splitted;
// 	bool						result = false;


// 	validate::argumentCheck(argc, argv);

// 	infile.open(std::string(argv[1]));
// 	while (std::getline(infile, line))
// 	{
// 		splitted = split(line, ' ');
// 		if (splitted[0].compare("http") == 0)
// 		{
// 			if (splitted.size() != 1)
// 				printErrorWithExit(BLOCK_NAME);
// 			ServerBlock::blockCheck(infile);
// 			return result;
// 		}
// 	}
// 	infile.close();
// 	if (result == false)
// 		printErrorWithExit();
// 	return result;
// }