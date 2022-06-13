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

int		cap(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur cap fonction" ENDL;
	return 2;
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
	COUT "Pointeur nick fonction" ENDL;
	return 2;
}
int		user(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur user fonction" ENDL;
	User* user_new = new User(fd, "nick", "name", "pass", "mode");
	if (server.addUser(user_new) == true)
		server.addSocket(fd, POLLIN);
	else
		delete user_new;
	server.send_reply(fd, 001, "nick", "", "", "");
	server.send_reply(fd, 002, "servername", "ver", "", "");
	server.send_reply(fd, 003, "Date", "", "", "");
	server.send_reply(fd, 004, "servername", "version", "usr_mod", "chan_mod");
	return 2;
}

int		oper(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;
	COUT "Pointeur oper fonction" ENDL;
	return 2;
}

int    mode(const std::string &line, int fd, Server& server)
{
	COUT line ENDL;
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

