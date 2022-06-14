#include "../headers/User.hpp"

User::User( void )
{
	if (DEBUG == 2)
		COUT "Construct User " << this->_socket ENDL;
	_operator = false;
}
User::User( int socket, std::string nick, std::string user_name,
		std::string pass, std::string mode)
		: _socket(socket), _nick(nick), _user_name(user_name),
			_pass(pass), _mode(mode) 
			{
				if (DEBUG == 2)
					COUT "Construct User " << this->_nick ENDL;
			}

User::~User( void )
{
	COUT "Destruct User." ENDL;
}

bool    User::isOperator(void) const
{
	return _operator;
}

int		User::getSocket(void) const
{
	return _socket;
}

const std::string	User::getNick(void) const
{
	return this->_nick;
}
const std::string	User::getUserName(void) const
{
	return this->_user_name;
}
const std::string	User::getPass(void) const
{
	return this->_pass;
}
const std::string	User::getMode(void) const
{
	return this->_mode;
}

void	User::setNick(std::string nick)
{
	_nick = nick;
}
void	User::setUserName(std::string user_name)
{
	_user_name = user_name;
}
void	User::setPass(std::string pass)
{
	_pass = pass;
}

void	User::addMode(std::string mode)
{
	for (std::string::iterator it = mode.begin(); it != mode.end(); ++it)
	{
		if (*it == 'o' && *it == 'O' && *it == 'a')
			continue ;
		if (_mode.empty())
			_mode = *it;
		else if (_mode.find(*it) == std::string::npos)
			_mode += *it;	
	}
}
void	User::delMode(std::string mode)
{
	
	for (std::string::iterator it = mode.begin(); it != mode.end(); ++it)
	{
		if (!_mode.empty())
			return ;
		if (*it == 'a' && *it != 'r')
			continue ;
		if (mode.find(*it) != std::string::npos)
			_mode.erase(it);
	}
}

void	User::updateMode(std::string mode, char op)
{
	if (op == '+')
		addMode(mode);
	else
		delMode(mode);
}

bool	User::operator==(User* user) const
{
	if (this->_nick == user->_nick)
		return true;
	return false;
}

