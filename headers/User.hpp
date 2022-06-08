#ifndef USER_HPP
# define USER_HPP

#include <iostream>
#include <string>
#include "Irc.hpp"

class User
{
public:
	bool		_operator;
	int			_socket;
	std::string	_nick;
	std::string	_user;
	std::string	_pass;
	std::string	_mode;
	
public:
	User( void );
	virtual ~User( void );

	User( int socket, std::string nick, std::string user,
		std::string pass, std::string mode);

	int		getSocket(void) const;
	bool	isOperator(void) const;

	const std::string	getNick(void) const;
	const std::string	getUser(void) const;
	const std::string	getPass(void) const;
	const std::string	getMode(void) const;

	void	setNick(std::string nick);
	void	setUser(std::string user);
	void	setPass(std::string pass);
	void	setMode(std::string mode);

	bool	operator==(User* user) const;
	
};

#endif

