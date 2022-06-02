#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include "user.h"


class Server
{
private:
	// std::vector<int>	_socket;

	std::map<User, int>	_user;

public:
	Server( void );
	virtual ~Server( void );
	Server(Server const & src);
	Server& operator=(Server const & rhs);

	Server( std::string type );
		
};

#endif
