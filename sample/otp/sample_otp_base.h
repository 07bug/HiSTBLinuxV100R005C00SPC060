#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include "hi_type.h"
#include "hi_error_mpi.h"

#define sample_printf printf

typedef struct otp_sample OTP_SAMPLE;
struct otp_sample
{
    HI_U32  index;
    HI_CHAR name[32];
    HI_S32(*run_sample)(HI_S32 ,HI_CHAR**,OTP_SAMPLE *);
    HI_U8   help[3][128];
};

HI_BOOL case_strcmp(const HI_CHAR *s1,const HI_CHAR *s2)
{
    HI_U32 s1_len = strlen(s1);
    HI_U32 s2_len = strlen(s2);

    if (s1_len == s2_len && s1_len > 0)
    {
        return (0 == strncasecmp(s1, s2, s1_len)) ? HI_TRUE : HI_FALSE;
    }

    return HI_FALSE;
}

HI_VOID print_buffer(HI_CHAR* pString, HI_U8* pu8Buf, HI_U32 u32Len)
{
    HI_U32 i;

    if ( (NULL == pu8Buf) || (NULL == pString) )
    {
        sample_printf("null pointer input in function print_buf!\n");
        return ;
    }

    sample_printf("%s:\n", pString);

    for ( i = 0 ; i < u32Len ; i++ )
    {
        if ( ( i != 0) && ( (i % 16) == 0) )
        {
            sample_printf("\n");
        }

        sample_printf("%02x ", pu8Buf[i]);
    }

    sample_printf("\n");
}

HI_VOID show_usage(OTP_SAMPLE sample_table[], HI_U32 len)
{
    HI_U32 i = 0, k = 0;
    sample_printf("Usage:\n");
    sample_printf("----------------------------------------------------\n");

    for (i = 0; i < len; i++)
    {
        sample_printf("    %10s %-16s %s\n","name:", sample_table[i].name, sample_table[i].help[0]);
        for (k = 1; k < sizeof(sample_table[i].help) / sizeof(sample_table[i].help[0]); k++)
        {
            if (sample_table[i].help[k][0] == 0)
            {
                break;
            }
            sample_printf("    %10s %-16s %s\n","","", sample_table[i].help[k]);
        }
    }
}


void show_returne_msg(OTP_SAMPLE sample_table[], HI_U32 len,HI_S32 ret)
{
    if (HI_SUCCESS == ret)
    {
        sample_printf("Sample executed successfully. \n");
        return ;
    }

    if (HI_ERR_OTP_NOT_SUPPORT_INTERFACE == ret)
    {
        sample_printf("This chipset not support this interface. ret:0X%X\n", ret);
    }
    else
    {
        sample_printf("Sample executed failed. ret:0X%X\n", ret);

    }
    if (HI_ERR_OTP_INVALID_PARA == ret )
    {
        show_usage(sample_table, len);
    }
}

