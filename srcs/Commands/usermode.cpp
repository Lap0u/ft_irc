#include "../../headers/Commands.hpp"

int		checkError(int fd, Server& server, std::string mode_read,
					std::vector<std::string> word)
{
	const std::string	user_mode(USER_MODE);
	User*				cur = server.findMatchingUser(fd);

	if (word.size() < 3)
	{
		server.send_reply(fd, 461, "MODE", ES, ES, ES); //ERR_NEEDMOREPARAMS
		return 1;
	}
	if ((word[2][0] != '+' && word[2][0] != '-')
		|| word[2].size() != 2 || word.size() > 3)
		return 1;
	if (!is_in_set(mode_read, user_mode))
	{
		server.send_reply(fd, 501, ES, ES, ES, ES); //ERR_UMODEUNKNOWNFLAG
		return 1;
	}
	if (!server.getUser(word[1]))
		return 1;
	if (!cur->isOperator() && word[1] != cur->getNick())
	{
		server.send_reply(fd, 502, ES, ES, ES, ES); //ERR_USERSDONTMATCH
		return (1);
	}
	return 0;
}

int    mode(const std::string &line, int fd, Server& server)
{
	std::vector<std::string>	word = ft_split(line, ' ');
	User* 						cur = server.findMatchingUser(fd);

    if (cur && !cur->isRegistered())
		return 1;
	std::string mode (word[2].begin() + 1, word[2].end());

	if (word.size() > 1 && server.check_first_char_channel(word[1]) == 0)
		return (channel_mode(line, fd, server));
	if (checkError(fd, server, mode, word))
		return (1);
	User*	target = server.getUser(word[1]);

	target->updateMode(word[2][0], word[2][1], cur->isOperator());
	server.send_reply(target->getSocket(), 221, target->getMode(), ES, ES, ES); // RPL_UMODEIS
    return 0;
}
