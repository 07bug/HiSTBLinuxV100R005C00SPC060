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

int main(int argc,char *argv[])
{
    struct sockaddr_in server_addr;
    int sockfd;
    int len;
    char *buf = "Hello, This is socket client!\n";

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

    sample_printf("Connect sucess, sending msg...");

    while (-1 != send(sockfd, buf, strlen(buf),0))
    {
        sample_printf(".");
    }

    sample_printf("Sending error, Quit now\n");
    close(sockfd);
    return 0;
}

