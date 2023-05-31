#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "ServerBlock.hpp"
# include "LimitExcept.hpp"

class LocationBlock : public ServerBlock
{
	private :
		std::string		_path;
		LimitExcept		_limitExcept;

	public :
		LocationBlock(){};
		LocationBlock(const ServerBlock &);
		LocationBlock(const ServerBlock&, const std::vector<std::string>&);
		//LocationBlock();
		//~LocationBlock();

		static void blockCheck(std::ifstream&, Validate&);
		void	setLocationPath(const std::vector<std::string>&);
		void	setLimitExcept(const std::string&);
		void	setPath(const std::string&);
		std::string	getPath() { return(this->_path);};
		
		//	test
		void	printLocationBlock();

		bool	isValidMethodByLimitExcept(const std::string&) {return true;};

};

#endif