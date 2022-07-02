#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

#define C_RPL_UMODEIS 221

#define	C_ERR_NOSUCHCHANNEL 403

#define C_ERR_USERNOTINCHANNEL 441

#define C_ERR_NEEDMOREPARAMS 461

#define C_ERR_UNKNOWNMODE 472

#define C_ERR_CHANOPRIVSNEEDED 482

#define TYPE_NO_PARAM "aimnqpsrt"
#define TYPE_ONE_PARAM "kl"
#define TYPE_PARAMS "OovbeI"

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
	std::string params(TYPE_PARAMS);
	if (no_param.find(mode) != std::string::npos)
		return 1;
	if (one_param.find(mode) != std::string::npos)
		return 2;
	if (params.find(mode) != std::string::npos)
		return 3;
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
	if ((*tab[2].begin() != '-' && *tab[2].begin() != '+') || (tab[2].size() < 2 || tab[2].size() > 4))
	{
		return 1;
	}
	std::string mode (tab[2].begin() + 1, tab[2].end());
	COUT mode ENDL;
	COUT line ENDL;
	bool plus;
	for (unsigned int i = 0, j = 0; i < tab[2].size(); i++)
	{
		if (tab[2][i] == '+' || tab[2][i] == '-')
		{
			plus = tab[2][i] == '+' ? true : false;
			continue;
		}

		int type = check_type_of_mode(tab[2][i]);
		if (type == 1)
		{
			if (plus == true)
				add_flag(chan, tab[2][i]);
			else
				delete_flag(chan, tab[2][i]);
		}
		else if (type == 2)
		{
			if (tab.size() < 3 + j && plus == true)
			{
				server.send_reply(fd, C_ERR_NEEDMOREPARAMS, "MODE", ES, ES, ES);
			}
			else if (tab[2][i] == 'k')
			{
				if (plus == true)
				{
					chan->isKeyed() = true;
					chan->setKey(tab[2 + j]);
					chan->addMode(KEY);
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
				if (plus == true)
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
		else if (type == 3)
		{
			COUT "type 3" ENDL;
			for (size_t i = 3; i < tab.size(); i++)
			{

			}
		}
		else
		{
			std::string character(1, tab[2][i]);
			server.send_reply(fd, C_ERR_UNKNOWNMODE, character, ES, ES, ES);
		}
	}
	COUT "" ENDL;
	server.send_reply(fd, C_RPL_UMODEIS, chan->getMode(), ES, ES, ES);
	return 0;
}
