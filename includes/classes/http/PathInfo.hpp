#ifndef PATH_INFO_HPP
# define PATH_INFO_HPP

# include "webserv.hpp"
# include "LocationBlock.hpp"

class LocationBlock;
class ErrorPage;

class PathInfo
{
	private :
		std::string		_path;
		PathType		_pathType;
		std::string		_fileType;  //*
		bool			_access;
		bool			_autoIndex; //*

	public :
		// constructor
		PathInfo();
		PathInfo(std::string, LocationBlock &);
		PathInfo(std::string);

		// getter
		PathType		getPathType() const;
		std::string		getFileType() const;
		std::string		getPath() const;
		bool			getAccess() const;
		bool			getAutoIndex() const;

		// setter
		void			setAutoIndex(bool);
		void			setFileType(std::string type);


		// print
		void			print();

};
#endif
