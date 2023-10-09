# include "ErrorPage.hpp"

/* constructor */
ErrorPage::ErrorPage(std::vector<std::string>& value) {
	for (size_t i = 1; i < value.size() - 1; i++)
	{
		this->statusCode.push_back(atoi(value[i].c_str()));
	}
	this->path = value[value.size() - 1];
}

/* getter */
std::vector<int>	ErrorPage::getStatusCodeList() const {
	return (this->statusCode);
}

std::string			ErrorPage::getPath() const {
	return (this->path);
}

/* method*/
bool	ErrorPage::compareCode(int code)
{
	for (size_t i = 0; i < this->statusCode.size(); i++)
	{
		if (code == this->statusCode[i])
			return (true);
	}
	return (false);
}

/* print */
void ErrorPage::PrintInfo() const {
	std::cout << "error_page : ";
	for(size_t i = 0; i < this->statusCode.size(); i++) {
		std::cout << statusCode[i] << " ";
	}
	std::cout << path << std::endl;
}