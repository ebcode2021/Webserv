#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "ServerBlock.hpp"
# include "LimitExcept.hpp"

class LocationBlock : public ServerBlock
{
	private :
		std::string		_path;
		LimitExcept		_limitExcept;
		std::string		_cgi_pass;

	public :
		// constructor
		LocationBlock();
		LocationBlock(const ServerBlock &);
		LocationBlock(const ServerBlock&, const std::vector<std::string>&);

		// getter
		LimitExcept	getLimitExcept() const;
		std::string	getPath() const;
		std::string getCgiPass() const;

		// setter
		void		setPath(const std::string&);
		void		setLimitExcept(const std::string&);
		void		setCgiPass(const std::string&);
		
		// checker
		static void blockCheck(std::ifstream&, Validate&);
		void		setLocationPath(const std::vector<std::string>&);

		// method
		std::string	getFullPath() const;

		// print
		void	printInfo() const;
};

#endif