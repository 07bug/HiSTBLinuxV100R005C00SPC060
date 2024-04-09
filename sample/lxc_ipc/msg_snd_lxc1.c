#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include "common.h"

#define exit_err(str) do{perror(str);exit(1);}while(0);
#define MSGKEY  1024
#define BUF_LEN 1024


struct msgstru
{
    long msgtype;
    char msgtext[2048];
};

struct msgstru msgs;
int msqid = 0;
long flag = 1;
char *p_addr = NULL;

void sig_handler(int signo);
void msg_init(void);
void sig_init(void);

int main()
{
    char str[256];
    int   ret_value;

    sig_init();
    msg_init();

    while(flag)
    {
        memset(&msgs,'\0',sizeof(msgs));
        msgs.msgtype = flag;
        sprintf(str,"%ld",flag);
        strcpy(msgs.msgtext, str);

        ret_value = msgsnd(msqid,&msgs,sizeof(struct msgstru),IPC_NOWAIT);
        if ( ret_value < 0 )
        {
            sample_printf("msgsnd() write msg failed,errno=%d[%s]\n",errno,strerror(errno));
            msgctl(msqid,IPC_RMID,0);
            exit(-1);
        }

        sleep(1);
        flag++;
    }
    return 0;
}

void sig_handler(int signo)
{
    switch(signo)
    {
        case SIGINT:
            {
                msgctl(msqid,IPC_RMID,0);
                exit(0);
                break;
            }
    }
}

void msg_init(void)
{
    msqid=msgget(MSGKEY,IPC_EXCL);
    if(msqid < 0)
    {
        msqid = msgget(MSGKEY,IPC_CREAT|0666);
        if(msqid <0)
        {
            sample_printf("failed to create msq | errno=%d [%s]\n",errno,strerror(errno));
            exit(-1);
        }
    }
}

void sig_init(void)
{
    if(signal(SIGINT,sig_handler) == SIG_ERR)
    {
        sample_printf("signal errror\n");
        exit(0);
    }
}


