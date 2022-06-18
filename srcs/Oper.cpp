#include "../headers/Oper.hpp"

Oper::~Oper()
{}

Oper::Oper(std::string name, User *creator)
: _name(name), _creator(creator)
{}

bool    Oper::operator==(Oper* oper) const
{
	if (this->_name == oper->_name)
		return true;
	return false;
}

const std::string	Oper::getName(void) const
{
	return _name;
}

User*				Oper::getUser(void) const
{
	return _creator;
}

const std::string	Oper::getUserNick(void) const
{
	return _creator->getNick();
}
