#include "webserv.hpp"

// 다중 delim 가능하게
std::vector<std::string> split(std::string input, char delimiter)
{
	std::vector<std::string>	answer;
	std::stringstream 			ss(input);
	std::string					line;

	while (getline(ss, line, delimiter))
		answer.push_back(line);
	return (answer);
}