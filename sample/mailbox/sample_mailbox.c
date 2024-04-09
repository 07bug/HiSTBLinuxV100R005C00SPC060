#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include "hi_unf_mailbox.h"
#include "hi_type.h"
#include <sys/time.h>
#include "hi_common.h"

static HI_S32 printBuffer(HI_CHAR *pString, HI_U8 *pu8Buf, HI_U32 u32Len)
{
    HI_U32 i;

    if ( (NULL == pu8Buf) || (NULL == pString) )
    {
        printf("null pointer input in function print_buf!\n");
        return HI_FAILURE;
    }

    printf("%s:\n", pString);
    for ( i = 0 ; i < u32Len ; i++ )
    {
        if ( ( i != 0) && ( (i% 16) == 0) )
        {
            printf("\n");
        }
        printf("%x ", pu8Buf[i]);
    }
    printf("\n");

    return HI_SUCCESS;
}

HI_U8 message1[512] = {0x1, 0x2, 0x3, 0x4, 0x5};
HI_U8 output[4096];

HI_S32 main(int argc, char *argv[])
{
    HI_S32 ret = HI_FAILURE;
    HI_HANDLE handle = HI_INVALID_HANDLE;
    HI_UNF_MAILBOX_BUFFER_S buffer_info;
    HI_U32 outputlength = 4096;
    HI_U32 start, end;
    HI_S32 i;

    HI_SYS_Init();
    ret = HI_UNF_MAILBOX_Init();
	if(HI_SUCCESS != ret)
	{
		printf("HI_UNF_MAILBOX_Init!\n");
		return HI_FAILURE;
	}

    ret = HI_UNF_MAILBOX_Open(&handle, MID_ACPU_COMMON);
	if (HI_SUCCESS != ret)
	{
		printf("HI_UNF_MAILBOX_Open!\n");
		return HI_FAILURE;
	}

    for (i = 0; i < 512; i++)
    {
        message1[i] = i;
    }

    buffer_info.pMessage = message1;
    buffer_info.u32MessageLen = sizeof (message1);
//    buffer_info.u32MessageLen = 1;
    buffer_info.pOutBuffer = output;
    buffer_info.pu32OutBufferLen = &outputlength;

    HI_SYS_GetTimeStampMs(&start);
    ret= HI_UNF_MAILBOX_Send(handle, MID_SCPU_COMMON, &buffer_info, 0, 0);
    if (HI_SUCCESS != ret)
    {
		printf("HI_UNF_MAILBOX_Send!\n");
		return HI_FAILURE;
    }
    HI_SYS_GetTimeStampMs(&end);
    printf("=================================\n");
    printf("end:%u, start:%u, cost:%u\n", end, start, end - start);
    printf("=================================\n");

    printf("receive length:%x\n", outputlength);
    printBuffer("return message", output, outputlength);

    ret= HI_UNF_MAILBOX_Close(handle);
    if (HI_SUCCESS != ret)
    {
		printf("HI_UNF_MAILBOX_Close!\n");
		return HI_FAILURE;
    }

    ret= HI_UNF_MAILBOX_DeInit();
    if (HI_SUCCESS != ret)
    {
		printf("HI_UNF_MAILBOX_DeInit!\n");
		return HI_FAILURE;
    }

    return HI_SUCCESS;
}
