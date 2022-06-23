#include "../../headers/Commands.hpp"

int     checkError(std::vector<std::string>split, int fd, Server& server, User*& receiver)
{
    size_t size = split.size();

    if (size <= 1 || split[1][0] == ':' ) //no recipient
    {
        server.send_reply(fd, 411, split[0], ES, ES, ES);
        return 1;
    }
    if (size <= 2)
    {
        server.send_reply(fd, 412, ES, ES, ES, ES);
        return 1;
    }
    if (size >= 2 && split[2][0] != ':')// too many targets
    {
        server.send_reply(fd, 407, split[1], "407", "Message couldn't be delivered", ES);
        return 1;
    }
    if (receiver == NULL)
    {
        server.send_reply(fd, 401, split[1], ES, ES, ES);
        return 1;
    }
    return 0;
}

int		privateMessage(const std::string &line, int fd, Server& server)
{
    User *sender = server.findMatchingUser(fd);
    if (sender)
    {
        if (!sender->isRegistered())
            return 1;
    }

    std::vector<std::string>split = ft_split(line, ' ');
    User *receiver = server.getUser(split[1]);
    std::string chan_first = "#&+!";
    std::string message;

    for (size_t i = 2; i < split.size(); i++)
        message += split[i] + " ";
    if (split.size() > 1 && chan_first.find(split[1][0]) != std::string::npos)
    {
        server.send_chan_message(sender, "PRIVMSG", split[1], message);
        return 0;
    }

    if (checkError(split, fd, server, receiver) == 1)
        return 1;
    std::string paquet = ":" + sender->getNick() + "!" + server.getServerName() + "@localhost" + " " + line + "\r\n";
    DEB "Private message function" ENDL;
    server.send_raw_message(receiver->getSocket(), paquet);
    return 0;
}
