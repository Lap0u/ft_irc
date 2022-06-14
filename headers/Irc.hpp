#ifndef IRC_HPP
# define IRC_HPP

# ifndef DEBUG
#  define DEBUG 0
# endif


# include <sys/socket.h>
# include <sys/types.h>
# include <signal.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <strings.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <iostream>
# include <algorithm>
# include <errno.h>

# define SERVER_PORT 6667
# define MAXLINE 4096
# define SA struct sockaddr
# define OP_PASS "oppass"
# define USER_MODE "aiwroOs"

# define COUT std::cout <<
# define CERR std::cerr <<
# define DEB if (DEBUG == 2) std::cerr << 
# define ENDL << std::endl
# define NL std::cout << std::endl;

// typedef enum e_rpl {
//     RPL_WELCOME = 001,
//     RPL_YOURHOST = 002,
//     RPL_CREATED = 003,
//     RPL_MYINFO = 004
// } t_rpl;

/*  srcs/socket.cpp */
void            launch_serv(std::string port, std::string password);

/*  srcs/Server/ServerUtils.cpp */


#endif