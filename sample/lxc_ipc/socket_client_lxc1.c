#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include"common.h"

#define exit_err(str) do{perror(str);exit(1);}while(0);
#define PORT 4444
#define BUFFER_SIZE 1024

void str_cli(int sockfd);

int main(int argc,char *argv[])
{
    struct sockaddr_in server_addr;
    int sockfd;
    int len;

    if(argc != 2)
    {
        exit_err("Need server ip");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
        exit_err("Socket error");

    len = sizeof(struct sockaddr);
    if(connect(sockfd,(struct sockaddr *)&server_addr,len) == -1)
        exit_err("Connect error");

    sample_printf("Connect sucess!!!\n");

    str_cli(sockfd);
    close(sockfd);
    return 0;
}

void str_cli(int sockfd)
{
    int n = 0;
    int maxfd = 0;
    int stdineof = 0;
    fd_set readfd;
    char buf[BUFFER_SIZE];
    struct timeval tv;

    tv.tv_sec = 0;
    tv.tv_usec = 0;
    maxfd = sockfd + 1;

    FD_ZERO(&readfd);

    while(1)
    {
        if(0 == stdineof)
            FD_SET(STDIN_FILENO,&readfd);

        FD_SET(sockfd,&readfd);
        select(maxfd,&readfd,NULL,NULL,&tv);
        if(FD_ISSET(sockfd,&readfd))
        {
            memset(buf,0,sizeof(buf));
            n = recv(sockfd,buf,sizeof(buf),MSG_WAITALL);
            if(0 == n)
            {
                if(stdineof == 1)
                {
                    return;
                }
                else
                {
                    sample_printf("str_cli:server terminated prematurely!!!\n");
                    return;
                }
            }
            else if(-1 == n)
            {
                exit_err("Recieve error!!!");
            }
        }

        if(FD_ISSET(STDIN_FILENO,&readfd))
        {
            if(fgets(buf,sizeof(buf),stdin) == NULL)
            {
                stdineof = 1;
                shutdown(sockfd,SHUT_WR);
                FD_CLR(STDIN_FILENO,&readfd);
                continue;
            }
            else if(send(sockfd,buf,sizeof(buf),0) == -1)
                exit_err("Send error");
        }
    }
}

