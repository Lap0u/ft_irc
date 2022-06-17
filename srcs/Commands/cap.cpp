#include "../../headers/Commands.hpp"

int		cap(const std::string &line, int fd, Server& server)
{
	std::vector<std::string>parsedLine = ft_split(line, ' ');
	if ( parsedLine.size () != 2 || parsedLine[1] != "LS")
	{
		User *cur = server.findMatchingUser(fd);
		if (cur->_registered == 0)
			server.deleteUserSocket(server.findPosSocket(fd));
	}
	DEB "Pointeur cap fonction" ENDL;
	return 2;
}
