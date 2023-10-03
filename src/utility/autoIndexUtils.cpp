#include "utils.hpp"

std::vector<std::string>	getFileNameByPath(std::string& path)
{
	std::vector<std::string>	filename;
	struct dirent				*entry;
	DIR							*dir;

	dir = opendir(path.c_str());
	if (dir == nullptr) {
		return (filename);
	}

	entry = readdir(dir);
	while ((entry = readdir(dir)) != nullptr)
	{
		filename.push_back(entry->d_name);
	}
	closedir(dir);
	return (filename);
}

std::string	createAutoIndexBody(std::string path)
{
	std::stringstream	body;
	std::vector<std::string> fileName = getFileNameByPath(path);

	body << "<!DOCTYPE html>\n";
	body << "<html>\n";
	body << "<title>" << path << "</title>\n";
	body << "<meta charset=\"UTF-8\">\n";
	body << "</head>\n";
	body << "<body>\n";
	body << "<h1>" << path << "</h1>\n";
	body << "<hr>\n";
	body << "<pre>\n";
	for (size_t i = 0; i < fileName.size(); i++) {
		body << "<a href=\"" << fileName[i] << "\">" << fileName[i] << "</a>\n";
	}
	body << "</pre>\n";
	body << "<hr>\n";
	body << "</body>\n";
	body << "</html>\n";
	
	return (body.str());
}