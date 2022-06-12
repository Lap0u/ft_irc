#include "../headers/Commands.hpp"

std::vector<std::string> ft_split(std::string tosplit, char delimiter)
{
    std::vector<std::string>res;

    while(!tosplit.empty())
    {
        size_t pos = tosplit.find(delimiter);

        if (pos == std::string::npos)
            pos = tosplit.size();
        res.push_back(std::string(tosplit.begin(), tosplit.begin() + pos));
        tosplit.erase(0, pos);
        while (tosplit[0] == delimiter && !tosplit.empty())
            tosplit.erase(0, 1);
    }
    return res;
}


int		pass(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur pass fonction" ENDL;
	return 2;
}
int		nick(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur fonction" ENDL;
	return 2;
}
int		oper(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur fonction" ENDL;
	return 2;
}
int		user(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur fonction" ENDL;
	return 2;
}

int    mode(const std::string &line, int fd, Server& server)
{
	// a - user is flagged as away;
	// i - marks a users as invisible;
	// w - user receives wallops;
	// r - restricted user connection;
	// o - operator flag;
	// O - local operator flag;
	// s - marks a user for receipt of server notices.
	std::string user_mode("aiwroOs");

	(void)fd;
	(void)server;
	
	std::vector<std::string> word = ft_split(line, ' ');
	if (word.size() != 2)
	{
		COUT "Paquet complet (MODE + WHOIS)" ENDL;
		for (std::vector<std::string>::iterator it = word.begin(); it != word.end(); ++it)
		{
			std::cout << "boucle1: "<< *it << std::endl;
		}
		return (461); //ERR_NEEDMOREPARAMS
	}
	if ((*word[1].begin() != '+' && *word[1].begin() != '-')
		|| word[1].size() < 2)
	{
		return (501); //ERR_UMODEUNKNOWNFLAG;
	}
	COUT "Paquet partiel (MODE)" ENDL;
	COUT "word[1].size(): " << word[1].size() ENDL;
	for (std::string::iterator it = word[1].begin() + 1; it != word[1].end(); ++it)
	{
		COUT "user_mode.find(*it): "<< user_mode.find(*it) ENDL;
		COUT "*it: "<< *it ENDL;
		if (it != word[1].end() && *(it + 1))
			COUT "*(it + 1): |" << *(it + 1) << "|" ENDL;
		if (it != word[1].end() && user_mode.find(*it) == std::string::npos)
		{
			COUT "501" ENDL;
			return (501); //ERR_UMODEUNKNOWNFLAG
		}
	}

	// ERR_UMODEUNKNOWNFLAG 501
	// ERR_USERSDONTMATCH 502
	COUT "REPL 221" ENDL;
    return 221; //RPL_UMODEIS
}

int    whois(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur whois" ENDL;

    return 2;
}

int    ping(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur ping" ENDL;

    return 2;
}

