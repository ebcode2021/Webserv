#ifndef INDICATION_HPP
# define INDICATION_HPP

#include <map>
#include <string>
#include <enum.hpp>

enum locationIndications
{
	l_not_found,
	l_limit_except,
	l_autoindex,
	l_client_max_body_size,
	l_client_body_temp_path,
	l_error_page,
	l_index,
	l_root,
	l_none,
};

enum serverIndications
{
	s_not_found,
	s_location,
	s_listen,
	s_server_name,
	s_error_page,
	s_client_max_body_size,
	s_client_body_temp_path,
	s_autoindex,
	s_index,
	s_root,
	s_none,
};

#endif