/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mpi_pvr.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2008/04/09
  Description   : hi_pvr_api.h header file
  History       :
  1.Date        : 2008/04/09
    Author      :
    Modification: Created file

******************************************************************************/

#ifndef __HI_MPI_PVR_H__
#define __HI_MPI_PVR_H__


#include "hi_type.h"

#include "hi_unf_pvr.h"
#include "hi_error_mpi.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define PVR_FIFO_DIO_LEN     512
#define PVR_FIFO_SECTOR_SIZE 512

#define PVR_FIFO_WRITE_BLOCK_SIZE(u32PacketSize) ((u32PacketSize) * PVR_FIFO_DIO_LEN * 2LLU) /* packetSize * 1024:the bigger block make more efficient*/

/**<Callback function type when asynchronously processing truncate. CNcomment:异步处理truncate时的回调函数类型CNend
\param[in] pszSrcFileName  Pointer to the original file name CNcomment:指针类型，指向原文件名CNend
\param[in] u32SrcFileNameLen    The length of original file name CNcomment:原文件名的长度CNend
\param[in] pszDstFileName    Pointer to the destination file name  CNcomment:指针类型，指向目标文件名CNend
\param[in] u32DstFileNameLen   The length of destination file name  CNcomment:目标文件名的长度CNend
\param[in] s32ErrCode The error code of truncate CNcomment:truncate过程中的错误码CNend
\param[in] pArgs    User private data CNcomment:用户私有数据CNend
\note: This callback function only needs to be processed asynchronously CNcomment:该回调函数仅在异步处理时需要CNend
*/
typedef HI_S32 (*TruncateCallBack)(HI_CHAR *pszSrcFileName, HI_U32 u32SrcFileNameLen, HI_CHAR *pszDstFileName, HI_U32 u32DstFileNameLen, HI_S32 s32ErrCode, HI_VOID *pArgs);

/*Attributes of truncate*/
typedef struct hiMPI_PVR_RECFILE_TRUNCATE_INFO_S
{
    HI_BOOL             bSync;                  /**Whether need to be synchronized,Currently only support sync processing*//**<CNcomment: 是否需要同步处理，目前仅支持同步处理*/
    HI_U32              u32PaddingTimeMs;       /**Redundant data that guarantees data integrity*//**<CNcomment: 冗余长度，保证数据完整性*/
    HI_BOOL             bTruncateHead;          /**Whether need to be deal with Head,Currently not supported*//**<CNcomment: 是否需要处理头部，目前不支持*/
    HI_U32              u32StartTimeMs;         /**Expected starting position,Currently not supported*//**<CNcomment: 期望的起始位置，目前不支持*/ /*实际处理后的起始位置 <= u32StartTimeMs-u32PaddingTimeMs*/
    HI_BOOL             bTruncateTail;          /**Whether need to be deal with Tail*//**<CNcomment: 是否需要处理尾部*/
    HI_U32              u32EndTimeMs;           /**Expected end position*//**<CNcomment: *期望的尾部位置*/ /*实际处理后的结束位置 >= u32EndTimeMs+u32PaddingTimeMs*/
    TruncateCallBack    pfnAsyncCB;             /**The callback funcation of Asynchronously*//**<CNcomment: 异步处理时处理完成的回调函数*/
    HI_VOID             *pArgs;                 /**The private data of callback*//**<CNcomment: 回调函数的私有数据，底层不作任何处理，直接透传*/
}HI_MPI_PVR_RECFILE_TRUNCATE_INFO_S;

/***********************************************************
                API Declaration
 ***********************************************************/

/***** APIs for PVR recode *****/

/* initialize and de-initialize of record module                            */
HI_S32 HI_PVR_RecInit(HI_VOID);
HI_S32 HI_PVR_RecDeInit(HI_VOID);

/* applay and release new record channel                                    */
HI_S32 HI_PVR_RecCreateChn(HI_U32 *pu32ChnID, const HI_UNF_PVR_REC_ATTR_S *pstRecAttr);
HI_S32 HI_PVR_RecDestroyChn(HI_U32 u32ChnID);

/* set and get attributes of record channel                                 */
HI_S32 HI_PVR_RecSetChn(HI_U32 u32ChnID, const HI_UNF_PVR_REC_ATTR_S *pstRecAttr);
HI_S32 HI_PVR_RecGetChn(HI_U32 u32ChnID, HI_UNF_PVR_REC_ATTR_S *pstRecAttr);

/* start and stop record channel                                            */
HI_S32 HI_PVR_RecStartChn(HI_U32 u32ChnID);
HI_S32 HI_PVR_RecStopChn(HI_U32 u32ChnID);
HI_S32 HI_PVR_RecPauseChn(HI_U32 u32ChnID);
HI_S32 HI_PVR_RecResumeChn(HI_U32 u32ChnID);


/* get record status                                                        */
HI_S32 HI_PVR_RecGetStatus(HI_U32 u32ChnID, HI_UNF_PVR_REC_STATUS_S *pstRecStatus);


/***** APIs for PVR play *****/

/* initialize and de-initialize of play module                              */
HI_S32 HI_PVR_PlayInit(HI_VOID);
HI_S32 HI_PVR_PlayDeInit(HI_VOID);

/* apply and release new play channel                                       */
HI_S32 HI_PVR_PlayCreateChn(HI_U32 *pChn, const HI_UNF_PVR_PLAY_ATTR_S *pAttr, HI_HANDLE hAvplay, HI_HANDLE hTsBuffer);
HI_S32 HI_PVR_PlayDestroyChn(HI_U32 u32ChnID);

/* start and stop time shift                                                */
HI_S32 HI_PVR_PlayStartTimeShift(HI_U32 *pu32PlayChnID, HI_U32 u32RecChnID, HI_HANDLE hAvplay, HI_HANDLE hTsBuffer);
HI_S32 HI_PVR_PlayStopTimeShift(HI_U32 u32PlayChnID, const HI_UNF_AVPLAY_STOP_OPT_S *pstStopOpt);

/* set and get attributes of play channel                                   */
HI_S32 HI_PVR_PlaySetChn(HI_U32 u32ChnID, const HI_UNF_PVR_PLAY_ATTR_S *pstPlayAttr);
HI_S32 HI_PVR_PlayGetChn(HI_U32 u32ChnID, HI_UNF_PVR_PLAY_ATTR_S *pstPlayAttr);

/* start and stop play channel                                              */
HI_S32 HI_PVR_PlayStartChn(HI_U32 u32ChnID);
HI_S32 HI_PVR_PlayStopChn(HI_U32 u32ChnID, const HI_UNF_AVPLAY_STOP_OPT_S *pstStopOpt);

/* pause and resume play channel                                            */
HI_S32 HI_PVR_PlayPauseChn(HI_U32 u32ChnID);
HI_S32 HI_PVR_PlayResumeChn(HI_U32 u32ChnID);

/* get play status                                                          */
HI_S32 HI_PVR_PlayGetStatus(HI_U32 u32ChnID, HI_UNF_PVR_PLAY_STATUS_S *pstStatus);

/* locate play position                                                     */
HI_S32 HI_PVR_PlaySeek(HI_U32 u32ChnID, const HI_UNF_PVR_PLAY_POSITION_S *pstPosition);

/* start trick mode of playing                                              */
HI_S32 HI_PVR_PlayTrickMode(HI_U32 u32ChnID, const HI_UNF_PVR_PLAY_MODE_S *pstTrickMode);

/* start step back frame by frame                                           */
HI_S32 HI_PVR_PlayStep(HI_U32 u32ChnID, HI_S32 s32Direction);

/* get file info */
HI_S32 HI_PVR_PlayGetFileAttr(HI_U32 u32ChnID, HI_UNF_PVR_FILE_ATTR_S *pAttr);

/* get file attr, no need to new play channel */
HI_S32 HI_PVR_GetFileAttrByFileName(const HI_CHAR *pFileName, HI_UNF_PVR_FILE_ATTR_S *pAttr);

HI_S32 HI_PVR_SetUsrDataInfoByFileName(const HI_CHAR *pFileName, HI_U8 *pInfo, HI_U32 u32UsrDataLen);

HI_S32 HI_PVR_GetUsrDataInfoByFileName(const HI_CHAR *pFileName, HI_U8 *pInfo, HI_U32 u32BufLen, HI_U32* pUsrDataLen);

HI_S32 HI_PVR_SetCAData(const HI_CHAR *pFileName, HI_U8 *pInfo, HI_U32 u32CADataLen);

HI_S32 HI_PVR_GetCAData(const HI_CHAR *pFileName, HI_U8 *pInfo, HI_U32 u32BufLen, HI_U32* u32CADataLen);

/***** APIs for PVR event callback *****/

/* register and un-register envent callback function    AI7D02612                    */
HI_S32 HI_PVR_RegisterEvent(HI_UNF_PVR_EVENT_E enEventType, eventCallBack callBack, HI_VOID *args);
HI_S32 HI_PVR_UnRegisterEvent(HI_UNF_PVR_EVENT_E enEventType);

#if 0 /*obsolete APIs*/
HI_S32 HI_PVR_RegisterEventByChn(HI_U32 u32ChnId, eventCallBack callBack, HI_VOID *args);
HI_S32 HI_PVR_UnRegisterEventByChn(HI_U32 u32ChnId);
#endif
HI_S32 HI_PVR_CreateIdxFile(HI_U8* pstTsFileName, HI_U8* pstIdxFileName, HI_UNF_PVR_GEN_IDX_ATTR_S* pAttr);

HI_VOID HI_PVR_ConfigDebugInfo(HI_LOG_LEVEL_E u32DebugLevel);

HI_VOID HI_PVR_RemoveFile(const HI_CHAR *pFileName);

/*callback type is HI_UNF_PVR_EXTRA_READ_CALLBACK  and called by HI_UNF_PVR_RegisterExtraCallback or HI_UNF_PVR_UnRegisterExtraCallback*/
HI_S32 HI_PVR_PlayRegisterReadCallBack(HI_U32 u32Chn, ExtraCallBack readCallBack);
HI_S32 HI_PVR_PlayUnRegisterReadCallBack(HI_U32 u32Chn);

/*callback type is HI_UNF_PVR_EXTRA_READ_CALLBACK and called by HI_UNF_PVR_RegisterExtendCallback or HI_UNF_PVR_UnRegisterExtendCallback*/
HI_S32 HI_PVR_PlayRegisterPlayCallBack(HI_U32 u32Chn, ExtendCallBack playCallBack, HI_VOID *pUserData);
HI_S32 HI_PVR_PlayUnRegisterPlayCallBack(HI_U32 u32Chn, ExtendCallBack pfnPlayCallback);

/*callback type is HI_UNF_PVR_EXTRA_WRITE_CALLBACK and called by HI_UNF_PVR_RegisterExtraCallback or HI_UNF_PVR_UnRegisterExtraCallback*/
HI_S32 HI_PVR_RecRegisterWriteCallBack(HI_U32 u32ChnID, ExtraCallBack writeCallBack);
HI_S32 HI_PVR_RecUnRegisterWriteCallBack(HI_U32 u32ChnID);

/*callback type is HI_UNF_PVR_EXTRA_WRITE_CALLBACK and called by HI_UNF_PVR_RegisterExtendCallback or HI_UNF_PVR_UnRegisterExtendCallback*/
HI_S32 HI_PVR_RecRegisterRecordCallBack(HI_U32 u32ChnID, ExtendCallBack RecCallBack, HI_VOID *pUserData);
HI_S32 HI_PVR_RecUnRegisterRecordCallBack(HI_U32 u32ChnID, ExtendCallBack pRecCallback);

/*callback type is HI_UNF_PVR_EXTRA_READ_CALLBACK and called by HI_UNF_PVR_RegisterPidChangeCallback or HI_UNF_PVR_UnRegisterPidChangeCallback*/
HI_S32 HI_PVR_PlayRegisterPidChangeCallBack(HI_U32 u32ChnID, PidChangeCallBack fCallback, HI_VOID *pArgs);
HI_S32 HI_PVR_PlayUnRegisterPidChangeCallBack(HI_U32 u32ChnID, PidChangeCallBack fCallback);

/*callback type is HI_UNF_PVR_EXTRA_WRITE_CALLBACK and called by HI_UNF_PVR_RegisterPidChangeCallback or HI_UNF_PVR_UnRegisterPidChangeCallback*/
HI_S32 HI_PVR_RecRegisterPidChangeCallBack(HI_U32 u32ChnID, PidChangeCallBack fCallback, HI_VOID *pArgs);
HI_S32 HI_PVR_RecUnRegisterPidChangeCallBack(HI_U32 u32ChnID, PidChangeCallBack fCallback);

HI_S32 HI_PVR_RecAddPid(HI_U32 u32ChnID, HI_U32 u32Pid);

HI_S32 HI_PVR_RecDelPid(HI_U32 u32ChnID, HI_U32 u32Pid);

HI_S32 HI_PVR_RecDelAllPid(HI_U32 u32ChnID);

HI_S32 HI_PVR_RecChangePid(HI_U32 u32ChnId, HI_UNF_PVR_PID_CHANGE_INFO_S *pstPidInfo);

HI_BOOL HI_PVR_AdvcaRecCheckAppend(HI_U32 u32ChnId, HI_U64 *p64LastRecGlobalOffset, HI_U32 *p32LastRecDisPlayTime);

HI_U64 HI_PVR_AdvcaRecCorrectFileOffset(HI_U32 u32ChnId, HI_U64 u64GlobalOffset);

HI_S32 HI_PVR_RecGetHandle(HI_HANDLE hPVR, HI_MOD_ID_E enModID, HI_HANDLE *pHandle, HI_U32 *pu32DemuxID);

HI_S32 HI_PVR_RecSetAttr(HI_U32 u32RecChnID, HI_UNF_PVR_REC_ATTR_ID_E enRecAttrID, HI_VOID *pPara);

HI_S32 HI_PVR_RecFileStartLinearization(HI_U32 *pu32ChnId, const HI_UNF_PVR_LINEARIZATION_ATTR_S *pstRepaireAttr);

HI_S32 HI_PVR_RecFileLinearizationGetStatus(HI_U32 u32ChnId, HI_UNF_PVR_LINEARIZATION_STATUS_S *pstLineariztionStatus);

HI_S32 HI_PVR_RecFileStopLinearization(HI_U32 u32ChnId);

HI_S32 HI_PVR_RecFileTruncate(const HI_CHAR *pszSrcFileName, HI_U32 u32SrcFileNameLen, const HI_CHAR *pszDstFileName, HI_U32 u32DstFileNameLen, const HI_MPI_PVR_RECFILE_TRUNCATE_INFO_S *pstTruncInfo);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  // __HI_MPI_PVR_H__

