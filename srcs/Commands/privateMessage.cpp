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
    std::vector<std::string>split = ft_split(line, ' ');
    User *receiver = server.getUser(split[1]);

    if (checkError(split, fd, server, receiver) == 1)
        return 1;
    std::string message = ":" + sender->getNick() + "!" + receiver->getUserName() + "@localhost" + " " + line + "\r\n";
    DEB "Private message function" ENDL;
    server.send_raw_message(receiver->getSocket(), message);
    return 0;
}
