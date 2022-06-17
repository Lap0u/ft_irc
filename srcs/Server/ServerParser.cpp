#include "../../headers/Server.hpp"

void	Server::parseCmd(std::string line, int fd)
{
	size_t pos = line.find(" ");
	if (pos == std::string::npos)
	{
		DEB "Command not found (find)" ENDL;
		User *cur = findMatchingUser(fd);
		if (cur->_registered == 0)
			deleteUserSocket(findPosSocket(fd));
		return;
	}
	std::string cmd (line.begin(), line.begin() + line.find(" "));

	commandMap::iterator it = _commands.find(cmd);
	if (it != _commands.end())
		it->second(line, fd, *this);
	else
	{
		if (findMatchingUser(fd)->_registered == 0)
			deleteUserSocket(findPosSocket(fd));
		DEB "Command not found" ENDL;
	}
}
