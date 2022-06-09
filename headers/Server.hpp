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
public:
	typedef void (Server::*commandFunction)(void); // function pointer type
	typedef std::map<std::string, commandFunction>		commandMap;
	typedef std::map<int, std::string>					repliesMap;
	typedef	std::vector<t_pollfd>						pollfdVector;
	typedef	std::vector<User*>							userVector;

private:
	int							_main_socket;
	std::string					_server_password;
	std::string					_server_name;

	pollfdVector				_socket_tab;
	userVector					_user_tab;
	repliesMap					_replies;

	void			initReplies(void);
	void			initCommands(void);

public:
	commandMap					_commands;
	void	pass(void);
	Server(int port, std::string pass);
	virtual ~Server( void );

	bool			isUserUnique(User* user) const;
	bool			addUser(User* user);

	t_pollfd*		getSocket(nfds_t i);
	nfds_t			getSocketSize(void) const;
	int				getMainSocket(void) const;
	std::string		getServerName(void) const;

	void			addSocket(int fd, short events);
	void			connectionRequest(void);
	int				setConnection(int fd);
	int				parseRecv(int fd, char buf[]);
	int				connectionSuccess(void);
	int				connectionFailure(void);
	void			deleteUserSocket(nfds_t i);
};

#endif
