#include "../../headers/Server.hpp"

void	Server::parseCmd(std::string line, int fd)
{
	(void)line;
	send_reply(fd, 221, "irewrrqr", "suis", "une", "reponse");
}

int		Server::parseRecv(int fd, char recv[])
{
	std::string str(recv);
	std::string token;
	size_t pos = 0;

	pos = str.find("\r\n", pos);
	while (pos != std::string::npos)
	{
		token = str.substr(0, pos);
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
		str.erase(0, pos + 2);
		pos = str.find("\r\n");
	}
	return (connectionFailure());
}