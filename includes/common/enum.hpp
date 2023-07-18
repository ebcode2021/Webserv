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
	R_LINE,
	R_HEADER,
	R_BODY,
	R_END,
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
	M_SERVER,
	M_CLIENT
};


#endif