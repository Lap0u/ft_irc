#include "../../headers/Server.hpp"

bool    Server::isUserUnique(User* user) const
{
	for (std::vector<User*>::const_iterator it = _user_tab.begin(); it != _user_tab.end(); it++)
	{
		if ((*it)->getNick() == user->getNick())
		{
			DEB "NICK EQUAL: "<< (*it)->getNick() ENDL;
			return false;
		}
	}
	return true;
}

bool	Server::addUser(User* user)
{
	if (!_user_tab.empty() && !isUserUnique(user))
	{

		return false;
	}
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

// Server::handlingExistingConnection()

void		Server::deleteUserSocket(nfds_t i)
{
	_socket_tab.erase(_socket_tab.begin() + i);
	_user_tab.erase(_user_tab.begin() + i);
}

std::string	Server::findMatchingUser(int socket)
{
	pollfdVector::const_iterator res;
	t_pollfd temp;

	temp.fd = socket;

	res = find(_socket_tab.begin(), _socket_tab.end(), temp);
	if (res == _socket_tab.end())
	{
		CERR "not found" ENDL;
		return (std::string ());
	}
	DEB res - _socket_tab.begin() ENDL;
	return _user_tab[res - _socket_tab.begin()]->getUser();
}

std::string	getPaquet(int fd)
{
	char		recvline[MAXLINE + 1];
	int			n = 0;

	memset(recvline, 0, MAXLINE);
	n = recv(fd, recvline, MAXLINE -1, 0); //flag MSG_DONTWAIT? 
	if (n == -1)
	{
		perror("recv");
		exit(1);
	}
	return (std::string (recvline));
}

bool	operator==(const t_pollfd &pollfd1, const t_pollfd &pollfd2)
{
	return (pollfd1.fd == pollfd2.fd);
}