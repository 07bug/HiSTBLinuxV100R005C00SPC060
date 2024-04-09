#include "sample_ms12.h"
#include "sample_osd.h"

typedef struct tagSAMPLE_OSD_INFO_S
{
    HI_BOOL   bInitFlag;
    HI_HANDLE hOsdLayer;
    HI_HANDLE hOsdSurface;
    HI_HANDLE hFont;
}SAMPLE_OSD_INFO_S;
typedef struct tagSAMPLE_OSD_SEARCH_INFO_S
{
    HI_BOOL bInitFlag;
    SAMPLE_OSD_SEARCH_VIEW_E enCurPos;
    SAMPLE_OSD_ELEMENT_INFO_S stElem[SAMPLE_OSD_SEARCH_BUTT + 1];
}SAMPLE_OSD_SEARCH_INFO_S;
typedef struct tagSAMPLE_CHANNEL_LIST_INFO_S
{
    HI_BOOL bInitFlag;
    HI_U32 u32TotalNum;
    HI_U32 u32CurFocusIdx;
    SAMPLE_OSD_ELEMENT_INFO_S stElem[SAMPLE_MAX_PROG_NUM];
}SAMPLE_CHANNEL_LIST_INFO_S;

typedef struct tagSAMPLE_PLAY_CTRL_INFO_S
{
    HI_BOOL bInitFlag;
    HI_U32 u32AudNum;
    HI_U32 u32Focus;
    HI_U32 u32CurAudIdx;
    HI_U32 u32CurADLev;
    HI_U32 u32ADLevel;/*0 -- OFF; 33 -- LOW; 66 -- MID; 100 -- HIGH*/
    SAMPLE_OSD_AUDIO_INFO_S stAudoInfo[SAMPLE_MAX_AUDIO_NUM];
    SAMPLE_OSD_ELEMENT_INFO_S stAudElem[SAMPLE_MAX_AUDIO_NUM + 1];
    SAMPLE_OSD_ELEMENT_INFO_S stADLeElem[5];
}SAMPLE_PLAY_CTRL_INFO_S;

static SAMPLE_OSD_INFO_S s_stOsdInfo =
{
    .bInitFlag = HI_FALSE,
};

static SAMPLE_OSD_SEARCH_INFO_S s_stSearchInfo =
{
    .bInitFlag = HI_FALSE,
};

static SAMPLE_CHANNEL_LIST_INFO_S s_stChnInfo =
{
    .bInitFlag = HI_FALSE,
};
static SAMPLE_PLAY_CTRL_INFO_S s_stPlayCtrlInfo =
{
    .bInitFlag = HI_FALSE,
};

#define SAMPLE_OSD_CHECK_INIT_RETURN(initFlags)\
    do{\
        if (HI_TRUE != (initFlags))\
        {\
            sample_printf("not init!\n");\
            return HI_FAILURE;\
        }\
    }while(0)

HI_S32 Sample_Osd_Init(HI_VOID)
{
    HI_S32   s32Ret;
    HIGO_LAYER_INFO_S stLayerInfo;
    HIGO_TEXT_INFO_S stTextInfo;
    HIGO_LAYER_ALPHA_S stAlphaInfo;

    SAMPLE_DOFUNC_RETURN(HI_GO_Init(), s32Ret);

    HI_GO_GetLayerDefaultParam(HIGO_LAYER_HD_0, &stLayerInfo);
    stLayerInfo.PixelFormat  = HIGO_PF_1555;
    stLayerInfo.ScreenWidth  = 1920;
    stLayerInfo.ScreenHeight = 1080;
    stLayerInfo.CanvasWidth = 1920;
    stLayerInfo.CanvasHeight = 1080;
    stLayerInfo.DisplayWidth  = 1280;
    stLayerInfo.DisplayHeight = 720;
    memset(&stAlphaInfo, 0x00, sizeof(stAlphaInfo));

    SAMPLE_DOFUNC_RETURN(HI_GO_CreateLayer(&stLayerInfo, &s_stOsdInfo.hOsdLayer), s32Ret);
    SAMPLE_DOFUNC_NO_RETURN(HI_GO_GetLayerAlphaEx(s_stOsdInfo.hOsdLayer, &stAlphaInfo), s32Ret);
    stAlphaInfo.GlobalAlpha = 192;
    stAlphaInfo.Alpha0 = 192;
    stAlphaInfo.Alpha1 = 192;
    stAlphaInfo.bAlphaEnable = HI_TRUE;
    stAlphaInfo.bAlphaChannel = HI_TRUE;
    SAMPLE_DOFUNC_NO_RETURN(HI_GO_SetLayerAlphaEx(s_stOsdInfo.hOsdLayer, &stAlphaInfo), s32Ret);
    SAMPLE_DOFUNC_RETURN(HI_GO_GetLayerSurface(s_stOsdInfo.hOsdLayer, &s_stOsdInfo.hOsdSurface), s32Ret);
    SAMPLE_DOFUNC_NO_RETURN(HI_GO_FillRect(s_stOsdInfo.hOsdSurface, NULL, 0x00000000, HIGO_COMPOPT_NONE), s32Ret);

    stTextInfo.pMbcFontFile = NULL;
    stTextInfo.pSbcFontFile = "../../res/font/DroidSansFallbackLegacy.ttf";
    stTextInfo.u32Size = 20;

    SAMPLE_DOFUNC_RETURN(HI_GO_CreateTextEx(&stTextInfo,  &s_stOsdInfo.hFont), s32Ret);
    SAMPLE_DOFUNC_NO_RETURN(HI_GO_RefreshLayer(s_stOsdInfo.hOsdLayer, NULL), s32Ret);

    s_stOsdInfo.bInitFlag = HI_TRUE;
    return HI_SUCCESS;
}
HI_S32 Sample_Osd_DrawString(HI_CHAR *pszText, HI_RECT *pstRect, HI_BOOL bHighLight)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_COLOR cBackColor = 0x80000000;
    HI_COLOR cRimColor = 0xffffffff;
    HI_COLOR cTextColor = 0xff00ff00;

    SAMPLE_CHECK_POINTER_RETURN(pszText);
    SAMPLE_CHECK_POINTER_RETURN(pstRect);

    if (HI_TRUE == bHighLight)
    {

        cBackColor = 0x88008888;
        cRimColor = 0x88008888;
    }
    SAMPLE_DOFUNC_NO_RETURN(HI_GO_FillRect(s_stOsdInfo.hOsdSurface, pstRect, cBackColor, HIGO_COMPOPT_NONE), s32Ret);
    SAMPLE_DOFUNC_NO_RETURN(HI_GO_DrawRect(s_stOsdInfo.hOsdSurface, pstRect, cRimColor), s32Ret);
    SAMPLE_DOFUNC_NO_RETURN(HI_GO_SetTextColor(s_stOsdInfo.hFont, cTextColor), s32Ret);
    SAMPLE_DOFUNC_NO_RETURN(HI_GO_TextOutEx(s_stOsdInfo.hFont, s_stOsdInfo.hOsdSurface, pszText, pstRect, HIGO_LAYOUT_LEFT), s32Ret);
    SAMPLE_DOFUNC_RETURN(HI_GO_RefreshLayer(s_stOsdInfo.hOsdLayer, NULL), s32Ret);

    return HI_SUCCESS;
}

HI_S32 Sample_Osd_ShowElem(SAMPLE_OSD_ELEMENT_INFO_S *pstElm, HI_BOOL bHighLight)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_CHAR szContent[256];

    SAMPLE_CHECK_POINTER_RETURN(pstElm);
    memset(szContent, 0x00, 256*sizeof(HI_CHAR));
    if (pstElm->enType == SAMPLE_OSD_ELEMENT_BOTH)
    {
        if ((pstElm->u32StrNum == 2) && (pstElm->u32ValNum == 2))
            snprintf(szContent, 256, "%s%d%s%d", pstElm->szContent0, pstElm->u32Value[0],  pstElm->szContent1, pstElm->u32Value[1]);
        else if ((pstElm->u32StrNum == 2) && (pstElm->u32ValNum == 1))
            snprintf(szContent, 256, "%s%d%s", pstElm->szContent0, pstElm->u32Value[0],  pstElm->szContent1);
        else if ((pstElm->u32StrNum == 1) && (pstElm->u32ValNum == 1))
            snprintf(szContent, 256, "%s%d", pstElm->szContent0, pstElm->u32Value[0]);
        else
            sample_printf("not support(strNum, valNum) = %d, %d)!\n", pstElm->u32StrNum, pstElm->u32ValNum);
    }
    else
    {
        if (pstElm->u32StrNum == 2)
            snprintf(szContent, 256, "%s%s", pstElm->szContent0, pstElm->szContent1);
        else
            snprintf(szContent, 256, "%s", pstElm->szContent0);
    }
    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_DrawString(szContent, &pstElm->stRect, bHighLight), s32Ret);

    return HI_SUCCESS;
}
HI_S32 Sample_Osd_EnableShow(HI_BOOL bVisbile)
{
    HI_S32 s32Ret = HI_SUCCESS;
    SAMPLE_DOFUNC_RETURN(HI_GO_ShowLayer(s_stOsdInfo.hOsdLayer, bVisbile), s32Ret);
    return HI_SUCCESS;
}

HI_VOID Sample_Osd_DeInit(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    SAMPLE_DOFUNC_NO_RETURN(HI_GO_DestroyText(s_stOsdInfo.hFont), s32Ret);
    SAMPLE_DOFUNC_NO_RETURN(HI_GO_DestroyLayer(s_stOsdInfo.hOsdLayer), s32Ret);
    SAMPLE_DOFUNC_NO_RETURN(HI_GO_Deinit(), s32Ret);
    return;
}

static HI_VOID SampleSearchGetRecPara(SAMPLE_OSD_SEARCH_VIEW_E enType, SAMPLE_OSD_ELEMENT_INFO_S *pstElem)
{
    pstElem->stRect.x = 300;
    pstElem->stRect.y = 100 + 100*enType;
    pstElem->stRect.w = 260;
    pstElem->stRect.h = 30;
    if (SAMPLE_OSD_SEARCH_BEGIN == enType)
    {
        pstElem->stRect.x = 100;
        pstElem->stRect.w = 300;
    }
    if (SAMPLE_OSD_SEARCH_START == enType)
    {
        pstElem->stRect.x = 500;
        pstElem->stRect.w = 50;
    }
    if (SAMPLE_OSD_SEARCH_REPEAT == enType)
    {
        pstElem->stRect.x = 500;
        pstElem->stRect.w = 500;
    }
    return;
}
HI_S32 Sample_Osd_ShowSearchView(HI_BOOL bRepeat)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_RECT stRect = {0, 0, 1920, 1000};

    SAMPLE_OSD_CHECK_INIT_RETURN(s_stOsdInfo.bInitFlag);

    s_stSearchInfo.bInitFlag = HI_TRUE;
    memset(&s_stSearchInfo.stElem, 0x00, (SAMPLE_OSD_SEARCH_BUTT + 1)*sizeof(SAMPLE_OSD_ELEMENT_INFO_S));
    SAMPLE_DOFUNC_NO_RETURN(HI_GO_FillRect(s_stOsdInfo.hOsdSurface, &stRect, 0xFF888888, HIGO_COMPOPT_NONE), s32Ret);
    s_stSearchInfo.stElem[0].enType = SAMPLE_OSD_ELEMENT_STRING;
    SampleSearchGetRecPara(SAMPLE_OSD_SEARCH_BEGIN, &s_stSearchInfo.stElem[0]);
    s_stSearchInfo.stElem[0].u32StrNum = 1;
    s_stSearchInfo.stElem[0].u32ValNum = 0;
    memcpy(s_stSearchInfo.stElem[0].szContent0, "manual search(only support -C)", strlen("manual search(only support -C)"));
    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_ShowElem(&s_stSearchInfo.stElem[0], HI_FALSE), s32Ret);

    s_stSearchInfo.stElem[1].enType = SAMPLE_OSD_ELEMENT_BOTH;
    SampleSearchGetRecPara(SAMPLE_OSD_SEARCH_TUNER_ID, &s_stSearchInfo.stElem[1]);
    s_stSearchInfo.stElem[1].u32StrNum = 1;
    s_stSearchInfo.stElem[1].u32ValNum = 1;
    s_stSearchInfo.stElem[1].u32Value[0] = 0;
    memcpy(s_stSearchInfo.stElem[1].szContent0, "tunerID:             ", strlen("tunerID:             "));
    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_ShowElem(&s_stSearchInfo.stElem[1], HI_TRUE), s32Ret);
    s_stSearchInfo.enCurPos = SAMPLE_OSD_SEARCH_TUNER_ID;


    s_stSearchInfo.stElem[2].enType = SAMPLE_OSD_ELEMENT_BOTH;
    SampleSearchGetRecPara(SAMPLE_OSD_SEARCH_FREQ, &s_stSearchInfo.stElem[2]);
    s_stSearchInfo.stElem[2].u32StrNum = 1;
    s_stSearchInfo.stElem[2].u32ValNum = 1;
    s_stSearchInfo.stElem[2].u32Value[0] = 778;
    memcpy(s_stSearchInfo.stElem[2].szContent0, "search freq(MHz):   ", strlen("search freq(MHz):   "));
    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_ShowElem(&s_stSearchInfo.stElem[2], HI_FALSE), s32Ret);

    s_stSearchInfo.stElem[3].enType = SAMPLE_OSD_ELEMENT_BOTH;
    SampleSearchGetRecPara(SAMPLE_OSD_SEARCH_SYMRATE, &s_stSearchInfo.stElem[3]);
    s_stSearchInfo.stElem[3].u32StrNum = 1;
    s_stSearchInfo.stElem[3].u32ValNum = 1;
    s_stSearchInfo.stElem[3].u32Value[0] = 6875;
    memcpy(s_stSearchInfo.stElem[3].szContent0, "symbol rate(kS/s):  ", strlen("symbol rate(kS/s):  "));
    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_ShowElem(&s_stSearchInfo.stElem[3], HI_FALSE), s32Ret);

    s_stSearchInfo.stElem[4].enType = SAMPLE_OSD_ELEMENT_BOTH;
    SampleSearchGetRecPara(SAMPLE_OSD_SEARCH_QAM, &s_stSearchInfo.stElem[4]);
    s_stSearchInfo.stElem[4].u32StrNum = 2;
    s_stSearchInfo.stElem[4].u32ValNum = 1;
    s_stSearchInfo.stElem[4].u32Value[0] = 64;
    memcpy(s_stSearchInfo.stElem[4].szContent0, "modulate type:   <|QAM", strlen("modulate type:   <|QAM"));
    memcpy(s_stSearchInfo.stElem[4].szContent1, "|>", strlen("|>"));
    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_ShowElem(&s_stSearchInfo.stElem[4], HI_FALSE), s32Ret);

    s_stSearchInfo.stElem[5].enType = SAMPLE_OSD_ELEMENT_STRING;
    SampleSearchGetRecPara(SAMPLE_OSD_SEARCH_START, &s_stSearchInfo.stElem[5]);
    memcpy(s_stSearchInfo.stElem[5].szContent0, "start", strlen("start"));
    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_ShowElem(&s_stSearchInfo.stElem[5], HI_FALSE), s32Ret);

    if (HI_TRUE == bRepeat)
    {
        s_stSearchInfo.stElem[6].enType = SAMPLE_OSD_ELEMENT_STRING;
        SampleSearchGetRecPara(SAMPLE_OSD_SEARCH_REPEAT, &s_stSearchInfo.stElem[6]);
        memcpy(s_stSearchInfo.stElem[6].szContent0, "No program! please check the configuration and try again!", strlen("No program! please check the configuration and try again!"));
        SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_ShowElem(&s_stSearchInfo.stElem[6], HI_FALSE), s32Ret);
    }
    return HI_SUCCESS;
}

HI_S32 Sample_Osd_GetSearchElemByType(SAMPLE_OSD_SEARCH_VIEW_E enType, SAMPLE_OSD_ELEMENT_INFO_S *pstElem)
{
    SAMPLE_CHECK_POINTER_RETURN(pstElem);
    SAMPLE_OSD_CHECK_INIT_RETURN(s_stOsdInfo.bInitFlag);
    SAMPLE_OSD_CHECK_INIT_RETURN(s_stSearchInfo.bInitFlag);

    memcpy(pstElem, &s_stSearchInfo.stElem[enType], sizeof(SAMPLE_OSD_ELEMENT_INFO_S));
    return HI_SUCCESS;
}


HI_S32 Sample_Osd_GetCurSearchElem(SAMPLE_OSD_SEARCH_VIEW_E *penType, SAMPLE_OSD_ELEMENT_INFO_S *pstElem)
{
    SAMPLE_CHECK_POINTER_RETURN(penType);
    SAMPLE_CHECK_POINTER_RETURN(pstElem);
    SAMPLE_OSD_CHECK_INIT_RETURN(s_stOsdInfo.bInitFlag);
    SAMPLE_OSD_CHECK_INIT_RETURN(s_stSearchInfo.bInitFlag);

    *penType = s_stSearchInfo.enCurPos;
    memcpy(pstElem, &s_stSearchInfo.stElem[s_stSearchInfo.enCurPos], sizeof(SAMPLE_OSD_ELEMENT_INFO_S));
    return HI_SUCCESS;
}

HI_S32 Sample_Osd_GetNextSearchElem(SAMPLE_OSD_SEARCH_VIEW_E *penType, SAMPLE_OSD_ELEMENT_INFO_S *pstElem)
{
    SAMPLE_OSD_SEARCH_VIEW_E enNext = s_stSearchInfo.enCurPos;
    SAMPLE_CHECK_POINTER_RETURN(penType);
    SAMPLE_CHECK_POINTER_RETURN(pstElem);
    SAMPLE_OSD_CHECK_INIT_RETURN(s_stOsdInfo.bInitFlag);
    SAMPLE_OSD_CHECK_INIT_RETURN(s_stSearchInfo.bInitFlag);

    if (SAMPLE_OSD_SEARCH_START == enNext)
    {
        enNext = SAMPLE_OSD_SEARCH_TUNER_ID;
    }
    else
    {
        enNext += 1;
    }
    *penType = enNext;
    memcpy(pstElem, &s_stSearchInfo.stElem[enNext], sizeof(SAMPLE_OSD_ELEMENT_INFO_S));
    return HI_SUCCESS;
}

HI_S32 Sample_Osd_GetPrevSearchElem(SAMPLE_OSD_SEARCH_VIEW_E *penType, SAMPLE_OSD_ELEMENT_INFO_S *pstElem)
{
    SAMPLE_OSD_SEARCH_VIEW_E enPrev = s_stSearchInfo.enCurPos;
    SAMPLE_CHECK_POINTER_RETURN(penType);
    SAMPLE_CHECK_POINTER_RETURN(pstElem);
    SAMPLE_OSD_CHECK_INIT_RETURN(s_stOsdInfo.bInitFlag);
    SAMPLE_OSD_CHECK_INIT_RETURN(s_stSearchInfo.bInitFlag);

    if (SAMPLE_OSD_SEARCH_TUNER_ID == enPrev)
    {
        enPrev = SAMPLE_OSD_SEARCH_START;
    }
    else
    {
        enPrev -= 1;
    }
    *penType = enPrev;
    memcpy(pstElem, &s_stSearchInfo.stElem[enPrev], sizeof(SAMPLE_OSD_ELEMENT_INFO_S));
    return HI_SUCCESS;
}

HI_S32 Sample_Osd_SetSearchElem(SAMPLE_OSD_SEARCH_VIEW_E enType, SAMPLE_OSD_ELEMENT_INFO_S *pstElem, HI_BOOL bHightLight)
{
    HI_S32 s32Ret = HI_SUCCESS;

    SAMPLE_CHECK_POINTER_RETURN(pstElem);
    SAMPLE_OSD_CHECK_INIT_RETURN(s_stOsdInfo.bInitFlag);
    SAMPLE_OSD_CHECK_INIT_RETURN(s_stSearchInfo.bInitFlag);

    memcpy(&s_stSearchInfo.stElem[enType], pstElem, sizeof(SAMPLE_OSD_ELEMENT_INFO_S));
    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_ShowElem(&s_stSearchInfo.stElem[enType], bHightLight), s32Ret);
    if ((HI_TRUE == bHightLight) && (s_stSearchInfo.enCurPos != enType))
    {
        SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_ShowElem(&s_stSearchInfo.stElem[s_stSearchInfo.enCurPos], HI_FALSE), s32Ret);
        s_stSearchInfo.enCurPos = enType;
    }
    return HI_SUCCESS;
}

static HI_VOID SampleChnListGetRect(HI_U32 idx, HI_RECT *pstRect)
{
    pstRect->x = 50;
    pstRect->y = 50 *idx + 50;
    pstRect->w = 300;
    pstRect->h = 30;
}

HI_S32 Sample_Osd_ChannelInit(HI_U32 u32TotalChannel)
{
    if ((u32TotalChannel >= SAMPLE_MAX_PROG_NUM) || (0 == u32TotalChannel))
    {
        sample_printf("only support (%d) channels, input is %d!\n", SAMPLE_MAX_PROG_NUM, u32TotalChannel);
        return HI_FAILURE;
    }

    memset(&s_stChnInfo, 0x00, sizeof(s_stChnInfo));
    s_stChnInfo.bInitFlag = HI_TRUE;
    s_stChnInfo.u32TotalNum = u32TotalChannel;
    return HI_SUCCESS;
}


HI_S32 Sample_Osd_ChannelAdd(HI_U32 idx, HI_CHAR *pszChnName)
{
    SAMPLE_OSD_CHECK_INIT_RETURN(s_stChnInfo.bInitFlag);
    SAMPLE_CHECK_POINTER_RETURN(pszChnName);

    if (idx >= s_stChnInfo.u32TotalNum)
    {
        sample_printf("only has (%d) channels, input is %d!\n", s_stChnInfo.u32TotalNum, idx);
        return HI_FAILURE;
    }

    snprintf(s_stChnInfo.stElem[idx].szContent0, 255, " %02d %s", idx, pszChnName);
    s_stChnInfo.stElem[idx].enType = SAMPLE_OSD_ELEMENT_STRING;
    s_stChnInfo.stElem[idx].u32StrNum = 1;
    s_stChnInfo.stElem[idx].u32ValNum = 0;
    SampleChnListGetRect(idx, &s_stChnInfo.stElem[idx].stRect);
    return HI_SUCCESS;
}

HI_S32 Sample_Osd_ChannelGetCurrent(HI_U32 *pidx, HI_CHAR *pszChnName)
{
    SAMPLE_OSD_CHECK_INIT_RETURN(s_stChnInfo.bInitFlag);
    SAMPLE_CHECK_POINTER_RETURN(pidx);
    SAMPLE_CHECK_POINTER_RETURN(pszChnName);

    *pidx = s_stChnInfo.u32CurFocusIdx;
    memcpy(pszChnName, s_stChnInfo.stElem[*pidx].szContent0, strlen(s_stChnInfo.stElem[*pidx].szContent0));
    return HI_SUCCESS;
}

HI_S32 Sample_Osd_ChannelDisplay(HI_U32 u32CurFocus)
{
    HI_U32 i = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_RECT stRect = {0, 0, 1920, 1000};
    HI_BOOL bHighlight = HI_FALSE;

    SAMPLE_OSD_CHECK_INIT_RETURN(s_stChnInfo.bInitFlag);
    if (u32CurFocus >= s_stChnInfo.u32TotalNum)
    {
        sample_printf("only has (%d) channels, input is %d!\n", s_stChnInfo.u32TotalNum, u32CurFocus);
        return HI_FAILURE;
    }

    SAMPLE_DOFUNC_NO_RETURN(HI_GO_FillRect(s_stOsdInfo.hOsdSurface, &stRect, 0x00000000, HIGO_COMPOPT_NONE), s32Ret);

    for (i = 0; i < s_stChnInfo.u32TotalNum; i++)
    {
        bHighlight = HI_FALSE;
        if (u32CurFocus == i)
        {
            bHighlight = HI_TRUE;
            s_stChnInfo.u32CurFocusIdx = u32CurFocus;
        }
        SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_ShowElem(&s_stChnInfo.stElem[i], bHighlight), s32Ret);
    }

    return HI_SUCCESS;
}

static HI_VOID SamplePlayGetRect(HI_BOOL bADLevel, HI_U32 u32Idx, HI_RECT *pstRect)
{
    pstRect->x = 1500;
    if (HI_TRUE != bADLevel)
    {
        pstRect->y = 120 + 32*u32Idx;
    }
    pstRect->w = 350;
    pstRect->h = 28;

    if (HI_TRUE == bADLevel)
    {
        pstRect->y = ((0 == u32Idx) ? 120 : 152);
        pstRect->x = ((1 >= u32Idx) ? 1100 : 1100 + 90*(u32Idx-1));
        pstRect->w = ((0 == u32Idx) ? 350 : 80);
        sample_printf("[%d](x,y,w,h) = (%d, %d, %d, %d)\n", u32Idx, pstRect->x, pstRect->y, pstRect->w, pstRect->h);
    }

    return;
}

HI_S32 Sample_Osd_PlayCtrlInit(HI_U32 u32TotalChannel, HI_U32 u32ADLevel)
{
    HI_U32 i = 0;
    HI_CHAR *szContent[4] =
    {
        "    OFF",
        "    LOW",
        "    MID",
        "    HIGH"
    };

    if ((u32TotalChannel >= SAMPLE_MAX_AUDIO_NUM) || (0 == u32TotalChannel))
    {
        sample_printf("only support (%d) audio, input is %d!\n", SAMPLE_MAX_PROG_NUM, u32TotalChannel);
        return HI_FAILURE;
    }

    memset(&s_stPlayCtrlInfo, 0x00, sizeof(s_stPlayCtrlInfo));
    s_stPlayCtrlInfo.bInitFlag = HI_TRUE;
    s_stPlayCtrlInfo.u32AudNum = u32TotalChannel;
    s_stPlayCtrlInfo.u32ADLevel = u32ADLevel;
    s_stPlayCtrlInfo.u32Focus = 1;

    memset(&s_stPlayCtrlInfo.stAudElem[0], 0x00, sizeof(SAMPLE_OSD_ELEMENT_INFO_S));
    memcpy(s_stPlayCtrlInfo.stAudElem[0].szContent0, "SOUNDTRACK", strlen("SOUNDTRACK"));
    s_stPlayCtrlInfo.stAudElem[0].enType = SAMPLE_OSD_ELEMENT_STRING;
    s_stPlayCtrlInfo.stAudElem[0].u32StrNum = 1;
    s_stPlayCtrlInfo.stAudElem[0].u32ValNum = 0;
    SamplePlayGetRect(HI_FALSE, 0, &s_stPlayCtrlInfo.stAudElem[0].stRect);

    memset(&s_stPlayCtrlInfo.stADLeElem[0], 0x00, sizeof(SAMPLE_OSD_ELEMENT_INFO_S));
    memcpy(s_stPlayCtrlInfo.stADLeElem[0].szContent0, "Audio Description", strlen("Audio Description"));
    s_stPlayCtrlInfo.stADLeElem[0].enType = SAMPLE_OSD_ELEMENT_STRING;
    s_stPlayCtrlInfo.stADLeElem[0].u32StrNum = 1;
    s_stPlayCtrlInfo.stADLeElem[0].u32ValNum = 0;
    SamplePlayGetRect(HI_TRUE, 0, &s_stPlayCtrlInfo.stADLeElem[0].stRect);
    sample_printf("s_stPlayCtrlInfo.stADLeElem[0].szContent0:%s\n", s_stPlayCtrlInfo.stADLeElem[0].szContent0);
    for (i = 1; i < 5; i++)
    {
        memset(&s_stPlayCtrlInfo.stADLeElem[i], 0x00, sizeof(SAMPLE_OSD_ELEMENT_INFO_S));
        memcpy(s_stPlayCtrlInfo.stADLeElem[i].szContent0, szContent[i - 1], strlen(szContent[i - 1]));
        s_stPlayCtrlInfo.stADLeElem[i].enType = SAMPLE_OSD_ELEMENT_STRING;
        s_stPlayCtrlInfo.stADLeElem[i].u32StrNum = 1;
        s_stPlayCtrlInfo.stADLeElem[i].u32ValNum = 0;
        SamplePlayGetRect(HI_TRUE, i, &s_stPlayCtrlInfo.stADLeElem[i].stRect);
        sample_printf("s_stPlayCtrlInfo.stADLeElem[%d].szContent0:%s\n", i, s_stPlayCtrlInfo.stADLeElem[i].szContent0);
    }

    return HI_SUCCESS;
}

HI_S32 Sample_Osd_PlayCtrlAdd(HI_U32 idx, SAMPLE_OSD_AUDIO_INFO_S *pstAudInfo)
{
    HI_U32 i = 0;
    HI_U32 u32Pos = 0;
    HI_U32 u32LanguageLen = 0;
    SAMPLE_OSD_CHECK_INIT_RETURN(s_stPlayCtrlInfo.bInitFlag);
    SAMPLE_CHECK_POINTER_RETURN(pstAudInfo);

    if (idx >= s_stPlayCtrlInfo.u32AudNum)
    {
        sample_printf("only has (%d) audio, input is %d!\n", s_stPlayCtrlInfo.u32AudNum, idx);
        return HI_FAILURE;
    }

    idx += 1;
    u32LanguageLen = strlen(pstAudInfo->szLanguage);
    if (u32LanguageLen >= MAX_AUDIO_LANGUAGE_LENGTH)
        u32LanguageLen = 7;

    memset(&s_stPlayCtrlInfo.stAudoInfo[idx], 0x00, sizeof(SAMPLE_OSD_AUDIO_INFO_S));
    memset(&s_stPlayCtrlInfo.stAudElem[idx], 0x00, sizeof(SAMPLE_OSD_ELEMENT_INFO_S));

    memcpy(s_stPlayCtrlInfo.stAudoInfo[idx].szLanguage, pstAudInfo->szLanguage, u32LanguageLen);
    s_stPlayCtrlInfo.stAudoInfo[idx].u32ADType = pstAudInfo->u32ADType;

    memcpy(s_stPlayCtrlInfo.stAudElem[idx].szContent0, "    ", strlen("    "));
    u32Pos += strlen("    ");

    if (!strncmp("eng", pstAudInfo->szLanguage, 3))
    {
        memcpy(s_stPlayCtrlInfo.stAudElem[idx].szContent0 + u32Pos, "ENGLISH", strlen("ENGLISH"));
        u32Pos += strlen("ENGLISH");
    }
    else if (!strncmp("chi", pstAudInfo->szLanguage, 3))
    {
        memcpy(s_stPlayCtrlInfo.stAudElem[idx].szContent0 + u32Pos, "CHINESE", strlen("CHINESE"));
        u32Pos += strlen("CHINESE");
    }
    else if (!strncmp("ger", pstAudInfo->szLanguage, 3))
    {
        memcpy(s_stPlayCtrlInfo.stAudElem[idx].szContent0 + u32Pos, "GERMAN", strlen("GERMAN"));
        u32Pos += strlen("GERMAN");
    }
    else
    {
        memcpy(s_stPlayCtrlInfo.stAudElem[idx].szContent0 + u32Pos, s_stPlayCtrlInfo.stAudoInfo[idx].szLanguage, u32LanguageLen);
        u32Pos += u32LanguageLen;
    }

    if (u32Pos < 15)
    {
        for (i = u32Pos; i < 15; i++)
        {
            s_stPlayCtrlInfo.stAudElem[idx].szContent0[i] = ' ';
        }
        u32Pos = 15;
    }

    switch(pstAudInfo->stStreamInfo.enStreamType)
    {
        case MS12_STREAM_DD:
            memcpy(s_stPlayCtrlInfo.stAudElem[idx].szContent0 + u32Pos, "Dolby Digital", strlen("Dolby Digital"));
            u32Pos += strlen("Dolby Digital");
            break;
        case MS12_STREAM_DDP:
            memcpy(s_stPlayCtrlInfo.stAudElem[idx].szContent0 + u32Pos, "Dolby Digital Plus", strlen("Dolby Digital Plus"));
            u32Pos += strlen("Dolby Digital Plus");
            break;
        case MS12_STREAM_ATMOS:
            memcpy(s_stPlayCtrlInfo.stAudElem[idx].szContent0 + u32Pos, "Dolby Atmos", strlen("Dolby Atmos"));
            u32Pos += strlen("Dolby Atmos");
            break;
        case MS12_STREAM_AAC:
            memcpy(s_stPlayCtrlInfo.stAudElem[idx].szContent0 + u32Pos, "AAC", strlen("AAC"));
            u32Pos += strlen("AAC");
            break;
        default:
            break;
    }

    if (u32Pos < 37)
    {
        for (i = u32Pos; i < 37; i++)
        {
            s_stPlayCtrlInfo.stAudElem[idx].szContent0[i] = ' ';
        }
        u32Pos = 37;
    }

    if (1 == pstAudInfo->u32ADType)
    {
        memcpy(s_stPlayCtrlInfo.stAudElem[idx].szContent0 + u32Pos, "AD", strlen("AD"));
        u32Pos += strlen("AD");
    }

    sample_printf("s_stPlayCtrlInfo.stAudElem[%d].szContent0:%s\n", idx, s_stPlayCtrlInfo.stAudElem[idx].szContent0);
    s_stPlayCtrlInfo.stAudElem[idx].enType = SAMPLE_OSD_ELEMENT_STRING;
    s_stPlayCtrlInfo.stAudElem[idx].u32StrNum = 1;
    s_stPlayCtrlInfo.stAudElem[idx].u32ValNum = 0;
    SamplePlayGetRect(HI_FALSE, idx, &s_stPlayCtrlInfo.stAudElem[idx].stRect);
    return HI_SUCCESS;
}

HI_S32 Sample_Osd_PlayCtrlGetCurrentFocus(HI_U32 *pu32AudIdx, HI_U32 *pu32ADLevel)
{
    SAMPLE_OSD_CHECK_INIT_RETURN(s_stPlayCtrlInfo.bInitFlag);
    SAMPLE_CHECK_POINTER_RETURN(pu32AudIdx);
    SAMPLE_CHECK_POINTER_RETURN(pu32ADLevel);

    *pu32ADLevel = s_stPlayCtrlInfo.u32ADLevel;
    *pu32AudIdx = s_stPlayCtrlInfo.u32Focus - 1;
    return HI_SUCCESS;
}
HI_S32 Sample_Osd_PlayCtrlGetCurrentUsed(HI_U32 *pu32AudIdx, HI_U32 *pu32ADLevel)
{
    SAMPLE_OSD_CHECK_INIT_RETURN(s_stPlayCtrlInfo.bInitFlag);
    SAMPLE_CHECK_POINTER_RETURN(pu32AudIdx);
    SAMPLE_CHECK_POINTER_RETURN(pu32ADLevel);

    *pu32ADLevel = s_stPlayCtrlInfo.u32CurADLev;
    *pu32AudIdx = s_stPlayCtrlInfo.u32CurAudIdx - 1;
    return HI_SUCCESS;
}

HI_S32 Sample_Osd_PlayCtrlSetCurrentFocus(HI_U32 u32AudIdx, HI_U32 u32ADLevel)
{
    SAMPLE_OSD_CHECK_INIT_RETURN(s_stPlayCtrlInfo.bInitFlag);
    s_stPlayCtrlInfo.u32ADLevel = u32ADLevel;
    s_stPlayCtrlInfo.u32Focus = u32AudIdx + 1;
    return HI_SUCCESS;
}

HI_S32 Sample_Osd_PlayCtrlSetCurrentUsed(HI_U32 u32AudIdx, HI_U32 u32ADLevel)
{
    SAMPLE_OSD_CHECK_INIT_RETURN(s_stPlayCtrlInfo.bInitFlag);
    s_stPlayCtrlInfo.u32CurADLev = u32ADLevel;
    s_stPlayCtrlInfo.u32CurAudIdx = u32AudIdx + 1;
    return HI_SUCCESS;
}

HI_S32 Sample_Osd_PlayCtrlDisplay(HI_BOOL bADLevel)
{
    HI_U32 i = 0;
    HI_CHAR ch = ' ';
    HI_S32 s32Ret = HI_SUCCESS;
    HI_RECT stRect = {0, 0, 1920, 1000};
    HI_BOOL bHighlight = HI_FALSE;
    HI_U32 u32Level[5] = {0xFF, 0, 1, 2, 3};

    SAMPLE_OSD_CHECK_INIT_RETURN(s_stPlayCtrlInfo.bInitFlag);

    SAMPLE_DOFUNC_NO_RETURN(HI_GO_FillRect(s_stOsdInfo.hOsdSurface, &stRect, 0x00000000, HIGO_COMPOPT_NONE), s32Ret);

    for (i = 0; i < s_stPlayCtrlInfo.u32AudNum + 1; i++)
    {
        bHighlight = HI_FALSE;

        if (s_stPlayCtrlInfo.u32Focus == i)
            bHighlight = (HI_TRUE == bADLevel) ? HI_FALSE : HI_TRUE;

        if (0 != i)
        {
            s_stPlayCtrlInfo.stAudElem[i].szContent0[0] = ch;
            s_stPlayCtrlInfo.stAudElem[i].szContent0[1] = ch;
            s_stPlayCtrlInfo.stAudElem[i].szContent0[2] = ch;
            s_stPlayCtrlInfo.stAudElem[i].szContent0[3] = ch;
        }

        if ((0 < s_stPlayCtrlInfo.stAudElem[i].stRect.h) && (0 < s_stPlayCtrlInfo.stAudElem[i].stRect.w))
        {
            SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_ShowElem(&s_stPlayCtrlInfo.stAudElem[i], bHighlight), s32Ret);
        }
    }

    if (0 != s_stPlayCtrlInfo.stAudoInfo[s_stPlayCtrlInfo.u32CurAudIdx].u32ADType)
    {
        for (i = 0; i < 5; i++)
        {
            bHighlight = HI_FALSE;

            if (s_stPlayCtrlInfo.u32ADLevel == u32Level[i])
                bHighlight = (HI_TRUE == bADLevel) ? HI_TRUE : HI_FALSE;

            if (0 != i)
            {
                s_stPlayCtrlInfo.stADLeElem[i].szContent0[0] = ch;
                s_stPlayCtrlInfo.stADLeElem[i].szContent0[1] = ch;
                s_stPlayCtrlInfo.stADLeElem[i].szContent0[2] = ch;
                s_stPlayCtrlInfo.stADLeElem[i].szContent0[3] = ch;
            }

            if ((0 < s_stPlayCtrlInfo.stADLeElem[i].stRect.h) && (0 < s_stPlayCtrlInfo.stADLeElem[i].stRect.w))
            {
                SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_ShowElem(&s_stPlayCtrlInfo.stADLeElem[i], bHighlight), s32Ret);
            }
        }
    }

    return HI_SUCCESS;
}

HI_S32 Sample_Osd_AC4Display(HI_BOOL bDispPlay)
{
    SAMPLE_OSD_ELEMENT_INFO_S stAc4Elm;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_RECT stRect = {0, 0, 1920, 1080};

    memset(&stAc4Elm, 0x00, sizeof(stAc4Elm));
    SAMPLE_DOFUNC_NO_RETURN(HI_GO_FillRect(s_stOsdInfo.hOsdSurface, &stRect, 0x00000000, HIGO_COMPOPT_NONE), s32Ret);

    if (HI_FALSE == bDispPlay)
        return HI_SUCCESS;

    Sample_Osd_EnableShow(HI_TRUE);

    stAc4Elm.enType = SAMPLE_OSD_ELEMENT_STRING;
    stAc4Elm.u32StrNum = 1;
    stAc4Elm.stRect.x = 1000;
    stAc4Elm.stRect.y = 800;
    stAc4Elm.stRect.w = 300;
    stAc4Elm.stRect.h = 40;
    memcpy(stAc4Elm.szContent0, "Not Support AC4 audio!", strlen("Not Support AC4 audio!"));

    SAMPLE_DOFUNC_NO_RETURN(Sample_Osd_ShowElem(&stAc4Elm, HI_TRUE), s32Ret);

    return HI_SUCCESS;
}

