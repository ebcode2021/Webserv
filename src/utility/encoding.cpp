# include "utils.hpp"

std::string identityEncoding(std::string &data)
{
	return (data);
}

std::string chunkedEncoding(std::string &data, ReadPhase &phase)
{
	std::string body;
	std::string chunkSizeString;
	int			chunkSize;
	size_t		pos;
	
	while (1)
	{
		pos = data.find("\r\n");
		if (pos == std::string::npos)
			break ;
		chunkSizeString = data.substr(0, pos);
		chunkSize = std::stoi(chunkSizeString, nullptr, 16);
		std::cout << chunkSize << std::endl;
		if (chunkSize == 0) {
			phase = R_END;
		}
		data.erase(0, pos + 2);
		body += data.substr(0, chunkSize);
		data.erase(0, chunkSize + 2);
	}
	return (body);
}

std::string encodingData(std::string &data, std::string encoding, ReadPhase &phase)
{
	std::string backUp;

	if (encoding == "chunked")
		backUp = chunkedEncoding(data, phase);
	else
		backUp = identityEncoding(data);
	return (backUp);
}