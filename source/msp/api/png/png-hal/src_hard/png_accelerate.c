/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name	   : png_accelerate.c
Version		   : Initial Draft
Author		   : sdk
Created		   : 2018/01/01
Description    :
Function List  :

History        :
Date                             Author                     Modification
2018/01/01		                  sdk                        Created file
************************************************************************************************/
#ifdef HIPNG_ACCELERATE

/*********************************add include here***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>

#ifdef CONFIG_PNG_INTERNAL
#define PNG_INTERNAL
#else
#include "pngpriv.h"
#endif

#include "hipng_accelerate.h"
#include "hi_gfx_sys.h"

/***************************** Macro Definition *************************************************/
#define PNG_CHUNK_HEAD_LEN            8
#define PNG_CHUNK_TAIL_LEN            4
#define PNG_INFLEXION_SIZE            (40 * 40)
#define HIPNG_MAX_WIDTH               4096
#define HIPNG_MAX_HEIGHT              4096
#define HIPNG_MIN_HEIGHT              1
#define HIPNG_MAX_MEM                 (100 * 1024 * 1024)

#define HIPNG_IS_TRANSFORM_FMT(transformations) \
    (   (transformations & HIPNG_ARGB1555) \
     || (transformations & HIPNG_ARGB4444) \
     || (transformations & HIPNG_RGB565)   \
     || (transformations & HIPNG_RGB555)   \
     || (transformations & HIPNG_RGB444))

#define HIPNG_STATE_PUSHSTREAM_FAILED         0x1
#define HIPNG_STATE_DECODE_FAILED             0x2
#define HIPNG_STATE_SWITCH_COMPLETE           0x3
#define HIPNG_PUSHSTREAM_FAIL_START	          0x1   /* ��ʼ��������ʱʧ��          */
#define HIPNG_PUSHSTREAM_FAIL_PROCESS         0x2   /* ��������һ����ʧ��          */
#define HIPNG_DECODE_FAIL_TRANSFORM           0x3   /* ����ת��ʧ��                */
#define HIPNG_DECODE_FAIL_DECODE              0x4   /* ����ʧ��                    */
#define HIPNG_PUSHSTREAM_FAIL_IDATHEAD        0x5   /* ���׸�IDAT HEAD��������ʧ�� */
#define HIPNG_PUSHSTREAM_FAIL_CRCNODATA       0x6   /* ��ȡCRCʱ���ݲ���           */
#define HIPNG_PUSHSTREAM_FAIL_CRCNOBUF        0x7   /* ��ȡCRCʱbuf����            */

/*************************** Enum Definition ****************************************************/


/*************************** Structure Definition ***********************************************/


/********************** Global Variable declaration *********************************************/

/******************************* API declaration ************************************************/
HI_VOID hipng_push_switch_start(png_structp png_ptr);

HI_S32 hipng_set_transform(png_structp png_ptr, HI_PNG_TRANSFORM_S *pstTransform);

HI_U8 hipng_select_decmode(png_structp png_ptr, png_bytepp image, png_uint_32 num_rows);

/*****************************************************************
* func    : create the struct of hardWare dec
* in      : user_png_ver,error_ptr,png_error_ptr,warn_fn Consistent with libpng
* out     : stuct PT
* ret     : HI_SUCCESS
            HI_FAILURE
* others  :
*****************************************************************/
hipng_struct_hwctl_s *hipng_create_read_struct_hw(png_const_charp user_png_ver, png_voidp error_ptr,png_error_ptr error_fn, png_error_ptr warn_fn)
{
    HI_PNG_HANDLE s32Handle = -1;
    HI_S32 s32Ret = HI_SUCCESS;
    hipng_struct_hwctl_s *pstPngStruct = NULL;
    HI_S32 s32MemFd = -1;

    HI_UNUSED(user_png_ver);
    HI_UNUSED(error_ptr);
    HI_UNUSED(error_fn);
    HI_UNUSED(warn_fn);

#ifdef CONFIG_GFX_MEM_ION
    s32MemFd = gfx_mem_open();
    if (s32MemFd < 0)
    {
        return NULL;
    }
#endif

    s32Ret = HI_PNG_Open();
    if (s32Ret < 0)
    {
#ifdef CONFIG_GFX_MEM_ION
        gfx_mem_close(s32MemFd);
#endif
        return NULL;
    }

    s32Ret = HI_PNG_CreateDecoder(&s32Handle);
    if (s32Ret < 0)
    {
        HI_PNG_Close();
#ifdef CONFIG_GFX_MEM_ION
        gfx_mem_close(s32MemFd);
#endif
        return NULL;
    }

    pstPngStruct = (hipng_struct_hwctl_s *)malloc(sizeof(hipng_struct_hwctl_s));
    if (NULL == pstPngStruct)
    {
        HI_PNG_DestroyDecoder(s32Handle);
        HI_PNG_Close();
#ifdef CONFIG_GFX_MEM_ION
        gfx_mem_close(s32MemFd);
#endif
        return NULL;
    }

    HI_GFX_Memset(pstPngStruct, 0, sizeof(hipng_struct_hwctl_s));

    pstPngStruct->u8DecMode        = HIPNG_NO_DEC;
    pstPngStruct->u8SupportDecMode = (HIPNG_SW_DEC | HIPNG_HW_DEC | HIPNG_HWCOPY_DEC);
    pstPngStruct->u8UserDecMode    = (HIPNG_SW_DEC | HIPNG_HW_DEC | HIPNG_HWCOPY_DEC);
    pstPngStruct->s32Handle        = s32Handle;
    pstPngStruct->u32InflexionSize = PNG_INFLEXION_SIZE;
    pstPngStruct->bSyncDec         = HI_TRUE;
    pstPngStruct->s32MmzFd         = s32MemFd;
    pstPngStruct->u8ReadHeadCount  = PNG_CHUNK_HEAD_LEN;

    return pstPngStruct;
}

/*****************************************************************
* func    : destroy the struct of hardWare dec
* in      : pstHwctlStruct the struct of hardWare dec
* out     : none
* ret     : none
* others  :
*****************************************************************/
HI_VOID hipng_destroy_read_struct_hw(hipng_struct_hwctl_s *pstHwctlStruct)
{
#ifdef CONFIG_GFX_MMU_SUPPORT
    HI_BOOL bMmu = HI_TRUE;
#else
    HI_BOOL bMmu = HI_FALSE;
#endif
    if (NULL == pstHwctlStruct)
    {
        return;
    }

    HI_PNG_DestroyDecoder(pstHwctlStruct->s32Handle);

    if (  !(pstHwctlStruct->u8DecMode & HIPNG_HW_DEC)
        &&(pstHwctlStruct->u8DecMode & HIPNG_HWCOPY_DEC)
        &&(pstHwctlStruct->u32TmpPhyaddr))
    {
#ifdef CONFIG_GFX_MEM_MMZ
        HI_GFX_Unmap(pstHwctlStruct->u32TmpPhyaddr, HI_TRUE);
        HI_GFX_FreeMem(pstHwctlStruct->u32TmpPhyaddr, HI_TRUE);
#else
        HI_GFX_Unmap(pstHwctlStruct->s32MmzFd, pstHwctlStruct->u32TmpPhyaddr, pstHwctlStruct->pTmpMemData);
        HI_GFX_FreeMem(pstHwctlStruct->s32MmzFd, pstHwctlStruct->u32TmpPhyaddr, pstHwctlStruct->pTmpMemData, HI_TRUE);
#endif
        pstHwctlStruct->u32TmpPhyaddr = 0;
    }

    if (pstHwctlStruct->pallateaddr != 0)
    {
#ifdef CONFIG_GFX_MEM_MMZ
        HI_GFX_FreeMem(pstHwctlStruct->pallateaddr, bMmu);
#else
        HI_GFX_FreeMem(pstHwctlStruct->s32MmzFd, pstHwctlStruct->pallateaddr, pstHwctlStruct->pPallateMemData, bMmu);
#endif
        pstHwctlStruct->pallateaddr = 0;
    }

    HI_PNG_Close();

    if (pstHwctlStruct->s32MmzFd >= 0)
    {
#ifndef CONFIG_GFX_MEM_MMZ
        gfx_mem_close(pstHwctlStruct->s32MmzFd);
#endif
    }

    free(pstHwctlStruct);

    return;
}

#if PNG_LIBPNG_VER > 10246
HI_S32 hipng_read_chunk_header(png_structrp png_ptr)
#else
HI_S32 hipng_read_chunk_header(png_structp png_ptr)
#endif
{
    png_byte buf[8] = {0};
    png_uint_32 length = 0;

    if (NULL == png_ptr)
    {
       return HI_FAILURE;
    }

#ifdef PNG_IO_STATE_SUPPORTED
    png_ptr->io_state = PNG_IO_READING | PNG_IO_CHUNK_HDR;
#endif

    png_read_data(png_ptr, buf, 8);

    length = png_get_uint_31(png_ptr, buf);

#if PNG_LIBPNG_VER > 10246
    png_ptr->chunk_name = PNG_CHUNK_FROM_STRING(buf + 4);
#else
    png_memcpy(png_ptr->chunk_name, buf + 4, 4);
#endif

    png_reset_crc(png_ptr);

    png_calculate_crc(png_ptr, buf + 4, 4);

#ifdef PNG_IO_STATE_SUPPORTED
    png_ptr->io_state = PNG_IO_READING | PNG_IO_CHUNK_DATA;
#endif

    return length;
}

/* fill to stream */
HI_S32 hipng_read_stream(png_structp png_ptr)
{
    HI_PNG_BUF_S stBuf = {0, 0, 0};
    HI_S32 s32Ret = HI_SUCCESS;
    hipng_struct_hwctl_s *pstHwStruct = NULL;
    HI_UCHAR ucChunkHead[PNG_CHUNK_HEAD_LEN] = {0, 0, 0, 0, 'I', 'D', 'A', 'T'};
    HI_UCHAR *pBuf = NULL;          /* stream buf head point*/
    HI_UCHAR *pWrite = NULL;        /* stream buf write point*/
    HI_BOOL bNewChunk = HI_TRUE;    /* head data*/
    HI_U8 u8ReadHeadCount = 0;      /* length of has write to data trunk */
    HI_U32 u32IdatSize = 0;
    HI_U32 u32Len = 0;
    HI_PNG_BUF_S stTempBuf;
    HI_BOOL bEnd = HI_FALSE;

    if (NULL == png_ptr)
    {
       return HI_FAILURE;
    }

    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (NULL == pstHwStruct)
    {
       return HI_FAILURE;
    }

    if ((0 == png_ptr->idat_size) || (png_ptr->idat_size > (UINT_MAX - PNG_CHUNK_HEAD_LEN)))
    {
       return HI_FAILURE;
    }

    u32IdatSize = png_ptr->idat_size + PNG_CHUNK_HEAD_LEN;

    if (u32IdatSize > (UINT_MAX - PNG_CHUNK_TAIL_LEN))
    {
       return HI_FAILURE;
    }
    u32IdatSize = u32IdatSize + PNG_CHUNK_TAIL_LEN;

    memset(&stTempBuf, 0, sizeof(HI_PNG_BUF_S));

    ucChunkHead[0] = (png_ptr->idat_size >> 24) & 0xff;
    ucChunkHead[1] = (png_ptr->idat_size >> 16) & 0xff;
    ucChunkHead[2] = (png_ptr->idat_size >> 8) & 0xff;
    ucChunkHead[3] = png_ptr->idat_size & 0xff;

    while (!bEnd)
    {
        if ((0 == stBuf.u32Size) && (0 == stTempBuf.u32Size))
        {
            stBuf.u32Size = u32IdatSize;
            s32Ret = HI_PNG_AllocBuf(pstHwStruct->s32Handle, &stBuf);
            if (s32Ret < 0)
            {
                return HI_FAILURE;
            }
            pBuf = (HI_UCHAR *)stBuf.pVir;
            pWrite = pBuf;
        }
        else if (0 == stBuf.u32Size)
        {
            HI_GFX_Memcpy(&stBuf, &stTempBuf, sizeof(HI_PNG_BUF_S));
            HI_GFX_Memset(&stTempBuf, 0, sizeof(HI_PNG_BUF_S));
            pBuf = (HI_UCHAR *)stBuf.pVir;
            pWrite = pBuf;
        }
        if (NULL == pWrite)
        {
            return HI_FAILURE;
        }

        /* fill IDAT head data*/
        if (bNewChunk)
        {
            u32Len = (HI_U32)(PNG_CHUNK_HEAD_LEN - u8ReadHeadCount) < stBuf.u32Size ? (HI_U32)(PNG_CHUNK_HEAD_LEN - u8ReadHeadCount) : stBuf.u32Size;
            HI_GFX_Memcpy(pWrite, &ucChunkHead[u8ReadHeadCount], u32Len);
            pWrite += u32Len;
            u32IdatSize -= u32Len;
            stBuf.u32Size -= u32Len;
            u8ReadHeadCount += u32Len;
            if (u8ReadHeadCount == PNG_CHUNK_HEAD_LEN)
            {
                bNewChunk = HI_FALSE;
            }
        }

        if (u32IdatSize)
        {
            u32Len = (u32IdatSize < stBuf.u32Size) ? u32IdatSize : stBuf.u32Size;
            png_read_data(png_ptr, pWrite, u32Len);
            u32IdatSize -= u32Len;
            stBuf.u32Size -= u32Len;
            pWrite += u32Len;
        }
        else if ((stBuf.u32Size < PNG_CHUNK_HEAD_LEN) && (HI_NULL == stTempBuf.pVir))
        {
            s32Ret = HI_PNG_AllocBuf(pstHwStruct->s32Handle, &stTempBuf);
            if (s32Ret < 0)
            {
                s32Ret = HI_PNG_SetStreamLen(pstHwStruct->s32Handle, stBuf.u32PhyAddr, pWrite - pBuf);
                return HI_FAILURE;
            }
        }
        /* read next chunk */
        else
        {
#if PNG_LIBPNG_VER < 10500
            PNG_IDAT;
#endif
            png_ptr->idat_size = hipng_read_chunk_header(png_ptr);
#if PNG_LIBPNG_VER >= 10500
            if (png_IDAT == png_ptr->chunk_name)
#else
			if (png_memcmp(png_ptr->chunk_name, png_IDAT, 4) == 0)
#endif
            {
                bNewChunk = HI_TRUE;
                u8ReadHeadCount = 0;
                u32IdatSize = png_ptr->idat_size + PNG_CHUNK_HEAD_LEN + PNG_CHUNK_TAIL_LEN;

                ucChunkHead[0] = (png_ptr->idat_size >> 24) & 0xff;
                ucChunkHead[1] = (png_ptr->idat_size >> 16) & 0xff;
                ucChunkHead[2] = (png_ptr->idat_size >> 8) & 0xff;
                ucChunkHead[3] = png_ptr->idat_size & 0xff;
            }
            else
            {
                bEnd = HI_TRUE;
                s32Ret = HI_PNG_SetStreamLen(pstHwStruct->s32Handle, stBuf.u32PhyAddr, pWrite - pBuf);

                pstHwStruct->idat_size = png_ptr->idat_size;
                pstHwStruct->crc = png_ptr->crc;

                #if (PNG_LIBPNG_VER >= 10500)
                pstHwStruct->chunk_name = png_ptr->chunk_name;
                #else
				HI_GFX_Memcpy(pstHwStruct->chunk_name, png_ptr->chunk_name, 5);
                #endif
            }
        }

        /* set stream length*/
        if (0 == stBuf.u32Size)
        {
            s32Ret = HI_PNG_SetStreamLen(pstHwStruct->s32Handle, stBuf.u32PhyAddr, pWrite - pBuf);
            HI_GFX_Memset(&stBuf, 0, sizeof(HI_PNG_BUF_S));
        }
    }
    return HI_SUCCESS;
}

#ifdef HIPNG_PUSH_DECODE
static HI_S32 hipng_push_check(png_structp png_ptr)
{
    HI_U8 u8DecMode = 0;
    hipng_struct_hwctl_s *pstHwStruct = NULL;
    if (NULL == png_ptr)
    {
       return HI_FAILURE;
    }

    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (NULL == pstHwStruct)
    {
        HIPNG_TRACE("Null decode handle!\n");
        return HI_FAILURE;
    }

    if (pstHwStruct->u8PushState)
    {
        HIPNG_TRACE("state:%d!\n", pstHwStruct->u8PushState);
        return HI_FAILURE;
    }

    u8DecMode = hipng_select_decmode(png_ptr, NULL, 0);

    if (!(u8DecMode & HIPNG_HW_DEC) && !(u8DecMode & HIPNG_HWCOPY_DEC))
    {
        HIPNG_TRACE("u8DecMode:%d\n", u8DecMode);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 hipng_push_allocstream(png_structp png_ptr)
{
    hipng_struct_hwctl_s *pstHwStruct = NULL;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UCHAR ucChunkHead[PNG_CHUNK_HEAD_LEN] = {0, 0, 0, 0, 'I', 'D', 'A', 'T'};

    if (NULL == png_ptr)
    {
       return HI_FAILURE;
    }

    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (NULL == pstHwStruct)
    {
       return HI_FAILURE;
    }

    if (pstHwStruct->stBuf.u32Size > 0)
    {
        return HI_SUCCESS;
    }

    pstHwStruct->stBuf.u32Size = pstHwStruct->idat_size;
    if (pstHwStruct->u8ExceptionMode == HIPNG_PUSHSTREAM_FAIL_START)
    {
        s32Ret = HI_FAILURE;
    }
    else if ((pstHwStruct->u8ExceptionMode == HIPNG_PUSHSTREAM_FAIL_IDATHEAD) && (pstHwStruct->u8IdatCount > 0))
    {
        s32Ret = HI_FAILURE;
    }
    else
    {
        s32Ret = HI_PNG_AllocBuf(pstHwStruct->s32Handle, &pstHwStruct->stBuf);
    }

    if (s32Ret < 0)
    {
        /*todo:�����������л��������*/
        if (pstHwStruct->bHasStream && pstHwStruct->u8ReadHeadCount)
        {
            HI_GFX_Memcpy(pstHwStruct->chunkHead, ucChunkHead, 8);
            pstHwStruct->bChunkheadValid = HI_TRUE;
        }
        HI_GFX_Memset(&pstHwStruct->stBuf, 0, sizeof(HI_PNG_BUF_S));
        pstHwStruct->u8PushState = HIPNG_STATE_PUSHSTREAM_FAILED;
        hipng_push_switch_start(png_ptr);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_VOID hipng_push_readidat(png_structp png_ptr)
{
    hipng_struct_hwctl_s *pstHwStruct = NULL;
    HI_U32 u32Len = 0;

    if (NULL == png_ptr)
    {
       return;
    }

    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (NULL == pstHwStruct)
    {
       return;
    }

    /*��ȡidat����*/
    while (png_ptr->idat_size > 0 && png_ptr->save_buffer_size > 0)
    {
        u32Len = (png_ptr->idat_size < png_ptr->save_buffer_size) ? png_ptr->idat_size : png_ptr->save_buffer_size;
        u32Len = (u32Len < pstHwStruct->stBuf.u32Size) ? u32Len : pstHwStruct->stBuf.u32Size;
        if (u32Len == 0)
        {
            break;
        }

        HI_GFX_Memcpy(pstHwStruct->stBuf.pVir + pstHwStruct->u32StreamLen, png_ptr->save_buffer_ptr, u32Len);

        pstHwStruct->u32StreamLen += u32Len;
        pstHwStruct->idat_size -= u32Len;
        pstHwStruct->stBuf.u32Size -= u32Len;
        png_ptr->idat_size -= u32Len;
        png_ptr->buffer_size -= u32Len;
        png_ptr->save_buffer_size -= u32Len;
        png_ptr->save_buffer_ptr += u32Len;
    }

    while (png_ptr->idat_size > 0 && png_ptr->current_buffer_size > 0)
    {
        u32Len = (png_ptr->idat_size < png_ptr->current_buffer_size) ? png_ptr->idat_size : png_ptr->current_buffer_size;
        u32Len = (u32Len < pstHwStruct->stBuf.u32Size) ? u32Len : pstHwStruct->stBuf.u32Size;
        if (u32Len == 0)
        {
            break;
        }

        HI_GFX_Memcpy(pstHwStruct->stBuf.pVir + pstHwStruct->u32StreamLen, png_ptr->current_buffer_ptr, u32Len);

        pstHwStruct->u32StreamLen += u32Len;
        pstHwStruct->idat_size -= u32Len;
        pstHwStruct->stBuf.u32Size -= u32Len;
        png_ptr->idat_size -= u32Len;
        png_ptr->buffer_size -= u32Len;
        png_ptr->current_buffer_size -= u32Len;
        png_ptr->current_buffer_ptr += u32Len;
    }

    return;
}

static HI_S32 hipng_push_readcrc(png_structp png_ptr, HI_BOOL *bEnd)
{
    hipng_struct_hwctl_s *pstHwStruct = NULL;
    if ((NULL == png_ptr) || (NULL == bEnd))
    {
       return HI_FAILURE;
    }

    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (NULL == pstHwStruct)
    {
       return HI_FAILURE;
    }

    if (PNG_CHUNK_TAIL_LEN == pstHwStruct->idat_size)
    {
        if (png_ptr->idat_size != 0)
        {
            HIPNG_TRACE("Unknown error!\n");
        }

        if (HIPNG_PUSHSTREAM_FAIL_CRCNODATA == pstHwStruct->u8ExceptionMode)
        {
            png_push_save_buffer(png_ptr);
            pstHwStruct->u8ExceptionMode = 0;
            return HI_SUCCESS;
        }

        if (png_ptr->buffer_size < PNG_CHUNK_TAIL_LEN)
        {
            png_push_save_buffer(png_ptr);
            return HI_SUCCESS;
        }

        if (HIPNG_PUSHSTREAM_FAIL_CRCNOBUF == pstHwStruct->u8ExceptionMode)
        {
            pstHwStruct->u8ExceptionMode = 0;
            pstHwStruct->stBuf.u32Size = 0;
        }

        if (pstHwStruct->stBuf.u32Size < PNG_CHUNK_TAIL_LEN)
        {
            pstHwStruct->stBuf.u32Size = 0;
        }

        png_ptr->idat_size = PNG_CHUNK_TAIL_LEN;
        pstHwStruct->bCrc  = HI_TRUE;
    }
    else if (pstHwStruct->idat_size == 0)
    {
        if (png_ptr->idat_size != 0)
        {
            HIPNG_TRACE("Unknown error!\n");
        }

        png_ptr->mode &= ~PNG_HAVE_CHUNK_HEADER;
        png_ptr->mode |= PNG_AFTER_IDAT;

        /*��u8ReadHeadCount,bCrc����Ϊ��ʼ ֵ�Զ�ȡ��һ��idat*/
        pstHwStruct->u8ReadHeadCount = PNG_CHUNK_HEAD_LEN;
        pstHwStruct->bCrc = HI_FALSE;
        pstHwStruct->u8IdatCount++;
        *bEnd = HI_TRUE;
    }

    return HI_FAILURE;
}

/*��������*/
HI_S32 hipng_push_stream(png_structp png_ptr)
{
    HI_BOOL bEnd = HI_FALSE;
    hipng_struct_hwctl_s *pstHwStruct = NULL;
    HI_UCHAR ucChunkHead[PNG_CHUNK_HEAD_LEN] = {0, 0, 0, 0, 'I', 'D', 'A', 'T'};
    HI_U32 u32Len = 0;
    HI_S32 s32Ret = HI_SUCCESS;

    if (NULL == png_ptr)
    {
       return HI_FAILURE;
    }

    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (NULL == pstHwStruct)
    {
       return HI_FAILURE;
    }

    s32Ret = hipng_push_check(png_ptr);
    if (s32Ret != HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    pstHwStruct->mode = png_ptr->mode;
    while (!bEnd)
    {
        if (pstHwStruct->u8ReadHeadCount == PNG_CHUNK_HEAD_LEN)
        {
            ucChunkHead[0] = (png_ptr->idat_size >> 24) & 0xff;
            ucChunkHead[1] = (png_ptr->idat_size >> 16) & 0xff;
            ucChunkHead[2] = (png_ptr->idat_size >> 8) & 0xff;
            ucChunkHead[3] = png_ptr->idat_size & 0xff;
            pstHwStruct->idat_size = png_ptr->idat_size + PNG_CHUNK_HEAD_LEN + PNG_CHUNK_TAIL_LEN;
        }

        s32Ret = hipng_push_allocstream(png_ptr);
        if (s32Ret != HI_SUCCESS)
        {
            return HI_FAILURE;
        }

        if (pstHwStruct->u8ReadHeadCount > 0)
        {
            if ((HI_U32)(pstHwStruct->u8ReadHeadCount) > pstHwStruct->stBuf.u32Size)
            {
                pstHwStruct->stBuf.u32Size = 0;
            }
            else
            {
                u32Len = (HI_U32)(pstHwStruct->u8ReadHeadCount);
                HI_GFX_Memcpy(pstHwStruct->stBuf.pVir + pstHwStruct->u32StreamLen, &ucChunkHead[PNG_CHUNK_HEAD_LEN - pstHwStruct->u8ReadHeadCount], u32Len);
                pstHwStruct->u32StreamLen += u32Len;
                pstHwStruct->idat_size -= u32Len;
                pstHwStruct->stBuf.u32Size -= u32Len;
                pstHwStruct->u8ReadHeadCount -= u32Len;
            }
        }

        hipng_push_readidat(png_ptr);

        /*idat���ݶ�ȡ�꣬��ȡCRC����*/
        s32Ret = hipng_push_readcrc(png_ptr, &bEnd);
        if (s32Ret == HI_SUCCESS)
        {
            return s32Ret;
        }

        /*����buf�����������������ˣ��͸��ײ㴦��*/
        if ((0 == pstHwStruct->stBuf.u32Size) || bEnd)
        {
            s32Ret = HI_PNG_SetStreamLen(pstHwStruct->s32Handle, pstHwStruct->stBuf.u32PhyAddr, pstHwStruct->u32StreamLen);
            if (pstHwStruct->u8ExceptionMode == HIPNG_PUSHSTREAM_FAIL_PROCESS)
            {
                s32Ret = HI_FAILURE;
            }
            if (s32Ret < 0)
            {
                /*todo:�����������л��������*/
                pstHwStruct->u8PushState = HIPNG_STATE_PUSHSTREAM_FAILED;
                hipng_push_switch_start(png_ptr);
                return HI_FAILURE;
            }
            if (!pstHwStruct->bHasStream)
            {
                pstHwStruct->bHasStream = HI_TRUE;
            }

            HI_GFX_Memset(&pstHwStruct->stBuf, 0, sizeof(HI_PNG_BUF_S));
            pstHwStruct->u32StreamLen = 0;
        }

        if ((0 == png_ptr->save_buffer_size) && (0 == png_ptr->current_buffer_size))
        {
            bEnd = HI_TRUE;
        }
    }

    return HI_SUCCESS;
}

HI_S32 hipng_push_decode(png_structp png_ptr)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_PNG_DECINFO_S stInfo = {0};
    HI_U32 i = 0;
    hipng_struct_hwctl_s *pstHwStruct = NULL;
    HI_CHAR *row = null;
    HI_U8 u8DecMode = 0;
    png_bytep row_buf;

    if (NULL == png_ptr)
    {
       return HI_FAILURE;
    }

    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (NULL == pstHwStruct)
    {
       return HI_FAILURE;
    }

    if (pstHwStruct->u8PushState)
    {
        HIPNG_TRACE("state:%d!\n", pstHwStruct->u8PushState);
        return HI_SUCCESS;
    }

    /*ѡ�����ģʽ*/
    u8DecMode = hipng_select_decmode(png_ptr, NULL, 0);

    if (!(u8DecMode & HIPNG_HW_DEC) && !(u8DecMode & HIPNG_HWCOPY_DEC))
    {
        /*ֱ�ӷ��ظ��������*/
        HIPNG_TRACE("u8DecMode:%d\n", u8DecMode);
        return HI_SUCCESS;
    }

    s32Ret = hipng_set_transform(png_ptr, &stInfo.stTransform);
    if (pstHwStruct->u8ExceptionMode == HIPNG_DECODE_FAIL_TRANSFORM)
    {
        s32Ret = HI_FAILURE;
    }
    if (s32Ret < 0)
    {
        /*todo:�����������л��������*/
        pstHwStruct->u8PushState = HIPNG_STATE_DECODE_FAILED;
        hipng_push_switch_start(png_ptr);
        HIPNG_TRACE("Set transform failed!\n");
        return HI_FAILURE;
    }

    stInfo.bSync = pstHwStruct->bSyncDec;
    stInfo.stPngInfo.eColorFmt = png_ptr->color_type;
    stInfo.stPngInfo.u32Width = png_ptr->width;
    stInfo.stPngInfo.u32Height = png_ptr->height;
    stInfo.stPngInfo.u8BitDepth = png_ptr->bit_depth;
    stInfo.u32Phyaddr = pstHwStruct->u32TmpPhyaddr;
    stInfo.u32Stride = (pstHwStruct->u32TmpStride + 0xf) & 0xfffffff0;

    if (pstHwStruct->u8ExceptionMode == HIPNG_DECODE_FAIL_DECODE)
    {
        s32Ret = HI_FAILURE;
    }
    else
    {
        s32Ret = HI_PNG_Decode(pstHwStruct->s32Handle, &stInfo);
    }
    if (s32Ret < 0)
    {
        /*todo:�����������л��������*/
        pstHwStruct->u8PushState = HIPNG_STATE_DECODE_FAILED;
        hipng_push_switch_start(png_ptr);
        return HI_FAILURE;
    }

    png_ptr->transformed_pixel_depth = pstHwStruct->pixel_depth;

    row_buf = png_ptr->row_buf;

    /*�����лص�������*/
    if (png_ptr->row_fn != NULL)
    {
        row = (HI_CHAR *)pstHwStruct->pu8TmpImage;
        for (i = 0; i < png_ptr->height; i++)
        {
            /*attention:*/
            png_ptr->row_buf = (png_bytep)row - 1;
            (*(png_ptr->row_fn))(png_ptr, (png_bytep)row, i, (int)png_ptr->pass);
            row += ((pstHwStruct->u32TmpStride + 0xf) & 0xfffffff0);
        }
    }
    png_ptr->row_buf = row_buf;

    /*���������ʶ*/
    png_ptr->flags |= PNG_FLAG_ZSTREAM_ENDED;

    return HI_SUCCESS;
}

#define PNG_READ_CHUNK_MODE 1
#define PNG_READ_IDAT_MODE  2
extern HI_VOID HI_PNG_GetStream(HI_PNG_HANDLE s32Handle, HI_VOID **ppStream, HI_U32 *pu32Len);
HI_VOID hipng_push_switch_start(png_structp png_ptr)
{
    hipng_struct_hwctl_s *pstHwStruct = NULL;
    HI_VOID *pStream = NULL;
    HI_U32 u32Len = 0;
    png_byte chunk_length[4];
    png_byte chunk_tag[4];
    png_uint_32 mode = 0;

    if (NULL == png_ptr)
    {
       return;
    }

    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (NULL == pstHwStruct)
    {
       return;
    }

    mode = pstHwStruct->mode;

    pstHwStruct->save_buffer         = png_ptr->save_buffer;
    pstHwStruct->save_buffer_ptr     = png_ptr->save_buffer_ptr;
    pstHwStruct->save_buffer_size    = png_ptr->save_buffer_size;
    pstHwStruct->save_buffer_max     = png_ptr->save_buffer_max;
    pstHwStruct->current_buffer      = png_ptr->current_buffer;
    pstHwStruct->current_buffer_ptr  = png_ptr->current_buffer_ptr;
    pstHwStruct->current_buffer_size = png_ptr->current_buffer_size;
    pstHwStruct->buffer_size         = png_ptr->buffer_size;
    pstHwStruct->push_length         = png_ptr->push_length;
    pstHwStruct->crc                 = png_ptr->crc;
    pstHwStruct->chunk_name          = png_ptr->chunk_name;
    pstHwStruct->mode                = png_ptr->mode;

    /*��ȡ������ַ������*/
    HI_PNG_GetStream(pstHwStruct->s32Handle, &pStream, &u32Len);
    if ((0 == u32Len) || (NULL == pStream))
    {
        pstHwStruct->u8PushState = HIPNG_STATE_SWITCH_COMPLETE;
        return;
    }

    /*�׸��������Ȳ���С��PNG_CHUNK_HEAD_LEN*/
    if (u32Len < PNG_CHUNK_HEAD_LEN)
    {
        HIPNG_TRACE("Unknown error!\n");
    }

    png_ptr->save_buffer         = NULL;
    png_ptr->save_buffer_ptr     = NULL;
    png_ptr->save_buffer_size    = 0;
    png_ptr->save_buffer_max     = 0;
    png_ptr->current_buffer      = pStream;
    png_ptr->current_buffer_ptr  = pStream;
    png_ptr->current_buffer_size = u32Len;
    png_ptr->buffer_size         = png_ptr->current_buffer_size;

    HI_GFX_Memcpy(chunk_length, png_ptr->current_buffer_ptr, 4);
    png_ptr->current_buffer_ptr += 4;
    png_ptr->current_buffer_size -= 4;
    png_ptr->buffer_size -= 4;
    png_ptr->push_length = png_get_uint_31(png_ptr, chunk_length);
    png_ptr->idat_size = png_ptr->push_length;
    HI_GFX_Memcpy(chunk_tag, png_ptr->current_buffer_ptr, 4);
    png_ptr->current_buffer_ptr += 4;
    png_ptr->current_buffer_size -= 4;
    png_ptr->buffer_size -= 4;

    png_reset_crc(png_ptr);
    png_calculate_crc(png_ptr, chunk_tag, 4);
    png_ptr->chunk_name = PNG_CHUNK_FROM_STRING(chunk_tag);
    png_ptr->mode = (mode | PNG_HAVE_CHUNK_HEADER);
    png_ptr->process_mode = PNG_READ_IDAT_MODE;

    return;
}

HI_VOID hipng_push_switch_process(png_structp png_ptr)
{
    hipng_struct_hwctl_s *pstHwStruct = NULL;
    HI_VOID *pStream = NULL;
    HI_U32 u32Len = 0;

    if (NULL == png_ptr)
    {
       return;
    }

    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if ((NULL == pstHwStruct) || (HIPNG_STATE_SWITCH_COMPLETE == pstHwStruct->u8PushState))
    {
        return;
    }

    if ((0 == png_ptr->buffer_size) && pstHwStruct->u8PushState)
    {
        HI_PNG_GetStream(pstHwStruct->s32Handle, &pStream, &u32Len);

        if (u32Len > 0)
        {
            png_ptr->current_buffer = pStream;
            png_ptr->current_buffer_size = u32Len;
            png_ptr->buffer_size = u32Len + png_ptr->save_buffer_size;
            png_ptr->current_buffer_ptr = png_ptr->current_buffer;
        }
        else if (pstHwStruct->bChunkheadValid)
        {
            png_ptr->current_buffer = pstHwStruct->chunkHead;
            png_ptr->current_buffer_size = 8;
            png_ptr->buffer_size = 8 + png_ptr->save_buffer_size;
            png_ptr->current_buffer_ptr = png_ptr->current_buffer;
            pstHwStruct->bChunkheadValid = HI_FALSE;
        }
        else
        {
            /*�����ѻָ��꣬�ָ�֮ǰ��״̬*/
            if (HIPNG_STATE_DECODE_FAILED == pstHwStruct->u8PushState)
            {
                if (png_ptr->save_buffer)
                {
                    HIPNG_TRACE("Free old buf!\n");
                    png_free(png_ptr, png_ptr->save_buffer);
                }
                png_ptr->save_buffer = pstHwStruct->save_buffer;
                png_ptr->save_buffer_ptr = pstHwStruct->save_buffer_ptr;
                png_ptr->save_buffer_size = pstHwStruct->save_buffer_size;
                png_ptr->save_buffer_max = pstHwStruct->save_buffer_max;
                png_ptr->current_buffer = pstHwStruct->current_buffer;
                png_ptr->current_buffer_ptr = pstHwStruct->current_buffer_ptr;
                png_ptr->current_buffer_size = pstHwStruct->current_buffer_size;
                png_ptr->buffer_size = pstHwStruct->buffer_size;
                png_ptr->push_length = pstHwStruct->push_length;
                png_ptr->crc = pstHwStruct->crc;
                png_ptr->chunk_name = pstHwStruct->chunk_name;
                png_ptr->mode |= pstHwStruct->mode;
                png_ptr->process_mode = PNG_READ_CHUNK_MODE;
            }
            else
            {
                HIPNG_TRACE("%d, %d, %d\n", png_ptr->save_buffer_size,
                            png_ptr->current_buffer_size, png_ptr->buffer_size);
                png_ptr->save_buffer = pstHwStruct->save_buffer;
                png_ptr->save_buffer_ptr = pstHwStruct->save_buffer_ptr;
                png_ptr->save_buffer_size = pstHwStruct->save_buffer_size;
                png_ptr->save_buffer_max = pstHwStruct->save_buffer_max;
                png_ptr->current_buffer = pstHwStruct->current_buffer;
                png_ptr->current_buffer_ptr = pstHwStruct->current_buffer_ptr;
                png_ptr->current_buffer_size = pstHwStruct->current_buffer_size;
                png_ptr->buffer_size = pstHwStruct->buffer_size;
            }
            pstHwStruct->u8PushState = HIPNG_STATE_SWITCH_COMPLETE;
        }
    }

    return;
}
#endif

static HI_S32 hipng_do_expand(png_structp png_ptr, HI_PNG_TRANSFORM_S *pstTransform)
{
    HI_U32 *pu32Clut = HI_NULL;
    HI_U32 i = 0;
    HI_U8 u8Alpha = 0;
    hipng_struct_hwctl_s *pstHwStruct = NULL;

    if ((NULL == png_ptr) || (NULL == pstTransform))
    {
       return HI_FAILURE;
    }

    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (NULL == pstHwStruct)
    {
       return HI_FAILURE;
    }

    pstTransform->u32Transform |= HI_PNG_TRANSFORM_ADJUSTPIXELORDER;
    pstTransform->u32Transform |= HI_PNG_TRANSFORM_GRAY124TO8;
    pstTransform->u32Transform |= HI_PNG_TRANSFORM_CLUT2RGB;

    if (png_ptr->color_type & PNG_COLOR_MASK_PALETTE)
    {
        HI_BOOL bMmu;
#ifdef CONFIG_GFX_MMU_SUPPORT
        HI_CHAR *pZoneName = "iommu";
#else
        HI_CHAR *pZoneName = NULL;
#endif

        /* alloc palette*/
#ifdef CONFIG_GFX_MEM_MMZ
#ifndef CONFIG_GFX_PROC_UNSUPPORT
        pstTransform->u32ClutPhyaddr = HI_GFX_AllocMem(256 * 4, 16, pZoneName, "PNG_PALETTE", &bMmu);
#else
        pstTransform->u32ClutPhyaddr = HI_GFX_AllocMem(256 * 4, 16, pZoneName, HI_NULL, &bMmu);
#endif
#else
#ifndef CONFIG_GFX_PROC_UNSUPPORT
        pstTransform->u32ClutPhyaddr = HI_GFX_AllocMem(pstHwStruct->s32MmzFd, 256 * 4, 16, pZoneName, "PNG_PALETTE", &(pstHwStruct->pPallateMemData), &bMmu);
#else
        pstTransform->u32ClutPhyaddr = HI_GFX_AllocMem(pstHwStruct->s32MmzFd, 256 * 4, 16, pZoneName, HI_NULL, &(pstHwStruct->pPallateMemData), &bMmu);
#endif
#endif
        if (0 == pstTransform->u32ClutPhyaddr)
        {
#ifdef CONFIG_GFX_MEM_MMZ
            HI_GFX_FreeMem(pstTransform->u32ClutPhyaddr, bMmu);
#else
            HI_GFX_FreeMem(pstHwStruct->s32MmzFd, pstTransform->u32ClutPhyaddr, pstHwStruct->pPallateMemData, bMmu);
#endif
            return HI_FAILURE;
        }

#ifdef CONFIG_GFX_MEM_MMZ
        pu32Clut = (HI_U32 *)HI_GFX_MapCached(pstTransform->u32ClutPhyaddr, bMmu);
#else
        pu32Clut = (HI_U32 *)HI_GFX_MapCached(pstHwStruct->s32MmzFd, pstTransform->u32ClutPhyaddr, pstHwStruct->pPallateMemData);
#endif
        if (HI_NULL == pu32Clut)
        {
#ifdef CONFIG_GFX_MEM_MMZ
            HI_GFX_FreeMem(pstTransform->u32ClutPhyaddr, bMmu);
#else
            HI_GFX_FreeMem(pstHwStruct->s32MmzFd, pstTransform->u32ClutPhyaddr, pstHwStruct->pPallateMemData, bMmu);
#endif
            return HI_FAILURE;
        }

        pstHwStruct->pallateaddr = pstTransform->u32ClutPhyaddr;

        if (png_ptr->num_trans || (png_ptr->transformations & PNG_ADD_ALPHA))
        {
            pstHwStruct->bPallateAlpha = HI_TRUE;
        }
        else
        {
            pstHwStruct->bPallateAlpha = HI_FALSE;
        }

        pstTransform->bClutAlpha = pstHwStruct->bPallateAlpha;

        for (i = 0; i < png_ptr->num_palette; i++)
        {
            if (png_ptr->num_trans)
            {
                if (i < png_ptr->num_trans)
                {
#if PNG_LIBPNG_VER >= 10400
                        u8Alpha = png_ptr->trans_alpha[i];
#else
                        u8Alpha = png_ptr->trans[i];
#endif
                }
                else
                {
                    u8Alpha = 0xff;
                }
            }
            else
            {
                if (png_ptr->transformations & PNG_ADD_ALPHA)
                {
                    u8Alpha = png_ptr->filler;
                }
                else
                {
                    u8Alpha = 0xff;
                }
            }
            *(pu32Clut + i) = (u8Alpha << 24) | (png_ptr->palette[i].red << 16)
                              | (png_ptr->palette[i].green << 8) | png_ptr->palette[i].blue;
        }

#ifdef CONFIG_GFX_MEM_MMZ
        HI_GFX_Flush(0, bMmu);
        HI_GFX_Unmap(pstTransform->u32ClutPhyaddr, bMmu);
#else
        HI_GFX_Flush(pstHwStruct->s32MmzFd, 0, pstHwStruct->pPallateMemData);
        HI_GFX_Unmap(pstHwStruct->s32MmzFd, pstTransform->u32ClutPhyaddr, pstHwStruct->pPallateMemData);
#endif
    }

    return HI_SUCCESS;
}

static HI_VOID hipng_do_trans(png_structp png_ptr, HI_PNG_TRANSFORM_S *pstTransform)
{
    if ((NULL == png_ptr) || (NULL == pstTransform))
    {
       return;
    }
    pstTransform->u32Transform |= HI_PNG_TRANSFORM_ADDALPHA;
    pstTransform->eAddAlphaMode = HI_PNG_ADDALPHA_TRNS;
    if (png_ptr->color_type & PNG_COLOR_MASK_COLOR)
    {
#if PNG_LIBPNG_VER > 10246
        pstTransform->sTrnsInfo.u16Red = png_ptr->trans_color.red;
        pstTransform->sTrnsInfo.u16Green = png_ptr->trans_color.green;
        pstTransform->sTrnsInfo.u16Blue = png_ptr->trans_color.blue;
#else
        pstTransform->sTrnsInfo.u16Red = png_ptr->trans_values.red;
        pstTransform->sTrnsInfo.u16Green = png_ptr->trans_values.green;
        pstTransform->sTrnsInfo.u16Blue = png_ptr->trans_values.blue;
#endif
    }
    else
    {
#if PNG_LIBPNG_VER > 10246
        pstTransform->sTrnsInfo.u16Blue = png_ptr->trans_color.gray;
#else
        pstTransform->sTrnsInfo.u16Blue = png_ptr->trans_values.gray;
#endif
    }
    pstTransform->u16Filler = 0xffff;

    return;
}

HI_S32 hipng_set_transform(png_structp png_ptr, HI_PNG_TRANSFORM_S *pstTransform)
{
    hipng_struct_hwctl_s *pstHwStruct = NULL;

    if ((NULL == png_ptr) || (NULL == pstTransform))
    {
       return HI_FAILURE;
    }

    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (NULL == pstHwStruct)
    {
       return HI_FAILURE;
    }

    pstTransform->e124To8Mode = HI_PNG_124TO8_ACCURATE;
    pstTransform->e16To8Mode  = HI_PNG_16TO8_BRIEF;

    /* 1.if 1/2/4bit gray image,expand 8bit; alpha deal with
        2.if palette to RGB*/
    if (png_ptr->transformations & PNG_EXPAND)
    {
        HI_S32 s32Ret = hipng_do_expand(png_ptr, pstTransform);
        if (HI_SUCCESS != s32Ret)
        {
            return HI_FAILURE;
        }
    }

    /* swap pixels order*/
    if (png_ptr->transformations & PNG_PACKSWAP)
    {
        pstTransform->u32Transform |= HI_PNG_TRANSFORM_ADJUSTPIXELORDER;
    }

    if (png_ptr->transformations & PNG_GRAY_TO_RGB)
    {
        pstTransform->u32Transform |= HI_PNG_TRANSFORM_GRAY2RGB;
    }

    if ((png_ptr->transformations & PNG_EXPAND_tRNS) && png_ptr->num_trans)
    {
        hipng_do_trans(png_ptr, pstTransform);
    }
    else if (png_ptr->transformations & PNG_ADD_ALPHA
             || png_ptr->transformations & PNG_FILLER)
    {
        pstTransform->u32Transform |= HI_PNG_TRANSFORM_ADDALPHA;
        pstTransform->eAddAlphaMode = HI_PNG_ADDALPHA_BRIEF;
        pstTransform->u16Filler = png_ptr->filler;
    }

#if PNG_LIBPNG_VER >= 10400
    if (png_ptr->flags & PNG_STRIP_ALPHA)
#else
    if (png_ptr->flags & PNG_FLAG_STRIP_ALPHA)
#endif
    {
        pstTransform->u32Transform |= HI_PNG_TRANSFORM_STRIPALPHA;
    }

    if (png_ptr->transformations & PNG_BGR)
    {
        pstTransform->u32Transform |= HI_PNG_TRANSFORM_BGR2RGB;
    }

    if (png_ptr->transformations & PNG_SWAP_ALPHA)
    {
        pstTransform->u32Transform |= HI_PNG_TRANSFORM_SWAPALPHA;
    }

    if (png_ptr->transformations & PNG_16_TO_8)
    {
        pstTransform->u32Transform |= HI_PNG_TRANSFORM_16TO8;
        if (16 == png_ptr->bit_depth)
        {
            pstTransform->u16Filler <<= 8;
        }
    }

    if (png_ptr->transformations & HIPNG_ARGB1555)
    {
        pstTransform->u32Transform |= HI_PNG_TRANSFORM_8TO4;
        pstTransform->eOutFmt = HI_PNG_COLORFMT_ARGB1555;
    }

    if (png_ptr->transformations & HIPNG_ARGB4444)
    {
        pstTransform->u32Transform |= HI_PNG_TRANSFORM_8TO4;
        pstTransform->eOutFmt = HI_PNG_COLORFMT_ARGB4444;
    }

    if (png_ptr->transformations & HIPNG_RGB565)
    {
        pstTransform->u32Transform |= HI_PNG_TRANSFORM_8TO4;
        pstTransform->eOutFmt = HI_PNG_COLORFMT_RGB565;
    }

    if (png_ptr->transformations & HIPNG_RGB555)
    {
        pstTransform->u32Transform |= HI_PNG_TRANSFORM_8TO4;
        pstTransform->eOutFmt = HI_PNG_COLORFMT_RGB555;
    }

    if (png_ptr->transformations & HIPNG_RGB444)
    {
        pstTransform->u32Transform |= HI_PNG_TRANSFORM_8TO4;
        pstTransform->eOutFmt = HI_PNG_COLORFMT_RGB444;
    }
    if (png_ptr->transformations & HIPNG_PREMULTI_ALPHA)
    {
#ifdef CONFIG_PNG_PREMULTIALPHA_ENABLE
        pstTransform->u32Transform |= HI_PNG_TRANSFORM_PREMULTI_ALPHA;
#else
        return HI_FAILURE;
#endif
    }

    return HI_SUCCESS;
}

static HI_BOOL HIPNG_ACCELERATE_SUPPORT(png_structp png_ptr)
{
#ifdef CONFIG_GFX_MMU_SUPPORT
    if (png_ptr->color_type == PNG_COLOR_TYPE_PALETTE)
    {
        return HI_FALSE;
    }
#endif

#if (PNG_LIBPNG_VER >= 10400)
    if ((png_ptr->transformations & PNG_QUANTIZE) || (png_ptr->transformations & PNG_COMPOSE))
    {
        return HI_FALSE;
    }
#else
    if ((png_ptr->transformations & PNG_DITHER) || (png_ptr->transformations & PNG_BACKGROUND))
    {
        return HI_FALSE;
    }
#endif

    if (   (png_ptr->interlaced)                               \
        || (png_ptr->transformations & PNG_PACK)               \
        || (png_ptr->transformations & PNG_SHIFT)              \
        || (png_ptr->transformations & PNG_SWAP_BYTES)         \
        || (png_ptr->transformations & PNG_INVERT_MONO)        \
        || (png_ptr->transformations & PNG_BACKGROUND_EXPAND)  \
        || (png_ptr->transformations & PNG_GAMMA)              \
        || (png_ptr->transformations & PNG_INVERT_ALPHA)       \
        || (png_ptr->transformations & PNG_USER_TRANSFORM)     \
        || (png_ptr->transformations & PNG_RGB_TO_GRAY_ERR)    \
        || (png_ptr->transformations & PNG_RGB_TO_GRAY_WARN)   \
        || (png_ptr->transformations & PNG_RGB_TO_GRAY)        \
        || ((png_ptr->transformations & PNG_FILLER) && !(png_ptr->flags & PNG_FLAG_FILLER_AFTER)) \
        || (png_ptr->width >= HIPNG_MAX_WIDTH)                 \
        || (png_ptr->height >= HIPNG_MAX_HEIGHT || png_ptr->height <= HIPNG_MIN_HEIGHT) \
        || (png_ptr->read_row_fn))
     {
         return HI_FALSE;
     }

     return HI_TRUE;
}

static HI_S32 hipng_alloc_mem(png_structp png_ptr)
{
    hipng_struct_hwctl_s *pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);

    HI_BOOL bMmu;
#ifdef CONFIG_GFX_MMU_SUPPORT
    HI_CHAR *pZoneName = "iommu";
#else
    HI_CHAR *pZoneName = NULL;
#endif

    HI_U32 u32MemSize = 0;

    if ((0 == pstHwStruct->u32TmpStride) || (pstHwStruct->u32TmpStride > (UINT_MAX - 0xf)))
    {
        return HI_FAILURE;
    }

    u32MemSize = (pstHwStruct->u32TmpStride + 0xf) & 0xfffffff0;
    if ((unsigned long)u32MemSize * (unsigned long)png_ptr->height > UINT_MAX)
    {
        return HI_FAILURE;
    }

    u32MemSize = u32MemSize * png_ptr->height;
    if (u32MemSize >= HIPNG_MAX_MEM)
    {
        return HI_FAILURE;
    }
    else
    {
#ifdef CONFIG_GFX_MEM_MMZ
   #ifndef CONFIG_GFX_PROC_UNSUPPORT
           pstHwStruct->u32TmpPhyaddr = HI_GFX_AllocMem(u32MemSize,
                                        16, pZoneName, "HIPNG_IMAGE_BUF", &bMmu);
   #else
           pstHwStruct->u32TmpPhyaddr = HI_GFX_AllocMem(u32MemSize,
                                        16, pZoneName, HI_NULL, &bMmu);
   #endif
#else
#ifndef CONFIG_GFX_PROC_UNSUPPORT
        pstHwStruct->u32TmpPhyaddr = HI_GFX_AllocMem(pstHwStruct->s32MmzFd, u32MemSize,
                                     16, pZoneName, "HIPNG_IMAGE_BUF", &(pstHwStruct->pTmpMemData), &bMmu);
#else
        pstHwStruct->u32TmpPhyaddr = HI_GFX_AllocMem(pstHwStruct->s32MmzFd, u32MemSize,
                                     16, pZoneName, HI_NULL, &(pstHwStruct->pTmpMemData), &bMmu);

#endif
#endif
        if (0 == pstHwStruct->u32TmpPhyaddr)
        {
            HIPNG_TRACE("no mem:0x%x!\n", u32MemSize);
            return HI_FAILURE;
        }
        else
        {
#ifdef CONFIG_GFX_MEM_MMZ
            pstHwStruct->pu8TmpImage = (HI_U8 *)HI_GFX_MapCached(pstHwStruct->u32TmpPhyaddr, bMmu);
#else
            pstHwStruct->pu8TmpImage = (HI_U8 *)HI_GFX_MapCached(pstHwStruct->s32MmzFd, pstHwStruct->u32TmpPhyaddr, pstHwStruct->pTmpMemData);
#endif
            if (HI_NULL == pstHwStruct->pu8TmpImage)
            {
#ifdef CONFIG_GFX_MEM_MMZ
                HI_GFX_FreeMem(pstHwStruct->u32TmpPhyaddr, bMmu);
#else
                HI_GFX_FreeMem(pstHwStruct->s32MmzFd, pstHwStruct->u32TmpPhyaddr, pstHwStruct->pTmpMemData, bMmu);
#endif
                pstHwStruct->u32TmpPhyaddr = 0;
                HIPNG_TRACE("no mem:0x%x!\n", u32MemSize);
                return HI_FAILURE;
            }

        }
    }

    return HI_SUCCESS;
}

static HI_S32 hipng_check_addr(png_structp png_ptr, png_bytepp image, HI_U32 *pAddr, HI_U32 *pStride)
{
    hipng_struct_hwctl_s *pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    HI_S32 s32Ret;
    HI_U32 u32Size;
    HI_U32 i;

#ifdef CONFIG_GFX_MEM_MMZ
    HI_BOOL bMmu;
    s32Ret = HI_GFX_GetPhyaddr(image[0], pAddr, &u32Size, &bMmu);
#else
    s32Ret = HI_GFX_GetPhyaddr(pstHwStruct->s32MmzFd, image[0], pAddr, &u32Size, NULL);
#endif
    if (s32Ret < 0)
    {
        return HI_FAILURE;
    }

    if ( (image[1] - image[0] < 0) || ((HI_U32)(image[1] - image[0]) > u32Size) ||  (((image[1] - image[0]) & 0xf) != 0))
    {
        return HI_FAILURE;
    }

    *pStride = image[1] - image[0];

    for (i = 2; i < png_ptr->height; i++)
    {
        if (((HI_U32)(image[i] - image[0]) > u32Size) || ((HI_U32)(image[i] - image[i - 1]) != *pStride)
            || (image[i] - image[0]  < 0) || (image[i] - image[i - 1] < 0))
        {
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

HI_U8 hipng_select_decmode(png_structp png_ptr, png_bytepp image, png_uint_32 num_rows)
{
    hipng_struct_hwctl_s *pstHwStruct = NULL;
    HI_U32 u32Phyaddr = 0;
    HI_U32 u32Stride = 0;
    HI_S32 s32Ret;
    HI_U8 u8DecMode;
    HI_S32 Support = HI_FALSE;
    if (NULL == png_ptr)
    {
        return HIPNG_NO_DEC;
    }

    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (NULL == pstHwStruct)
    {
        return HIPNG_NO_DEC;
    }

    if (pstHwStruct->u8DecMode != HIPNG_NO_DEC)
    {
        return pstHwStruct->u8DecMode;
    }

    Support = HIPNG_ACCELERATE_SUPPORT(png_ptr);
    if (HI_TRUE != Support)
    {
        pstHwStruct->u8SupportDecMode &= ~HIPNG_HW_DEC;
        pstHwStruct->u8SupportDecMode &= ~HIPNG_HWCOPY_DEC;
        goto CHECKSOFT;
    }

    if (image && (num_rows == png_ptr->height))
    {
        s32Ret = hipng_check_addr(png_ptr, image, &u32Phyaddr, &u32Stride);
        if (HI_SUCCESS != s32Ret)
        {
            pstHwStruct->u8SupportDecMode &= ~HIPNG_HW_DEC;
        }
    }
    else
    {
        pstHwStruct->u8SupportDecMode &= ~HIPNG_HW_DEC;
    }

CHECKSOFT:
    if (HIPNG_IS_TRANSFORM_FMT(png_ptr->transformations))
    {
        pstHwStruct->u8SupportDecMode &= ~HIPNG_SW_DEC;
    }

    u8DecMode = (pstHwStruct->u8SupportDecMode & pstHwStruct->u8UserDecMode);

    if ((u8DecMode & HIPNG_SW_DEC)
        && ((u8DecMode & HIPNG_HW_DEC) || (u8DecMode & HIPNG_HWCOPY_DEC)))
    {
        if (png_ptr->height * png_ptr->width < pstHwStruct->u32InflexionSize)
        {
            u8DecMode &= ~HIPNG_HW_DEC;
            u8DecMode &= ~HIPNG_HWCOPY_DEC;
        }
    }

    if (!(u8DecMode & HIPNG_HW_DEC) && (u8DecMode & HIPNG_HWCOPY_DEC))
    {
        s32Ret = hipng_alloc_mem(png_ptr);
        if (s32Ret != HI_SUCCESS)
        {
            u8DecMode &= ~HIPNG_HWCOPY_DEC;
        }
    }
    else
    {
        pstHwStruct->u32TmpPhyaddr = u32Phyaddr;
        pstHwStruct->u32TmpStride = u32Stride;
    }

    if (!(u8DecMode & HIPNG_SW_DEC) && !(u8DecMode & HIPNG_HW_DEC)
        && !(u8DecMode & HIPNG_HWCOPY_DEC))
    {
        png_error(png_ptr, "Unsupport!\n");
    }

    pstHwStruct->u8DecMode = u8DecMode;

    return pstHwStruct->u8DecMode;
}

void hipng_read_fn(png_structp png_ptr, png_bytep pbuf, png_size_t size)
{
    hipng_struct_hwctl_s *pstHwStruct = NULL;
    png_size_t read = 0;

   if ((NULL == png_ptr) || (NULL == pbuf))
    {
        return;
    }
    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (NULL == pstHwStruct)
    {
        return;
    }

    read = pstHwStruct->read_data_fn_hw(pbuf, size, pstHwStruct->s32Handle);
    if (read != size)
    {
        size -= read;
        pstHwStruct->read_data_fn(png_ptr, pbuf + read, size);
    }

    return;
}

HI_S32 hipng_get_readfn(png_structp png_ptr)
{
    HI_S32 s32Ret = HI_SUCCESS;
    hipng_struct_hwctl_s *pstHwStruct = NULL;
    if (NULL == png_ptr)
    {
        return HI_FAILURE;
    }

    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (NULL == pstHwStruct)
    {
        return HI_FAILURE;
    }

    s32Ret = HI_PNG_GetReadPtr(pstHwStruct->s32Handle, &pstHwStruct->read_data_fn_hw);
    if (s32Ret < 0)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

void hipng_prepare_switch(png_structp png_ptr)
{
    hipng_struct_hwctl_s *pstHwStruct = NULL;
    HI_S32 s32Ret = 0;
    if (NULL == png_ptr)
    {
        return;
    }
    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (NULL == pstHwStruct)
    {
        return;
    }

    pstHwStruct->read_data_fn = png_ptr->read_data_fn;
    s32Ret = hipng_get_readfn(png_ptr);
    if (s32Ret < 0)
    {
        png_error(png_ptr, "Internal Err!\n");
    }

    if (pstHwStruct->read_data_fn_hw != NULL)
    {
        png_ptr->read_data_fn = hipng_read_fn;
        png_ptr->idat_size = png_read_chunk_header(png_ptr);
    }

    return;
}

void hipng_finish_switch(png_structp png_ptr)
{
    hipng_struct_hwctl_s *pstHwStruct = NULL;
    if (NULL == png_ptr)
    {
        return;
    }
    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (NULL == pstHwStruct)
    {
        return;
    }

    /*Resume original IO funciton after finishing decode*/
#if PNG_LIBPNG_VER >= 10400
    if (png_ptr->flags & PNG_FLAG_ZSTREAM_ENDED)
#else
    if (png_ptr->flags & PNG_FLAG_ZLIB_FINISHED)
#endif
    {
        pstHwStruct->eState = HI_PNG_STATE_FINISH;
        if (pstHwStruct->read_data_fn)
        {
            png_ptr->read_data_fn = pstHwStruct->read_data_fn;
        }
    }

    return;
}

void hipng_copy_rows(png_structp png_ptr, png_bytepp row,
                     png_bytepp display_row, png_uint_32 num_rows)
{
    HI_U32 i;
    hipng_struct_hwctl_s *pstHwStruct = HI_NULL;
    HI_U32 u32CopyRows = num_rows;

    if ((NULL == png_ptr) || (NULL == row))
    {
        return;
    }

    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (NULL == pstHwStruct)
    {
        return;
    }

    if (pstHwStruct->u32CopyRows + u32CopyRows > png_ptr->height)
    {
        u32CopyRows = png_ptr->height - pstHwStruct->u32CopyRows;
    }

    if (u32CopyRows > 0)
    {
        for (i = 0; i < u32CopyRows; i++)
        {
            if (row)
            {
                HI_GFX_Memcpy(row[i], pstHwStruct->pu8TmpImage + ((pstHwStruct->u32TmpStride + 0xf) & 0xfffffff0) * (i + pstHwStruct->u32CopyRows), pstHwStruct->u32TmpStride);
            }
            if (display_row)
            {
                HI_GFX_Memcpy(display_row[i], pstHwStruct->pu8TmpImage + ((pstHwStruct->u32TmpStride + 0xf) & 0xfffffff0) * (i + pstHwStruct->u32CopyRows), pstHwStruct->u32TmpStride);
            }
        }

        pstHwStruct->u32CopyRows += u32CopyRows;
    }

    if (pstHwStruct->u32CopyRows >= png_ptr->height)
    {
        pstHwStruct->eState = HI_PNG_STATE_FINISH;
    }

    return;
}

/*****************************************************************
* func:	png hardware dec
* in:	png_ptr png dec struct
* in:    image target line point
* out:	image data after dec
* ret:	HI_SUCCESS
*		HI_FAILURE
* others:
*****************************************************************/
HI_S32 hipng_read_rows(png_structp png_ptr, png_bytepp row,
                       png_bytepp display_row, png_uint_32 num_rows)
{
    HI_S32 s32Ret = HI_SUCCESS;
    hipng_struct_hwctl_s *pstHwStruct;
    HI_PNG_DECINFO_S stInfo;
    HI_U8 u8DecMode;

    if ((NULL == png_ptr) || (NULL == row))
    {
        return HI_FAILURE;
    }

    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (NULL == pstHwStruct)
    {
        return HI_FAILURE;
    }

    memset(&stInfo, 0, sizeof(HI_PNG_DECINFO_S));

    u8DecMode = hipng_select_decmode(png_ptr, row, num_rows);

    if ((u8DecMode & HIPNG_HW_DEC) || (u8DecMode & HIPNG_HWCOPY_DEC))
    {
        if (pstHwStruct->eState == HI_PNG_STATE_ERR)
        {
            return HI_FAILURE;
        }
        else if (pstHwStruct->eState == HI_PNG_STATE_DECING)
        {
            return HI_SUCCESS;
        }
        else if (pstHwStruct->eState == HI_PNG_STATE_FINISH)
        {
            if (!(u8DecMode & HIPNG_HW_DEC))
            {
                hipng_copy_rows(png_ptr, row, display_row, num_rows);
            }
            return HI_SUCCESS;
        }
    }
    else
    {
        return HI_FAILURE;
    }

    /* read stream*/
    s32Ret = hipng_read_stream(png_ptr);
    if (s32Ret < 0)
    {
        goto ERR;
    }

    s32Ret = hipng_set_transform(png_ptr, &stInfo.stTransform);
    if (s32Ret < 0)
    {
        goto ERR;
    }

    stInfo.bSync = pstHwStruct->bSyncDec;
    stInfo.stPngInfo.eColorFmt = png_ptr->color_type;
    stInfo.stPngInfo.u32Width = png_ptr->width;
    stInfo.stPngInfo.u32Height = png_ptr->height;
    stInfo.stPngInfo.u8BitDepth = png_ptr->bit_depth;
    stInfo.u32Phyaddr = pstHwStruct->u32TmpPhyaddr;
    stInfo.u32Stride = (pstHwStruct->u32TmpStride + 0xf) & 0xfffffff0;

#ifdef CONFIG_GFX_MEM_MMZ
    HI_GFX_Flush(0, HI_TRUE);
#else
    HI_GFX_Flush(pstHwStruct->s32MmzFd, 0, pstHwStruct->pTmpMemData);
#endif
    s32Ret = HI_PNG_Decode(pstHwStruct->s32Handle, &stInfo);
    if (s32Ret < 0)
    {
        goto ERR;
    }

    if (stInfo.bSync)
    {
        pstHwStruct->eState = HI_PNG_STATE_FINISH;
        if (!(u8DecMode & HIPNG_HW_DEC))
        {
            hipng_copy_rows(png_ptr, row, display_row, num_rows);
        }
    }
    else
    {
        pstHwStruct->image = row;
        pstHwStruct->eState = HI_PNG_STATE_DECING;
    }

    return HI_SUCCESS;

ERR:
    pstHwStruct->eState = HI_PNG_STATE_ERR;

    if (!(u8DecMode & HIPNG_SW_DEC))
    {
        png_error(png_ptr, "Internel err!\n");
    }

    hipng_prepare_switch(png_ptr);

    return HI_FAILURE;
}

HI_S32 hipng_get_result(png_structp png_ptr, HI_BOOL bBlock)
{
    HI_S32 s32Ret = HI_SUCCESS;
    hipng_struct_hwctl_s *pstHwStruct = NULL;

    if (NULL == png_ptr)
    {
        return HI_FAILURE;
    }

    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (NULL == pstHwStruct)
    {
        return HI_FAILURE;
    }

    s32Ret = HI_PNG_GetResult(pstHwStruct->s32Handle, bBlock, &pstHwStruct->eState);
    if (s32Ret < 0)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

void PNGAPI
png_set_inflexion(png_structp png_ptr, png_uint_32 u32InflexionSize)
{
    hipng_struct_hwctl_s *pstHwStruct = NULL;
    if (NULL == png_ptr)
    {
        return;
    }

    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (NULL == pstHwStruct)
    {
        return;
    }

    pstHwStruct->u32InflexionSize = u32InflexionSize;

    return;
}

void PNGAPI
png_read_image_async(png_structp png_ptr, png_bytepp image)
{
    hipng_struct_hwctl_s *pstHwStruct = NULL;
    if ((NULL == png_ptr) || (NULL == image))
    {
        return;
    }

    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (NULL != pstHwStruct)
    {
        pstHwStruct->bSyncDec = HI_FALSE;
    }

    png_read_image(png_ptr, image);

    return;
}

void PNGAPI
png_get_state(png_structp png_ptr, PNG_BOOL bBlock, PNG_STATE_E *pState)
{
    HI_S32 s32Ret = 0;
    hipng_struct_hwctl_s *pstHwStruct = NULL;

    if ((NULL == png_ptr) || (NULL == pState))
    {
        return;
    }
    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);

    if (NULL == pstHwStruct)
    {
#if PNG_LIBPNG_VER >= 10400
        if (png_ptr->flags & PNG_FLAG_ZSTREAM_ENDED)
#else
        if (png_ptr->flags & PNG_FLAG_ZLIB_FINISHED)
#endif
        {
            *pState = HI_PNG_STATE_FINISH;
        }
        else
        {
            *pState = HI_PNG_STATE_NOSTART;
        }
        return;
    }

    if (pstHwStruct->bSyncDec)
    {
        *pState = pstHwStruct->eState;
    }
    else
    {
        if (HI_PNG_STATE_DECING == pstHwStruct->eState)
        {
            s32Ret = hipng_get_result(png_ptr, bBlock);
            if (s32Ret < 0)
            {
                png_error(png_ptr, "Internal Err!\n");
            }
        }

        if (HI_PNG_STATE_ERR == pstHwStruct->eState)
        {
            png_read_rows(png_ptr, pstHwStruct->image, NULL, png_ptr->height);
            pstHwStruct->eState = HI_PNG_STATE_FINISH;
            *pState = HI_PNG_STATE_FINISH;
        }
        else
        {
            *pState = pstHwStruct->eState;
            if (*pState == PNG_STATE_FINISH)
            {
                if (!(pstHwStruct->u8DecMode & HIPNG_HW_DEC)
                    && (pstHwStruct->u8DecMode & HIPNG_HWCOPY_DEC)
#if PNG_LIBPNG_VER >= 10400
                    && !(png_ptr->flags & PNG_FLAG_ZSTREAM_ENDED)
#else
                    && !(png_ptr->flags & PNG_FLAG_ZLIB_FINISHED)
#endif
					)
                {
                    hipng_copy_rows(png_ptr, pstHwStruct->image, NULL, png_ptr->height);
                }
            }
        }
    }

    return;
}

void PNGAPI
png_set_outfmt(png_structp png_ptr, HIPNG_FMT_E eOutFmt)
{
    if (NULL == png_ptr)
    {
        return;
    }

    switch (eOutFmt)
    {
        case HIPNG_FMT_ARGB4444:
        {
            png_ptr->transformations |= HIPNG_ARGB4444;
            return;
        }
        case HIPNG_FMT_ARGB1555:
        {
            png_ptr->transformations |= HIPNG_ARGB1555;
            return;
        }
        case HIPNG_FMT_RGB565:
        {
            png_ptr->transformations |= HIPNG_RGB565;
            return;
        }
        case HIPNG_FMT_RGB555:
        {
            png_ptr->transformations |= HIPNG_RGB555;
            return;
        }
        case HIPNG_FMT_RGB444:
        {
            png_ptr->transformations |= HIPNG_RGB444;
            return;
        }
        default:
            return;
    }
}

void PNGAPI
png_set_swdec(png_structp png_ptr)
{
    hipng_struct_hwctl_s *pstHwStruct = NULL;

    if (NULL == png_ptr)
    {
        return;
    }

    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (pstHwStruct == NULL)
    {
        return;
    }

    pstHwStruct->u8UserDecMode = HIPNG_SW_DEC;

    return;
}


HI_VOID hipng_read_transform_info(png_structp png_ptr, png_infop info_ptr)
{
    hipng_struct_hwctl_s *pstHwStruct = NULL;
    if ((NULL == png_ptr) || (NULL == info_ptr))
    {
        return;
    }
    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (NULL == pstHwStruct)
    {
        return;
    }

    if ((png_ptr->transformations & HIPNG_ARGB1555)
        || (png_ptr->transformations & HIPNG_ARGB4444)
        || (png_ptr->transformations & HIPNG_RGB565)
        || (png_ptr->transformations & HIPNG_RGB555)
        || (png_ptr->transformations & HIPNG_RGB444))
    {
        if (info_ptr->color_type == PNG_COLOR_TYPE_RGBA && info_ptr->bit_depth == 8)
        {
            info_ptr->rowbytes /= 2;
        }
    }

    pstHwStruct->u32TmpStride = info_ptr->rowbytes;
    pstHwStruct->pixel_depth = info_ptr->pixel_depth;

    return;
}

void PNGAPI
png_read_png_async(png_structp png_ptr, png_infop info_ptr,
                   int transforms, png_voidp params)
{
    hipng_struct_hwctl_s *pstHwStruct = NULL;

    if ((NULL == png_ptr) || (NULL == info_ptr))
    {
        return;
    }

    pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);
    if (NULL == pstHwStruct)
    {
        return;
    }

    pstHwStruct->bSyncDec = HI_FALSE;

    png_read_png(png_ptr, info_ptr, transforms, params);
}

HI_VOID hipng_set_outfmt(png_structp png_ptr, int transforms)
{
    if (NULL == png_ptr)
    {
       return;
    }

    if (transforms & HIPNG_TRANSFORM_ARGB1555)
    {
        png_set_outfmt(png_ptr, HIPNG_FMT_ARGB1555);
    }
    else if (transforms & HIPNG_TRANSFORM_ARGB4444)
    {
        png_set_outfmt(png_ptr, HIPNG_FMT_ARGB4444);
    }
    else if (transforms & HIPNG_TRANSFORM_RGB565)
    {
        png_set_outfmt(png_ptr, HIPNG_FMT_RGB565);
    }
    else if (transforms & HIPNG_TRANSFORM_RGB555)
    {
        png_set_outfmt(png_ptr, HIPNG_FMT_RGB555);
    }
    else if (transforms & HIPNG_TRANSFORM_RGB444)
    {
        png_set_outfmt(png_ptr, HIPNG_FMT_RGB444);
    }

    return;
}

#ifdef PNG_DO_PREMULTI_TO_ALPHA
void PNGAPI
png_set_premulti_alpha(png_structp png_ptr)
{
    if (png_ptr == NULL)
    {
        return;
    }

    png_ptr->transformations |= HIPNG_PREMULTI_ALPHA;
}

HI_VOID /* PRIVATE */
png_do_premulti_alpha(png_row_infop row_info, png_bytep row, png_uint_32 flags)
{
    if ((NULL == row_info) || (NULL == row))
    {
        return;
    }

    {
        png_uint_32 row_width = row_info->width;
        png_uint_32 i;
        char r, b, g;
        if (((row_info->color_type == PNG_COLOR_TYPE_RGB) && (row_info->bit_depth == 8) &&
             (row_info->channels == 4)) || ((row_info->color_type == PNG_COLOR_TYPE_RGB_ALPHA) && (row_info->bit_depth == 8)))
        {
            if (flags & PNG_FLAG_ALPHA_SWAP)
            {
                for (i = 0; i < row_width; i++)
                {
                    r = ((*(row + 1)) * (*(row) + 1) + 128) >> 8;
                    g = ((*(row + 2)) * (*(row) + 1) + 128) >> 8;
                    b = ((*(row + 3)) * (*(row) + 1) + 128) >> 8;
                    *(row + 1) = r;
                    *(row + 2) = g;
                    *(row + 3) = b;
                    row += 4;
                }
            }
            else
            {
                for (i = 0; i < row_width; i++)
                {
                    r = ((*row) * (*(row + 3) + 1) + 128) >> 8;
                    g = ((*(row + 1)) * (*(row + 3) + 1) + 128) >> 8;
                    b = ((*(row + 2)) * (*(row + 3) + 1) + 128) >> 8;
                    *(row) = r;
                    *(row + 1) = g;
                    *(row + 2) = b;
                    row += 4;
                }
            }
        }

    }
}
#endif
#endif
