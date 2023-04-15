#ifndef SERVERLIST_HPP
# define SERVERLIST_HPP

# include "ServerInfo.hpp"

class ServerList {
    private :
        std::vector<ServerInfo> serverList;
    public :
        void    addServer(std::ifstream &);
};

#endif