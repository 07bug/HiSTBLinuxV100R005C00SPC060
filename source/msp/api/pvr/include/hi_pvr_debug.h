/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_pvr_debug.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2008/04/25
  Description   : hi_pvr_debug.h header file
  History       :
  1.Date        : 2008/04/25
    Author      : sdk
    Modification: Created file

******************************************************************************/

#ifndef __HI_PVR_DEBUG_H__
#define __HI_PVR_DEBUG_H__

#include <stdlib.h>

#include "hi_error_mpi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* End of #ifdef __cplusplus */

/* assert NULL pointer                                                      */
#define PVR_CHECK_POINTER(PTR)\
    do\
    {\
        if ( HI_NULL_PTR == PTR )\
        {\
            HI_ERR_PVR("Parameter is NULL.\n");\
            return HI_ERR_PVR_NUL_PTR;\
        }\
    } while (0)

/*the length of key shall be [16 - 128]*/
#define PVR_CHECK_CIPHER_CFG(pCipherCfg)\
    do {\
            if ((pCipherCfg)->bDoCipher)\
            {\
                if ((pCipherCfg)->enType >= HI_UNF_CIPHER_ALG_BUTT\
                    || ((pCipherCfg)->u32KeyLen < (PVR_CIPHER_AES_KEY_LENGTH_BIT/8))\
                    || ((pCipherCfg)->u32KeyLen > PVR_MAX_CIPHER_KEY_LEN))\
                {\
                    HI_ERR_PVR("Invalid cipher config: type(%d) error or key len(%u) invalid!\n", (pCipherCfg)->enType, (pCipherCfg)->u32KeyLen);\
                    return HI_ERR_PVR_INVALID_PARA;\
                }\
                switch((pCipherCfg)->enType)\
                {\
                    case HI_UNF_CIPHER_ALG_DES:\
                    case HI_UNF_CIPHER_ALG_3DES:\
                    case HI_UNF_CIPHER_ALG_AES:\
                    {  break; }\
                    default:\
                    {\
                        HI_ERR_PVR("PVR not support the cipher algorithm(%d),only support AES,DES,3DES!\n", (pCipherCfg)->enType);\
                        return HI_ERR_PVR_NOT_SUPPORT;\
                    }\
                }\
            }\
       }while(0)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */


#endif /* End of #ifndef __HI_PVR_DEBUG_H__ */
