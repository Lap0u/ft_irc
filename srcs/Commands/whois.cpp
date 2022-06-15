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
    DEB "pointer whois" ENDL;
    DEB line ENDL;
    std::vector<std::string> tab = ft_split(line, " ,");
    if (tab.size() == 1)
    {
        server.send_reply(fd, WI_ERR_NONICKNAMEGIVEN, std::string(), std::string(), std::string(), std::string());
        return 1;
    }
    for (unsigned int i = 1; i < tab.size(); i++)
    {
        User *user = server.getUser(tab[i]);
        if (user == NULL)
        {
            server.send_reply(fd, WI_ERR_NOSUCHNICK, tab[i], std::string(), std::string(), std::string());
            DEB "Nosuchnick(whois)" ENDL;
        }
        else
        {
			server.send_reply(fd, WI_RPL_WHOISUSER, user->getNick(), user->getUserName(), server.getServerName(), user->getRealName());
			server.send_reply(fd, WI_RPL_WHOISSERVER, user->getNick(), server.getServerName(), server.getServerInfos(), std::string());
    		if (user->isOperator())
            {
                server.send_reply(fd, WI_RPL_WHOISOPERATOR, user->getNick(), std::string(), std::string(), std::string());
            }
    		server.send_reply(fd, WI_RPL_WHOISIDLE, user->getNick(), "0", std::string(), std::string());
    		server.send_reply(fd, WI_RPL_WHOISCHANNELS, user->getNick(), "make_function_to_get_user_channel", std::string(), std::string());
            if (user->getMode().find("a") != std::string::npos)
            {
    		    server.send_reply(fd, WI_RPL_AWAY, user->getNick(), " is away", std::string(), std::string());
            }
        }
    }
    server.send_reply(fd, WI_RPL_ENDOFWHOIS, tab[1], std::string(), std::string(), std::string());
    return 0;
}