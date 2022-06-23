#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include "Irc.hpp"
#include "Server.hpp"

class Server;

std::vector<std::string> ft_split(std::string tosplit, char delimiter);
std::vector<std::string> ft_split(std::string tosplit, std::string delimiter);

bool    is_in_set(const std::string& str, const std::string& str2);
bool    is_in_set(const std::string& str, const std::string& str2, size_t size);

int		cap(const std::string &line, int fd, Server& server);
int     pass(const std::string &line, int fd, Server& server);
int     nick(const std::string &line, int fd, Server& server);
int     oper(const std::string &line, int fd, Server& server);
int     user(const std::string &line, int fd, Server& server);
int     mode(const std::string &line, int fd, Server& server);
int     whois(const std::string &line, int fd, Server& server);
int     ping(const std::string &line, int fd, Server& server);
int     join(const std::string &line, int fd, Server& server);
int     part(const std::string &line, int fd, Server& server);
int     names(const std::string &line, int fd, Server& server);
int     privateMessage(const std::string &line, int fd, Server& server);
int     quit(const std::string &line, int fd, Server& server);
int		error(const std::string &line, int fd, Server& server);
int		topic(const std::string &line, int fd, Server& server);
int		list(const std::string &line, int fd, Server& server);

#endif