#include "headers/Irc.hpp"
#include "headers/Server.hpp"
#include "headers/User.hpp"

int main(int argc, char **argv)
{
    (void)argv;
    if (argc != 3)
    {
        CERR "./ircserv <port> <password>" ENDL;
        exit(1);
    }
    // launch_serv(argv[1], argv[2]);
    Server serv;
    User user1(1, "nom1", "nom1", "nom1", "nom1");
    User user2(2, "nom2", "nom2", "nom2", "nom2");
    User user3(2, "nom3", "nom2", "nom2", "nom2");
    User user4(2, "nom3", "nom2", "nom2", "nom2");
    serv.addUser(&user1, 1);
    serv.addUser(&user2, 2);
    serv.addUser(&user3, 3);
    serv.addUser(&user4, 4);
    return 0;
}