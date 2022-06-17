#include "../headers/Oper.hpp"

Oper::Oper() : User()
{}

Oper::~Oper()
{}

Oper::Oper(int socket, std::string nick, std::string user_name,
		std::string pass, std::string mode)
        : User(socket, nick, user_name, pass, mode)
{}


