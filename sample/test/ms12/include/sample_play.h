#include "sample_ms12.h"
#include "sample_osd.h"

#ifndef __SAMPLE_PLAY_H__
#define __SAMPLE_PLAY_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef HI_S32 (*SAMPLE_AC4_PROCESS_FB)(HI_BOOL bAc4Audio);

HI_S32 Sample_Play_SaveProgInfo(PMT_COMPACT_TBL *pstProgInfo, HI_HANDLE hAvplay);
HI_S32 Sample_Play_PlayByIdx(HI_U32 u32Idx);
HI_S32 Sample_Play_PlayByProg(PMT_COMPACT_PROG *pstProg);
HI_S32 Sample_Play_PlayPrev(HI_VOID);
HI_S32 Sample_Play_PlayNext(HI_VOID);
HI_S32 Sample_Play_PlayAudioNext(HI_VOID);
HI_S32 Sample_Play_PlayAudioPrev(HI_VOID);
HI_S32 Sample_Play_GetPlayAudio(HI_U32 *pu32Idx, HI_U32 *pu32ADLevel);
HI_S32 Sample_Play_GetAudioInfo(SAMPLE_OSD_AUDIO_INFO_S* pstAudInfo);
HI_S32 Sample_Play_GetProgNum(HI_U32 *pu32ProgNum);
HI_S32 Sample_Play_SetPlayAudio(HI_U32 u32Idx);
HI_S32 Sample_Play_SetAudioBalance(HI_U32 u32ADLevel);
HI_S32 Sample_Play_GetAudioNum(HI_U32 *pu32AudNum);
HI_S32 Sample_Play_GetCurPlayProg(HI_U32 *pu32ProgNum);
HI_S32 Sample_Play_GetProgInfoByIdx(HI_U32 u32Idx, PMT_COMPACT_PROG *pstProg);
HI_S32 Sample_Play_RegisterCallBack(SAMPLE_AC4_PROCESS_FB pCallBack);
HI_S32 Sample_Play_UnRegisterCallBack(HI_VOID);


#ifdef __cplusplus
}
#endif

#endif

