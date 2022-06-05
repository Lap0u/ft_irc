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
	addServerSocket();
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

int	Server::getMainSocket(void) const
{
	return _main_socket;
}

void	Server::addServerSocket(void)
{
	t_pollfd main_fd;

	main_fd.fd = _main_socket;
	main_fd.events = POLLIN;
	main_fd.revents = 0;
	_socket_tab.push_back(main_fd);
}
void	Server::acceptingRequest(void)
{
	int		fd_new;
	char	*str = NULL;
	struct sockaddr_storage client_saddr;
	socklen_t addrlen = sizeof(struct sockaddr_storage);

	fd_new = accept(getMainSocket(), (SA*) &client_saddr, &addrlen);
	if (fd_new == -1)
		CERR "error accept() : " << strerror( errno ) ENDL;
	User* user_new = new User(fd_new, "nick", "name", "pass", "mode");
	addUser(user_new, fd_new);

	// print IP address of the new client
	struct sockaddr_in  *ptr = (struct sockaddr_in  *) &client_saddr;
	inet_ntop (AF_INET, &(ptr -> sin_addr), str, sizeof(str));
}

// Server::handlingExistingConnection()