#include "../headers/Irc.hpp"
#include "../headers/Server.hpp"



void    launch_serv(std::string port, std::string password)
{
	Server		server(atoi(port.c_str()), password);
	int			ret_poll;
	std::string	recvline;
	std::string	separatedline;
	int			fd;
	
	while(1)
	{
		ret_poll = poll(server.getSocket(0), server.getSocketSize(), 15000);
		COUT "Size" << server.getSocketSize() ENDL;
		if (ret_poll == -1)
		{
			perror("poll");
			exit (1); // need a clean exit closing all fds
		}
		else if (ret_poll == 0)
			continue ;
		// usleep(200);
		for (nfds_t i = 0; i < server.getSocketSize(); i++)
		{
			if ((server.getSocket(i)->revents & POLLIN) == POLLIN)
			{
				server.getSocket(i)->revents = 0;
				if (i == 0)
				{
					fd = accept(server.getMainSocket(), (SA*) NULL, NULL);
					if (fd == -1)
					{
						perror("accept");
						exit(1);
					}
					server.addSocket(fd, POLLIN);
					User *user = new User();
					user->setSocket(fd);
					server.addUser(user);
					// DEB "Sleep" ENDL;
					// usleep(2000);
				}
				else
				
					fd = server.getSocket(i)->fd;
				// while (1)
				// {
				DEB "Tour" ENDL;
				COUT "Will try to read" ENDL;
				recvline = server.getPackage(fd, true);
				if (recvline.empty())
				{	COUT "Continue" ENDL;
					continue ;}
				COUT recvline << " and size " << recvline.size() ENDL;
				while (recvline.find("\r\n") != std::string::npos)
				{
					separatedline = recvline.substr(0, recvline.find("\r\n"));
					server.parseCmd(separatedline, fd);
					recvline.erase(0, recvline.find("\r\n") + 2);
				}
				recvline.clear();
				// }
			}
		}
	}
	// close(temp_fd);//
}
