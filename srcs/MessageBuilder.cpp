#include "../headers/MessageBuilder.hpp"
#include "../headers/Server.hpp"

std::string    find_reply(int code, std::string arg1, std::string arg2, std::string arg3, std::string arg4)
{
    switch (code)
    {
        case 1:
            return RPL_WELCOME(arg1);
        case 2:
            return RPL_YOURHOST(arg1, arg2);
        case 3:
            return RPL_CREATED(arg1);
        case 4:
            return RPL_MYINFO(arg1, arg2, arg3, arg4);
        case 221:
            return RPL_UMODEIS(arg1);
    }
    return ("");
}

void    Server::send_reply(int fd, int code, std::string arg1, std::string arg2, std::string arg3, std::string arg4) const
{
    // std::string message = find_reply(code, arg1, arg2, arg3, arg4);
    std::string message = ":OurServ 221 Nick " + find_reply(code, arg1, arg2, arg3, arg4) + "\r\n";
    // message = ": " + getServerName() + " " + message + "\r\n";
    // message = message + "\r\n";
    DEB "reply sent " << message ENDL;
    if (send(fd, message.c_str(), message.length(), 0) < 0)
    {
        perror("send");
        exit(1);
    }
}