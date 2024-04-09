#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "hi_type.h"
#include "hi_loader_info_v2.h"

#include "loader_flash.h"
#include "loader_osal.h"

#define LOADER_PrintFuncErr(Func, ErrCode)      printf("> [%s][%u] Call [%s] return [0x%08x]\n", __FUNCTION__, __LINE__, #Func, ErrCode);
#define LOADER_PrintErrInfo(ErrInfo)            printf("> [%s][%u] Error info: %s \n", __FUNCTION__, __LINE__, ErrInfo);
#define LOADER_Notice(pszFormat...)             printf("> "); printf(pszFormat);
#define LOADER_Print(pszFormat...)              printf(pszFormat);
#define LOADER_CHECK(func)                                  \
    {                                                       \
        HI_S32 s32ErrCode = func;                           \
        if (HI_SUCCESS != s32ErrCode)                       \
        {                                                   \
            LOADER_PrintFuncErr(#func, s32ErrCode);         \
        }                                                   \
    }
#define LOADER_CHECK_INPUTPARAM(val)                        \
    {                                                       \
        if (val)                                            \
        {                                                   \
            LOADER_PrintErrInfo("Input Error!");            \
            return -1;                                      \
        }                                                   \
    }

#define LOADER_PrintBuf(pcNotice, pu8Input, u32Length)  \
{  \
    HI_U32 u32ii = 0;  \
    HI_CHAR aciOutStr[64] = {0};  \
    HI_CHAR* pciBuffer = (HI_CHAR*)(pu8Input);  \
    printf(" %s\n", pcNotice);  \
    for (u32ii = 0; u32ii < (u32Length); u32ii++)  \
    {  \
        if((u32ii % 16 == 0)  \
           && (u32ii != 0))  \
        {  \
            printf("%s\n", aciOutStr);  \
            printf(aciOutStr, 0x00, sizeof(aciOutStr));\
        }  \
        snprintf(&aciOutStr[(u32ii % 16) * 3], 4, " %02X", pciBuffer[u32ii]);  \
    }  \
    if(u32ii != 0)  \
    { \
        printf("%s\n", aciOutStr);  \
        printf(aciOutStr, 0x00, sizeof(aciOutStr));\
    }\
}

#define LOADER_PARTSIZE_TEEOS          (0x02000000)

HI_VOID ShowUsageInfo(HI_VOID)
{
    LOADER_Notice("usage: sample_backup main_partition back_partition.\n");
    LOADER_Notice("command as follows:\n");
    LOADER_Notice("./sample_backup trustedcore trustedcorebak \n");

    return;
}

static HI_S32 ImageBackup
(
    HI_CHAR*  pu8PartitionNameM,          /** Master Partition  */
    HI_CHAR*  pu8PartitionNameB           /** Backup Partition which to be renew*/
)
{
    HI_U32 u32DataSize = 0;
    LOADER_FLASH_INFO_S stFlashInfoB;
    LOADER_FLASH_INFO_S stFlashInfoM;
    HI_U8* pu8BufferM = HI_NULL_PTR;
    HI_U8* pu8BufferB = HI_NULL_PTR;
    HI_HANDLE hFlashHandleM = HI_INVALID_HANDLE;
    HI_HANDLE hFlashHandleB = HI_INVALID_HANDLE;

    HI_S32 s32Ret = HI_FAILURE;

    hFlashHandleB = LOADER_FLASH_OpenByName(pu8PartitionNameB);
    if (HI_INVALID_HANDLE == hFlashHandleB)
    {
        LOADER_PrintFuncErr(LOADER_FLASH_OpenByName, -1);
        return -1;
    }

    hFlashHandleM = LOADER_FLASH_OpenByName(pu8PartitionNameM);
    if (HI_INVALID_HANDLE == hFlashHandleM)
    {
        LOADER_PrintFuncErr(LOADER_FLASH_OpenByName, -1);

        LOADER_FLASH_Close(hFlashHandleB);
        hFlashHandleB = HI_NULL_PTR;

        return -1;
    }

    LOADER_MemSet(&stFlashInfoM, 0x00, sizeof(stFlashInfoM));
    s32Ret = LOADER_FLASH_GetInfo(hFlashHandleM, &stFlashInfoM);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(LOADER_FLASH_GetInfo, s32Ret);

        LOADER_FLASH_Close(hFlashHandleM);
        hFlashHandleM = HI_NULL_PTR;

        LOADER_FLASH_Close(hFlashHandleB);
        hFlashHandleB = HI_NULL_PTR;

        return s32Ret;
    }

    LOADER_MemSet(&stFlashInfoB, 0x00, sizeof(stFlashInfoB));
    s32Ret = LOADER_FLASH_GetInfo(hFlashHandleB, &stFlashInfoB);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(LOADER_FLASH_GetInfo, s32Ret);

        LOADER_FLASH_Close(hFlashHandleM);
        hFlashHandleM = HI_NULL_PTR;

        LOADER_FLASH_Close(hFlashHandleB);
        hFlashHandleB = HI_NULL_PTR;

        return s32Ret;
    }

    if (stFlashInfoM.u64PartSize > stFlashInfoB.u64PartSize)
    {
        LOADER_FLASH_Close(hFlashHandleM);
        hFlashHandleM = HI_NULL_PTR;

        LOADER_FLASH_Close(hFlashHandleB);
        hFlashHandleB = HI_NULL_PTR;

        return -1;
    }

    pu8BufferM = LOADER_MemMalloc(LOADER_PARTSIZE_TEEOS);
    if (HI_NULL_PTR == pu8BufferM)
    {
        LOADER_PrintFuncErr(LOADER_MemMalloc, -1);

        LOADER_FLASH_Close(hFlashHandleM);
        hFlashHandleM = HI_NULL_PTR;

        LOADER_FLASH_Close(hFlashHandleB);
        hFlashHandleB = HI_NULL_PTR;

        return -1;
    }

    u32DataSize = LOADER_FLASH_Read(hFlashHandleM, 0ULL, pu8BufferM, LOADER_PARTSIZE_TEEOS, stFlashInfoM.u64PartSize);
    if (stFlashInfoM.u64PartSize > u32DataSize)
    {
        LOADER_PrintFuncErr(LOADER_FLASH_Read, -1);

        LOADER_MemFree(pu8BufferM);

        LOADER_FLASH_Close(hFlashHandleM);
        hFlashHandleM = HI_NULL_PTR;

        LOADER_FLASH_Close(hFlashHandleB);
        hFlashHandleB = HI_NULL_PTR;


        return -1;
    }

    pu8BufferB = LOADER_MemMalloc(LOADER_PARTSIZE_TEEOS);
    if (HI_NULL_PTR == pu8BufferB)
    {
        LOADER_PrintFuncErr(LOADER_MemMalloc, -1);

        LOADER_MemFree(pu8BufferM);

        LOADER_FLASH_Close(hFlashHandleM);
        hFlashHandleM = HI_NULL_PTR;

        LOADER_FLASH_Close(hFlashHandleB);
        hFlashHandleB = HI_NULL_PTR;

        return -1;
    }

    u32DataSize = LOADER_FLASH_Read(hFlashHandleB, 0ULL, pu8BufferB, LOADER_PARTSIZE_TEEOS, stFlashInfoB.u64PartSize);
    if (stFlashInfoB.u64PartSize > u32DataSize)
    {
        LOADER_PrintFuncErr(LOADER_FLASH_Read, -1);

        LOADER_MemFree(pu8BufferM);
        LOADER_MemFree(pu8BufferB);

        LOADER_FLASH_Close(hFlashHandleM);
        hFlashHandleM = HI_NULL_PTR;

        LOADER_FLASH_Close(hFlashHandleB);
        hFlashHandleB = HI_NULL_PTR;

        return -1;
    }

    if (0 == LOADER_MemCmp(pu8BufferM, pu8BufferB, stFlashInfoM.u64PartSize))
    {
        LOADER_Print("The image in main partition is equal to the image in back partition! \n");
    }
    else
    {
        s32Ret = LOADER_FLASH_Write(hFlashHandleB, 0ULL, pu8BufferM, stFlashInfoM.u64PartSize);
        if (HI_SUCCESS != s32Ret)
        {
            LOADER_PrintFuncErr(LOADER_FLASH_Write, s32Ret);

            LOADER_MemFree(pu8BufferM);
            LOADER_MemFree(pu8BufferB);

            LOADER_FLASH_Close(hFlashHandleM);
            hFlashHandleM = HI_NULL_PTR;

            LOADER_FLASH_Close(hFlashHandleB);
            hFlashHandleB = HI_NULL_PTR;

            return s32Ret;
        }
    }

    LOADER_MemFree(pu8BufferM);
    LOADER_MemFree(pu8BufferB);

    LOADER_FLASH_Close(hFlashHandleM);
    hFlashHandleM = HI_NULL_PTR;

    LOADER_FLASH_Close(hFlashHandleB);
    hFlashHandleB = HI_NULL_PTR;

    return HI_SUCCESS;
}

HI_S32 main(HI_S32 argc, HI_CHAR* argv[])
{
    int ret = 0;

    if (3 != argc)
    {
        ShowUsageInfo();
        return 0;
    }

    ret = HI_SYS_Init();
    if (HI_SUCCESS != ret)
    {
		LOADER_PrintErrInfo("call HI_SYS_Init failed.\n");
		return ret;
	}

    ret = ImageBackup(argv[1], argv[2]);
    if (HI_SUCCESS != ret)
    {
		LOADER_PrintErrInfo("call ImageRenew failed.\n");
		return ret;
	}

    return 0;
}

