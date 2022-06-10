#include "../headers/MessageBuilder.hpp"

std::string    build_reply(int code, std::string arg1, std::string arg2, std::string arg3, std::string arg4)
{
    std::string message(":Our_IRC ");
    switch (code)
    {
        case 1:
            return message + RPL_WELCOME(arg1);
        case 2:
            return message + RPL_YOURHOST(arg1, arg2);
        case 3:
            return message + RPL_CREATED(arg1);
        case 4:
            return message + RPL_MYINFO(arg1, arg2, arg3, arg4);
    }
}

void    send_reply(int fd, int code, std::string arg1, std::string arg2, std::string arg3, std::string arg4)
{
    std::string message = build_reply(code, arg1, arg2, arg3, arg4);
    // message = ": " + server.getServName() + " " + message; passer le serveur
    COUT message ENDL;
    if (send(fd, message.c_str(), message.length(), 0) < 0)
    {
        perror("send");
        exit(1);
    }
}