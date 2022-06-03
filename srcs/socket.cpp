#include "../headers/Irc.hpp"
#include "../headers/Server.hpp"

void    launch_serv(std::string port, std::string password)
{
	Server server(atoi(port.c_str()), password);

	int 				temp_fd;
	int					n = 0;

	char                recvline[MAXLINE + 1];
	char                buff[MAXLINE + 1];
	
	while(1)
	{        
		temp_fd = accept(server.getMainSocket(), (SA*) NULL, NULL);
		memset(recvline, 0, MAXLINE);
		// user1._socket = temp_fd;
		// server.addUser(&user1, temp_fd);
		server.setup_connection(temp_fd);
		if (server.getSocketSize())
		{
			if (poll(server.getSocketTab(), server.getSocketSize(), 5000) > 0)
			{//il faudra lire sur les fd qui ont ete modifie dans recv, pas juste temp_fd
				while ((n = recv(temp_fd, recvline, MAXLINE -1, 0)) > 0) //flag MSG_DONTWAIT? 
				{
					fprintf(stdout, "\n%s\n", recvline);
					if (recvline[n - 1] == '\n' && recvline[n - 2] == '\r')
						break;
				}
				memset(recvline, 0, MAXLINE);           
				if (n < 0)
				{
					fprintf(stdout, "Connection closed\n");
					exit(1);
				}
				snprintf((char*)buff, sizeof(buff), "001\r\nWelcome to irc\r\n002\r\nYour host is blabla\r\n003\r\nThis server was created today\r\n004\r\nAll server infos\r\n");
				if (send(temp_fd, (char*)buff, strlen((char *)buff), 0) < 0) //flag MSG_DONTWAIT?
				{
					fprintf(stdout, "send failed\n");
					exit(1);
				}
			}
		}
	}
	close(temp_fd);//
}
