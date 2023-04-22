#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "ServerBlock.hpp"
# include "LimitExcept.hpp"

class LocationBlock : public ServerBlock {

	private :
		std::string		_path;
		LimitExcept		_limittExcept;
		

	public :
		LocationBlock(const ServerBlock&, const std::vector<std::string>&);

		static void blockCheck(std::ifstream&);
		void	setLocationPath(const std::vector<std::string>&);
		void	setLimitExcept(const std::string &);
		
		//	test
		void	printLocationBlock();
};

#endif