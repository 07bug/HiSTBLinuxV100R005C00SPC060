#include "sample_ms12.h"

#ifndef __SAMPLE_OSD_H__
#define __SAMPLE_OSD_H__

#ifdef __cplusplus
extern "C" {
#endif
#define MAX_STRING_DISPLAY_LENGTH   (256)
#define MAX_AUDIO_LANGUAGE_LENGTH   (8)
typedef enum
{
    SAMPLE_OSD_SEARCH_BEGIN = 0,
    SAMPLE_OSD_SEARCH_TUNER_ID,
    SAMPLE_OSD_SEARCH_FREQ,
    SAMPLE_OSD_SEARCH_SYMRATE,
    SAMPLE_OSD_SEARCH_QAM,
    SAMPLE_OSD_SEARCH_START,
    SAMPLE_OSD_SEARCH_BUTT,
    SAMPLE_OSD_SEARCH_REPEAT
}SAMPLE_OSD_SEARCH_VIEW_E;
typedef enum
{
    SAMPLE_OSD_ELEMENT_STRING = 0,
    SAMPLE_OSD_ELEMENT_NUMBER,
    SAMPLE_OSD_ELEMENT_BOTH,
    SAMPLE_OSD_ELEMENT_BUTT
}SAMPLE_OSD_ELEMENT_TYPE_E;
typedef struct tagSAMPLE_OSD_AUDIO_INFO_S
{
    HI_CHAR szLanguage[MAX_AUDIO_LANGUAGE_LENGTH];
    HI_U32 u32ADType;/*0 -- no; 1 -- yes*/
    HA_MS12_GET_STREAM_INFO_S stStreamInfo;
}SAMPLE_OSD_AUDIO_INFO_S;
typedef struct tagSAMPLE_OSD_ELEMENT_INFO_S
{
    HI_RECT stRect;
    SAMPLE_OSD_ELEMENT_TYPE_E enType;
    HI_U32 u32ValNum;
    HI_U32 u32StrNum;
    HI_U32 u32Value[2];
    HI_CHAR szContent0[MAX_STRING_DISPLAY_LENGTH];
    HI_CHAR szContent1[MAX_STRING_DISPLAY_LENGTH];
}SAMPLE_OSD_ELEMENT_INFO_S;
HI_S32 Sample_Osd_Init(HI_VOID);
HI_VOID Sample_Osd_DeInit(HI_VOID);
HI_S32 Sample_Osd_EnableShow(HI_BOOL bVisbile);
HI_S32 Sample_Osd_ShowSearchView(HI_BOOL bRepeat);
HI_S32 Sample_Osd_HideSearchView();
HI_S32 Sample_Osd_GetSearchElemByType(SAMPLE_OSD_SEARCH_VIEW_E enType, SAMPLE_OSD_ELEMENT_INFO_S *pstElem);
HI_S32 Sample_Osd_GetCurSearchElem(SAMPLE_OSD_SEARCH_VIEW_E *penType, SAMPLE_OSD_ELEMENT_INFO_S *pstElem);
HI_S32 Sample_Osd_SetCurSearchElem(SAMPLE_OSD_SEARCH_VIEW_E *penType, SAMPLE_OSD_ELEMENT_INFO_S *pstElem);
HI_S32 Sample_Osd_GetNextSearchElem(SAMPLE_OSD_SEARCH_VIEW_E *penType, SAMPLE_OSD_ELEMENT_INFO_S *pstElem);
HI_S32 Sample_Osd_GetPrevSearchElem(SAMPLE_OSD_SEARCH_VIEW_E *penType, SAMPLE_OSD_ELEMENT_INFO_S *pstElem);
HI_S32 Sample_Osd_SetSearchElem(SAMPLE_OSD_SEARCH_VIEW_E enType, SAMPLE_OSD_ELEMENT_INFO_S *pstElem, HI_BOOL bHightLight);
HI_S32 Sample_Osd_ChannelInit(HI_U32 u32TotalChannel);
HI_S32 Sample_Osd_ChannelAdd(HI_U32 idx, HI_CHAR *pszChnName);
HI_S32 Sample_Osd_ChannelDisplay(HI_U32 u32CurPlay);
HI_S32 Sample_Osd_ChannelGetCurrent(HI_U32 *pidx, HI_CHAR *pszChnName);
HI_S32 Sample_Osd_PlayCtrlInit(HI_U32 u32TotalChannel, HI_U32 u32ADLevel);
HI_S32 Sample_Osd_PlayCtrlAdd(HI_U32 idx, SAMPLE_OSD_AUDIO_INFO_S *pstAudInfo);
HI_S32 Sample_Osd_PlayCtrlGetCurrentFocus(HI_U32 *pu32AudIdx, HI_U32 *pu32ADLevel);
HI_S32 Sample_Osd_PlayCtrlGetCurrentUsed(HI_U32 *pu32AudIdx, HI_U32 *pu32ADLevel);
HI_S32 Sample_Osd_PlayCtrlSetCurrentFocus(HI_U32 u32AudIdx, HI_U32 u32ADLevel);
HI_S32 Sample_Osd_PlayCtrlSetCurrentUsed(HI_U32 u32AudIdx, HI_U32 u32ADLevel);
HI_S32 Sample_Osd_PlayCtrlDisplay(HI_BOOL bADLevel);
HI_S32 Sample_Osd_AC4Display(HI_BOOL bDispPlay);

#ifdef __cplusplus
}
#endif

#endif

