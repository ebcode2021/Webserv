# include "utils.hpp"

std::string	extractRequestLine(std::string &data)
{
	const std::string	delim = CRLF;
	std::string			ret;
	std::size_t			pos = 0;

	pos = data.find(delim);
	if (pos == std::string::npos)
		throw 400;
	ret = data.substr(0, pos);
	data.erase(0, pos + delim.length());
	return (ret);
}

std::string extractQueryString(std::string &data)
{
	const std::string	delim = "?";
	std::string			ret;
	std::size_t			pos = 0;
	pos = data.find(delim);
	if (pos == std::string::npos)
		return "";
	ret = data.substr(pos + 1, data.length());
	data.erase(pos, data.length());
	return (ret);
}

std::string	extractHeaderField(std::string &data)
{
	const std::string	delim = CRLF;
	std::size_t			pos = 0;
	std::string			ret;
	std::string			line;

	while (true)
	{
		pos = data.find(delim);
		if (pos == std::string::npos)
			return "400";
		line = data.substr(0, pos);
		data.erase(0, pos + delim.length());
		if (line == "")
			break ;
	}
	return ret;
}