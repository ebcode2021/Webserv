#include "webserv.hpp"

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

bool	isNumber(const std::string& str)
{
	for (std::string::const_iterator it = str.begin(); it != (str.end() - 1); ++it)
	{
		if (std::isdigit(*it) == 0)
			return false;
	}
	return true;
}