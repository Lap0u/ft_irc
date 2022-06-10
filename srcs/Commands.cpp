#include "../headers/Commands.hpp"

int		pass(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur pass fonction" ENDL;
	return 2;
}
int		nick(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur fonction" ENDL;
	return 2;
}
int		oper(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur fonction" ENDL;
	return 2;
}
int		user(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur fonction" ENDL;
	return 2;
}

int    mode(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur mode" ENDL;

    return 2;
}

// int    whois(const std::string &line, int fd, Server& server)
// {
// 	(void)line;
// 	(void)fd;
// 	(void)server;
// 	COUT "Pointeur whois" ENDL;

//     return 2;
// }

int    ping(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur ping" ENDL;

    return 2;
}

