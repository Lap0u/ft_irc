#include "../../headers/Commands.hpp"

int		pass(const std::string &line, int fd, Server& server)
{
	COUT "Point pass fonction" ENDL;
	std::vector<std::string>parsedLine = ft_split(line, ' ');
	if (parsedLine.size() < 2)
	{
		server.send_reply(fd, 461, "PASS", "", "", "");
		return 1;		
	}
	if (server.findMatchingUser(fd) != NULL)
	{
		server.send_reply(fd, 462, "", "", "", "");
		return 1;
	}
	if (parsedLine[1] != server.getServerPassword())
	{
		DEB "Password " << parsedLine[1] << " was wrong" ENDL;
		return 1;
	}
	DEB "Pass is matching" ENDL;
	return 0;
}
