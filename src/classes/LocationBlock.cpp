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
		if (splitted[0].compare("limit_except") && splitted.size() == 1)
			fileErrorWithExit(I_PROPERTIES, infile);
		locationIndications indication = dataset.findLocationIndication(splitted);
		switch (indication)
		{
			case locationIndications::limit_except :
				//LimitExcept::limitExceptCheck(infile, dataset);
				break ;
			case locationIndications::client_max_body_size :
				Validate::isNumeric(infile, splitted);
				break ;
			case locationIndications::root :
			case locationIndications::client_body_temp_path :
				Validate::isPathList(infile, splitted, multiplicityOption::single);
				break ;
			case locationIndications::index :
				Validate::isPathList(infile, splitted, multiplicityOption::multiple);
				break ;
			case locationIndications::autoindex :
				Validate::isStatus(infile, splitted);
				break ;
			case locationIndications::error_page :
				Validate::isErrorPageForm(infile, splitted);
				break ;
			case locationIndications::none :
				break ;
			default :
				fileErrorWithExit(NO_INDICATION, infile);
		}
		dataset.decrementCounter(infile, splitted[0]);
	}
	Validate::braceCheck(infile, CLOSE_BRACE);
}