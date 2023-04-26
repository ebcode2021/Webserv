#ifndef VALIDATE_HPP
# define VALIDATE_HPP

#include "webserv.hpp"

class	Validate
{
	private :
		std::map<std::string, serverIndications>	_serverIndications;
		std::map<std::string, locationIndications>	_locationIndications;
		std::map<std::string, serverIndications>	_ServerType;
		std::map<std::string, locationIndications>	_LocationType;
		std::map<std::string, unsigned short>		_originServerMap;
		std::map<std::string, unsigned short>		_originLocationMap;
		std::map<std::string, unsigned short>		_serverMap;
		std::map<std::string, unsigned short>		_locationMap;

	public :
		/* constructor */
		Validate();

		/* checker */
		static fileMode		argumentCheck(int, char *[]);
		static void			braceCheck(std::ifstream&, std::string);
		static void			endsWithSemicolon(std::ifstream&, std::string);
		static void			extensionCheck(char *);
		static void			propertyCntCheck(std::ifstream&,std::vector<std::string>);

		/* decrement properites */
		void				decrementServerCounter(std::ifstream&, std::string);
		void				decrementLocationCounter(std::ifstream&, std::string);

		/* getter & setter */
		serverIndications	getServerType(const std::string& indication);
		locationIndications	getLocationType(const std::string& indication);

		/* initialize */
		void				initServerAndLocationType();

		/* mapping */
		std::map<std::string, serverIndications>	mappingServerIndications(std::map<std::string, unsigned short>&);
		std::map<std::string, locationIndications>	mappingLocationIndications(std::map<std::string, unsigned short>&);

		/* file form check */
		static void 		isNumeric(std::ifstream&, std::vector<std::string>);
		static void			isStringList(std::ifstream&, std::vector<std::string>);
		static void 		isErrorPageForm(std::ifstream&, std::vector<std::string>);
		static void			isPathList(std::ifstream&, std::vector<std::string>, multiplicityOption);
		static void			isStatus(std::ifstream&, std::vector<std::string>);

		/* find */
		serverIndications	findServerIndication(std::vector<std::string>);
		locationIndications	findLocationIndication(std::vector<std::string>);

		/* reset */
		void				resetServerIndicationList();
		void				resetLocationIndicationList();

};


#endif