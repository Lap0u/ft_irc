#ifndef OPER_HPP
# define OPER_HPP

#include <iostream>
#include <string>
#include "Irc.hpp"
#include "User.hpp"

class Oper : public User
{
private:
	
public:
	Oper( void );
	virtual ~Oper( void );

	Oper( int socket, std::string nick, std::string user_name,
		std::string pass, std::string mode);

	// bool	operator==(Oper* Oper) const;
	
};

#endif

