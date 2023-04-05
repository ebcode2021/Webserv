#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "Webserv.hpp"

class Location {

	private :
		std::string _path;
		std::string _root;
		std::vector<std::string> _index;

	public :
		Location();
		~Location();
};

#endif