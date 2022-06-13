#include "../../headers/Commands.hpp"

// int		checkNickErrors(const std::string &nick, int fd, Server& server)
// {
// 	(void)nick;
// 	return 1
// }

int		nick(const std::string &line, int fd, Server& server)
{
	std::vector<std::string>splited = ft_split(line, ' ');
	if (splited.size() < 2)
	{
		server.send_reply(fd, 431, ES, ES, ES, ES);
	}
	// if (checkNickErrors(splited[1], fd, server) == 1)
	// 	return 1;
	COUT "Pointeur nick fonction" ENDL;
	server.send_reply(fd, 431, ES, ES, ES, ES);
	return 2;
}
