#include "../headers/Server.hpp"

Server::Server(int port, std::string pass)
{
	COUT "Server waiting on port " << port ENDL;

	struct sockaddr_in  servaddr;

	_server_password = pass;
	_main_socket = socket(AF_INET, SOCK_STREAM, 0);
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
}

Server::~Server( void )
{
	COUT "Destruct Server." ENDL;
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

bool	Server::addUser(User* user, int socket)
{
	t_pollfd    temp;

	if (!_user_tab.empty() && !isUserUnique(user))
		return false;

	_user_tab.push_back(user);
	temp.fd = socket;
	temp.events = POLLIN;
	temp.revents = 0;
	_socket_tab.push_back(temp);
	return true;
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

int	Server::getMainSocket(void)const
{
	return _main_socket;
}

void	Server::setup_connection(int new_fd)
{
	char buffer[MAXLINE + 1];
	t_pollfd fd_tab[1];

	fd_tab[0].fd = new_fd;
	fd_tab[0].events = POLLIN;
	fd_tab[0].revents = 0;
	if (poll(fd_tab, 1, 10000) < 0)
	{
		if (DEBUG == 2)
			COUT "Too slow to establish connection, aborted" ENDL;
		return;
	}
	if (recv(new_fd, buffer, MAXLINE - 1, 0) < 0)
	{
		CERR "Error while reading" ENDL;
	}
	COUT buffer ENDL; //parser buffer pour ajouter un user ou non

	// User user1(0, "nom1", "nom1", "nom1", "nom1");

}