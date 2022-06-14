#include "../../headers/Commands.hpp"

int		checkError(int fd, Server& server, std::vector<std::string> word,
					int pos, std::string mode_read)
{
	const std::string			user_mode(USER_MODE);

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
	return 0;
}

int    mode(const std::string &line, int fd, Server& server)
{
	// a - user is flagged as away;
	// i - marks a users as invisible;
	// w - user receives wallops;
	// r - restricted user connection;
	// o - operator flag;
	// O - local operator flag;
	// s - marks a user for receipt of server notices.
	int							pos = 1;
	std::vector<std::string>	word = ft_split(line, ' ');
	User*						cur = NULL;

	if (word.size() == 3)
		pos = 2;
	std::string mode_read (word[pos].begin() + 1, word[pos].end());

	if (checkError(fd, server, word, pos, mode_read))
		return (1);
	if (word.size() == 3)
		cur = server.getUser(word[1]);
	else
		cur = server.findMatchingUser(fd);
	

	server.send_reply(fd, 221, mode_read, "", "", ""); // RPL_UMODEIS
    return 0; //RPL_UMODEIS
	/**
	 * 502    ERR_USERSDONTMATCH
              ":Cannot change mode for other users"

         - Error sent to any user trying to view or change the
           user mode for a user other than themselves
	 * 
	 */
}

