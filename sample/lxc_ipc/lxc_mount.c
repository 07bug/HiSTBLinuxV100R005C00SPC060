#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

static int usb_mount(char *dev,char *dir, char *type);
int mount_write(void);
int mount_read(void);

int main(int argc,char *argv[])
{
    char dir[32] = "/mnt";
    char dev[32];
    char type[32];
    int  status = 0;

    if(argc != 3)
    {
        printf("Need to input mount dev ,dir and type\n");
        printf("Example: ./a.out /dev/sda1  ext4\n\n");
        exit(1);
    }

    sprintf(dev,"/dev/%s",argv[1]);
    sprintf(type,"%s",argv[2]);

    status = usb_mount(dev,dir,type);
    if(status == 0 )
    {
        printf("mount success\n");
    }
    else
    {
        printf("mount fail\n");
    }
#undef _RW_TEST
#ifdef _RW_TEST
    status = mount_write();
    if(status == 0 )
    {
        printf("mount write success\n");
    }
    else
    {
        printf("mount write fail\n");
    }

    status = mount_read();
    if(status != 0 )
    {
        printf("mount read fail\n");
    }

    remove("/mnt/tmp.txt");
    umount("/mnt");
#endif
    return 0;
}

static int usb_mount(char *dev,char *dir, char *type)
{
    int status;
    char cmd[128];
    const char* opts = "uid=1000,gid=1000,fmask=007,dmask=007";

    if((strcmp(type,"ext4") == 0) || (strcmp(type,"ext3") == 0) || (strcmp(type,"ext2") == 0) )
    {
        status = mount(dev,dir ,type,MS_NODEV|MS_NOEXEC|MS_NOSUID,NULL);
        chown(dir,1000,1000);
    }
    else if(strcmp(type,"exfat") == 0)
    {
        sprintf(cmd,"mount.exfat -o nosuid,nodev,noexec %s %s",dev,dir);
        status = system(cmd);
    }
    else
    {
        status = mount(dev,dir ,type,MS_NODEV|MS_NOEXEC|MS_NOSUID,opts);
    }

    return status;
}



int mount_write(void)
{
    char buf[] = "number\n";
    FILE * fp;
    fp = fopen("/mnt/tmp.txt","w+");
    if(fp == NULL)
    {
        return -1;
    }

    fwrite(buf, sizeof(buf), 1, fp);
    fclose(fp);
    return 0;
}

int mount_read(void)
{
    char buf[8];
    FILE * fp;
    fp = fopen("/mnt/tmp.txt","r+");
    if(fp == NULL)
    {
        return -1;
    }

    while(feof(fp) != fread(buf, sizeof(buf), 1, fp))
        printf("read success : %s",buf);
    fclose(fp);
    return 0;
}

