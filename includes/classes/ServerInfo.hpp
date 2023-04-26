#ifndef SERVERINFO_HPP
# define SERVERINFO_HPP

# include "LocationBlock.hpp"
# include "ServerBlock.hpp"


class ServerInfo {
    private :
        ServerBlock _serverBlock;
        std::vector<LocationBlock> locationList;

    public :
        ServerInfo() {};
        ServerInfo(ServerBlock&, std::vector<LocationBlock>&);

        // test
        void printServerInfo();
};

#endif