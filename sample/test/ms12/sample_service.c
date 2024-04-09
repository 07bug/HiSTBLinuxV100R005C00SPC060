#include "sample_ms12.h"
#include "sample_ir.h"
#include "sample_osd.h"
#include "sample_play.h"
#include "sample_service.h"

typedef struct tagSAMPLE_SERVICE_INFO_S
{
    HI_BOOL bSearch;
    HI_BOOL bChnList;
    HI_BOOL bPlayInit;
    HI_BOOL bHighLightForAD;
}SAMPLE_SERVICE_INFO_S;

static SAMPLE_SERVICE_INFO_S s_stServiceInfo =
{
    .bSearch = HI_FALSE,
    .bChnList = HI_FALSE,
    .bPlayInit = HI_FALSE,
};

HI_S32 Sample_Service_GetFreqParams(HI_U32 *pu32Tuner, HI_U32 *pu32TunerFreq, HI_U32 *pu32TunerSrate, HI_U32 *pu32ThirdParam, HI_BOOL bRepeat)
{
    SAMPLE_OSD_ELEMENT_INFO_S stElem;
    HI_S32 s32Ret = HI_SUCCESS;
    SAMPLE_CHECK_POINTER_RETURN(pu32Tuner);
    SAMPLE_CHECK_POINTER_RETURN(pu32TunerFreq);
    SAMPLE_CHECK_POINTER_RETURN(pu32TunerSrate);
    SAMPLE_CHECK_POINTER_RETURN(pu32ThirdParam);
    Sample_Osd_EnableShow(HI_TRUE);
    SAMPLE_DOFUNC_RETURN(Sample_Osd_ShowSearchView(bRepeat), s32Ret);
    s_stServiceInfo.bSearch = HI_TRUE;
    while(HI_TRUE == s_stServiceInfo.bSearch)
    {
        usleep(100000);
    }

    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_GetSearchElemByType(SAMPLE_OSD_SEARCH_TUNER_ID, &stElem), s32Ret);
    *pu32Tuner = stElem.u32Value[0];
    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_GetSearchElemByType(SAMPLE_OSD_SEARCH_FREQ, &stElem), s32Ret);
    *pu32TunerFreq = stElem.u32Value[0];
    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_GetSearchElemByType(SAMPLE_OSD_SEARCH_SYMRATE, &stElem), s32Ret);
    *pu32TunerSrate = stElem.u32Value[0];
    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_GetSearchElemByType(SAMPLE_OSD_SEARCH_QAM, &stElem), s32Ret);
    *pu32ThirdParam = stElem.u32Value[0];
    Sample_Osd_EnableShow(HI_FALSE);
    return HI_SUCCESS;
}
HI_S32 Sample_Service_SearchProcKeys(IR_KEY_TYPE_E enKeyType)
{
    HI_S32 s32Ret = HI_SUCCESS;
    SAMPLE_OSD_SEARCH_VIEW_E enType = SAMPLE_OSD_SEARCH_BUTT;
    SAMPLE_OSD_ELEMENT_INFO_S stElem;

    SAMPLE_DOFUNC_RETURN(Sample_Osd_GetCurSearchElem(&enType, &stElem), s32Ret);
    switch(enKeyType)
    {
        case IR_KEY_type_1:
        case IR_KEY_type_2:
        case IR_KEY_type_3:
        case IR_KEY_type_4:
        case IR_KEY_type_5:
        case IR_KEY_type_6:
        case IR_KEY_type_7:
        case IR_KEY_type_8:
        case IR_KEY_type_9:
        case IR_KEY_type_0:
        case IR_KEY_type_BACKSPACE:
            if ((SAMPLE_OSD_SEARCH_QAM == enType) || (SAMPLE_OSD_SEARCH_START == enType))
            {
                return HI_SUCCESS;
            }
            break;
        case IR_KEY_type_UP:
        case IR_KEY_type_DOWN:
            if (IR_KEY_type_UP == enKeyType)
                SAMPLE_DOFUNC_RETURN(Sample_Osd_GetPrevSearchElem(&enType, &stElem), s32Ret);
            else
                SAMPLE_DOFUNC_RETURN(Sample_Osd_GetNextSearchElem(&enType, &stElem), s32Ret);
            SAMPLE_DOFUNC_RETURN(Sample_Osd_SetSearchElem(enType, &stElem, HI_TRUE), s32Ret);
            break;
        case IR_KEY_type_LEFT:
        case IR_KEY_type_RIGHT:
            if (SAMPLE_OSD_SEARCH_QAM != enType)
            {
                return HI_SUCCESS;
            }
            break;
        case IR_KEY_type_ENTER:
            if (SAMPLE_OSD_SEARCH_START == enType)
            {
                s_stServiceInfo.bSearch = HI_FALSE;
                return HI_SUCCESS;
            }
            break;
        default:
            return HI_SUCCESS;
    }

    switch(enType)
    {
        case SAMPLE_OSD_SEARCH_TUNER_ID:
        case SAMPLE_OSD_SEARCH_FREQ:
        case SAMPLE_OSD_SEARCH_SYMRATE:
            if ((IR_KEY_type_1 <= enKeyType) && (IR_KEY_type_0 > enKeyType))
                stElem.u32Value[0] = stElem.u32Value[0] * 10 + 1 + enKeyType - IR_KEY_type_1;
            if (IR_KEY_type_0 == enKeyType)
                stElem.u32Value[0] = stElem.u32Value[0] * 10;
            if (IR_KEY_type_BACKSPACE == enKeyType)
                stElem.u32Value[0] = stElem.u32Value[0]/10;
            break;
        case SAMPLE_OSD_SEARCH_QAM:
            if (IR_KEY_type_LEFT == enKeyType)
                stElem.u32Value[0] = stElem.u32Value[0]/2;
            if (IR_KEY_type_RIGHT == enKeyType)
                stElem.u32Value[0] = stElem.u32Value[0]*2;
            if (16 > stElem.u32Value[0])
                stElem.u32Value[0] = 256;
            if (256 < stElem.u32Value[0])
                stElem.u32Value[0] = 16;
            break;
        default:
            return HI_SUCCESS;
    }

    SAMPLE_DOFUNC_RETURN(Sample_Osd_SetSearchElem(enType, &stElem, HI_TRUE), s32Ret);
    return HI_SUCCESS;
}
static HI_VOID SampleServiceGetChnName(HI_CHAR *pszChnName, PMT_COMPACT_PROG *pstProg)
{
    snprintf(pszChnName, 255, "no name(V:0x%x, A:0x%x)", pstProg->VElementPid, pstProg->AElementPid);
    return;
}
HI_S32 Sample_Service_ChnListInit(HI_VOID)
{
    HI_U32 i = 0;
    HI_CHAR szChnName[256];
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32TotalProg = 0;
    PMT_COMPACT_PROG stProg;
    Sample_Osd_EnableShow(HI_TRUE);
    SAMPLE_DOFUNC_NO_RETURN(Sample_Play_GetProgNum(&u32TotalProg), s32Ret);
    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_ChannelInit(u32TotalProg), s32Ret);
    for (i = 0; i < u32TotalProg; i++)
    {
        SAMPLE_DOFUNC_NO_RETURN(Sample_Play_GetProgInfoByIdx(i, &stProg), s32Ret);
        memset(szChnName, 0x00, 256*sizeof(HI_CHAR));
        SampleServiceGetChnName(szChnName, &stProg);
        SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_ChannelAdd(i, szChnName), s32Ret);
    }
    SAMPLE_DOFUNC_NO_RETURN(Sample_Play_GetCurPlayProg(&i), s32Ret);
    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_ChannelDisplay(i), s32Ret);
    s_stServiceInfo.bChnList = HI_TRUE;
    return HI_SUCCESS;
}

HI_S32 Sample_Service_ChnListProcKeys(IR_KEY_TYPE_E enKeyType)
{
    HI_U32 u32CurFocus = 0;
    HI_U32 u32TotalProg = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_CHAR szContent[256] = {0};

    switch(enKeyType)
    {
        case IR_KEY_type_BACK:
        case IR_KEY_type_UP:
        case IR_KEY_type_DOWN:
        case IR_KEY_type_ENTER:
            break;
        default:
            return HI_SUCCESS;
    }

    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_ChannelGetCurrent(&u32CurFocus, szContent), s32Ret);
    SAMPLE_DOFUNC_NO_RETURN(Sample_Play_GetProgNum(&u32TotalProg), s32Ret);

    if ((IR_KEY_type_DOWN == enKeyType) || (IR_KEY_type_UP == enKeyType))
    {
        u32CurFocus = (IR_KEY_type_DOWN == enKeyType) ? (u32CurFocus + 1) : (u32CurFocus + u32TotalProg - 1);
        u32CurFocus = u32CurFocus%u32TotalProg;
        SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_ChannelDisplay(u32CurFocus), s32Ret);
    }

    if (IR_KEY_type_ENTER == enKeyType)
    {
        SAMPLE_DOFUNC_NO_RETURN(Sample_Play_PlayByIdx(u32CurFocus), s32Ret);
    }

    if (IR_KEY_type_BACK == enKeyType)
    {
        s_stServiceInfo.bChnList = HI_FALSE;
        Sample_Osd_EnableShow(HI_FALSE);
    }
    return HI_SUCCESS;
}

static HI_VOID SampleServiceTrans(PMT_AUDIO *pstPmtAudio, SAMPLE_OSD_AUDIO_INFO_S *pstOsdAudInfo)
{
    pstOsdAudInfo->szLanguage[0] = pstPmtAudio->u8AudLang[0];
    pstOsdAudInfo->szLanguage[1] = pstPmtAudio->u8AudLang[1];
    pstOsdAudInfo->szLanguage[2] = pstPmtAudio->u8AudLang[2];
    pstOsdAudInfo->u32ADType = pstPmtAudio->u16ADType;
    if ((0 == pstOsdAudInfo->szLanguage[0])
        && (0 == pstOsdAudInfo->szLanguage[1])
        && (0 == pstOsdAudInfo->szLanguage[2]))
    {
        pstOsdAudInfo->szLanguage[0] = 'U';
        pstOsdAudInfo->szLanguage[1] = 'N';
        pstOsdAudInfo->szLanguage[2] = 'D';
    }

    return;
}
HI_S32 Sample_Service_PlyCtrlInit(HI_VOID)
{
    HI_U32 i = 0, j = 0;
    HI_U32 idx = 0;
    HI_U32 u32AudIdx = 0;
    HI_U32 u32ADLevel = 0;
    PMT_COMPACT_PROG stProg;
    SAMPLE_OSD_AUDIO_INFO_S stAudInfo;
    SAMPLE_OSD_AUDIO_INFO_S stADAudInfo;
    HI_S32 s32Ret = HI_SUCCESS;

    Sample_Osd_EnableShow(HI_TRUE);
    SAMPLE_DOFUNC_NO_RETURN(Sample_Play_GetCurPlayProg(&idx), s32Ret);
    SAMPLE_DOFUNC_NO_RETURN(Sample_Play_GetPlayAudio(&u32AudIdx, &u32ADLevel), s32Ret);
    SAMPLE_DOFUNC_NO_RETURN(Sample_Play_GetProgInfoByIdx(idx, &stProg), s32Ret);
    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_PlayCtrlInit(stProg.AElementNum, u32ADLevel), s32Ret);

    for (i = 0; i < stProg.AElementNum; i++)
    {
        memset(&stAudInfo, 0x00, sizeof(stAudInfo));
        SampleServiceTrans(&stProg.Audioinfo[i], &stAudInfo);
        SAMPLE_DOFUNC_NO_RETURN(Sample_Play_GetAudioInfo(&stAudInfo), s32Ret);

        if (0 == stAudInfo.u32ADType)
        {
            for (j = 0; j < stProg.AElementNum; j++)
            {
                memset(&stADAudInfo, 0x00, sizeof(stADAudInfo));
                SampleServiceTrans(&stProg.Audioinfo[j], &stADAudInfo);
                if ((1 == stADAudInfo.u32ADType) && (!strncmp(stADAudInfo.szLanguage, stAudInfo.szLanguage, 3)))
                {
                    stAudInfo.u32ADType = 1;
                    break;
                }
            }

            SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_PlayCtrlAdd(i, &stAudInfo), s32Ret);
        }
    }

    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_PlayCtrlSetCurrentFocus(u32AudIdx, u32ADLevel), s32Ret);
    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_PlayCtrlSetCurrentUsed(u32AudIdx, u32ADLevel), s32Ret);
    s_stServiceInfo.bHighLightForAD = HI_FALSE;
    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_PlayCtrlDisplay(s_stServiceInfo.bHighLightForAD), s32Ret);
    s_stServiceInfo.bPlayInit = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 Sample_Service_PlyCtrlProcKeys(IR_KEY_TYPE_E enKeyType)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32FocusAud = 0;
    HI_U32 u32FocusADLev = 0;
    HI_U32 u32UsedAud = 0;
    HI_U32 u32UsedADLev = 0;
    HI_U32 u32TotalAudNum = 0;

    switch(enKeyType)
    {
        case IR_KEY_type_UP:
        case IR_KEY_type_DOWN:
        case IR_KEY_type_LEFT:
        case IR_KEY_type_RIGHT:
        case IR_KEY_type_ENTER:
        case IR_KEY_type_BACK:
            break;
        default:
            return HI_SUCCESS;
    }

    if ((IR_KEY_type_RIGHT == enKeyType) || (IR_KEY_type_LEFT == enKeyType))
    {
        s_stServiceInfo.bHighLightForAD = (HI_FALSE == s_stServiceInfo.bHighLightForAD) ? HI_TRUE : HI_FALSE;
        SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_PlayCtrlDisplay(s_stServiceInfo.bHighLightForAD), s32Ret);
        return HI_SUCCESS;
    }

    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_PlayCtrlGetCurrentFocus(&u32FocusAud, &u32FocusADLev), s32Ret);
    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_PlayCtrlGetCurrentUsed(&u32UsedAud, &u32UsedADLev), s32Ret);
    SAMPLE_DOFUNC_RETURN(Sample_Play_GetAudioNum(&u32TotalAudNum), s32Ret);
    if (IR_KEY_type_UP == enKeyType)
    {
        if (HI_TRUE == s_stServiceInfo.bHighLightForAD)
            u32FocusADLev = (0 == u32FocusADLev) ? 3 : ((u32FocusADLev - 1)%4);
        else
            u32FocusAud = (0 == u32FocusAud) ? (u32TotalAudNum - 1) : ((u32FocusAud - 1)%u32TotalAudNum);
        SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_PlayCtrlSetCurrentFocus(u32FocusAud, u32FocusADLev), s32Ret);
    }

    if (IR_KEY_type_DOWN == enKeyType)
    {
        if (HI_TRUE == s_stServiceInfo.bHighLightForAD)
            u32FocusADLev = (u32FocusADLev + 1)%4;
        else
            u32FocusAud = (u32FocusAud + 1)%u32TotalAudNum;
        SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_PlayCtrlSetCurrentFocus(u32FocusAud, u32FocusADLev), s32Ret);
    }

    if (IR_KEY_type_ENTER == enKeyType)
    {
        if (HI_TRUE == s_stServiceInfo.bHighLightForAD)
        {
            SAMPLE_DOFUNC_NO_RETURN(Sample_Play_SetAudioBalance(u32FocusADLev), s32Ret);
        }
        else
        {
            SAMPLE_DOFUNC_NO_RETURN(Sample_Play_SetPlayAudio(u32FocusAud), s32Ret);
        }

        SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_PlayCtrlSetCurrentUsed(u32FocusAud, u32FocusADLev), s32Ret);
    }

    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_PlayCtrlDisplay(s_stServiceInfo.bHighLightForAD), s32Ret);
    if (IR_KEY_type_BACK == enKeyType)
    {
        Sample_Osd_EnableShow(HI_FALSE);
        s_stServiceInfo.bPlayInit = HI_FALSE;
        s_stServiceInfo.bHighLightForAD = HI_FALSE;
    }
    return HI_SUCCESS;
}

HI_S32 Sample_Service_ProcessKeys(IR_KEY_TYPE_E enKeyType)
{
    if (IR_KEY_type_POWER == enKeyType)
    {
        sample_printf("exit the sample!\n");
        exit(0);
    }

    if (HI_TRUE == s_stServiceInfo.bSearch)
        return Sample_Service_SearchProcKeys(enKeyType);

    if (IR_KEY_type_EPG == enKeyType)
        return Sample_Service_ChnListInit();

    if (HI_TRUE == s_stServiceInfo.bChnList)
        return Sample_Service_ChnListProcKeys(enKeyType);

    if ((IR_KEY_type_PLAYPAUSE == enKeyType) || (IR_KEY_type_INFO == enKeyType))
        return Sample_Service_PlyCtrlInit();

    if (HI_TRUE == s_stServiceInfo.bPlayInit)
        return Sample_Service_PlyCtrlProcKeys(enKeyType);

    if (IR_KEY_type_BACK == enKeyType)
    {
        Sample_Osd_EnableShow(HI_FALSE);
    }
    return HI_SUCCESS;
}
