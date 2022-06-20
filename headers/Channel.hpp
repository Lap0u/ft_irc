#pragma once

#include "Irc.hpp"
#include "Server.hpp"

#define ANONYMOUS "a"
#define INVITE_ONLY "i"
#define MODERATED "m"
#define NO_MESSAGE "n"
#define QUIET "q"
#define PRIVATE "p"
#define SECRET "s"
#define REOP "r"
#define TOPIC "t"
#define USER_LIMIT "l"
#define KEY "k"

class Channel
{
	public:

	typedef Server::userVector	Clients;
	// typedef Server::userVector	Operators;

    private:
    
    int							_socket;
    std::string             	_name;
    std::string             	_topic;
    std::string             	_key;
    std::string	            	_mode;
    std::string                 _flags;
    Clients      				_clients;
    // Operators                   _operators;

    public:

    Channel(std::string name, std::string key = std::string());
    virtual ~Channel();

    const std::string&			getName(void) const;
    const std::string&			getTopic(void) const;
    const std::string&			getKey(void) const;
    const std::string&			getMode(void) const;
    const int&      			getSocket(void) const;

    // const std::string&			getIdentifier(void) const;

    void						setName(std::string const & name);
	void						setTopic(std::string const & topic);
    void						setKey(std::string const & key);
    void                        addMode(std::string const mode);
    void                        delMode(std::string const mode);

    int                         joinChannel(User* const user, std::string const & key = std::string());
    User*                       findClient(std::string const client);
};