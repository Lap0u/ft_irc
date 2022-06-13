#include "../../headers/Server.hpp"

void	Server::parseCmd(std::string line, int fd)
{
	std::string cmd (line.begin(), line.begin() + line.find(" "));

	commandMap::iterator it = _commands.find(cmd);
	if (it != _commands.end())
		it->second(line, fd, *this);
	else
		CERR "Command not found" ENDL;
	
}

int		Server::parseRecv(int fd, std::string recv)
{
	std::string token;
	size_t pos = 0;

	pos = recv.find("\r\n", pos);
	while (pos != std::string::npos)
	{
		token = recv.substr(0, pos);
		DEB "==> " << token ENDL;
		if (token.compare(0, 5, "USER ") == 0)
		{
			User* user_new = new User(fd, "nick", "name", "pass", "mode");
			if (addUser(user_new) == true)
				addSocket(fd, POLLIN);
			else
				delete user_new;
			return (connectionSuccess());
		}
		recv.erase(0, pos + 2);
		pos = recv.find("\r\n");
	}
	return (connectionFailure());
}