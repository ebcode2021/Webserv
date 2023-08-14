#ifndef ENUM_HPP
# define ENUM_HPP

enum	blockType
{
	server,
	location,
	other,
};

enum MethodType
{
	GET,
	POST,
	DELETE,
	OTHER,
};

enum	multiplicityOption
{
	single,
	multiple,
};

enum ReadPhase
{
	R_LINE,
	R_HEADER,
	R_BODY,
	R_END,
};

enum SendPhase
{
	S_LINE,
	S_HEADER,
	S_BODY,
	S_END,
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