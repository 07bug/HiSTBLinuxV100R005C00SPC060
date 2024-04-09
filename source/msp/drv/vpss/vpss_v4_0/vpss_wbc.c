#include "vpss_osal.h"
#include "vpss_cbb_hal.h"
#include "vpss_wbc.h"
#include "vpss_alg_buf.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

HI_U32 VPSS_WBC_GetTotalBufSize(VPSS_WBC_ATTR_S *pstAttr, HI_U32 u32NodeBufSize)
{
    HI_U32 u32TotalBufSize = 0;
    switch (pstAttr->enMode)
    {
        case VPSS_WBC_MODE_NORMAL:
        {
            u32TotalBufSize = u32NodeBufSize * 2;
            break;
        }
        case VPSS_WBC_MODE_3FIELD:
        {
            u32TotalBufSize = u32NodeBufSize * 2;
            break;
        }
        case VPSS_WBC_MODE_4FIELD:
        {
            u32TotalBufSize = u32NodeBufSize * 2;
            break;
        }
        case VPSS_WBC_MODE_5FIELD:
        {
            u32TotalBufSize = u32NodeBufSize * 3;
            break;
        }
        default:
        {
            VPSS_ERROR("Vpss wbc GetTotalBufSize error(WbcMode = %d).\n", pstAttr->enMode);
            return 0;
        }
    }

    return u32TotalBufSize;
}
HI_S32 VPSS_WBC_CalBufSize(HI_U32 *pSize, HI_U32 *pStride, VPSS_WBC_ATTR_S *pstAttr)
{
    HI_U32 u32RetSize = 0;
    HI_U32 u32RetStride = 0;
    HI_U32 u32Height = pstAttr->u32Height;
    HI_U32 u32Width = pstAttr->u32Width;
    HI_DRV_PIX_FORMAT_E ePixFormat = pstAttr->ePixFormat;
    HI_DRV_PIXEL_BITWIDTH_E  enBitWidth = pstAttr->enBitWidth;

    HI_U32 u32FirstWth = 0;
    HI_U32 u32MidWth = 0;
    HI_U32 u32LastWth = 0;
    HI_U32 u32SplitCnt = 0;
    VPSS_HAL_CalcSplitWth(u32Width, &u32FirstWth, &u32MidWth, &u32LastWth, &u32SplitCnt);
    switch (ePixFormat)
    {
        case HI_DRV_PIX_FMT_NV12:
        case HI_DRV_PIX_FMT_NV21:
        case HI_DRV_PIX_FMT_NV12_TILE://wbc don't support tile,use linear
        case HI_DRV_PIX_FMT_NV21_TILE://wbc don't support tile,use linear
        case HI_DRV_PIX_FMT_NV12_TILE_CMP:
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:
        {
            if (HI_DRV_PIXEL_BITWIDTH_8BIT == enBitWidth)
            {
                if (pstAttr->bSplitEnable)
                {
                    u32RetStride = HI_ALIGN_8BIT_YSTRIDE(u32FirstWth);
                    u32RetStride += HI_ALIGN_8BIT_YSTRIDE(u32MidWth) * ((u32SplitCnt > 2) ? (u32SplitCnt - 2) : 0);
                    u32RetStride += HI_ALIGN_8BIT_YSTRIDE(u32LastWth);
                }
                else
                {
                    u32RetStride = HI_ALIGN_8BIT_YSTRIDE(u32Width);
                }
                u32RetSize = u32Height * u32RetStride * 3 / 2;
#ifdef VPSS_SUPPORT_SPLIT_MCDI_MANR
                if (pstAttr->bSplitEnable)
                {
                    u32RetSize = (u32Height + VPSS_OVERLAP_HEIGHT) * u32RetStride * 3 / 2;
                }
#endif
            }
            else if (HI_DRV_PIXEL_BITWIDTH_10BIT == enBitWidth)
            {
                if (pstAttr->bSplitEnable)
                {
                    u32RetStride = HI_ALIGN_10BIT_COMP_YSTRIDE((u32FirstWth * 10 + 7) / 8);
                    u32RetStride += HI_ALIGN_10BIT_COMP_YSTRIDE((u32MidWth * 10 + 7) / 8) * ((u32SplitCnt > 2) ? (u32SplitCnt - 2) : 0);
                    u32RetStride += HI_ALIGN_10BIT_COMP_YSTRIDE((u32LastWth * 10 + 7) / 8);
                }
                else
                {
                    u32RetStride = HI_ALIGN_10BIT_COMP_YSTRIDE(u32Width);
                }
                u32RetSize = u32Height * u32RetStride * 3 / 2;

#ifdef VPSS_SUPPORT_SPLIT_MCDI_MANR
                if (pstAttr->bSplitEnable)
                {
                    u32RetSize = (u32Height + VPSS_OVERLAP_HEIGHT) * u32RetStride * 3 / 2;
                }
#endif
            }
            else
            {
                VPSS_FATAL("Unsupport BitWidth %d.\n", enBitWidth);
                return HI_FAILURE;
            }
            break;
        }
        case HI_DRV_PIX_FMT_NV16_2X1:
        case HI_DRV_PIX_FMT_NV61_2X1:
        case HI_DRV_PIX_FMT_YUYV:
        case HI_DRV_PIX_FMT_YVYU:
        case HI_DRV_PIX_FMT_UYVY:
        {
            if (HI_DRV_PIXEL_BITWIDTH_8BIT == enBitWidth)
            {
                if (pstAttr->bSplitEnable)
                {
                    u32RetStride = HI_ALIGN_8BIT_YSTRIDE(u32FirstWth);
                    u32RetStride += HI_ALIGN_8BIT_YSTRIDE(u32MidWth) * ((u32SplitCnt > 2) ? (u32SplitCnt - 2) : 0);
                    u32RetStride += HI_ALIGN_8BIT_YSTRIDE(u32LastWth);
                }
                else
                {
                    u32RetStride = HI_ALIGN_8BIT_YSTRIDE(u32Width);
                }
                u32RetSize = u32Height * u32RetStride * 2;
#ifdef VPSS_SUPPORT_SPLIT_MCDI_MANR
                if (pstAttr->bSplitEnable)
                {
                    u32RetSize = (u32Height + VPSS_OVERLAP_HEIGHT) * u32RetStride * 2;
                }
#endif

            }
            else if (HI_DRV_PIXEL_BITWIDTH_10BIT == enBitWidth)
            {
                if (pstAttr->bSplitEnable)
                {
                    u32RetStride = HI_ALIGN_10BIT_COMP_YSTRIDE((u32FirstWth * 10 + 7) / 8);
                    u32RetStride += HI_ALIGN_10BIT_COMP_YSTRIDE((u32MidWth * 10 + 7) / 8) * ((u32SplitCnt > 2) ? (u32SplitCnt - 2) : 0);
                    u32RetStride += HI_ALIGN_10BIT_COMP_YSTRIDE((u32LastWth * 10 + 7) / 8);
                }
                else
                {
                    u32RetStride = HI_ALIGN_10BIT_COMP_YSTRIDE(u32Width);
                }
                u32RetSize = u32Height * u32RetStride * 2;

#ifdef VPSS_SUPPORT_SPLIT_MCDI_MANR
                if (pstAttr->bSplitEnable)
                {
                    u32RetSize = (u32Height + VPSS_OVERLAP_HEIGHT) * u32RetStride * 2;
                }
#endif

            }
            else
            {
                VPSS_FATAL("Unsupport BitWidth %d.\n", enBitWidth);
                return HI_FAILURE;
            }
            break;
        }
        case HI_DRV_PIX_FMT_NV12_CMP:
        case HI_DRV_PIX_FMT_NV21_CMP:
        {
            if (HI_DRV_PIXEL_BITWIDTH_8BIT == enBitWidth)
            {
                if (pstAttr->bSplitEnable)
                {
                    u32RetStride = HI_ALIGN_8BIT_YSTRIDE(u32FirstWth);
                    u32RetStride += HI_ALIGN_8BIT_YSTRIDE(u32MidWth) * ((u32SplitCnt > 2) ? (u32SplitCnt - 2) : 0);
                    u32RetStride += HI_ALIGN_8BIT_YSTRIDE(u32LastWth);
                }
                else
                {
                    u32RetStride = HI_ALIGN_8BIT_YSTRIDE(u32Width);
                }
                u32RetSize = u32Height * u32RetStride * 3 / 2 + 16 * u32Height * 3 / 2;

#ifdef VPSS_SUPPORT_SPLIT_MCDI_MANR
                if (pstAttr->bSplitEnable)
                {
                    u32RetSize = (u32Height + VPSS_OVERLAP_HEIGHT) * u32RetStride * 3 / 2 + 16 * ( u32Height + VPSS_OVERLAP_HEIGHT ) * 3 / 2;
                }
#endif

            }
            else if (HI_DRV_PIXEL_BITWIDTH_10BIT == enBitWidth)
            {
                if (pstAttr->bSplitEnable)
                {
                    u32RetStride = HI_ALIGN_10BIT_COMP_YSTRIDE(u32FirstWth);
                    u32RetStride += HI_ALIGN_10BIT_COMP_YSTRIDE(u32MidWth) * ((u32SplitCnt > 2) ? (u32SplitCnt - 2) : 0);
                    u32RetStride += HI_ALIGN_10BIT_COMP_YSTRIDE(u32LastWth);
                }
                else
                {
                    u32RetStride = HI_ALIGN_10BIT_COMP_YSTRIDE(u32Width);
                }
                u32RetSize = u32Height * u32RetStride * 3 / 2 + 16 * u32Height * 3 / 2;

#ifdef VPSS_SUPPORT_SPLIT_MCDI_MANR
                if (pstAttr->bSplitEnable)
                {
                    u32RetSize = (u32Height + VPSS_OVERLAP_HEIGHT) * u32RetStride * 3 / 2 + 16 * ( u32Height + VPSS_OVERLAP_HEIGHT ) * 3 / 2;
                }
#endif

            }
            else
            {
                VPSS_FATAL("Unsupport BitWidth %d.\n", enBitWidth);
                return HI_FAILURE;
            }
            break;
        }
        case HI_DRV_PIX_FMT_NV16_CMP:
        case HI_DRV_PIX_FMT_NV61_CMP:
        {
            if (HI_DRV_PIXEL_BITWIDTH_8BIT == enBitWidth)
            {
                if (pstAttr->bSplitEnable)
                {
                    u32RetStride = HI_ALIGN_8BIT_YSTRIDE(u32FirstWth);
                    u32RetStride += HI_ALIGN_8BIT_YSTRIDE(u32MidWth) * ((u32SplitCnt > 2) ? (u32SplitCnt - 2) : 0);
                    u32RetStride += HI_ALIGN_8BIT_YSTRIDE(u32LastWth);
                }
                else
                {
                    u32RetStride = HI_ALIGN_8BIT_YSTRIDE(u32Width);
                }
                u32RetSize = u32Height * u32RetStride * 3 / 2 + 16 * u32Height * 2;

#ifdef VPSS_SUPPORT_SPLIT_MCDI_MANR
                if (pstAttr->bSplitEnable)
                {
                    u32RetSize = (u32Height + VPSS_OVERLAP_HEIGHT) * u32RetStride * 3 / 2 + 16 * ( u32Height + VPSS_OVERLAP_HEIGHT ) * 2;
                }
#endif

            }
            else if (HI_DRV_PIXEL_BITWIDTH_10BIT == enBitWidth)
            {
                if (pstAttr->bSplitEnable)
                {
                    u32RetStride = HI_ALIGN_10BIT_COMP_YSTRIDE(u32FirstWth);
                    u32RetStride += HI_ALIGN_10BIT_COMP_YSTRIDE(u32MidWth) * ((u32SplitCnt > 2) ? (u32SplitCnt - 2) : 0);
                    u32RetStride += HI_ALIGN_10BIT_COMP_YSTRIDE(u32LastWth);
                }
                else
                {
                    u32RetStride = HI_ALIGN_10BIT_COMP_YSTRIDE(u32Width);
                }
                u32RetSize = u32Height * u32RetStride * 3 / 2 + 16 * u32Height * 2;

#ifdef VPSS_SUPPORT_SPLIT_MCDI_MANR
                if (pstAttr->bSplitEnable)
                {
                    u32RetSize = (u32Height + VPSS_OVERLAP_HEIGHT) * u32RetStride * 3 / 2 + 16 * ( u32Height + VPSS_OVERLAP_HEIGHT ) * 2;
                }
#endif

            }
            else
            {
                VPSS_FATAL("Unsupport BitWidth %d.\n", enBitWidth);
                return HI_FAILURE;
            }
            break;
        }
        case HI_DRV_PIX_FMT_ARGB8888:
        case HI_DRV_PIX_FMT_ABGR8888:
        {
            if (HI_DRV_PIXEL_BITWIDTH_8BIT == enBitWidth)
            {
                u32RetStride = HI_ALIGN_8BIT_YSTRIDE(u32Width * 4);
                u32RetSize = u32Height * u32RetStride;
            }
            else if (HI_DRV_PIXEL_BITWIDTH_10BIT == enBitWidth)
            {
                u32RetStride = HI_ALIGN_10BIT_COMP_YSTRIDE(u32Width * 4);
                u32RetSize = u32Height * u32RetStride;
            }
            else
            {
                VPSS_FATAL("Unsupport BitWidth %d.\n", enBitWidth);
                return HI_FAILURE;
            }
            break;
        }
        default:
        {
            VPSS_FATAL("Unsupport PixFormat %d.\n", ePixFormat);
            return HI_FAILURE;
        }
    }
    *pSize = u32RetSize;
    *pStride = u32RetStride;
    return HI_SUCCESS;
}

HI_S32 VPSS_WBC_InitFrame(HI_DRV_VIDEO_FRAME_S *pstWbcFrame, VPSS_WBC_ATTR_S *pstAttr, HI_U32 u32PhyAddr, HI_U8 *pu8VirAddr)
{
    HI_U32 u32Stride = 0;
    HI_U32 u32BuffSize = 0;
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32ImgHeight;

    s32Ret = VPSS_WBC_CalBufSize(&u32BuffSize, &u32Stride, pstAttr);

    if (HI_FAILURE == s32Ret)
    {
        return HI_FAILURE;
    }

    pstWbcFrame->u32Width = pstAttr->u32Width;
    pstWbcFrame->u32Height = pstAttr->u32Height;
    pstWbcFrame->enBitWidth = pstAttr->enBitWidth;
    pstWbcFrame->ePixFormat = pstAttr->ePixFormat;
    u32ImgHeight = pstAttr->u32Height;

#ifdef VPSS_SUPPORT_TB_SAME_ADDR
    if (VPSS_WBC_MODE_NORMAL != pstAttr->enMode)
    {
        u32ImgHeight = u32ImgHeight / 2;
    }
#endif

    pstWbcFrame->stBufAddr[0].u32Stride_Y = u32Stride;
    pstWbcFrame->stBufAddr[0].u32Stride_C = u32Stride;

    pstWbcFrame->stBufAddr[0].vir_addr_y = (HI_U64)(HI_SIZE_T)pu8VirAddr;

    pstWbcFrame->u32FrameIndex = pstAttr->u32FrameIndex;
    pstWbcFrame->u32Pts = pstAttr->u32Pts;
    pstWbcFrame->s64OmxPts = pstAttr->s64OmxPts;
    pstWbcFrame->bSecure = pstAttr->bSecure;

    switch (pstAttr->ePixFormat)
    {
        case HI_DRV_PIX_FMT_NV12_TILE://wbc don't support tile,use linear
            pstWbcFrame->ePixFormat = HI_DRV_PIX_FMT_NV12;
            break;
        case HI_DRV_PIX_FMT_NV21_TILE://wbc don't support tile,use linear
            pstWbcFrame->ePixFormat = HI_DRV_PIX_FMT_NV21;
            break;
        case HI_DRV_PIX_FMT_NV12_TILE_CMP://wbc don't support tile,use linear
            pstWbcFrame->ePixFormat = HI_DRV_PIX_FMT_NV12_CMP;
            break;
        case HI_DRV_PIX_FMT_NV21_TILE_CMP://wbc don't support tile,use linear
            pstWbcFrame->ePixFormat = HI_DRV_PIX_FMT_NV21_CMP;
            break;
        case HI_DRV_PIX_FMT_YUYV:
        case HI_DRV_PIX_FMT_YVYU:
        case HI_DRV_PIX_FMT_UYVY:
            pstWbcFrame->ePixFormat = HI_DRV_PIX_FMT_NV61_2X1;
            break;
        default:
        {
            pstWbcFrame->ePixFormat = pstAttr->ePixFormat;
        }
    }

    switch (pstAttr->ePixFormat)
    {
        case HI_DRV_PIX_FMT_NV12:
        case HI_DRV_PIX_FMT_NV21:
        case HI_DRV_PIX_FMT_NV12_TILE://wbc don't support tile,use linear
        case HI_DRV_PIX_FMT_NV21_TILE://wbc don't support tile,use linear
        case HI_DRV_PIX_FMT_NV16_2X1:
        case HI_DRV_PIX_FMT_NV61_2X1:
        case HI_DRV_PIX_FMT_YUYV:
        case HI_DRV_PIX_FMT_YVYU:
        case HI_DRV_PIX_FMT_UYVY:
        {
            pstWbcFrame->stBufAddr[0].u32PhyAddr_Y = u32PhyAddr;
            pstWbcFrame->stBufAddr[0].u32PhyAddr_C = u32PhyAddr + u32Stride * u32ImgHeight;
            break;
        }
        case HI_DRV_PIX_FMT_NV12_CMP:
        case HI_DRV_PIX_FMT_NV21_CMP:
        case HI_DRV_PIX_FMT_NV12_TILE_CMP:
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:
        case HI_DRV_PIX_FMT_NV16_CMP:
        case HI_DRV_PIX_FMT_NV61_CMP:
        {
            pstWbcFrame->stBufAddr[0].u32PhyAddr_YHead = u32PhyAddr;
            pstWbcFrame->stBufAddr[0].u32PhyAddr_Y = u32PhyAddr + u32ImgHeight * 16;
            pstWbcFrame->stBufAddr[0].u32PhyAddr_CHead =
                pstWbcFrame->stBufAddr[0].u32PhyAddr_Y + u32Stride * u32ImgHeight;

            if ((HI_DRV_PIX_FMT_NV12_CMP == pstAttr->ePixFormat
                 || HI_DRV_PIX_FMT_NV21_CMP == pstAttr->ePixFormat)
                || (HI_DRV_PIX_FMT_NV12_TILE_CMP == pstAttr->ePixFormat)
                || (HI_DRV_PIX_FMT_NV21_TILE_CMP == pstAttr->ePixFormat))
            {
                pstWbcFrame->stBufAddr[0].u32PhyAddr_C =
                    pstWbcFrame->stBufAddr[0].u32PhyAddr_CHead + u32ImgHeight * 16 / 2;
            }
            else
            {
                pstWbcFrame->stBufAddr[0].u32PhyAddr_C =
                    pstWbcFrame->stBufAddr[0].u32PhyAddr_CHead + u32ImgHeight * 16;
            }

            break;
        }
        case HI_DRV_PIX_FMT_ARGB8888:
        case HI_DRV_PIX_FMT_ABGR8888:
        {
            pstWbcFrame->stBufAddr[0].u32PhyAddr_Y = u32PhyAddr;
            break;
        }
        default:
        {
            VPSS_FATAL("Unsupport PixFormat %d.\n", pstAttr->ePixFormat);
            return HI_FAILURE;
        }
    }

    VPSS_SAFE_MEMCPY(&pstWbcFrame->stBufAddr[1], &pstWbcFrame->stBufAddr[0],
                     sizeof(HI_DRV_VID_FRAME_ADDR_S));

    return HI_SUCCESS;
}

HI_S32 VPSS_WBC_Init(VPSS_WBC_S *pstWbc, VPSS_WBC_ATTR_S *pstAttr)
{
    LIST *pListHead = HI_NULL;
    HI_U32 u32Stride = 0;
    HI_U32 u32NodeBuffSize = 0;
    HI_U32 u32TotalBuffSize = 0;
    HI_U32 u32PhyAddr = 0;
    HI_U8 *pu8VirAddr = 0;
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 i = 0;
    HI_U32 u32NodeCount;
    HI_U32 u32TmpInstanceId;
    if (HI_NULL == pstWbc)
    {
        VPSS_ERROR("Vpss wbc Init error(null pointer).\n");
        return HI_FAILURE;
    }
    if (HI_TRUE == pstWbc->bInit)
    {
        (HI_VOID)VPSS_WBC_DeInit(pstWbc);
    }

    if ((VPSS_WBC_REF_MODE_INIT > pstAttr->enRefMode) || (VPSS_WBC_REF_MODE_BUTT <= pstAttr->enRefMode))
    {
        VPSS_ERROR("Vpss wbc Init error(RefMode = %d).\n", pstAttr->enRefMode);
        return HI_FAILURE;
    }

    if (pstWbc->stWbcAttr.enMode >= VPSS_WBC_MODE_BUTT)
    {
        VPSS_ERROR("Vpss wbc Init error(pstWbc->stWbcAttr.enMode = %d).\n", pstWbc->stWbcAttr.enMode);
        return HI_FAILURE;
    }

    if ((HI_DRV_PIXEL_BITWIDTH_8BIT != pstAttr->enBitWidth) && (HI_DRV_PIXEL_BITWIDTH_10BIT != pstAttr->enBitWidth))
    {
        VPSS_ERROR("Vpss wbc Init error(BitWidth = %d).\n", pstAttr->enBitWidth);
        return HI_FAILURE;
    }

    u32TmpInstanceId = pstWbc->u32InstanceId;
    memset(pstWbc, 0, sizeof(VPSS_WBC_S));
    pstWbc->u32InstanceId = u32TmpInstanceId;
    VPSS_SAFE_MEMCPY(&pstWbc->stWbcAttr, pstAttr, sizeof(VPSS_WBC_ATTR_S));

    s32Ret = VPSS_WBC_CalBufSize(&u32NodeBuffSize, &u32Stride, pstAttr);
    if (HI_FAILURE == s32Ret)
    {
        return HI_FAILURE;
    }

    u32TotalBuffSize = VPSS_WBC_GetTotalBufSize(pstAttr, u32NodeBuffSize + u32Stride);

#ifdef HI_VPSS_SMMU_SUPPORT
    if (pstAttr->bSecure)
    {
#ifdef HI_TEE_SUPPORT
        s32Ret = HI_DRV_SECSMMU_Alloc("VPSS_WbcBuf", u32TotalBuffSize, 0, &pstWbc->stTEEBuf);
#else
        if (VPSS_IS_TILE_FMT(pstAttr->ePixFormat))
        {
            s32Ret = HI_DRV_SMMU_AllocAndMap("VPSS_WbcBuf", u32TotalBuffSize, 0, &(pstWbc->stTEEBuf));
        }
        else
        {
            s32Ret = HI_DRV_SMMU_Alloc("VPSS_WbcBuf", u32TotalBuffSize, 0, &(pstWbc->stTEEBuf));
        }
#endif
        if (HI_FAILURE == s32Ret)
        {
            VPSS_FATAL("VPSS WBC Alloc memory failed.\n");
            return HI_FAILURE;
        }

        u32PhyAddr = pstWbc->stTEEBuf.u32StartSmmuAddr;
        pu8VirAddr = pstWbc->stTEEBuf.pu8StartVirAddr;
    }
    else
    {
        if (VPSS_IS_TILE_FMT(pstAttr->ePixFormat))
        {
#if defined(ALGBUF_MANAGE_MODE1)
            s32Ret = VPSS_AlgBuf_Malloc(&g_VpssAlgBuf, VPSS_ALG_WBC, "VPSS_WbcBuf", u32TotalBuffSize, 0, &(pstWbc->stMMUBuf));
#elif defined(ALGBUF_MANAGE_MODE2)
            VPSS_ALG_INSTANCEID_CHECK(pstWbc->u32InstanceId, VPSS_ALG_WBC);
            s32Ret = VPSS_AlgBuf_Get(&g_VpssAlgBuf[pstWbc->u32InstanceId], VPSS_ALG_WBC, "VPSS_WbcBuf", u32TotalBuffSize, 0, &(pstWbc->stMMUBuf));
#else
            s32Ret = HI_DRV_SMMU_AllocAndMap("VPSS_WbcBuf", u32TotalBuffSize, 0, &(pstWbc->stMMUBuf));
#endif
        }
        else
        {
#if defined(ALGBUF_MANAGE_MODE1)
            s32Ret = VPSS_AlgBuf_Malloc(&g_VpssAlgBuf, VPSS_ALG_WBC, "VPSS_WbcBuf", u32TotalBuffSize, 0, &(pstWbc->stMMUBuf));
#elif defined(ALGBUF_MANAGE_MODE2)
            VPSS_ALG_INSTANCEID_CHECK(pstWbc->u32InstanceId, VPSS_ALG_WBC);
            s32Ret = VPSS_AlgBuf_Get(&g_VpssAlgBuf[pstWbc->u32InstanceId], VPSS_ALG_WBC, "VPSS_WbcBuf", u32TotalBuffSize, 0, &(pstWbc->stMMUBuf));
#else
            s32Ret = HI_DRV_SMMU_Alloc("VPSS_WbcBuf", u32TotalBuffSize, 0, &(pstWbc->stMMUBuf));
#endif
        }

        if (HI_FAILURE == s32Ret)
        {
            VPSS_FATAL("VPSS WBC Alloc memory failed.\n");
            return HI_FAILURE;
        }

        u32PhyAddr = pstWbc->stMMUBuf.u32StartSmmuAddr;
        pu8VirAddr = pstWbc->stMMUBuf.pu8StartVirAddr;
    }
#else
    if (VPSS_IS_TILE_FMT(pstAttr->ePixFormat))
    {
        s32Ret = HI_DRV_MMZ_AllocAndMap("VPSS_WbcBuf", HI_NULL, u32TotalBuffSize, 0, &(pstWbc->stMMZBuf));
    }
    else
    {
        s32Ret = HI_DRV_MMZ_Alloc("VPSS_WbcBuf", HI_NULL, u32TotalBuffSize, 0, &(pstWbc->stMMZBuf));
    }

    if (HI_FAILURE == s32Ret)
    {
        VPSS_FATAL("VPSS WBC Alloc memory failed.\n");
        return HI_FAILURE;
    }

    u32PhyAddr = pstWbc->stMMZBuf.u32StartPhyAddr;
    pu8VirAddr = pstWbc->stMMZBuf.pu8StartVirAddr;
#endif

    u32NodeCount = (HI_U32)pstWbc->stWbcAttr.enMode;
    if (u32NodeCount >= VPSS_WBC_MODE_BUTT)
    {
        VPSS_ERROR("Vpss wbc Init error(invalid wbc mode:%d).\n", u32NodeCount);
        (HI_VOID)VPSS_WBC_DeInit(pstWbc);
        return HI_FAILURE;
    }

    pListHead = &(pstWbc->stDataList[0].node);
    INIT_LIST_HEAD(pListHead);
    pstWbc->pstFirstRef = pListHead;

    for (i = 1 ; i < u32NodeCount; i++)
    {
        list_add_tail(&(pstWbc->stDataList[i].node), pListHead);
    }

    switch (pstAttr->enMode)
    {
        case VPSS_WBC_MODE_NORMAL:
        {
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[0].stWbcFrame), pstAttr, u32PhyAddr, pu8VirAddr);
            u32PhyAddr = u32PhyAddr + u32NodeBuffSize;
            pu8VirAddr = pu8VirAddr + u32NodeBuffSize;
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[1].stWbcFrame), pstAttr, u32PhyAddr, pu8VirAddr);
            break;
        }
        case VPSS_WBC_MODE_3FIELD:
        {
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[0].stWbcFrame), pstAttr, u32PhyAddr, pu8VirAddr);
#ifdef VPSS_SUPPORT_TB_SAME_ADDR
            u32PhyAddr = u32PhyAddr + u32NodeBuffSize / 2;
            pu8VirAddr = pu8VirAddr + u32NodeBuffSize / 2;
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[1].stWbcFrame), pstAttr, u32PhyAddr + u32Stride, pu8VirAddr);
            u32PhyAddr = u32PhyAddr + u32NodeBuffSize / 2;
            pu8VirAddr = pu8VirAddr + u32NodeBuffSize / 2;
#else
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[1].stWbcFrame), pstAttr, u32PhyAddr + u32Stride, pu8VirAddr + u32Stride);
            u32PhyAddr = u32PhyAddr + u32NodeBuffSize;
            pu8VirAddr = pu8VirAddr + u32NodeBuffSize;
#endif
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[2].stWbcFrame), pstAttr, u32PhyAddr, pu8VirAddr);
            break;
        }
        case VPSS_WBC_MODE_4FIELD:
        {
#ifdef VPSS_SUPPORT_TB_SAME_ADDR
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[0].stWbcFrame), pstAttr, u32PhyAddr, pu8VirAddr);
            pstWbc->stDataList[0].stWbcFrame.enFieldMode = HI_DRV_FIELD_TOP;
            u32PhyAddr = u32PhyAddr + u32NodeBuffSize / 2;
            pu8VirAddr = pu8VirAddr + u32NodeBuffSize / 2;
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[1].stWbcFrame), pstAttr, u32PhyAddr, pu8VirAddr);
            pstWbc->stDataList[1].stWbcFrame.enFieldMode = HI_DRV_FIELD_BOTTOM;
            u32PhyAddr = u32PhyAddr + u32NodeBuffSize / 2;
            pu8VirAddr = pu8VirAddr + u32NodeBuffSize / 2;
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[2].stWbcFrame), pstAttr, u32PhyAddr, pu8VirAddr);
            pstWbc->stDataList[2].stWbcFrame.enFieldMode = HI_DRV_FIELD_TOP;
            u32PhyAddr = u32PhyAddr + u32NodeBuffSize / 2;
            pu8VirAddr = pu8VirAddr + u32NodeBuffSize / 2;
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[3].stWbcFrame), pstAttr, u32PhyAddr, pu8VirAddr);
            pstWbc->stDataList[3].stWbcFrame.enFieldMode = HI_DRV_FIELD_BOTTOM;
#else
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[0].stWbcFrame), pstAttr, u32PhyAddr, pu8VirAddr);
            pstWbc->stDataList[0].stWbcFrame.enFieldMode = HI_DRV_FIELD_TOP;
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[1].stWbcFrame), pstAttr, u32PhyAddr + u32Stride, pu8VirAddr + u32Stride);
            pstWbc->stDataList[1].stWbcFrame.enFieldMode = HI_DRV_FIELD_BOTTOM;
            u32PhyAddr = u32PhyAddr + u32NodeBuffSize;
            pu8VirAddr = pu8VirAddr + u32NodeBuffSize;
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[2].stWbcFrame), pstAttr, u32PhyAddr, pu8VirAddr);
            pstWbc->stDataList[2].stWbcFrame.enFieldMode = HI_DRV_FIELD_TOP;
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[3].stWbcFrame), pstAttr, u32PhyAddr + u32Stride, pu8VirAddr + u32Stride);
            pstWbc->stDataList[3].stWbcFrame.enFieldMode = HI_DRV_FIELD_BOTTOM;
#endif
            break;
        }
        case VPSS_WBC_MODE_5FIELD:
        {
#ifdef VPSS_SUPPORT_TB_SAME_ADDR
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[0].stWbcFrame), pstAttr, u32PhyAddr, pu8VirAddr);
            u32PhyAddr = u32PhyAddr + u32NodeBuffSize / 2;
            pu8VirAddr = pu8VirAddr + u32NodeBuffSize / 2;
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[1].stWbcFrame), pstAttr, u32PhyAddr, pu8VirAddr);
            u32PhyAddr = u32PhyAddr + u32NodeBuffSize / 2;
            pu8VirAddr = pu8VirAddr + u32NodeBuffSize / 2;

            VPSS_WBC_InitFrame(&(pstWbc->stDataList[2].stWbcFrame), pstAttr, u32PhyAddr, pu8VirAddr);
            u32PhyAddr = u32PhyAddr + u32NodeBuffSize / 2;
            pu8VirAddr = pu8VirAddr + u32NodeBuffSize / 2;
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[3].stWbcFrame), pstAttr, u32PhyAddr, pu8VirAddr);
            u32PhyAddr = u32PhyAddr + u32NodeBuffSize / 2;
            pu8VirAddr = pu8VirAddr + u32NodeBuffSize / 2;
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[4].stWbcFrame), pstAttr, u32PhyAddr, pu8VirAddr);
#else
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[0].stWbcFrame), pstAttr, u32PhyAddr, pu8VirAddr);
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[1].stWbcFrame), pstAttr, u32PhyAddr, pu8VirAddr);
            u32PhyAddr = u32PhyAddr + u32NodeBuffSize;
            pu8VirAddr = pu8VirAddr + u32NodeBuffSize;
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[2].stWbcFrame), pstAttr, u32PhyAddr, pu8VirAddr);
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[3].stWbcFrame), pstAttr, u32PhyAddr, pu8VirAddr);
            u32PhyAddr = u32PhyAddr + u32NodeBuffSize;
            pu8VirAddr = pu8VirAddr + u32NodeBuffSize;
            VPSS_WBC_InitFrame(&(pstWbc->stDataList[4].stWbcFrame), pstAttr, u32PhyAddr, pu8VirAddr);
#endif
            break;
        }
        default:
        {
            VPSS_ERROR("Vpss wbc Init error(WbcMode = %d).\n", pstWbc->stWbcAttr.enMode);
            return HI_FAILURE;
        }
    }

    pstWbc->bInit = HI_TRUE;
    return HI_SUCCESS;
}

HI_S32 VPSS_WBC_DeInit(VPSS_WBC_S *pstWbc)
{
    if (HI_NULL == pstWbc)
    {
        VPSS_ERROR("Vpss wbc DeInit error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstWbc->bInit)
    {
        VPSS_WARN("Vpss wbc DeInit error(not init).\n");
        return HI_SUCCESS;
    }

    if (0 != pstWbc->stTEEBuf.u32StartSmmuAddr)
    {
#ifdef HI_TEE_SUPPORT
        (HI_VOID)HI_DRV_SECSMMU_Release(&pstWbc->stTEEBuf);
#else
        if (HI_NULL != pstWbc->stTEEBuf.pu8StartVirAddr)
        {
            HI_DRV_SMMU_UnmapAndRelease(&pstWbc->stTEEBuf);
        }
        else
        {
            HI_DRV_SMMU_Release(&pstWbc->stTEEBuf);
        }
#endif
    }

#ifdef HI_VPSS_SMMU_SUPPORT
    if (0 != pstWbc->stMMUBuf.u32StartSmmuAddr)
    {
        if (HI_NULL != pstWbc->stMMUBuf.pu8StartVirAddr)
        {
#if defined(ALGBUF_MANAGE_MODE1)
            VPSS_AlgBuf_Free(&g_VpssAlgBuf, &pstWbc->stMMUBuf, VPSS_ALG_WBC);
#elif defined(ALGBUF_MANAGE_MODE2)
            VPSS_ALG_INSTANCEID_CHECK(pstWbc->u32InstanceId, VPSS_ALG_WBC);
            VPSS_AlgBuf_Rel(&g_VpssAlgBuf[pstWbc->u32InstanceId], &pstWbc->stMMUBuf, VPSS_ALG_WBC);
#else
            HI_DRV_SMMU_UnmapAndRelease(&pstWbc->stMMUBuf);
#endif
        }
        else
        {
#if defined(ALGBUF_MANAGE_MODE1)
            VPSS_AlgBuf_Free(&g_VpssAlgBuf, &pstWbc->stMMUBuf, VPSS_ALG_WBC);
#elif defined(ALGBUF_MANAGE_MODE2)
            VPSS_ALG_INSTANCEID_CHECK(pstWbc->u32InstanceId, VPSS_ALG_WBC);
            VPSS_AlgBuf_Rel(&g_VpssAlgBuf[pstWbc->u32InstanceId], &pstWbc->stMMUBuf, VPSS_ALG_WBC);
#else
            HI_DRV_SMMU_Release(&pstWbc->stMMUBuf);
#endif
        }

    }
#else
    if (0 != pstWbc->stMMZBuf.u32StartPhyAddr)
    {
        if (HI_NULL != pstWbc->stMMZBuf.pu8StartVirAddr)
        {
            HI_DRV_MMZ_UnmapAndRelease(& (pstWbc->stMMZBuf));
        }
        else
        {
            HI_DRV_MMZ_Release(& (pstWbc->stMMZBuf));
        }
    }
#endif

    memset(pstWbc, 0, sizeof(VPSS_WBC_S));

    return HI_SUCCESS;
}

HI_S32 VPSS_WBC_GetRefInfo(VPSS_WBC_S *pstWbc,
                           HI_DRV_VIDEO_FRAME_S **pstDataList)
{
    HI_U32 i;
    VPSS_WBC_DATA_S *pstRefNodeData = HI_NULL;
    LIST *pstRefNode = HI_NULL;
    VPSS_WBC_REF_MODE_E enRefMode;
    HI_U32 u32NodeCount;

    if ((HI_NULL == pstWbc) || (HI_NULL == pstDataList))
    {
        VPSS_ERROR("Vpss wbc GetRefInfo error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstWbc->bInit)
    {
        VPSS_ERROR("Vpss wbc GetRefInfo error(not init).\n");
        return HI_FAILURE;
    }

    enRefMode = pstWbc->stWbcAttr.enRefMode;
    u32NodeCount = (HI_U32)pstWbc->stWbcAttr.enMode - 1;
    pstRefNode = pstWbc->pstFirstRef->prev->prev;

    for (i = 0; i < u32NodeCount; i++)
    {
        pstRefNodeData = list_entry(pstRefNode, VPSS_WBC_DATA_S, node);
        pstDataList[u32NodeCount - i - 1] = &(pstRefNodeData->stWbcFrame);

        pstRefNode = pstRefNode->prev;
    }

    for (i = pstWbc->u32CompleteCount; i < u32NodeCount; i++)
    {
        if (VPSS_WBC_REF_MODE_NULL == enRefMode)
        {
            pstDataList[u32NodeCount - i - 1] = HI_NULL;
        }
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_WBC_GetWbcInfo(VPSS_WBC_S *pstWbc, HI_DRV_VIDEO_FRAME_S **pstData)
{
    VPSS_WBC_DATA_S *pstWbcNodeData = HI_NULL;
    LIST *pstWbcNode = HI_NULL;

    if ((HI_NULL == pstWbc) || (HI_NULL == pstData))
    {
        VPSS_ERROR("Vpss wbc GetWbcInfo error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstWbc->bInit)
    {
        VPSS_ERROR("Vpss wbc GetWbcInfo error(not init).\n");
        return HI_FAILURE;
    }

    pstWbcNode = pstWbc->pstFirstRef->prev;
    pstWbcNodeData = list_entry(pstWbcNode, VPSS_WBC_DATA_S, node);
    *pstData = &(pstWbcNodeData->stWbcFrame);

    return HI_SUCCESS;
}

HI_S32 VPSS_WBC_Complete(VPSS_WBC_S *pstWbc)
{
    if (HI_NULL == pstWbc)
    {
        VPSS_ERROR("Vpss wbc complete error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstWbc->bInit)
    {
        VPSS_ERROR("Vpss wbc complete error(not init).\n");
        return HI_FAILURE;
    }

    if (0 == (pstWbc->u32CompleteCount + 1))
    {
        pstWbc->u32CompleteCount = VPSS_WBC_MAX_NODE;
    }

    pstWbc->u32CompleteCount++;

    pstWbc->pstFirstRef = pstWbc->pstFirstRef->next;

    return HI_SUCCESS;
}

HI_S32 VPSS_WBC_Reset(VPSS_WBC_S *pstWbc)
{
    if (HI_NULL == pstWbc)
    {
        VPSS_WARN("Vpss wbc reset error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstWbc->bInit)
    {
        VPSS_WARN("Vpss wbc reset error(not init).\n");
        return HI_FAILURE;
    }

    pstWbc->u32CompleteCount = 0;

    return HI_SUCCESS;
}

HI_S32 VPSS_WBC_GetCurInfo(VPSS_WBC_S *pstWbc, HI_DRV_VIDEO_FRAME_S **ppstCurImage)
{
    VPSS_WBC_DATA_S *pstCurNodeData = HI_NULL;
    LIST *pstCurNode = HI_NULL;
    VPSS_WBC_REF_MODE_E enRefMode;

    if (HI_NULL == pstWbc)
    {
        VPSS_ERROR("Vpss wbc GetRefInfo error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstWbc->bInit)
    {
        VPSS_ERROR("Vpss wbc GetRefInfo error(not init).\n");
        return HI_FAILURE;
    }

    enRefMode = pstWbc->stWbcAttr.enRefMode;
    /**/
    if (pstWbc->stWbcAttr.enMode == VPSS_WBC_MODE_4FIELD)
    {
        pstCurNode = pstWbc->pstFirstRef->prev->prev->prev;

        pstCurNodeData = list_entry(pstCurNode, VPSS_WBC_DATA_S, node);

        *ppstCurImage = &(pstCurNodeData->stWbcFrame);
    }
    else if (pstWbc->stWbcAttr.enMode == VPSS_WBC_MODE_NORMAL)
    {
        pstCurNode = pstWbc->pstFirstRef->prev->prev;

        pstCurNodeData = list_entry(pstCurNode, VPSS_WBC_DATA_S, node);

        *ppstCurImage = &(pstCurNodeData->stWbcFrame);
    }
    else
    {
        VPSS_ERROR("wbc mode %d can't support get current image\n", pstWbc->stWbcAttr.enMode);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


