#include "hi_unf_otp.h"
#include<sys/mman.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include <errno.h>
#include<stdlib.h>

#define PAGE_SHIFT  0xc
#define PAGE_NUM_SHIFT          0 /* it depends on how many pages can be maped, 0:one page, 1:two pages, 2:four pages, 3: eight pages */
#define OTP_MAP_PAGE_NUM        (1ULL << PAGE_NUM_SHIFT)
#define OTP_MAP_MASK            (((OTP_MAP_PAGE_NUM) << PAGE_SHIFT) - 1)

HI_VOID print_buffer(char* str, char* buf, int len)
{
    HI_U32 i = 0;

    if ( (NULL == buf) || (NULL == str) )
    {
        printf("Null pointer input in function print_buf!\n");
        return ;
    }
    printf("%s:\n", str);
    for ( i = 0 ; i < len ; i+=4 )
    {
        if ( ( i != 0) && ( (i % 16) == 0) )
        {
            printf("\n");
        }
        if ((i % 16) == 0)
        {
            printf("%04x: ", i);
        }
        printf("%08x ", *((unsigned int*)&buf[i]));
    }
    printf("\n");
}

HI_VOID show_usage(HI_VOID)
{
    printf("\nHelp:\n");
    printf("----------------------------------------------------\n");
    printf("./sample /dev/hi_otp 0xf8ab0000 0x1000\n\n");
}

HI_S32 main(HI_S32 argc,HI_CHAR **argv)
{

    HI_S32 fd = 0;
    HI_VOID *p_map;
    HI_U32 len = 0;
    off_t off_addr = 0;

    printf("\n***********begin*********\n");
    if (argc != 4)
    {
        printf("Input para wrong,argc = %d.\n", argc);
        show_usage();
        return HI_SUCCESS;
    }
    len = strtoul(argv[3], NULL, 16);
    off_addr = (off_t)strtoul(argv[2], NULL, 16);
    if (0 != (off_addr & OTP_MAP_MASK) )
    {
        printf("Address has not been aligned 4k.\n");
        show_usage();
        return HI_SUCCESS;
    }

    fd = open(argv[1], O_RDWR, 00777);
    printf("Open file %s fd = %d\n", argv[1], fd);
    if (fd < 0)
    {
        printf("Open file(%s) failed.fd = %d\n", argv[1], fd);
        show_usage();
        return HI_SUCCESS;
    }
    p_map = mmap(NULL, len, PROT_READ, MAP_SHARED,fd, off_addr);
    close(fd);

    if (MAP_FAILED == p_map)
    {
        printf("Mmap failed.\nmmap error:%s\n", strerror(errno));
        return HI_SUCCESS;
    }
    printf("After mmap, p_map = %p.\n", p_map);
    print_buffer("mmap", p_map, len);
    return HI_SUCCESS;
}
