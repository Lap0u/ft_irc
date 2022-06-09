#ifndef MESSAGE_HPP
# define MESSAGE_HPP

#include "Irc.hpp"

class Message
{
private:
    std::string     _sender;
    std::string     _receiver;
    std::string     _command;
    std::string     _paylod;
    int             _socket;

public:
    Message(std::string send, std::string receiv, std::string paquet, int fd);

    std::string     getSender(void) const;
    std::string     getReceiver(void) const;
    std::string     getCommand(void) const;
    std::string     getPaylod(void) const;
    int             getSocket(void) const;

    void            setSender(std::string sender);
    void            setReceiver(std::string receiver);
    void            setCommand(std::string Command);
    void            setPaylod(std::string Paylod);
    void            setSocket(int fd);

    void display(void) const;
};
#endif