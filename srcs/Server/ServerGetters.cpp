#include "../../headers/Server.hpp"

t_pollfd*	Server::getSocket(nfds_t i)
{
	if (_socket_tab.empty())
		return (NULL);
	return (&_socket_tab[i]);
}

nfds_t		Server::getSocketSize(void) const
{
	return _socket_tab.size();
}

int	Server::getMainSocket(void) const
{
	return _main_socket;
}

std::string Server::getServerName(void) const
{
	return _server_name;
}

std::string Server::getServerPassword(void) const
{
	return _server_password;
}
