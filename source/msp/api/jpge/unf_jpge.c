/************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*************************************************************************************************
File Name         : unf_jpge.c
Version           : Initial Draft
Author            :
Created           : 2018/01/01
Description       : CNcomment:  CNend\n
Function List     :


History           :
Date                             Author                   Modification
2018/01/01                       sdk                      Created file
*************************************************************************************************/


/*********************************add include here***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/types.h>

#include "hi_debug.h"
#include "hi_jpge_api.h"
#include "drv_jpge_ioctl.h"
#include "hi_jpge_errcode.h"
#include "hi_gfx_sys.h"

#ifdef HI_SMMU_SUPPORT
#include "mpi_mmz.h"
#endif

/***************************** Macro Definition *************************************************/

#define JPGE_CHECK_FD() \
    do {                                         \
        if (g_s32JPGEFd < 0)                     \
        {                                        \
            return HI_ERR_JPGE_DEV_NOT_OPEN;     \
        }                                        \
    } while (0)


/*************************** Structure Definition ***********************************************/


/********************** Global Variable declaration *********************************************/

#if !defined(CHIP_TYPE_hi3716mv410) && !defined(CHIP_TYPE_hi3716mv430) && !defined(CHIP_TYPE_hi3798mv310)
static const char *g_pszJPGEDevName = "/dev/hi_jpge";

static HI_S32 g_s32JPGEFd = -1;

static HI_S32 g_s32JPGERef = 0;
#endif

/********************** API forward declarations     ********************************************/


/********************** API forward release          ********************************************/

#if !defined(CHIP_TYPE_hi3716mv410) && !defined(CHIP_TYPE_hi3716mv430) && !defined(CHIP_TYPE_hi3798mv310)

#ifdef HI_SMMU_SUPPORT
/***************************************************************************
* func          : JPGE_FreeMem
* description   : free the mem that has alloced
                  CNcomment: �ͷŷ�������ڴ� CNend\n
* retval        : HI_SUCCESS �ɹ�
* retval        : HI_FAILURE ʧ��
* others:       : NA
****************************************************************************/
static HI_VOID JPGE_FreeMem(HI_U32 u32PhyAddr)
{
    if (0 != u32PhyAddr)
    {
       HI_MPI_MMZ_Delete(u32PhyAddr);
    }

    return;
}


/***************************************************************************
* func          : JPGE_AllocMem
* description   : alloc the mem that need
                  CNcomment: ������Ҫ���ڴ� CNend\n
* retval        : HI_SUCCESS �ɹ�
* retval        : HI_FAILURE ʧ��
* others:       : NA
****************************************************************************/
static HI_U32 JPGE_AllocMem(HI_U32 u32Size, HI_U32 u32Align,HI_CHAR *pName)
{
    HI_U32 u32PhyAddr = 0;

    if (0 != u32Size)
    {
       u32PhyAddr = HI_MPI_MMZ_New(u32Size, u32Align, NULL, pName);
    }

    return u32PhyAddr;
}

/***************************************************************************
* func          : JPGE_Map
* description   : CNcomment: ӳ�䲻��cache�������ڴ� CNend\n
* retval        : HI_SUCCESS �ɹ�
* retval        : HI_FAILURE ʧ��
* others:       : NA
****************************************************************************/
static HI_VOID *JPGE_Map(HI_U32 u32PhyAddr)
{
    return HI_MPI_MMZ_Map(u32PhyAddr, HI_FALSE);
}

/***************************************************************************
* func          : JPGE_Unmap
* description   : un map phy ddr
                  CNcomment: ��ӳ�������ַ CNend\n
* retval        : HI_SUCCESS �ɹ�
* retval        : HI_FAILURE ʧ��
* others:       : NA
****************************************************************************/
static HI_VOID JPGE_Unmap(HI_U32 u32PhyAddr)
{
    if (0 != u32PhyAddr)
    {
        HI_MPI_MMZ_Unmap(u32PhyAddr);
    }
}
#endif
#endif

/***************************************************************************
* func          : HI_JPGE_Open
* description   : api open jpge dev call this function
                  CNcomment: ���豸�ļ� CNend\n
* retval        : NA
* others:       : NA
****************************************************************************/
HI_S32 HI_JPGE_Open(HI_VOID)
{
#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv430) || defined(CHIP_TYPE_hi3798mv310)
    return HI_ERR_JPGE_UNSUPPORT;
#else
    if (g_s32JPGEFd >= 0)
    {
        g_s32JPGERef++;
        return HI_SUCCESS;
    }

    g_s32JPGEFd = open(g_pszJPGEDevName, O_RDWR, S_IRUSR);
    if (g_s32JPGEFd < 0)
    {
        return HI_ERR_JPGE_DEV_OPEN_FAILED;
    }

    g_s32JPGERef++;

    return HI_SUCCESS;
#endif
}

/***************************************************************************
* func          : HI_JPGE_Close
* description   : close open jpge dev call this function
                  CNcomment: �ر�jpge�����豸 CNend\n
* retval        : NA
* others:       : NA
****************************************************************************/
HI_VOID HI_JPGE_Close(HI_VOID)
{
#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv430) || defined(CHIP_TYPE_hi3798mv310)
    return;
#else
    if (g_s32JPGEFd < 0)
    {
        return;
    }

    g_s32JPGERef--;

    if (g_s32JPGERef > 0)
    {
        return;
    }
    else
    {
        g_s32JPGERef = 0;
    }

    close(g_s32JPGEFd);
    g_s32JPGEFd = -1;

    return;
#endif
}


/***************************************************************************
* func         : HI_JPGE_Create
* description  : create jpge encode
                 CNcomment: ����jpeg�������� CNend\n
* param[out]   : *pEncHandle  CNcomment: ������������   CNend\n
* param[in]    : pEncCfg      CNcomment: ����ı�����Ϣ   CNend\n
* retval       : NA
* others:      : NA
****************************************************************************/
HI_S32 HI_JPGE_Create(HI_U32 *pEncHandle, const Jpge_EncCfg_S *pEncCfg )
{
#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv430) || defined(CHIP_TYPE_hi3798mv310)
    return HI_ERR_JPGE_UNSUPPORT;
#else
    HI_S32 s32Ret = HI_SUCCESS;
    JPGE_HANDLE EncHandle = 0;
    Jpge_EncCfg_S stEncCfg = {0};

    JPGE_CHECK_FD();

    if ((NULL == pEncHandle) || (NULL == pEncCfg))
    {
        return HI_ERR_JPGE_NULL_PTR;
    }

    s32Ret = ioctl(g_s32JPGEFd, JPGE_CREATEHANDLE_CMD, &EncHandle);
    if ((s32Ret < 0) || (EncHandle < 0))
    {
        return HI_FAILURE;
    }

    HI_GFX_Memcpy(&stEncCfg, pEncCfg,sizeof(Jpge_EncCfg_S));

    s32Ret = ioctl(g_s32JPGEFd, JPGE_CREATE_CMD, &stEncCfg);
    if (s32Ret < 0)
    {
        (HI_VOID)ioctl(g_s32JPGEFd, JPGE_DESTROY_CMD, &EncHandle);
        return HI_FAILURE;
    }

    *pEncHandle = (HI_U32)EncHandle;

    return s32Ret;
#endif
}

/***************************************************************************
* func         : HI_JPGE_Encode
* description  : begin to encode
                 CNcomment: ��ʼ���� CNend\n
* param[in]    : EncHandle  CNcomment: ���������       CNend\n
* param[in]    : pEncIn     CNcomment: ����ı�����Ϣ   CNend\n
* param[in]    : pEncOut    CNcomment: ����ı�����Ϣ   CNend\n
* retval       : NA
* others:      : NA
****************************************************************************/
HI_S32 HI_JPGE_Encode(HI_U32 EncHandle, const Jpge_EncIn_S *pEncIn, Jpge_EncOut_S *pEncOut)
{
#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv430) || defined(CHIP_TYPE_hi3798mv310)
    return HI_ERR_JPGE_UNSUPPORT;
#else

    HI_S32 s32Ret = HI_SUCCESS;
    Jpge_EncInfo_S stEncInfo = {0};
#ifdef HI_SMMU_SUPPORT
    HI_U32 u32OutPhyBuf = 0;
    HI_U8* pu8OutVirBuf = NULL;
    HI_U32 u32TmpPhyBuf = 0;
    HI_U8* pu8TmpVirBuf = NULL;
#endif

    JPGE_CHECK_FD();

    if ((NULL == pEncIn) || (NULL == pEncOut))
    {
        return HI_ERR_JPGE_NULL_PTR;
    }

#ifdef HI_SMMU_SUPPORT
    u32TmpPhyBuf = pEncIn->BusOutBuf;
    if (0 == u32TmpPhyBuf)
    {
       return HI_ERR_JPGE_NULL_PTR;
    }

    pu8TmpVirBuf = pEncIn->pOutBuf;
    if (NULL == pu8TmpVirBuf)
    {
       return HI_ERR_JPGE_NULL_PTR;
    }
#endif

    stEncInfo.EncHandle = (JPGE_HANDLE)EncHandle;

    HI_GFX_Memcpy(&stEncInfo.EncIn, pEncIn, sizeof(Jpge_EncIn_S));

#ifdef HI_SMMU_SUPPORT
    u32OutPhyBuf = JPGE_AllocMem(pEncIn->OutBufSize,64,"JPGE-OUT-BUF");
    if (0 == u32OutPhyBuf)
    {
        return HI_FAILURE;
    }

    pu8OutVirBuf = (HI_U8*)JPGE_Map(u32OutPhyBuf);
    if (NULL == pu8OutVirBuf)
    {
        JPGE_FreeMem(u32OutPhyBuf);
        return HI_FAILURE;
    }
    stEncInfo.EncIn.BusOutBuf = u32OutPhyBuf;
    stEncInfo.EncIn.pOutBuf   = pu8OutVirBuf;
#endif

    s32Ret = ioctl(g_s32JPGEFd, JPGE_ENCODE_CMD, &stEncInfo);
    HI_GFX_Memcpy(pEncOut,&stEncInfo.EncOut,sizeof(Jpge_EncOut_S));

#ifdef HI_SMMU_SUPPORT
    if ((NULL != pEncOut->pStream) && (0 != pEncOut->StrmSize))
    {
       HI_GFX_Memcpy(pu8TmpVirBuf,pEncOut->pStream,pEncOut->StrmSize);
    }

    pEncOut->BusStream = u32TmpPhyBuf;
    pEncOut->pStream   = pu8TmpVirBuf;

    JPGE_Unmap(u32OutPhyBuf);
    JPGE_FreeMem(u32OutPhyBuf);
#endif

    return s32Ret;
#endif
}

HI_S32 HI_JPGE_Destroy(HI_U32 EncHandle)
{
#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv430) || defined(CHIP_TYPE_hi3798mv310)
    return HI_ERR_JPGE_UNSUPPORT;
#else
    JPGE_CHECK_FD();
    return ioctl(g_s32JPGEFd, JPGE_DESTROY_CMD, &EncHandle);
#endif
}
