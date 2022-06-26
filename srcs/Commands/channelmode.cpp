#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

#define C_RPL_UMODEIS 221

#define	C_ERR_NOSUCHCHANNEL 403

#define C_ERR_USERNOTINCHANNEL 441

#define C_ERR_NEEDMOREPARAMS 461

#define C_ERR_UNKNOWNMODE 472

#define C_ERR_CHANOPRIVSNEEDED 482

#define TYPE_A
#define TYPE_B
#define TYPE_C
#define TYPE_D USER_MODE

//	o - give/take channel operator privilege;								// PARAMS
//  v - give/take the voice privilege;										// PARAMS

//	a - toggle the anonymous channel flag;									// NO PARAM
//	i - toggle the invite-only channel flag;								// NO PARAM
//	m - toggle the moderated channel;										// NO PARAM
//	n - toggle the no messages to channel from clients on the outside;
//	q - toggle the quiet channel flag;										// NO PARAM
//	p - toggle the private channel flag;									// NO PARAM
//	s - toggle the secret channel flag;										// NO PARAM
//	r - toggle the server reop channel flag;
//	t - toggle the topic settable by channel operator only flag;			// NO PARAM

//	k - set/remove the channel key (password); 								// 1 PARAM
//	l - set/remove the user limit to channel;								// 1 PARAM

//	b - set/remove ban mask to keep users out;											// PARAMS
//	e - set/remove an exception mask to override a ban mask;							// PARAMS
//	I - set/remove an invitation mask to automatically override the invite-only flag;

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
	if (tab.size() < 3)
	{
		server.send_reply(fd, C_ERR_NEEDMOREPARAMS, "MODE", ES, ES, ES);
		return 1;
	}
	if (cur->isChanOp() == false)
	{
		server.send_reply(fd, C_ERR_CHANOPRIVSNEEDED, chan->getName(), ES, ES, ES);
		return 1;
	}
	unsigned int i = 0;
	while (i < tab.size())
	{
		checkErrors(tab, fd, server);
	}
	server.send_reply(fd, C_RPL_UMODEIS, chan->getMode(), ES, ES, ES);
	return 0;
}
