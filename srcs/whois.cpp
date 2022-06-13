#include "../headers/Commands.hpp"

#define RPL_AWAY 301

#define RPL_WHOISUSER 311

#define RPL_WHOISSERVER 312

#define RPL_WHOISOPERATOR 313

#define RPL_WHOISIDLE 317

#define RPL_ENDOFWHOIS 318

#define RPL_WHOISCHANNELS 319

#define ERR_NOSUCHNICK 401

#define ERR_NOSUCHSERVER 402

#define ERR_NONICKNAMEGIVEN 431                        

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
	// (void)line;
	(void)fd;
	// (void)server;

    std::vector<std::string> tab = ft_split(line, " \r\n,");

	// COUT "Pointeur whois" ENDL;
	COUT "line == " << line << "!" ENDL;
    // for (unsigned int i = 0; i < tab.size(); i++)
    // {
    //     COUT "tab == " << tab[i] << " size == " << tab.size() ENDL;
    // }
    if (tab.size() == 1)
    {
        return ERR_NONICKNAMEGIVEN;
    }
    for (unsigned int i = 1; i < tab.size(); i++)
    {
        COUT "tab i == " << tab[i] ENDL;
        if (server.findMatchingUser(tab[i]) == std::string())
        {
            COUT "no such nick" ENDL;
            return ERR_NOSUCHNICK; 
        }
    }
    return RPL_ENDOFWHOIS;
}