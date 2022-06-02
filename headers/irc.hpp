#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#define SERVER_PORT 6667
#define MAXLINE 4096
#define SA struct sockaddr

#define COUT std::cout <<
#define ENDL << std::endl;
#define CERR std::cerr <<

typedef enum e_rpl {
    RPL_WELCOME = 001,
    RPL_YOURHOST = 002,
    RPL_CREATED = 003,
    RPL_MYINFO = 004
} t_rpl;

/*  srcs/socket.cpp */
void    launch_serv(std::string port, std::string password);