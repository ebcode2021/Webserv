#include "webserv.hpp"
#include "Config.hpp"
#include "KqueueHandler.hpp"
#include "SocketEventHandler.hpp"
#include "HttpResponse.hpp"
#include "SessionStorage.hpp"
#include "Server.hpp"

int	main(int argc, char *argv[])
{
	if (Config::fileCheck(argc, argv) == true)
	{
		Server server(argv[1]);
		server.run();
	}
	return (0);
}