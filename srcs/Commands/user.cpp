#include "../../headers/Commands.hpp"

int		user(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur user fonction" ENDL;
	User* user_new = new User(fd, "Nick", "name", "pass", std::string());
	if (server.addUser(user_new) == true)
		server.addSocket(fd, POLLIN);
	else
		delete user_new;
	server.send_reply(fd, 001, "nick", "", "", "");
	server.send_reply(fd, 002, "servername", "ver", "", "");
	server.send_reply(fd, 003, "Date", "", "", "");
	server.send_reply(fd, 004, "servername", "version", "usr_mod", "chan_mod");
	return 2;
}
