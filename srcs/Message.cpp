#include "../headers/Message.hpp"

Message::Message(std::string send, std::string receiv, std::string paquet, int fd) :
    _sender(send), _receiver(receiv), _socket(fd)
{
    _command = std::string(paquet.begin(), paquet.begin() + paquet.find(" "));
    _paylod = std::string(paquet.begin() + paquet.find(" ") + 1, paquet.end());
}

void    Message::display(void) const
{
    COUT "This message is sent by " << _sender ENDL;
    COUT "This message is receiver by " << _receiver ENDL;
    COUT "The command is " << _command ENDL;
    COUT "The paylod is " << _paylod ENDL;
    COUT "The fd used was " << _socket ENDL;
}

std::string     Message::getSender(void) const
{
    return _sender;
}

std::string     Message::getReceiver(void) const
{
    return _receiver;
}

std::string     Message::getCommand(void) const
{
    return _command;
}

std::string     Message::getPaylod(void) const
{
    return _paylod;
}

int             Message::getSocket(void) const
{
    return _socket;
}

void    Message::setSender(std::string sender)
{
    _sender = sender;
}
void    Message::setReceiver(std::string receiver)
{
    _receiver = receiver;
}
void    Message::setCommand(std::string command)
{
    _command = command;
}
void    Message::setPaylod(std::string paylod)
{
    _paylod = paylod;
}
void    Message::setSocket(int fd)
{
    _socket = fd;
}