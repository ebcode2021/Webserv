#ifndef ENUM_HPP
# define ENUM_HPP

enum	blockType
{
	server,
	location,
	other,
};

enum	status
{
	off,
	on,
};

enum	fileMode
{
	fail,
	success,
	test,
};

enum	multiplicityOption
{
	single,
	multiple,
};

enum	Method
{
	GET,
	POST,
	DELETE,
};

enum readMode
{
	HEADER,
	IDENTITY,
	CHUNKED,
	END,
};

enum	PathType
{
	P_FILE,
	P_DIRECTORY,
	P_NONE,
};

#endif