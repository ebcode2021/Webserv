#ifndef PATH_INFO_HPP
# define PATH_INFO_HPP

# include "webserv.hpp"
# include "ResponseException.hpp"

class LocationBlock;
class ErrorPage;

class PathInfo
{
	private :
		PathType		_pathType;
		std::string		_fileType;
		std::string		_path;
		bool			_access;
		bool			_autoIndex;
		std::string		_returnPage;

	public :
		// constructor
		PathInfo();
		PathInfo(const std::string&);

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
		void			processGetRequest(LocationBlock&);
		void			processDeleteRequest();

		PathType		determinePathType();
		std::string		determineFileType();
		bool			isAccess();
		bool			isAccess(std::string&);
		static bool		isFile(std::string&);
		void			setReturnPageByError(const std::vector<ErrorPage>&, const int);
		void			setReturnPageBySession(const std::string&, const std::string&);

		// validate
		void			validatePath();

		// print
		void			printPathInfo();

};
#endif
