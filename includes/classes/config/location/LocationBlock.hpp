#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "ServerBlock.hpp"

class LocationBlock : public ServerBlock
{
	private :
		std::string		_path;
		std::vector<std::string>	_limitExcept;
		std::string		_cgi_pass;
		std::string		_return;

	public :
		/* constructor */
		LocationBlock();
		LocationBlock(const ServerBlock &);
		LocationBlock(const ServerBlock&, const std::vector<std::string>&);

		/* getter */
		std::vector<std::string>	getLimitExcept() const;
		std::string					getPath() const;
		std::string					getCgiPass() const;
		std::string 				getReturn() const;

		/* setter */
		void		setPath(const std::string&);
		void		setLimitExcept(const std::vector<std::string>&);
		void		setCgiPass(const std::string&);
		void		setReturn(const std::string&);
		void		setLocationPath(const std::vector<std::string>&);
		
		/* checker */
		static void blockCheck(std::ifstream&, Validate&);

		/* method */
		std::string	getFullPath() const;
		bool		isValidMethod(const std::string&);

		/* print */
		void	printInfo() const;
};

#endif