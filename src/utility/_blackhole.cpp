#include "validate.hpp"

void		Validate::propertyCntCheck(std::ifstream& infile, std::vector<std::string> data)
{
	static std::vector<std::string> blocks;
	blocks.push_back("location");
	blocks.push_back("server");
	blocks.push_back("limit_except");

	bool	blockExist = (std::find(blocks.begin(), blocks.end(), data[0]) != blocks.end());
	
	if (blockExist && data.size() != 2)
		fileErrorWithExit(BLOCK_NAME, infile);
	else if (data.size() == 1)
		fileErrorWithExit(I_PROPERTIES, infile);
}
