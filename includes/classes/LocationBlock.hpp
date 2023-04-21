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
		LocationBlock(const ServerBlock&, const std::string&);

		static void blockCheck(std::ifstream&);
		void	setLocationPath(const std::vector<std::string>&);
		void	setLimitExcept(const std::vector<std::string> &, size_t *);
};

#endif