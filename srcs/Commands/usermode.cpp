#include "../../headers/Commands.hpp"

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
	const std::string			user_mode("aiwroOs");
	std::vector<std::string>	word = ft_split(line, ' ');

	(void)server;
	if (word.size() == 3)
		pos = 2;
	if (word.size() < 2 || word.size() > 3)
	{
		server.send_reply(fd, 461, "MODE", "", "", ""); //ERR_NEEDMOREPARAMS
		return 1;
	}
	if ((*word[pos].begin() != '+' && *word[pos].begin() != '-')
		|| word[pos].size() < 2)
	{
		server.send_reply(fd, 501, "", "", "", ""); //ERR_NEEDMOREPARAMS
		return 1;
	}
	std::string mode_read (word[pos].begin() + 1, word[pos].end());

	for (std::string::iterator it = mode_read.begin(); it != mode_read.end(); ++it)
	{
		if (user_mode.find(*it) == std::string::npos)
		{
			std::cout << "Error: + - "<< std::endl;
			server.send_reply(fd, 501, "", "", "", ""); //ERR_NEEDMOREPARAMS
			return (1); //ERR_UMODEUNKNOWNFLAG
		}
	}

	COUT "REPL 221" ENDL;
	server.send_reply(fd, 221, "", "", "", ""); // RPL_UMODEIS
    return 0; //RPL_UMODEIS
}

