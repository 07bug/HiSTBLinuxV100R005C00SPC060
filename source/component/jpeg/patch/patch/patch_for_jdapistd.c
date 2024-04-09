/**************************************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
****************************************************************************************************
File Name        : patch_for_jdapistd.c
Version          : Initial Draft
Author           :
Created          : 2017/10/01
Description      :
Function List    :

History          :
Date                     Author           Modification
2017/10/01               sdk              Created file
***************************************************************************************************/


/****************************  add include here     ***********************************************/
#include "jpeg_sdec_outinfo.c"
#include "jpeg_sdec_decode.c"

/***************************** Macro Definition     ***********************************************/

/***************************** Structure Definition ***********************************************/


/********************** Global Variable declaration ***********************************************/


/********************** API forward declarations    ***********************************************/

/**********************       API realization       ***********************************************/
#define adp_for_save_cur_input_data         JPEG_SDEC_SaveCurInputData(cinfo);

#define adp_for_set_output_info             JPEG_SDEC_SetOutPutInfo(cinfo);

#define adp_for_check_support_crop          JPEG_DEC_IfSupport((HI_ULONG)cinfo->client_data);\
                                            if (HI_FALSE == JPEG_DEC_SupportCrop((HI_ULONG)cinfo->client_data))\
                                            {\
                                                ERREXIT(cinfo, JERR_NO_IMAGE);\
                                            }

#define adp_for_set_cropxw                  HI_BOOL SupportHdec = HI_FALSE;\
                                            JPEG_DEC_SetCropXW((HI_ULONG)cinfo->client_data, *xoffset, *width);\
                                            JPEG_DEC_GetSupportHdecState((HI_ULONG)cinfo->client_data, &SupportHdec);\
                                            if (HI_TRUE == SupportHdec)\
                                            {\
                                               return;\
                                            }

#define adp_for_hard_decode                 HI_BOOL HdecSuccess = HI_FALSE;\
                                            row_ctr = (NULL != scanlines) ? \
                                                      JPEG_DEC_Scanlines(cinfo,(HI_CHAR*)scanlines[0],1) :\
                                                      JPEG_DEC_Scanlines(cinfo,NULL,1);\
                                            JPEG_DEC_GetHdecSuccess((HI_ULONG)cinfo->client_data,&HdecSuccess);\
                                            if (HI_TRUE == HdecSuccess)\
                                            {\
                                               cinfo->global_state = DSTATE_STOPPING;\
                                               cinfo->inputctl->eoi_reached  = HI_TRUE;\
                                               cinfo->output_scanline = cinfo->output_scanline + row_ctr;\
                                               return row_ctr;\
                                            }\
                                            JPEG_DEC_SetSupportHdecState((HI_ULONG)cinfo->client_data,HI_FALSE);


#define adp_for_set_skip_info               HI_S32 Ret = HI_SUCCESS;\
                                            Ret = JPEG_DEC_SetCropYH((HI_ULONG)cinfo->client_data,num_lines,cinfo->output_height - num_lines);\
                                            if (HI_SUCCESS != Ret)\
                                            {\
                                                ERREXIT(cinfo, JERR_NO_IMAGE);\
                                            }\
                                            Ret = JPEG_DEC_SetSkipLines((HI_ULONG)cinfo->client_data, num_lines);\
                                            if (HI_SUCCESS != Ret)\
                                            {\
                                                ERREXIT(cinfo, JERR_NO_IMAGE);\
                                            }

#define adp_for_enable_discard_scanlines    {\
                                              JPEG_DEC_SetDisScanMark((HI_ULONG)cinfo->client_data,HI_TRUE);

#define adp_for_disable_discard_scanlines     JPEG_DEC_SetDisScanMark((HI_ULONG)cinfo->client_data,HI_FALSE);\
                                            }


#define adp_for_begin_check_hdec_support    HI_BOOL SupportHdec = HI_FALSE;\
                                            JPEG_DEC_IfSupport((HI_ULONG)cinfo->client_data);\
                                            JPEG_DEC_GetSupportHdecState((HI_ULONG)cinfo->client_data,&SupportHdec);\
                                            if (HI_TRUE != SupportHdec)\
                                            {

#define adp_for_end_check_hdec_support      }

#define adp_for_check_hdec_support          JPEG_DEC_GetSupportHdecState((HI_ULONG)cinfo->client_data,&SupportHdec);\
                                            if (HI_TRUE == SupportHdec)\
                                            {\
                                                 cinfo->output_scanline += num_lines;\
                                                 return num_lines;\
                                            }
