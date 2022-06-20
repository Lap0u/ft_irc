#include "../../headers/Commands.hpp"

int		privateMessage(const std::string &line, int fd, Server& server)
{
    User *sender = server.findMatchingUser(fd);
    std::vector<std::string>split = ft_split(line, ' ');
    User *receiver = server.getUser(split[1]);

    // if (checkError(split, fd, server) == 1)
    //     return 1;
    std::string message = ":" + sender->getNick() + "!" + receiver->getUserName() + "@localhost" + " " + line + "\r\n";
    DEB "Private message function" ENDL;
    server.send_raw_message(receiver->getSocket(), message);
    return 0;
}
