#include "HttpBody.hpp"

/* constructor */
HttpBody::HttpBody() {
	this->_body = "";
}

/* getter, setter */
std::string	HttpBody::getBody() const {
	return (this->_body);
}

void		HttpBody::setBody(const std::string& body) {
	this->_body += body;
}

/* method */
size_t		HttpBody::getBodySize() const {
	return (this->_body.size());
}

void	HttpBody::createErrorBody(const HttpStatus& httpStatus)
{
	std::stringstream	body;

	body << "<!DOCTYPE html>\n";
	body << "<html>\n";
	body << "<head><title>" << httpStatus.getStatusCode() << SP << httpStatus.getReason() << "</title>\n";
	body << "<meta charset=\"UTF-8\">\n";
	body << "</head>\n";
	body << "<body>\n";
	body << "<center><h1>" << httpStatus.getStatusCode() << SP << httpStatus.getReason() << "</h1></center>\n";
	body << "<hr><center>" << SERVER_NAME << "</center>\n";
	body << "</body>\n";
	body << "</html>\n";
	
	this->_body = body.str();
}

std::vector<std::string>	HttpBody::getFileNameByPath(const std::string& path)
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

void	HttpBody::createAutoIndexBody(const std::string& path)
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
	
	this->_body = body.str();
}

void	HttpBody::createGenericBody(const std::string& path)
{
	std::ifstream		file(path);
	std::stringstream	body;

	if (file.is_open())
	{
		body << file.rdbuf();
		file.close();
	}

	this->_body = body.str();
	// std::cout << this->_body << std::endl;
}