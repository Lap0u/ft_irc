#include "../../headers/Commands.hpp"

int	checkNickInSet(const std::string &nick)
{
	if (nick == "Pierre")
		return 1;
	return 0;
}

int	checkNickDoublon(const std::string &nick, Server& server)
{
	return (!server.isUserUnique(nick));
}

int	checkNickDelay(const std::string &nick, Server& server)
{
	if (nick == "Pierre")
		return 1;
	return 0;
}

int	checkNickRestricted(const std::string &nick, Server& server)
{
	if (nick == "Pierre")
		return 1;
	return 0;
}

int		checkNickErrors(const std::string &nick, int fd, Server& server, int size)
{
	if (size < 2)//nick provided
	{
		server.send_reply(fd, 431, ES, ES, ES, ES);
		return 1;
	}
	if (checkNickInSet(nick) == -1) //nick respect nickname allowed characters
	{
		server.send_reply(fd, 432, nick, ES, ES, ES);
		return 1;
	}
	if (checkNickDoublon(nick, server) == -1)//nick is not doublon
	{
		server.send_reply(fd, 433, nick, ES, ES, ES);
		return 1;
	}
	if (checkNickDelay(nick, server) == -1)//user has no delay to change nick again
	{
		server.send_reply(fd, 437, nick, ES, ES, ES);
		return 1;
	}
	if (checkNickRestricted(nick, server) == -1)//user is allowed to change (mode)
	{
		server.send_reply(fd, 484, ES, ES, ES);
		return 1;
	}
	return 0;
}

int		nick(const std::string &line, int fd, Server& server)
{
	std::vector<std::string>splited = ft_split(line, ' ');
	if (checkNickErrors(splited[1], fd, server) == 1, splited.size())
		return 1;
	COUT "Pointeur nick fonction" ENDL;
	server.send_reply(fd, 431, ES, ES, ES, ES);
	return 2;
}
