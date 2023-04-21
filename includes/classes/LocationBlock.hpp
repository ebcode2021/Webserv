#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "ServerBlock.hpp"
# include "LimitExcept.hpp"

class LocationBlock : public ServerBlock {

	private :
		std::string		_path;
		LimitExcept		_limitExcept;
		

	public :
		//LocationBlock();
		//~LocationBlock();

		static void blockCheck(std::ifstream&, Validate&);
};

#endif