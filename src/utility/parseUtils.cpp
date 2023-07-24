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

std::map<std::string, std::string>	extractHeaderField(std::string &data)
{
	std::map<std::string, std::string> headers;
	std::vector<std::string> splittedLine;
	const std::string	delim = CRLF;
	std::size_t			pos = 0;
	std::string			line;

	while (true)
	{
		pos = data.find(delim);
		if (pos == std::string::npos)
			throw 400;
		line = data.substr(0, pos);
		std::cout << line << std::endl;
		data.erase(0, pos + delim.length());
		if (line == "")
			break ;
		
		std::string::size_type colonPos = line.find(":");
        if (colonPos != std::string::npos) {
            std::string key = line.substr(0, colonPos);
            std::string value = trimString(line.substr(colonPos + 1), " ");
            headers[key] = value;
        }
		else
			throw 400;
	}
	return (headers);
}

std::string trimString(const std::string &str, const std::string &delim) {
    size_t first = str.find_first_not_of(delim);
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(delim);
    return str.substr(first, (last - first + 1));
}