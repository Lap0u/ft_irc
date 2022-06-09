#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include "Irc.hpp"

typedef void (*commandFunction)(void); // function pointer type


void	pass(void);
void	nick(void);
void	oper(void);
void	user(void);



#endif