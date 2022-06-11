#include "../../headers/Server.hpp"

int		Server::setConnection(int fd)
{
	int		n = 0;
	int		ret = 0;
	char	recvline[MAXLINE + 1];
	char	buff[MAXLINE + 1];

	for (int i = 0; i < 4; i++)
	{
		memset(recvline, 0, MAXLINE);

		n = recv(fd, recvline, MAXLINE -1, 0); //flag MSG_DONTWAIT? 
		if (n == -1)
		{
			perror("recv");
			exit(1);
		}
		else if (n == 0)
		{
			CERR "Socket close by client" ENDL;
			close(fd);
			_socket_tab.pop_back();
			_user_tab.pop_back();
			return (-1);
		}
		ret = parseRecv(fd, recvline);
		if (ret == 1)
			break ;
    }
	memset(recvline, 0, MAXLINE);
	snprintf((char*)buff, sizeof(buff), "001\r\nWelcome to irc\r\n002\r\nYour host is blabla\r\n003\r\nThis server was created today\r\n004\r\nAll server infos\r\n");
	if (send(fd, (char*)buff, strlen((char *)buff), 0) < 0) //flag MSG_DONTWAIT?
	{
		perror("send");
		exit(1);
	}
	// findMatchingUser(fd);
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
