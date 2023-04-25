#ifndef VALIDATE_HPP
# define VALIDATE_HPP

#include "webserv.hpp"




class	Validate
{
	private :
		std::map<std::string, locationIndications>	_locationIndications;
		std::map<std::string, serverIndications>	_serverIndications;
		std::map<std::string, unsigned short>		_originServerMap;
		std::map<std::string, unsigned short>		_originLocationMap;
		std::map<std::string, unsigned short>		_serverMap;
		std::map<std::string, unsigned short>		_locationMap;

	public :
		/* constructor */
		Validate();

		/* checker */
		static fileMode	argumentCheck(int, char *[]);
		static void		braceCheck(std::ifstream&, std::string);
		static void		propertyCntCheck(std::ifstream&,std::vector<std::string>);
		static void		endsWithSemicolon(std::ifstream&, std::string);
		static void		extensionCheck(char *);
		//bool			requiredDataCheck();

		/* decrement properites */
		void			decrementServerCounter(std::ifstream&, std::string);
		void			decrementLocationCounter(std::ifstream&, std::string);
		/* file form check */
		static void isNumeric(std::ifstream&, std::vector<std::string>); //listen, client_max_body_size
		static void	isStringList(std::ifstream&, std::vector<std::string>); //server_name
		static void isErrorPageForm(std::ifstream&, std::vector<std::string>); //error_page
		static void	isPathList(std::ifstream&, std::vector<std::string>, multiplicityOption); // root, temp_path(1개만 가능), index(여러개가능)
		static void	isStatus(std::ifstream&, std::vector<std::string>); //autoIndex

		/* find */
		serverIndications	findServerIndication(std::vector<std::string>);
		locationIndications	findLocationIndication(std::vector<std::string>);

		/* reset */
		void		resetServerIndicationList();
		void		resetLocationIndicationList();

};


#endif