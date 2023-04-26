
#include "Config.hpp"
#include "indication.hpp"
#include "enum.hpp"
#include "notice.hpp"




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

	fileMode mode = Validate::argumentCheck(argc, argv);
	if (mode)
	{
		Validate dataset;
		infile.open(std::string(argv[1]));
		if (infile.fail())
			printErrorWithExit(CHECK_CONFIG_FILE);
		while (std::getline(infile, line))
		{
			splitted = split(line, WHITESPACE);
			if (splitted[0].compare("server") == 0)
			{
				if (splitted.size() != 1)
					fileErrorWithExit(BLOCK_NAME, infile);
				ServerBlock::blockCheck(infile, dataset);
			}
			else
				fileErrorWithExit(UNDEFINED_LINE, infile);
		}
		infile.close();
		if (mode == test)
			notice::printMessage(TEST_SUCCESS);
		else
			return true;
	}
	return false;
}
