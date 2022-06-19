#include "../../headers/Commands.hpp"

int		privateMessage(const std::string &line, int fd, Server& server)
{
    std::vector<std::string>split = ft_split(line, ' ');
    // if (checkError(split, fd, server) == 1)
    //     return 1;
    std::string message;
    for (size_t i = 2; i < split.size(); i++)
        message += split[i] + " ";
    server.send_raw_message(fd, message);
    DEB "Private message function" ENDL;
    return 0;
}
