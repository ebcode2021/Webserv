#include "LocationBlock.hpp"
#include "webserv.hpp"

void LocationBlock::blockCheck(std::ifstream &infile, Validate& dataset)
{
	std::string					line;
	std::vector<std::string>	splitted;

	Validate::braceCheck(infile, OPEN_BRACE);
	dataset.resetLocationIndicationList();
	while (std::getline(infile, line))
	{
		splitted = split(line, WHITESPACE);
		if (splitted.size() == 0)
			continue ;
		if (splitted.size() == 1 && splitted[0].compare(CLOSE_BRACE) == 0)
			break ;
		Validate::propertyCntCheck(infile, splitted);
		locationIndications indication = dataset.findLocationIndication(splitted);
		switch (indication)
		{
			case l_limit_except :
				//LimitExcept::limitExceptCheck(infile, dataset);
				break ;
			case l_client_max_body_size :
				Validate::isNumeric(infile, splitted);
				break ;
			case l_root :
			case l_client_body_temp_path :
				Validate::isPathList(infile, splitted, single);
				break ;
			case l_index :
				Validate::isPathList(infile, splitted, multiple);
				break ;
			case l_autoindex :
				Validate::isStatus(infile, splitted);
				break ;
			case l_error_page :
				Validate::isErrorPageForm(infile, splitted);
				break ;
			case l_none :
				break ;
			default :
				fileErrorWithExit(NO_INDICATION, infile);
		}
		dataset.decrementLocationCounter(infile, splitted[0]);
	}
}