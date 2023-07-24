#include "utils.hpp"

std::vector<std::string> split(const std::string& str, const std::string& delims)
{
	std::vector<std::string>	tokens;
	size_t	start = 0, end = 0;

	while ((end = str.find_first_of(delims, start)) != std::string::npos) {
		if (end != start) {
			tokens.push_back(str.substr(start, end - start));
		}
		start = end + 1;
	}
	if (start < str.length())
		tokens.push_back(str.substr(start));
	return (tokens);
}

bool	endsWithSemicolon(std::string str)
{
	char	lastChar = str.back();

	if (lastChar != ';')
		return false;
	return true;
}

std::string	itos(int integer)
{
	std::stringstream	str;
	
	str << integer;
	return (str.str());
}

std::map<std::string, int> create_directivemap(const std::string &path) {
	std::map<std::string, int> ret;
	std::ifstream server_keywords(path);
	std::string line;
	std::vector<std::string> splittedLine;
	size_t	i = 0;
	while (std::getline(server_keywords, line))
	{
		splittedLine = split(line, WHITESPACE);
		if (splittedLine.size() > 0)
			ret.insert(make_pair(splittedLine[0], i++));
	}
	return (ret);
}

bool compareContentLengthAndBodySize(const std::string& contentLength, size_t bodySize)
{
	size_t expectedSize = std::atoi(contentLength.c_str());

    return (expectedSize == bodySize);
}