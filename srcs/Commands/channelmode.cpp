#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

#define C_RPL_CHANNELMODEIS 324

#define C_RPL_UNIQOPIS 325

#define C_RPL_INVITELIST 346
#define C_RPL_ENDOFINVITELIST 347

#define C_RPL_EXCEPTLIST 348
#define C_RPL_ENDOFEXCEPTLIST 349

#define C_RPL_BANLIST 367
#define C_RPL_ENDOFBANLIST 368

#define	C_ERR_NOSUCHCHANNEL 403

#define C_ERR_USERNOTINCHANNEL 441

#define C_ERR_NEEDMOREPARAMS 461

#define C_ERR_KEY_SET 467

#define C_ERR_UNKNOWNMODE 472

#define C_ERR_CHANOPRIVSNEEDED 482


#define TYPE_NO_PARAM "aimnqpsrt"
#define TYPE_ONE_PARAM "kl"
#define TYPE_ONE_OR_ZERO "beI"
#define TYPE_PARAMS "Oov"

//  O - give "channel creator" status;
//	o - give/take channel operator privilege;								// PARAMS
//  v - give/take the voice privilege;										// PARAMS

//	a - toggle the anonymous channel flag;									// NO PARAM
//	i - toggle the invite-only channel flag;								// NO PARAM
//	m - toggle the moderated channel;										// NO PARAM
//	n - toggle the no messages to channel from clients on the outside;		// NO PARAM
//	q - toggle the quiet channel flag;										// NO PARAM
//	p - toggle the private channel flag;									// NO PARAM
//	s - toggle the secret channel flag;										// NO PARAM
//	r - toggle the server reop channel flag;								// NO PARAM
//	t - toggle the topic settable by channel operator only flag;			// NO PARAM

//	k - set/remove the channel key (password); 								// 1 PARAM
//	l - set/remove the user limit to channel;								// 1 PARAM

//	b - set/remove ban mask to keep users out;								// PARAMS
//	e - set/remove an exception mask to override a ban mask;				// PARAMS
//	I - set/remove an invitation mask to automatically override the invite-only flag;

void	add_flag(Channel *chan, char const & mode)
{
	chan->addMode(std::string(1, mode));
	if (mode == 'a')
		chan->isAnonymous() = true;
	else if (mode == 'i')
		chan->isInviteOnly() = true;
	else if (mode == 'm')
		chan->isModerated() = true;
	else if (mode == 'n')
		chan->noMessageFromChannel() = true;
	else if (mode == 'q')
		chan->isQuiet() = true;
	else if (mode == 'p')
		chan->isPrivate() = true;
	else if (mode == 's')
		chan->isSecret() = true;
	else if (mode == 'r')
		chan->reOp() = true;
	else if (mode == 't')
		chan->topicSettableForChanOpOnly() = true;
}

void	delete_flag(Channel *chan, char const & mode)
{
	chan->delMode(std::string(1, mode));
	if (mode == 'a')
		chan->isAnonymous() = false;
	else if (mode == 'i')
		chan->isInviteOnly() = false;
	else if (mode == 'm')
		chan->isModerated() = false;
	else if (mode == 'n')
		chan->noMessageFromChannel() = false;
	else if (mode == 'q')
		chan->isQuiet() = false;
	else if (mode == 'p')
		chan->isPrivate() = false;
	else if (mode == 's')
		chan->isSecret() = false;
	else if (mode == 'r')
		chan->reOp() = false;
	else if (mode == 't')
		chan->topicSettableForChanOpOnly() = false;
}

int		check_type_of_mode(char const & mode)
{
	std::string no_param(TYPE_NO_PARAM);
	std::string one_param(TYPE_ONE_PARAM);
	std::string one_or_zero(TYPE_ONE_OR_ZERO);
	std::string params(TYPE_PARAMS);
	if (no_param.find(mode) != std::string::npos)
		return 1;
	if (one_param.find(mode) != std::string::npos)
		return 2;
	if (one_or_zero.find(mode) != std::string::npos)
		return 3;
	if (params.find(mode) != std::string::npos)
		return 4;
	return 0;
}

int     channel_mode(const std::string &line, int fd, Server& server)
{
	COUT "CHANNEL MODE" ENDL;
	std::vector<std::string>	tab = ft_split(line, ' ');
	// User*						cur = server.findMatchingUser(fd);
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
	// if (cur->isChanOp() == false) // WRONG CONDITION : isChanOP() not good
	// {
	// 	server.send_reply(fd, C_ERR_CHANOPRIVSNEEDED, chan->getName(), ES, ES, ES);
	// 	return 1;
	// }
	COUT line ENDL;
	bool plus;
	bool sign = false;
	for (unsigned int i = 0, j = 1; i < tab[2].size(); i++)
	{
		if (tab[2][i] == '+' || tab[2][i] == '-')
		{
			sign = true;
			plus = tab[2][i] == '+' ? true : false;
			continue;
		}
		int type = check_type_of_mode(tab[2][i]);
		if (type == 1)
		{
			if (sign)
			{
				if (plus)
					add_flag(chan, tab[2][i]);
				else
					delete_flag(chan, tab[2][i]);
			}
		}
		else if (type == 2)
		{
			if (sign)
			{
				if (tab.size() < 3 + j)
				{
					server.send_reply(fd, C_ERR_NEEDMOREPARAMS, "MODE", ES, ES, ES);
				}
				else if (tab[2][i] == 'k')
				{
					if (plus)
					{
						if (chan->getKey() == tab[2 + j])
						{
							server.send_reply(fd, C_ERR_KEY_SET, chan->getName(), ES, ES, ES);
						}
						else
						{
							chan->isKeyed() = true;
							chan->setKey(tab[2 + j]);
							chan->addMode(KEY);
						}
					}
					else
					{
						chan->isKeyed() = false;
						chan->setKey(ES);
						chan->delMode(KEY);
					}
				}
				else if (tab[2][i] == 'l')
				{
					if (plus)
					{
						chan->isUserLimited() = true;
						chan->setUserLimit(strtol(tab[2 + j].c_str(), NULL, 10));
						chan->addMode(USER_LIMIT);
					}
					else
					{
						chan->isUserLimited() = false;
						chan->setUserLimit(0);
						chan->delMode(USER_LIMIT);
					}
				}
				j++;
			}
		}
		else if (type == 3)
		{
			if (sign)
			{
				if (tab.size() < 3 + j && plus)
				{
					if (tab[2][i] == 'b')
					{
						server.send_reply(fd, C_RPL_BANLIST, chan->getName(), ES, ES, ES);
						server.send_reply(fd, C_RPL_ENDOFBANLIST, chan->getName(), ES, ES, ES);
					}
					if (tab[2][i] == 'e')
					{
						server.send_reply(fd, C_RPL_EXCEPTLIST, chan->getName(), ES, ES, ES);
						server.send_reply(fd, C_RPL_ENDOFBANLIST, chan->getName(), ES, ES, ES);
					}
					else if (tab[2][i] == 'I')
					{
						server.send_reply(fd, C_RPL_INVITELIST, chan->getName(), ES, ES, ES);
						server.send_reply(fd, C_RPL_ENDOFINVITELIST, chan->getName(), ES, ES, ES);
					}
					else
					{
						server.send_reply(fd, C_ERR_NEEDMOREPARAMS, "MODE", ES, ES, ES);
					}
				}
				else if (tab[2][i] == 'b')
				{
					// COUT "BAN" ENDL;
					if (plus && !chan->isInBanList(tab[2 + j]))
					{
						// COUT "boom" ENDL;
						// COUT tab[2+j] ENDL;
						chan->addBanList(tab[2 + j]);
					}
					else if (!plus && chan->isInBanList(tab[2 + j]))
					{
						chan->removeBanList(tab[2 + j]);
					}
				}
				else if (tab[2][i] == 'e')
				{
					if (plus && !chan->isInExceptList(tab[2 + j]))
						chan->addExceptList(tab[2 + j]);
					else if (!plus && chan->isInExceptList(tab[2 + j]))
						chan->removeExceptList(tab[2 + j]);
				}
				else if (tab[2][i] == 'I')
				{
					if (plus && !chan->isInInviteList(tab[2 + j]))
						chan->addInviteList(tab[2 + j]);
					else if (!plus && chan->isInInviteList(tab[2 + j]))
						chan->removeInviteList(tab[2 + j]);
				}
				j++;
			}
		}
		else if (type == 0)
		{
			std::string character(1, tab[2][i]);
			server.send_reply(fd, C_ERR_UNKNOWNMODE, character, ES, ES, ES);
		}
	}
	server.send_reply(fd, C_RPL_CHANNELMODEIS, chan->getMode(), ES, ES, ES);
	return 0;
}
