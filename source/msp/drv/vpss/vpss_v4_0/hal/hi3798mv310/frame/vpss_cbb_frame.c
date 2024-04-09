#include "vpss_cbb_frame.h"
#include "vpss_cbb_func.h"
#include "vpss_cbb_component.h"
#include "vpss_cbb_debug.h"
#include "vpss_cbb_reg.h"
#include "vpss_cbb_intf.h"
#include "vpss_cbb_assert.h"
#include "vpss_reg_struct.h"

VPSS_MAC_RCHN_E CBB_FrmRChnEnumMap(CBB_FRAME_CHANNEL_E enFrameChan)
{
    VPSS_MAC_RCHN_E enMacRchn = VPSS_MAC_RCHN_CF;
    switch (enFrameChan)
    {
        case CBB_FRAME_READ_REF:
            enMacRchn = VPSS_MAC_RCHN_P3;
            break;
        case CBB_FRAME_READ_REE:
            enMacRchn = VPSS_MAC_RCHN_P3I;
            break;
        case CBB_FRAME_READ_CUR:
            enMacRchn = VPSS_MAC_RCHN_P2;
            break;
        case CBB_FRAME_READ_NX1:
            enMacRchn = VPSS_MAC_RCHN_P1;
            break;
        case CBB_FRAME_READ_NX2:
            enMacRchn = VPSS_MAC_RCHN_CF;
            break;
        default :
            VPSS_ASSERT(enFrameChan <= CBB_FRAME_READ_NX2);
            break;
    }
    return  enMacRchn;
}
VPSS_MAC_WCHN_E CBB_FrmWChnEnumMap(CBB_FRAME_CHANNEL_E enFrameChan)
{
    VPSS_MAC_WCHN_E enMacWchn = VPSS_MAC_WCHN_OUT0;
    switch (enFrameChan)
    {
        case CBB_FRAME_WRITE_RFR:
            enMacWchn = VPSS_MAC_WCHN_NR_RFR;
            break;
        case CBB_FRAME_WRITE_CUE:
            enMacWchn = VPSS_MAC_WCHN_DI_RFR;
            break;
        case CBB_FRAME_WRITE_VHD0:
            enMacWchn = VPSS_MAC_WCHN_OUT0;
            break;
        default :
            VPSS_ASSERT((enFrameChan > CBB_FRAME_READ_NX2) && (enFrameChan <= CBB_FRAME_WRITE_VHD0));
            break;
    }
    return  enMacWchn;
}

HI_U32 CBB_FrameFmtTrans( HI_DRV_PIX_FORMAT_E   enPixelFmt )
{
    HI_U32 u32Fmt = 0xFFFFFFFF;
    HI_S32 s32Index;

    HI_S32 au32FmtTransTbl[][2] =
    {
        {HI_DRV_PIX_FMT_NV21,           0x0},
        {HI_DRV_PIX_FMT_NV12,           0x0},
        {HI_DRV_PIX_FMT_NV12_CMP,       0x0},
        {HI_DRV_PIX_FMT_NV21_CMP,       0x0},
        {HI_DRV_PIX_FMT_NV12_TILE,      0x0},
        {HI_DRV_PIX_FMT_NV21_TILE,      0x0},
        {HI_DRV_PIX_FMT_NV21_TILE_CMP,  0x0},
        {HI_DRV_PIX_FMT_NV12_TILE_CMP,  0x0},

        {HI_DRV_PIX_FMT_NV61_2X1_CMP,   0x1},
        {HI_DRV_PIX_FMT_NV16_2X1_CMP,   0x1},
        {HI_DRV_PIX_FMT_NV61_CMP,       0x1},
        {HI_DRV_PIX_FMT_NV16_CMP,       0x1},
        {HI_DRV_PIX_FMT_NV16_2X1,       0x1},
        {HI_DRV_PIX_FMT_NV61_2X1,       0x1},
        {HI_DRV_PIX_FMT_NV16,           0x1},
        {HI_DRV_PIX_FMT_NV61,           0x1},

        {HI_DRV_PIX_FMT_YUV400,         0x4},
        {HI_DRV_PIX_FMT_YUV_444,        0x5},
        {HI_DRV_PIX_FMT_YUV422_2X1,     0x6},
        {HI_DRV_PIX_FMT_YUV420p,        0x8},
        {HI_DRV_PIX_FMT_YUV411,         0x9},
        {HI_DRV_PIX_FMT_YUV410p,        0xa},
        {HI_DRV_PIX_FMT_YUYV,           0xb},
        {HI_DRV_PIX_FMT_YVYU,           0xc},
        {HI_DRV_PIX_FMT_UYVY,           0xd}
    };


    for (s32Index = 0; s32Index < VPSS_GET_ARRAY_CNT(au32FmtTransTbl);
         s32Index++)
    {
        if (enPixelFmt == au32FmtTransTbl[s32Index][0])
        {
            u32Fmt = au32FmtTransTbl[s32Index][1];
            break;
        }
    }

    if (0xFFFFFFFF == u32Fmt)
    {
        CBB_ERRMSG("Invalid pixel format! enPixelFmt:%d u32Fmt:%d\n", enPixelFmt, u32Fmt);
        dump_stack();
    }

    return u32Fmt;
}


HI_VOID CBB_RFrmPixelFmtMap(CBB_FRAME_S *pstFrmCfg, VPSS_MAC_RCHN_CFG_S *pstRchnCfg, CBB_FRAME_CHANNEL_E enFrameChan)
{
    switch (pstFrmCfg->enPixelFmt)
    {
        case HI_DRV_PIX_FMT_NV12_TILE: /* 12 tile  */
        case HI_DRV_PIX_FMT_NV21_TILE: /* 21 tile  */
        case HI_DRV_PIX_FMT_YUV400_TILE: /* 21 tile  */
        case HI_DRV_PIX_FMT_NV12_TILE_CMP:
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:

            pstRchnCfg->enDataType = XDP_DATA_TYPE_SP_TILE;
            break;
        default:
            pstRchnCfg->enDataType = XDP_DATA_TYPE_SP_LINEAR;
            break;
    }

    pstRchnCfg->enDataFmt = CBB_FrameFmtTrans(pstFrmCfg->enPixelFmt);


    if (enFrameChan != CBB_FRAME_READ_NX2)
    {
        pstRchnCfg->enDataType = XDP_DATA_TYPE_SP_LINEAR;
        VPSS_ASSERT((XDP_PROC_FMT_SP_420 == pstRchnCfg->enDataFmt) || (XDP_PROC_FMT_SP_422 == pstRchnCfg->enDataFmt));//wrong data fmt
    }
}
HI_VOID CBB_WFrmPixelFmtMap(CBB_FRAME_S *pstFrmCfg, VPSS_MAC_WCHN_CFG_S *pstWchnCfg, CBB_FRAME_CHANNEL_E enFrameChan)
{
    switch (pstFrmCfg->enPixelFmt)
    {
        case HI_DRV_PIX_FMT_NV12_TILE: /* 12 tile  */
        case HI_DRV_PIX_FMT_NV21_TILE: /* 21 tile  */
        case HI_DRV_PIX_FMT_YUV400_TILE: /* 21 tile  */
        case HI_DRV_PIX_FMT_NV12_TILE_CMP:
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:

            pstWchnCfg->enDataType = XDP_DATA_TYPE_SP_TILE;
            break;
        default:
            pstWchnCfg->enDataType = XDP_DATA_TYPE_SP_LINEAR;
            break;
    }

    pstWchnCfg->enDataFmt = CBB_FrameFmtTrans(pstFrmCfg->enPixelFmt);



    VPSS_ASSERT((XDP_PROC_FMT_SP_420 == pstWchnCfg->enDataFmt) || (XDP_PROC_FMT_SP_422 == pstWchnCfg->enDataFmt));
    VPSS_ASSERT(pstWchnCfg->enDataType == XDP_DATA_TYPE_SP_LINEAR);
}
HI_VOID CBB_RFrmAddrMap(CBB_FRAME_S *pstFrmCfg, VPSS_MAC_RCHN_CFG_S *pstRchnCfg)
{
    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr = (HI_U64) pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y;
    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64UAddr = (HI_U64) pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C;
    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32YStr  = pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y;
    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32CStr  = pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C;
    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64YAddr = (HI_U64) pstFrmCfg->stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_Y;
    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64UAddr = (HI_U64) pstFrmCfg->stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_C;
    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u32YStr  = pstFrmCfg->stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_Y;
    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u32CStr  = pstFrmCfg->stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_C;
    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64YAddr = (HI_U64) pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_YHead;
    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64UAddr = (HI_U64) pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_CHead;
    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u32YStr  = pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Head_Stride;
    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u32CStr  = pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Head_Stride;
}
HI_VOID CBB_WFrmAddrMap(CBB_FRAME_S *pstFrmCfg, VPSS_MAC_WCHN_CFG_S *pstWchnCfg)
{
    pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr = (HI_U64) pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y;
    pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64UAddr = (HI_U64) pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C;
    pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32YStr  = pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y;
    pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32CStr  = pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C;
}
HI_VOID CBB_RFrmStMap(CBB_FRAME_S *pstFrmCfg, VPSS_MAC_RCHN_CFG_S *pstRchnCfg, CBB_FRAME_CHANNEL_E enFrameChan)
{
    pstRchnCfg->bEn = pstFrmCfg->bEn;
    if (CBB_FRAME_READ_NX2 == enFrameChan)
    {
        pstRchnCfg->stInRect.u32X = (HI_U32)pstFrmCfg->stOffset.s32X;
        pstRchnCfg->stInRect.u32Y = (HI_U32)pstFrmCfg->stOffset.s32Y;
        pstRchnCfg->stInRect.u32Wth = pstFrmCfg->u32Width;
        pstRchnCfg->stInRect.u32Hgt = pstFrmCfg->u32Height;
        pstRchnCfg->stDcmpCfg.enCmpType = (pstFrmCfg->bCompress == HI_TRUE) ? XDP_CMP_TYPE_SEG : XDP_CMP_TYPE_OFF;
        if (HI_TRUE == pstFrmCfg->bSpecialTile)
        {
            pstRchnCfg->enRdMode = (HI_TRUE == pstFrmCfg->bTop) ? XDP_RMODE_PRO_TOP : XDP_RMODE_PRO_BOTTOM;
        }
        else
        {
            pstRchnCfg->enRdMode = ((HI_TRUE == pstFrmCfg->bProgressive) ? XDP_RMODE_PROGRESSIVE : \
                                    (HI_TRUE == pstFrmCfg->bTop) ? XDP_RMODE_TOP : XDP_RMODE_BOTTOM);
        }
    }
    else
    {
        pstRchnCfg->stInRect.u32Wth = pstFrmCfg->u32Width;
        pstRchnCfg->stInRect.u32Hgt = pstFrmCfg->u32Height;
        pstRchnCfg->stDcmpCfg.enCmpType = XDP_CMP_TYPE_OFF;
    }

    pstRchnCfg->enDataWidth = (XDP_DATA_WTH) pstFrmCfg->enBitWidth;
    pstRchnCfg->bMmuBypass  = !pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y;
    CBB_RFrmPixelFmtMap(pstFrmCfg, pstRchnCfg, enFrameChan);
    CBB_RFrmAddrMap(pstFrmCfg, pstRchnCfg);
}
HI_VOID CBB_MAC_SetRchnCfg(S_VPSS_REGS_TYPE *pstReg, VPSS_MAC_RCHN_E enLayer, VPSS_MAC_RCHN_CFG_S *pstRchnCfg)
{
    HI_U32  u32RealOffset = 0;
    HI_BOOL bIsSoloData   = HI_FALSE;;
    if (pstRchnCfg->bSetFlag == HI_TRUE )
    {
        return;
    }
    else
    {
        pstRchnCfg->bSetFlag = HI_TRUE;
    }
    bIsSoloData  = VpssGetRchnClassType(enLayer);
    if (HI_FALSE == bIsSoloData)
    {
        u32RealOffset = (gu32VpssRchnAddr[enLayer] - VPSS_RCHN_IMG_START_OFFSET);
    }
    else
    {
        u32RealOffset = (gu32VpssRchnAddr[enLayer] - VPSS_RCHN_SOLO_START_OFFSET);
    }
    if (HI_FALSE == bIsSoloData)
    {
        u32RealOffset = (gu32VpssRchnAddr[enLayer] - VPSS_RCHN_IMG_START_OFFSET);
        VPSS_RCHN_SetEn         ( pstReg, u32RealOffset, pstRchnCfg->bEn                 );
        VPSS_RCHN_SetType       ( pstReg, u32RealOffset, pstRchnCfg->enDataType          );
        VPSS_RCHN_SetFormat     ( pstReg, u32RealOffset, pstRchnCfg->enDataFmt           );
        VPSS_RCHN_SetOrder      ( pstReg, u32RealOffset, pstRchnCfg->enPkgFmt            );

        VPSS_RCHN_SetLmRmode    ( pstReg, u32RealOffset, pstRchnCfg->enRdMode            );
        VPSS_RCHN_SetBitw       ( pstReg, u32RealOffset, pstRchnCfg->enDataWidth         );
        VPSS_RCHN_SetWidth      ( pstReg, u32RealOffset, pstRchnCfg->stInRect.u32Wth - 1 );
        VPSS_RCHN_SetHeight     ( pstReg, u32RealOffset, pstRchnCfg->stInRect.u32Hgt - 1 );
        VPSS_RCHN_SetHorOffset  ( pstReg, u32RealOffset, pstRchnCfg->stInRect.u32X       );
        VPSS_RCHN_SetVerOffset  ( pstReg, u32RealOffset, pstRchnCfg->stInRect.u32Y       );
        VPSS_RCHN_SetDBypass    ( pstReg, u32RealOffset, pstRchnCfg->bMmuBypass         );
        VPSS_RCHN_SetHBypass    ( pstReg, u32RealOffset, pstRchnCfg->bMmuBypass         );
        VPSS_RCHN_Set2bBypass   ( pstReg, u32RealOffset, pstRchnCfg->bMmuBypass         );
        VPSS_RCHN_SetYAddrL       ( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr     ) & 0xffffffff) );
        VPSS_RCHN_SetCAddrL       ( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64UAddr     ) & 0xffffffff) );
        VPSS_RCHN_SetYStride      ( pstReg, u32RealOffset,   pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32YStr );
        VPSS_RCHN_SetCStride      ( pstReg, u32RealOffset,   pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32CStr );
        VPSS_RCHN_SetYTopHeadAddrL( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64YAddr     ) & 0xffffffff) );
        VPSS_RCHN_SetCTopHeadAddrL( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64UAddr     ) & 0xffffffff) );
        VPSS_RCHN_SetYHeadStride  ( pstReg, u32RealOffset,   pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u32YStr );
        VPSS_RCHN_SetCHeadStride  ( pstReg, u32RealOffset,   pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u32CStr );
        VPSS_RCHN_SetY2bAddrL     ( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64YAddr     ) & 0xffffffff) );
        VPSS_RCHN_SetC2bAddrL     ( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64UAddr     ) & 0xffffffff) );
        VPSS_RCHN_SetY2bStride    ( pstReg, u32RealOffset,   pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u32YStr );
        VPSS_RCHN_SetC2bStride    ( pstReg, u32RealOffset,   pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u32CStr );
        VPSS_RCHN_SetDcmpMode         ( pstReg, u32RealOffset, pstRchnCfg->stDcmpCfg.enCmpType );
        if (pstRchnCfg->bEn)
        {
            if (pstRchnCfg->enDataType == XDP_DATA_TYPE_PACKAGE)
            {
                XDP_ASSERT(pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_422);
            }
            else if (pstRchnCfg->enDataType == XDP_DATA_TYPE_PLANAR)
            {
                XDP_ASSERT((pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_420) || (pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_422) || (pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_400));
            }
            XDP_ASSERT( pstRchnCfg->stInRect.u32Wth >= 31 );
            XDP_ASSERT( pstRchnCfg->stInRect.u32Hgt >= 16 );
            if (pstRchnCfg->bMirrorEn)
            {
                XDP_ASSERT(pstRchnCfg->stInRect.u32X == 0);
                XDP_ASSERT(pstRchnCfg->stInRect.u32Y == 0);
            }
            if (pstRchnCfg->enDataWidth == XDP_DATA_WTH_8)
            {
                if (pstRchnCfg->enDataType == XDP_DATA_TYPE_PACKAGE)
                {
                }
                else if (pstRchnCfg->enDataType == XDP_DATA_TYPE_SP_LINEAR)
                {
                    if ((pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_420) || (pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_422))
                    {
                    }
                }
            }
            else if (pstRchnCfg->enDataWidth == XDP_DATA_WTH_10)
            {
                if (pstRchnCfg->enDataType == XDP_DATA_TYPE_SP_LINEAR)
                {
                    if ((pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_420) || (pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_422))
                    {
                    }
                }
            }
            if (pstRchnCfg->enDataWidth == XDP_DATA_WTH_8)
            {
                XDP_ASSERT(pstRchnCfg->stMuteCfg.u32MuteY <= 0xff);
                XDP_ASSERT(pstRchnCfg->stMuteCfg.u32MuteC <= 0xff);
            }
            else
            {
                XDP_ASSERT(pstRchnCfg->stMuteCfg.u32MuteY <= 0x3ff);
                XDP_ASSERT(pstRchnCfg->stMuteCfg.u32MuteC <= 0x3ff);
            }
            if ((VPSS_MAC_RCHN_CF != enLayer) && (VPSS_MAC_RCHN_P2 != enLayer) && (VPSS_MAC_RCHN_P1 != enLayer) && (VPSS_MAC_RCHN_P3 != enLayer))
            {
                XDP_ASSERT(pstRchnCfg->enDataWidth == XDP_DATA_WTH_8);
            }
            XDP_ASSERT(pstRchnCfg->enDataType != XDP_DATA_TYPE_PLANAR);
            if (VPSS_MAC_RCHN_CF != enLayer)
            {
                XDP_ASSERT(pstRchnCfg->bUvInvEn   == HI_FALSE);
                XDP_ASSERT(pstRchnCfg->enDataType == XDP_DATA_TYPE_SP_LINEAR);
                XDP_ASSERT(pstRchnCfg->enDataFmt  != XDP_PROC_FMT_SP_400);
                XDP_ASSERT(pstRchnCfg->enRdMode != XDP_RMODE_TOP   );
                XDP_ASSERT(pstRchnCfg->enRdMode != XDP_RMODE_BOTTOM);
                XDP_ASSERT(pstRchnCfg->stInRect.u32X == 0);
                XDP_ASSERT(pstRchnCfg->stInRect.u32Y == 0);
            }
            if (pstRchnCfg->stDcmpCfg.enCmpType == XDP_CMP_TYPE_SEG)
            {
                XDP_ASSERT((pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_400) || (pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_420));
                XDP_ASSERT(pstRchnCfg->enDataType == XDP_DATA_TYPE_SP_TILE);
                XDP_ASSERT(pstRchnCfg->enRdMode != XDP_RMODE_TOP   );
                XDP_ASSERT(pstRchnCfg->enRdMode != XDP_RMODE_BOTTOM);
            }
            else
            {
                XDP_ASSERT(pstRchnCfg->stDcmpCfg.enCmpType == XDP_CMP_TYPE_OFF);
            }
            if (pstRchnCfg->enDataType == XDP_DATA_TYPE_SP_TILE)
            {
                if (pstRchnCfg->stDcmpCfg.enCmpType == XDP_CMP_TYPE_OFF)
                {
                }
                XDP_ASSERT((pstRchnCfg->stInRect.u32Wth + pstRchnCfg->stInRect.u32X) <= 4096);
            }
            if ((pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_400) || (pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_420))
            {
                if ((VPSS_MAC_RCHN_CF == enLayer) && (pstRchnCfg->enRdMode != XDP_RMODE_PROGRESSIVE))
                {
                    XDP_ASSERT((pstRchnCfg->stInRect.u32Y  % 4) == 0);
                    XDP_ASSERT((pstRchnCfg->stInRect.u32Hgt % 4) == 0);
                }
            }
        }
    }
    else
    {
        u32RealOffset = (gu32VpssRchnAddr[enLayer] - VPSS_RCHN_SOLO_START_OFFSET);
        VPSS_RCHN_SOLO_SetEn           ( pstReg, u32RealOffset, pstRchnCfg->bEn                 );
        VPSS_RCHN_SOLO_SetEn1          ( pstReg, u32RealOffset, pstRchnCfg->bEn1                );
        VPSS_RCHN_SOLO_SetWidth        ( pstReg, u32RealOffset, pstRchnCfg->stInRect.u32Wth - 1 );
        VPSS_RCHN_SOLO_SetHeight       ( pstReg, u32RealOffset, pstRchnCfg->stInRect.u32Hgt - 1 );
        VPSS_RCHN_SOLO_SetDBypass      ( pstReg, u32RealOffset, pstRchnCfg->bMmuBypass          );
        VPSS_RCHN_SOLO_SetAddrL        ( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr     ) & 0xffffffff) );
        VPSS_RCHN_SOLO_SetStride       ( pstReg, u32RealOffset,   pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32YStr                      );
        if (pstRchnCfg->bEn)
        {
            XDP_ASSERT(pstRchnCfg->stDcmpCfg.enCmpType == XDP_CMP_TYPE_OFF);
        }
    }
    if (pstRchnCfg->bEn)
    {
        XDP_ASSERT(pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32YStr % 16 == 0);
        XDP_ASSERT(pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32CStr % 16 == 0);
        XDP_ASSERT(pstRchnCfg->stInRect.u32Wth <= gu32VpssRchnMaxWth[enLayer]);
    }
    if ((VPSS_MAC_RCHN_P1RGMV != enLayer) && (VPSS_MAC_RCHN_P2RGMV != enLayer))
    {
        XDP_ASSERT(pstRchnCfg->bEn1 == HI_FALSE);
    }
    return;
}
HI_VOID CBB_MAC_SetWchnCfg(S_VPSS_REGS_TYPE *pstReg, VPSS_MAC_WCHN_E enLayer, VPSS_MAC_WCHN_CFG_S *pstWchnCfg)
{
    HI_U32  u32RealOffset = 0;
    HI_BOOL bIsSoloData   = HI_FALSE;
    bIsSoloData  = VpssGetWchnClassType(enLayer);
    if (HI_FALSE == bIsSoloData)
    {
        u32RealOffset = (gu32VpssWchnAddr[enLayer] - VPSS_WCHN_IMG_START_OFFSET);
    }
    else
    {
        u32RealOffset = (gu32VpssWchnAddr[enLayer] - VPSS_WCHN_SOLO_START_OFFSET);
    }

    if (HI_FALSE == bIsSoloData)
    {
#if EDA_TEST
        if (enLayer == VPSS_MAC_WCHN_OUT0)
        {
            if (pstWchnCfg->enDataWidth == XDP_DATA_WTH_10)
            {
                pstWchnCfg->stDitherCfg.bEn = HI_FALSE;
            }
        }
        if (enLayer == VPSS_MAC_WCHN_NR_RFR)
        {
            if (pstWchnCfg->enDataWidth == XDP_DATA_WTH_10)
            {
                pstWchnCfg->stDitherCfg.bEn = HI_FALSE;
            }
        }
#endif
        u32RealOffset = (gu32VpssWchnAddr[enLayer] - VPSS_WCHN_IMG_START_OFFSET);
        //---------------------------
        // Cfg
        //---------------------------
        VPSS_WCHN_SetEn            ( pstReg, u32RealOffset, pstWchnCfg->bEn                 );
        VPSS_WCHN_SetBitw          ( pstReg, u32RealOffset, pstWchnCfg->enDataWidth         );
        VPSS_WCHN_SetType          ( pstReg, u32RealOffset, pstWchnCfg->enDataType          );
        //VPSS_WCHN_SetFlip          ( pstReg, u32RealOffset, pstWchnCfg->bFlipEn             );
        //VPSS_WCHN_SetMirror        ( pstReg, u32RealOffset, pstWchnCfg->bMirrorEn           );
        //VPSS_WCHN_SetUvInvert      ( pstReg, u32RealOffset, pstWchnCfg->bUvInvEn            );
        //VPSS_WCHN_SetDitherEn      ( pstReg, u32RealOffset, pstWchnCfg->stDitherCfg.bEn     );
        //VPSS_WCHN_SetDitherMode    ( pstReg, u32RealOffset, pstWchnCfg->stDitherCfg.enMode  );
        VPSS_WCHN_SetHorOffset     ( pstReg, u32RealOffset, pstWchnCfg->stOutRect.u32X      );
        VPSS_WCHN_SetVerOffset     ( pstReg, u32RealOffset, pstWchnCfg->stOutRect.u32Y      );
        //VPSS_WCHN_SetTunlEn        ( pstReg, u32RealOffset, pstWchnCfg->bTunlEn            );
        VPSS_WCHN_SetDBypass       ( pstReg, u32RealOffset, pstWchnCfg->bMmuBypass           );
        VPSS_WCHN_SetHBypass       ( pstReg, u32RealOffset, pstWchnCfg->bMmuBypass           );
        //---------------------------
        // Addr
        //---------------------------
        //VPSS_WCHN_SetYAddrH        ( pstReg, u32RealOffset, ((pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr>>32 ) & 0xffffffff ));
        //VPSS_WCHN_SetCAddrH        ( pstReg, u32RealOffset, ((pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64UAddr>>32 ) & 0xffffffff ));
        VPSS_WCHN_SetYAddrL        ( pstReg, u32RealOffset, ((pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr     ) & 0xffffffff ));
        VPSS_WCHN_SetCAddrL        ( pstReg, u32RealOffset, ((pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64UAddr     ) & 0xffffffff ));
        VPSS_WCHN_SetYStride       ( pstReg, u32RealOffset,   pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32YStr                      );
        VPSS_WCHN_SetCStride       ( pstReg, u32RealOffset,   pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32CStr                      );
        //---------------------------
        // Cmp
        //---------------------------
        VPSS_WCHN_SetCmpMode       ( pstReg, u32RealOffset, pstWchnCfg->enCmpType );

        //---------------------------
        // Env Reg Setting
        //---------------------------
        VPSS_WCHN_ENV_SetFormat    ( pstReg, u32RealOffset, pstWchnCfg->enDataFmt           );
        VPSS_WCHN_SetLmRmode       ( pstReg, u32RealOffset, pstWchnCfg->enRdMode            );
        VPSS_WCHN_ENV_SetWidth     ( pstReg, u32RealOffset, pstWchnCfg->stOutRect.u32Wth - 1  );
        VPSS_WCHN_ENV_SetHeight    ( pstReg, u32RealOffset, pstWchnCfg->stOutRect.u32Hgt - 1  );
        VPSS_WCHN_ENV_SetFinfoH    ( pstReg, u32RealOffset, ((pstWchnCfg->u64Finfo >> 32 ) & 0xffffffff ));
        VPSS_WCHN_ENV_SetFinfoL    ( pstReg, u32RealOffset, ((pstWchnCfg->u64Finfo     ) & 0xffffffff ));
        //---------------------------
        //Assertion
        //---------------------------
        if (pstWchnCfg->bEn)
        {
            XDP_ASSERT(pstWchnCfg->stOutRect.u32Wth >= 32);
            XDP_ASSERT(pstWchnCfg->stOutRect.u32Hgt >= 8 );
            XDP_ASSERT(pstWchnCfg->enCmpType == XDP_CMP_TYPE_OFF);
        }
    }
    else
    {
        u32RealOffset = (gu32VpssWchnAddr[enLayer] - VPSS_WCHN_SOLO_START_OFFSET);
        //---------------------------
        //Cfg
        //---------------------------
        VPSS_WCHN_SOLO_SetEn         ( pstReg, u32RealOffset, pstWchnCfg->bEn        );
        //VPSS_WCHN_SOLO_SetFlip       ( pstReg, u32RealOffset, pstWchnCfg->bFlipEn    );
        //VPSS_WCHN_SOLO_SetMirror     ( pstReg, u32RealOffset, pstWchnCfg->bMirrorEn  );
        //VPSS_WCHN_SOLO_SetTunlEn     ( pstReg, u32RealOffset, pstWchnCfg->bTunlEn    );
        VPSS_WCHN_SOLO_SetDBypass    ( pstReg, u32RealOffset, pstWchnCfg->bMmuBypass );
        //---------------------------
        // Addr
        //---------------------------
        //VPSS_WCHN_SOLO_SetAddrH      ( pstReg, u32RealOffset, ((pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr>>32 ) & 0xffffffff ));
        VPSS_WCHN_SOLO_SetAddrL      ( pstReg, u32RealOffset, ((pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr     ) & 0xffffffff ));
        VPSS_WCHN_SOLO_SetStride     ( pstReg, u32RealOffset,   pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32YStr                      );
#if 1//EDA_TEST
        //---------------------------
        // Env Reg Setting
        //---------------------------
        VPSS_WCHN_SOLO_ENV_SetWidth  ( pstReg, u32RealOffset, pstWchnCfg->stOutRect.u32Wth - 1 );
        VPSS_WCHN_SOLO_ENV_SetHeight ( pstReg, u32RealOffset, pstWchnCfg->stOutRect.u32Hgt - 1 );
#endif
    }

    //---------------------------
    //Assertion
    //---------------------------
    if (pstWchnCfg->bEn)
    {
        XDP_ASSERT(pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32YStr % 16 == 0);
        XDP_ASSERT(pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32CStr % 16 == 0);
        //XDP_ASSERT(pstWchnCfg->stOutRect.u32Wth <= gu32VpssWchnMaxWth[enLayer]);
        // XDP_ASSERT(pstWchnCfg->stOutRect.u32Hgt <= gu32VpssWchnMaxHgt[enLayer]);
        if (pstWchnCfg->stDitherCfg.bEn)
        {
            XDP_ASSERT(pstWchnCfg->enDataWidth == XDP_DATA_WTH_8);
        }
    }

    return;
}



HI_VOID CBB_WFrmStMap(CBB_FRAME_S *pstFrmCfg, VPSS_MAC_WCHN_CFG_S *pstWchnCfg, CBB_FRAME_CHANNEL_E enFrameChan)
{
    pstWchnCfg->bEn = pstFrmCfg->bEn;

    pstWchnCfg->stOutRect.u32X = (HI_U32)pstFrmCfg->stOffset.s32X;
    pstWchnCfg->stOutRect.u32Y = (HI_U32)pstFrmCfg->stOffset.s32Y;
    pstWchnCfg->stOutRect.u32Wth = pstFrmCfg->u32Width;
    pstWchnCfg->stOutRect.u32Hgt = pstFrmCfg->u32Height;

    pstWchnCfg->enDataWidth = (XDP_DATA_WTH) pstFrmCfg->enBitWidth;
    pstWchnCfg->enCmpType   = XDP_CMP_TYPE_OFF;

    pstWchnCfg->bMmuBypass  = !pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y;

    CBB_WFrmPixelFmtMap(pstFrmCfg, pstWchnCfg, enFrameChan);

    CBB_WFrmAddrMap(pstFrmCfg, pstWchnCfg);
}

HI_S32 CBB_CfgFrm_ReadChn(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr, CBB_FRAME_CHANNEL_E enFrameChan)
{
    S_VPSS_REGS_TYPE *pstVpssNode = HI_NULL;  //DDR中节点首地址
    VPSS_MAC_RCHN_CFG_S stRchnCfg = {0};
    VPSS_MAC_RCHN_E enVpssMacRchn = VPSS_MAC_RCHN_CF;

    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;
    enVpssMacRchn = CBB_FrmRChnEnumMap(enFrameChan);

    //VPSS_MAC_InitRchnCfg(enVpssMacRchn, &stRchnCfg);
    CBB_RFrmStMap(pstFrmCfg, &stRchnCfg, enFrameChan);
    CBB_MAC_SetRchnCfg(pstVpssNode, enVpssMacRchn, &stRchnCfg);

    if (CBB_FRAME_READ_NX2 == enFrameChan)
    {
        VPSS_MAC_SetProt( pstVpssNode, (HI_TRUE == pstFrmCfg->bSecure) ? 0x0 : 0x2);
    }

    return HI_SUCCESS;
}

HI_S32 CBB_CfgFrm_WriteChn(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr, CBB_FRAME_CHANNEL_E enFrameChan)
{
    S_VPSS_REGS_TYPE *pstVpssNode = HI_NULL;  //DDR中节点首地址
    VPSS_MAC_WCHN_CFG_S stWchnCfg = {0};
    VPSS_MAC_WCHN_E enVpssMacWchn = VPSS_MAC_WCHN_OUT0;

    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;
    enVpssMacWchn = CBB_FrmWChnEnumMap(enFrameChan);

    //VPSS_MAC_InitWchnCfg(enVpssMacWchn, &stWchnCfg);
    CBB_WFrmStMap(pstFrmCfg, &stWchnCfg, enFrameChan);
    CBB_MAC_SetWchnCfg(pstVpssNode, enVpssMacWchn, &stWchnCfg);

    return HI_SUCCESS;
}

#if 0
HI_S32 CBB_CfgFrm_ReadCur(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    //CBB_FUNC_VC1_S        stFuncVC1Cfg;
    //CBB_FRAME_CHANNEL_E enChan;
    HI_BOOL             bEnTile;
    HI_U32              u32BitWth;

    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    if (pstFrmCfg->enBitWidth == CBB_BITWIDTH_8BIT)
    {
        u32BitWth = 0;
    }
    else if (pstFrmCfg->enBitWidth == CBB_BITWIDTH_10BIT)
    {
        u32BitWth = 1;
    }
    else
    {
        CBB_ERRMSG("invalid enBitWidth\n");
        return HI_FAILURE;
    }

    switch (pstFrmCfg->enPixelFmt)
    {
        case HI_DRV_PIX_FMT_NV12_TILE: /* 12 tile  */
        case HI_DRV_PIX_FMT_NV21_TILE: /* 21 tile  */
        case HI_DRV_PIX_FMT_YUV400_TILE: /* 21 tile  */
        case HI_DRV_PIX_FMT_NV12_TILE_CMP:
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:
            bEnTile = HI_TRUE;
            break;
        default:
            bEnTile = HI_FALSE;
            break;
    }

    VPSS_Mac_SetRchCuryBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y);
    VPSS_Mac_SetRchCurcBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C);


    VPSS_Sys_SetRefDitherMode(pstVpssNode, REG_DITHER_MODE_DITHER);
    VPSS_Sys_SetRefDitherEn(pstVpssNode, HI_FALSE);
#if 0
    stFuncVC1Cfg.bEnable = HI_FALSE;
    enChan = CBB_FRAME_READ_CUR;
    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VC1, (HI_VOID *)&stFuncVC1Cfg, (HI_VOID *)&enChan);
#endif
    VPSS_Mac_SetRefWidth(pstVpssNode, pstFrmCfg->u32Width);
    VPSS_Mac_SetRefHeight(pstVpssNode, pstFrmCfg->u32Height);
    VPSS_Mac_SetCurHorOffset(pstVpssNode, pstFrmCfg->stOffset.s32X);
    VPSS_Mac_SetCurVerOffset(pstVpssNode, pstFrmCfg->stOffset.s32Y);
    VPSS_Mac_SetCurTileFormat(pstVpssNode, bEnTile);
    VPSS_Mac_SetCuryAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y);
    VPSS_Mac_SetCurcAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C);
    VPSS_Mac_SetCuryStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y);
    VPSS_Mac_SetCurcStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C);
    VPSS_Sys_SetRefPixBitw(pstVpssNode, u32BitWth);
    return HI_SUCCESS;
}

HI_S32 CBB_CfgFrm_ReadNx1(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    //CBB_FUNC_VC1_S        stFuncVC1Cfg;
    //CBB_FRAME_CHANNEL_E enChan;
    HI_BOOL             bEnTile;
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    switch (pstFrmCfg->enPixelFmt)
    {
        case HI_DRV_PIX_FMT_NV12_TILE: /* 12 tile  */
        case HI_DRV_PIX_FMT_NV21_TILE: /* 21 tile  */
        case HI_DRV_PIX_FMT_YUV400_TILE: /* 21 tile  */
        case HI_DRV_PIX_FMT_NV12_TILE_CMP:
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:

            bEnTile = HI_TRUE;
            break;
        default:
            bEnTile = HI_FALSE;
            break;
    }

    VPSS_Mac_SetRchNx1yBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y);
    VPSS_Mac_SetRchNx1cBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C);

#if 0
    stFuncVC1Cfg.bEnable = HI_FALSE;
    enChan = CBB_FRAME_READ_NX1;
    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VC1, (HI_VOID *)&stFuncVC1Cfg, (HI_VOID *)&enChan);
#endif

    VPSS_Mac_SetNxt1HorOffset(pstVpssNode, pstFrmCfg->stOffset.s32X);
    VPSS_Mac_SetNxt1VerOffset(pstVpssNode, pstFrmCfg->stOffset.s32Y);
    VPSS_Mac_SetNxt1TileFormat(pstVpssNode, bEnTile);
    VPSS_Mac_SetNxt1yAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y);
    VPSS_Mac_SetNxt1cAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C);
    VPSS_Mac_SetNxt1yStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y);
    VPSS_Mac_SetNxt1cStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C);

    return HI_SUCCESS;
}

HI_U32 CBB_FrameFmtTrans( HI_DRV_PIX_FORMAT_E   enPixelFmt )
{
    HI_U32 u32Fmt = 0;

    switch (enPixelFmt)
    {
        case HI_DRV_PIX_FMT_NV21:
        case HI_DRV_PIX_FMT_NV12:
        case HI_DRV_PIX_FMT_NV12_CMP:
        case HI_DRV_PIX_FMT_NV21_CMP:
        case HI_DRV_PIX_FMT_NV12_TILE:
        case HI_DRV_PIX_FMT_NV21_TILE:
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:
        case HI_DRV_PIX_FMT_NV12_TILE_CMP:
            u32Fmt = 0x0;
            break;
        case HI_DRV_PIX_FMT_NV61_2X1_CMP:
        case HI_DRV_PIX_FMT_NV16_2X1_CMP:
        case HI_DRV_PIX_FMT_NV61_CMP:
        case HI_DRV_PIX_FMT_NV16_CMP:
        case HI_DRV_PIX_FMT_NV16_2X1:
        case HI_DRV_PIX_FMT_NV61_2X1:
        case HI_DRV_PIX_FMT_NV16:
        case HI_DRV_PIX_FMT_NV61:
            u32Fmt = 0x1;
            break;
        case HI_DRV_PIX_FMT_YUV400:
            u32Fmt = 0x4;
            break;
        case HI_DRV_PIX_FMT_YUV_444:
            u32Fmt = 0x5;
            break;
        case HI_DRV_PIX_FMT_YUV422_2X1:
            u32Fmt = 0x6;
            break;
        case HI_DRV_PIX_FMT_YUV420p:
            u32Fmt = 0x8;
            break;
        case HI_DRV_PIX_FMT_YUV411:
            u32Fmt = 0x9;
            break;
        case HI_DRV_PIX_FMT_YUV410p:
            u32Fmt = 0xa;
            break;
        case HI_DRV_PIX_FMT_YUYV:
            u32Fmt = 0xb;
            break;
        case HI_DRV_PIX_FMT_YVYU:
            u32Fmt = 0xc;
            break;
        case HI_DRV_PIX_FMT_UYVY:
            u32Fmt = 0xd;
            break;
        default:
            CBB_ERRMSG("REG ERROR");
    }

    return u32Fmt;
}

HI_S32 CBB_CfgFrm_ReadNx2(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    HI_U32 u32BitWth = 0;
    HI_U32 u32Format = 0;
    HI_BOOL bEnTile = HI_FALSE;
    HI_BOOL bDeCmp;
    HI_U32 u32Field;
    HI_U32 u32FieldFirst;
    //CBB_FUNC_VC1_S        stFuncVC1Cfg;
    //CBB_FRAME_CHANNEL_E enChan;
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    if (pstFrmCfg->enBitWidth == CBB_BITWIDTH_8BIT)
    {
        u32BitWth = 0;
    }
    else if (pstFrmCfg->enBitWidth == CBB_BITWIDTH_10BIT)
    {
        u32BitWth = 1;
    }
    else
    {
        CBB_ERRMSG("invalid enBitWth\n");
        return HI_FAILURE;
    }
#if (!CBB_TEST)
    switch (pstFrmCfg->enPixelFmt)
    {
        case HI_DRV_PIX_FMT_NV12_TILE: /* 12 tile  */
        case HI_DRV_PIX_FMT_NV21_TILE: /* 21 tile  */
        case HI_DRV_PIX_FMT_YUV400_TILE: /* 21 tile  */
        case HI_DRV_PIX_FMT_NV12_TILE_CMP:
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:

            bEnTile = HI_TRUE;
            break;
        default:
            bEnTile = HI_FALSE;
            break;
    }

    u32Format = CBB_FrameFmtTrans(pstFrmCfg->enPixelFmt);
#else
    switch (pstFrmCfg->enPixelFmt)
    {
        case INPUTFMT_TILE_SP420 :
        case INPUTFMT_TILE_400 :
            bEnTile = HI_TRUE;
            break;
        default:
            bEnTile = HI_FALSE;
            break;
    }
    u32Format = VPSS_FrameFmtTrans(pstFrmCfg->enPixelFmt);
#endif

    if (pstFrmCfg->bProgressive)
    {
        VPSS_Sys_SetBfield(pstVpssNode, HI_FALSE);
    }
    else
    {
        VPSS_Sys_SetBfield(pstVpssNode, HI_TRUE);
    }

    if (pstFrmCfg->bTop)
    {
        u32Field = 0x0;
    }
    else
    {
        u32Field = 0x1;
    }

    if (pstFrmCfg->bTopFirst)
    {
        u32FieldFirst = 0x0;
    }
    else
    {
        u32FieldFirst = 0x1;
    }

    VPSS_INFO("u32FieldFirst : %d.\n", u32FieldFirst);

    //VPSS_MEM_CLEAR(stFuncVC1Cfg);
    VPSS_Mac_SetRchNx2yBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y);
    VPSS_Mac_SetRchNx2cBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C);
    VPSS_Mac_SetRchNx2ylbBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y);
    VPSS_Mac_SetRchNx2clbBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C);

    VPSS_Sys_SetBfieldMode(pstVpssNode, u32Field);
    VPSS_Sys_SetBfieldFirst(pstVpssNode, u32FieldFirst);
#if 0
    stFuncVC1Cfg.bEnable = HI_FALSE;
    enChan = CBB_FRAME_READ_NX2;
    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VC1, (HI_VOID *)&stFuncVC1Cfg, (HI_VOID *)&enChan);
#endif
    if (pstFrmCfg->bSecure)
    {
        VPSS_Sys_SetProt(pstVpssNode, 0);
    }
    else
    {
        VPSS_Sys_SetProt(pstVpssNode, 2);
    }

    if (pstFrmCfg->bCompress)
    {
        VPSS_Mac_SetNx2yTopHeadAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_YHead);
        VPSS_Mac_SetNx2yBotHeadAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_YHead);
        VPSS_Mac_SetNx2cTopHeadAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_CHead);
        VPSS_Mac_SetNx2cBotHeadAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_CHead);
        VPSS_Mac_SetNx2HeadStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Head_Stride);

        VPSS_Mac_SetRchNx2yHeadBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_YHead);
        VPSS_Mac_SetRchNx2cHeadBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_CHead);
        bDeCmp = HI_TRUE;
    }
    else
    {
        bDeCmp = HI_FALSE;
    }

    VPSS_Sys_SetInPixBitw(pstVpssNode, u32BitWth);
    VPSS_Sys_SetInFormat(pstVpssNode, u32Format);
    VPSS_Mac_SetImgwidth(pstVpssNode, pstFrmCfg->u32Width);
    VPSS_Mac_SetImgheight(pstVpssNode, pstFrmCfg->u32Height);


    VPSS_Mac_SetNxt2yAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y);
    VPSS_Mac_SetNxt2cAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C);
    VPSS_Mac_SetNxt2yStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y);
    VPSS_Mac_SetNxt2cStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C);

    VPSS_Mac_SetNxt2DcmpEn(pstVpssNode, bDeCmp);
    VPSS_Mac_SetNxt2HorOffset(pstVpssNode, pstFrmCfg->stOffset.s32X);
    VPSS_Mac_SetNxt2VerOffset(pstVpssNode, pstFrmCfg->stOffset.s32Y);
    VPSS_Mac_SetNxt2TileFormat(pstVpssNode, bEnTile);

    if ( CBB_BITWIDTH_10BIT == pstFrmCfg->enBitWidth && bEnTile == HI_TRUE)
    {
        VPSS_Mac_SetNx2yLbAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_Y);
        VPSS_Mac_SetNx2cLbAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_C);
        VPSS_Mac_SetNx2LbStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_Y);
    }

    return HI_SUCCESS;
}


HI_S32 CBB_CfgFrm_ReadRef(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    HI_U32 u32BitWth = 0;
    //CBB_FUNC_VC1_S        stFuncVC1Cfg;
    //CBB_FRAME_CHANNEL_E enChan;
    HI_BOOL             bEnTile;
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;


    if (pstFrmCfg->enBitWidth == CBB_BITWIDTH_8BIT)
    {
        u32BitWth = 0;
    }
    else if (pstFrmCfg->enBitWidth == CBB_BITWIDTH_10BIT)
    {
        u32BitWth = 1;
    }
    else
    {
        CBB_ERRMSG("invalid enBitWidth\n");
        return HI_FAILURE;
    }

    switch (pstFrmCfg->enPixelFmt)
    {
        case HI_DRV_PIX_FMT_NV12_TILE: /* 12 tile  */
        case HI_DRV_PIX_FMT_NV21_TILE: /* 21 tile  */
        case HI_DRV_PIX_FMT_YUV400_TILE: /* 21 tile  */
            bEnTile = HI_TRUE;
            break;
        default:
            bEnTile = HI_FALSE;
            break;
    }

    VPSS_Mac_SetRchRefyBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y);
    VPSS_Mac_SetRchRefcBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C);

#if 0
    stFuncVC1Cfg.bEnable = HI_FALSE;
    enChan = CBB_FRAME_READ_REF;
    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VC1, (HI_VOID *)&stFuncVC1Cfg, (HI_VOID *)&enChan);
#endif
    //VPSS_Mac_SetRefWidth(pstVpssNode, pstFrmCfg->u32Width);
    //VPSS_Mac_SetRefHeight(pstVpssNode, pstFrmCfg->u32Height);

    VPSS_Mac_SetRefHorOffset(pstVpssNode, pstFrmCfg->stOffset.s32X);
    VPSS_Mac_SetRefVerOffset(pstVpssNode, pstFrmCfg->stOffset.s32Y);
    VPSS_Mac_SetRefTileFormat(pstVpssNode, bEnTile);

    VPSS_Mac_SetRefyAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y);
    VPSS_Mac_SetRefcAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C);
    VPSS_Mac_SetRefyStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y);
    VPSS_Mac_SetRefcStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C);


    return HI_SUCCESS;
}

HI_S32 CBB_CfgFrm_ReadRee(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    CBB_FRAME_ADDR_S    *pstAddr;
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    pstAddr = &(pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT]);
    VPSS_Mac_SetReeyAddr(pstVpssNode, pstAddr->u32PhyAddr_Y);
    VPSS_Mac_SetReecAddr(pstVpssNode, pstAddr->u32PhyAddr_C);
    VPSS_Mac_SetReeyStride(pstVpssNode, pstAddr->u32Stride_Y);
    VPSS_Mac_SetReecStride(pstVpssNode, pstAddr->u32Stride_C);

    VPSS_Mac_SetRchReeyBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y);
    VPSS_Mac_SetRchReecBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C);

    return HI_SUCCESS;
}


HI_S32 CBB_CfgFrm_WriteVhd0(CBB_FRAME_S *pstFrmCfg, HI_VOID *pArgs, CBB_REG_ADDR_S stRegAddr)
{

    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    HI_U32 u32BitWth = 0;
    HI_U32 u32CtsEn = 0;
    HI_U32 u32Format = 0;
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    if (pstFrmCfg->enBitWidth == CBB_BITWIDTH_8BIT)
    {
        u32BitWth = 0;
    }
    else if ((pstFrmCfg->enBitWidth == CBB_BITWIDTH_10BIT) || (pstFrmCfg->enBitWidth == CBB_BITWIDTH_10BIT_CTS))
    {
        u32BitWth = 1;
    }
    else
    {
        CBB_ERRMSG("invalid enBitWidth\n");
        return HI_FAILURE;
    }
    if (pstFrmCfg->enBitWidth == CBB_BITWIDTH_10BIT_CTS)
    {
        u32CtsEn = 1;
    }
    else
    {
        u32CtsEn = 0;
    }
#if 0
    switch (pstFrmCfg->enPixelFmt)
    {
        case HI_DRV_PIX_FMT_NV21:
        case HI_DRV_PIX_FMT_NV12:
            u32Format = 0x0;
            break;
        case HI_DRV_PIX_FMT_NV61_2X1:
        case HI_DRV_PIX_FMT_NV16_2X1:
        case HI_DRV_PIX_FMT_NV16:
        case HI_DRV_PIX_FMT_NV61:
            u32Format = 0x1;
            break;
        default:
            return HI_FAILURE;
    }
#else
    u32Format = pstFrmCfg->enPixelFmt ;
#endif
    VPSS_Sys_SetCtsEn(pstVpssNode, u32CtsEn);
    VPSS_Sys_SetCtsBitSel(pstVpssNode, 0);

    VPSS_Mac_SetVhd0Width(pstVpssNode, pstFrmCfg->u32Width);
    VPSS_Mac_SetVhd0Height(pstVpssNode, pstFrmCfg->u32Height);
    VPSS_Mac_SetVhd0PixBitw(pstVpssNode, u32BitWth);
    VPSS_Sys_SetVhd0Format(pstVpssNode, u32Format);

    if (pstFrmCfg->enBitWidth > CBB_BITWIDTH_8BIT)
    {
        VPSS_Mac_SetVhd0DitherMode(pstVpssNode, REG_DITHER_MODE_DITHER);
        VPSS_Mac_SetVhd0DitherEn(pstVpssNode, HI_FALSE);
    }
    else
    {
        VPSS_Mac_SetVhd0DitherMode(pstVpssNode, REG_DITHER_MODE_DITHER);
        VPSS_Mac_SetVhd0DitherEn(pstVpssNode, HI_FALSE);//HI_TRUE);
    }

    VPSS_Mac_SetVhd0yAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y);
    VPSS_Mac_SetVhd0cAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C);
    VPSS_Mac_SetVhd0yStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y);
    VPSS_Mac_SetVhd0cStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C);

    VPSS_Mac_SetWchVhd0yBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y);
    VPSS_Mac_SetWchVhd0cBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C);

    VPSS_Sys_SetVhd0En(pstVpssNode, HI_TRUE);

    return HI_SUCCESS;
}

HI_S32 CBB_CfgFrm_WriteRfr(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr, HI_BOOL bEnable)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    HI_U32 u32BitWth = 0;
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    if (pstFrmCfg->enBitWidth == CBB_BITWIDTH_8BIT)
    {
        u32BitWth = 0;
    }
    else if (pstFrmCfg->enBitWidth == CBB_BITWIDTH_10BIT)
    {
        u32BitWth = 1;
    }
    else
    {
        CBB_ERRMSG("invalid enBitWidth\n");
        return HI_FAILURE;
    }

    //VPSS_Mac_SetRfrWidth(pstVpssNode, pstFrmCfg->u32Width);
    //VPSS_Mac_SetRfrWidth(pstVpssNode, pstFrmCfg->u32Height);
    VPSS_Sys_SetRfrPixBitw(pstVpssNode, u32BitWth);

    VPSS_Mac_SetRfryAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y);
    VPSS_Mac_SetRfrcAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C);
    VPSS_Mac_SetRfryStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y);
    VPSS_Mac_SetRfrcStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C);

    if (pstFrmCfg->enBitWidth > CBB_BITWIDTH_8BIT)
    {
        VPSS_Mac_SetRfrDitherMode(pstVpssNode, REG_DITHER_MODE_DITHER);
        VPSS_Mac_SetRfrDitherEn(pstVpssNode, HI_FALSE);
    }
    else
    {
        VPSS_Mac_SetRfrDitherMode(pstVpssNode, REG_DITHER_MODE_DITHER);
        VPSS_Mac_SetRfrDitherEn(pstVpssNode, HI_FALSE);
    }

    VPSS_Mac_SetWchRfryBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y);
    VPSS_Mac_SetWchRfrcBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C);

    VPSS_Sys_SetRfrEn(pstVpssNode, bEnable);

    return HI_SUCCESS;
}

HI_S32 CBB_CfgFrm_WriteCue(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    CBB_FRAME_ADDR_S    *pstAddr;
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    pstAddr = &(pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT]);

    VPSS_Mac_SetCueyAddr(pstVpssNode,  pstAddr->u32PhyAddr_Y);
    VPSS_Mac_SetCuecAddr(pstVpssNode, pstAddr->u32PhyAddr_C);
    VPSS_Mac_SetCueyStride(pstVpssNode, pstAddr->u32Stride_Y);
    VPSS_Mac_SetCuecStride(pstVpssNode, pstAddr->u32Stride_C);

    VPSS_Mac_SetWchCueyBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y);
    VPSS_Mac_SetWchCuecBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C);

    return HI_SUCCESS;
}
#endif
