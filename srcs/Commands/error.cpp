#include "../../headers/Commands.hpp"

int    error(const std::string &line, int fd, Server& server)
{
    if (line.find(" ") == std::string::npos)
        return 0;
    std::string message(line.begin() + line.find(" "), line.end());
    server.send_raw_message(fd, message);
    return 0;
}