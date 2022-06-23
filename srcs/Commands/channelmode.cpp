#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

#define	C_ERR_NOSUCHCHANNEL 403

int		checkErrors(std::vector<std::string> & tab, int fd, Server& server)
{
	if (server.findChannel(tab[1]) == NULL)
	{
		server.send_reply(fd, C_ERR_NOSUCHCHANNEL, "MODE", ES, ES, ES); //ERR_NOSUCHCHANNEL
		return 1;
	}
	if (tab.size() < 3)
	{
		server.send_reply(fd, 461, "MODE", ES, ES, ES); //ERR_NEEDMOREPARAMS
		return 1;
	}
	else if ((*tab[2].begin() != '+' && *tab[2].begin() != '-') || tab[2].size() < 2)
		return 1;
	else if (1)
	{

	}
	return 0;
}

int     channel_mode(const std::string &line, int fd, Server& server)
{
	COUT "CHANNEL MODE" ENDL;
	std::vector<std::string>	tab = ft_split(line, ' ');
	(void)fd;
	(void)server;
	// if (checkErrors(tab, fd, server))
		// return 1;
	return 0;
}
