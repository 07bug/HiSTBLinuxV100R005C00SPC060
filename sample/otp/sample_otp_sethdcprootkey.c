#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include "hi_unf_otp.h"
#include "hi_type.h"

static HI_S32 print_buffer(HI_CHAR *str, HI_U8 *buf, HI_U32 len)
{
    HI_U32 i;

    if ( (NULL == buf) || (NULL == str) )
    {
        printf("Null pointer input in function print_buf!\n");
        return HI_FAILURE;
    }

    printf("%s:\n", str);
    for ( i = 0 ; i < len ; i++ )
    {
        if ( ( i != 0) && ( (i% 16) == 0) )
        {
            printf("\n");
        }
        printf("%x ", buf[i]);
    }
    printf("\n");

    return HI_SUCCESS;
}

HI_S32 main(int argc, char *argv[])
{
    HI_S32 ret = HI_SUCCESS;
    HI_U8 hdcp_rootKey[16] = {0x12,0x34,0x56,0x78,0,0,0,0,0,0,0,0,0,0,0,0};

    ret = HI_UNF_OTP_Init();
	if(HI_SUCCESS != ret)
	{
		printf("OTP init failed, ret = 0x%x \n", ret);
		return HI_FAILURE;
	}

    ret = HI_UNF_OTP_WriteHdcpRootKey(hdcp_rootKey, 16);
	if(HI_SUCCESS != ret)
	{
		printf("Write hdcp rootKey failed, ret = 0x%x \n", ret);
		(HI_VOID)HI_UNF_OTP_DeInit();
		return HI_FAILURE;
	}

    print_buffer("Set hdcp root key", hdcp_rootKey, sizeof(hdcp_rootKey));

    (HI_VOID)HI_UNF_OTP_DeInit();

    return HI_SUCCESS;
}

