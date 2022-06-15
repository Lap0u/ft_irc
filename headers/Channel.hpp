#pragma once

#include "Irc.hpp"
#include "Server.hpp"

class Channel
{
    private:
    
    int						_socket;
    std::string             _name;
    std::string	            _mode;
    Server::userVector      _clients;

    public:

    Channel();
    Channel();
    virtual ~Channel();

};