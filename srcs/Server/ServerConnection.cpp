#include "../../headers/Server.hpp"

int		Server::setConnection(int fd)
{
	std::string	recvline;
	std::string	separatedline;
	int			i = 0;

	while (1)
	{
		recvline = getPackage(fd, false);
		if (recvline.empty())
			break ;
		while (recvline.find("\r\n") != std::string::npos)
		{
			separatedline = recvline.substr(0, recvline.find("\r\n"));
			if (i == 1 && std::string(separatedline.begin(), separatedline.begin() + 5) != "PASS ")
                return 1;
			parseCmd(separatedline, fd);
			recvline.erase(0, recvline.find("\r\n") + 2);
			i++;
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
