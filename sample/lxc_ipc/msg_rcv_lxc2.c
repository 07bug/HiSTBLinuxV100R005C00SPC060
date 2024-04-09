#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#define MSGKEY 1024

struct msgstru
{
    long msgtype;
    char msgtext[2048];
};

int  main()
{
    struct msgstru msgs;
    int msgid = 0;
    int ret = 0;
    int i = 60;

    msgid=msgget(MSGKEY,IPC_EXCL);
    if(msgid < 0)
    {
        sample_printf("failed to get msq | errno=%d [%s]\n",errno,strerror(errno));
        exit(-1);
    }

    while(i--)
    {
        ret = msgrcv(msgid,&msgs,sizeof(struct msgstru),0,MSG_NOERROR);
        if ( ret < 0 )
        {
            sample_printf("msgrcv() read msg failed,errno=%d[%s]\n",errno,strerror(errno));
            exit(-1);
        }
        sample_printf("[lxc2] receive string : %s\n",msgs.msgtext);
    }
    return 0;
}

