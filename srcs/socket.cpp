#include "../headers/Irc.hpp"
#include "../headers/Server.hpp"

void    launch_serv(std::string port, std::string password)
{
	Server		server(atoi(port.c_str()), password);
	int			ret_poll;
	std::string	recvline;
	
	while(1)
	{
		ret_poll = poll(server.getSocket(0), server.getSocketSize(), 15000);
		if (ret_poll == -1)
		{
			perror("poll");
			exit (1); // need a clean exit closing all fds
		}
		else if (ret_poll == 0)
			continue ;
		for (nfds_t i = 0; i < server.getSocketSize(); i++)
		{
			if (server.getSocket(i)->revents == POLLIN)
			{
				if (i == 0)
					server.connectionRequest();
				else
				{
					recvline = getPaquet(server.getSocket(i)->fd);
					std::cout << "recvline: |" << recvline << "|"<< std::endl;
					server.parseCmd(recvline, server.getSocket(i)->fd);
				}
			}
		}
	}
	// close(temp_fd);//
}
