#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<errno.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/wait.h>


#ifdef CONFIG_SUPPORT_CA_RELEASE
#define sample_printf
#else
#define sample_printf printf
#endif

#define exit_err(str) do{perror(str);exit(0);}while(0);
#define BUFFER_SIZE 1024
#define PORT 4444
#define LIS_NUM 5

void signal_handler(int signo)
{
    pid_t pid;
    int stat;
    while((pid = waitpid(-1,&stat,WNOHANG)) > 0)
        sample_printf("Child pid=%d\n",pid);
    return;
}

void str_echo(int client_sockfd)
{
    char buffer[BUFFER_SIZE];
    while(1)
    {
        memset(buffer,0,sizeof(buffer));
        if(recv(client_sockfd,buffer,sizeof(buffer),MSG_WAITALL) > 0)
        {
            sample_printf("Recieve buffer=%s",buffer);
        }
        else
        {
            exit(0);
        }
    }
    return;
}

int main()
{
    int server_sockfd,client_sockfd;
    socklen_t len;
    pid_t pid;
    int reuse=1;
    struct sockaddr_in server_addr,client_addr;
    struct sigaction sigact;

    bzero(&server_addr,sizeof(server_addr));
    bzero(&server_addr,sizeof(server_addr));

    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(PORT);

    if((server_sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
        exit_err("Socket error!");
    if((setsockopt(server_sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse)))==-1)
        exit_err("Setsockopt error!");
    if(bind(server_sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr))==-1)
        exit_err("Bind error!");
    if(listen(server_sockfd,LIS_NUM)==-1)
        exit_err("Listen error!");

    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags=0;
    sigact.sa_handler=signal_handler;
    sigaction(SIGCHLD,&sigact,NULL);

    while(1)
    {
        len = sizeof(client_addr);
        if((client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_addr,&len))<0)
        {
            if(errno == EINTR)
                continue;
            else
                exit_err("Accept error!");
        }

        if((pid = fork()) == 0)
        {
            sample_printf("Accept successed!!!\n");
            close(server_sockfd);
            str_echo(client_sockfd);
            exit(0);
        }
        close(client_sockfd);
    }
    return 0;
}

