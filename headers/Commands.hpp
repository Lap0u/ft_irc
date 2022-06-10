#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include "Irc.hpp"
#include "Server.hpp"

class Server;

int     pass(const std::string &line, int fd, Server& server);
int     nick(const std::string &line, int fd, Server& server);
int     oper(const std::string &line, int fd, Server& server);
int     user(const std::string &line, int fd, Server& server);
int     usermod(const std::string &line, int fd, Server& server);



#endif