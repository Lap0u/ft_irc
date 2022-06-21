#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

#define P_ERR_NEEDMOREPARAMS 461

#define	P_ERR_NOSUCHCHANNEL 403

#define P_ERR_NOTONCHANNEL 442

int     part(const std::string &line, int fd, Server& server)
{
    std::vector<std::string>		tab = ft_split(line, ' ');
	if (tab.size() == 1)
	{
		server.send_reply(fd, P_ERR_NEEDMOREPARAMS, "part:", ES, ES, ES);
		return 1;
	}
	if (tab.size() >= 2 && tab.size() <= 3)
	{
		std::vector<std::string> 	tab1 = ft_split(tab[1].data(), ',');
		User*						client = server.findMatchingUser(fd);
		Channel*					chan;
		std::string					message;
		for (unsigned int i = 0; i < tab1.size(); i++)
		{

			if ((chan = server.findChannel(tab1[i])) == NULL)
			{
				server.send_reply(fd, P_ERR_NOSUCHCHANNEL, tab1[i], ES, ES, ES);
			}
			else
			{
				if (chan->partWithAClient(client->getNick()) == 1)
				{
					server.send_reply(fd, P_ERR_NOTONCHANNEL, chan->getName(), ES, ES, ES);
				}
				else
				{
					message = tab.size() == 3 ? tab[2] : client->getNick();
					server.send_raw_message(fd, " " + message);
				}
			}
		}
	}
    return 0;
}