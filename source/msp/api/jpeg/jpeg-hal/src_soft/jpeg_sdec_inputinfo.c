/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name        : jpeg_sdec_inputinfo.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      : get table
Function List    :


History          :
Date                  Author                 Modification
2018/01/01            sdk                    Created file
***************************************************************************************************/

/***************************** add include here****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jpeglib.h"
#include "jerror.h"

#include "hi_jpeg_api.h"
#include "jpeg_sdec_api.h"
#include "jpeg_sdec_table.c"
/***************************** Macro Definition ***************************************************/


/***************************** Structure Definition ***********************************************/

/***************************** Global Variable declaration ****************************************/

/***************************** API forward declarations *******************************************/

/******************************* API realization **************************************************/
static inline HI_VOID JPEG_SDEC_SetInputColorSpace(j_decompress_ptr cinfo, JPEG_IMG_INFO_S *pstImgInfo)
{
    if (cinfo->num_components == 1)
    {
       if (cinfo->comp_info[0].h_samp_factor==cinfo->comp_info[0].v_samp_factor)
       {
             pstImgInfo->jpeg_color_space = HI_JPEG_FMT_YUV400;
             pstImgInfo->u8Fac[0][0] = 1;
             pstImgInfo->u8Fac[0][1] = 1;
             pstImgInfo->u8Fac[1][0] = 0;
             pstImgInfo->u8Fac[1][1] = 0;
             pstImgInfo->u8Fac[2][0] = 0;
             pstImgInfo->u8Fac[2][1] = 0;
       }
    }
    else if ((cinfo->num_components == 3) && (cinfo->comp_info[1].h_samp_factor == cinfo->comp_info[2].h_samp_factor) && (cinfo->comp_info[1].v_samp_factor == cinfo->comp_info[2].v_samp_factor))
    {
        if (cinfo->comp_info[0].h_samp_factor == ((cinfo->comp_info[1].h_samp_factor)<<1))
        {
             if (cinfo->comp_info[0].v_samp_factor == ((cinfo->comp_info[1].v_samp_factor)<<1))
             {
                pstImgInfo->jpeg_color_space = HI_JPEG_FMT_YUV420;
             }
             else if (cinfo->comp_info[0].v_samp_factor == cinfo->comp_info[1].v_samp_factor)
             {
                  pstImgInfo->jpeg_color_space = HI_JPEG_FMT_YUV422_21;
             }

         }
         else if (cinfo->comp_info[0].h_samp_factor == cinfo->comp_info[1].h_samp_factor)
         {
               if (cinfo->comp_info[0].v_samp_factor == ((cinfo->comp_info[1].v_samp_factor)<<1))
               {
                    pstImgInfo->jpeg_color_space = HI_JPEG_FMT_YUV422_12;
               }
               else if (cinfo->comp_info[0].v_samp_factor == cinfo->comp_info[1].v_samp_factor)
               {
                    pstImgInfo->jpeg_color_space = HI_JPEG_FMT_YUV444;
               }
          }
          pstImgInfo->u8Fac[0][0] = cinfo->comp_info[0].h_samp_factor;
          pstImgInfo->u8Fac[0][1] = cinfo->comp_info[0].v_samp_factor;
          pstImgInfo->u8Fac[1][0] = cinfo->comp_info[1].h_samp_factor;
          pstImgInfo->u8Fac[1][1] = cinfo->comp_info[1].v_samp_factor;
          pstImgInfo->u8Fac[2][0] = cinfo->comp_info[2].h_samp_factor;
          pstImgInfo->u8Fac[2][1] = cinfo->comp_info[2].v_samp_factor;
    }
    else
    {
        pstImgInfo->jpeg_color_space = HI_JPEG_FMT_BUTT;
    }

    if (JCS_CMYK  == cinfo->jpeg_color_space)
    {
        pstImgInfo->jpeg_color_space = HI_JPEG_FMT_CMYK;
    }

    if (JCS_YCCK  == cinfo->jpeg_color_space)
    {
        pstImgInfo->jpeg_color_space = HI_JPEG_FMT_YCCK;
    }

    if (JCS_RGB  == cinfo->jpeg_color_space)
    {
        pstImgInfo->jpeg_color_space = HI_JPEG_FMT_RGB_888;
    }

    return;
}

static inline HI_VOID JPEG_SDEC_SetLuDcCodeLen(j_decompress_ptr cinfo, JPEG_IMG_INFO_S *pstImgInfo)
{
    if (NULL != cinfo->dc_huff_tbl_ptrs[0])
    {
        pstImgInfo->LuDcLen[0] = cinfo->dc_huff_tbl_ptrs[0]->bits[11];
        pstImgInfo->LuDcLen[1] = cinfo->dc_huff_tbl_ptrs[0]->bits[12];
        pstImgInfo->LuDcLen[2] = cinfo->dc_huff_tbl_ptrs[0]->bits[13];
        pstImgInfo->LuDcLen[3] = cinfo->dc_huff_tbl_ptrs[0]->bits[14];
        pstImgInfo->LuDcLen[4] = cinfo->dc_huff_tbl_ptrs[0]->bits[15];
        pstImgInfo->LuDcLen[5] = cinfo->dc_huff_tbl_ptrs[0]->bits[16];
    }

    if (NULL != cinfo->dc_huff_tbl_ptrs[1])
    {
        pstImgInfo->LuDcLen[0] = cinfo->dc_huff_tbl_ptrs[1]->bits[11];
        pstImgInfo->LuDcLen[1] = cinfo->dc_huff_tbl_ptrs[1]->bits[12];
        pstImgInfo->LuDcLen[2] = cinfo->dc_huff_tbl_ptrs[1]->bits[13];
        pstImgInfo->LuDcLen[3] = cinfo->dc_huff_tbl_ptrs[1]->bits[14];
        pstImgInfo->LuDcLen[4] = cinfo->dc_huff_tbl_ptrs[1]->bits[15];
        pstImgInfo->LuDcLen[5] = cinfo->dc_huff_tbl_ptrs[1]->bits[16];
    }

    return;
}

static inline HI_VOID JPEG_SDEC_HufTableNumSupport(j_decompress_ptr cinfo, JPEG_IMG_INFO_S *pstImgInfo)
{
    HI_S32 ComponentNum = 0;

    for (ComponentNum = 0; ComponentNum < cinfo->num_components && ComponentNum < HI_MAX_COMPS_IN_SCAN; ComponentNum++)
    {
       if (NULL == cinfo->cur_comp_info[ComponentNum])
       {
          pstImgInfo->HuffTabNoSupport = HI_FALSE;
          return;
       }

       if (cinfo->cur_comp_info[ComponentNum]->dc_tbl_no != cinfo->cur_comp_info[ComponentNum]->ac_tbl_no)
       {
          pstImgInfo->HuffTabNoSupport = HI_FALSE;
          return;
       }

       if ((cinfo->cur_comp_info[ComponentNum]->dc_tbl_no >= 2) || (cinfo->cur_comp_info[ComponentNum]->ac_tbl_no >= 2))
       {
          pstImgInfo->HuffTabNoSupport = HI_FALSE;
          return;
       }
    }

    pstImgInfo->HuffTabNoSupport = HI_TRUE;

    return;
}

static inline HI_VOID JPEG_SDEC_SampleFactorSupport(j_decompress_ptr cinfo, JPEG_IMG_INFO_S *pstImgInfo)
{
    HI_S32  ComponentCnt = 0;
    HI_BOOL bY22 = HI_FALSE;
    HI_BOOL bU12 = HI_FALSE;
    HI_BOOL bV12 = HI_FALSE;
    jpeg_component_info *compptr = NULL;

    if (cinfo->comps_in_scan >= MAX_COMPS_IN_SCAN)
    {
        return;
    }

    for (ComponentCnt = 0; ComponentCnt < cinfo->comps_in_scan; ComponentCnt++)
    {
         compptr = cinfo->cur_comp_info[ComponentCnt];
         if( (0 == ComponentCnt) && (2 == compptr->h_samp_factor) && (2 == compptr->v_samp_factor))
             bY22 = HI_TRUE;
         if( (1 == ComponentCnt) && (1 == compptr->h_samp_factor) && (2 == compptr->v_samp_factor))
             bU12 = HI_TRUE;
         if( (2 == ComponentCnt) && (1 == compptr->h_samp_factor) && (2 == compptr->v_samp_factor))
             bV12 = HI_TRUE;
    }

    if ( (HI_TRUE == bY22) && (HI_TRUE == bU12) && (HI_TRUE == bV12))
    {
         pstImgInfo->SampleFactorSupport = HI_FALSE;
    }

    if ( (HI_JPEG_FMT_YUV444 == pstImgInfo->jpeg_color_space) && (HI_TRUE == bU12) && (HI_TRUE == bV12))
    {
        pstImgInfo->SampleFactorSupport = HI_FALSE;
    }

    pstImgInfo->SampleFactorSupport = HI_TRUE;

    return;
}

static inline HI_VOID JPEG_SDEC_SetInputImgeInfo(j_decompress_ptr cinfo)
{
    HI_S32 Cnt = 0;
    HI_S32 Cnt1 = 0;
    HI_S32 Cnt2 = 0;
    JPEG_IMG_INFO_S stImgInfo;
    jpeg_component_info *compptr = NULL;

    if ((NULL == cinfo) || (NULL == cinfo->src))
    {
       return;
    }

    HI_GFX_Memset(&stImgInfo, 0x0, sizeof(stImgInfo));

    JPEG_DEC_GetImgInfo((HI_ULONG)cinfo->client_data, &stImgInfo);

    stImgInfo.progressive_mode = cinfo->progressive_mode;
    stImgInfo.arith_code       = cinfo->arith_code;
    stImgInfo.data_precision   = cinfo->data_precision;
    stImgInfo.restart_interval = cinfo->restart_interval;

    stImgInfo.image_width = cinfo->image_width;
    stImgInfo.image_height = cinfo->image_height;

    stImgInfo.bytes_in_buffer  = cinfo->src->bytes_in_buffer;
    stImgInfo.next_input_byte  = (HI_CHAR*)cinfo->src->next_input_byte;
    stImgInfo.curpos_in_buffer = cinfo->src->current_offset - cinfo->src->bytes_in_buffer;

    JPEG_SDEC_SetInputColorSpace(cinfo, &stImgInfo);

    JPEG_SDEC_SetLuDcCodeLen(cinfo, &stImgInfo);

    JPEG_SDEC_HufTableNumSupport(cinfo, &stImgInfo);

    JPEG_SDEC_SampleFactorSupport(cinfo, &stImgInfo);

    /**set table **/
    stImgInfo.num_components = cinfo->num_components;

    if (cinfo->num_components > HI_JPEG_MAX_COMPONENT_NUM)
    {
        return;
    }

    for (Cnt = 0; Cnt < MAX_NUM_QUANT_TBLS; Cnt++)
    {
        if (NULL == cinfo->quant_tbl_ptrs[Cnt])
        {
            continue;
        }

        stImgInfo.QuantTbl[Cnt].bHasQuantTbl = HI_TRUE;

        for (Cnt1 = 0; Cnt1 < HI_DCT_SIZE2; Cnt1++)
        {
            stImgInfo.QuantTbl[Cnt].quantval[Cnt1] = cinfo->quant_tbl_ptrs[Cnt]->quantval[Cnt1];
        }
    }

    for (Cnt = 0, compptr = cinfo->comp_info; Cnt < cinfo->num_components; Cnt++, compptr++)
    {
        if (NULL == cinfo->comp_info)
        {
           continue;
        }
        stImgInfo.stComponentInfo[Cnt].QuantTblNo = compptr->quant_tbl_no;
    }

    for (Cnt = 0; Cnt < MAX_NUM_HUFF_TBLS; Cnt++)
    {
        if (NULL == cinfo->dc_huff_tbl_ptrs[Cnt])
        {
           continue;
        }

        stImgInfo.DcHuffTbl[Cnt].bHasHuffTbl = HI_TRUE;

        for (Cnt1 = 0; Cnt1 < 17; Cnt1++)
        {
            stImgInfo.DcHuffTbl[Cnt].bits[Cnt1] = cinfo->dc_huff_tbl_ptrs[Cnt]->bits[Cnt1];
        }

        for (Cnt2 = 0; Cnt2 < 256; Cnt2++)
        {
            stImgInfo.DcHuffTbl[Cnt].huffval[Cnt2] = cinfo->dc_huff_tbl_ptrs[Cnt]->huffval[Cnt2];
        }
    }

    for (Cnt = 0; Cnt < MAX_NUM_HUFF_TBLS; Cnt++)
    {

        if (NULL == cinfo->ac_huff_tbl_ptrs[Cnt])
        {
            continue;
        }

        stImgInfo.AcHuffTbl[Cnt].bHasHuffTbl = HI_TRUE;

        for (Cnt1 = 0; Cnt1 < 17; Cnt1++)
        {
            stImgInfo.AcHuffTbl[Cnt].bits[Cnt1] = cinfo->ac_huff_tbl_ptrs[Cnt]->bits[Cnt1];
        }
        for (Cnt2 = 0; Cnt2 < 256; Cnt2++)
        {
            stImgInfo.AcHuffTbl[Cnt].huffval[Cnt2] = cinfo->ac_huff_tbl_ptrs[Cnt]->huffval[Cnt2];
        }
    }

    JPEG_SDEC_GetTable(&stImgInfo);

    JPEG_DEC_SetImgInfo((HI_ULONG)cinfo->client_data, &stImgInfo);

    return;
}
