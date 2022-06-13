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
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur mode" ENDL;

    return 2;
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
	COUT "Tried ping" ENDL;
	std::vector<std::string>parsedLine = ft_split(line, ' ');
	if (parsedLine.size() < 2)
	{
		server.send_reply(fd, 409, NULL, NULL, NULL, NULL);
		return 1;		
	}
	server.send_reply_no_header(fd, 1000, server.getServerName(), parsedLine[1], "", "");

    return 2;
}

