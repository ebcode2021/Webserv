#ifndef PATH_INFO_HPP
# define PATH_INFO_HPP

# include "webserv.hpp"
# include "HttpException.hpp"

class LocationBlock;
class ErrorPage;


enum	PathType
{
	P_FILE,
	P_DIRECTORY,
	P_NONE,
};

enum	FileType
{
	F_HTML,
	F_JPG,
	F_NONE,
};

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
		PathType	getPathType() const;
		std::string	getFileType() const;
		std::string	getPath() const;
		bool		getAccess() const;
		void		setAutoIndex(bool);
		void		autoIndexOn() {(this->_autoIndex = true);};
		void		setReturnPage(const std::string&);
		std::string	getReturnPage(){return(this->_returnPage);};

		// method
		void		validatePath();
		bool		isValidDirectory();
		bool		validateDirectoryIndex();
		std::string selectErrorPage(HttpStatus&, const std::vector<ErrorPage>);

		// private method
		PathType		determinePathType();
		std::string		determineFileType();
		bool			isAccess();
		static bool		isFile(std::string&);



		// exception
		void			validatePathInfo(LocationBlock&);
		// print
		void			printPathInfo();
};
#endif
