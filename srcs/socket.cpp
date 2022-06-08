#include "../headers/Irc.hpp"
#include "../headers/Server.hpp"

void    launch_serv(std::string port, std::string password)
{
	Server server(atoi(port.c_str()), password);

	int			ret_poll;
	int			n = 0;
	char		recvline[MAXLINE + 1];
	char		buff[MAXLINE + 1];
	t_pollfd	*sock_tab;

	while(1)
	{
		sock_tab = server.getSocketTab();

		ret_poll = poll(sock_tab, server.getSocketSize(), 15000);
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
				if (sock_tab[i].revents == POLLIN)
				{
					// request for connection
					if (i == 0)
					{
						server.connectionRequest();
					}
					else // data from an existing connection, recieve it
					{
						CERR "sortie 4" ENDL;
						memset(recvline, 0, MAXLINE);
						n = recv(sock_tab[i].fd, recvline, MAXLINE -1, 0); //flag MSG_DONTWAIT? 
						if (n == -1)
						{
							perror("recv");
							exit(1);
						}
						else if (n == 0)
						{
							CERR "-->Socket close by client" ENDL;
							close(sock_tab[i].fd);
							sock_tab[i].fd = -1;
						}
						fprintf(stdout, "\n-->%s\n", recvline);
						// if (recvline[n - 1] == '\n' && recvline[n - 2] == '\r')
						// 	break;
						memset(recvline, 0, MAXLINE);
						snprintf((char*)buff, sizeof(buff), "salut\r\n");
						CERR "sortie 3" ENDL;
						if (send(sock_tab[i].fd, (char*)buff, strlen((char *)buff), 0) < 0) //flag MSG_DONTWAIT?
						{
							perror("send");
							exit(1);
						}
					}
				}
			}
		}
	}
	// close(temp_fd);//
}
