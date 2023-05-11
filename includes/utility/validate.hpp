#ifndef VALIDATE_HPP
# define VALIDATE_HPP

#include "webserv.hpp"

class	Validate
{
	private :
		std::map<std::string, serverIndications>		_serverIndications;
		std::map<std::string, locationIndications>		_locationIndications;
		std::map<std::string, limitExceptIndications>	_limitExceptIndications;
		std::map<std::string, serverIndications>		_ServerType;
		std::map<std::string, locationIndications>		_LocationType;
		std::map<std::string, limitExceptIndications>	_LimitExceptType;
		std::map<std::string, unsigned short>			_originServerMap;
		std::map<std::string, unsigned short>			_originLocationMap;
		std::map<std::string, unsigned short>			_originLimitExceptMap;
		std::map<std::string, unsigned short>			_serverMap;
		std::map<std::string, unsigned short>			_locationMap;
		std::map<std::string, unsigned short>			_limitExceptMap;

	public :
		/* constructor */
		Validate();

		/* initialize */
		void					initBlockType();

		/* getter, setter */
		serverIndications		getServerType(const std::string& indication);
		locationIndications		getLocationType(const std::string& indication);
		limitExceptIndications	getLimitExceptType(const std::string& indication);
		void					setServerType();
		void					setLocationType();
		void					setLimitExceptType();

		/* checker */
		static fileMode			argumentCheck(int, char *[]);
		static bool				braceCheck(std::vector<std::string>, std::string);
		static void				extensionCheck(char *);
		static void				propertyCntCheck(std::ifstream&,std::vector<std::string>);

		/* decrement properites */
		bool					decrementServerCounter(std::string);
		bool					decrementLocationCounter(std::string);
		bool					decrementLimitExceptCounter(std::string);

		/* find */
		serverIndications		findServerIndication(std::vector<std::string>);
		locationIndications		findLocationIndication(std::vector<std::string>);
		limitExceptIndications	findLimitExceptIndication(std::vector<std::string>);

		/* reset */
		void					resetServerIndicationList();
		void					resetLocationIndicationList();
		void					resetLimitExceptIndicationList();

		/* mapping */
		std::map<std::string, serverIndications>		mappingServerIndications(std::map<std::string, unsigned short>&);
		std::map<std::string, locationIndications>		mappingLocationIndications(std::map<std::string, unsigned short>&);
		std::map<std::string, limitExceptIndications>	mappingLimitExceptIndications(std::map<std::string, unsigned short>&);


};

#endif