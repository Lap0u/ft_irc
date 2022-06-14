#include "../../headers/Commands.hpp"

int	checkNickInSet(const std::string &nick)
{
	if (nick.size() > 9)
		return 1;
	if (is_in_set(nick, NICK_CHAR, 8) == false || is_in_set(&nick[8], NICK_LAST_CHAR, 1) == false)
		return 1;
	return 0;
}

int	checkNickDoublon(const std::string &nick, Server& server)
{
	return (!server.isUserUnique(nick));
}

int	checkNickDelay(User *newUser)
{
	if (newUser == NULL)
		return 0;
	//check le delay du USER
	return 0;
}

int	checkNickRestricted(User *newUser)
{
	if (newUser == NULL)
		return 0;
	std::string mode = newUser->getMode();
	if (!(mode.find('r') == std::string::npos))
		return 1;
	return 0;
}

int		checkNickErrors(const std::string &nick, int fd, Server& server, int size)
{
	User* newly = server.findMatchingUser(fd);
	if (size < 2)//nick not provided
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
	if (checkNickDelay(newly) == -1)//user has no delay to change nick again
	{
		server.send_reply(fd, 437, nick, ES, ES, ES);
		return 1;
	}
	if (checkNickRestricted(newly) == -1)//user is allowed to change (mode)
	{
		server.send_reply(fd, 484, ES, ES, ES, ES);
		return 1;
	}
	if (newly == NULL)
	{
		newly = new User(fd, nick, ES, ES, ES);
		server.addUser(newly);
		server.addSocket(fd, POLLIN);
		DEB "new user added, nick : " << nick ENDL;
	}
	else
		newly->setNick(nick);
	return 0;
}

int		nick(const std::string &line, int fd, Server& server)
{
	DEB "Pointeur nick fonction, line : " << line ENDL;
	std::vector<std::string>splited = ft_split(line, ' ');
	if (checkNickErrors(splited[1], fd, server, splited.size()) == 1)
		return 1;
	return 2;
}
