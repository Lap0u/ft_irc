#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>

#include "Irc.hpp"
#include "User.hpp"
#include "Commands.hpp"
#include <poll.h>

class Server;

typedef struct pollfd t_pollfd;
typedef int (*commandFunction)(const std::string &line, int fd, Server& server); // function pointer type

class Server
{
public:
	
	typedef std::map<std::string, commandFunction>		commandMap;
	typedef std::map<int, std::string>					repliesMap;
	typedef	std::vector<t_pollfd>						pollfdVector;
	typedef	std::vector<User*>							userVector;

private:
	int				_main_socket;
	std::string		_server_password;
	std::string		_server_name;
	std::string		_oper_password;
	std::string		_version;
	std::time_t		_date;

	pollfdVector	_socket_tab;
	userVector		_user_tab;

	commandMap		_commands;
	repliesMap		_replies;
	
	void			initReplies(void);
	void			initCommands(void);

public:
	Server(int port, std::string pass);
	virtual ~Server( void );

	bool			isUserUnique(User* user) const;
	bool			isUserUnique(const std::string &nick) const;
	bool			addUser(User* user);

	t_pollfd*		getSocket(nfds_t i);
	User*			getUser(std::string nick) const;
	nfds_t			getSocketSize(void) const;
	int				getMainSocket(void) const;
	std::string		getServerName(void) const;
	std::string		getOperPassword(void) const;
	std::string		getServerPassword(void) const;
	std::string		getVersion(void) const;
	std::string		getDate(void) const;

	void			addSocket(int fd, short events);
	void			connectionRequest(void);
	int				setConnection(int fd);
	void			deleteUserSocket(nfds_t i);

	User*			findMatchingUser(int fd);
	t_pollfd		findMatchingSocket(std::string user);
	int				findPosSocket(int fd);

	void			parseCmd(std::string line, int fd);
	std::string     getPackage(int fd, bool registered);

	void			send_reply(int fd, int code, std::string arg1, std::string arg2, std::string arg3, std::string arg4) const;
	void			send_reply_no_header(int fd, int code, std::string arg1, std::string arg2, std::string arg3, std::string arg4) const;
	
};

bool	operator==(const t_pollfd &pollfd1, const t_pollfd &pollfd2);


#endif
