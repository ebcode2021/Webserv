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

//std::map<std::string, locationIndications> LocationType;

// LocationType.insert(std::make_pair("limit_except", l_limit_except));
// LocationType.insert(std::make_pair("autoindex", l_autoindex));
// LocationType.insert(std::make_pair("client_max_body_size", l_client_max_body_size));
// LocationType.insert(std::make_pair("client_body_temp_path", l_client_body_temp_path));
// LocationType.insert(std::make_pair("error_page", l_error_page));
// LocationType.insert(std::make_pair("index", l_index));
// LocationType.insert(std::make_pair("root", l_root));

//std::map<std::string, serverIndications> ServerType;
// {
// 	{"limit_except", l_limit_except},
// 	{"autoindex", l_autoindex},
// 	{"client_max_body_size", l_client_max_body_size},
// 	{"client_body_temp_path", l_client_body_temp_path},
// 	{"error_page", l_error_page},
// 	{"index", l_index},
// 	{"root", l_root},
// };



// {
// 	{"location", s_location},
// 	{"listen", s_listen},
// 	{"server_name", s_server_name},
// 	{"error_page", s_error_page},
// 	{"client_max_body_size", s_client_max_body_size},
// 	{"client_body_temp_path", s_client_body_temp_path},
// 	{"autoindex", s_autoindex},
// 	{"index", s_index},
// 	{"root", s_root},
// };

#endif