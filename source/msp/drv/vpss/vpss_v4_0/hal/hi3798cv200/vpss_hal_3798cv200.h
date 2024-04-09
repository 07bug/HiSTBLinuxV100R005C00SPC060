#ifndef __VPSS_HAL_3798CV200_H__
#define __VPSS_HAL_3798CV200_H__
#include"hi_type.h"
#include "hi_drv_mmz.h"
#include"vpss_common.h"
#include "hi_drv_vpss.h"
#include "vpss_reg_3798cv200.h"
#include "vpss_sttinf.h"
#include "vpss_wbc.h"
#include "vpss_rwzb.h"
#include "drv_pq_ext.h"
#include "vpss_wbc_mcdei.h"
#include "vpss_stt_mcdei.h"

#define DEF_LOGIC_TIMEOUT  0xffffffff//0xe4e1c0
#define VPSS_LOGIC_CLOCK_SEL   1
#define  VPSS_ZME_HPREC        (1<<20)
#define  VPSS_ZME_HPREC_F        (1<<19)
#define  VPSS_ZME_HPREC_B        (1<<1)

#define  VPSS_ZME_VPREC        (1<<12)

#define HAL_VERSION_3798M 0x300

#define VPSS0_BASE_ADDR  0xf8cb0000
#define VPSS1_BASE_ADDR  0xffffffff
#define VPSS_REG_SIZE ((sizeof(VPSS_REG_S) + 15) & 0xFFFFFFF0)

#define VPSS_SPLIT_WTH 384
#define VPSS_RGMV_WTH 32
#define VPSS_SPLIT_MAX_NODE 1


#define VPSS_REG_SIZE_CALC(start, end)\
    (offsetof(VPSS_REG_S, end) + sizeof(HI_U32) -\
     offsetof(VPSS_REG_S, start))

#define VPSS_HAL_CHECK_IP_VAILD(enIP) \
    do{\
        if((enIP != VPSS_IP_0)&&(enIP != VPSS_IP_1))\
        {\
            VPSS_ERROR("VPSS IP%d, is Not Vaild\n", enIP);\
            return HI_FAILURE;\
        }\
    }while(0)

#define VPSS_HAL_CHECK_INST_VAILD(enInstance) \
    do{\
        if(enInstance >= VPSS_INSTANCE_MAX_NUMB)\
        {\
            VPSS_ERROR("VPSS Instance%d, is Not Vaild\n", enInstance);\
            return HI_FAILURE;\
        }\
    }while(0)

#define VPSS_HAL_CHECK_TASKNODE_ID_VAILD(enTaskNodeId) \
    do{\
        if(enTaskNodeId >= VPSS_HAL_TASK_NODE_BUTT)\
        {\
            VPSS_ERROR("VPSS NODE ID%d, is Not Vaild\n", enTaskNodeId);\
            return HI_FAILURE;\
        }\
    }while(0)
#define VPSS_HAL_CHECK_HALNODE_ID_VAILD(enHalNodeId) \
    do{\
        if(enHalNodeId >= VPSS_HAL_NODE_BUTT)\
        {\
            VPSS_ERROR("VPSS hal NODE ID%d, is Not Vaild\n", enHalNodeId);\
            return HI_FAILURE;\
        }\
    }while(0)

#define VPSS_HAL_CHECK_INIT(bInit) \
    do{\
        if (HI_FALSE == bInit){\
            VPSS_ERROR("VPSS HAL Is Not Init\n");\
            return HI_FAILURE;\
        }\
    }while(0)


#define VPSS_HAL_CHECK_NULL_PTR(ptr) \
    do{\
        if (HI_NULL == ptr){\
            VPSS_ERROR("pointer is NULL!\n");\
            return HI_FAILURE;\
        }\
    }while(0)

#define DEF_VPSS_HAL_PORT_NUM 1
#define DEF_VPSS_HAL_REF_LIST_NUM 4

typedef enum hiVPSS_IP_E
{
    VPSS_IP_0 = 0,
    VPSS_IP_1,
    VPSS_IP_BUTT
} VPSS_IP_E;

typedef enum hiVPSS_HAL_TASK_NODE_E
{
    VPSS_HAL_TASK_NODE_2D_FIELD = 0,
    VPSS_HAL_TASK_NODE_2D_FIELD_VIRTUAL,
    VPSS_HAL_TASK_NODE_2D,
    VPSS_HAL_TASK_NODE_SPLIT_L,
    VPSS_HAL_TASK_NODE_SPLIT_R,
    VPSS_HAL_TASK_NODE_2D_VIRTUAL,
    VPSS_HAL_TASK_NODE_3D_R,
    VPSS_HAL_TASK_NODE_3DDET,
    VPSS_HAL_TASK_NODE_P0_ZME_L2,
    VPSS_HAL_TASK_NODE_P1_ZME_L2,
    VPSS_HAL_TASK_NODE_P2_ZME_L2,
    VPSS_HAL_TASK_NODE_P0_RO_Y,
    VPSS_HAL_TASK_NODE_P0_RO_C,
    VPSS_HAL_TASK_NODE_P1_RO_Y,
    VPSS_HAL_TASK_NODE_P1_RO_C,
    VPSS_HAL_TASK_NODE_P2_RO_Y,
    VPSS_HAL_TASK_NODE_P2_RO_C,
    VPSS_HAL_TASK_NODE_2D_DETILE_STEP1,
    VPSS_HAL_TASK_NODE_2D_DETILE_STEP2,
    VPSS_HAL_TASK_NODE_2D_H265_STEP1_INTERLACE,
    VPSS_HAL_TASK_NODE_2D_H265_STEP2_DEI,

    VPSS_HAL_TASK_NODE_BUTT
} VPSS_HAL_TASK_NODE_E;


#define DEF_CBB_MAX_NODE_NUM VPSS_HAL_TASK_NODE_BUTT

typedef struct hiVPSS_HAL_CTX_S
{
    HI_BOOL  bInit;
    HI_BOOL  bClockEn;
    HI_U32   u32LogicVersion;

    HI_U32   u32BaseRegPhy;
    HI_U8   *pu8BaseRegVir;

#ifdef HI_VPSS_SMMU_SUPPORT
    SMMU_BUFFER_S     stDeTileMMUBuf;      //��tileʹ�õ���ʱbuffer
#else
    MMZ_BUFFER_S     stDeTileMMZBuf;       //��tileʹ�õ���ʱbuffer
#endif

    SMMU_BUFFER_S     stDeTileTEEBuf;

} VPSS_HAL_CTX_S;


typedef struct hiVPSS_HAL_ZME_PARAM_S
{
    HI_BOOL bYUV;
    HI_U32 u32YHRatio;
    HI_U32 u32CHRatio;
    HI_U32 u32YVRatio;
    HI_U32 u32CVRatio;
    ZME_FORMAT_E enInFmt;
    ZME_FORMAT_E enOutFmt;
} VPSS_HAL_ZME_PARAM_S;

typedef struct hiVPSS_HAL_FRAME_S
{
    HI_DRV_FRAME_TYPE_E      eFrmType;
    HI_U32 u32Width;
    HI_U32 u32Height;
    HI_DRV_PIX_FORMAT_E enFormat;
    HI_DRV_FIELD_MODE_E enFieldMode;
    HI_BOOL bProgressive;
    HI_DRV_VID_FRAME_ADDR_S stAddr;
    HI_DRV_VID_FRAME_ADDR_S stAddr_LB; //@sdk for dither
    HI_DRV_VID_FRAME_ADDR_S stAddr_META;
    HI_U32                   u32MetaSize;
    HI_BOOL                  bCompressd;
    HI_BOOL                  bUVInver;
    HI_DRV_PIXEL_BITWIDTH_E  enBitWidth;
    HI_U32 u32TunnelAddr;
    HI_BOOL  bTopFirst;
    HI_BOOL  bSecure;
} VPSS_HAL_FRAME_S;


typedef struct hiVPSS_HAL_PORT_INFO_S
{
    HI_BOOL    bEnable;
    HI_RECT_S  stInCropRect; /* PORT CROP��Ϣ */
    HI_RECT_S  stVideoRect; /* ��ʵ��ʾ���� */
    HI_RECT_S   stOutCropRect;
    HI_DRV_VPSS_ROTATION_E enRotation; /* ��ת��Ϣ */
    HI_BOOL bNeedFlip;
    HI_BOOL bNeedMirror;
    HI_BOOL bCmpLoss;
    HI_BOOL bConfig;

    VPSS_HAL_FRAME_S stOutInfo; /* PORT�����Ϣ */
#ifdef VPSS_SUPPORT_OUT_TUNNEL
    HI_BOOL     bOutLowDelay;
#endif
    VPSS_COLOR_E eLetterBoxColor;
} VPSS_HAL_PORT_INFO_S;

typedef struct hiVPSS_HAL_RefList
{
#ifdef HI_VPSS_SMMU_SUPPORT
    SMMU_BUFFER_S stRefListBuf_mmu;
#ifdef HI_TEE_SUPPORT
    SMMU_BUFFER_S stRefListBuf_tee;
#endif
#else
    MMZ_BUFFER_S  stRefListBuf_mmz;
#endif

    HI_DRV_VID_FRAME_ADDR_S stRefListAddr[DEF_VPSS_HAL_REF_LIST_NUM];
    HI_BOOL                 abRefNodeValid[DEF_VPSS_HAL_REF_LIST_NUM];
    HI_BOOL                 bRefListValid;
    HI_U32                  u32RefListHead;

} VPSS_HAL_RefList_S;


typedef struct hiVPSS_DIE_INFO_S
{
    VPSS_DIESTCFG_S stDieStCfg;
    HI_BOOL bBottom_first;

    //:TODO: ��ֵѡ����Ϣ

} VPSS_DIE_INFO_S;

typedef struct hiVPSS_NR_INFO_S
{
    HI_BOOL bNrEn;
    VPSS_NRMADCFG_S stNrMadCfg;
} VPSS_NR_INFO_S;



typedef enum hiVPSS_HAL_NODE_TYPE_E
{
    VPSS_HAL_NODE_2D_FRAME = 0,
    VPSS_HAL_NODE_2D_5Field,
    VPSS_HAL_NODE_2D_3Field,
    VPSS_HAL_NODE_2D_Field,
    VPSS_HAL_NODE_3D_FRAME_R, //�������ö�ȡƫ�ƣ��ڽ���ԴΪSBS/TAB����ʱ�����ǲ��֮���и��е����
    VPSS_HAL_NODE_PZME, //��Ӧ���У�������Դ������
    VPSS_HAL_NODE_UHD, // 4K*2K���������濴�Ƿ���UHD�Ǳ�����ⳡ��������������
    VPSS_HAL_NODE_UHD_HIGH_SPEED,// 4K*2K������DTV  4k@60����,һ������������
    VPSS_HAL_NODE_UHD_SPLIT_L,
    VPSS_HAL_NODE_UHD_SPLIT_R,
    VPSS_HAL_NODE_UHD_HALF,
    VPSS_HAL_NODE_3DDET,// 3D���ͨ·��ֻ��ҪY����
    VPSS_HAL_NODE_ZME_2L,// 2�����Žڵ�
    VPSS_HAL_NODE_ROTATION_Y,
    VPSS_HAL_NODE_ROTATION_C,
    VPSS_HAL_NODE_HDR_DETILE_NOALG,
    VPSS_HAL_NODE_2D_DETILE_STEP1, //de-tile node
    VPSS_HAL_NODE_2D_DETILE_STEP2, //first3field's 2D node
    VPSS_HAL_NODE_2D_H265_STEP1_INTERLACE,
    VPSS_HAL_NODE_2D_H265_STEP2_DEI,

    VPSS_HAL_NODE_BUTT
} VPSS_HAL_NODE_TYPE_E;

typedef struct hiVPSS_MCDEI_RFR_S
{
    HI_BOOL bMcdeiEn;   //MCDEI����
    HI_BOOL bMedsEn;    //ME�²�������
    VPSS_HAL_FRAME_S stRgmeWbc;  //rgme��д֡
    VPSS_HAL_FRAME_S stRgmeRef[3];  //rgme�ο�֡
    VPSS_HAL_FRAME_S stBlendWbc;  //blend��д֡
    VPSS_HAL_FRAME_S stBlendRef;  //blend�ο�֡
} VPSS_MCDEI_RFR_S;

typedef struct hiVPSS_MCDEI_ST_S
{
    VPSS_ST_RGME_CFG_S   stRgmeCfg;   //rgme�˶���Ϣ
    VPSS_ST_BLKMV_CFG_S  stBlkmvCfg;  //blkmv�˶���Ϣ
    VPSS_ST_PRJH_CFG_S   stPrjhCfg;  //prjh�˶���Ϣ
    VPSS_ST_PRJV_CFG_S   stPrjvCfg;  //prjv�˶���Ϣ
} VPSS_MCDEI_ST_S;

typedef struct hiVPSS_HAL_NODE_S
{
    HI_U32 u32NodeId;
    HI_U32 u32AppPhy;
    HI_U8 *pu8AppVir;
    MMZ_BUFFER_S stRegBuf;
} VPSS_HAL_NODE_S;

typedef struct hiVPSS_HAL_INFO_S
{
    VPSS_REG_S *pstPqCfg;
    VPSS_HAL_NODE_TYPE_E enNodeType;
    VPSS_HAL_FRAME_S stInInfo;             //����Դ��Ϣ
    VPSS_RWZB_INFO_S stRwzbInfo;

    /*VPSS V2_0*/
    VPSS_HAL_FRAME_S stInRefInfo[4];       //�ο�֡��Ϣ
    VPSS_HAL_FRAME_S stInWbcInfo;          //��д��Ϣ
    VPSS_HAL_FRAME_S stDeTileFrame;    //��tile����ʱbuffer
    HI_U32           u32DetileFieldIdx;    //��tile ��ǰ3�����
    HI_U32 u32stt_w_phy_addr;
    HI_U8 *pu8stt_w_vir_addr;

    VPSS_NR_INFO_S stNrInfo;

    /*VPSS V1_0*/
    HI_DRV_VID_FRAME_ADDR_S stFieldAddr[6];
    VPSS_DIE_INFO_S stDieInfo;

    HI_U32 u32ScdValue;
    VPSS_MCDEI_RFR_S stMcdeiRfrInfo;    //mcdei��д��Ϣ
    VPSS_MCDEI_ST_S    stMcdeiStInfo;     //mcdei�˶���Ϣ
    VPSS_HAL_PORT_INFO_S astPortInfo[DEF_HI_DRV_VPSS_PORT_MAX_NUMBER];

    VPSS_HAL_RefList_S *pstH265RefList;
    VPSS_HAL_NODE_S         stNodeList[VPSS_HAL_NODE_BUTT];
    HI_U32                  u32NodeCount;
#ifdef VPSS_SUPPORT_OUT_TUNNEL
#ifdef HI_VPSS_SUPPORT_OUTTUNNEL_SMMU
    SMMU_BUFFER_S   stLowDelayBuf_MMU;
#else
    MMZ_BUFFER_S    stLowDelayBuf_MMZ;
#endif
#endif
    HI_S32              s32InstanceID;
} VPSS_HAL_INFO_S;


extern VPSS_HAL_CTX_S  stHalCtx[VPSS_IP_BUTT][VPSS_INSTANCE_MAX_NUMB];

HI_S32 VPSS_HAL_Init(VPSS_IP_E enIP);
HI_S32 VPSS_HAL_DelInit(VPSS_IP_E enIP);

HI_S32 VPSS_HAL_SetClockEn(VPSS_IP_E enIP, HI_BOOL bClockEn);
HI_S32 VPSS_HAL_GetClockEn(VPSS_IP_E enIP, HI_BOOL *pbClockEn);
HI_S32 VPSS_HAL_CfgAXI(VPSS_IP_E enIP);
HI_S32 VPSS_HAL_GetIntState(VPSS_IP_E enIP, HI_U32 *pu32IntState);
HI_S32 VPSS_HAL_ClearIntState(VPSS_IP_E enIP, HI_U32 u32IntState);

HI_S32 VPSS_HAL_SetNodeInfo(VPSS_IP_E enIP,
                            VPSS_HAL_INFO_S *pstHalInfo,  VPSS_HAL_TASK_NODE_E
                            enTaskNodeId);

HI_S32 VPSS_HAL_GetSCDInfo(HI_U32 *pu32AppVir, HI_S32 s32SCDInfo[32]);

HI_VOID VPSS_HAL_GetDetPixel(HI_U32 *pu32AppVir, HI_U32 BlkNum, HI_U8 *pstData);

HI_S32 VPSS_HAL_GetBaseRegAddr(VPSS_IP_E enIP,
                               HI_U32 *pu32PhyAddr,
                               HI_U8 **ppu8VirAddr);
HI_S32 VPSS_HAL_SetAlgParaAddr(HI_U32 *pu32AppVir, HI_U32 u32AppPhy);
HI_S32 VPSS_HAL_DumpReg(VPSS_IP_E enIP, HI_U32 *pu32AppVir);
HI_S32 VPSS_HAL_H265RefListInit(VPSS_HAL_RefList_S *pstRefList, HI_S32 s32Width, HI_S32 s32Height, HI_DRV_PIX_FORMAT_E
                                enFormat, HI_BOOL bSecure);

HI_S32 VPSS_HAL_H265RefListDeInit(VPSS_HAL_RefList_S *pstRefList);
HI_S32 VPSS_HAL_SetNode_H265_Step2_Dei(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo,
                                       HI_U32 *pu32AppVir, HI_U32 u32AppPhy);
HI_S32 VPSS_HAL_SetNode_H265_Step2_Dei(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo,
                                       HI_U32 *pu32AppVir, HI_U32 u32AppPhy);
HI_S32 VPSS_HAL_GetSystemTickCounter(VPSS_IP_E enIP, HI_U32 *ptickcnt, HI_U32 *pSystemClock);

#ifdef VPSS_SUPPORT_OUT_TUNNEL
HI_S32 VPSS_HAL_TunnelOut_GetBufAddr(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 u32PortID);
#endif
HI_VOID VPSS_Hal_PrintHalInfo(struct seq_file *p, S_VPSS_REGS_TYPE *pstNodeReg);

HI_S32 VPSS_HAL_GetNodeAddr(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstVpssHalInfo, HI_U32 u32NodeId,
                            HI_U8 **pstRegAddr, HI_CHAR **ppNodeName);

HI_BOOL VPSS_HAL_SupportMcSplit(VPSS_MCDI_SPLIT_MODE_E enSplitMode, HI_U32 u32Width, HI_BOOL
                                bProgressive);
HI_VOID VPSS_HAL_CalcSplitWth(HI_U32 u32Width, HI_U32 *pu32FirstWth, HI_U32 *pu32MidWth, HI_U32 *pu32LastWth, HI_U32
                              *pu32SplitCnt);


#endif

