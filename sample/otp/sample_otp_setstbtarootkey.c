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
    HI_U8 stb_ta_rootKey[16] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};

    ret = HI_UNF_OTP_Init();
    if(HI_SUCCESS != ret)
    {
		printf("OTP init failed, ret = 0x%x \n", ret);
        return HI_FAILURE;
    }

    ret = HI_UNF_OTP_SetRootKey(HI_UNF_OTP_STBTA_ROOTKEY, stb_ta_rootKey, 16);
    if(HI_SUCCESS != ret)
    {
		printf("Write STB TA rootKey failed, ret = 0x%x \n", ret);
        (HI_VOID)HI_UNF_OTP_DeInit();
        return HI_FAILURE;
    }

    print_buffer("Set STB TA root key", stb_ta_rootKey, sizeof(stb_ta_rootKey));

    (HI_VOID)HI_UNF_OTP_DeInit();

    return HI_SUCCESS;
}




