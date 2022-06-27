#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

#define J_ERR_NEEDMOREPARAMS 461

#define J_ERR_INVITEONLYCHAN 473

#define J_ERR_CHANNELISFULL 471

#define J_ERR_NOSUCHCHANNEL 403

#define J_ERR_TOOMANYTARGETS 407

#define J_ERR_INVITEONLYCHAN 473

#define J_ERR_BANNEDFROMCHAN 474

#define J_ERR_BADCHANNELKEY 475

#define J_ERR_BADCHANMASK 476

#define J_ERR_TOOMANYCHANNELS 405

#define J_ERR_UNAVAILRESOURCE 437

#define J_RPL_TOPIC 332

#define J_RPL_NAMREPLY 353

#define J_RPL_ENDOFNAMES 366

int		check_first_char_channel(std::string &name)
{
	if (name[0] == '#' || name[0] == '+' || name[0] == '!' || name[0] == '&')
		return 0;
	return 1;
}

int		not_enough_parameters(int fd, Server& server)
{
	server.send_reply(fd, J_ERR_NEEDMOREPARAMS, "join:", ES, ES, ES);
    return 1;
}

void	joinChannel_and_send_replies(int fd, Server& server, std::string& chaname, const std::string& key)
{
	if (check_first_char_channel(chaname) != 0)
		return ;
	Channel* chan = server.findChannel(chaname);
	User* user = server.findMatchingUser(fd);
	int joined = chan->joinChannel(user, key);

	if (joined == 0)
	{
		server.send_chan_message(user, "JOIN", chaname, ES);
		if (chan->getTopic() != ES)
			server.send_reply(fd, J_RPL_TOPIC, chan->getName(), chan->getTopic(), ES, ES);
		server.parseCmd("NAMES " + chan->getName(), fd);
	}
	else if (joined == 2)
	{
		server.send_reply(fd, J_ERR_BADCHANNELKEY, chan->getName(), ES, ES, ES);
		return ;
	}
	else if (joined == 3)
	{
		server.send_reply(fd, J_ERR_INVITEONLYCHAN, chan->getName(), ES, ES, ES);
		return ;		
	}
	COUT "joined = " << joined ENDL;
}

int		ft_handle_two_tabs(std::vector<std::string> & tab1,
			std::vector<std::string> const & tab2, int fd, Server& server)
{
	for (unsigned int i = 0; i < tab1.size(); i++)
	{
		DEB "there " << tab1[i] << " " << tab2[i] ENDL;
		if (server.findChannel(tab1[i]) == NULL)
		{
			DEB tab1[i] << " is not added" ENDL;
			server.addChannel(new Channel(tab1[i], tab2[i]));
		}
		if (i < tab2.size())
		{
			joinChannel_and_send_replies(fd, server, tab1[i], tab2[i]);
		}
		else
		{
			joinChannel_and_send_replies(fd, server, tab1[i], ES);
		}
	}
	return 0;
}

int		ft_handle_one_tab(std::vector<std::string> & tab, int fd, Server& server, User *& cur)
{
	for (unsigned int i = 0; i < tab.size(); i++)
	{
		DEB "here " << tab[i] ENDL;
		if (server.findChannel(tab[i]) == NULL)
		{
			DEB tab[i] << " is not added" ENDL;
			if (cur->getMode().find('r') != std::string::npos)
			{
				DEB "User is restricted and can't create server";
				return 1;
			}
			server.addChannel(new Channel(tab[i]));
		}
		joinChannel_and_send_replies(fd, server, tab[i], ES);
	}
	return 0;
}

int     join(const std::string &line, int fd, Server& server)
{
    std::vector<std::string> tab = ft_split(line, ' ');
	User*   cur = server.findMatchingUser(fd);
    if (cur)
    {
        if (!cur->isRegistered())
            return 1;
    }

	COUT line ENDL;
    if (tab.size() == 1)
	{
		return not_enough_parameters(fd, server);
	}
	std::vector<std::string> tab1 = ft_split(tab[1].data(), ',');
	if (tab.size() == 2)
	{
		return ft_handle_one_tab(tab1, fd, server, cur);
	}
	if (tab.size() == 3)
	{
		std::vector<std::string> tab2 = ft_split(tab[2].data(), ',');
		if (tab2.size() > tab1.size())
			return not_enough_parameters(fd, server);
		return ft_handle_two_tabs(tab1, tab2, fd, server);
	}
    return 1;
}