#ifndef ENUM_HPP
# define ENUM_HPP

enum	blockType
{
	server,
	location,
	other,
};

enum	multiplicityOption
{
	single,
	multiple,
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
	P_DIR,
	P_NONE,
};


#endif