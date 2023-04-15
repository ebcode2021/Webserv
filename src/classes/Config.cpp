
#include "Config.hpp"

Config::Config(std::string fileName)
{
	std::string					line;
	std::ifstream				confFile(fileName);
	std::vector<std::string>	splitedLine;
	///
	std::cout << "설정 파일 시작 지점" << std::endl;
	///
	if (!confFile.is_open())
		printErrorWithExit("Invaild FileName");
	while (std::getline(confFile, line))
	{
		splitedLine = split(line, WHITESPACE);
		if (splitedLine[0].compare("server") == 0)
			this->_serverList.addServer(confFile);
	}
}

bool Config::fileCheck(int argc, char *argv[])
{
	std::ifstream				infile;
	std::string					line;
	std::vector<std::string>	splitted;

	(void)argc;
	(void)argv;
	return 0;
	// if (Validate::argumentCheck(argc, argv))
	// {
	// 	Validate dataset;
	// 	infile.open(std::string(argv[1]));
	// 	while (std::getline(infile, line))
	// 	{
	// 		splitted = split(line, ' ');
	// 		if (splitted[0].compare("server") == 0)
	// 		{
	// 			if (splitted.size() != 1)
	// 				printErrorWithExit(BLOCK_NAME);
	// 			ServerBlock::blockCheck(infile);
	// 		}
	// 	}
	// 	infile.close();
	// 	return (dataset.requiredDataCheck());
	// }
	// else
	// 	return false;
}
