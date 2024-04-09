/************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*************************************************************************************************
File Name	     : hi_png_errcode.h
Version		     : Initial Draft
Author		     : sdk
Created		     : 2018/01/01
Description	     : PNG errcode
Function List	 :

History       	 :
Date                            Author                 Modification
2018/01/01                       sdk                  Created file
*************************************************************************************************/

#ifndef __HI_PNG_ERRCODE_H__
#define __HI_PNG_ERRCODE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif	/* __cplusplus__ */
#endif	/* __cplusplus__ */

/* PNG error code*/
typedef enum tag_HI_ERR_PNG_E
{
    HI_ERR_PNG_DEV_NOEXIST = 0x80000001,            /* device not exist  */
    HI_ERR_PNG_DEV_NOOPEN,                          /* device not open   */
    HI_ERR_PNG_NULLPTR,                             /* NULL PTR          */
    HI_ERR_PNG_NOHANDLE,                            /* no handle         */
    HI_ERR_PNG_INVALID_HANDLE,                      /* invalid handle    */
    HI_ERR_PNG_NOMEM,                               /* no mem            */
    HI_ERR_PNG_NOSTREAM,                            /* no stream         */
    HI_ERR_PNG_INVALID_PARAM,                       /* invalid param:
                                                       1.address or stride is 0, or no-16 align
                                                       2.pixel format error when decoding
                                                       3.stream buffer error or out of length         */
    HI_ERR_PNG_DEV_BUSY,                            /* devide is busy,for example, alloc stream buffer , setting stream buffer len or release stream buffer after  decoder startting*/
    HI_PNG_ERR_INTERNAL,                            /* internal error ,for example TDE or PNG error    */
    HI_ERR_PNG_SYS,                                 /* systme error: for example MMZ map error,delete memory error,block is waken up by  interrupt*/
    HI_ERR_PNG_TIMEOUT,
    HI_ERR_PNG_INTERRUPT,
    HI_ERR_PNG_BUTT
}HI_ERR_PNG_E;

#ifdef __cplusplus
#if __cplusplus
}
#endif	/* __cplusplus__ */
#endif	/* __cplusplus__ */

#endif	/* __HI_PNG_ERRCODE_H__ */
