#include "../../headers/Commands.hpp"

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
