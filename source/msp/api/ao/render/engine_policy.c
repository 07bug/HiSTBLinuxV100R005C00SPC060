#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "hi_type.h"
#include "hi_common.h"
#include "hi_drv_ao.h"
#include "engine_policy.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define MAIN                (0)
#define ASSC                (1)
#define PTS_DELTA_MAX       (500)
#define PTS_INVALID         (0xffffffff)
#define WAIT_MAIN_TIMEOUT   (300)
#define WAIT_ASSC_TIMEOUT   (48)
#define INVERT_TIMEMS       (2000)
#define CUTOFF_TIMEMS       (500)

#define POLICY_DEBUG
#ifdef POLICY_DEBUG
#define POLICY_PRINTF HI_WARN_AO
#else
#define POLICY_PRINTF(...)
#endif

#define RECORD_FIRST_TIMEMS(u32CurTimeMs, u32FirstTimeMs) \
    do { \
        u32FirstTimeMs = (0 == u32FirstTimeMs) ? u32CurTimeMs : u32FirstTimeMs; \
    } while(0)

static HI_BOOL CheckIsInSync(ENGINE_POLICY_S* pstPolicy)
{
    return (HI_BOOL)((pstPolicy->u32CurPts[ASSC] <= pstPolicy->u32CurPts[MAIN] + PTS_DELTA_MAX) &&
                     (pstPolicy->u32CurPts[MAIN] <= pstPolicy->u32CurPts[ASSC] + PTS_DELTA_MAX));
}

static HI_BOOL CheckIsMainTimeOut(HI_U32 u32CurTimeMs, HI_U32 u32FirstTimeMs)
{
    return (u32CurTimeMs >= u32FirstTimeMs + WAIT_MAIN_TIMEOUT);
}

static HI_BOOL CheckIsAsscTimeOut(HI_U32 u32CurTimeMs, HI_U32 u32FirstTimeMs)
{
    return (u32CurTimeMs >= u32FirstTimeMs + WAIT_ASSC_TIMEOUT);
}

static HI_BOOL CheckIsMainPtsInvert(ENGINE_POLICY_S* pstPolicy)
{
    return (pstPolicy->u32PrePts[MAIN] > pstPolicy->u32CurPts[MAIN] + INVERT_TIMEMS) ? HI_TRUE : HI_FALSE;
}

static HI_BOOL CheckIsAsscPtsInvert(ENGINE_POLICY_S* pstPolicy)
{
    return (pstPolicy->u32PrePts[ASSC] > pstPolicy->u32CurPts[ASSC] + INVERT_TIMEMS) ? HI_TRUE : HI_FALSE;
}

static HI_BOOL CheckMainBeyondAsscSyncRange(ENGINE_POLICY_S* pstPolicy)
{
    return (pstPolicy->u32CurPts[MAIN] > pstPolicy->u32CurPts[ASSC] + PTS_DELTA_MAX) ? HI_TRUE : HI_FALSE;
}

static HI_BOOL CheckAsscBeyondMainSyncRange(ENGINE_POLICY_S* pstPolicy)
{
    return (pstPolicy->u32CurPts[ASSC] > pstPolicy->u32CurPts[MAIN] + PTS_DELTA_MAX) ? HI_TRUE : HI_FALSE;
}

static HI_BOOL CheckHaveDualInjectData(HI_U32 u32MSize, HI_U32 u32ASize)
{
    return ((u32MSize > 0) && (u32ASize > 0)) ? HI_TRUE : HI_FALSE;
}

static HI_BOOL CheckOnlyMainInjectData(HI_U32 u32MSize, HI_U32 u32ASize)
{
    return ((u32MSize > 0) && (0 == u32ASize)) ? HI_TRUE : HI_FALSE;
}

static HI_BOOL CheckOnlyAsscInjectData(HI_U32 u32MSize, HI_U32 u32ASize)
{
    return ((u32ASize > 0) && (0 == u32MSize)) ? HI_TRUE : HI_FALSE;
}

static HI_BOOL PolicyGetNewStateFromPts(ENGINE_POLICY_S* pstPolicy)
{
    HI_U32 u32CurMPts = pstPolicy->u32CurPts[MAIN];
    HI_U32 u32CurAPts = pstPolicy->u32CurPts[ASSC];
    HI_U32 u32PreMPts = pstPolicy->u32PrePts[MAIN];
    HI_U32 u32PreAPts = pstPolicy->u32PrePts[ASSC];

    if (HI_TRUE == CheckIsMainPtsInvert(pstPolicy))
    {
        POLICY_PRINTF("Main Invert!\n");
        pstPolicy->bMainPtsInvert = HI_TRUE;
    }

    if (HI_TRUE == CheckIsAsscPtsInvert(pstPolicy))
    {
        POLICY_PRINTF("Assc Invert!\n");
        pstPolicy->bAssocPtsInvert = HI_TRUE;
    }

    /* If main & assoc is in sync (including pts invert. skip. wrap), to hold current dual decode status */
    if (HI_TRUE == CheckIsInSync(pstPolicy) || (PTS_INVALID == u32CurMPts || PTS_INVALID == u32CurAPts))
    {
        return HI_FALSE;
    }

    /* main & assoc pts skip */
    if ((u32CurMPts > u32PreMPts + PTS_DELTA_MAX) && (u32CurAPts > u32PreAPts + PTS_DELTA_MAX))
    {
        pstPolicy->enStatus = (u32CurMPts > u32CurAPts) ? POLICY_DEC_A : POLICY_DEC_M;
        return HI_TRUE;
    }

    /* main or assoc pts skip */
    if ((u32CurMPts > u32PreMPts + PTS_DELTA_MAX) || (u32CurAPts > u32PreAPts + PTS_DELTA_MAX))
    {
        pstPolicy->enStatus = (u32CurMPts > u32PreMPts + PTS_DELTA_MAX) ? POLICY_DEC_A : POLICY_DEC_M;
        return HI_TRUE;
    }

    /* main & assoc pts invert */
    if (((u32PreMPts > u32CurMPts + PTS_DELTA_MAX) && (u32PreMPts < u32CurMPts + INVERT_TIMEMS)) &&
        ((u32PreAPts > u32CurAPts + PTS_DELTA_MAX) && (u32PreAPts < u32CurAPts + INVERT_TIMEMS)))
    {
        pstPolicy->enStatus = (u32CurMPts > u32CurAPts) ? POLICY_DEC_A : POLICY_DEC_M;
        return HI_TRUE;
    }

    /* main or assoc pts invert */
    if (((u32PreMPts > u32CurMPts + PTS_DELTA_MAX) && (u32PreMPts < u32CurMPts + INVERT_TIMEMS)) ||
        ((u32PreAPts > u32CurAPts + PTS_DELTA_MAX) && (u32PreAPts < u32CurAPts + INVERT_TIMEMS)))
    {
        pstPolicy->enStatus = (u32CurMPts > u32CurAPts) ? POLICY_DEC_M : POLICY_DEC_A;
        return HI_TRUE;
    }

    /* main & assoc pts wrap */
    if ((HI_TRUE == CheckIsMainPtsInvert(pstPolicy)) && (HI_TRUE == CheckIsAsscPtsInvert(pstPolicy)))
    {
        pstPolicy->enStatus = (u32CurMPts > u32CurAPts) ? POLICY_DEC_A : POLICY_DEC_M;
        pstPolicy->bPtsInvert = HI_TRUE;
        return HI_TRUE;
    }

    /* main or assoc pts wrap */
    if ((HI_TRUE == CheckIsMainPtsInvert(pstPolicy)) || (HI_TRUE == CheckIsAsscPtsInvert(pstPolicy)))
    {
        if (HI_TRUE == CheckIsMainPtsInvert(pstPolicy))
        {
            pstPolicy->bPtsInvert = HI_TRUE;
            pstPolicy->enStatus = POLICY_DEC_A;
        }

        if (HI_TRUE == CheckIsAsscPtsInvert(pstPolicy))
        {
            pstPolicy->bPtsInvert = HI_TRUE;
            pstPolicy->enStatus = POLICY_DEC_M;
        }

        return HI_TRUE;
    }

    //OTHER CASE NOT SUPPORT
    return HI_FALSE;
}

static HI_VOID PolicyGetDataCutOffStatus(ENGINE_POLICY_S* pstPolicy, HI_U32 u32CurTimeMs)
{
    if (u32CurTimeMs >= pstPolicy->u32AllEmptyTimeMs + CUTOFF_TIMEMS)
    {
        pstPolicy->bAssocWaiting = HI_TRUE;
        pstPolicy->u32AllEmptyTimeMs = 0;
    }
}

static ENGINE_POLICY_E PolicyMainUnderRunTimeOut(ENGINE_POLICY_S* pstPolicy, HI_U32 u32CurTimeMs)
{
    RECORD_FIRST_TIMEMS(u32CurTimeMs, pstPolicy->u32FirstTimeMs[MAIN]);

    POLICY_PRINTF("CurTimeMs=%d, FirstTimeMs=%d\n", u32CurTimeMs, pstPolicy->u32FirstTimeMs[MAIN]);

    if (HI_TRUE == CheckIsMainTimeOut(u32CurTimeMs, pstPolicy->u32FirstTimeMs[MAIN]))
    {
        pstPolicy->enStatus = POLICY_DEC_A;
        pstPolicy->bDecoding = HI_TRUE;
        pstPolicy->bAssocWaiting = HI_FALSE;
        pstPolicy->u32FirstTimeMs[MAIN] = 0;
        return pstPolicy->enStatus;
    }

    return POLICY_NONE;
}

static ENGINE_POLICY_E PolicyAsscUnderRunTimeOut(ENGINE_POLICY_S* pstPolicy, HI_U32 u32CurTimeMs)
{
    RECORD_FIRST_TIMEMS(u32CurTimeMs, pstPolicy->u32FirstTimeMs[ASSC]);

    POLICY_PRINTF("CurTimeMs=%d, FirstTimeMs=%d\n", u32CurTimeMs, pstPolicy->u32FirstTimeMs[ASSC]);

    if (HI_TRUE == CheckIsAsscTimeOut(u32CurTimeMs, pstPolicy->u32FirstTimeMs[ASSC]))
    {
        pstPolicy->enStatus = POLICY_DEC_M;
        pstPolicy->bDecoding = HI_TRUE;
        pstPolicy->u32FirstTimeMs[ASSC] = 0;
        return pstPolicy->enStatus;
    }

    return POLICY_NONE;
}

static ENGINE_POLICY_E PolicyIniProc(ENGINE_POLICY_S* pstPolicy)
{
    HI_U32 u32CurMPts = pstPolicy->u32CurPts[MAIN];
    HI_U32 u32CurAPts = pstPolicy->u32CurPts[ASSC];

    pstPolicy->u32FirstTimeMs[MAIN] = 0;
    pstPolicy->u32FirstTimeMs[ASSC] = 0;

    /* Sugguest: limit the sync range at the first dual-decode case*/
    if (HI_TRUE == CheckIsInSync(pstPolicy) || (PTS_INVALID == u32CurMPts || PTS_INVALID == u32CurAPts))
    {
        pstPolicy->enStatus = POLICY_DEC_DUAL;
        pstPolicy->bDecoding = HI_TRUE;
        return POLICY_DEC_DUAL;
    }
    else if (u32CurAPts > u32CurMPts + PTS_DELTA_MAX)
    {
        /* Assoc PTS being larger than Main PTS, and beyond the sync range */
        pstPolicy->enStatus = POLICY_DEC_M;
        pstPolicy->bDecoding = HI_TRUE;
        return POLICY_DEC_M;
    }
    else if (u32CurMPts > u32CurAPts + PTS_DELTA_MAX)
    {
        /* Main PTS being larger than Assoc PTS, and beyond the sync range */
        pstPolicy->enStatus = POLICY_DEC_A;
        pstPolicy->bDecoding = HI_TRUE;
        return POLICY_DEC_A;
    }

    return POLICY_NONE;
}

static ENGINE_POLICY_E PolicyFirstIn(ENGINE_POLICY_S* pstPolicy, HI_U32 u32MSize, HI_U32 u32ASize)
{
    HI_U32 u32CurTimeMs = 0;

    HI_SYS_GetTimeStampMs(&u32CurTimeMs);

    if (HI_TRUE == CheckHaveDualInjectData(u32MSize, u32ASize))
    {
        return PolicyIniProc(pstPolicy);
    }

    if (HI_TRUE == CheckOnlyMainInjectData(u32MSize, u32ASize))
    {
        return PolicyAsscUnderRunTimeOut(pstPolicy, u32CurTimeMs);
    }

    if (HI_TRUE == CheckOnlyAsscInjectData(u32MSize, u32ASize))
    {
        return PolicyMainUnderRunTimeOut(pstPolicy, u32CurTimeMs);
    }

    //NO-InjectData
    return POLICY_NONE;
}

static ENGINE_POLICY_E PolicyDecMain(ENGINE_POLICY_S* pstPolicy, HI_U32 u32ASize)
{
    pstPolicy->u32FirstTimeMs[MAIN] = 0;
    pstPolicy->u32FirstTimeMs[ASSC] = 0;

    if (HI_TRUE == CheckIsMainPtsInvert(pstPolicy))
    {
        POLICY_PRINTF("Main Invert!\n");
        pstPolicy->bDropStream = HI_TRUE;
        pstPolicy->bMainPtsInvert = HI_TRUE;
    }

    /* When main being decoding, receive assoc data */
    if (u32ASize > 0)
    {
        if (HI_TRUE == CheckIsInSync(pstPolicy))
        {
            pstPolicy->enStatus = POLICY_DEC_DUAL;
            pstPolicy->bPtsInvert = HI_FALSE;
            pstPolicy->bDropStream = HI_FALSE;
            return POLICY_DEC_DUAL;
        }

        if (HI_TRUE == CheckIsAsscPtsInvert(pstPolicy))
        {
            POLICY_PRINTF("Assc Invert!\n");
            pstPolicy->bPtsInvert = HI_TRUE;
            pstPolicy->bAssocPtsInvert = HI_TRUE;
        }

        /* Main PTS being larger than Assoc PTS, and beyond the sync range */
        if (HI_TRUE == CheckMainBeyondAsscSyncRange(pstPolicy))
        {
            if (HI_TRUE != pstPolicy->bDropStream)
            {
                return ((HI_TRUE != pstPolicy->bPtsInvert) ? POLICY_DROP_A : POLICY_NONE);
            }
            else
            {
                pstPolicy->enStatus = POLICY_DEC_A;
                pstPolicy->bPtsInvert = HI_FALSE;
                pstPolicy->bDropStream = HI_FALSE;
                return POLICY_DEC_A;
            }
        }

        if (HI_TRUE == CheckAsscBeyondMainSyncRange(pstPolicy))
        {
            if (HI_TRUE == pstPolicy->bDropStream)
            {
                return ((HI_TRUE != pstPolicy->bPtsInvert) ? POLICY_DROP_A : POLICY_NONE);
            }
        }
    }

    return POLICY_NONE;
}

static ENGINE_POLICY_E PolicyDecAssc(ENGINE_POLICY_S* pstPolicy, HI_U32 u32MSize)
{
    pstPolicy->u32FirstTimeMs[MAIN] = 0;
    pstPolicy->u32FirstTimeMs[ASSC] = 0;

    if (HI_TRUE == CheckIsAsscPtsInvert(pstPolicy))
    {
        POLICY_PRINTF("Assc Invert!\n");
        pstPolicy->bDropStream = HI_TRUE;
        pstPolicy->bAssocPtsInvert = HI_TRUE;
    }

    /* When assoc being decoding, receive main data */
    if (u32MSize > 0)
    {
        if (HI_TRUE == CheckIsInSync(pstPolicy))
        {
            pstPolicy->enStatus = POLICY_DEC_DUAL;
            pstPolicy->bPtsInvert = HI_FALSE;
            pstPolicy->bDropStream = HI_FALSE;
            return POLICY_DEC_DUAL;
        }

        if (HI_TRUE == CheckIsMainPtsInvert(pstPolicy))
        {
            POLICY_PRINTF("Main Invert!\n");
            pstPolicy->bPtsInvert = HI_TRUE;
            pstPolicy->bMainPtsInvert = HI_TRUE;
        }

        /* Assoc PTS being larger than Main PTS, and beyond the sync range */
        if (HI_TRUE == CheckAsscBeyondMainSyncRange(pstPolicy))
        {
            if (HI_TRUE != pstPolicy->bDropStream)
            {
                if (HI_TRUE != pstPolicy->bPtsInvert)
                {
                    pstPolicy->enStatus = POLICY_DEC_M;
                    return POLICY_DEC_M;
                }
                return POLICY_NONE;
            }

            pstPolicy->enStatus = POLICY_DEC_M;
            pstPolicy->bPtsInvert = HI_FALSE;
            pstPolicy->bDropStream = HI_FALSE;
            return POLICY_DEC_M;
        }

        if (HI_TRUE == CheckMainBeyondAsscSyncRange(pstPolicy))
        {
            if (HI_TRUE == pstPolicy->bDropStream)
            {
                if (HI_TRUE != pstPolicy->bPtsInvert)
                {
                    pstPolicy->enStatus = POLICY_DEC_M;
                    return POLICY_DEC_M;
                }
                return POLICY_NONE;
            }
        }
    }

    return POLICY_NONE;
}

static ENGINE_POLICY_E PolicyDecDual(ENGINE_POLICY_S* pstPolicy, HI_U32 u32MSize, HI_U32 u32ASize)
{
    HI_U32 u32CurTimeMs = 0;

    HI_SYS_GetTimeStampMs(&u32CurTimeMs);

    /* When being dual decoding, no main & assoc data */
    if (0 == u32MSize && 0 == u32ASize)
    {
        RECORD_FIRST_TIMEMS(u32CurTimeMs, pstPolicy->u32AllEmptyTimeMs);
        return POLICY_NONE;
    }

    /* When being dual decoding, no main data */
    if (0 == u32MSize)
    {
        PolicyGetDataCutOffStatus(pstPolicy, u32CurTimeMs);
        return PolicyMainUnderRunTimeOut(pstPolicy, u32CurTimeMs);
    }

    pstPolicy->bAssocWaiting = HI_FALSE;
    pstPolicy->u32AllEmptyTimeMs = 0;
    pstPolicy->u32FirstTimeMs[MAIN] = 0;

    /* When being dual decoding, no assoc data */
    if (0 == u32ASize)
    {
        return PolicyAsscUnderRunTimeOut(pstPolicy, u32CurTimeMs);
    }

    pstPolicy->u32FirstTimeMs[ASSC] = 0;

    /* When being dual decoding, receive main & assoc data and check pts*/
    if (HI_TRUE == PolicyGetNewStateFromPts(pstPolicy))
    {
        return pstPolicy->enStatus;
    }

    return POLICY_NONE;
}

ENGINE_POLICY_E Policy_Process(ENGINE_POLICY_S* pstPolicy, HI_U32 u32MSize, HI_U32 u32ASize)
{
    /* first play, first being in decode policy */
    if (HI_FALSE == pstPolicy->bDecoding)
    {
        return PolicyFirstIn(pstPolicy, u32MSize, u32ASize);
    }

    /* Current status: only decode main */
    if (POLICY_DEC_M == pstPolicy->enStatus)
    {
        return PolicyDecMain(pstPolicy, u32ASize);
    }

    /* Current status: only decode assoc */
    if (POLICY_DEC_A == pstPolicy->enStatus)
    {
        return PolicyDecAssc(pstPolicy, u32MSize);
    }

    /* Current status: dual decode */
    if (POLICY_DEC_DUAL == pstPolicy->enStatus)
    {
        return PolicyDecDual(pstPolicy, u32MSize, u32ASize);
    }

    return POLICY_NONE;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
