#include "../../headers/Commands.hpp"

int    error(const std::string &line, int fd, Server& server)
{
    User*   cur = server.findMatchingUser(fd);
    if (cur)
    {
        if (!cur->isRegistered())
            return 1;
    }
    if (line.find(" ") == std::string::npos)
        return 0;
    std::string message(line.begin() + line.find(" "), line.end());
    message += "\r\n";
    server.send_raw_message(fd, message);
    return 0;
}