#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define REG_DEV_NAME    "/dev/register"

#define HI_CRG_REG_BASE_ADDR    0xF8A22000
#define HI_CRG_REG_OFFSET       0xE8

int main(int argc, char *argv[])
{
    int fd = -1;
    unsigned int *vaddr = NULL;

    fd = open(REG_DEV_NAME, O_RDWR | O_NONBLOCK | O_SYNC);
    if (-1 == fd)
    {
        perror("Fail to open "REG_DEV_NAME);
        return errno;
    }

    vaddr = mmap(NULL, 0x100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, HI_CRG_REG_BASE_ADDR);
    if (!vaddr)
    {
        close(fd);

        printf("Fail to mmap\n");

        return -1;
    }

    printf("0x%x: 0x%08x\n", (HI_CRG_REG_BASE_ADDR + HI_CRG_REG_OFFSET), *(vaddr + HI_CRG_REG_OFFSET / 4));

    munmap(vaddr, 0x100);

    close(fd);

    return 0;
}

