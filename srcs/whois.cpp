#include "../headers/Commands.hpp"

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

int find_a_delimiter(std::string tosplit, std::string delimiter)
{
    for (unsigned int i = 0; i < tosplit.length(); i++)
    {
        for (unsigned int j = 0; j < delimiter.length(); j++)
        {
            if (delimiter[j] == tosplit[i])
                return i;
        }
    }
    return -1;
}

int find_a_delimiter_at_beginning(std::string tosplit, std::string delimiter)
{
    for (unsigned int j = 0; j < delimiter.length(); j++)
    {
		if (delimiter[j] == tosplit[0])
        	return j;
    }
    return -1;
}

std::vector<std::string> ft_split(std::string tosplit, std::string delimiter)
{
    std::vector<std::string>res;

    while(!tosplit.empty())
    {
        int pos = find_a_delimiter(tosplit, delimiter);

        if (pos == -1)
            pos = tosplit.size();
        res.push_back(std::string(tosplit.begin(), tosplit.begin() + pos));
        tosplit.erase(0, pos);
        while (find_a_delimiter_at_beginning(tosplit, delimiter) != -1 && !tosplit.empty())
        {
            tosplit.erase(0, 1);
        }
    }
    return res;
}

int    whois(const std::string &line, int fd, Server& server)
{
    std::vector<std::string> tab = ft_split(line, " ,");

	// COUT "line == " << line << "!" ENDL;
    // for (unsigned int i = 0; i < tab.size(); i++)
    // {
    //     COUT "tab == " << tab[i] << " size == " << tab.size() ENDL;
    // }
    if (tab.size() == 1)
    {
        server.send_reply(fd, WI_ERR_NONICKNAMEGIVEN, std::string(), std::string(), std::string(), std::string());
        return 1;
    }
    for (unsigned int i = 1; i < tab.size(); i++)
    {
        // COUT "tab i == " << tab[i] ENDL;
        User *user = server.findMatchingUser(tab[i]);
        if (user == NULL)
        {
            server.send_reply(fd, WI_ERR_NOSUCHNICK, tab[i], std::string(), std::string(), std::string());
        }
        else
        {
			server.send_reply(fd, WI_RPL_WHOISUSER, std::string(), std::string(), std::string(), std::string());
    		server.send_reply(fd, WI_RPL_WHOISOPERATOR, std::string(), std::string(), std::string(), std::string());
    		server.send_reply(fd, WI_RPL_WHOISIDLE, std::string(), std::string(), std::string(), std::string());
    		server.send_reply(fd, WI_RPL_WHOISCHANNELS, std::string(), std::string(), std::string(), std::string());
            if (user->getMode() == "a")
            {
    		    server.send_reply(fd, WI_RPL_AWAY, std::string(), std::string(), std::string(), std::string());
            }
        }
    }
    server.send_reply(fd, WI_RPL_ENDOFWHOIS, std::string(), std::string(), std::string(), std::string());
    return 0;
}