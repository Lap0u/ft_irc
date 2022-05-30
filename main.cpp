#include "headers/irc.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        CERR "./ircserv <port> <password>" ENDL;
        exit(1);
    }
    launch_serv(argv[1], argv[2]);
    return 0;
}