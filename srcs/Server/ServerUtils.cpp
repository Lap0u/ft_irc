#include "../../headers/Server.hpp"

bool    	Server::isUserUnique(User* user) const
{
	for (userVector::const_iterator it = _user_tab.begin(); it != _user_tab.end(); it++)
	{
		if ((*it)->getNick() == user->getNick())
		{
			DEB "NICK EQUAL: "<< (*it)->getNick() ENDL;
			return false;
		}
	}
	return true;
}

bool    	Server::isUserUnique(const std::string &nick) const
{
	for (std::vector<User*>::const_iterator it = _user_tab.begin(); it != _user_tab.end(); it++)
	{
		if ((*it)->getNick() == nick)
		{
			DEB "NICK EQUAL: "<< (*it)->getNick() ENDL;
			return false;
		}
	}
	return true;
}

bool		Server::addUser(User* user)
{
	if (!_user_tab.empty() && !isUserUnique(user))
		return false;
	_user_tab.push_back(user);
	return true;
}

void		Server::addSocket(int fd, short events)
{
	t_pollfd fd_new;

	fd_new.fd = fd;
	fd_new.events = events;
	fd_new.revents = 0;
	_socket_tab.push_back(fd_new);
}

void		Server::deleteUserSocket(nfds_t i)
{
	_socket_tab.erase(_socket_tab.begin() + i);
	_user_tab.erase(_user_tab.begin() + i);
}

User*		Server::findMatchingUser(int socket)
{
	pollfdVector::const_iterator	res;
	t_pollfd 						temp;

	temp.fd = socket;

	res = find(_socket_tab.begin(), _socket_tab.end(), temp);
	if (res == _socket_tab.end())
	{
		DEB "not found" ENDL;
		return (NULL);
	}
	return _user_tab[res - _socket_tab.begin()];
}

t_pollfd	Server::findMatchingSocket(std::string user)
{
	userVector::const_iterator	it = _user_tab.begin();
	int							i = 0;

	for (; it != _user_tab.end(); it++, i++)
	{
		if ((*it)->getNick() == user)
			return _socket_tab[i];
	}
	return _socket_tab[0];
}

int			Server::findPosSocket(int fd)
{
	size_t pos = 0;

	for (; pos < _socket_tab.size(); pos++)
	{
		if (_socket_tab[pos].fd == fd)
			break ;
	}
	return pos;
}

std::string	Server::getPackage(int fd, bool registered)
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
	else if (n == 0)
	{
		CERR "Socket close by client" ENDL;
		if (registered)
			deleteUserSocket(findPosSocket(fd));
		close(fd);
		return (std::string ());
	}
	return (std::string (recvline));
}

bool	operator==(const t_pollfd &pollfd1, const t_pollfd &pollfd2)
{
	return (pollfd1.fd == pollfd2.fd);
}
