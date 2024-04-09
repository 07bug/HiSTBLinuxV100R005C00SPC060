/*****************************************************************************
*              Copyright 2004 - 2016, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: render_source.c
* Description: Describe main functionality and purpose of this file.
*
* History:
* Version   Date         Author     DefectNum    Description
* 0.01
*
*****************************************************************************/
#include <string.h>
#include <stdlib.h>

#include "hi_mpi_ao.h"
#include "hi_error_mpi.h"
#include "render_dccm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */


#define DCCM_POLICY_MAX_PTS      (888)
#define DCCM_TIMEOUT_MS          (1000)

typedef enum
{
    DCCM_INIT,
    DCCM_HOLD,
    DCCM_PLAY,
} DCCM_STATUS_E;

typedef struct
{
    HI_U32          u32LastSysTimeMs;
    HI_U32          u32FirstPts;
    DCCM_STATUS_E   enDCCMStatus;
} DCCM_POLICY_S;


HI_S32 DCCM_Init(HI_DCCM_HANDLE* phDccm)
{
    DCCM_POLICY_S* state;

    if (HI_NULL == phDccm)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    state = (DCCM_POLICY_S*)malloc(sizeof(DCCM_POLICY_S));
    if (HI_NULL == state)
    {
        HI_ERR_AO("Malloc Dccm Policy instance failed\n");
        return HI_ERR_AO_MALLOC_FAILED;
    }
    memset(state, 0, sizeof(DCCM_POLICY_S));

    state->enDCCMStatus = DCCM_INIT;

    *phDccm = (HI_DCCM_HANDLE)state;

    return HI_SUCCESS;
}

HI_VOID DCCM_DeInit(HI_DCCM_HANDLE hDccm)
{
    if (HI_NULL == hDccm)
    {
        return;
    }

    free(hDccm);
    hDccm = HI_NULL;
}

HI_VOID DCCM_ApplyPolicy(HI_DCCM_HANDLE hDccm, HI_U32 u32PtsMs)
{
    HI_U32 u32CurSysTimeMs = 0;
    DCCM_POLICY_S* state;

    if (HI_NULL == hDccm)
    {
        return;
    }

    state = (DCCM_POLICY_S*)hDccm;

    HI_SYS_GetTimeStampMs(&u32CurSysTimeMs);

    if ((DCCM_INIT == state->enDCCMStatus) || (u32CurSysTimeMs > state->u32LastSysTimeMs + DCCM_TIMEOUT_MS))
    {
        HI_WARN_AO("DCCM: Status INIT/Start -> HOLD\n");
        /* maybe -1, so need to reset it when in HOLD status */
        state->u32FirstPts = u32PtsMs;
        state->enDCCMStatus = DCCM_HOLD;
    }

    if ((DCCM_HOLD == state->enDCCMStatus) && (HI_INVALID_PTS != u32PtsMs))
    {
        if (HI_INVALID_PTS == state->u32FirstPts)
        {
            state->u32FirstPts = u32PtsMs;
        }

        HI_INFO_AO("DCCM: CurPTS=%d, FirstPTS=%d\n", u32PtsMs, state->u32FirstPts);
        if (u32PtsMs > state->u32FirstPts + DCCM_POLICY_MAX_PTS)
        {
            HI_WARN_AO("DCCM: Status HOLD -> Start\n");
            state->enDCCMStatus = DCCM_PLAY;
        }
    }

    state->u32LastSysTimeMs = u32CurSysTimeMs;
}

HI_BOOL DCCM_CheckIsNeedDecode(HI_DCCM_HANDLE hDccm)
{
    DCCM_POLICY_S* state;

    if (HI_NULL == hDccm)
    {
        return HI_TRUE;
    }

    state = (DCCM_POLICY_S*)hDccm;
    return ((DCCM_HOLD == state->enDCCMStatus) ? HI_FALSE : HI_TRUE);
}

HI_VOID DCCM_Reset(HI_DCCM_HANDLE hDccm)
{
    DCCM_POLICY_S* state;

    if (HI_NULL == hDccm)
    {
        return;
    }

    state = (DCCM_POLICY_S*)hDccm;
    state->enDCCMStatus = DCCM_INIT;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
