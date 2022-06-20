#include "../headers/User.hpp"

User::User( void ) : _socket(0), _nick(ES),
	_user_name(ES), _real_name("Server"),
	_pass(ES), _mode(ES) , _registered(0)
{
	DEB  "Construct User " ENDL;
}
User::User( int socket, std::string nick, std::string user_name,
		std::string pass, std::string mode)
		: _socket(socket), _nick(nick), _user_name(user_name),
			_real_name("Server"), _pass(pass), _mode(mode) , _registered(0)
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
	return _serv_op;
}

bool    User::isChanOp(void) const
{
	return _chan_op;
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
const std::string	User::getRealName(void) const
{
	return this->_real_name;
}
const std::string	User::getPass(void) const
{
	return this->_pass;
}
const std::string	User::getMode(void) const
{
	return this->_mode;
}
bool				User::isRegistered(void) const
{
	return this->_registered;
}

void	User::setSocket(int socket)
{
	_socket = socket;
}

void	User::setNick(std::string nick)
{
	_nick = nick;
}
void	User::setUserName(std::string user_name)
{
	_user_name = user_name;
}
void	User::setRealName(std::string real_name)
{
	_real_name = real_name;
}
void	User::setPass(std::string pass)
{
	_pass = pass;
}
void	User::setRegister(void)
{
	_registered = true;
}
void	User::setServOp(bool status)
{
	_serv_op = status;
}

void	User::setChanOp(bool status)
{
	_chan_op = status;
}

void	User::addMode(std::string mode)
{
	for (std::string::iterator it = mode.begin(); it != mode.end(); ++it)
	{
		if (*it == 'o' && !isOperator())
			continue ;
		if (*it == 'O' && !isChanOp())
			continue ;
		if (*it == 'a')
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
		if (_mode.empty())
			return ;
		if (*it == 'a' && *it != 'r')
			continue ;
		size_t pos = _mode.find(*it);
		if (pos != std::string::npos)
		{
			if (*it == 'o')
				setServOp(false);
			else if (*it == 'O')
				setChanOp(false);
			_mode.erase(pos, 1);
		}
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
