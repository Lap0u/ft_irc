#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <map>
#include <vector>
#include <utility>

#include "Irc.hpp"
#include "User.hpp"
#include <poll.h>

typedef struct pollfd t_pollfd;

class Server
{
private:
	std::vector<t_pollfd>	_socket_tab;
	std::vector<User*>		_user_tab;

public:
	Server( void );
	virtual ~Server( void );

	Server( std::string type );

	bool    isUserUnique(User* user) const;
	bool	addUser(User* user, int socket);

	t_pollfd*	getSocketTab(void);
	nfds_t		getSockeSize(void) const;

};

#endif
