#include "../../headers/Commands.hpp"

#define WI_RPL_AWAY 301

#define WI_RPL_WHOISUSER 311

#define WI_RPL_WHOISSERVER 312

#define WI_RPL_WHOISOPERATOR 313

#define WI_RPL_WHOISIDLE 317

#define WI_RPL_ENDOFWHOIS 318

#define WI_RPL_WHOISCHANNELS 319

#define WI_ERR_NOSUCHNICK 401

#define WI_ERR_NOSUCHSERVER 402

#define WI_ERR_NONICKNAMEGIVEN 431

int    whois(const std::string &line, int fd, Server& server)
{
    std::vector<std::string> tab = ft_split(line, " ,");
    if (tab.size() == 1)
    {
        server.send_reply(fd, WI_ERR_NONICKNAMEGIVEN, ES, ES, ES, ES);
        return 1;
    }
    for (unsigned int i = 1; i < tab.size(); i++)
    {
        User *user = server.getUser(tab[i]);
        if (user == NULL)
        {
            server.send_reply(fd, WI_ERR_NOSUCHNICK, tab[i], ES, ES, ES);
        }
        else
        {
			server.send_reply(fd, WI_RPL_WHOISUSER, user->getNick(), user->getUserName(), server.getServerName(), user->getUserName()); // PUT REAL NAME INSTEAD
			server.send_reply(fd, WI_RPL_WHOISSERVER, user->getNick(), server.getServerName(), "server info", ES);
    		if (user->isOperator())
            {
                server.send_reply(fd, WI_RPL_WHOISOPERATOR, user->getNick(), ES, ES, ES);
            }
    		server.send_reply(fd, WI_RPL_WHOISIDLE, user->getNick(), ES, ES, ES); // time since it's not there
    		server.send_reply(fd, WI_RPL_WHOISCHANNELS, user->getNick(), ES, ES, ES);
            if (user->getMode().find("a") != std::string::npos)
            {
    		    server.send_reply(fd, WI_RPL_AWAY, user->getNick(), "is away", ES, ES);
            }
        }
    }
    server.send_reply(fd, WI_RPL_ENDOFWHOIS, tab[1], ES, ES, ES);
    return 0;
}