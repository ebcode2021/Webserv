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
		// constructor
		LocationBlock();
		LocationBlock(const ServerBlock &);
		LocationBlock(const ServerBlock&, const std::vector<std::string>&);

		// getter, setter
		LimitExcept	getLimitExcept() const;
		std::string	getPath() const;
		void		setLocationPath(const std::vector<std::string>&);
		void		setLimitExcept(const std::string&);
		void		setPath(const std::string&);
		
		// checker
		static void blockCheck(std::ifstream&, Validate&);

		// method
		bool		isValidByLimitExcept(const std::string&, const std::string&);
		std::string	getFullPath() const;

		// print
		void	printInfo();
};

#endif