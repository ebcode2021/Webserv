#ifndef VALIDATE_HPP
# define VALIDATE_HPP

#include "webserv.hpp"

class	Validate
{
	private :
		std::map<std::string, unsigned short>	_originServerIndications;
		std::map<std::string, unsigned short>	_originLocationIndications;
		std::map<std::string, unsigned short>	_serverIndications;
		std::map<std::string, unsigned short>	_locationIndications;

	public :
		/* constructor */
		Validate();

		/* checker */
		static bool	argumentCheck(int, char *[]);
		static void	extensionCheck(char *);
		void		braceCheck(char);
		bool		requiredDataCheck();

		/* find */
		void		findIndication(std::string);

		/* getter && setter */
		void		setServerIndicationList();
		void		setLocationIndicationList();

		/* reset */
		void		resetServerIndicationList();
		void		resetLocationIndicationList();

};


#endif