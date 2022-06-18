#ifndef OPER_HPP
# define OPER_HPP

#include <iostream>
#include <string>
#include "Irc.hpp"
#include "User.hpp"

class Oper
{
private:
	std::string	_name;
	User*		_creator;
	
public:
	virtual ~Oper( void );
	Oper(std::string name, User *creator);

	const std::string	getName(void) const;
	User*				getUser(void) const;
	const std::string	getUserNick(void) const;

	bool	operator==(Oper* Oper) const;
};

#endif
