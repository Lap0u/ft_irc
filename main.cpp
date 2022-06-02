#include "headers/Irc.hpp"
#include "headers/Server.hpp"
#include "headers/User.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv)
{
	(void)argv;
	if (argc != 3)
	{
		CERR "./ircserv <port> <password>" ENDL;
		exit(1);
	}
	launch_serv(argv[1], argv[2]);

	// int fd[4];

	// fd[0] = open("file1", 644);
	// fd[1] = open("file2", 644);
	// fd[2] = open("file3", 644);
	// fd[3] = open("file4", 644);

	// Server serv;
	// User user1(fd[0], "nom1", "nom1", "nom1", "nom1");
	// User user2(fd[1], "nom2", "nom2", "nom2", "nom2");
	// User user3(fd[2], "nom3", "nom2", "nom2", "nom2");
	// User user4(fd[3], "nom3", "nom2", "nom2", "nom2");
	
	// serv.addUser(&user1, 1);
	// serv.addUser(&user2, 2);
	// serv.addUser(&user3, 3);
	// serv.addUser(&user4, 4);
	// poll(serv.getSocketTab(), serv.getSocketSize(), 5000);
	// return 0;
}