#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

#define P_ERR_NEEDMOREPARAMS 461

#define	P_ERR_NOSUCHCHANNEL 403

#define P_ERR_NOTONCHANNEL 442

int     part(const std::string &line, int fd, Server& server)
{
    std::vector<std::string> tab = ft_split(line, ' ');
	COUT line ENDL;
	if (tab.size() == 1)
	{
		server.send_reply(fd, P_ERR_NEEDMOREPARAMS, "part:", ES, ES, ES);
		return 1;
	}
	std::vector<std::string> tab1 = ft_split(tab[1].data(), ',');
	if (tab.size() >= 2 && tab.size() <= 3)
	{
		for (unsigned int i = 0; i < tab1.size(); i++)
		{
			Channel*	chan;
			User*		client;
			std::string message;

			if ((chan = server.findChannel(tab1[i])) == NULL)
			{
				server.send_reply(fd, P_ERR_NOSUCHCHANNEL, tab1[i], ES, ES, ES);
			}
			else
			{
				client = server.findMatchingUser(fd);
				if (chan->partWithAClient(client->getNick()) == 1)
				{
					server.send_reply(fd, P_ERR_NOTONCHANNEL, chan->getName(), ES, ES, ES);
				}
				else
				{
					message = tab.size() == 3 ? tab[2] : client->getNick();
					COUT "Message == " << message ENDL;
				}
			}
		}
	}
    return 0;
}