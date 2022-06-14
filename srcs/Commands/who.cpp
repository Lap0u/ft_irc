#include "../../headers/Commands.hpp"

#define W_RPL_ENDOFWHO 315

#define W_RPL_WHOREPLY 352

#define W_ERR_NOSUCHSERVER 402

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
    std::vector<std::string> tab = ft_split(line, " ");
    server.send_reply(fd, W_RPL_ENDOFWHO, tab[1], std::string(), std::string(), std::string());
    return 0;
}