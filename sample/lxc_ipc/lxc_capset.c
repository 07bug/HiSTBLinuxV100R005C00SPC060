#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <errno.h>
#include "capability.h"
#include <time.h>

void list_caps()
{
    cap_t    caps;
    caps = cap_get_proc();
    printf("capabilities: %s\n", cap_to_text(caps, NULL));
    cap_free(caps);
}

int  set_time()
{
    time_t t_t = 0;
    struct timeval tv;
    struct tm info;

    info.tm_year = 2001 - 1900;
    info.tm_mon = 6;
    info.tm_mday = 4;
    info.tm_hour = 0;
    info.tm_min = 0;
    info.tm_sec = 1;
    info.tm_isdst = -1;

    t_t = mktime(&info);
    if(t_t == -1 )
    {
        printf("call mktime fail\n");
        exit(0);
    }

    tv.tv_sec = t_t;
    tv.tv_usec = 0;
    if(settimeofday(&tv, (struct timezone *) 0) < 0)
    {
        printf("Set system datatime fail!\n");
        exit(0);
    }

    return 0;
}

int get_time()
{
    struct  timeval    tv;
    struct  timezone   tz;

    gettimeofday(&tv,&tz);

    printf("tv_sec:%ld\n",tv.tv_sec);
    printf("tv_usec:%ld\n",tv.tv_usec);
    printf("tz_minuteswest:%d\n",tz.tz_minuteswest);
    printf("tz_dsttime:%d\n",tz.tz_dsttime);
    return 0;
}

int main(int argc, char **argv)
{
    unsigned int num_caps = 6;
    cap_t caps = cap_init();

    list_caps();
    printf("--------------------First set time--------------------\n");
    set_time();
    get_time();

    cap_value_t capList[6] = {CAP_CHOWN,CAP_SETGID,CAP_SETUID,CAP_NET_ADMIN,CAP_NET_RAW,CAP_SYS_ADMIN};
    cap_set_flag(caps, CAP_EFFECTIVE, num_caps, capList, CAP_SET);
    cap_set_flag(caps, CAP_INHERITABLE, num_caps, capList, CAP_SET);
    cap_set_flag(caps, CAP_PERMITTED, num_caps, capList, CAP_SET);
    prctl(PR_SET_KEEPCAPS,1);
    cap_set_proc(caps);

    list_caps();
    printf("--------------------Second set time--------------------\n");
    set_time();
    get_time();
    return 0;
}

