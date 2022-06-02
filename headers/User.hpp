#ifndef USER_HPP
# define USER_HPP

#include <iostream>

typedef enum e_type
{
	NORMAL,
	OP
} t_type;

class User
{
private:
	t_type		_type;
	std::string	_nick;
	
public:
	User( void );
	virtual ~User( void );
	User(User const & src);
	User& operator=(User const & rhs);

	User( std::string type );

	const int	getSocket(void);
		
};

#endif

