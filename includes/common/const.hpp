#ifndef CONST_HPP
# define CONST_HPP

#include "webserv.hpp"

#define SOCKET_ERROR	-1
#define INVALID_SOCKET	-1

/* Symbols */
const std::string	SP = " ";
const std::string	CRLF = "\r\n";
const std::string	DOUBLE_CRLF = "\r\n\r\n";
const std::string	SEMICOLON = ";";
const std::string	OPEN_BRACE = "{";
const std::string	CLOSE_BRACE = "}";
const std::string	WHITESPACE = " \t\n\v\f\r";
const std::string	KEEPALIVE = "keep-alive";

/* Size */
const std::size_t	EVENT_SIZE = 256;
const std::size_t	BUFSIZE = 512;
const std::size_t	CLIENT_BODY_SIZE = 1048576;

/* Related to HTTP */
const std::string	HTTP_VERSION = "HTTP/1.1";
const std::string	FAVICON_URL = "/favicon.ico";

static const	std::string METHODS[] = {
	"GET", "POST", "DELETE"
};

static const	std::string REQUEST_HEADERS[] = {
	"Host", "User-Agent", "Connection", "Content-Type", "Content-Length", "Transfer-Encoding", "Cookie"
};

static const	std::string RESPONSE_HEADERS[] = {
	"Date", "Server", "Content-Length", "Content-Type", "Set-Cookie", "Transfer-Encoding"
};

const size_t		METHODS_SIZE = sizeof(METHODS) / sizeof(std::string);
const size_t		REQUEST_HEADER_SIZE = sizeof(REQUEST_HEADERS) / sizeof(std::string);
const size_t		RESPONSE_HEADER_SIZE = sizeof(RESPONSE_HEADERS) / sizeof(std::string);

/* Session */
static const size_t			SESSION_ID_LENGTH = 16;
static const std::string	SESSION_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
static const size_t			SESSION_CHARS_LENGTH = SESSION_CHARS.size();
static const size_t			DEFAULT_SESSION_DURATION = 3600;

#endif