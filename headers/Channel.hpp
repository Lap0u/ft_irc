#pragma once

#include "Irc.hpp"
#include "Server.hpp"

class Channel
{
	public:

	typedef Server::userVector	Clients;

    private:
    
    int							_socket;
    std::string             	_name;
    std::string             	_topic;
    std::string             	_password;
    std::string	            	_mode;
    Clients      				_clients;

    public:

    Channel();
    Channel(std::string name, std::string password = std::string());
    virtual ~Channel();

    const std::string&			getName(void) const;
    const std::string&			getTopic(void) const;
    const std::string&			getPassword(void) const;
    const std::string&			getMode(void) const;

    void						setName(std::string const & name);
	void						setTopic(std::string const & topic);
    void						setPassword(std::string const & psw);
    void						addMode(std::string const & mode);

};