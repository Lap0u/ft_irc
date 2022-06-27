#include "../headers/Channel.hpp"

Channel::Channel(std::string name, std::string key) :
		_name(name), _topic(ES), _mode(ES), _flags("aimnqpsrtlk"),
	_anonymous(false), _invite_only(false), _moderated(false),
	_no_msg_outside(false), _quiet(false), _private(false),
	_secret(false), _topic_chanop_only(false), _key(key), _user_limit(0)
{
	DEB "Construct Channel " << this->_name ENDL;
	if (_key != ES)
		this->addMode(KEY);
}

Channel::~Channel()
{
	DEB "Destruct Channel." ENDL;
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

bool						Channel::isAnonymous(void)
{
	return _anonymous;
}

bool						Channel::isInviteOnly(void)
{
	return _invite_only;
}

bool						Channel::isModerated(void)
{
	return _moderated;
}

bool						Channel::noMessageFromChannel(void)
{
	return _no_msg_outside;
}

bool						Channel::isQuiet(void)
{
	return _quiet;
}

bool						Channel::isPrivate(void)
{
	return _private;
}

bool						Channel::isSecret(void)
{
	return _secret;
}

bool                        Channel::topicSettableForChanOpOnly(void)
{
	return _topic_chanop_only;
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

int						Channel::joinChannel(User* const user, std::string const & key)
{
	if (this->findClient(user->getNick()) != NULL)
		return 1;
	if (this->getMode().find("k") != std::string::npos && this->getKey() != key)
		return 2;
	_clients.push_back(user);
	return 0;
}

int						Channel::partWithAClient(std::string const client)
{
	Clients::iterator it = _clients.begin();
	for (; it != _clients.end(); it++)
	{
		if ((*it)->getNick() == client)
			break;
	}
	if (it == _clients.end())
		return 1;
	_clients.erase(it);
	return 0;
}

User*					Channel::findClient(std::string const client)
{
	Clients::iterator it = _clients.begin();
	for (; it != _clients.end(); it++)
	{
		if ((*it)->getNick() == client)
			return *it;
	}
	return NULL;
}

size_t					Channel::getClientsSize(void) const
{
	return _clients.size();
}

User*					Channel::getAClient(size_t i) const
{
	if (i >= _clients.size())
		return NULL;
	return (_clients[i]);
}
