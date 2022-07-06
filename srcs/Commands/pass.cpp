#include "../../headers/Commands.hpp"

int		pass(const std::string &line, int fd, Server& server)
{
	User*						cur = server.findMatchingUser(fd);
	std::vector<std::string>	parsedLine = ft_split(line, ' ');
	DEB "Point pass fonction" ENDL;

	if (parsedLine.size() < 2)
	{
		server.send_reply(fd, 461, "PASS", ES, ES, ES);
		return 1;		
	}
	if (cur && cur->isRegistered())
	{
		server.send_reply(fd, 462, ES, ES, ES, ES);
		return 1;
	}
	if (parsedLine[1] != server.getServerPassword())
	{
		return 1;
	}
	cur->setPassOK();
	return 0;
}
