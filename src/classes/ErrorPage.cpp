# include "ErrorPage.hpp"

ErrorPage::ErrorPage(std::vector<std::string>& value) {
	for (size_t i = 1; i < value.size() - 1; i++)
	{
		this->statusCode.push_back(atoi(value[i].c_str()));
	}
	this->path = value[value.size() - 1];
	std::cout << "testestes" << this->path << std::endl;
}

// testPrint
using namespace std;

void ErrorPage::PrintInfo() {
	cout << "error_page : ";
	for(size_t i = 0; i < this->statusCode.size(); i++) {
		cout << statusCode[i] << " ";
	}
	cout << path << endl;
}