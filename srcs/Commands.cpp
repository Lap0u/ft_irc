#include "../headers/Commands.hpp"

int		cap(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur cap fonction" ENDL;
	return 2;
}
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
	COUT "Pointeur nick fonction" ENDL;
	return 2;
}
int		user(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur user fonction" ENDL;
	User* user_new = new User(fd, "nick", "name", "pass", "mode");
	if (server.addUser(user_new) == true)
		server.addSocket(fd, POLLIN);
	server.send_reply(fd, 001, "nick", "", "", "");
	server.send_reply(fd, 002, "servername", "ver", "", "");
	server.send_reply(fd, 003, "Date", "", "", "");
	server.send_reply(fd, 004, "servername", "version", "usr_mod", "chan_mod");
	return 2;
}

int		oper(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur oper fonction" ENDL;
	return 2;
}

int    mode(const std::string &line, int fd, Server& server)
{
	COUT line ENDL;
	(void)fd;
	(void)server;
	COUT "Pointeur mode" ENDL;

    return 2;
}

int    whois(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur whois" ENDL;

    return 2;
}

int    ping(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur ping" ENDL;

    return 2;
}

