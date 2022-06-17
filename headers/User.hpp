#ifndef USER_HPP
# define USER_HPP

#include <iostream>
#include <string>
#include "Irc.hpp"

class User
{
protected:
	bool		_operator;
	int			_socket;
	std::string	_nick;
	std::string	_user_name;
	std::string	_real_name;
	std::string	_pass;
	std::string	_mode;
	bool		_registered;
	
public:
	User( void );
	virtual ~User( void );

	User( int socket, std::string nick, std::string user,
		std::string pass, std::string mode);

	int		getSocket(void) const;
	bool	isOperator(void) const;

	const std::string	getNick(void) const;
	const std::string	getUserName(void) const;
	const std::string	getPass(void) const;
	const std::string	getMode(void) const;
	const std::string	getRealName(void) const;
	bool				isRegistered(void) const;

	void	setNick(std::string nick);
	void	setSocket(int socket);
	void	setUserName(std::string user);
	void	setRealName(std::string user);
	void	setPass(std::string pass);
	void	updateMode(std::string mode, char op);
	void	addMode(std::string mode);
	void	delMode(std::string mode);
	void	setRegister(void);


	bool	operator==(User* user) const;
	
};

#endif

