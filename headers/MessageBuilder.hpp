#ifndef MESSAGEBUILDER_HPP
# define MESSAGEBUILDER_HPP

# include "Irc.hpp"


# define RPL_WELCOME(nick) ("Welcome to the Internet Relay Network " + nick)
# define RPL_YOURHOST(servername, ver) ("Your host is " + servername + " running version " + ver)
# define RPL_CREATED(date) ("This server was created " + date)
# define RPL_MYINFO(servername, version, usr_mod, chan_mod) (servername + " " + version + " " + usr_mod + " " + chan_mod)
# define RPL_UMODEIS(usr_mod) (usr_mod)
# define SPE_PONG(sender, receiver) ("PONG " + arg1 + " " + arg2)

# define ERR_NEEDMOREPARAMS(command) (command + " :Not enough parameters")
# define ERR_ALREADYREGISTRED ":Unauthorized command (already registered)"
# define ERR_NOORIGIN ":No origin specified"


# define SPE_PONG(sender, receiver) ("PONG " + arg1 + " " + arg2)

void    send_reply(int fd, int code, std::string arg1, std::string arg2, std::string arg3, std::string arg4);

#endif