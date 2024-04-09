/******************************************************************************

Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : mpi_session_manager.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2017-08-11
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "session_manager_debug.h"
#include "hi_mpi_session_manager.h"
#include "hi_unf_session_manager.h"
#include "hi_mpi_avplay.h"
#include "hi_mpi_pvr.h"
#include "drv_sm_ioctl.h"
#include "hi_drv_struct.h"
#include <pthread.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "string.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define SM_MIN(a, b)  ((a) > (b) ? (b) : (a))

static HI_S32 s_s32SMFd = -1;
static HI_S32 s_s32SMOpenCounter = 0;
static pthread_mutex_t   s_mSM = PTHREAD_MUTEX_INITIALIZER;

#define HI_SM_LOCK()    (HI_VOID)pthread_mutex_lock(&s_mSM);
#define HI_SM_UNLOCK()  (HI_VOID)pthread_mutex_unlock(&s_mSM);

HI_S32 HI_MPI_SM_Init(HI_VOID)
{
    SM_FUNC_ENTER();
    HI_SM_LOCK();

    if (-1 != s_s32SMFd)
    {
        s_s32SMOpenCounter++;
        HI_SM_UNLOCK();
        SM_FUNC_EXIT();
        return HI_SUCCESS;
    }

    s_s32SMFd = open("/dev/" UMAP_DEVNAME_SM, O_RDWR, 0);
    if (s_s32SMFd < 0)
    {
        SM_PrintErrorFunc(open, s_s32SMFd);
        HI_SM_UNLOCK();
        return HI_FAILURE;
    }

    s_s32SMOpenCounter++;

    HI_SM_UNLOCK();
    SM_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_MPI_SM_DeInit(HI_VOID)
{
    SM_FUNC_ENTER();

    HI_SM_LOCK();

    if (s_s32SMFd < 0)
    {
        HI_SM_UNLOCK();
        SM_FUNC_EXIT();
        return HI_SUCCESS;
    }

    s_s32SMOpenCounter--;
    if ( 0 == s_s32SMOpenCounter)
    {
        close(s_s32SMFd);
        s_s32SMFd = -1;
    }

    HI_SM_UNLOCK();
    SM_FUNC_EXIT();
    return HI_SUCCESS;

}

HI_S32 HI_MPI_SM_Create(HI_HANDLE *phSM, HI_UNF_SM_ATTR_S *pstSMAttr)
{
    HI_S32 ret = HI_FAILURE;
    SM_CTL_CREATE_S stCreate;

    SM_FUNC_ENTER();

    SM_CHECK_POINTER(phSM);
    SM_CHECK_POINTER(pstSMAttr);

    memset(&stCreate, 0x00, sizeof (SM_CTL_CREATE_S));
    stCreate.hCreate               = HI_INVALID_HANDLE;
    stCreate.stSMAttr.u32SessionID = pstSMAttr->u32SessionID;

    ret = ioctl(s_s32SMFd, CMD_SM_CREATE, &stCreate);
    if (HI_SUCCESS != ret)
    {
        SM_PrintErrorFunc(ioctl, ret);
        return ret;
    }

    *phSM = stCreate.hCreate;

    SM_FUNC_EXIT();
    return HI_SUCCESS;
}

static HI_S32 MPI_SM_AddResource(HI_HANDLE hSM, HI_UNF_SM_MODULE_E enModID, HI_UNF_SM_MODULE_S *pstMod)
{
    HI_S32 ret = HI_FAILURE;
    SM_CTL_ADD_S stAdd;

    memset(&stAdd, 0x00, sizeof (SM_CTL_ADD_S));
    stAdd.hSM        = hSM;
    stAdd.enModule   = enModID;
    memcpy(&stAdd.stModule, pstMod, sizeof (HI_UNF_SM_MODULE_S));

    ret = ioctl(s_s32SMFd, CMD_SM_ADD_RESOURCE, &stAdd);
    if (HI_SUCCESS != ret)
    {
        SM_PrintErrorFunc(ioctl, ret);
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_SM_AddResource(HI_HANDLE hSM, HI_UNF_SM_MODULE_E enModID, HI_UNF_SM_MODULE_S *pstMod)
{
    HI_S32 ret = HI_FAILURE;
    HI_UNF_SM_MODULE_S stModule;
    HI_HANDLE handle = HI_INVALID_HANDLE;
    HI_U32 u32DemuxID   = 0;
    HI_U32 u32Reserve   = 0;

    SM_FUNC_ENTER();

    SM_CHECK_SMHANDLE(hSM);
    SM_CHECK_MODULEID(enModID);
    SM_CHECK_POINTER(pstMod);

    memset(&stModule, 0x0, sizeof (stModule));

    if (HI_UNF_SM_MODULE_PVR == enModID)
    {
        ret = HI_PVR_RecGetHandle(pstMod->hHandle, HI_ID_DEMUX, &handle, &u32DemuxID);
        if (HI_SUCCESS != ret)
        {
            SM_PrintErrorFunc(HI_PVR_RecGetHandle, ret);
            return ret;
        }

        stModule.hHandle = handle;
        stModule.unModAttr.u32DemuxID = u32DemuxID;

        ret = MPI_SM_AddResource(hSM, HI_UNF_SM_MODULE_DEMUX, &stModule);
        if (HI_SUCCESS != ret)
        {
            SM_PrintErrorFunc(MPI_SM_AddResource, ret);
            return ret;
        }
    }
    else if (HI_UNF_SM_MODULE_AVPLAY == enModID)
    {
        ret = HI_MPI_AVPLAY_GetHandle(pstMod->hHandle, HI_ID_DEMUX, &handle, &u32DemuxID);
        if (HI_ERR_AVPLAY_INVALID_OPT == ret)
        {
            SM_PrintInfoCode(HI_ERR_AVPLAY_INVALID_OPT);
        }
        else if (HI_SUCCESS == ret)
        {
            stModule.hHandle = handle;
            stModule.unModAttr.u32DemuxID = u32DemuxID;

            ret = MPI_SM_AddResource(hSM, HI_UNF_SM_MODULE_DEMUX, &stModule);
            if (HI_SUCCESS != ret)
            {
                SM_PrintErrorFunc(MPI_SM_AddResource, ret);
                return ret;
            }
        }
        else
        {
            SM_PrintErrorFunc(HI_MPI_AVPLAY_GetHandle, ret);
            return ret;
        }

        handle = HI_INVALID_HANDLE;
        ret = HI_MPI_AVPLAY_GetHandle(pstMod->hHandle, HI_ID_VDEC, &handle, &u32Reserve);
        if (HI_SUCCESS != ret)
        {
            SM_PrintErrorFunc(HI_MPI_AVPLAY_GetHandle, ret);
            return ret;
        }

        memset(&stModule, 0x0, sizeof (stModule));

        stModule.hHandle = handle;

        ret = MPI_SM_AddResource(hSM, HI_UNF_SM_MODULE_VDEC, &stModule);
        if (HI_SUCCESS != ret)
        {
            SM_PrintErrorFunc(MPI_SM_AddResource, ret);
            return ret;
        }
    }
    else
    {

        ret = MPI_SM_AddResource(hSM, enModID, pstMod);
        if (HI_SUCCESS != ret)
        {
            SM_PrintErrorFunc(MPI_SM_AddResource, ret);
            return ret;
        }
    }

    SM_FUNC_EXIT();
    return HI_SUCCESS;
}

static HI_S32 MPI_SM_DelResource(HI_HANDLE hSM, HI_UNF_SM_MODULE_E enModID, HI_UNF_SM_MODULE_S *pstMod)
{
    HI_S32 ret = HI_FAILURE;
    SM_CTL_DEL_S stDel;

    memset(&stDel, 0x00, sizeof (SM_CTL_DEL_S));
    stDel.hSM        = hSM;
    stDel.enModule   = enModID;
    memcpy(&stDel.stModule, pstMod, sizeof (HI_UNF_SM_MODULE_S));

    ret = ioctl(s_s32SMFd, CMD_SM_DEL_RESOURCE, &stDel);
    if (HI_SUCCESS != ret)
    {
        SM_PrintErrorFunc(ioctl, ret);
        return ret;
    }

    return HI_SUCCESS;
}


HI_S32 HI_MPI_SM_DelResource(HI_HANDLE hSM, HI_UNF_SM_MODULE_E enModID, HI_UNF_SM_MODULE_S *pstMod)
{
    HI_S32 ret = HI_FAILURE;
    HI_HANDLE handle = HI_INVALID_HANDLE;
    HI_UNF_SM_MODULE_S stModule;
    HI_U32 u32DemuxID  = 0;
    HI_U32 u32Reserve  = 0;

    SM_FUNC_ENTER();

    SM_CHECK_SMHANDLE(hSM);
    SM_CHECK_MODULEID(enModID);
    SM_CHECK_POINTER(pstMod);

    memset(&stModule, 0x0, sizeof (stModule));

    if (HI_UNF_SM_MODULE_PVR == enModID)
    {
        ret = HI_PVR_RecGetHandle(pstMod->hHandle, HI_ID_DEMUX, &handle, &u32DemuxID);
        if (HI_SUCCESS != ret)
        {
            SM_PrintErrorFunc(HI_PVR_RecGetHandle, ret);
            return ret;
        }

        stModule.hHandle = handle;
        stModule.unModAttr.u32DemuxID = u32DemuxID;

        ret = MPI_SM_DelResource(hSM, HI_UNF_SM_MODULE_DEMUX, &stModule);
        if (HI_SUCCESS != ret)
        {
            SM_PrintErrorFunc(MPI_SM_DelResource, ret);
            return ret;
        }
    }
    else if (HI_UNF_SM_MODULE_AVPLAY == enModID)
    {
        ret = HI_MPI_AVPLAY_GetHandle(pstMod->hHandle, HI_ID_DEMUX, &handle, &u32DemuxID);
        if (HI_ERR_AVPLAY_INVALID_OPT == ret)
        {
            SM_PrintInfoCode(HI_ERR_AVPLAY_INVALID_OPT);
        }
        else if (HI_SUCCESS == ret)
        {
            stModule.hHandle = handle;
            stModule.unModAttr.u32DemuxID = u32DemuxID;

            ret = MPI_SM_DelResource(hSM, HI_UNF_SM_MODULE_DEMUX, &stModule);
            if (HI_SUCCESS != ret)
            {
                SM_PrintErrorFunc(MPI_SM_DelResource, ret);
                return ret;
            }
        }
        else
        {
            SM_PrintErrorFunc(HI_MPI_AVPLAY_GetHandle, ret);
            return ret;
        }


        handle = HI_INVALID_HANDLE;
        ret = HI_MPI_AVPLAY_GetHandle(pstMod->hHandle, HI_ID_VDEC, &handle, &u32Reserve);
        if (HI_SUCCESS != ret)
        {
            SM_PrintErrorFunc(HI_MPI_AVPLAY_GetHandle, ret);
            return ret;
        }

        memset(&stModule, 0x0, sizeof (stModule));

        stModule.hHandle = handle;

        ret = MPI_SM_DelResource(hSM, HI_UNF_SM_MODULE_VDEC, &stModule);
        if (HI_SUCCESS != ret)
        {
            SM_PrintErrorFunc(MPI_SM_DelResource, ret);
            return ret;
        }
    }
    else
    {
        ret = MPI_SM_DelResource(hSM, enModID, pstMod);
        if (HI_SUCCESS != ret)
        {
            SM_PrintErrorFunc(MPI_SM_DelResource, ret);
            return ret;
        }
    }

    SM_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_MPI_SM_Destroy(HI_HANDLE hSM)
{
    HI_S32 ret = HI_FAILURE;
    SM_CTL_DESTROY_S stDestroy;

    SM_FUNC_ENTER();

    memset(&stDestroy, 0x00, sizeof (SM_CTL_DESTROY_S));
    stDestroy.hSM = hSM;

    SM_CHECK_SMHANDLE(stDestroy.hSM);

    ret = ioctl(s_s32SMFd, CMD_SM_DESTORY, &stDestroy);
    if (HI_SUCCESS != ret)
    {
        SM_PrintErrorFunc(ioctl, ret);
        return ret;
    }

    SM_FUNC_EXIT();
    return HI_SUCCESS;
}


HI_S32 HI_MPI_SM_SetIntent(HI_HANDLE hSM, HI_UNF_SM_INTENT_E enIntent)
{
    HI_S32 ret = HI_FAILURE;
    SM_CTL_INTENT_S stIntent;

    SM_FUNC_ENTER();

    memset(&stIntent, 0x00, sizeof (SM_CTL_INTENT_S));
    stIntent.hSM      = hSM;
    stIntent.enIntent = enIntent;

    SM_CHECK_SMHANDLE(stIntent.hSM);
    SM_CHECK_INTENT(stIntent.enIntent);

    ret = ioctl(s_s32SMFd, CMD_SM_SET_INTENT, &stIntent);
    if (HI_SUCCESS != ret)
    {
        SM_PrintErrorFunc(ioctl, ret);
        return ret;
    }

    SM_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_MPI_SM_GetResource(HI_UNF_SM_MODULE_E enSrcModID, HI_HANDLE hSrcModHandle, HI_UNF_SM_MODULE_E enModID, HI_UNF_SM_MODULE_S *pstMod, HI_U32 *pu32ModNum)
{
    HI_S32 ret = HI_FAILURE;
    HI_S32 i = 0;
    HI_S32 loop = 0;
    SM_CTL_MODULE_S stModule;

    SM_FUNC_ENTER();

    SM_CHECK_POINTER(pstMod);
    SM_CHECK_POINTER(pu32ModNum);
    SM_CHECK_RESOURCE_NUM(*pu32ModNum);

    memset(&stModule, 0x00, sizeof (SM_CTL_MODULE_S));
    stModule.enSrcModule = enSrcModID;
    stModule.hSrcHandle  = hSrcModHandle;
    stModule.enModule    = enModID;

    SM_CHECK_MODULEID(stModule.enSrcModule);
    SM_CHECK_MODULEID(stModule.enModule);

    ret = ioctl(s_s32SMFd, CMD_SM_GET_RESOURCE, &stModule);
    if (HI_SUCCESS != ret)
    {
        SM_PrintErrorFunc(ioctl, ret);
        return ret;
    }

    loop = stModule.u32ModuleNum < *pu32ModNum ? stModule.u32ModuleNum : *pu32ModNum;

    for (i = 0; i < loop; i++)
    {
        memcpy(pstMod + i, &stModule.stModule[i], sizeof (HI_UNF_SM_MODULE_S));
    }

    *pu32ModNum = loop;

    SM_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_MPI_SM_GetSMHandleBySID(HI_U32 u32SessionID, HI_HANDLE *phSM)
{
    HI_S32 ret = HI_FAILURE;
    SM_CTL_SMHANDLE_S stSMHandle;

    SM_FUNC_ENTER();

    SM_CHECK_POINTER(phSM);
    memset(&stSMHandle, 0x00, sizeof (SM_CTL_SMHANDLE_S));
    stSMHandle.hHandle = HI_INVALID_HANDLE;
    stSMHandle.u32SessionID = u32SessionID;

    SM_CHECK_POINTER(phSM);

    ret = ioctl(s_s32SMFd, CMD_SM_GET_SMHANDLE, &stSMHandle);
    if (HI_SUCCESS != ret)
    {
        SM_PrintErrorFunc(ioctl, ret);
        return ret;
    }

    *phSM = stSMHandle.hHandle;

    SM_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_MPI_SM_GetIntent(HI_HANDLE hSM, HI_UNF_SM_INTENT_E *penIntent)
{
    HI_S32 ret = HI_FAILURE;
    SM_CTL_INTENT_S stIntent;

    SM_FUNC_ENTER();

    SM_CHECK_POINTER(penIntent);

    memset(&stIntent, 0x00, sizeof (SM_CTL_INTENT_S));
    stIntent.hSM = hSM;

    SM_CHECK_SMHANDLE(stIntent.hSM);

    ret = ioctl(s_s32SMFd, CMD_SM_GET_INTENT, &stIntent);
    if (HI_SUCCESS != ret)
    {
        SM_PrintErrorFunc(ioctl, ret);
        return ret;
    }

    *penIntent = stIntent.enIntent;

    SM_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_MPI_SM_GetResourceBySMHandle(HI_HANDLE hSM, HI_UNF_SM_MODULE_E enModID, HI_UNF_SM_MODULE_S *pstModule, HI_U32 *pu32ModNum)
{
    HI_S32 ret = HI_FAILURE;
    HI_S32 i = 0;
    SM_CTL_MODULEBYSM_S stModule;

    SM_FUNC_ENTER();

    SM_CHECK_POINTER(pu32ModNum);

    memset(&stModule, 0x00, sizeof (SM_CTL_MODULEBYSM_S));
    stModule.hSM          = hSM;
    stModule.enModule     = enModID;
    stModule.u32ModuleNum = SM_MIN(MAX_RESOURCE_NUM, *pu32ModNum);

    SM_CHECK_SMHANDLE(stModule.hSM);
    SM_CHECK_MODULEID(enModID);
    SM_CHECK_RESOURCE_NUM(stModule.u32ModuleNum);

    ret = ioctl(s_s32SMFd, CMD_SM_GET_RESOURCE_BYSM, &stModule);
    if (HI_SUCCESS != ret)
    {
        SM_PrintErrorFunc(ioctl, ret);
        return ret;
    }

    for (i = 0; i < stModule.u32ModuleNum; i++)
    {
        memcpy(pstModule + i, &stModule.stModule[i], sizeof (HI_UNF_SM_MODULE_S));
    }

    *pu32ModNum = stModule.u32ModuleNum;

    SM_FUNC_EXIT();
    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
