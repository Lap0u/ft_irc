#include "../headers/Server.hpp"

Server::Server(int port, std::string pass)
{
	COUT "Server waiting on port " << port ENDL;

	struct sockaddr_in  servaddr;

	_server_password = pass;
	_main_socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (_main_socket < 0)
		exit(1);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family         = AF_INET;
	servaddr.sin_addr.s_addr    = htonl(INADDR_ANY);
	servaddr.sin_port           = htons(port);

	if ((bind(_main_socket, (SA *) &servaddr, sizeof(servaddr))) < 0)
	{
		fprintf(stdout, "bind\n");
		exit(1);
	}

	if ((listen(_main_socket, 10)) < 0)
	{
		fprintf(stdout, "listen\n");
		exit(1);
	};
	addSocket(_main_socket, POLLIN);
}

Server::~Server( void )
{
	COUT "Destruct Server." ENDL;
}

t_pollfd*	Server::getSocketTab(void)
{
	if (_socket_tab.empty())
		return (NULL);
	return (&_socket_tab[0]);
}

nfds_t		Server::getSocketSize(void) const
{
	return _socket_tab.size();
}

int	Server::getMainSocket(void) const
{
	return _main_socket;
}

bool    Server::isUserUnique(User* user) const
{
	for (std::vector<User*>::const_iterator it = _user_tab.begin(); it != _user_tab.end(); it++)
	{
		if ((*it)->getNick() == user->getNick())
			return false;
	}
	return true;
}

bool	Server::addUser(User* user)
{
	if (!_user_tab.empty() && !isUserUnique(user))
		return false;
	_user_tab.push_back(user);
	return true;
}

void	Server::addSocket(int fd, short events)
{
	t_pollfd fd_new;

	fd_new.fd = fd;
	fd_new.events = events;
	fd_new.revents = 0;
	_socket_tab.push_back(fd_new);
}

int		Server::parseRecv(char recv[])
{
	std::string str(recv);
	std::string token;
	size_t pos = 0;

	pos = str.find("\r\n", pos);
	while (pos != std::string::npos)
	{
		token = str.substr(0, pos);
		CERR "==> " << token ENDL;
		str.erase(0, pos + 2);
		pos = str.find("\r\n");
	}
	return 0;
}

int		Server::setConnection(int fd)
{
	int		n = 0;
	int 	ret = 0;
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
			fd = -1;
			return (-1);
		}
		ret = parseRecv(recvline);
		if (ret == -1)
		{
			CERR "Mauvais mdp" ENDL;
			return (-1);
		}
		else if (ret == 1)
			break ;
		// fprintf(stdout, "\n%s\n", recvline);

	}
	CERR "sorti" ENDL;
	memset(recvline, 0, MAXLINE);
	snprintf((char*)buff, sizeof(buff), "001\r\nWelcome to irc\r\n002\r\nYour host is blabla\r\n003\r\nThis server was created today\r\n004\r\nAll server infos\r\n");
	if (send(fd, (char*)buff, strlen((char *)buff), 0) < 0) //flag MSG_DONTWAIT?
	{
		perror("send");
		exit(1);
	}

	User* user_new = new User(fd, "nick", "name", "pass", "mode");
	addUser(user_new);
	addSocket(fd, POLLIN);
	CERR "sorti2" ENDL;
	return(0);
}

void	Server::connectionRequest(void)
{
	int		fd_new;

	fd_new = accept(getMainSocket(), (SA*) NULL, NULL);
	if (fd_new == -1)
	{
		perror("accept");
		exit(1);
	}
	if (setConnection(fd_new) == -1)
		return ;
}

// Server::handlingExistingConnection()

