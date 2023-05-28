#ifndef PATH_INFO_HPP
# define PATH_INFO_HPP

# include "webserv.hpp"
# include "LocationBlock.hpp"
# include "HttpException.hpp"

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
		FileType		_fileType;
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
		FileType	getFileType() const;
		std::string	getPath() const;
		bool		getAccess() const;
		void		setAutoIndex(bool);
		void		autoIndexOn() {(this->_autoIndex = true);};
		std::string	setReturnPage(const std::string&);

		// method
		void		validatePath();
		bool		isValidDirectory();
		bool		validateDirectoryIndex();
		std::string selectErrorPage(HttpStatus&, const std::vector<ErrorPage>);

		// private method
		PathType		determinePathType();
		FileType		determineFileType();
		bool			isAccess();
		bool			isFile(std::string&);



		// exception
		void			validatePathInfo(LocationBlock& locationBlock);
		// print
		void			printPathInfo();
};
#endif
