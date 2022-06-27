#ifndef USER_HPP
# define USER_HPP

#include <iostream>
#include <string>
#include <map>
#include "Irc.hpp"

class Channel;

class User
{
protected:
	bool								_serv_op;
	bool								_chan_op;
	int									_socket;
	std::string							_nick;
	std::string							_user_name;
	std::string							_real_name;
	std::string							_pass;
	std::string							_mode;
	bool								_registered;
	std::map <Channel*, std::string>	_chan_and_modes;

	
	
public:
	User( void );
	virtual ~User( void );

	User( int socket, std::string nick, std::string user,
		std::string pass, std::string mode);

	bool    isOperator(void) const; // isServOp()
	bool    isChanOp(void) const;

	int					getSocket(void) const;
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
	void	setServOp(bool status);
	void	setChanOp(bool status);


	bool	operator==(User* user) const;
	
};

#endif

