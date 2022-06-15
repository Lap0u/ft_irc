#ifndef MESSAGEBUILDER_HPP
# define MESSAGEBUILDER_HPP

# include "Irc.hpp"


# define RPL_WELCOME(nickname, user, localhost) ("Welcome to the Internet Relay Network " + nickname + "!" + user + "@" + localhost)
# define RPL_YOURHOST(servername, ver) ("Your host is " + servername + " running version " + ver)
# define RPL_CREATED(date) ("This server was created " + date)
# define RPL_MYINFO(servername, version, usr_mod, chan_mod) (servername + " " + version + " " + usr_mod + " " + chan_mod)
# define RPL_UMODEIS(usr_mod) (usr_mod)
# define RPL_WHOISUSER(nickname, user, host, realname) (nickname + " " + user + " " + host + " * :" + realname)
# define RPL_WHOISSERVER(nickname, server, serverInfo) (nickname + " " + server + " :" + serverInfo)
# define RPL_WHOISIDLE(nickname, time) (nickname + " " + time + " :seconds idle")
# define RPL_ENDOFWHOIS(nickname) (nickname + " :End of WHOIS list")
# define RPL_WHOISCHANNELS(nickname, chanlist) (nickname + " " + chanlist)
# define RPL_AWAY(nickname, message)( nickname + " :" + message)
# define RPL_WHOISOPERATOR(nickname) (nickname + " :is an IRC operator")

# define ERR_UMODEUNKNOWNFLAG ":Unknown MODE flag"
# define ERR_USERSDONTMATCH ":Cannot change mode for other users"
# define ERR_NOSUCHNICK(nickname) (nickname + " :No such nick/channel")
# define ERR_NEEDMOREPARAMS(command) (command + " :Not enough parameters")
# define ERR_ALREADYREGISTRED ":Unauthorized command (already registered)"
# define ERR_NOORIGIN ":No origin specified"
# define ERR_NONICKNAMEGIVEN ":No nickname given"
# define ERR_ERRONEUSNICKNAME(nickname) (nickname + " :Erroneous nickname")
# define ERR_NICKNAMEINUSE(nickname) (nickname + " :Nickname is already in use")
# define ERR_UNAVAILRESOURCE(nickname) (nickname + " :Nick is temporarily unavailable")
# define ERR_RESTRICTED ":Your connection is restricted!"


# define SPE_PONG(sender, receiver) ("PONG " + arg1 + " " + arg2)

void    send_reply(int fd, int code, std::string arg1, std::string arg2, std::string arg3, std::string arg4);

#endif