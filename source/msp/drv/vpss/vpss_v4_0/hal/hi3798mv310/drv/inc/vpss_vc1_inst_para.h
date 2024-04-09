#ifndef __VPSS_VC1_INST_PARA_H__
#define __VPSS_VC1_INST_PARA_H__

typedef struct
{
    HI_U32 u32Offset       ;

} XDP_VC1_INST_PARA_S;

typedef enum tagXDP_VC1_ID_E
{
    XDP_VC1_ID_CF  = 0,
    XDP_VC1_ID_ME_CF  = 1,

    XDP_VC1_ID_BUTT

} XDP_VC1_ID_E;

HI_VOID vGetVc1InstPara (HI_U32 u32ID, XDP_VC1_INST_PARA_S *pstVc1InstPara);

#endif

