/************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*************************************************************************************************
File Name         : hi_png_checkpara.h
Version           : Initial Draft
Author            :
Created           : 2018/01/01
Description       : �������
Function List     :


History           :
Date                          Author                   Modification
2018/01/01                    sdk                      Created file
*************************************************************************************************/

#ifndef __HI_PNG_CHECKPARA_H__
#define __HI_PNG_CHECKPARA_H__

/*********************************add include here***********************************************/

/************************************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */


    /***************************** Macro Definition *********************************************/
    #define CHECK_PNG_EQUAL_UNRETURN(para1, para2) \
                            do{\
                                if (para1 == para2)\
                                {\
                                    return;\
                                }\
                            }while(0)

    #define CHECK_PNG_UNEQUAL_UNRETURN(para1, para2) \
                            do{\
                                if (para1 != para2)\
                                {\
                                    return;\
                                }\
                            }while(0)

    #define CHECK_PNG_EQUAL_RETURN(para1, para2, Ret) \
                            do{\
                                if (para1 == para2)\
                                {\
                                    return Ret;\
                                }\
                            }while(0)

    #define CHECK_PNG_UNEQUAL_RETURN(para1, para2, Ret) \
                            do{\
                                if (para1 != para2)\
                                {\
                                    return Ret;\
                                }\
                            }while(0)


    #define CHECK_PNG_GREATER_RETURN(para1, para2, Ret) \
                            do{\
                                if (para1 > para2)\
                                {\
                                    return Ret;\
                                }\
                            }while(0)

    #define CHECK_PNG_LESS_RETURN(para1, para2, Ret) \
                            do{\
                                if (para1 < para2)\
                                {\
                                    return Ret;\
                                }\
                            }while(0)

    #define CHECK_PNG_LESS_UNRETURN(para1, para2) \
                            do{\
                                if (para1 < para2)\
                                {\
                                    return;\
                                }\
                            }while(0)

    /*************************** Structure Definition *******************************************/

    /***************************  The enum of Jpeg image format  ********************************/


    /********************** Global Variable declaration *****************************************/


    /******************************* API declaration ********************************************/


    #ifdef __cplusplus
        #if __cplusplus

}
        #endif
   #endif /* __cplusplus */
#endif /* __HI_PNG_CHECKPARA_H__*/
