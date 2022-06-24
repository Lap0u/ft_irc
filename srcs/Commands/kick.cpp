#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

int     kick(const std::string &line, int fd, Server& server)
{
    User *sender = server.findMatchingUser(fd);
    if (sender)
    {
        if (!sender->isRegistered())
            return 1;
    }
    

    std::vector<std::string>split = ft_split(line, ' ');
    if (split.size() < 3)
    {
        server.send_reply(fd, 461, "KICK", ES, ES, ES);
        return 1;
    }
    std::vector<std::string>channels = ft_split(split[1], ',');
    std::vector<std::string>users = ft_split(split[2], ',');
    return 0;
}