#ifndef SERVERINFO_HPP
# define SERVERINFO_HPP

# include "Webserv.hpp"

class ServerInfo {
    private :
        ServerBlock _serverBlock;
        std::vector<LocationBlock> locationList;

    public :
        ServerInfo();
        ~ServerInfo();
};

#endif