/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name       : drv_hifb_paracheck.h
Version         : Initial Draft
Author          :
Created         : 2018/01/01
Description     : check framebuffer para that before be used
                  CNcomment: �ڲ���ʹ��֮ǰ�������Ϸ���CNend\n
Function List   :

History         :
Date                         Author                     Modification
2018/01/01                    sdk                       Created file
***************************************************************************************************/
#ifndef __DRV_HIFB_PARACHECK_H__
#define __DRV_HIFB_PARACHECK_H__

/*********************************add include here*************************************************/
#include "hi_type.h"

/**************************************************************************************************/
#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */

/***************************** Macro Definition ***************************************************/
#define HIFB_CHECK_ARRAY_OVER_RETURN(CurIndex, MaxIndex, Ret) \
                            do{\
                                if ((CurIndex) >= (MaxIndex))\
                                {\
                                    HIFB_ERROR("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                                    return Ret;\
                                }\
                            }while(0)

#define HIFB_CHECK_ARRAY_OVER_UNRETURN(CurIndex, MaxIndex) \
                            do{\
                                if ((CurIndex) >= (MaxIndex))\
                                {\
                                    HIFB_ERROR("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                                    return;\
                                }\
                            }while(0)

#define HIFB_CHECK_LEFT_LARGER_RIGHT_RETURN(left_value, right_value, Ret) \
                            do{\
                                if ((left_value) > (right_value))\
                                {\
                                    HIFB_ERROR("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                                    return Ret;\
                                }\
                            }while(0)

#define HIFB_CHECK_LEFT_LARGER_RIGHT_UNRETURN(left_value, right_value) \
                            do{\
                                if ((left_value) > (right_value))\
                                {\
                                    HIFB_ERROR("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                                    return;\
                                }\
                            }while(0)

#define HIFB_CHECK_NULLPOINTER_UNRETURN(Pointer) \
                            do{\
                                if (NULL == (Pointer))\
                                {\
                                    HIFB_ERROR("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                                    return;\
                                }\
                            }while(0)

#define HIFB_CHECK_NULLPOINTER_RETURN(Pointer, Ret) \
                            do{\
                                if (NULL == (Pointer))\
                                {\
                                    HIFB_ERROR("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                                    return Ret;\
                                }\
                            }while(0)

#define HIFB_CHECK_UNEQUAL_RETURN(para1, para2, Ret) \
                            do{\
                                if ((para1) != (para2))\
                                {\
                                    HIFB_ERROR("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                                    return Ret;\
                                }\
                            }while(0)

#define HIFB_CHECK_UNEQUAL_UNRETURN(para1, para2) \
                            do{\
                                if ((para1) != (para2))\
                                {\
                                    HIFB_ERROR("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                                    return;\
                                }\
                            }while(0)

#define HIFB_CHECK_EQUAL_RETURN(para1, para2, Ret) \
                            do{\
                                if ((para1) == (para2))\
                                {\
                                    HIFB_ERROR("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                                    return Ret;\
                                }\
                            }while(0)

#define HIFB_CHECK_EQUAL_UNRETURN(para1, para2) \
                            do{\
                                if ((para1) == (para2))\
                                {\
                                    HIFB_ERROR("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                                    return;\
                                }\
                            }while(0)

#define HIFB_CHECK_LAYERID_SUPPORT_RETURN(LayerId,Ret) do{\
                            if (LayerId >= OPTM_MAX_LOGIC_HIFB_LAYER){\
                                  HIFB_ERROR("this %d layer id is not support\n",LayerId);\
                                  return Ret;}\
                            }while(0)


#define HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(LayerId) do{\
                            if (LayerId >= OPTM_MAX_LOGIC_HIFB_LAYER){\
                                  HIFB_ERROR("this %d layer id is not support\n",LayerId);\
                                  return;}\
                            }while(0)


#define HIFB_CHECK_GPID_SUPPORT_UNRETURN(GpId) do{\
                            if (GpId >= 2){\
                                  HIFB_ERROR("this %d gp id is not support\n",GpId);\
                                  return;}\
                            }while(0)

#define HIFB_CHECK_GPID_SUPPORT_RETURN(GpId,Ret) do{\
                            if (GpId >= 2){\
                                  HIFB_ERROR("this %d gp id is not support\n",GpId);\
                                  return Ret;}\
                            }while(0)

/*************************** Structure Definition *************************************************/

/********************** Global Variable declaration ***********************************************/

/******************************* API declaration **************************************************/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif/*__DRV_HIFB_PARACHECK_H__ */
