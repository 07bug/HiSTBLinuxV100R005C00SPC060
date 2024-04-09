#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
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
int msgid = 0;
int shmid = 0;
int ret   = 0;
char *p_addr = NULL;

void msg_init(void);
void shm_init(void);

int main()
{
    int i = 20;
    msg_init();
    shm_init();

    while(i--)
    {
        ret = msgrcv(msgid,&msgs,sizeof(struct msgstru),0,MSG_NOERROR);
        if ( ret < 0 )
        {
            sample_printf("msgrcv() read msg failed,errno=%d[%s]\n",errno,strerror(errno));
            exit(-1);
        }
        sample_printf("[lxc2] read data %s from addr %p\n",p_addr,p_addr);
        memset(p_addr,'\0',BUF_LEN);
    }
    return 0;
}

void msg_init(void)
{
    msgid=msgget(MSGKEY,IPC_EXCL);
    if(msgid < 0)
    {
        sample_printf("failed to get msq | errno=%d [%s]\n",errno,strerror(errno));
        exit(-1);
    }
}

void shm_init(void)
{
    if((shmid = shmget((key_t)1234,BUF_LEN,0666)) == -1)
    {
        if((shmid = shmget((key_t)1234,BUF_LEN,0666 | IPC_CREAT)) == -1)
              exit_err("shmget error");
    }

    if((p_addr = (char *)shmat(shmid,0,0)) == (char *)-1)
    {
        exit_err("shmat error");
    }
}
