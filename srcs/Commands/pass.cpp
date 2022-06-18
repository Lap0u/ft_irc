#include "../../headers/Commands.hpp"

int		pass(const std::string &line, int fd, Server& server)
{
	User* cur = server.findMatchingUser(fd);
	DEB "Point pass fonction" ENDL;
	std::vector<std::string>parsedLine = ft_split(line, ' ');
	if (parsedLine.size() < 2)
	{
		server.send_reply(fd, 461, "PASS", ES, ES, ES);
		if (cur->isRegistered() == false)
			server.deleteUserSocket(server.findPosSocket(fd));
		return 1;		
	}
	if (cur && cur->isRegistered())
	{
		server.send_reply(fd, 462, ES, ES, ES, ES);
		return 1;
	}
	if (parsedLine[1] != server.getServerPassword())
	{
		DEB "Password " << parsedLine[1] << " was wrong" ENDL;
		if (cur->isRegistered() == false)
			server.deleteUserSocket(server.findPosSocket(fd));
		return 1;
	}
	DEB "Pass is matching" ENDL;
	return 0;
}
