#include "../headers/Channel.hpp"

Channel::Channel()
{
	if (DEBUG == 2)
		COUT "Construct Channel " << this->_name ENDL;
}

Channel::Channel(std::string name) : _name(name)
{
	if (DEBUG == 2)
		COUT "Construct Channel " << this->_name ENDL;
}

Channel::~Channel()
{
	COUT "Destruct Channel." ENDL;
}