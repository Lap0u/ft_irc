#ifndef MESSAGEBUILDER_HPP
# define MESSAGEBUILDER_HPP

# include "Irc.hpp"


# define RPL_WELCOME(nick, user, localhost) ("Welcome to the Internet Relay Network " + nick + "!" + user + "@" + localhost)
# define RPL_YOURHOST(servername, ver) ("Your host is " + servername + " running version " + ver)
# define RPL_CREATED(date) ("This server was created " + date)
# define RPL_MYINFO(servername, version, usr_mod, chan_mod) (servername + " " + version + " " + usr_mod + " " + chan_mod)
# define RPL_UMODEIS(usr_mod) (usr_mod)
# define ERR_NONICKNAMEGIVEN ":No nickname given"
# define ERR_ERRONEUSNICKNAME (nick) nick + " :Erroneous nickname"
# define ERR_NICKNAMEINUSE (nick) nick + " :Nickname is already in use"
# define ERR_UNAVAILRESOURCE (nick) nick + " :Nick is temporarily unavailable"
# define ERR_RESTRICTED ":Your connection is restricted!"
# define SPE_PONG(sender, receiver) ("PONG " + arg1 + " " + arg2)

# define ERR_NEEDMOREPARAMS(command) (command + " :Not enough parameters")
# define ERR_ALREADYREGISTRED ":Unauthorized command (already registered)"
# define ERR_NOORIGIN ":No origin specified"


# define SPE_PONG(sender, receiver) ("PONG " + arg1 + " " + arg2)

void    send_reply(int fd, int code, std::string arg1, std::string arg2, std::string arg3, std::string arg4);

#endif