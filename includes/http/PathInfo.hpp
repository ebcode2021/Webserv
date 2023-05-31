#ifndef PATH_INFO_HPP
# define PATH_INFO_HPP

# include "webserv.hpp"
# include "ResponseException.hpp"

class LocationBlock;
class ErrorPage;

class PathInfo
{
	private :
		// variable
		PathType		_pathType;
		std::string		_fileType;
		std::string		_path;
		bool			_access;
		bool			_autoIndex;
		std::string		_returnPage;


	public :
		// constructor
		PathInfo();
		PathInfo(std::string&);

		// getter, setter
		PathType		getPathType() const;
		std::string		getFileType() const;
		std::string		getPath() const;
		std::string		getReturnPage() const;
		bool			getAccess() const;
		bool			getAutoIndex() const;
		void			setAutoIndex(bool);
		void			setReturnPage(const std::string&);

		// method
		bool			isValidDirectory();
		std::string 	selectErrorPage(HttpStatus&, const std::vector<ErrorPage>);

		// private method
		PathType		determinePathType();
		std::string		determineFileType();
		bool			isAccess();
		bool			isAccess(std::string&);
		static bool		isFile(std::string&);

		// print
		void			printPathInfo();

		// exception
		void			validatePathInfo(LocationBlock&);
};
#endif
