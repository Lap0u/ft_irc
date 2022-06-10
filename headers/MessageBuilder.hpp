#ifndef MESSAGEBUILDER_HPP
# define MESSAGEBUILDER_HPP

# include "Irc.hpp"


# define RPL_WELCOME(nick) ("001 :Welcome to the Internet Relay Network " + nick)
# define RPL_YOURHOST(servername, ver) ("002: Your host is " + servername + " running version " + ver)
# define RPL_CREATED(date) ("003: This server was created " + date)
# define RPL_MYINFO(servername, version, usr_mod, chan_mod) ("004: " + servername + version + usr_mod + chan_mod)
# define RPL_UMODEIS(usr_mod) ("221: " + usr_mod)

void    send_reply(int fd, int code, std::string arg1, std::string arg2, std::string arg3, std::string arg4);

#endif 