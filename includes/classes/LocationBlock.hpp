#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "ServerBlock.hpp"

class LimitExcept {
	private :
		std::vector<std::string>	_methodList;
		std::string					_allow;
		std::string					_deny;
	public :
};

class LocationBlock : public ServerBlock {

	private :
		std::string		_path;
		LimitExcept		_limittExcept;
		

	public :
		static void blockCheck(std::ifstream&);
};

#endif