#include "../headers/irc.h"

void    launch_serv(std::string port, std::string password)
{
    (void)password; // on en fait quoi????

    int listenfd;
    int conffd;
    int n = 0;

    struct sockaddr_in  servaddr;
    char                recvline[MAXLINE + 1];
    char                buff[MAXLINE + 1];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0)
        exit(1);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family         = AF_INET;
    servaddr.sin_addr.s_addr    = htonl(INADDR_ANY);
    servaddr.sin_port           = htons(atoi(port.c_str()));

    if ((bind(listenfd, (SA *) &servaddr, sizeof(servaddr))) < 0)
    {
        fprintf(stdout, "bind\n");
        exit(1);
    }

    if ((listen(listenfd, 10)) < 0)
    {
        fprintf(stdout, "listen\n");
        exit(1);
    };
    while(1)
    {        
        printf("Waiting\n");fflush(stdout);
        conffd = accept(listenfd, (SA*) NULL, NULL);

        memset(recvline, 0, MAXLINE);
        while (1)
        {
            while ((n = recv(conffd, recvline, MAXLINE -1, 0)) > 0) //flag MSG_DONTWAIT? 
            {
                fprintf(stdout, "\n%s\n", recvline);
                if (recvline[n - 1] == '\n')
                    break;
            }
            memset(recvline, 0, MAXLINE);           
            if (n < 0)
            {
                fprintf(stdout, "Connection closed\n");
                exit(1);
            }
            snprintf((char*)buff, sizeof(buff), "HTTP/1.0 200 OK\r\n\r\n001   ");
            if (send(conffd, (char*)buff, strlen((char *)buff), 0) < 0) //flag MSG_DONTWAIT?
            {
                fprintf(stdout, "send\n");
                exit(1);
            }
            fprintf(stdout, "we sent\n");
        }
        close(conffd);
    }
}