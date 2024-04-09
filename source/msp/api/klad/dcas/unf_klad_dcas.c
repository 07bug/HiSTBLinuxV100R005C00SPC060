/******************************************************************************

Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : unf_klad_dcas.c
Version       : Initial
Author        : Hisilicon hisecurity team
Created       : 2017-03-21
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include <errno.h>
#include <sys/ioctl.h>
#include <string.h>
#include "hi_debug.h"
#include "hi_type.h"
#include "hi_error_mpi.h"
#include "drv_klad_ioctl.h"
#include "hi_unf_klad_dcas.h"
#include "hi_drv_klad.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


extern HI_S32 g_klad_init_nm;
extern HI_S32 g_klad_fd;

HI_S32 HI_UNF_KLAD_DCAS_K30GenDaNonce(HI_HANDLE hKlad, HI_UNF_KLAD_DCAS_DA_NONCE_S *pstDaNonce)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_DA_NONCE_S ctl_handle;

    KLAD_CHECK_INIT(g_klad_init_nm);
    KLAD_CHECK_POINTER(pstDaNonce);

    memset(&ctl_handle, 0x00, sizeof(KLAD_CTL_DA_NONCE_S));
    ctl_handle.handle = hKlad;
    memcpy(ctl_handle.nonce, pstDaNonce->au8Nonce, HI_UNF_KLAD_MAX_KEY_LEN);
    KLAD_CHECK_HANDLE(ctl_handle.handle);

    ret = ioctl(g_klad_fd, CMD_KLAD_GEN_K30_DA_NONCE, &ctl_handle);
    if (ret != HI_SUCCESS)
    {
        KLAD_PrintErrorFunc(ioctl,ret);
        return ret;
    }
    memcpy(pstDaNonce->au8DaNonce, ctl_handle.da_nonce, HI_UNF_KLAD_MAX_KEY_LEN);

    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
