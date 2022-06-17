#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

#define J_ERR_NEEDMOREPARAMS 461

#define J_ERR_INVITEONLYCHAN 473

#define J_ERR_CHANNELISFULL 471

#define J_ERR_NOSUCHCHANNEL 403

#define J_ERR_TOOMANYTARGETS 407

#define J_ERR_BANNEDFROMCHAN 474

#define J_ERR_BADCHANNELKEY 475

#define J_ERR_BADCHANMASK 476

#define J_ERR_TOOMANYCHANNELS 405

#define J_ERR_UNAVAILRESOURCE 437

#define J_RPL_TOPIC 332

int		not_enough_parameters(int fd, Server& server)
{
	server.send_reply(fd, J_ERR_NEEDMOREPARAMS, "join", ES, ES, ES);
    return 1;
}

int		ft_handle_two_tabs(std::vector<std::string> const & tab1, std::vector<std::string> const & tab2)
{
	for (unsigned int i = 0; i < tab1.size(); i++)
	{
		COUT "there " << tab1[i] << " " << tab2[i] ENDL;
	}
	return 0;
}

int		ft_handle_one_tab(std::vector<std::string> const & tab)
{
	for (unsigned int i = 0; i < tab.size(); i++)
	{
		COUT "here " << tab[i] ENDL;
	}
	return 0;
}

int     join(const std::string &line, int fd, Server& server)
{
    std::vector<std::string> tab = ft_split(line, ' ');
	COUT line ENDL;
    if (tab.size() == 1)
		return not_enough_parameters(fd, server);
	if (tab.size() == 2)
	{
		std::vector<std::string> tab1 = ft_split(tab[1].data(), ' ');
		return ft_handle_one_tab(tab1);
	}
	if (tab.size() == 3)
	{
		COUT "SIZE 3 " ENDL;
		COUT "tab1 " << tab[1].data() ENDL;
		COUT "tab2 " << tab[2].data() ENDL;
		std::vector<std::string> tab1 = ft_split(tab[1].data(), ',');
		std::vector<std::string> tab2 = ft_split(tab[2].data(), ',');
		COUT "tab1 == " << tab1.size() ENDL;
		COUT "tab2 == " << tab2.size() ENDL;
		if (tab2.size() > tab1.size())
			return not_enough_parameters(fd, server);
		return ft_handle_two_tabs(tab1, tab2);
	}
    return 1;
}