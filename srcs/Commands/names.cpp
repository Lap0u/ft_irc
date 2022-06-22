#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

#define N_RPL_NAMREPLY 353

#define N_RPL_ENDOFNAMES 366

int     names(const std::string &line, int fd, Server& server)
{
    std::vector<std::string> tab = ft_split(line, ' ');
    std::string user_list;
    COUT line ENDL;
    if (tab.size() == 1)
        return 1;
    std::vector<std::string> tab1 = ft_split(tab[1].data(), ',');
    for (unsigned int i = 0; i < tab1.size(); i++)
    {
        Channel* chan;
        DEB tab1[i] ENDL;
        if ((chan = server.findChannel(tab1[i])) == NULL)
            continue;
        
        for (unsigned int i = 0; i < chan->getClientsSize(); i++)
            user_list += chan->getAClient(i)->getNick() + " ";
        server.send_reply(fd, N_RPL_NAMREPLY, chan->getName(), user_list, ES, ES);
    	server.send_reply(fd, N_RPL_ENDOFNAMES, chan->getName(), ES, ES, ES);
        user_list.clear();
    }
    return 0;
}