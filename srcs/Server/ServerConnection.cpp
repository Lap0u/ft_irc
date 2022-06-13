#include "../../headers/Server.hpp"

int		Server::setConnection(int fd)
{
	std::string	recvline;

	while (1)
	{
		recvline = getPackage(fd);
		if (recvline.empty())
			break ;
		while (recvline.find("\r\n") != std::string::npos)
		{
			parseCmd(recvline, fd);
			recvline.erase(0, recvline.find("\r\n") + 2);
		}
		recvline.clear();
    }
	return(0);
}

void	Server::connectionRequest(void)
{
	int		fd;

	fd = accept(getMainSocket(), (SA*) NULL, NULL);
	if (fd == -1)
	{
		perror("accept");
		exit(1);
	}
	if (setConnection(fd) == -1)
		return ;
}

int		Server::connectionSuccess(void)
{
	return (1);
}

int		Server::connectionFailure(void)
{
	return (0);
}
