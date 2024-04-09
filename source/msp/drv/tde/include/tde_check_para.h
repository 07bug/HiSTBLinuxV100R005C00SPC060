/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name        : tde_check_para.h
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      :
Function List    :

History          :
Date                     Author           Modification
2018/01/01               sdk              Created file
************************************************************************************************/
#ifndef __TDE_CHECK_PARA_H__
#define __TDE_CHECK_PARA_H__

/*********************************add include here**********************************************/
#include "hi_type.h"

/***********************************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */

/***************************** Macro Definition ********************************************/
#define TDE_CHECK_ARRAY_OVER_RETURN_VALUE(CurIndex, MaxIndex, Ret) \
                            do{\
                                if (CurIndex >= MaxIndex)\
                                {\
                                    return Ret;\
                                }\
                            }while(0)


#define TDE_CHECK_ARRAY_OVER_RETURN_NOVALUE(CurIndex, MaxIndex) \
                            do{\
                                if (CurIndex >= MaxIndex)\
                                {\
                                    return;\
                                }\
                            }while(0)

#define TDE_CHECK_NULLPOINTER_RETURN_NOVALUE(Pointer) \
                            do{\
                                if (NULL == Pointer)\
                                {\
                                    return;\
                                }\
                            }while(0)

#define TDE_CHECK_NULLPOINTER_RETURN_VALUE(Pointer, Ret) \
                            do{\
                                if (NULL == Pointer)\
                                {\
                                    return Ret;\
                                }\
                            }while(0)


#define TDE_CHECK_UNEQUAL_RETURN_NOVALUE(para1, para2) \
                            do{\
                                if (para1 != para2)\
                                {\
                                    return;\
                                }\
                            }while(0)


#define TDE_CHECK_UNEQUAL_RETURN_VALUE(para1, para2, Ret) \
                            do{\
                                if (para1 != para2)\
                                {\
                                    return Ret;\
                                }\
                            }while(0)

#define TDE_CHECK_EQUAL_RETURN_VALUE(para1, para2, Ret) \
                            do{\
                                if (para1 == para2)\
                                {\
                                    return Ret;\
                                }\
                            }while(0)

#define TDE_CHECK_EQUAL_RETURN_NOVALUE(para1, para2) \
                            do{\
                                if (para1 == para2)\
                                {\
                                    return;\
                                }\
                            }while(0)

/*************************** Enum Definition ***********************************************/

/*************************** Structure Definition ******************************************/

/******************************* API declaration *******************************************/

/******************************* API release ***********************************************/


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif/*__TDE_CHECK_PARA_H__ */
