#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define SERVER_PORT 18000
#define MAXLINE 4096
#define SA struct sockaddr

int main()
{
    int listenfd;
    int conffd;
    int n = 0;

    struct sockaddr_in  servaddr;
    uint8_t             recvline[MAXLINE + 1];
    uint8_t             buff[MAXLINE + 1];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0)
        exit(1);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family         = AF_INET;
    servaddr.sin_addr.s_addr    = htonl(INADDR_ANY);
    servaddr.sin_port           = htons(SERVER_PORT);

    if ((bind(listenfd, (SA *) &servaddr, sizeof(servaddr))) < 0)
        exit(1);
    if ((listen(listenfd, 10)) < 0)
        exit(1);
    while(1)
    {
        struct sockaddr_in addr;
        socklen_t   addr_len;
        printf("Waiting\n");fflush(stdout);
        conffd = accept(listenfd, (SA*) NULL, NULL);

        memset(recvline, 0, MAXLINE);
        while ((n = read(conffd, recvline, MAXLINE -1)) > 0)
        {
            fprintf(stdout, "\n%s\n", recvline);
            if (recvline[n - 1] == '\n')
                break;
            memset(recvline, 0, MAXLINE);
        }
        if (n < 0)
            exit(1);
        snprintf((char*)buff, sizeof(buff), "HTTP/1.0 200 OK\r\n\r\nHello   ");
        write(conffd, (char*)buff, strlen((char *)buff));
        close(conffd);
    }
}