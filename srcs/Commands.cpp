n#include "../headers/Commands.hpp"

std::vector<std::string> ft_split(std::string tosplit, char delimiter)
{
    tosplit.erase(tosplit.size() - 2, 2);
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

int    whois(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur whois" ENDL;

    return 2;
}

