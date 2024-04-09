/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mpi_vo.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/12/17
  Description   :
  History       :
  1.Date        : 2009/12/17
    Author      : sdk
    Modification: Created file

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <errno.h>
#include <pthread.h>
#include <linux/types.h>

#include "hi_drv_video.h"
#include "hi_drv_disp.h"
#include "hi_mpi_win.h"
#include "drv_win_ioctl.h"

#include "hi_mpi_avplay.h"
#include "hi_error_mpi.h"
#include "hi_drv_struct.h"
#include "hi_mpi_mem.h"
#include "mpi_mmz.h"
#include "hi_common.h"

#include "drv_venc_ext.h"
#include "win_ratio.h"

#define VDP_MEM_MAX 0x1000000

#ifdef HI_VDP_VIDEO_LINEDCMP
#include "./vo_algbase/src/dcmp.h"
#endif
#ifdef HI_HDR_DOLBYVISION_SUPPORT
#include "dolby_wrap.h"
#endif
#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif


static HI_S32           g_VoDevFd = -1;
static const HI_CHAR    g_VoDevName[] = "/dev/"UMAP_DEVNAME_VO;
static pthread_mutex_t  g_VoMutex = PTHREAD_MUTEX_INITIALIZER;

#ifdef HI_HDR_DOLBYVISION_SUPPORT
#define DOLBY_BUF_SIZE        (64 * 1024)

static pthread_mutex_t  g_DolbyLibMutex = PTHREAD_MUTEX_INITIALIZER;
#define HI_DOLBY_LIB_LOCK()    (void)pthread_mutex_lock(&g_DolbyLibMutex);
#define HI_DOLBY_LIB_UNLOCK()  (void)pthread_mutex_unlock(&g_DolbyLibMutex);

static HI_MMZ_BUF_S stDolbyBuf;

static HI_VOID* pDllModule = HI_NULL;
static HI_U32   s_u32DolbyLibInitCount = 0;

#ifdef ANDROID
static HI_CHAR* pszDolbyDllName = "/system/lib/libdolbyvision.so";
#else
static HI_CHAR* pszDolbyDllName = "/usr/lib/libdolbyvision.so";
#endif

static DOLBY_UNIVERSAL_FUN_S s_DolbyFuncEntry = {0};

#endif

#define HI_VO_LOCK()     (void)pthread_mutex_lock(&g_VoMutex);
#define HI_VO_UNLOCK()   (void)pthread_mutex_unlock(&g_VoMutex);

#define CHECK_VO_INIT()\
do{\
    HI_VO_LOCK();\
    if (g_VoDevFd < 0)\
    {\
        HI_ERR_WIN("VO is not init.\n");\
        HI_VO_UNLOCK();\
        return HI_ERR_VO_NO_INIT;\
    }\
    HI_VO_UNLOCK();\
}while(0)

#define CHECK_VO_NULL_PTR(a)\
    do{\
        if (HI_NULL == (a))\
        {\
            HI_ERR_WIN("para %s is null.\n", #a);\
            return HI_ERR_VO_NULL_PTR;\
        }\
    }while(0)

#ifdef HI_HDR_DOLBYVISION_SUPPORT
HI_S32  HI_MPI_WIN_CheckDolbyLib(DOLBY_UNIVERSAL_FUN_S *pstDolbyFun)
{
    if ((HI_NULL == pstDolbyFun)
        || (HI_NULL == pstDolbyFun->pfn_dolby_lib_wrap_interface))
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_RegisterDolbyLib(HI_VOID)
{
    HI_S32  s32Ret = HI_FAILURE;
    WIN_DOLBY_LIB_INFO_S stDolbyLibInfo;
    dolby_vision_info_t dolby_vision_info;

    memset(&stDolbyLibInfo, 0x0, sizeof(stDolbyLibInfo));
    memset(&dolby_vision_info, 0x0, sizeof(dolby_vision_info_t));

    pDllModule = dlopen(pszDolbyDllName, RTLD_LAZY | RTLD_GLOBAL);
    if (HI_NULL == pDllModule)
    {
        HI_WARN_WIN("Register %s fail:%s.\n", pszDolbyDllName, dlerror());
        memset(&s_DolbyFuncEntry, 0x0, sizeof(s_DolbyFuncEntry));
        return HI_FAILURE;
    }

    s_DolbyFuncEntry.pfn_dolby_lib_wrap_interface = dlsym(pDllModule, "dolby_lib_wrap_interface");

    if (HI_FAILURE == HI_MPI_WIN_CheckDolbyLib(&s_DolbyFuncEntry))
    {
        HI_ERR_WIN("Open s_DolbyFuncEntry functions fail.\n");
        memset(&s_DolbyFuncEntry, 0x0, sizeof(s_DolbyFuncEntry));
        return HI_FAILURE;
    }

    s32Ret = s_DolbyFuncEntry.pfn_dolby_lib_wrap_interface(CMD_GET_VERSION_INFO, NULL, &dolby_vision_info);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_WIN("Get dolbylib info fail.\n");
        memset(&s_DolbyFuncEntry, 0x0, sizeof(s_DolbyFuncEntry));
        return HI_FAILURE;
    }

    memset(stDolbyLibInfo.cVersion, 0, sizeof(stDolbyLibInfo.cVersion));
    memset(stDolbyLibInfo.cBuildtime, 0, sizeof(stDolbyLibInfo.cBuildtime));
    memset(stDolbyLibInfo.cUserName, 0, sizeof(stDolbyLibInfo.cUserName));

    strncpy(stDolbyLibInfo.cVersion, dolby_vision_info.pversion, sizeof(stDolbyLibInfo.cVersion) - 1);
    strncpy(stDolbyLibInfo.cBuildtime, dolby_vision_info.pbuild_time, sizeof(stDolbyLibInfo.cBuildtime) - 1);
    strncpy(stDolbyLibInfo.cUserName, dolby_vision_info.puser_name, sizeof(stDolbyLibInfo.cUserName) - 1);

    stDolbyLibInfo.cVersion[sizeof(stDolbyLibInfo.cVersion)-1] = '\0';
    stDolbyLibInfo.cBuildtime[sizeof(stDolbyLibInfo.cBuildtime)-1] = '\0';
    stDolbyLibInfo.cUserName[sizeof(stDolbyLibInfo.cUserName)-1] = '\0';

    stDolbyLibInfo.u32UserID[0] = dolby_vision_info.user_id[0];
    stDolbyLibInfo.u32UserID[1] = dolby_vision_info.user_id[1];
    stDolbyLibInfo.u32UserID[2] = dolby_vision_info.user_id[2];
    stDolbyLibInfo.u32UserID[3] = dolby_vision_info.user_id[3];
    stDolbyLibInfo.bValid = HI_TRUE;

    s32Ret = HI_MPI_WIN_SetDolbyLibInfo(&stDolbyLibInfo);

    return s32Ret;
}

HI_VOID HI_MPI_WIN_UnRegisterDolbyLib(HI_VOID)
{
    WIN_DOLBY_LIB_INFO_S stDolbyLibInfo;
    memset(&stDolbyLibInfo, 0x0, sizeof(WIN_DOLBY_LIB_INFO_S));

    //close dolby lib.
    if (HI_NULL != pDllModule)
    {
        dlclose(pDllModule);
        pDllModule = HI_NULL;
    }

    if (HI_NULL != s_DolbyFuncEntry.pfn_dolby_lib_wrap_interface)
    {
        memset(&s_DolbyFuncEntry, 0x0, sizeof(s_DolbyFuncEntry));
    }

    //Reset dolbylib info
    (HI_VOID)HI_MPI_WIN_SetDolbyLibInfo(&stDolbyLibInfo);

    return;
}

HI_S32  HI_MPI_WIN_AllocateDolbyBuf(HI_MMZ_BUF_S *pstDolbyVisionBuf)
{
    if (HI_NULL == pstDolbyVisionBuf)
    {
        return HI_ERR_VO_NULL_PTR;
    }

    if (HI_NULL != pstDolbyVisionBuf->phyaddr)
    {
        HI_ERR_WIN("dolby buffer has been allocated!\n");
        return HI_ERR_VO_MALLOC_FAILED;
    }

    memset(pstDolbyVisionBuf,0x0,sizeof(HI_MMZ_BUF_S));

    strncpy(pstDolbyVisionBuf->bufname, "VDP_DolbyVisionBuf", sizeof(pstDolbyVisionBuf->bufname) - 1);
    pstDolbyVisionBuf->bufname[sizeof(pstDolbyVisionBuf->bufname)-1] = '\0';
    pstDolbyVisionBuf->bufsize = DOLBY_BUF_SIZE;

#ifdef HI_SMMU_SUPPORT
    pstDolbyVisionBuf->phyaddr = HI_MPI_SMMU_New(pstDolbyVisionBuf->bufname, pstDolbyVisionBuf->bufsize);
    if (HI_NULL == pstDolbyVisionBuf->phyaddr )
    {
        HI_FATAL_WIN("HI_MPI_SMMU_New stDolbyBuf %d failed!\n", pstDolbyVisionBuf->bufsize);
        return HI_ERR_VO_MALLOC_FAILED;
    }

    pstDolbyVisionBuf->user_viraddr = (HI_U8*)HI_MPI_SMMU_Map(pstDolbyVisionBuf->phyaddr, HI_FALSE);
    if (HI_NULL == pstDolbyVisionBuf->user_viraddr )
    {
        HI_FATAL_WIN("HI_MPI_SMMU_Map stDolbyBuf %d failed!\n", pstDolbyVisionBuf->bufsize);
        return HI_ERR_VO_NULL_PTR;
    }
#else
    if (HI_MPI_MMZ_Malloc(pstDolbyVisionBuf) != HI_SUCCESS)
    {
        HI_FATAL_WIN("HI_MPI_MMZ_Malloc stDolbyBuf %d failed!\n", pstDolbyVisionBuf->bufsize);
        return HI_ERR_VO_DEV_OPEN_ERR;

    }
#endif
    return HI_SUCCESS;
}

HI_VOID HI_MPI_WIN_ReleaseDolbyBuf(HI_MMZ_BUF_S *pstDolbyVisionBuf)
{
    if (HI_NULL == pstDolbyVisionBuf)
    {
        return;
    }
#ifdef HI_SMMU_SUPPORT
    if (HI_NULL != pstDolbyVisionBuf->phyaddr)
    {
        if(HI_NULL != pstDolbyVisionBuf->user_viraddr)
        {
            HI_MPI_SMMU_Unmap(pstDolbyVisionBuf->phyaddr);
        }
        HI_MPI_SMMU_Delete(pstDolbyVisionBuf->phyaddr);
    }
#else
    if (HI_NULL != pstDolbyVisionBuf->phyaddr)
    {
        HI_MPI_MMZ_Free(pstDolbyVisionBuf);
    }
#endif
    memset(pstDolbyVisionBuf, 0x0, sizeof(HI_MMZ_BUF_S));

    return;
}


static HI_S32  HI_MPI_WIN_GetMetadataStream(WIN_XDR_FRAME_S *pstWinXdrFrm,
                              HI_DRV_VIDEO_DOLBY_METADATA_STREAM_S *pstMetadata)
{
    HI_BOOL bBLHasMeta = HI_FALSE;
    HI_BOOL bELHasMeta = HI_FALSE;

    CHECK_VO_NULL_PTR(pstWinXdrFrm);
    CHECK_VO_NULL_PTR(pstMetadata);

    if (HI_DRV_VIDEO_FRAME_TYPE_DOLBY_BL != pstWinXdrFrm->stBaseFrm.enSrcFrameType)
    {
        pstMetadata->u32Addr = HI_NULL;
        pstMetadata->u32Length = 0;
        return HI_SUCCESS;
    }

    if (pstWinXdrFrm->bEnhanceValid)
    {
        bBLHasMeta = pstWinXdrFrm->stBaseFrm.unHDRInfo.stDolbyInfo.bMetadataValid;
        bELHasMeta = pstWinXdrFrm->stEnhanceFrm.unHDRInfo.stDolbyInfo.bMetadataValid;
    }
    else
    {
        bBLHasMeta = pstWinXdrFrm->stBaseFrm.unHDRInfo.stDolbyInfo.bMetadataValid;
    }

    if ((bBLHasMeta && bELHasMeta) ||
        (!bBLHasMeta && !bELHasMeta))
    {
        HI_ERR_WIN("Dolby Frame has wrong metadata! bBLHasMeta %d,bELHasMeta %d\n",bBLHasMeta,bELHasMeta);
        return HI_ERR_VO_FRAME_INFO_ERROR;
    }

    if (bBLHasMeta)
    {
        pstMetadata->u32Addr   = pstWinXdrFrm->stBaseFrm.unHDRInfo.stDolbyInfo.stMetadata.u32Addr;
        pstMetadata->u32Length = pstWinXdrFrm->stBaseFrm.unHDRInfo.stDolbyInfo.stMetadata.u32Length;
    }
    else
    {
        pstMetadata->u32Addr   = pstWinXdrFrm->stEnhanceFrm.unHDRInfo.stDolbyInfo.stMetadata.u32Addr;
        pstMetadata->u32Length = pstWinXdrFrm->stEnhanceFrm.unHDRInfo.stDolbyInfo.stMetadata.u32Length;
    }

    return HI_SUCCESS;
}


HI_S32  HI_MPI_WIN_GetConfigFromDolbyLib(           cmd_generate_config_para_in_s *pstParaIn, cmd_generate_config_para_out_s *pstParaOut, HI_MMZ_BUF_S *pstRegBuf)
{
    HI_S32 Ret;

    CHECK_VO_NULL_PTR(pstRegBuf);

    pstParaIn->stRegsBuffer.u64Addr = (unsigned long long)(uintptr_t)pstRegBuf->user_viraddr;
    pstParaIn->stRegsBuffer.u32Len  = pstRegBuf->bufsize;

    if(HI_FAILURE == HI_MPI_WIN_CheckDolbyLib(&s_DolbyFuncEntry))
    {
        HI_ERR_WIN("s_DolbyFuncEntry is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    Ret = s_DolbyFuncEntry.pfn_dolby_lib_wrap_interface(CMD_GENERATE_CONFIG, pstParaIn, pstParaOut);

    return Ret;
}
#endif

HI_S32 HI_MPI_WIN_Init(HI_VOID)
{
    HI_VO_LOCK();

    if (g_VoDevFd > 0)
    {
        HI_VO_UNLOCK();
        return HI_SUCCESS;
    }

    g_VoDevFd = open(g_VoDevName, O_RDWR|O_NONBLOCK, 0);

    if (g_VoDevFd < 0)
    {
        HI_FATAL_WIN("open VO err.\n");
        HI_VO_UNLOCK();
        return HI_ERR_VO_DEV_OPEN_ERR;
    }

#ifdef HI_HDR_DOLBYVISION_SUPPORT
    HI_S32 Ret = HI_FAILURE;

    if (HI_SUCCESS == HI_MPI_WIN_RegisterDolbyLib())
    {
        Ret = HI_MPI_WIN_AllocateDolbyBuf(&stDolbyBuf);
        if (HI_SUCCESS != Ret)
        {
            HI_FATAL_WIN("HI_MPI_WIN_AllocateDolbyBuf failed!\n");
            goto ERR_PROCESS_RELEASE_RESOURCE;
        }
    }
    else
    {
        HI_MPI_WIN_UnRegisterDolbyLib();
    }
#endif

    HI_VO_UNLOCK();

    return HI_SUCCESS;

#ifdef HI_HDR_DOLBYVISION_SUPPORT
ERR_PROCESS_RELEASE_RESOURCE:
    HI_MPI_WIN_UnRegisterDolbyLib();
    HI_MPI_WIN_ReleaseDolbyBuf(&stDolbyBuf);

    close(g_VoDevFd);
    g_VoDevFd = -1;
    HI_VO_UNLOCK();
    return Ret;
#endif
}

HI_S32 HI_MPI_WIN_DeInit(HI_VOID)
{
    HI_S32 Ret;

    HI_VO_LOCK();

    if (g_VoDevFd < 0)
    {
        HI_VO_UNLOCK();
        return HI_SUCCESS;
    }

#ifdef HI_HDR_DOLBYVISION_SUPPORT
    HI_MPI_WIN_UnRegisterDolbyLib();
    HI_MPI_WIN_ReleaseDolbyBuf(&stDolbyBuf);
#endif

    Ret = close(g_VoDevFd);
    if (HI_SUCCESS != Ret)
    {
        HI_FATAL_WIN("DeInit VO err.\n");
        HI_VO_UNLOCK();
        return HI_ERR_VO_DEV_CLOSE_ERR;
    }

    g_VoDevFd = -1;

    HI_VO_UNLOCK();

    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_Create(const HI_DRV_WIN_ATTR_S *pWinAttr, HI_HANDLE *phWindow)
{
    HI_S32          Ret = HI_SUCCESS;
    WIN_CREATE_S    VoWinCreate;

    if (!pWinAttr)
    {
        HI_ERR_WIN("para pWinAttr is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    if (!phWindow)
    {
        HI_ERR_WIN("para phWindow is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    if (pWinAttr->enDisp >= HI_DRV_DISPLAY_2
        && pWinAttr->bVirtual == HI_FALSE)
    {
        HI_ERR_WIN("para pWinAttr->enDisp is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (pWinAttr->enARCvrs >= HI_DRV_ASP_RAT_MODE_BUTT)
    {
        HI_ERR_WIN("para pWinAttr->enARCvrs is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (pWinAttr->enDataFormat >= HI_DRV_PIX_BUTT)
    {
        HI_ERR_WIN("para pWinAttr->enDataFormat is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    memcpy(&VoWinCreate.WinAttr, pWinAttr, sizeof(HI_DRV_WIN_ATTR_S));
    VoWinCreate.bVirtScreen = HI_TRUE;
    VoWinCreate.bMCE = HI_FALSE;

    Ret = ioctl(g_VoDevFd, CMD_WIN_CREATE, &VoWinCreate);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("  HI_MPI_WIN_Create failed.\n");
        return Ret;
    }

    *phWindow = VoWinCreate.hWindow;

    /* Init dolby lib here instead of in WIN_INT.Android may create
    * different wins while ONLY call one time WIN_INT, thus may cause error status of
    * dolby lib.count the time of initial dolby lib when create win successfully, this
    * count will be used when de-init dolby lib when destory win in multi-wins situation.*/
#ifdef HI_HDR_DOLBYVISION_SUPPORT
    if (s_DolbyFuncEntry.pfn_dolby_lib_wrap_interface)
    {
        HI_DOLBY_LIB_LOCK();
        Ret = s_DolbyFuncEntry.pfn_dolby_lib_wrap_interface(CMD_LIB_INIT, NULL, NULL);
        if (Ret)
        {
            HI_ERR_WIN("metadata_parser_init fail.\n");
            HI_DOLBY_LIB_UNLOCK();
            return Ret;
        }

        /* record init times for de-init dolby lib when destory win. */
        s_u32DolbyLibInitCount++;
        HI_DOLBY_LIB_UNLOCK();
    }
#endif
    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_Create_Ext(const HI_DRV_WIN_ATTR_S *pWinAttr, HI_HANDLE *phWindow, HI_BOOL bVirtScreen)
{
    HI_S32           Ret = HI_SUCCESS;;
    WIN_CREATE_S  VoWinCreate;

    if (!pWinAttr)
    {
        HI_ERR_WIN("para pWinAttr is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    if (!phWindow)
    {
        HI_ERR_WIN("para phWindow is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    if (pWinAttr->enDisp >= HI_DRV_DISPLAY_2
        && pWinAttr->bVirtual == HI_FALSE)
    {
        HI_ERR_WIN("para pWinAttr->enDisp is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (pWinAttr->enARCvrs >= HI_DRV_ASP_RAT_MODE_BUTT)
    {
        HI_ERR_WIN("para pWinAttr->enARCvrs is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (pWinAttr->enDataFormat >= HI_DRV_PIX_BUTT)
    {
        HI_ERR_WIN("para pWinAttr->enDataFormat is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    memcpy(&VoWinCreate.WinAttr, pWinAttr, sizeof(HI_DRV_WIN_ATTR_S));
    VoWinCreate.bVirtScreen = bVirtScreen;

    Ret = ioctl(g_VoDevFd, CMD_WIN_CREATE, &VoWinCreate);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("  HI_MPI_WIN_Create failed.\n");
        return Ret;
    }

    *phWindow = VoWinCreate.hWindow;

   /* Init dolby lib here instead of in WIN_INT.Android may create
   * different wins while ONLY call one time WIN_INT, thus may cause error status of
   * dolby lib.count the time of initial dolby lib when create win successfully, this
   * count will be used when de-init dolby lib when destory win in multi-wins situation.*/
#ifdef HI_HDR_DOLBYVISION_SUPPORT
        if (s_DolbyFuncEntry.pfn_dolby_lib_wrap_interface)
        {
            HI_DOLBY_LIB_LOCK();
            Ret = s_DolbyFuncEntry.pfn_dolby_lib_wrap_interface(CMD_LIB_INIT, NULL, NULL);
            if (Ret)
            {
                HI_ERR_WIN("metadata_parser_init fail.\n");
                HI_DOLBY_LIB_UNLOCK();
                return Ret;
            }

            /* record init times for de-init dolby lib when destory win. */
            s_u32DolbyLibInitCount++;
            HI_DOLBY_LIB_UNLOCK();
        }
#endif

    return HI_SUCCESS;
}


HI_S32 HI_MPI_WIN_Destroy(HI_HANDLE hWindow)
{
    HI_S32      Ret;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    Ret = ioctl(g_VoDevFd, CMD_WIN_DESTROY, &hWindow);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_WIN("  HI_MPI_WIN_Destroy failed.\n");
        return Ret;
    }

#ifdef HI_HDR_DOLBYVISION_SUPPORT
    HI_DOLBY_LIB_LOCK();
    /* It may initial dolby lib many times when create multi-wins, in case of the last
     * win may use for DolbyVision, de-init dolby lib operation CANNOT be done until destory
     * the last win.*/
    if(1 == s_u32DolbyLibInitCount)
    {
        if (s_DolbyFuncEntry.pfn_dolby_lib_wrap_interface)
        {
            (HI_VOID)s_DolbyFuncEntry.pfn_dolby_lib_wrap_interface(CMD_LIB_DEINIT, NULL, NULL);
        }
    }

    /* remember to decrease init count. */
     s_u32DolbyLibInitCount --;
    HI_DOLBY_LIB_UNLOCK();
#endif

    return Ret;
}

HI_S32 HI_MPI_WIN_GetInfo(HI_HANDLE hWin, HI_DRV_WIN_INFO_S * pstInfo)
{
    HI_S32 Ret;
    WIN_PRIV_INFO_S WinPriv;

    if (HI_INVALID_HANDLE == hWin)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_NULL_PTR(pstInfo);
    CHECK_VO_INIT();

    WinPriv.hWindow = hWin;

    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_INFO, &WinPriv);
    if (HI_SUCCESS == Ret)
    {
        *pstInfo = WinPriv.stPrivInfo;
    }

    return Ret;
}

HI_S32 HI_MPI_WIN_GetPlayInfo(HI_HANDLE hWin, HI_DRV_WIN_PLAY_INFO_S * pstInfo)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_PLAY_INFO_S WinPlay;

    if (HI_INVALID_HANDLE == hWin)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_NULL_PTR(pstInfo);
    CHECK_VO_INIT();

    WinPlay.hWindow = hWin;

    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_PLAY_INFO, &WinPlay);
    if (HI_SUCCESS == Ret)
    {
        *pstInfo = WinPlay.stPlayInfo;
    }

    return Ret;
}


HI_S32 HI_MPI_WIN_SetSource(HI_HANDLE hWin, HI_DRV_WIN_SRC_HANDLE_S *pstSrc)
{
    HI_S32 Ret;
    WIN_SOURCE_S VoWinAttach;

    if (HI_INVALID_HANDLE == hWin)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_NULL_PTR(pstSrc);
    if (pstSrc->enSrcMode > HI_ID_BUTT)
    {
        HI_ERR_WIN("para pstSrc->enSrcMode is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    VoWinAttach.hWindow = hWin;
    VoWinAttach.stSrc   = *pstSrc;

    Ret = ioctl(g_VoDevFd, CMD_WIN_SET_SOURCE, &VoWinAttach);

    return Ret;
}

HI_S32 HI_MPI_WIN_GetSource(HI_HANDLE hWin, HI_DRV_WIN_SRC_HANDLE_S *pstSrc)
{
    return HI_FAILURE;
}

HI_S32 HI_MPI_WIN_SetEnable(HI_HANDLE hWindow, HI_BOOL bEnable)
{
    HI_S32            Ret;
    WIN_ENABLE_S   VoWinEnable;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if ((bEnable != HI_TRUE) &&(bEnable != HI_FALSE))
    {
        HI_ERR_WIN("para bEnable is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    VoWinEnable.hWindow = hWindow;
    VoWinEnable.bEnable = bEnable;

    Ret = ioctl(g_VoDevFd, CMD_WIN_SET_ENABLE, &VoWinEnable);

    return Ret;
}


HI_S32 HI_MPI_VO_SetMainWindowEnable(HI_HANDLE hWindow, HI_BOOL bEnable)
{
    return HI_FAILURE;
}


HI_S32 HI_MPI_WIN_GetEnable(HI_HANDLE hWindow, HI_BOOL *pbEnable)
{
    HI_S32          Ret = HI_SUCCESS;
    WIN_ENABLE_S    VoWinEnable;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_NULL_PTR(pbEnable);
    CHECK_VO_INIT();

    memset((HI_VOID*)&VoWinEnable, 0, sizeof(WIN_ENABLE_S));
    VoWinEnable.hWindow = hWindow;

    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_ENABLE, &VoWinEnable);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    *pbEnable = VoWinEnable.bEnable;

    return HI_SUCCESS;
}

HI_S32 HI_MPI_VO_GetMainWindowEnable(HI_HANDLE hWindow, HI_BOOL *pbEnable)
{
    return HI_FAILURE;
}


HI_S32 HI_MPI_VO_GetWindowsVirtual(HI_HANDLE hWindow, HI_BOOL *pbVirutal)
{
    return HI_FAILURE;
}

HI_S32 HI_MPI_WIN_AcquireFrame(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pFrameinfo)
{
    HI_S32           Ret = HI_SUCCESS;
    WIN_FRAME_S      VoWinFrame;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_NULL_PTR(pFrameinfo);
    CHECK_VO_INIT();

    memset((HI_VOID*)&VoWinFrame, 0, sizeof(WIN_FRAME_S));
    VoWinFrame.hWindow = hWindow;

    Ret = ioctl(g_VoDevFd, CMD_WIN_VIR_ACQUIRE, &VoWinFrame);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    memcpy(pFrameinfo, &(VoWinFrame.stFrame), sizeof(HI_DRV_VIDEO_FRAME_S));

    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_ReleaseFrame(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pFrameinfo)
{
    HI_S32           Ret = HI_SUCCESS;
    WIN_FRAME_S      VoWinFrame;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_NULL_PTR(pFrameinfo);
    CHECK_VO_INIT();

    memset((HI_VOID*)&VoWinFrame, 0, sizeof(WIN_FRAME_S));

    VoWinFrame.hWindow = hWindow;
    VoWinFrame.stFrame = *pFrameinfo;

    Ret = ioctl(g_VoDevFd, CMD_WIN_VIR_RELEASE, &VoWinFrame);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_SetAttr(HI_HANDLE hWindow, const HI_DRV_WIN_ATTR_S *pWinAttr)
{
    HI_S32           Ret = HI_SUCCESS;
    WIN_CREATE_S     VoWinCreate;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_NULL_PTR(pWinAttr);

    if (pWinAttr->enDisp >= HI_DRV_DISPLAY_2)
    {
        HI_ERR_WIN("para pWinAttr->enDisp is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (pWinAttr->enARCvrs >= HI_DRV_ASP_RAT_MODE_BUTT)
    {
        HI_ERR_WIN("para pWinAttr->enAspectCvrs is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (pWinAttr->enDataFormat >= HI_DRV_PIX_BUTT)
    {
        HI_ERR_WIN("para pWinAttr->enDataFormat is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    memset((HI_VOID*)&VoWinCreate, 0, sizeof(WIN_CREATE_S));
    VoWinCreate.hWindow = hWindow;
    memcpy(&VoWinCreate.WinAttr, pWinAttr, sizeof(HI_DRV_WIN_ATTR_S));

    Ret = ioctl(g_VoDevFd, CMD_WIN_SET_ATTR, &VoWinCreate);

    return Ret;
}

HI_S32 HI_MPI_WIN_GetAttr(HI_HANDLE hWindow, HI_DRV_WIN_ATTR_S *pWinAttr)
{
    HI_S32           Ret = HI_SUCCESS;
    WIN_CREATE_S  VoWinCreate;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_NULL_PTR(pWinAttr);
    CHECK_VO_INIT();

    memset((HI_VOID*)&VoWinCreate, 0, sizeof(WIN_CREATE_S));
    VoWinCreate.hWindow = hWindow;

    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_ATTR, &VoWinCreate);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    memcpy(pWinAttr, &VoWinCreate.WinAttr, sizeof(HI_DRV_WIN_ATTR_S));

    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_SetZorder(HI_HANDLE hWindow, HI_DRV_DISP_ZORDER_E enZFlag)
{
    HI_S32            Ret;
    WIN_ZORDER_S   VoWinZorder;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (enZFlag >= HI_DRV_DISP_ZORDER_BUTT)
    {
        HI_ERR_WIN("para enZFlag is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    VoWinZorder.hWindow = hWindow;
    VoWinZorder.eZFlag = enZFlag;

    Ret = ioctl(g_VoDevFd, CMD_WIN_SET_ZORDER, &VoWinZorder);

    return Ret;
}

HI_S32 HI_MPI_WIN_GetZorder(HI_HANDLE hWindow, HI_U32 *pu32Zorder)
{
    HI_S32            Ret = HI_SUCCESS;
    WIN_ORDER_S   VoWinOrder;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (!pu32Zorder)
    {
        HI_ERR_WIN("para SrcHandle is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    CHECK_VO_INIT();

    memset((HI_VOID*)&VoWinOrder, 0, sizeof(WIN_ORDER_S));
    VoWinOrder.hWindow = hWindow;

    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_ORDER, &VoWinOrder);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    *pu32Zorder = VoWinOrder.Order;

    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_Attach(HI_HANDLE hWindow, HI_HANDLE hSrc)
{

    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_Detach(HI_HANDLE hWindow, HI_HANDLE hSrc)
{

    return HI_FAILURE;
}

HI_S32 HI_MPI_VO_SetWindowRatio(HI_HANDLE hWindow, HI_U32 u32WinRatio)
{

    return HI_FAILURE;
}

HI_S32 HI_MPI_WIN_Freeze(HI_HANDLE hWindow, HI_BOOL bEnable, HI_DRV_WIN_SWITCH_E enWinFreezeMode)
{
    HI_S32           Ret;
    WIN_FREEZE_S  VoWinFreeze;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if ((bEnable != HI_TRUE)
      &&(bEnable != HI_FALSE)
       )
    {
        HI_ERR_WIN("para bEnable is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (enWinFreezeMode >= HI_DRV_WIN_SWITCH_BUTT)
    {
        HI_ERR_WIN("para enWinFreezeMode is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    VoWinFreeze.hWindow = hWindow;
    VoWinFreeze.bEnable = bEnable;
    VoWinFreeze.eMode   = enWinFreezeMode;

    Ret = ioctl(g_VoDevFd, CMD_WIN_FREEZE, &VoWinFreeze);

    return Ret;
}

HI_S32 HI_MPI_WIN_GetFreezeStat(HI_HANDLE hWindow, HI_BOOL *bEnable, HI_DRV_WIN_SWITCH_E *enWinFreezeMode)
{
    HI_S32           Ret;
    WIN_FREEZE_S    stWinFreeze;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if ((!bEnable) || (!enWinFreezeMode))
    {
        HI_ERR_WIN("param ptr is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    CHECK_VO_INIT();

    stWinFreeze.hWindow = hWindow;

    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_FREEZE_STATUS, &stWinFreeze);
    if (HI_SUCCESS == Ret)
    {
        *bEnable = stWinFreeze.bEnable;
        *enWinFreezeMode = stWinFreeze.eMode;
    }

    return Ret;
}

HI_S32 HI_MPI_WIN_SetFieldMode(HI_HANDLE hWindow, HI_BOOL bEnable)
{
    return HI_FAILURE;
}

HI_S32 HI_MPI_WIN_SendFrame(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pFrame)
{
    HI_S32             Ret = HI_SUCCESS;
    WIN_FRAME_S     VoWinFrame;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (!pFrame)
    {
        HI_ERR_WIN("para pFrame is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    CHECK_VO_INIT();

    memset((HI_VOID*)&VoWinFrame, 0, sizeof(WIN_FRAME_S));
    VoWinFrame.hWindow  = hWindow;
    VoWinFrame.stFrame = *pFrame;

    Ret = ioctl(g_VoDevFd, CMD_WIN_SEND_FRAME, &VoWinFrame);

    return Ret;
}

HI_S32 HI_MPI_WIN_DequeueFrame(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pFrame)
{
    HI_S32             Ret = HI_SUCCESS;
    WIN_FRAME_S VoWinFrame;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (!pFrame)
    {
        HI_ERR_WIN("para pFrameinfo is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    CHECK_VO_INIT();

    memset((HI_VOID*)&VoWinFrame, 0, sizeof(WIN_FRAME_S));
    VoWinFrame.hWindow = hWindow;

    Ret = ioctl(g_VoDevFd, CMD_WIN_DQ_FRAME, &VoWinFrame);
    if (HI_SUCCESS == Ret)
    {
        *pFrame = VoWinFrame.stFrame;
    }

    return Ret;
}

HI_S32 HI_MPI_WIN_QueueSyncFrame(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pFrame,HI_U32 *pu32FenceFd)
{
    HI_S32             Ret;
    WIN_SYNCFRAME_S     VoWinFrame;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (!pFrame)
    {
        HI_ERR_WIN("para pFrameinfo is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    CHECK_VO_INIT();

    VoWinFrame.hWindow = hWindow;
    VoWinFrame.stFrame = *pFrame;
    if (pu32FenceFd == HI_NULL)
    {
        VoWinFrame.u32FenceFd = 0x0;
    }
    else
    {
        VoWinFrame.u32FenceFd = 0xffffffff;
    }

    Ret = ioctl(g_VoDevFd, CMD_WIN_QUSYNC_FRAME, &VoWinFrame);
    if ((HI_SUCCESS == Ret) && (pu32FenceFd != HI_NULL))
    {
        *pu32FenceFd = VoWinFrame.u32FenceFd;
    }

    return Ret;
}

#ifdef HI_HDR_DOLBYVISION_SUPPORT
HI_VOID MPI_WIN_TransferHdr10InfoFrmForDolbyLib(HI_DRV_VIDEO_HDR10_INFO_S *pstHdr10Meta,hdr10_param_t *pstDolbyHdr10Param)
{
    if ((HI_NULL == pstHdr10Meta) || (HI_NULL == pstDolbyHdr10Param))
    {
        return;
    }

    pstDolbyHdr10Param->Rx = pstHdr10Meta->stMasteringInfo.u16DisplayPrimaries_x[0];
    pstDolbyHdr10Param->Ry = pstHdr10Meta->stMasteringInfo.u16DisplayPrimaries_y[0];
    pstDolbyHdr10Param->Gx = pstHdr10Meta->stMasteringInfo.u16DisplayPrimaries_x[1];
    pstDolbyHdr10Param->Gy = pstHdr10Meta->stMasteringInfo.u16DisplayPrimaries_y[1];
    pstDolbyHdr10Param->Bx = pstHdr10Meta->stMasteringInfo.u16DisplayPrimaries_x[2];
    pstDolbyHdr10Param->By = pstHdr10Meta->stMasteringInfo.u16DisplayPrimaries_y[2];
    pstDolbyHdr10Param->Wx = pstHdr10Meta->stMasteringInfo.u16WhitePoint_x;
    pstDolbyHdr10Param->Wy = pstHdr10Meta->stMasteringInfo.u16WhitePoint_y;
    pstDolbyHdr10Param->max_display_mastering_luminance = pstHdr10Meta->stMasteringInfo.u32MaxDisplayMasteringLuminance;
    pstDolbyHdr10Param->min_display_mastering_luminance = pstHdr10Meta->stMasteringInfo.u32MinDisplayMasteringLuminance;
    pstDolbyHdr10Param->max_content_light_level = (HI_U16)pstHdr10Meta->stContentInfo.u32MaxContentLightLevel;
    pstDolbyHdr10Param->max_pic_average_light_level = (HI_U16)pstHdr10Meta->stContentInfo.u32MaxPicAverageLightLevel;

    return;
}

static HI_S32 HI_MPI_WIN_MemoryMap(HI_U32 u32Addr, HI_U32 u32Len, HI_U8 **ppu8MapAddr)
{
    if ((HI_NULL == u32Addr) || (0 == u32Len))
    {
        *ppu8MapAddr = HI_NULL;
        return HI_SUCCESS;
    }

    if (u32Len > VDP_MEM_MAX)
    {
        HI_ERR_WIN("the length of mmp is too big.\n");
        return HI_FAILURE;
    }

    *ppu8MapAddr = HI_MMZ_Map(u32Addr, HI_FALSE);

    if (!(*ppu8MapAddr))
    {
        HI_FATAL_WIN("memap stMetadata %08x failed\r\n", u32Addr);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 HI_MPI_WIN_MemoryUnmap(HI_U32 u32Addr, HI_U8 *pu8MapAddr)
{
    if ((HI_NULL == u32Addr) || (HI_NULL == pu8MapAddr))
    {
        return HI_SUCCESS;
    }

#ifdef HI_SMMU_SUPPORT
    HI_MPI_SMMU_Unmap(u32Addr);
#else
    HI_MPI_MMZ_Unmap(pu8MapAddr);
#endif

    return HI_SUCCESS;
}

#define use_cbb_cfg_file 0
#define case_has_compser 0

static HI_S32 HI_MPI_WIN_DolbyLibProcess(WIN_XDR_FRAME_S *pstWinXdrFrm)
{
    HI_S32 s32Ret = HI_SUCCESS;
    cmd_generate_config_para_in_s  stParaIn;
    cmd_generate_config_para_out_s stParaOut;
    HI_DRV_VIDEO_DOLBY_METADATA_STREAM_S stMetadata;

#if use_cbb_cfg_file
        FILE  *fp_dmks = HI_NULL;
        FILE  *fp_com  = HI_NULL;
#endif

    CHECK_VO_NULL_PTR(pstWinXdrFrm);

    memset(&stParaIn, 0x0, sizeof(stParaIn));
    memset(&stParaOut, 0x0, sizeof(stParaOut));
    memset(&stMetadata, 0x0, sizeof(stMetadata));

    if(HI_FAILURE == HI_MPI_WIN_CheckDolbyLib(&s_DolbyFuncEntry))
    {
        HI_ERR_WIN("s_DolbyFuncEntry is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    //---------------set source info-----------------
    stParaIn.stSrcVideoInfo.w = pstWinXdrFrm->stBaseFrm.u32Width;
    stParaIn.stSrcVideoInfo.h = pstWinXdrFrm->stBaseFrm.u32Height;
    stParaIn.stSrcVideoInfo.bits = (pstWinXdrFrm->stBaseFrm.enBitWidth == HI_DRV_PIXEL_BITWIDTH_8BIT) ?  8 : 10;
    /* process different source. */
    if (HI_DRV_VIDEO_FRAME_TYPE_SDR == pstWinXdrFrm->stBaseFrm.enSrcFrameType)
    {
        stParaIn.stSrcVideoInfo.video_type = src_video_sdr;
    }
    else if (HI_DRV_VIDEO_FRAME_TYPE_HDR10 == pstWinXdrFrm->stBaseFrm.enSrcFrameType)
    {
        stParaIn.stSrcVideoInfo.video_type = src_video_hdr10;
        MPI_WIN_TransferHdr10InfoFrmForDolbyLib(&pstWinXdrFrm->stBaseFrm.unHDRInfo.stHDR10Info, &stParaIn.stSrcVideoInfo.hdr10_param);
    }
    /* dolby type will assigned in dolby lib after parse rpu. */

        /* get metadata stream addr and length. */
    s32Ret = HI_MPI_WIN_GetMetadataStream(pstWinXdrFrm, &stMetadata);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    stParaIn.stSrcVideoInfo.stRpu.rpu_len = stMetadata.u32Length;
    s32Ret = HI_MPI_WIN_MemoryMap(stMetadata.u32Addr, stMetadata.u32Length, &stParaIn.stSrcVideoInfo.stRpu.p_rpu_addr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_WIN("get dolby frame or metadata fail.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    //---------------set target info-----------------
    stParaIn.stTargetInfo.w = 1920;
    stParaIn.stTargetInfo.h = 1080;
    switch(pstWinXdrFrm->enDispOutType)
    {
        case HI_DRV_DISP_TYPE_NORMAL:
            stParaIn.stTargetInfo.tgt_type = display_out_sdr_normal;
            break;
        case HI_DRV_DISP_TYPE_SDR_CERT:
            stParaIn.stTargetInfo.tgt_type = display_out_sdr_authentication;
            break;
        case HI_DRV_DISP_TYPE_HDR10:
        case HI_DRV_DISP_TYPE_HDR10_CERT:
            stParaIn.stTargetInfo.tgt_type = display_out_hdr10;
            break;
        case HI_DRV_DISP_TYPE_DOLBY:
            stParaIn.stTargetInfo.tgt_type = display_out_dolby_ipt;
            break;
        default:
            stParaIn.stTargetInfo.tgt_type = display_out_sdr_normal;
            break;
    }

    //---------------set edid info-----------------
    stParaIn.stEdidInfo.edid_min = 50;
    stParaIn.stEdidInfo.edid_max = 40000000;

    //---------------set gfx info-----------------
    stParaIn.stSrcGfxInfo.w = 1920;
    stParaIn.stSrcGfxInfo.h = 1080;
    stParaIn.stSrcGfxInfo.graphics_on = HI_TRUE;//stWinDispTypeGfxState.bNeedProcessGfx;
    stParaIn.stSrcGfxInfo.graphic_max = 1000000;
    stParaIn.stSrcGfxInfo.graphic_min = 50;

    /* call dolby lib to produce the config. */
    s32Ret = HI_MPI_WIN_GetConfigFromDolbyLib(&stParaIn, &stParaOut, &stDolbyBuf);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_WIN("get configuration from DolbyLib fail!\n");
        HI_MPI_WIN_MemoryUnmap(stMetadata.u32Addr, stParaIn.stSrcVideoInfo.stRpu.p_rpu_addr);
        return s32Ret;
    }

    HI_MPI_WIN_MemoryUnmap(stMetadata.u32Addr, stParaIn.stSrcVideoInfo.stRpu.p_rpu_addr);

#if use_cbb_cfg_file
        HI_ERR_WIN("-----now open cbb's cfg file-----\n");
        fp_dmks = fopen("dm_cfg.bin", "rb");
        if (!fp_dmks)
            HI_ERR_WIN("open file dm_cfg failed\r\n");
#if case_has_compser
        fp_com = fopen("comp.bin", "rb");
        if (!fp_com)
            HI_ERR_WIN("open file comp failed\r\n");
        //fseek(fp_com,sizeof(rpu_ext_config_fixpt_main_t) * 0x2b, 0);
        fread((char *)(uintptr_t)stParaOut.stCommitRegs.stComposer.u64Addr, 1, COMPOSER_LEN, fp_com);
#endif
        //fseek(fp_dmks,sizeof(Hisi_DmKsFxp_t) * (0x2b - 1), 0);
        fread((char *)(uintptr_t)stParaOut.stCommitRegs.stDmKs.u64Addr, 1, HISI_DMKS_LEN, fp_dmks);

        if (fp_dmks)
            fclose(fp_dmks);
        if (fp_com)
            fclose(fp_com);
#endif

    pstWinXdrFrm->stDolbyInfo.u32PhyAddr = stDolbyBuf.phyaddr;//need to pass physical address to kernel.
    pstWinXdrFrm->stDolbyInfo.u32CompLen = stParaOut.stCommitRegs.stComposer.u32Len;
    pstWinXdrFrm->stDolbyInfo.u32DmCfgLen = stParaOut.stCommitRegs.stDmMetadata.u32Len;
    pstWinXdrFrm->stDolbyInfo.u32DmRegLen = stParaOut.stCommitRegs.stDmKs.u32Len;
    pstWinXdrFrm->stDolbyInfo.u32Hdr10InfoFrmLen = stParaOut.stCommitRegs.stHdr10InfoFrm.u32Len;
    pstWinXdrFrm->stDolbyInfo.u32UpMdLen = stParaOut.stCommitRegs.stUpdateMetadata.u32Len;
    pstWinXdrFrm->stDolbyInfo.u32TotalLen = stParaOut.stCommitRegs.u32TotalLen;

    /**Judge whether the length is valid.**/
    if (stDolbyBuf.bufsize < pstWinXdrFrm->stDolbyInfo.u32TotalLen)
    {
        HI_ERR_WIN("metadata buffer size is too small!\n");
        return HI_ERR_VO_WIN_UNSUPPORT;
    }

    if (src_video_dolby_yuv == stParaIn.stSrcVideoInfo.video_type)
    {
        pstWinXdrFrm->stBaseFrm.unHDRInfo.stDolbyInfo.bCompatible = HI_TRUE;
    }
    else
    {
        pstWinXdrFrm->stBaseFrm.unHDRInfo.stDolbyInfo.bCompatible = HI_FALSE;
    }

    return HI_SUCCESS;
}

#endif

/* get xdr engine and output type according to source type and system abilities.  */
HI_S32 HI_MPI_WIN_GetXdrOutputTypeAndEngine(HI_HANDLE  hWindow,
                                            HI_DRV_VIDEO_FRAME_TYPE_E enFrmType,
                                            HI_DRV_DISP_OUT_TYPE_E *penOutputType,
                                            HI_DRV_DISP_XDR_ENGINE_E *penXdrEngine)
{
    HI_S32 s32Ret = HI_SUCCESS;
    WIN_OUT_TYPE_AND_ENGINE_S stWinOutTypeAndEngine;

    CHECK_VO_NULL_PTR(penOutputType);
    CHECK_VO_NULL_PTR(penXdrEngine);

    memset((HI_VOID *)&stWinOutTypeAndEngine, 0x0, sizeof(stWinOutTypeAndEngine));

    if (HI_DRV_VIDEO_FRAME_TYPE_BUTT <= enFrmType)
    {
        HI_ERR_WIN("Invalid frame type->[%d].\n",enFrmType);
        return HI_ERR_VO_INVALID_PARA;
    }

    stWinOutTypeAndEngine.hWindow   = hWindow;
    stWinOutTypeAndEngine.enFrmType = enFrmType;
    stWinOutTypeAndEngine.enDispOutType = HI_DRV_DISP_TYPE_NORMAL;
    stWinOutTypeAndEngine.enXdrEngine = DRV_XDR_ENGINE_BUTT;
    /* get output type and support engine. */
    s32Ret = ioctl(g_VoDevFd, CMD_WIN_GET_OUT_TYPE_AND_ENGINE, &stWinOutTypeAndEngine);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_WIN("Fail to get output type and engine.\n");
        return s32Ret;
    }


    *penOutputType = stWinOutTypeAndEngine.enDispOutType;
    *penXdrEngine  = stWinOutTypeAndEngine.enXdrEngine;

    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_GenerateFrmCfg(WIN_XDR_FRAME_S *pstWinXdrFrame)
{
    HI_S32 s32Ret = HI_SUCCESS;

    CHECK_VO_NULL_PTR(pstWinXdrFrame);

    /* step1. get output and engine type from driver strategy. */
    s32Ret = HI_MPI_WIN_GetXdrOutputTypeAndEngine(pstWinXdrFrame->hWindow,\
                                                  pstWinXdrFrame->stBaseFrm.enSrcFrameType,\
                                                  &pstWinXdrFrame->enDispOutType,\
                                                  &pstWinXdrFrame->enXdrEngine);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_WIN("Get output type and engine fail.\n");
        return s32Ret;
    }

    if ((DRV_XDR_ENGINE_BUTT <= pstWinXdrFrame->enXdrEngine)
        || (DRV_XDR_ENGINE_AUTO == pstWinXdrFrame->enXdrEngine))
    {
        HI_ERR_WIN("Can not find valid xdr engine.\n");
        return HI_FAILURE;
    }

    if (DRV_XDR_ENGINE_DOLBY != pstWinXdrFrame->enXdrEngine)
    {
        return HI_SUCCESS;
    }

#ifdef HI_HDR_DOLBYVISION_SUPPORT
     /* step2. if use dolby engine, let dolby lib process this frame. */
    s32Ret = HI_MPI_WIN_DolbyLibProcess(pstWinXdrFrame);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_WIN("DolbyLib process fail.\n");
        return s32Ret;
    }
#endif

    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_QueueFrame(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pFrame)
{
    HI_S32                Ret = HI_SUCCESS;
    WIN_XDR_FRAME_S       stWinXdrFrame;

    memset(&stWinXdrFrame, 0x0, sizeof(stWinXdrFrame));

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (!pFrame)
    {
        HI_ERR_WIN("para pFrameinfo is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    CHECK_VO_INIT();

    stWinXdrFrame.hWindow = hWindow;
    stWinXdrFrame.bEnhanceValid = HI_FALSE;
    stWinXdrFrame.stBaseFrm = *pFrame;

#ifdef HI_NVR_SUPPORT
    stWinXdrFrame.enDispOutType = HI_DRV_DISP_TYPE_NORMAL;
    stWinXdrFrame.enXdrEngine = DRV_XDR_ENGINE_SDR;
#else

    Ret = HI_MPI_WIN_GenerateFrmCfg(&stWinXdrFrame);
    if (HI_SUCCESS != Ret)
    {
        return Ret;
    }

#endif
    Ret = ioctl(g_VoDevFd, CMD_WIN_QU_FRAME, &stWinXdrFrame);

    return Ret;
}

HI_S32 HI_MPI_WIN_QueueDolbyFrame(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S* pBLFrm, HI_DRV_VIDEO_FRAME_S* pELFrm)
{
#ifdef HI_HDR_DOLBYVISION_SUPPORT
    HI_S32             Ret = HI_SUCCESS;
    WIN_XDR_FRAME_S    stWinXdrFrame;

    memset(&stWinXdrFrame, 0x0, sizeof(WIN_XDR_FRAME_S));

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (HI_NULL == pBLFrm)
    {
        HI_ERR_WIN("para pBLFrminfo is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    CHECK_VO_INIT();

    if (HI_DRV_VIDEO_FRAME_TYPE_DOLBY_BL != pBLFrm->enSrcFrameType)
    {
        return HI_MPI_WIN_QueueFrame(hWindow, pBLFrm);
    }

    stWinXdrFrame.hWindow = hWindow;
    stWinXdrFrame.stBaseFrm = *pBLFrm;
    if (HI_NULL != pELFrm)
    {
        stWinXdrFrame.bEnhanceValid = HI_TRUE;
        stWinXdrFrame.stEnhanceFrm = *pELFrm;
    }
    else
    {
        stWinXdrFrame.bEnhanceValid = HI_FALSE;

    }

    Ret = HI_MPI_WIN_GenerateFrmCfg(&stWinXdrFrame);
    if (HI_SUCCESS != Ret)
    {
        return Ret;
    }

    Ret = ioctl(g_VoDevFd, CMD_WIN_QUDOLBY_FRAME, &stWinXdrFrame);

    return Ret;
#else
    HI_ERR_WIN("Don't supprt Dolby Frame\n");
    return HI_ERR_VO_WIN_UNSUPPORT;
#endif
}


HI_S32 HI_MPI_WIN_QueueUselessFrame(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pFrame)
{
    HI_S32             Ret;
    WIN_FRAME_S     VoWinFrame;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (!pFrame)
    {
        HI_ERR_WIN("para pFrameinfo is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    CHECK_VO_INIT();

    VoWinFrame.hWindow = hWindow;
    VoWinFrame.stFrame = *pFrame;

    Ret = ioctl(g_VoDevFd, CMD_WIN_QU_ULSFRAME, &VoWinFrame);

    return Ret;
}



HI_S32 HI_MPI_WIN_Reset(HI_HANDLE hWindow, HI_DRV_WIN_SWITCH_E enWinFreezeMode)
{
    WIN_RESET_S   VoWinReset;
    HI_S32 Ret;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (enWinFreezeMode >= HI_DRV_WIN_SWITCH_BUTT)
    {
        HI_ERR_WIN("para enWinFreezeMode is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    VoWinReset.hWindow = hWindow;
    VoWinReset.eMode = enWinFreezeMode;

    Ret = ioctl(g_VoDevFd, CMD_WIN_RESET, &VoWinReset);

    return Ret;
}

HI_S32 HI_MPI_WIN_Pause(HI_HANDLE hWindow, HI_BOOL bEnable)
{
    WIN_PAUSE_S   VoWinPause;
    HI_S32           Ret;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if ((bEnable != HI_TRUE)
      &&(bEnable != HI_FALSE)
       )
    {
        HI_ERR_WIN("para bEnable is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    VoWinPause.hWindow = hWindow;
    VoWinPause.bEnable = bEnable;

    Ret = ioctl(g_VoDevFd, CMD_WIN_PAUSE, &VoWinPause);

    return Ret;
}


HI_S32 HI_MPI_VO_GetWindowDelay(HI_HANDLE hWindow, HI_DRV_WIN_PLAY_INFO_S *pDelay)
{
    WIN_PLAY_INFO_S   VoWinDelay;
    HI_S32 Ret;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (!pDelay)
    {
        HI_ERR_WIN("para pDelay is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    CHECK_VO_INIT();

    VoWinDelay.hWindow = hWindow;

    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_PLAY_INFO, &VoWinDelay);
    if (HI_SUCCESS == Ret)
    {
        *pDelay = VoWinDelay.stPlayInfo;
    }

    return Ret;
}

HI_S32 HI_MPI_WIN_SetStepMode(HI_HANDLE hWindow, HI_BOOL bStepMode)
{
    HI_S32              Ret;
    WIN_STEP_MODE_S  WinStepMode;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    WinStepMode.hWindow = hWindow;
    WinStepMode.bStep = bStepMode;

    Ret = ioctl(g_VoDevFd, CMD_WIN_STEP_MODE, &WinStepMode);

    return Ret;
}

HI_S32 HI_MPI_WIN_SetStepPlay(HI_HANDLE hWindow)
{
    HI_S32      Ret;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    Ret = ioctl(g_VoDevFd, CMD_WIN_STEP_PLAY, &hWindow);

    return Ret;
}

HI_S32 HI_MPI_VO_DisableDieMode(HI_HANDLE hWindow)
{
    return HI_FAILURE;
}

HI_S32 HI_MPI_WIN_SetExtBuffer(HI_HANDLE hWindow, HI_DRV_VIDEO_BUFFER_POOL_S* pstBufAttr)
{
    HI_S32      Ret;
    WIN_BUF_POOL_S  bufferAttr;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_NULL_PTR(pstBufAttr);
    CHECK_VO_INIT();

    bufferAttr.hwin = hWindow;
    bufferAttr.stBufPool = *pstBufAttr;

    Ret = ioctl(g_VoDevFd, CMD_WIN_VIR_EXTERNBUF, &bufferAttr);

    return Ret;
}

HI_S32 HI_MPI_WIN_SetQuickOutput(HI_HANDLE hWindow, HI_BOOL bEnable)
{
    WIN_SET_QUICK_S stQuickOutputAttr;
    HI_S32      Ret = HI_FAILURE;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    stQuickOutputAttr.hWindow = hWindow;
    stQuickOutputAttr.bQuickEnable = bEnable;

    Ret = ioctl(g_VoDevFd, CMD_WIN_SET_QUICK, &stQuickOutputAttr);

    return Ret;
}

HI_S32 HI_MPI_WIN_GetQuickOutputStatus(HI_HANDLE hWindow, HI_BOOL *bQuickOutputEnable)
{
    WIN_SET_QUICK_S stQuickOutputAttr;
    HI_S32      Ret = HI_FAILURE;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }
    CHECK_VO_NULL_PTR(bQuickOutputEnable);
    CHECK_VO_INIT();

    stQuickOutputAttr.hWindow = hWindow;

    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_QUICK, &stQuickOutputAttr);
    if (Ret == HI_SUCCESS)
    {
        *bQuickOutputEnable = stQuickOutputAttr.bQuickEnable;
    }

    return Ret;
}

HI_S32 HI_MPI_VO_UseDNRFrame(HI_HANDLE hWindow, HI_BOOL bEnable)
{
    return HI_FAILURE;
}

#define STRIDE_ALIGN_NUM 15
HI_S32 HI_MPI_VO_CapturePictureExt(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pstCapPicture)
{
    HI_S32            Ret = HI_SUCCESS;
    WIN_CAPTURE_S     VoWinCapture;
    HI_U32   height = 0;
#if HI_VDP_VIDEO_LINEDCMP
    HI_U32 i = 0,y_stride = 0;
    HI_U32          OriginFrameSize = 0, DcmpOutputBufSize = 0;
    HI_UCHAR        *DecompressOutBuf = HI_NULL, *DecompressInBuf = HI_NULL;
    HI_UCHAR        *Inptr = HI_NULL, *Outptr = HI_NULL;
#endif
    HI_DRV_PIX_FORMAT_E  ePixFormat_Out = HI_DRV_PIX_BUTT;

    CHECK_VO_INIT();
    if ((HI_INVALID_HANDLE == hWindow) || (!pstCapPicture))
    {
        HI_ERR_WIN(" invalid param.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    /*first,  we get a frame from the window.*/
    VoWinCapture.hWindow = hWindow;
    Ret = ioctl(g_VoDevFd, CMD_VO_WIN_CAPTURE_START, &VoWinCapture);
    if (Ret != HI_SUCCESS)
        return Ret;

    height = VoWinCapture.CapPicture.u32Height;

#if HI_VDP_VIDEO_LINEDCMP
    y_stride = VoWinCapture.CapPicture.stBufAddr[0].u32Stride_Y;

    if (0 == y_stride)
    {
        HI_ERR_WIN("Stride_Y is 0\r\n");
        goto ret_err;
    }

    if (HI_DRV_PIX_FMT_NV21 == VoWinCapture.CapPicture.ePixFormat)
    {
        OriginFrameSize = height * y_stride * 3 / 2 + height * 4;
    }
    else if (HI_DRV_PIX_FMT_NV21_CMP == VoWinCapture.CapPicture.ePixFormat)
    {
        OriginFrameSize = height * y_stride * 3 / 2 + 16 * height * 3 / 2;
    }
    else  if (HI_DRV_PIX_FMT_NV61_2X1 == VoWinCapture.CapPicture.ePixFormat)
    {
        OriginFrameSize = height * y_stride * 2 + height * 4;
    }
    else
    {
        HI_ERR_WIN("pixel fmt not supported %d.\n",VoWinCapture.CapPicture.ePixFormat);
        goto ret_err;
    }

    DcmpOutputBufSize = VoWinCapture.driver_supply_addr.length;

    if (OriginFrameSize > VDP_MEM_MAX)
    {
        HI_ERR_WIN("the length of mmap is too big.\n");
        goto ret_err;
    }

    DecompressInBuf = (HI_UCHAR *)HI_MMZ_Map(VoWinCapture.CapPicture.stBufAddr[0].u32PhyAddr_Y, HI_FALSE);

    if (HI_NULL == DecompressInBuf)
    {
        HI_ERR_WIN("DecompressInBuf buffer map fail\r\n");
        goto ret_err;
    }

    if (DcmpOutputBufSize > VDP_MEM_MAX)
    {
        HI_ERR_WIN("the length of mmap is too big.\n");

        (HI_VOID)HI_MMZ_Unmap(VoWinCapture.CapPicture.stBufAddr[0].u32PhyAddr_Y);

        goto ret_err;
    }

    DecompressOutBuf = (HI_UCHAR *)HI_MMZ_Map(VoWinCapture.driver_supply_addr.startPhyAddr, HI_FALSE);

    if (HI_NULL == DecompressOutBuf)
    {
        Ret = HI_MMZ_Unmap(VoWinCapture.CapPicture.stBufAddr[0].u32PhyAddr_Y);

        if (HI_SUCCESS != Ret)
        {
            HI_ERR_WIN("decompress buffer unmap fail\r\n");
        }
        goto ret_err;
    }

    /*third  step, we make a decompress or simple copy from driver-vpss frame to user frame.*/
    Inptr = DecompressInBuf;
    Outptr = DecompressOutBuf;

    if ( HI_DRV_PIX_FMT_NV21_CMP == VoWinCapture.CapPicture.ePixFormat)
    {
    #ifdef HI_VDP_VIDEO_LINEDCMP
        (HI_VOID)Dcmp_Func(&VoWinCapture.CapPicture,
                           DcmpOutputBufSize,
                           Inptr,
                           Outptr);

        ePixFormat_Out = HI_DRV_PIX_FMT_NV21;
    #endif
    }
    else
    {
        ePixFormat_Out = VoWinCapture.CapPicture.ePixFormat;

        for(i = 0 ; i < OriginFrameSize / y_stride; i++)
        {
            memcpy(Outptr, Inptr, y_stride);
            Inptr += y_stride;
            Outptr += y_stride;
        }
    }

    Ret = HI_MMZ_Unmap(VoWinCapture.CapPicture.stBufAddr[0].u32PhyAddr_Y);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_WIN("decompress buffer unmap fail\r\n");

        Ret = HI_MMZ_Unmap(VoWinCapture.driver_supply_addr.startPhyAddr);
        goto ret_err;
    }

    Ret = HI_MMZ_Unmap(VoWinCapture.driver_supply_addr.startPhyAddr);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_WIN("decompress buffer unmap fail\r\n");
        goto ret_err;
    }

#else
    ePixFormat_Out = HI_DRV_PIX_FMT_NV21;
#endif


    Ret = ioctl(g_VoDevFd, CMD_VO_WIN_CAPTURE_RELEASE, &VoWinCapture);
    if (Ret != HI_SUCCESS)
        return Ret;

    *pstCapPicture = VoWinCapture.CapPicture;
    /*FIXME: we should know how the 3d will be dealed with*/
    pstCapPicture->stBufAddr[0].u32PhyAddr_Y = VoWinCapture.driver_supply_addr.startPhyAddr;

    pstCapPicture->stBufAddr[0].u32PhyAddr_C =
        pstCapPicture->stBufAddr[0].u32PhyAddr_Y +  height *pstCapPicture->stBufAddr[0].u32Stride_Y;

    pstCapPicture->ePixFormat  = ePixFormat_Out;

    return HI_SUCCESS;

#if HI_VDP_VIDEO_LINEDCMP
ret_err:

    Ret = ioctl(g_VoDevFd, CMD_VO_WIN_CAPTURE_RELEASE, &VoWinCapture);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }
    return HI_FAILURE;
#endif
}


HI_S32 HI_MPI_WIN_CapturePicture(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pstCapPicture)
{
    HI_S32            Ret = HI_SUCCESS;

    Ret = HI_MPI_VO_CapturePictureExt(hWindow, pstCapPicture);
    return Ret;
}


HI_S32 HI_MPI_WIN_CapturePictureRelease(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pstCapPicture)
{
    HI_S32          Ret = HI_SUCCESS;
    WIN_CAPTURE_S   VoWinRls;

    CHECK_VO_INIT();
    if ((HI_INVALID_HANDLE == hWindow) || (!pstCapPicture))
    {
        HI_ERR_WIN("invalid  param.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    VoWinRls.hWindow = hWindow;
    VoWinRls.CapPicture = *pstCapPicture;
    VoWinRls.driver_supply_addr.startPhyAddr = pstCapPicture->stBufAddr[0].u32PhyAddr_Y;

    Ret = ioctl(g_VoDevFd, CMD_VO_WIN_CAPTURE_FREE, &VoWinRls);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_CapturePictureRelease fail (INVALID_PARA)\r\n");
        return Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_SetRotation(HI_HANDLE hWindow, HI_DRV_ROT_ANGLE_E enRotation)
{
    HI_S32          Ret = HI_SUCCESS;
    WIN_ROTATION_S  VoWinRotation;

    if (enRotation >= HI_DRV_ROT_ANGLE_BUTT)
    {
        HI_ERR_WIN("invalid  param.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    VoWinRotation.hWindow = hWindow;
    VoWinRotation.enRotation = enRotation;
    Ret = ioctl(g_VoDevFd, CMD_WIN_SET_ROTATION, &VoWinRotation);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_SetRotation fail \r\n");
        return Ret;
    }
    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_GetRotation(HI_HANDLE hWindow, HI_DRV_ROT_ANGLE_E *penRotation)
{
    HI_S32          Ret = HI_SUCCESS;
    WIN_ROTATION_S  VoWinRotation;

    CHECK_VO_NULL_PTR(penRotation);
    memset(&VoWinRotation, 0x0, sizeof(VoWinRotation));

    VoWinRotation.hWindow = hWindow;
    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_ROTATION, &VoWinRotation);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_GetRotation fail \r\n");
        return Ret;
    }
    *penRotation = VoWinRotation.enRotation;
    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_SetFlip(HI_HANDLE hWindow, HI_BOOL bHoriFlip, HI_BOOL bVertFlip)
{
    HI_S32          Ret = HI_SUCCESS;
    WIN_FLIP_S  VoWinFlip;
    VoWinFlip.hWindow = hWindow;
    VoWinFlip.bHoriFlip = bHoriFlip;
    VoWinFlip.bVertFlip = bVertFlip;
    Ret = ioctl(g_VoDevFd, CMD_WIN_SET_FLIP, &VoWinFlip);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_SetFlip fail \r\n");
        return Ret;
    }
    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_GetFlip(HI_HANDLE hWindow, HI_BOOL *pbHoriFlip, HI_BOOL *pbVertFlip)
{
    HI_S32          Ret = HI_SUCCESS;
    WIN_FLIP_S  VoWinFlip;

    CHECK_VO_NULL_PTR(pbHoriFlip);
    CHECK_VO_NULL_PTR(pbVertFlip);

    VoWinFlip.hWindow = hWindow;
    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_FLIP, &VoWinFlip);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_GetRotation fail \r\n");
        return Ret;
    }
    *pbHoriFlip = VoWinFlip.bHoriFlip;
    *pbVertFlip = VoWinFlip.bVertFlip;
    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_SetMode(HI_HANDLE hWindow, HI_DRV_WINDOW_MODE_E enWinMode)
{
    HI_S32        Ret = HI_SUCCESS;
    WIN_MODE_S    VoWinMode;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("param hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if(enWinMode >= HI_DRV_WINDOW_MODE_BUTT)
    {
        HI_ERR_WIN("param enWinMode is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    VoWinMode.hWindow = hWindow;
    VoWinMode.enWinMode = enWinMode;
    Ret = ioctl(g_VoDevFd, CMD_WIN_SET_MODE, &VoWinMode);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_SetMode fail.\n");
        return Ret;
    }
    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_CloseHdrPath(HI_HANDLE hWindow, HI_BOOL bEnable)
{
    HI_S32          Ret = HI_SUCCESS;
    WIN_ENABLE_S    stWinHdrEnable;
    stWinHdrEnable.hWindow = hWindow;
    stWinHdrEnable.bEnable = bEnable;

    Ret = ioctl(g_VoDevFd, CMD_WIN_CLOSE_HDR_PATH, &stWinHdrEnable);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_CloseHdrPath fail \r\n");
        return Ret;
    }
    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_SetDolbyLibInfo(WIN_DOLBY_LIB_INFO_S *pstDolbyLibInfo)
{
    HI_S32  Ret = HI_SUCCESS;

    CHECK_VO_NULL_PTR(pstDolbyLibInfo);

    Ret = ioctl(g_VoDevFd, CMD_WIN_SET_DOLBY_LIB_STATUS, pstDolbyLibInfo);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_SetDolbyLibInfo fail \r\n");
        return Ret;
    }

    return HI_SUCCESS;
}

HI_S32  HI_MPI_WIN_Debug(WIN_DEBUG_CMD_AND_ARGS_S *pstWinDebugCmdAndArgs)
{
    HI_S32                    Ret = HI_SUCCESS;

    if(HI_NULL == pstWinDebugCmdAndArgs)
    {
        return HI_ERR_VO_NULL_PTR;
    }

    if (pstWinDebugCmdAndArgs->enDebugCmd >= WIN_DEBUG_CMD_BUTT)
    {
        HI_ERR_WIN("param pstWinDebugCmdAndArgs->enDebugCmd is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    Ret = ioctl(g_VoDevFd, CMD_WIN_DEBUG, pstWinDebugCmdAndArgs);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_Debug fail \r\n");
        return Ret;
    }
    return HI_SUCCESS;
}

#if 0
HI_S32 HI_MPI_VO_SetWindowExtAttr(HI_HANDLE hWindow, VO_WIN_EXTATTR_E detType, HI_BOOL bEnable)
{
    HI_S32      Ret;
    VO_WIN_DETECT_S stDetType;
    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();
    stDetType.hWindow = hWindow;
    stDetType.detType = detType;
    stDetType.bEnable = bEnable;
    Ret = ioctl(g_VoDevFd, CMD_VO_SET_DET_MODE, &stDetType);

    return Ret;
}

HI_S32 HI_MPI_VO_GetWindowExtAttr(HI_HANDLE hWindow, VO_WIN_EXTATTR_E detType, HI_BOOL *bEnable)
{
    HI_S32      Ret;
    VO_WIN_DETECT_S stDetType;
    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }
    CHECK_VO_INIT();

    stDetType.hWindow = hWindow;
    stDetType.detType = detType;
    Ret = ioctl(g_VoDevFd, CMD_VO_GET_DET_MODE, &stDetType);
    *bEnable = stDetType.bEnable;

    return Ret;
}
#endif

HI_S32 HI_MPI_WIN_Suspend(HI_VOID)
{
    HI_U32 u32Value = 0;
    HI_S32 Ret;

    CHECK_VO_INIT();

    Ret = ioctl(g_VoDevFd, CMD_WIN_SUSPEND, &u32Value);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_Suspend failed\n");
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_Resume(HI_VOID)
{
    HI_U32 u32Value = 0;
    HI_S32 Ret;

    CHECK_VO_INIT();

    Ret = ioctl(g_VoDevFd, CMD_WIN_RESUM, &u32Value);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_Resume failed\n");
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_GetHandle(WIN_GET_HANDLE_S *pstWinHandle)
{
    HI_S32 Ret;

    CHECK_VO_NULL_PTR(pstWinHandle);
    CHECK_VO_INIT();

    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_HANDLE, pstWinHandle);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_GetHandle failed\n");
    }

    return Ret;
}


HI_S32 HI_MPI_WIN_AttachWinSink(HI_HANDLE hWin, HI_HANDLE hSink)
{
    HI_S32      Ret;
    WIN_ATTACH_S stAttach;

    if (HI_INVALID_HANDLE == hWin)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    stAttach.enType = ATTACH_TYPE_SINK;
    stAttach.hWindow = hWin;
    stAttach.hMutual = hSink;

    Ret = ioctl(g_VoDevFd, CMD_WIN_ATTACH, &stAttach);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_AttachSink failed\n");
    }

    return Ret;
}

HI_S32 HI_MPI_WIN_DetachWinSink(HI_HANDLE hWin, HI_HANDLE hSink)
{
    HI_S32      Ret;
    WIN_ATTACH_S stAttach;

    if (HI_INVALID_HANDLE == hWin)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    stAttach.enType = ATTACH_TYPE_SINK;
    stAttach.hWindow = hWin;
    stAttach.hMutual = hSink;

    Ret = ioctl(g_VoDevFd, CMD_WIN_DETACH, &stAttach);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_DetachSink failed\n");
    }

    return Ret;
}


HI_S32 HI_MPI_WIN_GetLatestFrameInfo(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S  *frame_info)
{
    HI_S32      Ret;
    WIN_FRAME_S frame_struct;

    if (HI_INVALID_HANDLE == hWin)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_NULL_PTR(frame_info);
    CHECK_VO_INIT();

    frame_struct.hWindow = hWin;

    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_LATESTFRAME_INFO, &frame_struct);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("get latest frame info failed\n");
        return Ret;
    }

    *frame_info  = frame_struct.stFrame;
    return Ret;
}

HI_S32 HI_MPI_WIN_GetUnloadTimes(HI_HANDLE hWin, HI_U32 *pu32Time)
{
    HI_S32      Ret;
    WIN_UNLOAD_S stWinUnload;

    if (HI_INVALID_HANDLE == hWin)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_NULL_PTR(pu32Time);
    CHECK_VO_INIT();

    stWinUnload.hWindow = hWin;

    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_UNLOAD, &stWinUnload);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("get latest frame info failed\n");
        return Ret;
    }

    *pu32Time  = stWinUnload.u32Times;
    return Ret;
}

#if defined(CHIP_TYPE_hi3798mv100)\
        || defined(CHIP_TYPE_hi3796mv100)

#define VDEC_CAPABILITY_WIDTH   3840
#define VDEC_CAPABILITY_HEIGHT  2160

#elif defined(CHIP_TYPE_hi3798mv200)\
        || defined(CHIP_TYPE_hi3798mv300)\
        || defined(CHIP_TYPE_hi3798mv310)\
        || defined(CHIP_TYPE_hi3796mv200)\
        || defined(CHIP_TYPE_hi3716mv450)\
        || defined(CHIP_TYPE_hi3798cv100)\
        || defined(CHIP_TYPE_hi3798cv200)

#define VDEC_CAPABILITY_WIDTH   4096
#define VDEC_CAPABILITY_HEIGHT  2304

#else
#define VDEC_CAPABILITY_WIDTH   0
#define VDEC_CAPABILITY_HEIGHT  0
#endif

static HI_S32 MPI_WIN_GetVdecAbility(HI_CHIP_TYPE_E enChipType,
        HI_U32 *pu32WidthMax,
        HI_U32 *pu32HeightMax)
{
    HI_S32 s32Ret = HI_SUCCESS;

    CHECK_VO_NULL_PTR(pu32WidthMax);
    CHECK_VO_NULL_PTR(pu32HeightMax);

    if (enChipType >= HI_CHIP_TYPE_BUTT)
    {
        HI_ERR_WIN("param enChipType is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    *pu32WidthMax = VDEC_CAPABILITY_WIDTH;
    *pu32HeightMax = VDEC_CAPABILITY_HEIGHT;

    return s32Ret;
}


HI_S32 HI_MPI_WIN_CalMediaRect(HI_CHIP_TYPE_E enChipType,
                              HI_RECT_S stStreamRect,
                              HI_RECT_S *pstMediaRect)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32OriW = 0,u32OriH = 0;
    HI_U32 u32DstW = 0,u32DstH = 0;
    HI_U32 u32WidthLevel = 0, u32HeightLevel = 0;

    CHECK_VO_NULL_PTR(pstMediaRect);

    if (enChipType >= HI_CHIP_TYPE_BUTT)
    {
        HI_ERR_WIN("param enChipType is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    u32OriW = (HI_U32)stStreamRect.s32Width;
    u32OriH = (HI_U32)stStreamRect.s32Height;

    s32Ret = MPI_WIN_GetVdecAbility(enChipType,&u32WidthLevel,&u32HeightLevel);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_WIN("Can't get Width/Height Level\n");
        return s32Ret;
    }

    if(u32OriW < u32WidthLevel && u32OriH < u32HeightLevel)
    {
        u32DstW = u32OriW;
        u32DstH = u32OriH;
    }
    else
    {
        HI_U32 u32RatioW;
        HI_U32 u32RatioH;
        HI_U32 u32TmpH;
        HI_U32 u32TmpW;

        if (u32OriW >= u32WidthLevel && u32OriH >= u32HeightLevel)
        {
            u32DstW = u32WidthLevel;
            u32DstH = u32HeightLevel;
        }
        else
        {
            if (0 == u32WidthLevel || 0 == u32HeightLevel)
            {
                HI_FATAL_WIN("Denominator may be zero !\n");
                return HI_FAILURE;
            }
            u32RatioW = u32OriW*2048/u32WidthLevel;
            u32RatioH = u32OriH*2048/u32HeightLevel;

            if (0 == u32RatioW || 0 == u32RatioH )
            {
                HI_FATAL_WIN("Denominator may be zero !\n");
                return HI_FAILURE;
            }

            if (u32RatioW > u32RatioH)
            {
                u32TmpW = u32OriW*2048/u32RatioW;
                u32TmpH = u32OriH*2048/u32RatioW;
            }
            else
            {
                u32TmpW = u32OriW*2048/u32RatioH;
                u32TmpH = u32OriH*2048/u32RatioH;
            }

            u32TmpW = u32TmpW & 0xfffffffe;
            u32TmpH = u32TmpH & 0xfffffffc;

            u32DstW = u32TmpW;
            u32DstH = u32TmpH;
        }
    }

    pstMediaRect->s32Height = (HI_S32)u32DstH;
    pstMediaRect->s32Width = (HI_S32)u32DstW;

    return s32Ret;
}

HI_S32 HI_MPI_WIN_CalAspectRegion(HI_MPI_WIN_RATIO_PARA_S stInPara,HI_RECT_S *pstRevisedRect)
{
    HI_S32 s32Ret;

    ALG_RATIO_OUT_PARA_S stOutPara;
    ALG_RATIO_IN_PARA_S stInRatioPara;

    CHECK_VO_NULL_PTR(pstRevisedRect);

    if (stInPara.eAspMode >= HI_DRV_ASP_RAT_MODE_BUTT)
    {
        HI_ERR_WIN("param stInPara.eAspMode is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    stInRatioPara.SrcImgH = stInPara.SrcImgH;
    stInRatioPara.SrcImgW = stInPara.SrcImgW;
    stInRatioPara.DeviceWidth = stInPara.DeviceWidth;
    stInRatioPara.DeviceHeight = stInPara.DeviceHeight;
    stInRatioPara.eAspMode = stInPara.eAspMode;
    stInRatioPara.stOutWnd = stInPara.stOutWnd;
    stInRatioPara.stInWnd = stInPara.stInWnd;

    if (stInRatioPara.stInWnd.s32Width != stInRatioPara.SrcImgW
        || stInRatioPara.stInWnd.s32Height != stInRatioPara.SrcImgH)
    {
        if (0 == stInPara.stInWnd.s32Width || 0 == stInPara.stInWnd.s32Height)
        {
            HI_FATAL_WIN("Denominator may be zero !\n");
            return HI_FAILURE;
        }
        stInRatioPara.AspectWidth =
            stInPara.AspectWidth*stInPara.SrcImgW/stInPara.stInWnd.s32Width;
        stInRatioPara.AspectHeight =
            stInPara.AspectHeight*stInPara.SrcImgH/stInPara.stInWnd.s32Height;

        stInRatioPara.SrcImgW = stInPara.stInWnd.s32Width;
        stInRatioPara.SrcImgH = stInPara.stInWnd.s32Height;
    }
    else
    {
        stInRatioPara.AspectWidth = stInPara.AspectWidth;
        stInRatioPara.AspectHeight = stInPara.AspectHeight;
    }

    stInRatioPara.stScreen = stInPara.stScreen;
    stInRatioPara.stUsrAsp.bUserDefAspectRatio = HI_FALSE;

    if (stInPara.eAspMode == HI_DRV_ASP_RAT_MODE_FULL)
    {
        stOutPara.stOutWnd.s32X = stInPara.stOutWnd.s32X;
        stOutPara.stOutWnd.s32Y = stInPara.stOutWnd.s32Y;
        stOutPara.stOutWnd.s32Width = stInPara.stOutWnd.s32Width;
        stOutPara.stOutWnd.s32Height = stInPara.stOutWnd.s32Height;
    }
    else if (stInPara.eAspMode == HI_DRV_ASP_RAT_MODE_LETTERBOX)
    {
        s32Ret = WIN_RATIO_GetAspCfg(&stOutPara,&stInRatioPara);
        if (s32Ret != HI_SUCCESS)
        {
            HI_FATAL_WIN("GetAspCfg Failed\n");
        }
    }
    else
    {
        stOutPara.stOutWnd.s32X = stInPara.stOutWnd.s32X;
        stOutPara.stOutWnd.s32Y = stInPara.stOutWnd.s32Y;
        stOutPara.stOutWnd.s32Width = stInPara.stOutWnd.s32Width;
        stOutPara.stOutWnd.s32Height = stInPara.stOutWnd.s32Height;
        HI_FATAL_WIN("Invalid aspect mode %d\n",stInPara.eAspMode);
    }

    pstRevisedRect->s32X = stOutPara.stOutWnd.s32X;
    pstRevisedRect->s32Y = stOutPara.stOutWnd.s32Y;
    pstRevisedRect->s32Width = stOutPara.stOutWnd.s32Width;
    pstRevisedRect->s32Height  = stOutPara.stOutWnd.s32Height;

    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_SetFrostGlassLevel(HI_HANDLE hWindow, HI_DRV_WINDOW_FROST_E eFrostMode)
{
    HI_S32 s32Ret = HI_FAILURE;
    WIN_FROST_MODE_S   stWinFrostMode = {0};

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (HI_DRV_WINDOW_FROST_BUTT <= eFrostMode)
    {
        HI_ERR_WIN("para eFrostMode is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    stWinFrostMode.hWindow = hWindow;
    stWinFrostMode.eFrostMode = eFrostMode;

    s32Ret = ioctl(g_VoDevFd, CMD_WIN_SET_FROST_MODE, &stWinFrostMode);

    return s32Ret;
}

HI_S32 HI_MPI_WIN_GetFrostGlassLevel(HI_HANDLE hWindow, HI_DRV_WINDOW_FROST_E *peFrostMode)
{
    HI_S32 s32Ret = HI_FAILURE;
    WIN_FROST_MODE_S   stWinFrostMode = {0};

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (!peFrostMode)
    {
        HI_ERR_WIN("para peFrostMode is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    CHECK_VO_INIT();

    stWinFrostMode.hWindow = hWindow;

    s32Ret = ioctl(g_VoDevFd, CMD_WIN_GET_FROST_MODE, &stWinFrostMode);
    if (s32Ret != HI_SUCCESS)
    {
        return s32Ret;
    }

    *peFrostMode = stWinFrostMode.eFrostMode;

    return s32Ret;
}

HI_S32 HI_MPI_VO_SetWindowAlpha(HI_HANDLE hWindow, HI_U32 u32Alpha)
{
    WIN_ALPHA_S stWinAlpha;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    stWinAlpha.hWindow = hWindow;
    stWinAlpha.u32Alpha = u32Alpha;

    return ioctl(g_VoDevFd, CMD_WIN_SET_ALPHA, &stWinAlpha);
}

HI_S32 HI_MPI_VO_GetWindowAlpha(HI_HANDLE hWindow, HI_U32 *pu32Alpha)
{
    WIN_ALPHA_S stWinAlpha;
    HI_S32 s32Ret = HI_FAILURE;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_NULL_PTR(pu32Alpha);

    CHECK_VO_INIT();

    stWinAlpha.hWindow = hWindow;

    s32Ret = ioctl(g_VoDevFd, CMD_WIN_GET_ALPHA, &stWinAlpha);
    if (s32Ret != HI_SUCCESS)
    {
        return s32Ret;
    }

    *pu32Alpha = stWinAlpha.u32Alpha;

    return s32Ret;
}

HI_S32 HI_MPI_WIN_ResetFirstFrmStatus(HI_HANDLE hWindow)
{
    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    return ioctl(g_VoDevFd, CMD_WIN_RESET_FIRST_FRAME_STATUS, &hWindow);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

