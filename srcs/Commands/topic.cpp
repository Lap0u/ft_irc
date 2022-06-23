#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

int		topic(const std::string &line, int fd, Server& server)
{
    std::vector<std::string>split = ft_split(line, ' ');
    User *sender = server.findMatchingUser(fd);
    
    if (sender)
    {
        if (!sender->isRegistered())
            return 1;
    }
    if (split.size() <= 1)
    {
        server.send_reply(fd, 461, "TOPIC", ES, ES, ES);
        return 1;
    }
    Channel* chan = server.findChannel(split[1]);
    if (chan->findClient(sender->getNick()) == NULL)
    {
        server.send_reply(fd, 442, split[1], ES, ES, ES);
        return 1;
    }
    if (chan == NULL)
        return 0;
    split[2].erase(0, 1);
    if (split.size() >= 2)
        chan->setTopic(split[2]);
    if (chan->getTopic().empty() == 1)
        server.send_reply(fd, 331, split[1], ES, ES, ES);
    else
        server.send_reply(fd, 332, split[1], split[2], ES, ES);
    return 0;
}
