# include "utils.hpp"

std::string createPath(std::string url, std::string root)
{
	return (root + url);
}

PathType	determinePathType(std::string &path)
{
	struct stat pathStat;

	if (stat(path.c_str(), &pathStat) == 0)
	{
		if (S_ISREG(pathStat.st_mode))
			return P_FILE;
		else if (S_ISDIR(pathStat.st_mode))
			return P_DIR;
	}
	return P_NONE;
}

std::map<std::string, std::string> createTypeTable()
{
	std::map<std::string, std::string>	typeTable;
	std::vector<std::string> 			splittedLine;

	std::ifstream						file(FILE_TYPE_PATH);
	std::string							line;

	while (std::getline(file, line, ';'))
	{
		splittedLine = split(line, WHITESPACE);
		if (splittedLine.size() > 0)
		{
			for (size_t i = 1; i < splittedLine.size(); i++)
				typeTable.insert(make_pair(splittedLine[i], splittedLine[0]));
		}
	}
	return (typeTable);
}

std::string getFileExtension(const std::string &path)
{
	size_t dotIndex = path.find_last_of(".");

	if (dotIndex != std::string::npos && dotIndex < path.length() - 1)
		return path.substr(dotIndex + 1);

	return "";
}

std::string searchFileType(const std::string &path)
{
	static std::map<std::string, std::string> typeTable = createTypeTable();
	std::string fileExtension = getFileExtension(path);
	std::map<std::string, std::string>::iterator iter = typeTable.find(fileExtension);
	if (iter == typeTable.end())
		return (DEFAULT_FILE_TYPE);
	else
		return (iter->second);
}

bool	isAccess(std::string&	path)
{
	if (access(path.c_str(), R_OK | W_OK) == 0)
		return (true);
	return (false);
}

