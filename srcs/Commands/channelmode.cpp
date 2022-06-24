#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

#define C_RPL_UMODEIS 221

#define	C_ERR_NOSUCHCHANNEL 403

#define C_ERR_USERNOTINCHANNEL 441

#define C_ERR_NEEDMOREPARAMS 461

#define C_ERR_UNKNOWNMODE 472

int		checkErrors(std::vector<std::string> & tab, int fd, Server& server)
{
	Channel*	chan;
	if ((chan = server.findChannel(tab[1])) == NULL)
	{
		server.send_reply(fd, C_ERR_NOSUCHCHANNEL, tab[1], ES, ES, ES);
		return 1;
	}
	if (tab.size() < 3)
	{
		server.send_reply(fd, C_ERR_NEEDMOREPARAMS, "MODE", ES, ES, ES);
		return 1;
	}
	if ((*tab[2].begin() != '+' && *tab[2].begin() != '-') || (tab[2].size() < 2 || tab[2].size() > 4))
	{
		return 1;
	}
	std::string mode (tab[2].begin() + 1, tab[2].end());
	if (!is_in_set(mode, CHANNEL_MODE))
	{
		std::string character(1, server.findUnknownChannelMode(mode));
		server.send_reply(fd, C_ERR_UNKNOWNMODE, character, tab[1], ES, ES);
		return 1;
	}
	if (tab.size() > 3 && chan->findClient(tab[3]) == NULL)
	{
		server.send_reply(fd, C_ERR_USERNOTINCHANNEL, tab[3], chan->getName(), ES, ES);
		return 1;
	}
	return 0;
}

int     channel_mode(const std::string &line, int fd, Server& server)
{
	COUT "CHANNEL MODE" ENDL;
	std::vector<std::string>	tab = ft_split(line, ' ');
	User*						cur = server.findMatchingUser(fd);
	Channel*					chan;
	if ((chan = server.findChannel(tab[1])) == NULL)
	{
		server.send_reply(fd, C_ERR_NOSUCHCHANNEL, tab[1], ES, ES, ES);
		return 1;
	}
	server.send_reply(fd, C_RPL_UMODEIS, chan->getMode(), ES, ES, ES);
	return 0;
}
