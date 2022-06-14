#include "../../headers/Commands.hpp"

/**
 * @brief 
 * a - user is flagged as away;
 * i - marks a users as invisible;
 * w - user receives wallops;
 * r - restricted user connection;
 * o - operator flag;
 * O - local operator flag;
 * s - marks a user for receipt of server notices.
 */


int		checkError(int fd, Server& server, std::vector<std::string> word,
					int pos, std::string mode_read)
{
	const std::string	user_mode(USER_MODE);
	User*				cur = server.findMatchingUser(fd);

	if (word.size() < 2 || word.size() > 3)
	{
		server.send_reply(fd, 461, "MODE", "", "", ""); //ERR_NEEDMOREPARAMS
		return 1;
	}
	if ((*word[pos].begin() != '+' && *word[pos].begin() != '-')
		|| word[pos].size() < 2)
	{
		server.send_reply(fd, 501, "", "", "", ""); //ERR_UMODEUNKNOWNFLAG
		return 1;
	}
	if (!is_in_set(mode_read, user_mode))
	{
		server.send_reply(fd, 501, "", "", "", ""); //ERR_UMODEUNKNOWNFLAG
		return 1;
	}
	if (word.size() == 3 && server.getUser(word[1]) == NULL)
		return 1;
	if (!cur->isOperator() && word.size() == 3
			&& word[1].compare(cur->getNick()) != 0)
	{
		server.send_reply(fd, 502, "", "", "", ""); //ERR_USERSDONTMATCH
		return (1);
	}
	return 0;
}

int    mode(const std::string &line, int fd, Server& server)
{
	int							pos = 1;
	User*						cur = NULL;
	std::vector<std::string>	word = ft_split(line, ' ');

	DEB word[1] ENDL;
	if (word.size() == 3)
		pos = 2;
	std::string mode (word[pos].begin() + 1, word[pos].end());
	
	if (checkError(fd, server, word, pos, mode))
		return (1);
	cur = server.findMatchingUser(fd);
	if (word.size() == 3)
		cur = server.getUser(word[1]);
	cur->updateMode(mode, *word[pos].begin());
	server.send_reply(fd, 221, cur->getMode(), "", "", ""); // RPL_UMODEIS
    return 0;
}
