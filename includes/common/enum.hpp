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

enum ReadMode
{
	R_HEADER,
	R_IDENTITY,
	R_CHUNKED,
	END,
};

enum SendMode
{
	S_WAIT,
	S_CLIENT,// client
	S_PROCESS, // process
};

enum	PathType
{
	P_FILE,
	P_DIR,
	P_NONE,
};

enum	SockMode
{
	SERVER,
	CLIENT
};


#endif