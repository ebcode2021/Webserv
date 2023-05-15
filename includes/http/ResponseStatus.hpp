#ifndef STATUSCODE_HPP
# define STATUSCODE_HPP

#include "webserv.hpp"

struct HttpStatus {
	int 		statusCode;
	std::string reason;
};

static const std::map<int, std::string> httpStatusMap = {
	{ 200, "OK" },
	{ 201, "Created" },
	{ 202, "Accepted" },
	{ 400, "Bad Request" },
	{ 401, "Unauthorized" },
	{ 403, "Forbidden" },
	{ 404, "Not Found" },
	{ 405, "Method Not Allowed" },
	{ 500, "Internal Server Error" },
	{ 502, "Bad Gateway" },
	{ 503, "Service Unavailable" },
	{ 505, "HTTP Version Not Supported" }
};


// struct ResponseStatus
// {
// 	static int code[];
// 	static std::string reason[];

// 	static void	init()
// 	{
// 		int size = sizeof(statusScript) / sizeof(std::string);

// 		for (int idx = 0; idx < size; idx++)
// 		{
// 			std::vector<std::string>	splitted = split(statusScript[idx], " ");
// 			code[idx] = std::atoi(splitted[0].c_str());
// 			reason[idx] = splitted[1];
// 		}
// 	}
};

enum	StatusCodeaa
{
	// 1xx
	HTTP_STATUS_CONTINUE = 100,
	HTTP_STATUS_SWITCHING_PROTOCOLS = 101,

	// 2xx
	HTTP_STATUS_OK = 200,
	HTTP_STATUS_CREATED = 201,
	HTTP_STATUS_ACCEPTED = 202,
	HTTP_STATUS_NON_AUTHORITATIVE_INFORMATION = 203,
	HTTP_STATUS_NO_CONTENT = 204,
	HTTP_STATUS_RESET_CONTENT = 205,
	HTTP_STATUS_PARTIAL_CONTENT = 206,

	// 3xx
	HTTP_STATUS_MULTIPLE_CHOICES = 300,
	HTTP_STATUS_MOVED_PERMANENTLY = 301,
	HTTP_STATUS_FOUND = 302,
	HTTP_STATUS_SEE_OTHER = 303,
	HTTP_STATUS_NOT_MODIFIED = 304,
	HTTP_STATUS_USE_PROXY = 305,
	HTTP_STATUS_TEMPORARY_REDIRECT = 307,

	// 4xx
	HTTP_STATUS_BAD_REQUEST = 400,
	HTTP_STATUS_UNAUTHORIZED = 401,
	HTTP_STATUS_PAYMENT_REQUIRED = 402,
	HTTP_STATUS_FORBIDDEN = 403,
	HTTP_STATUS_NOT_FOUND = 404,
	HTTP_STATUS_METHOD_NOT_ALLOWED = 405,
	HTTP_STATUS_NOT_ACCEPTABLE = 406,
	HTTP_STATUS_PROXY_AUTHENTICATION_REQUIRED = 407,
	HTTP_STATUS_REQUEST_TIME_OUT = 408,
	HTTP_STATUS_CONFLICT = 409,
	HTTP_STATUS_GONE = 410,
	HTTP_STATUS_LENGTH_REQUIRED = 411,
	HTTP_STATUS_PRECONDITION_FAILED = 412,
	HTTP_STATUS_REQUEST_ENTITY_TOO_LARGE = 413,
	HTTP_STATUS_REQUEST_URI_TOO_LARGE = 414,
	HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE = 415,
	HTTP_STATUS_REQUESTED_RANGE_NOT_SATISFIABLE = 416,
	HTTP_STATUS_EXPECTATION_FAILED = 417,

	// 5xx
	HTTP_STATUS_INTERNAL_SERVER_ERROR = 500,
	HTTP_STATUS_NOT_IMPLEMENTED = 501,
	HTTP_STATUS_BAD_GATEWAY = 502,
	HTTP_STATUS_SERVICE_UNAVAILABLE = 503,
	HTTP_STATUS_GATEWAY_TIME_OUT = 504,
	HTTP_STATUS_HTTP_VERSION_NOT_SUPPORTED = 505,
};

// const int ResponseStatus::code[] = {
// 	"200",
// 	"201",
// 	"204",
// 	"400",
// 	"401",
// 	"403",
// 	"404",
// 	"500",
// 	"503",
// };

// const std::string ResponseStatus::reason[] = {
// 	"OK",
// 	"Created",
// 	"No Content"
// 	"Bad Request",
// 	"Unauthorized",
// 	"Forbidden",
// 	"Not Found",
// 	"Internal Server Error",
// 	"Service Unavailable"
// }


// throw ResponseException(C404);

// try
// {
// 	req.setHttpRequest();
// 	{
// 		throw 
// 	}
// }
// catch(std::exception &e)
// {
// 	header = http/1.1 + " " + ResopnseStats::code() + " " + ReseponseStatus::reason()
//  	body = setNotFound();
// }


/* * * * * * * * * * * * Status Code and Reason Phrase * * * * * * * * * * * */
/*
	The Status-Code element is a 3-digit integer result code of the
	attempt to understand and satisfy the request. These codes are fully
	defined in section 10. The Reason-Phrase is intended to give a short
	textual description of the Status-Code. The Status-Code is intended
	for use by automata and the Reason-Phrase is intended for the human
	user. The client is not required to examine or display the Reason-
	Phrase.

	The first digit of the Status-Code defines the class of response. 
	The last two digits do not have any categorization role. There are 5
	values for the first digit:

	- 1xx: Informational - Request received, continuing process

	- 2xx: Success - The action was successfully received,
		understood, and accepted

	- 3xx: Redirection - Further action must be taken in order to
		complete the request

	- 4xx: Client Error - The request contains bad syntax or cannot
		be fulfilled

	- 5xx: Server Error - The server failed to fulfill an apparently
		valid request
*/

#endif