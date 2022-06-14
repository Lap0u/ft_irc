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

bool    is_in_set(const std::string& str, const std::string& str2)
{
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
    {
        if (str2.find(*it) == std::string::npos)
            return false;
    }
    return true;
}

bool    is_in_set(const std::string& str, const std::string& str2, size_t size)
{
    size_t i = 0;

    for (std::string::const_iterator it = str.begin(); it != str.end() && i < size; ++it)
    {
        if (str2.find(*it) == std::string::npos)
            return false;
    }
    return true;
}

int    whois(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur whois" ENDL;

    return 2;
}

