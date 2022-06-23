#include "../../headers/Commands.hpp"

/**
 * @brief 
 * 
 * Mandatory :
 * r - restricted user connection;
 * o - operator flag; // server_operator
 * O - local operator flag; // channel_operator
 * 
 * Optionals :
 * i - marks a users as invisible; 
 * w - user receives wallops;
 * 
 * Obsoletes :
 * s - marks a user for receipt of server notices.
 * a - user is flagged as away;
 * 
 */

int		checkError(int fd, Server& server, std::vector<std::string> word,
					int pos, std::string mode_read)
{
	const std::string	user_mode(USER_MODE);
	User*				cur = server.findMatchingUser(fd);

	if (word.size() < 2 || word.size() > 3)
	{
		server.send_reply(fd, 461, "MODE", ES, ES, ES); //ERR_NEEDMOREPARAMS
		return 1;
	}
	if ((*word[pos].begin() != '+' && *word[pos].begin() != '-')
		|| word[pos].size() < 2)
		return 1;
	if (!is_in_set(mode_read, user_mode))
	{
		server.send_reply(fd, 501, ES, ES, ES, ES); //ERR_UMODEUNKNOWNFLAG
		return 1;
	}
	if (word.size() == 3 && !server.getUser(word[1]))
		return 1;
	if (!cur->isOperator() && word.size() == 3
			&& word[1].compare(cur->getNick()) != 0 )
	{
		server.send_reply(fd, 502, ES, ES, ES, ES); //ERR_USERSDONTMATCH
		return (1);
	}
	return 0;
}

int    mode(const std::string &line, int fd, Server& server)
{
	int							pos = 1;
	std::vector<std::string>	word = ft_split(line, ' ');
	User* 						cur = server.findMatchingUser(fd);
    if (cur)
    {
        if (!cur->isRegistered())
            return 1;
    }
	if (word.size() == 3)
		pos = 2;
	std::string mode (word[pos].begin() + 1, word[pos].end());
	if (word.size() > 1 && server.check_first_char_channel(word[1]) == 0)
		return (channel_mode(line, fd, server));
	if (checkError(fd, server, word, pos, mode))
		return (1);
	if (word.size() == 3)
		cur = server.getUser(word[1]);
	cur->updateMode(mode, *word[pos].begin());
	server.send_reply(fd, 221, cur->getMode(), ES, ES, ES); // RPL_UMODEIS
    return 0;
}
