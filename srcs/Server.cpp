#include "../headers/Server.hpp"

Server::Server( void )
{
	// COUT "Construct Server " << this->_user ENDL;
}
// Server::Server( std::string user ) : _user(user)
// {
//     COUT "Construct Server " << this->_user ENDL;
// }
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
	temp.events = 0;
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

nfds_t		Server::getSockeSize(void) const
{
	return _socket_tab.size();
}