#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

int     check_each_error(int fd, Server server, std::string chan, std::string sender, std::string user)
{
    Channel *cur_chan = server.findChannel(chan);
    if (cur_chan == NULL)
    {
        server.send_reply(fd, 403, chan, ES, ES, ES);// ERR_NOSUCHCHANNEL
        return 1;
    }
    if (cur_chan->findClient(sender) == NULL)
    {
        server.send_reply(fd, 442, chan, ES, ES, ES);// ERR_NOTONCHANNEL
        return 1;
    }
    User *target = cur_chan->findClient(user);
    if (target == NULL)
    {
        server.send_reply(fd, 441, user, chan, ES, ES);// ERR_USERNOTINCHANNEL
        return 1;
    }
    return 0;
}

int     kick(const std::string &line, int fd, Server& server)
{
    User *sender = server.findMatchingUser(fd);
    User *target = NULL; 

    if (sender)
    {
        if (!sender->isRegistered())
            return 1;
    }
    std::vector<std::string>split = ft_split(line, ' ');
    if (split.size() < 3)
    {
        server.send_reply(fd, 461, "KICK", ES, ES, ES);//ERR_NEEDMOREPARAMS
        return 1;
    }
	if (sender->getMode().find('o') == std::string::npos) // O
	{
		server.send_reply(fd, 482, split[2], ES, ES, ES); //ERR_CHANOPRIVSNEEDED
		return 1;
	}
    std::vector<std::string>    channels = ft_split(split[1], ',');
    std::vector<std::string>    users = ft_split(split[2], ',');
    Channel*                    cur_chan = NULL;
    if (channels.size() != 1 && channels.size() != users.size())//ERR_BADCHANMASK
    {
        server.send_reply(fd, 476, split[1], ES, ES, ES);
        return 1;
    }
    if (channels.size() == 1)
    {
        cur_chan = server.findChannel(channels[0]);
        if (cur_chan == NULL)
        {
            server.send_reply(fd, 403, channels[0], ES, ES, ES);// ERR_NOSUCHCHANNEL
            return 1;
        }
        if (cur_chan->findClient(sender->getNick()) == NULL)
        {
            server.send_reply(fd, 442, channels[0], ES, ES, ES);// ERR_NOTONCHANNEL
            return 1;
        }
        for (size_t i = 0; i < users.size(); i++)
        {
            target = cur_chan->findClient(users[i]);
            if (target == NULL)
            {
                server.send_reply(fd, 441, users[i], channels[0], ES, ES);// ERR_USERNOTINCHANNEL
                continue;
            }
            //KICK THE BOY DEGAGE
        }
        return 0;
    }
    for (size_t i = 0; i < channels.size(); i++)
    {
        if (check_each_error(fd, server, channels[i], sender->getNick(), users[i]) == 1)
            continue;
        //KICK THE BOY DEGAGE
    }
    return 0;
}