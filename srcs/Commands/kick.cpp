#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

void    kickOne(Server &server, User *& tokick, Channel *& channel, std::string message)
{
    error(message, tokick->getSocket(), server);
    server.send_chan_message(tokick, "PART", channel->getName(), message);
    channel->partWithAClient(tokick->getNick());
}

int     oneChan(int fd, Server& server, std::string chan, std::string sender, std::vector<std::string> users, std::string message)
{
    Channel     *cur_chan = server.findChannel(chan);
    User*       target = NULL;

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
    for (size_t i = 0; i < users.size(); i++)
    {
        target = cur_chan->findClient(users[i]);
        if (target == NULL)
        {
            server.send_reply(fd, 441, users[i], chan, ES, ES);// ERR_USERNOTINCHANNEL
            continue;
        }
        kickOne(server, target, cur_chan, message);
    }
    return 0;
}

int     check_each_error(int fd, Server& server, std::string chan, std::string sender, std::string user)
{
    Channel     *cur_chan = server.findChannel(chan);
    User        *target = NULL;
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
    target = cur_chan->findClient(user);
    if (target == NULL)
    {
        server.send_reply(fd, 441, user, chan, ES, ES);// ERR_USERNOTINCHANNEL
        return 1;
    }
    return 0;
}

int     kick(const std::string &line, int fd, Server& server)
{
    User        *sender = server.findMatchingUser(fd);
    User        *target = NULL;
    std::string message;
    std::vector<std::string>    channels;
    Channel*                    cur_chan = NULL;
    std::vector<std::string>    users;

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
	if (!sender->isOperator()) // O
	{
		server.send_reply(fd, 482, split[2], ES, ES, ES); //ERR_CHANOPRIVSNEEDED
		return 1;
	}
    for (size_t i = 2; i < split.size(); i++)
        message += split[i] + " ";
        
    channels = ft_split(split[1], ',');
    users = ft_split(split[2], ',');
    
    if (channels.size() != 1 && channels.size() != users.size())//ERR_BADCHANMASK
    {
        server.send_reply(fd, 476, split[1], ES, ES, ES);
        return 1;
    }
    if (channels.size() == 1)
        return oneChan(fd, server, channels[0], sender->getNick(), users, message);
    for (size_t i = 0; i < channels.size(); i++)
    {
        if (check_each_error(fd, server, channels[i], sender->getNick(), users[i]) == 1)
            continue;
        cur_chan = server.findChannel(channels[i]);
        target = server.getUser(users[i]);
        kickOne(server, target, cur_chan, message);
    }
    return 0;
}