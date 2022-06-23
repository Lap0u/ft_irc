#include "../../headers/Server.hpp"
#include "../../headers/Channel.hpp"

bool		Server::addChannel(Channel *channel)
{
	_channel_tab.push_back(channel);
	return true;
}

Channel*	Server::findChannel(std::string const & namechannel) const
{
	if (_channel_tab.empty())
		return (NULL);
	for (channelVector::const_iterator it = _channel_tab.begin(); it != _channel_tab.end(); it++)
	{
		if ((*it)->getName() == namechannel)
			return _channel_tab[it - _channel_tab.begin()];
	}
	return (NULL);
}

void		Server::deleteUserQuittingChannel(User *client)
{
	for (channelVector::iterator it = _channel_tab.begin(); it != _channel_tab.end(); it++)
	{
		if ((*it)->partWithAClient(client->getNick()) == 0)
			send_chan_message(client, "PART", (*it)->getName(), ES);
	}
}

void	Server::listChannel(int fd) const
{
	for(std::vector<Channel*>::const_iterator it = _channel_tab.begin(); it != _channel_tab.end(); it++)
		send_reply(fd, 322, (*it)->getName(), "visible", (*it)->getTopic(), ES);
    send_reply(fd, 323, ES, ES, ES, ES);
}