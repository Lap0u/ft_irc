#include "../headers/MessageBuilder.hpp"
#include "../headers/Server.hpp"
#include <stdlib.h>

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
        case 409:
            return ERR_NOORIGIN;
        case 461:
            return ERR_NEEDMOREPARAMS(arg1);
        case 462:
            return ERR_ALREADYREGISTRED;
        case 1000:
            return SPE_PONG(arg1, arg2);
        default:
            COUT "This response is not into the switch yet(find_reply function)" ENDL;
    }
    return ("");
}

void    Server::send_reply(int fd, int code, std::string arg1, std::string arg2, std::string arg3, std::string arg4) const
{
    std::string str_code;
    char        temp[30];

    sprintf(temp, "%d", code);
    if (code < 10)
		str_code = std::string(2, '0').append(temp);
	else if (code < 100)
		str_code = std::string(1, '0').append(temp);
    else
        str_code = temp;
    std::string message = ":OurServ " + str_code + " Nick " + find_reply(code, arg1, arg2, arg3, arg4) + "\r\n";
    DEB "reply sent " << message ENDL;
    if (send(fd, message.c_str(), message.length(), 0) < 0)
    {
        perror("send reply");
        exit(1);
    }
}

void    Server::send_reply_no_header(int fd, int code, std::string arg1, std::string arg2, std::string arg3, std::string arg4) const
{
    std::string message = find_reply(code, arg1, arg2, arg3, arg4) + "\r\n";
    DEB "reply sent " << message ENDL;
    if (send(fd, message.c_str(), message.length(), 0) < 0)
    {
        perror("send");
        exit(1);
    }
}