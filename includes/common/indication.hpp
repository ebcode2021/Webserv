#ifndef INDICATION_HPP
# define INDICATION_HPP

#include <unordered_map>
#include <string>
#include <enum.hpp>

enum class	locationIndications
{
	none,
	limit_except,
	autoindex,
	client_max_body_size,
	client_body_temp_path,
	error_page,
	index,
	root,
	not_found,
};

enum class	serverIndications
{
	none,
	location,
	listen,
	server_name,
	error_page,
	client_max_body_size,
	client_body_temp_path,
	autoindex,
	index,
	root,
	not_found,
};

const std::unordered_map<std::string, locationIndications> LocationType =
{
	{"limit_except", locationIndications::limit_except},
	{"autoindex", locationIndications::autoindex},
	{"client_max_body_size", locationIndications::client_max_body_size},
	{"client_body_temp_path", locationIndications::client_body_temp_path},
	{"error_page", locationIndications::error_page},
	{"index", locationIndications::index},
	{"root", locationIndications::root},
};

const std::unordered_map<std::string, serverIndications> ServerType =
{
	{"location", serverIndications::location},
	{"listen", serverIndications::listen},
	{"server_name", serverIndications::server_name},
	{"errpr_page", serverIndications::error_page},
	{"client_max_body_size", serverIndications::client_max_body_size},
	{"client_body_temp_path", serverIndications::client_body_temp_path},
	{"autoindex", serverIndications::autoindex},
	{"index", serverIndications::index},
	{"root", serverIndications::root},
};

#endif