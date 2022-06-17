#include "../headers/Channel.hpp"

Channel::Channel(std::string name, std::string key) :
	_name(name), _topic(std::string()), _key(key), _mode(std::string()), _flags("aimnqpsrtlk")
{
	if (_key != std::string())
		this->addMode(KEY);
	if (DEBUG == 2)
		COUT "Construct Channel " << this->_name ENDL;
}

Channel::~Channel()
{
	COUT "Destruct Channel." ENDL;
}

const std::string&			Channel::getName(void) const
{
	return _name;
}

const std::string&			Channel::getTopic(void) const
{
	return _topic;
}

const std::string&			Channel::getKey(void) const
{
	return _key;
}

const std::string&			Channel::getMode(void) const
{
	return _mode;
}

const int&					Channel::getSocket(void) const
{
	return _socket;
}

void						Channel::setName(std::string const & name)
{
	_name = name;
}

void						Channel::setTopic(std::string const & topic)
{
	_topic = topic;
}

void						Channel::setKey(std::string const & key)
{
	_key = key;
}

void						Channel::addMode(std::string mode)
{
	for (std::string::iterator it = mode.begin(); it != mode.end(); ++it)
	{
		// if (*it == 'o' && *it == 'O')
			// continue ;
		if (_mode.empty())
			_mode = *it;
		else if (_mode.find(*it) == std::string::npos)
			_mode += *it;
	}
}

void						Channel::delMode(std::string mode)
{
	if (_mode.empty())
		return;
	for (std::string::iterator it = mode.begin(); it != mode.end(); ++it)
	{
		// if (*it == 'a' && *it != 'r')
			// continue ; 
		if (mode.find(*it) != std::string::npos)
			_mode.erase(it);
	}
}