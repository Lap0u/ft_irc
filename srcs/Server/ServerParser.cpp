#include "../../headers/Server.hpp"

void	Server::parseCmd(std::string line, int fd)
{
	std::string cmd = line;
	size_t pos = line.find(" ");
	if (pos != std::string::npos)
		cmd.assign(line.begin(), line.begin() + line.find(" "));
	commandMap::iterator it = _commands.find(cmd);
	if (it != _commands.end())
		it->second(line, fd, *this);
	else
	{
		// if (findMatchingUser(fd)->isRegistered() == false)
		// 	deleteUserSocket(findPosSocket(fd));
		DEB "Command not found" ENDL;
	}
}
