#ifndef __VFMW_EXT_H__
#define __VFMW_EXT_H__

typedef SINT32(*FN_VFMW_Init)(VDEC_OPERATION_S *);
typedef SINT32(*FN_VFMW_Control)(HI_S32, VDEC_CID_E, HI_VOID *, UINT32);
typedef SINT32(*FN_VFMW_Exit)(UINT8);
typedef SINT32(*FN_VFMW_Suspend)(HI_VOID);
typedef SINT32(*FN_VFMW_Resume)(HI_VOID);
typedef SINT32(*FN_VFMW_GetImage)(SINT32 InstID, VOID *pFrame);
typedef SINT32(*FN_VFMW_ReleaseImage)(SINT32 InstID, VOID *pFrame);
typedef SINT32(*FN_VFMW_ReceiveFrame)(SINT32 InstID, VOID *pFrame);
typedef SINT32(*FN_VFMW_ReleaseFrame)(SINT32 InstID, VOID *pFrame);
typedef SINT32(*FN_VFMW_GLOBAL_ReleaseImage)(VOID *pImage);

typedef struct
{
    FN_VFMW_Init         pfnVfmwInit;
    FN_VFMW_Control      pfnVfmwControl;
    FN_VFMW_Exit         pfnVfmwExit;
    FN_VFMW_Suspend      pfnVfmwSuspend;
    FN_VFMW_Resume       pfnVfmwResume;
    FN_VFMW_GetImage     pfnVfmwGetImage;
    FN_VFMW_ReleaseImage pfnVfmwReleaseImage;
    FN_VFMW_ReceiveFrame pfnVfmwReceiveFrame;
    FN_VFMW_ReleaseFrame pfnVfmwReleaseFrame;
    FN_VFMW_GLOBAL_ReleaseImage pfnVfmwGlobalReleaseImage;
} VFMW_EXPORT_FUNC_S;

#endif
