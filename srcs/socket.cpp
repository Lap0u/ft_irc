#include "../headers/Irc.hpp"
#include "../headers/Server.hpp"

void    launch_serv(std::string port, std::string password)
{
	Server server(atoi(port.c_str()), password);

	int			ret_poll;
	int			n = 0;
	char		recvline[MAXLINE + 1];
	
	while(1)
	{
		ret_poll = poll(server.getSocket(0), server.getSocketSize(), 15000);
		if (ret_poll == -1)
		{
			perror("poll");
			exit (1); // need a clean exit closing all fds
		}
		else if (ret_poll > 0)
		{
			for (nfds_t i = 0; i < server.getSocketSize(); i++)
			{
				// fd is ready for reading
				if (server.getSocket(i)->revents == POLLIN)
				{
					// request for connection
					if (i == 0)
					{
						server.connectionRequest();
					}
					else // data from an existing connection, recieve it
					{
						memset(recvline, 0, MAXLINE);
						n = recv(server.getSocket(i)->fd, recvline, MAXLINE -1, 0); //flag MSG_DONTWAIT? 
						if (n == -1)
						{
							perror("recv");
							exit(1);
						}
						server.parseCmd(recvline, server.getSocket(i)->fd);
						
					}
				}
			}
		}
	}
	// close(temp_fd);//
}
