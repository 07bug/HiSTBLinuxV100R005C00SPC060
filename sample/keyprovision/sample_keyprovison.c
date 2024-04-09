#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include "hi_type.h"
#include "hi_common.h"
#include "hi_unf_mailbox.h"
#include "mpi_mmz.h"

typedef struct tagIMAGE_HEADER_S
{
    HI_U32   u32PackageType; //0x0 - RootKey
    HI_U32   u32KeyAreaOffset;
    HI_U32   u32DataAreaOffset;
    HI_U32   u32DataAreaLength;
    HI_U32   u32HDCPKeyOffset;
    HI_U32   u32HDCPKeyLength;
    HI_U8    u8Reserved[8];
} IMAGE_HEADER_S;

#define MID_ACPU_KEY_PROVISION            (0x63)
#define MID_SMCU_KEY_PROVISION            (0x22)

#define HDCP_ROOTKEY_PROVISION_TYPE       (0)
#define PLAYREADY_PROVISION_TYPE          (1)
#define WIDEVINE_PROVISION_TYPE           (2)
#define ROOTKEY_PROVISION_TYPE            (3)

#define SMCU_KEYPROVISION_ROOTKEY_TYPE    (0)
#define SMCU_KEYPROVISION_PK_TYPE         (1)

#define SMCU_KEYPROVISION_OK              (0x80510002)

#define KEYPROVISION_ERROR(pszFormat...)             printf("[%s][%u]", __FUNCTION__, __LINE__);printf(pszFormat);

#define KEYPROVISION_PrintFuncErr(Func, ErrCode)     KEYPROVISION_ERROR("Call [%s] return [0x%08X]\n", #Func, ErrCode);
#define KEYPROVISION_PrintErrCode(ErrCode)           KEYPROVISION_ERROR("Error Code: [0x%08X]\n", ErrCode);

#define KEYPROVISION_CHECK_PARAM(val)                   \
{                                                       \
    if (val)                                            \
    {                                                   \
        KEYPROVISION_PrintErrCode(HI_FAILURE);          \
        return HI_FAILURE;                              \
    }                                                   \
}

#define SAMPLE_DEBUG (0)

#if SAMPLE_DEBUG
#define Sample_FuncEnter()                   printf("[%s][%u]", __FUNCTION__, __LINE__);printf(" =====>[Enter]\n")
#define Sample_FuncExit()                    printf("[%s][%u]", __FUNCTION__, __LINE__);printf(" =====>[Exit]\n")

static HI_S32 printBuffer(HI_CHAR *pString, HI_U8 *pu8Buf, HI_U32 u32Len)
{
    HI_U32 i;

    if ( (NULL == pu8Buf) || (NULL == pString) )
    {
        printf("null pointer u32MailboxInput in function print_buf!\n");
        return HI_FAILURE;
    }

    printf("%s:\n", pString);
    for ( i = 0 ; i < u32Len ; i++ )
    {
        if ( ( i != 0) && ( (i% 16) == 0) )
        {
            printf("\n");
        }
        printf("%02x ", pu8Buf[i]);
    }
    printf("\n");

    return HI_SUCCESS;
}

#else
#define Sample_FuncEnter()
#define Sample_FuncExit()

static HI_S32 printBuffer(HI_CHAR *pString, HI_U8 *pu8Buf, HI_U32 u32Len)
{
    return HI_SUCCESS;
}
#endif

HI_S32 MmzMalloc(HI_U32 u32Size, HI_U32* pu32PhyAddr, HI_U8** ppu8VirAddr)
{
    HI_U32 u32PhyAddr = 0;
    HI_U8* pu8VirAddr = HI_NULL_PTR;

    Sample_FuncEnter();

    KEYPROVISION_CHECK_PARAM(0 == u32Size);
    KEYPROVISION_CHECK_PARAM(HI_NULL_PTR == pu32PhyAddr);
    KEYPROVISION_CHECK_PARAM(HI_NULL_PTR == ppu8VirAddr);

    u32PhyAddr = HI_MPI_MMZ_New(u32Size, 0, HI_NULL_PTR, "keyprovision");
    if (0 == u32PhyAddr)
    {
        KEYPROVISION_PrintFuncErr(HI_MPI_MMZ_New, HI_FAILURE);
        return HI_FAILURE;
    }

    pu8VirAddr = (HI_U8*)HI_MPI_MMZ_Map(u32PhyAddr, 0);
    if (HI_NULL_PTR == pu8VirAddr)
    {
        KEYPROVISION_PrintFuncErr(HI_MPI_MMZ_Map, HI_FAILURE);
        HI_MMZ_Delete(u32PhyAddr);
        return HI_FAILURE;
    }

    *pu32PhyAddr = u32PhyAddr;
    *ppu8VirAddr = pu8VirAddr;

    Sample_FuncExit();
    return HI_SUCCESS;
}
static HI_S32 MmzFree(HI_U32 u32PhyAddr)
{
    HI_S32 s32Ret = HI_FAILURE;

    Sample_FuncEnter();

    s32Ret = HI_MPI_MMZ_Unmap(u32PhyAddr);
    if (HI_SUCCESS != s32Ret)
    {
        KEYPROVISION_PrintFuncErr(HI_MPI_MMZ_Unmap, s32Ret);
        return s32Ret;
    }

    s32Ret = HI_MPI_MMZ_Delete(u32PhyAddr);
    if (HI_SUCCESS != s32Ret)
    {
        KEYPROVISION_PrintFuncErr(HI_MPI_MMZ_Delete, s32Ret);
        return s32Ret;
    }

    Sample_FuncExit();
    return HI_SUCCESS;
}

static HI_S32 s_CopyFromBufferToFile(HI_U8 *pu8Input, HI_U32 u32Length, HI_CHAR *pFileName)
{
    FILE *phFdEn = NULL;
    HI_S32 s32Ret = HI_SUCCESS;

    Sample_FuncEnter();

    KEYPROVISION_CHECK_PARAM(NULL == pFileName);
    KEYPROVISION_CHECK_PARAM(NULL == pu8Input);
    KEYPROVISION_CHECK_PARAM(0 == u32Length);

    phFdEn = fopen(pFileName, "w+");
    if( NULL == phFdEn )
    {
        KEYPROVISION_PrintFuncErr(fopen, -1);
        return HI_FAILURE;
    }

    s32Ret = fwrite((HI_VOID *)pu8Input, (size_t)1, (size_t)u32Length, phFdEn);
    if( u32Length != s32Ret)
    {
        KEYPROVISION_PrintFuncErr(fwrite, s32Ret);
        fclose(phFdEn);
        return HI_FAILURE;
    }
    fclose(phFdEn);

    Sample_FuncExit();
    return HI_SUCCESS;
}

static HI_S32 burn_hdcp_key_to_flash(HI_VOID *pBuffer, HI_U32 u32BufferLen)
{
    HI_S32 s32Ret = HI_FAILURE;

    Sample_FuncEnter();

    /** write hdcp key buffer into local file */
    s32Ret = s_CopyFromBufferToFile(pBuffer, u32BufferLen, "EncryptedKey_332bytes.bin");
    if(HI_SUCCESS != s32Ret)
    {
        KEYPROVISION_PrintFuncErr(CopyFromBufferToFile, s32Ret);
        return s32Ret;
    }

    Sample_FuncExit();
    return HI_SUCCESS;
}

static HI_S32 mailbox_send2smcu(HI_VOID *pMessage, HI_U32 u32MessageLen)
{
    HI_UNF_MAILBOX_BUFFER_S stBufferInfo;
    HI_HANDLE handle = HI_INVALID_HANDLE;
    HI_U32 au32MailboxOutput[4] = {0};
    HI_U32 outputlength = 4;
    HI_U32 u32StartTime, u32EndTime;

    HI_S32 s32Ret = HI_FAILURE;

    Sample_FuncEnter();

    s32Ret = HI_UNF_MAILBOX_Init();
    if(HI_SUCCESS != s32Ret)
    {
        KEYPROVISION_PrintFuncErr(HI_UNF_MAILBOX_Init, s32Ret);
        return s32Ret;
    }

    s32Ret = HI_UNF_MAILBOX_Open(&handle, MID_ACPU_COMMON);
    if (HI_SUCCESS != s32Ret)
    {
        KEYPROVISION_PrintFuncErr(HI_UNF_MAILBOX_Open, s32Ret);
        return s32Ret;
    }

    memset(&stBufferInfo, 0x00, sizeof(HI_UNF_MAILBOX_BUFFER_S));
    stBufferInfo.pMessage = pMessage;
    stBufferInfo.u32MessageLen = u32MessageLen;
    stBufferInfo.pOutBuffer = au32MailboxOutput;
    stBufferInfo.pu32OutBufferLen = &outputlength;
    printBuffer("mailbox input:", pMessage, u32MessageLen);

    HI_SYS_GetTimeStampMs(&u32StartTime);

    s32Ret = HI_UNF_MAILBOX_Send(handle, MID_SMCU_KEY_PROVISION, &stBufferInfo, 0, 0);
    if (HI_SUCCESS != s32Ret)
    {
        KEYPROVISION_PrintFuncErr(HI_UNF_MAILBOX_Send, s32Ret);
        return s32Ret;
    }

    HI_SYS_GetTimeStampMs(&u32EndTime);

    printf("=================================\n");
    printf("end:%u, start:%u, cost:%u\n", u32EndTime, u32StartTime, u32EndTime - u32StartTime);
    printf("=================================\n");

    printf("au32MailboxOutput[0]:%x receive length:%x\n", au32MailboxOutput[0], outputlength);

    if (SMCU_KEYPROVISION_OK != au32MailboxOutput[0])
    {
        return HI_FAILURE;
    }

    s32Ret = HI_UNF_MAILBOX_Close(handle);
    if (HI_SUCCESS != s32Ret)
    {
        KEYPROVISION_PrintFuncErr(HI_UNF_MAILBOX_Close, s32Ret);
		return s32Ret;
    }

    s32Ret = HI_UNF_MAILBOX_DeInit();
    if (HI_SUCCESS != s32Ret)
    {
        KEYPROVISION_PrintFuncErr(HI_UNF_MAILBOX_DeInit, s32Ret);
		return s32Ret;
    }

    Sample_FuncExit();
    return HI_SUCCESS;
}

static HI_S32 parse_rootkey(IMAGE_HEADER_S * pstHeader, HI_U8* pu8Data)
{
    HI_U8* pu8KeyArea = HI_NULL_PTR;
    HI_U8* pu8DataArea = HI_NULL_PTR;
    HI_U8* pu8HdcpArea = HI_NULL_PTR;

    HI_U8* pu8VirAddr = HI_NULL_PTR;
    HI_U32 u32PhyAddr = 0;
    HI_U32 u32MailboxInput[4] = {0};
    HI_U32 u32RSAKeyID = 0;

    HI_S32 s32Ret = HI_FAILURE;

    Sample_FuncEnter();

    pu8KeyArea = pu8Data + pstHeader->u32KeyAreaOffset;
    pu8DataArea = pu8Data + pstHeader->u32DataAreaOffset;

    printBuffer("pu8Data", pu8Data, 256);
    printBuffer("pu8KeyArea", pu8KeyArea, pstHeader->u32KeyAreaOffset);

    u32RSAKeyID = *((HI_U32*)(pu8KeyArea + 4));

    s32Ret = MmzMalloc(pstHeader->u32DataAreaLength, &u32PhyAddr, &pu8VirAddr);
    if(HI_SUCCESS != s32Ret)
    {
        KEYPROVISION_PrintFuncErr(MmzMalloc, s32Ret);
        return s32Ret;
    }

    memcpy(pu8VirAddr, pu8DataArea, pstHeader->u32DataAreaLength);

    printf("u32PhyAddr: 0x%x, *pu8VirAddr: 0x%x \n", u32PhyAddr, *pu8VirAddr);
    printBuffer("pu8VirAddr", pu8VirAddr, pstHeader->u32DataAreaLength);

    u32MailboxInput[0] = SMCU_KEYPROVISION_ROOTKEY_TYPE;
    u32MailboxInput[1] = u32RSAKeyID;
    u32MailboxInput[2] = u32PhyAddr;
    u32MailboxInput[3] = pstHeader->u32DataAreaLength;

    s32Ret = mailbox_send2smcu(u32MailboxInput, sizeof(u32MailboxInput));
    if (HI_SUCCESS != s32Ret)
    {
        KEYPROVISION_PrintFuncErr(mailbox_send2smcu, s32Ret);
        MmzFree(u32PhyAddr);
        return s32Ret;
    }

    s32Ret = MmzFree(u32PhyAddr);
    if (HI_SUCCESS != s32Ret)
    {
        KEYPROVISION_PrintFuncErr(MmzFree, s32Ret);
        return s32Ret;
    }

    if (HDCP_ROOTKEY_PROVISION_TYPE == pstHeader->u32PackageType)
    {
        pu8HdcpArea = pu8Data + pstHeader->u32HDCPKeyOffset;

        s32Ret = burn_hdcp_key_to_flash(pu8HdcpArea, pstHeader->u32HDCPKeyLength);
        if (HI_SUCCESS != s32Ret)
        {
            KEYPROVISION_PrintFuncErr(burn_hdcp_key_to_flash, s32Ret);
            return s32Ret;
        }
    }

    Sample_FuncExit();
    return HI_SUCCESS;
}

HI_S32 main(int argc, char *argv[])
{
    FILE *fp = NULL;
    HI_U8* pu8FileData = HI_NULL_PTR;
    IMAGE_HEADER_S stHeader;
    HI_U32 u32FileLen = 0;

    HI_S32 s32Ret = HI_FAILURE;

    Sample_FuncEnter();

    HI_SYS_Init();

    fp = fopen(argv[1], "rb");
    if (NULL == fp)
    {
        KEYPROVISION_PrintFuncErr(fopen, HI_FAILURE);
        return -1;
    }

    memset(&stHeader, 0, sizeof(stHeader));
    fread(&stHeader, 1, sizeof(stHeader), fp);

    printBuffer("stHeader", (HI_U8*)&stHeader, sizeof(stHeader));

    u32FileLen = stHeader.u32DataAreaOffset + stHeader.u32DataAreaLength + stHeader.u32HDCPKeyLength;
    printf("u32FileLen: 0x%x \n", u32FileLen);

    pu8FileData = malloc(u32FileLen);
    if(NULL == pu8FileData)
    {
        KEYPROVISION_PrintFuncErr(malloc, HI_FAILURE);
        return -1;
    }

    rewind(fp);
    fread(pu8FileData, 1, u32FileLen, fp);

    if (ROOTKEY_PROVISION_TYPE == stHeader.u32PackageType || HDCP_ROOTKEY_PROVISION_TYPE == stHeader.u32PackageType)
    {
        s32Ret = parse_rootkey(&stHeader, pu8FileData);
        if (HI_SUCCESS != s32Ret)
        {
            KEYPROVISION_PrintFuncErr(parse_rootkey, s32Ret);
            free(pu8FileData);
            fclose(fp);
            return s32Ret;
        }
    }
    else
    {
        printf("not supprot DRM keyprovision now \n");
    }

    free(pu8FileData);
    fclose(fp);

    HI_SYS_DeInit();

    Sample_FuncExit();
    return HI_SUCCESS;
}
