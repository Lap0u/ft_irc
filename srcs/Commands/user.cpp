#include "../../headers/Commands.hpp"

int		checkUserErrors(const std::vector<std::string> & split, int fd, Server& server)
{
	User *cur = server.findMatchingUser(fd);
	if (split.size() < 5) //not enough arguments
	{
		server.send_reply(fd, 461, "USER", ES, ES, ES);
		return 1;
	}
	if (cur && cur->getUserName().empty() != 1) //user is already registered
	{
		server.send_reply(fd, 462, ES, ES, ES, ES);
		return 1;
	}
	return 0;
}

int		user(const std::string &line, int fd, Server& server)
{
	COUT "Pointeur user fonction" ENDL;

	std::vector<std::string> split = ft_split(line, ' ');
	std::string real_name = split[4];
	real_name.erase(real_name.begin());

	if (checkUserErrors(split, fd, server) == 1)
		return 1;
	User *cur = server.findMatchingUser(fd);
	if (cur == NULL)//user is not made to create a new user, just add infos during connection
		return 0;
	cur->setUserName(split[1]);
	//set les modes??
	for (std::vector<std::string>::iterator it = split.begin() + 5; it != split.end(); it++)
		real_name += " " + *it;
	cur->setRealName(real_name);
	server.send_reply(fd, 001, cur->getNick(), cur->getUserName(), server.getServerName(), ES);
	server.send_reply(fd, 002, server.getServerName(), server.getVersion(), ES, ES);
	server.send_reply(fd, 003, server.getDate(), ES, ES, ES);
	server.send_reply(fd, 004, server.getServerName(), server.getVersion(), USER_MODE, CHANNEL_MODE);
	return 2;
}
