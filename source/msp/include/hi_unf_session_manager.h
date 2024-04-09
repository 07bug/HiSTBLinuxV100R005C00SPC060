/******************************************************************************

Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_unf_session_manager.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2017-08-11
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __HI_UNF_SESSION_MANAGER_H__
#define __HI_UNF_SESSION_MANAGER_H__

#include "hi_type.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* End of #ifdef __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      HI_UNF_SESSION_MANAGER */
/** @{ */  /** <!-- [HI_UNF_SESSION_MANAGER] */


/** the type of session manager attribute */
typedef struct
{
    HI_U32 u32SessionID;
} HI_UNF_SM_ATTR_S;

/** the type of session manager modid */
typedef enum
{
    HI_UNF_SM_MODULE_KEYLADDER = 0,
    HI_UNF_SM_MODULE_DESCRAMBLER,
    HI_UNF_SM_MODULE_CIPHER,
    HI_UNF_SM_MODULE_PLCIPHER,
    HI_UNF_SM_MODULE_DEMUX,
    HI_UNF_SM_MODULE_VDEC,
    HI_UNF_SM_MODULE_AVPLAY,
    HI_UNF_SM_MODULE_PVR,
    HI_UNF_SM_MOODULE_BUTT
} HI_UNF_SM_MODULE_E;

typedef enum
{
    HI_UNF_SM_CIPHER_TYPE_ENCRYPT,
    HI_UNF_SM_CIPHER_TYPE_DECRYPT,
    HI_UNF_SM_CIPHER_TYPE_BUTT
} HI_UNF_SM_CIPHER_TYPE_E;

typedef struct
{
    union
    {
        HI_UNF_SM_CIPHER_TYPE_E enCipherType;
        HI_U32 u32DemuxID;
        HI_U32 u32Reserve;
    } unModAttr;
    HI_HANDLE hHandle;
} HI_UNF_SM_MODULE_S;


/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      HI_UNF_SESSION_MANAGER */
/** @{ */  /** <!-- [HI_UNF_SESSION_MANAGER] */

/**
\brief Init the session manager device
\param  None
\retval HI_SUCCESS  Success
\retval HI_FAILURE  Failure
*/
HI_S32 HI_UNF_SM_Init(HI_VOID);


/**
\brief Deinit the session manager device
\param  None
\retval HI_SUCCESS  Success
\retval HI_FAILURE  Failure
*/
HI_S32 HI_UNF_SM_DeInit(HI_VOID);

/**
\brief Create a session manager instance.
\attention \n
\param[out] phSM       Handle of session manager.
\param[in] pstSMAttr   Pointer to the attributes of session manager.
\retval HI_SUCCESS     Success
\retval HI_FAILURE     Failure
\see \n
N/A
*/
HI_S32 HI_UNF_SM_Create(HI_HANDLE *phSM, HI_UNF_SM_ATTR_S *pstSMAttr);

/**
\brief add handle need to be managed by session manager.
\attention \n
\param[in] hSM         Handle of session manager.
\param[in] enModID     Handle module.
\param[in] pstModule   Resource need to manager.
\retval HI_SUCCESS     Success
\retval HI_FAILURE     Failure
\see \n
N/A
*/
HI_S32 HI_UNF_SM_AddResource(HI_HANDLE hSM, HI_UNF_SM_MODULE_E enModID, HI_UNF_SM_MODULE_S *pstModule);

/**
\brief del handle need to be remove by session manager.
\attention \n
\param[in] hSM         Handle of session manager.
\param[in] enModID     Handle module.
\param[in] pstModule   Resource need to manager.
\retval HI_SUCCESS     Success
\retval HI_FAILURE     Failure
\see \n
N/A
*/
HI_S32 HI_UNF_SM_DelResource(HI_HANDLE hSM, HI_UNF_SM_MODULE_E enModID, HI_UNF_SM_MODULE_S *pstModule);

/**
\brief destroy session manager.
\attention \n
\param[in] hSM         Handle of session manager.
\retval HI_SUCCESS     Success
\retval HI_FAILURE     Failure
\see \n
N/A
*/
HI_S32 HI_UNF_SM_Destroy(HI_HANDLE hSM);

/**
\brief get session manager handle by service id.
\attention \n
\param[in] u32SessionID     source handle module.
\param[out] pSM             handle to search.
\retval HI_SUCCESS     Success
\retval HI_FAILURE     Failure
\see \n
N/A
*/
HI_S32 HI_UNF_SM_GetSMHandleBySID(HI_U32 u32SessionID, HI_HANDLE *pSM);


/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef HI_UNF_SESSION_MANAGER*/
