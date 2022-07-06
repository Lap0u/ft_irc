#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

int		list(const std::string &line, int fd, Server& server)
{
    std::vector<std::string>    split = ft_split(line, ' ');
    Channel*                    cur;
    User*                       user = server.findMatchingUser(fd);
    std::vector<std::string>    all_chans;

    if (user && !user->isRegistered())
        return 1;
    if (split.size() <= 1)
    {
        server.listChannel(fd);
        return 0;
    }
    all_chans = ft_split(split[1], ',');
    for (std::vector<std::string>::iterator it = all_chans.begin(); it != all_chans.end(); it++)
    {
        cur = server.findChannel(*it);
        if (cur != NULL)
            server.send_reply(fd, 322, cur->getName(), "visible", cur->getTopic(), ES);
    }
    server.send_reply(fd, 323, ES, ES, ES, ES);
    return 0;
}