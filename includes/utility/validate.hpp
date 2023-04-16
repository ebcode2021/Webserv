#ifndef VALIDATE_HPP
# define VALIDATE_HPP

#include "webserv.hpp"

class	Validate
{
	private :
		std::unordered_map<std::string, locationIndications>	_locationIndications;
		std::unordered_map<std::string, serverIndications>		_serverIndications;
		std::map<std::string, unsigned short>	_originServerMap;
		std::map<std::string, unsigned short>	_originLocationMap;
		std::map<std::string, unsigned short>	_serverMap;
		std::map<std::string, unsigned short>	_locationMap;

	public :
		/* constructor */
		Validate();

		/* checker */
		static bool	argumentCheck(int, char *[]);
		static void	braceCheck(std::ifstream&, std::string);
		static void	extensionCheck(char *);
		bool		requiredDataCheck();

		/* find */
		serverIndications	findServerIndication(std::vector<std::string>);

		/* reset */
		void		resetServerIndicationList();
		void		resetLocationIndicationList();

};


#endif