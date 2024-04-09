/************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*************************************************************************************************
File Name        : hi_jpeg_checkpara.h
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      : ²ÎÊý¼ì²â
Function List    :


History          :
Date                         Author                   Modification
2018/01/01                   sdk                      Created file
*************************************************************************************************/

#ifndef __HI_JPEG_CHECKPARA_H__
#define __HI_JPEG_CHECKPARA_H__

/*********************************add include here***********************************************/

/************************************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */


    /***************************** Macro Definition *********************************************/
    #define CHECK_JPEG_EQUAL_UNRETURN(para1, para2) \
                                if (para1 == para2)\
                                {\
                                    HI_PRINT("[module-gfx] : %s[%d] %d == %d\n",   __FUNCTION__,__LINE__,para1,para2);\
                                    return;\
                                }

    #define CHECK_JPEG_UNEQUAL_UNRETURN(para1, para2) \
                                if (para1 != para2)\
                                {\
                                    HI_PRINT("[module-gfx] : %s[%d] %d != %d\n",   __FUNCTION__,__LINE__,para1,para2);\
                                    return;\
                                }

    #define CHECK_JPEG_EQUAL_RETURN(para1, para2, Ret) \
                                if (para1 == para2)\
                                {\
                                    HI_PRINT("[module-gfx] : %s[%d] %d == %d\n",   __FUNCTION__,__LINE__,para1,para2);\
                                    return Ret;\
                                }

    #define CHECK_JPEG_UNEQUAL_RETURN(para1, para2, Ret) \
                                if (para1 != para2)\
                                {\
                                    HI_PRINT("[module-gfx] : %s[%d] %d != %d\n",   __FUNCTION__,__LINE__,para1,para2);\
                                    return Ret;\
                                }


    #define CHECK_JPEG_GREATER_RETURN(para1, para2, Ret) \
                                if (para1 > para2)\
                                {\
                                    HI_PRINT("[module-gfx] : %s[%d] %d > %d\n",   __FUNCTION__,__LINE__,para1,para2);\
                                    return Ret;\
                                }

    #define CHECK_JPEG_LESS_RETURN(para1, para2, Ret) \
                                if (para1 < para2)\
                                {\
                                    HI_PRINT("[module-gfx] : %s[%d] %d < %d\n",   __FUNCTION__,__LINE__,para1,para2);\
                                    return Ret;\
                                }

    #define CHECK_JPEG_LESS_UNRETURN(para1, para2) \
                                if (para1 < para2)\
                                {\
                                    HI_PRINT("[module-gfx] : %s[%d] %d <= %d\n",   __FUNCTION__,__LINE__,para1,para2);\
                                    return;\
                                }

     #define CHECK_JPEG_NULLPOINTER_RETURN_VALUE(para, Ret) \
                                if (NULL == para)\
                                {\
                                    HI_PRINT("[module-gfx] : %s[%d] null pointer\n",   __FUNCTION__,__LINE__);\
                                    return Ret;\
                                }

    #define CHECK_JPEG_NULLPOINTER_RETURN_NOVALUE(para) \
                                if (NULL == para)\
                                {\
                                    HI_PRINT("[module-gfx] : %s[%d] null pointer\n",   __FUNCTION__,__LINE__);\
                                    return;\
                                }
    /*************************** Structure Definition *******************************************/

    /***************************  The enum of Jpeg image format  ********************************/


    /********************** Global Variable declaration ******************************************/


    /******************************* API declaration ********************************************/


    #ifdef __cplusplus
        #if __cplusplus

}
        #endif
   #endif /* __cplusplus */
#endif /* __HI_JPEG_CHECKPARA_H__*/
