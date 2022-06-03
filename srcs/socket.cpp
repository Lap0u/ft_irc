#include "../headers/Irc.hpp"
#include "../headers/Server.hpp"

void    launch_serv(std::string port, std::string password)
{
	Server server(atoi(port.c_str()), password);

	int					ret_poll;
	int					n = 0;
	char                recvline[MAXLINE + 1];
	char                buff[MAXLINE + 1];

	while(1)
	{
		ret_poll = poll(server.getSocketTab(), server.getSocketSize(), 15000);
		if (ret_poll == 0)
		{
			COUT "This server had timeout little buddy" ENDL;
			exit (1); // need a clean exit closing all fds
		}
		else if (ret_poll == -1)
			COUT "A poll error occurs little buddy" ENDL;
		for (nfds_t i = 0; i < server.getSocketSize(); i++)
		{
			t_pollfd*	current_socket = server.getSocketTab() + i;

			// fd == 0 is not expected, as there are socket fds and not stdin
			if (current_socket->fd <= 0)
				continue ;
			
			// fd is ready for reading
			if ((current_socket->revents & POLLIN) == POLLIN)
			{
				
				// request for connection
				if (current_socket->fd == server.getMainSocket())
				{
					server.acceptingRequest();
				}
			}
			else // data from an existing connection, recieve it
			{
				memset(recvline, 0, MAXLINE);
				n = recv(current_socket->fd, recvline, MAXLINE -1, 0); //flag MSG_DONTWAIT? 
				if (n == -1)
					COUT "error recv" ENDL;
				else if (n == 0)
				{
					COUT "Socket close by client" ENDL;
					close(current_socket->fd);
					current_socket->fd *= -1;
				}
				fprintf(stdout, "\n%s\n", recvline);
				if (recvline[n - 1] == '\n' && recvline[n - 2] == '\r')
					break;
				memset(recvline, 0, MAXLINE);
				snprintf((char*)buff, sizeof(buff), "001\r\nWelcome to irc\r\n002\r\nYour host is blabla\r\n003\r\nThis server was created today\r\n004\r\nAll server infos\r\n");
				if (send(current_socket->fd, (char*)buff, strlen((char *)buff), 0) < 0) //flag MSG_DONTWAIT?
				{
					fprintf(stdout, "send failed\n");
					exit(1);
				}
			}	
		}
	}
	// close(temp_fd);//
}
