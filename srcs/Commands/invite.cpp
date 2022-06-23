#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

int		checkError(int fd, Server& server,
	std::vector<std::string>& word, User *&cur)
{
	Channel *channel = server.findChannel(word[2]);

	if (word.size() < 3)
	{
		server.send_reply(fd, 461, "INVITE", ES, ES, ES); //ERR_NEEDMOREPARAMSreturn 1;
		return 1;
	}
	if (server.getUser(word[1]) == NULL)
	{
		server.send_reply(fd, 401, ES, ES, ES, ES); //ERR_NOSUCHNICK
		return 1;
	}
	if (!channel)
		return 1;
	if (channel->findClient(word[1]))
	{
		server.send_reply(fd, 443, word[1], word[2], ES, ES); //ERR_USERONCHANNEL
		return 1;
	}
	if (channel->findClient(cur->getNick()) == NULL)
	{
		server.send_reply(fd, 442, word[2], ES, ES, ES); //ERR_NOTONCHANNEL
		return 1;
	}
	if (cur->getMode().find('o') == std::string::npos) // O
	{
		server.send_reply(fd, 482, word[2], ES, ES, ES); //ERR_CHANOPRIVSNEEDED
		return 1;
	}
	return 0;
}

int     invite(const std::string &line, int fd, Server& server)
{
	std::vector<std::string>	word = ft_split(line, ' ');
	User*						cur = server.findMatchingUser(fd);
	if (cur)
	{
		if (!cur->isRegistered())
			return 1;
	}
	if (checkError(fd, server, word, cur))
		return 1;
	server.send_reply(fd, 341, word[2], word[1], ES, ES); //RPL_INVITING
	return 0;
}
