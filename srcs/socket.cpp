#include "../headers/Irc.hpp"
#include "../headers/Server.hpp"

void    launch_serv(std::string port, std::string password)
{
	Server server(atoi(port.c_str()), password);

	int					ret_poll;
	int					n = 0;
	char                recvline[MAXLINE + 1];
	char                buff[MAXLINE + 1];
	t_pollfd			*sock_tab;

	while(1)
	{
		sock_tab = server.getSocketTab();

		ret_poll = poll(sock_tab, server.getSocketSize(), 15000);
		if (ret_poll == 0)
		{
			CERR "This server had timeout little buddy" ENDL;
		}
		else if (ret_poll == -1)
		{
			CERR "A poll error occurs little buddy" ENDL;
			exit (1); // need a clean exit closing all fds
		}
		for (nfds_t i = 0; i < server.getSocketSize(); i++)
		{
			// fd == 0 is not expected, as there are socket fds and not stdin
			if (sock_tab[i].fd <= 0)
				continue ;
			
			// fd is ready for reading
			if ((sock_tab[i].revents & POLLIN) == POLLIN)
			{
				// request for connection
				if (i == 0)
				{
					server.acceptingRequest();
				}
				else // data from an existing connection, recieve it
				{
					memset(recvline, 0, MAXLINE);
					n = recv(sock_tab[i].fd, recvline, MAXLINE -1, 0); //flag MSG_DONTWAIT? 
					if (n == -1)
						CERR "error recv" ENDL;
					else if (n == 0)
					{
						CERR "Socket close by client" ENDL;
						close(sock_tab[i].fd);
						sock_tab[i].fd = -1;
					}
					fprintf(stdout, "\n%s\n", recvline);
					if (recvline[n - 1] == '\n' && recvline[n - 2] == '\r')
						break;
					memset(recvline, 0, MAXLINE);
					snprintf((char*)buff, sizeof(buff), "001\r\nWelcome to irc\r\n002\r\nYour host is blabla\r\n003\r\nThis server was created today\r\n004\r\nAll server infos\r\n");
					if (send(sock_tab[i].fd, (char*)buff, strlen((char *)buff), 0) < 0) //flag MSG_DONTWAIT?
					{
						fprintf(stdout, "send failed\n");
						exit(1);
					}
				}
			}	
		}
	}
	// close(temp_fd);//
}
