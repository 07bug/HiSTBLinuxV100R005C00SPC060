/******************************************************************************

 Copyright @ Hisilicon Technologies Co., Ltd. 1998-2015. All rights reserved.

 ******************************************************************************
  File Name     : vpss_hal_3798mv200.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2016/1/6
  Last Modified :
  Description   : vpss hal 3798mv200 source file
  Function List :
  History       :
  1.Date        : 2016/1/6
    Author      : sdk
    Modification: Created file

******************************************************************************/
#include "vpss_osal.h"
#include "vpss_ctrl.h"
#include "vpss_instance.h"
#include "hi_drv_proc.h"
#include "vpss_instance.h"
#include "vpss_reg_struct.h"
#include "vpss_cbb_common.h"
#include "vpss_cbb_hal.h"
#include "vpss_cbb_info.h"
#include "vpss_cbb_func.h"
#include "vpss_cbb_frame.h"
#include "vpss_cbb_alg.h"
#include "vpss_cbb_intf.h"
#include "vpss_cbb_reg.h"



/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

#define VPSS_OUT_TMPBUF

#define NUM_2_STRING(num) (#num)

#define VPSS_HAL_ENABLE_NODE(nodeid) do {\
        VPSS_DBG_INFO("Enable node:%s\n", (#nodeid));\
        bNodeList[(nodeid)] = HI_TRUE;\
    } while (0)

#define VPSS_HAL_DISABLE_NODE(nodeid) do {\
        VPSS_DBG_INFO("Disable node:%s\n", (#nodeid));\
        bNodeList[(nodeid)] = HI_FALSE;\
    } while (0)


#define VPSS_HAL_REG_BLOCK_SIZE 256     //print 256bytes per block
#define VPSS_HAL_REG_LINE_SIZE  16      //print 16bytes per line
#define VPSS_HAL_REG_UNIT_SIZE  4       //4bytes per reg

#define VPSS_HAL_IS_RWZB(rwzb) (((rwzb) > 0) && (PAT_M480I_NTSC_YD != (rwzb)) && (PAT_YDJC_0x67 != (rwzb)) && (PAT_YDJC_0x68 != (rwzb))&&(PAT_YDJC_0x69 != (rwzb)))
#define VPSS_HAL_IS_0X66(rwzb) ((rwzb) == PAT_M480I_NTSC_YD)
#define VPSS_HAL_IS_0X67(rwzb) ((rwzb) == PAT_YDJC_0x67)

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/
extern HI_VOID VPSS_HAL_Assert(HI_S32 s32NodeId, volatile S_VPSS_REGS_TYPE *vpss_reg, HI_BOOL bForcePrintInfo);
extern HI_VOID VPSS_DRV_Set_VPSS_DIECTRL_maonly(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 ma_only );
extern HI_VOID VPSS_DRV_Set_VPSS_DIELMA2_recmode(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 rec_mode_en);
extern HI_VOID VPSS_DRV_Set_VPSS_DIEHISMODE_hismot_ppreinfo(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 his_motion_en , HI_U32 ppre_info_en);
/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/
HI_S32 VPSS_HAL_Set_TNROutPutCur(CBB_REG_ADDR_S stRegAddr);
HI_S32 VPSS_HAL_NodeSplit(S_VPSS_REGS_TYPE *pstVirAddrBasePara,
                          VPSS_HAL_NODE_S *stNODE,
                          HI_U32 u32NodeCount,
                          HI_U32 u32FrameIdx);
HI_VOID VPSS_HAL_MCDINRBuffer_Free(SMMU_BUFFER_S *pstSBuf);

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

S_VPSS_REGS_TYPE g_stVirAddrBaseBackUp = {{{0}}};
SMMU_BUFFER_S g_VPSSMCDIBuf = {0};

PF_NODE_CFG_FUNC pfSetNodeInfo[VPSS_HAL_NODE_BUTT] =
{
    VPSS_HAL_Set_2DFrame_Node,
    VPSS_HAL_Set_2DFrame_Node, //virtual
    VPSS_HAL_Set_2DDei_Node,
    VPSS_HAL_Set_2DDei_Node, //virtual
    VPSS_HAL_Set_2DField_Node,
    VPSS_HAL_Set_2DField_Node, //virtual
    VPSS_HAL_Set_2DSDFirst_Node,
    VPSS_HAL_Set_2DSDSecond_Node,
    VPSS_HAL_Set_2DSDSecond_Node, //virtual

    VPSS_HAL_Set_CTS10_Node,
    VPSS_HAL_Set_CTS10_Node, //virtual

    VPSS_HAL_Set_2D_UHDFrame_Node, //4K zme
    VPSS_HAL_Set_2D_UHDFrame_Node, //4K zme

    VPSS_HAL_Set_3DFrameL_Node,
    VPSS_HAL_Set_3DFrameR_Node,

    VPSS_HAL_Set_HDR_Node, //VPSS_HAL_NODE_HDR_DETILE_NOALG
    VPSS_HAL_Set_LCHDR_Node,
    VPSS_HAL_SetNode_H265_Step1_Interlace,  //VPSS_HAL_NODE_2D_H265_STEP1_INTERLACE
    VPSS_HAL_SetNode_H265_Step2_Dei,//VPSS_HAL_NODE_2D_H265_STEP2_DEI

    VPSS_HAL_Set_2DField_Node,
    VPSS_HAL_Set_2DField_Node,

    VPSS_HAL_Set_2DDei_Last2Field_Node,
    VPSS_HAL_Set_2DDei_Last2Field_Node,

    VPSS_HAL_Set_RotaY_Node,
    VPSS_HAL_Set_RotaY_VIRTUAL_Node,//virtual
    VPSS_HAL_Set_RotaC_Node,
    VPSS_HAL_Set_RotaC_VIRTUAL_Node,//virtual
};

#ifdef VPSS_SUPPORT_PROC_V2
HI_U8 *g_pcHalNodeString[] =
{
    NUM_2_STRING(2D_FRAME),             //2D逐行
    NUM_2_STRING(2D_FRAME_VIRTUAL ),    //2D逐行虚拟端口), 转码使用
    NUM_2_STRING(2D_DEI),               //2D隔行),  hd
    NUM_2_STRING(2D_DEI_VIRTUAL),       //2D隔行),  hd虚拟端口), 转码使用
    NUM_2_STRING(2D_FIELD),             //2D逐行), 单场读入
    NUM_2_STRING(2D_FIELD_VIRTUAL),     //2D隔行), 单场读入虚拟端口), 转码使用
    NUM_2_STRING(2D_SD_FIRST),          //sd),  隔行),  tnr),  dei
    NUM_2_STRING(2D_SD_SECOND),         //sd),  隔行),  snr),  vhd0 funcs
    NUM_2_STRING(2D_SD_VIRTUAL),        //sd),  隔行虚拟端口), 转码使用
    NUM_2_STRING(2D_CTS10),             //只有2D时打开
    NUM_2_STRING(2D_CTS10_VIRTUAL ),    //CTS10), 虚拟端口
    NUM_2_STRING(2D_UHD),
    NUM_2_STRING(2D_UHD_VIRTUAL),
    NUM_2_STRING(3D_FRAME_L),           //3D左眼
    NUM_2_STRING(3D_FRAME_R),           //3D右眼
    NUM_2_STRING(HDR_DETILE_NOALG),
    NUM_2_STRING(HDR_LC),
    NUM_2_STRING(2D_H265_STEP1_INTERLACE),
    NUM_2_STRING(2D_H265_STEP2_DEI),
    NUM_2_STRING(2D_DEI_FRIST_3FIELD),
    NUM_2_STRING(2D_DEI_FRIST_3FIELD_VIRTUAL),
    NUM_2_STRING(2D_DEI_LAST_2FIELD),
    NUM_2_STRING(2D_DEI_LAST_2FIELD_VIRTUAL),

    NUM_2_STRING(ROTATION_Y),           //Y), C翻转
    NUM_2_STRING(ROTATION_Y_VIRTUAL),
    NUM_2_STRING(ROTATION_C),           //Y), C翻转
    NUM_2_STRING(ROTATION_C_VIRTUAL),
    NUM_2_STRING(MC_SPLIT_NODE1),
    NUM_2_STRING(MC_SPLIT_NODE2),
    NUM_2_STRING(MC_SPLIT_NODE3),
    NUM_2_STRING(MC_SPLIT_NODE4),
    NUM_2_STRING(MC_SPLIT_NODE5),

    NUM_2_STRING(MC_SPLIT_NODE6),
    NUM_2_STRING(MC_SPLIT_NODE7),
    NUM_2_STRING(MC_SPLIT_NODE8),
    NUM_2_STRING(MC_SPLIT_NODE9),

};
#endif


VPSS_HAL_CTX_S  stHalCtx[VPSS_IP_BUTT][VPSS_INSTANCE_MAX_NUMB] =
{
    {{0}}
};


/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/
HI_S32 VPSS_HAL_Init(VPSS_IP_E enIP)
{
    HI_U32 u32Idx = 0;
    HI_U32 u32IdxNew = 0;
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;

    VPSS_HAL_CHECK_IP_VAILD(enIP);

    for (u32Idx = 0; u32Idx < VPSS_INSTANCE_MAX_NUMB; u32Idx++)
    {
        pstHalCtx = &stHalCtx[enIP][u32Idx];

        if (pstHalCtx->bInit)
        {
            VPSS_WARN("VPSS IP%d, Already Init\n", enIP);
            continue;
        }

        pstHalCtx->bInit = HI_FALSE;
        pstHalCtx->bClockEn = HI_FALSE;
        pstHalCtx->u32LogicVersion = HAL_VERSION_3798MV200;
        pstHalCtx->u32BaseRegPhy   = VPSS0_BASE_ADDR;
        pstHalCtx->pu8BaseRegVir   = 0;

        /* 映射寄存器地址 */
        // pstHalCtx->pu32BaseRegVir = IO_ADDRESS(pstHalCtx->u32BaseRegPhy);

        pstHalCtx->pu8BaseRegVir
            = ioremap_nocache(pstHalCtx->u32BaseRegPhy, VPSS_REG_SIZE);

        if (HI_NULL == pstHalCtx->pu8BaseRegVir)
        {
            VPSS_FATAL("VPSS ioremap_nocache failed! idx:%d addr:%#x\n",
                       u32Idx, pstHalCtx->u32BaseRegPhy);

            for (u32IdxNew = 0; u32IdxNew < u32Idx; u32IdxNew++)
            {
                pstHalCtx = &stHalCtx[enIP][u32IdxNew];
                iounmap(pstHalCtx->pu8BaseRegVir);
                pstHalCtx->pu8BaseRegVir = HI_NULL;
                pstHalCtx->bInit = HI_FALSE;
            }
            return HI_FAILURE;
        }
        else
        {
            VPSS_DBG_INFO("VPSS regmap  phy:%#x-> vir:%#x\n", pstHalCtx->u32BaseRegPhy, (unsigned int)(long)pstHalCtx->pu8BaseRegVir);
        }
        pstHalCtx->bInit = HI_TRUE;
    }

    VPSS_HAL_SetClockEn(enIP, HI_FALSE);

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_DeInit(VPSS_IP_E enIP)
{
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
    HI_U32  u32Idx;

    VPSS_HAL_CHECK_IP_VAILD(enIP);

    VPSS_HAL_SetClockEn(enIP, HI_FALSE);

    VPSS_HAL_MCDINRBuffer_Free(&g_VPSSMCDIBuf);


    for (u32Idx = 0; u32Idx < VPSS_INSTANCE_MAX_NUMB; u32Idx++)
    {
        pstHalCtx = &stHalCtx[enIP][u32Idx];

        if (!pstHalCtx->bInit)
        {
            VPSS_WARN("VPSS IP%d, Already DeInit\n", enIP);
            continue;
        }

        HI_ASSERT(pstHalCtx->pu8BaseRegVir != 0);

        if (pstHalCtx->pu8BaseRegVir != 0)
        {
            iounmap(pstHalCtx->pu8BaseRegVir);
            pstHalCtx->pu8BaseRegVir = 0;
        }

        pstHalCtx->bInit = HI_FALSE;
    }
    return HI_SUCCESS;
}

HI_VOID VPSS_HAL_DumpReg_print(HI_ULONG ulBaseAddr, HI_ULONG ulStartAddr, HI_ULONG ulEndAddr, HI_BOOL bOnlyNoZero)
{
    HI_ULONG i;
    HI_U32   u32RegValue;

    for (i = ulStartAddr; i < ulEndAddr; i += VPSS_HAL_REG_UNIT_SIZE)
    {
        if (i % (VPSS_HAL_REG_BLOCK_SIZE) == 0)
        {
            HI_PRINT("\n-------------------- 0x%.4x --------------------", (HI_U32)i);
        }

        if (i % VPSS_HAL_REG_LINE_SIZE == 0)
        {
            HI_PRINT("\n0x%.4x: ", (HI_U32)i);
        }

        u32RegValue = *((HI_U32 *)(ulBaseAddr + i));

        if ((0x0 == u32RegValue) && (bOnlyNoZero))
        {
            HI_PRINT("         ");
        }
        else
        {
            HI_PRINT("%.8x ", u32RegValue);
        }
    }

    return;
}

HI_S32 VPSS_HAL_DumpReg(VPSS_IP_E enIP, HI_U32  *pu32AppVir)
{
    HI_ULONG ulRegBase;
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
    HI_BOOL  bDoNotPrintZero = HI_FALSE;

    VPSS_HAL_CHECK_IP_VAILD(enIP);

    pstHalCtx = &stHalCtx[enIP][0];

    HI_PRINT("\n####################################");
    if (HI_NULL == pu32AppVir)
    {
        ulRegBase = (HI_ULONG)(pstHalCtx->pu8BaseRegVir);
        HI_PRINT("\nDump Reg value PhyAddr %08x VirAddr %8lx\n",
                 pstHalCtx->u32BaseRegPhy, ulRegBase);
    }
    else
    {
        ulRegBase = (HI_ULONG)pu32AppVir;
        HI_PRINT("\nDump Config in DDR, VirAddr %8lx\n", ulRegBase);
    }
    HI_PRINT("\n####################################");

    VPSS_HAL_DumpReg_print(ulRegBase, 0x0,    0x50,  bDoNotPrintZero);
    VPSS_HAL_DumpReg_print(ulRegBase, 0x2F8,  0x700,  bDoNotPrintZero);
    VPSS_HAL_DumpReg_print(ulRegBase, 0x1000, 0x11D0, bDoNotPrintZero);
    VPSS_HAL_DumpReg_print(ulRegBase, 0x2000, 0x2600, bDoNotPrintZero);
    VPSS_HAL_DumpReg_print(ulRegBase, 0x3800, 0x3980, bDoNotPrintZero);
    VPSS_HAL_DumpReg_print(ulRegBase, 0x4000, 0x4100, bDoNotPrintZero);
    VPSS_HAL_DumpReg_print(ulRegBase, 0x5000, 0x5460, bDoNotPrintZero);
    VPSS_HAL_DumpReg_print(ulRegBase, 0x5800, 0x59C0, bDoNotPrintZero);

    VPSS_HAL_DumpReg_print(ulRegBase, 0xf000, 0xf400, bDoNotPrintZero);

    return HI_SUCCESS;
}


#ifdef VPSS_SUPPORT_PROC_V2
HI_VOID VPSS_Hal_PrintHalInfo(struct seq_file *p, S_VPSS_REGS_TYPE *pstNodeReg)
{
    if (HI_NULL == pstNodeReg)
    {
        return;
    }
#if 1
    PROC_PRINT(p,
               VPSS_PROC_LEVEL5"next2  readmode:%u topfirst:%u tunl_en:%u security:%u tile :%u dcmp:%u hdr_in:%u"
               VPSS_PROC_LEVEL5"next2  enable :%u mute :%u    smmu:%u bitw:%u format:%u yaddr:%08x ystride:%u yheadaddr:%08x headstride:%u"
               VPSS_PROC_LEVEL5"next2  w*h:%u*%u offsetH:%u offsetV:%u "
               VPSS_PROC_LEVEL5"next1  enable :%u mute :%u(%u) smmu:%u bitw:%u format:%u yaddr:%08x ystride:%u"
               VPSS_PROC_LEVEL5"cur    enable :%u mute :%u(%u) smmu:%u bitw:%u format:%u yaddr:%08x ystride:%u"
               VPSS_PROC_LEVEL5"last   enable :%u mute :%u(%u) smmu:%u bitw:%u format:%u yaddr:%08x ystride:%u"
               VPSS_PROC_LEVEL5"rfr    enable :%u mute :%u(%u) smmu:%u bitw:%u dither:%u(%u) yaddr:%08x ystride:%u"
               VPSS_PROC_LEVEL5"rfr    w*h:%u*%u"

               VPSS_PROC_LEVEL5"vhd0   enable :%u mute :%u    smmu:%u bitw:%u yaddr:%08x ystride:%u"
               VPSS_PROC_LEVEL5"vhd0   w*h:%u*%u offsetH:%u offsetV:%u "
               VPSS_PROC_LEVEL5"       4pc    :%u  rota:%u flip:%u mirror:%u cts:%u tunl:%u vfir:%u uvIvt:%u dither:%u"
               VPSS_PROC_LEVEL5"       crop_en:%u xywh: %u,%u,%u,%u"
               VPSS_PROC_LEVEL5"       zme_en :%u   wh: %u,%u"
               VPSS_PROC_LEVEL5"       lbx_en :%u xywh: %u,%u,%u,%u"
               VPSS_PROC_LEVEL5"alg    tnr:%u mcnr:%u (mc)nr:%u snr:%u (s)nr:%u dei:%u mcdi:%u rgme:%u ifmd:%u igbm:%u db:%u dm:%u blkdet:%u hdr_en:%u"
               VPSS_PROC_LEVEL5"       di_rfr:%u   rprjh:%u    wprjh:%u      rprjv:%u     wprjv:%u"
               VPSS_PROC_LEVEL5"       p1rgmv:%u   p2rgmv:%u   cfrgmv:%u     p2mv:%u      p3mv:%u   cfmv:%u   p3mt:%u    p2mt:%u"
               VPSS_PROC_LEVEL5"       di_rst_cnt:%u          di_wst_cnt:%u               di_rst:%u          di_wst:%u"
               VPSS_PROC_LEVEL5"       nr_wmad:%u  nr_rmad:%u maonly:%u mconly:%u"

               VPSS_PROC_LEVEL5"       p1rgmv:%08x  "
               VPSS_PROC_LEVEL5"       p2rgmv:%08x  "
               VPSS_PROC_LEVEL5"       cfgrgmv:%08x  "

               VPSS_PROC_LEVEL5"       chroma_mf_max:%u  "
               VPSS_PROC_LEVEL5"       luma_mf_max:%u  "
               VPSS_PROC_LEVEL5"       motion_adjust_gain:%u  "
               VPSS_PROC_LEVEL5"       dbm_out_mode:%u  "
               ,

               /*next2, cf*/
               pstNodeReg->VPSS_CF_CTRL.bits.cf_lm_rmode,
               !pstNodeReg->VPSS_CTRL.bits.bfield_first,
               pstNodeReg->VPSS_CF_RTUNL_CTRL.bits.cf_rtunl_en,
               pstNodeReg->VPSS_CHN_CFG_CTRL.bits.prot,
               pstNodeReg->VPSS_CF_CTRL.bits.cf_type,
               pstNodeReg->VPSS_CF_CTRL.bits.cf_dcmp_mode,
               pstNodeReg->VPSS_CTRL.bits.hdr_in,


               pstNodeReg->VPSS_CF_CTRL.bits.cf_en,
               pstNodeReg->VPSS_CF_CTRL.bits.cf_mute_en,
               !pstNodeReg->VPSS_CF_CTRL.bits.cf_d_bypass,
               pstNodeReg->VPSS_CF_CTRL.bits.cf_bitw,
               pstNodeReg->VPSS_CF_CTRL.bits.cf_format,
               pstNodeReg->VPSS_CFY_ADDR_LOW.u32,
               pstNodeReg->VPSS_CF_STRIDE.bits.cfy_stride,
               pstNodeReg->VPSS_CFY_HEAD_TOP_ADDR_LOW.u32,
               pstNodeReg->VPSS_CF_HEAD_STRIDE.bits.cfy_head_stride,

               pstNodeReg->VPSS_CF_SIZE.bits.cf_width  + 1,
               pstNodeReg->VPSS_CF_SIZE.bits.cf_height + 1,
               pstNodeReg->VPSS_CF_OFFSET.bits.cf_hor_offset,
               pstNodeReg->VPSS_CF_OFFSET.bits.cf_ver_offset,


               /*next1,p1*/
               pstNodeReg->VPSS_P1_CTRL.bits.p1_en,
               pstNodeReg->VPSS_P1_CTRL.bits.p1_mute_en,
               pstNodeReg->VPSS_P1_CTRL.bits.p1_mute_mode,
               !pstNodeReg->VPSS_P1_CTRL.bits.p1_d_bypass,
               pstNodeReg->VPSS_P1_CTRL.bits.p1_bitw,
               pstNodeReg->VPSS_P1_CTRL.bits.p1_format,
               pstNodeReg->VPSS_P1Y_ADDR_LOW.u32,
               pstNodeReg->VPSS_P1_STRIDE.bits.p1y_stride,

               /*cur,p2*/
               pstNodeReg->VPSS_P2_CTRL.bits.p2_en,
               pstNodeReg->VPSS_P2_CTRL.bits.p2_mute_en,
               pstNodeReg->VPSS_P2_CTRL.bits.p2_mute_mode,
               !pstNodeReg->VPSS_P2_CTRL.bits.p2_d_bypass,
               pstNodeReg->VPSS_P2_CTRL.bits.p2_bitw,
               pstNodeReg->VPSS_P2_CTRL.bits.p2_format,
               pstNodeReg->VPSS_P2Y_ADDR_LOW.u32,
               pstNodeReg->VPSS_P2_STRIDE.bits.p2y_stride,

               /*last,p3*/
               pstNodeReg->VPSS_P3_CTRL.bits.p3_en,
               pstNodeReg->VPSS_P3_CTRL.bits.p3_mute_en,
               pstNodeReg->VPSS_P3_CTRL.bits.p3_mute_mode,
               !pstNodeReg->VPSS_P3_CTRL.bits.p3_d_bypass,
               pstNodeReg->VPSS_P3_CTRL.bits.p3_bitw,
               pstNodeReg->VPSS_P3_CTRL.bits.p3_format,
               pstNodeReg->VPSS_P3Y_ADDR_LOW.u32,
               pstNodeReg->VPSS_P3_STRIDE.bits.p3y_stride,

               /*rfr*/
               pstNodeReg->VPSS_NR_RFR_CTRL.bits.nr_rfr_en,
               pstNodeReg->VPSS_NR_RFR_CTRL.bits.nr_rfr_mute_en,
               pstNodeReg->VPSS_NR_RFR_CTRL.bits.nr_rfr_mute_mode,
               !pstNodeReg->VPSS_NR_RFR_CTRL.bits.nr_rfr_d_bypass,
               pstNodeReg->VPSS_NR_RFR_CTRL.bits.nr_rfr_bitw,
               pstNodeReg->VPSS_NR_RFR_CTRL.bits.nr_rfr_dither_en,
               pstNodeReg->VPSS_NR_RFR_CTRL.bits.nr_rfr_dither_mode,
               pstNodeReg->VPSS_NR_RFRY_ADDR_LOW.u32,
               pstNodeReg->VPSS_NR_RFR_STRIDE.bits.nr_rfry_stride,
               pstNodeReg->VPSS_NR_RFR_SIZE.bits.nr_rfr_width + 1,
               pstNodeReg->VPSS_NR_RFR_SIZE.bits.nr_rfr_height + 1,

               /*vhd0*/
               pstNodeReg->VPSS_OUT0_CTRL.bits.out0_en,
               pstNodeReg->VPSS_OUT0_CTRL.bits.out0_mute_en,
               !pstNodeReg->VPSS_OUT0_CTRL.bits.out0_d_bypass,
               pstNodeReg->VPSS_OUT0_CTRL.bits.out0_bitw,
               pstNodeReg->VPSS_OUT0Y_ADDR_LOW.u32,
               pstNodeReg->VPSS_OUT0_STRIDE.bits.out0y_stride,

               pstNodeReg->VPSS_OUT0_SIZE.bits.out0_width + 1,
               pstNodeReg->VPSS_OUT0_SIZE.bits.out0_height + 1,
               pstNodeReg->VPSS_OUT0_OFFSET.bits.out0_hor_offset,
               pstNodeReg->VPSS_OUT0_OFFSET.bits.out0_ver_offset,

               pstNodeReg->VPSS_CTRL.bits.four_pix_en,
               pstNodeReg->VPSS_CHN_CFG_CTRL.bits.rotate_en,
               pstNodeReg->VPSS_OUT0_CTRL.bits.out0_flip,
               pstNodeReg->VPSS_OUT0_CTRL.bits.out0_mirror,
               pstNodeReg->VPSS_OUT0_CTRL.bits.out0_cts_en,
               pstNodeReg->VPSS_OUT0_WTUNL_CTRL.bits.out0_wtunl_en,
               pstNodeReg->VPSS_CTRL3.bits.vhd0_pre_vfir_en,
               pstNodeReg->VPSS_OUT0_CTRL.bits.out0_uv_invert,
               pstNodeReg->VPSS_OUT0_CTRL.bits.out0_dither_mode,

               pstNodeReg->VPSS_CTRL3.bits.vhd0_crop_en,
               pstNodeReg->VPSS_VHD0CROP_POS.bits.vhd0_crop_x,
               pstNodeReg->VPSS_VHD0CROP_POS.bits.vhd0_crop_y,
               pstNodeReg->VPSS_VHD0CROP_SIZE.bits.vhd0_crop_width + 1,
               pstNodeReg->VPSS_VHD0CROP_SIZE.bits.vhd0_crop_height + 1,
               pstNodeReg->VPSS_CTRL3.bits.zme_vhd0_en,
               pstNodeReg->VPSS_VHD0_ZMEORESO.bits.vhd0_zme_ow + 1,
               pstNodeReg->VPSS_VHD0_ZMEORESO.bits.vhd0_zme_oh + 1,
               pstNodeReg->VPSS_CTRL3.bits.vhd0_lba_en,
               pstNodeReg->VPSS_VHD0LBA_VFPOS.bits.vhd0_lba_xfpos,
               pstNodeReg->VPSS_VHD0LBA_VFPOS.bits.vhd0_lba_yfpos,
               pstNodeReg->VPSS_VHD0LBA_DSIZE.bits.vhd0_lba_width  + 1,
               pstNodeReg->VPSS_VHD0LBA_DSIZE.bits.vhd0_lba_height + 1,

               /*ALG*/
               pstNodeReg->VPSS_CTRL.bits.tnr_en,
               pstNodeReg->VPSS_CTRL.bits.mcnr_en,
               pstNodeReg->VPSS_TNR_CONTRL.bits.nren,
               pstNodeReg->VPSS_CTRL.bits.snr_en,
               pstNodeReg->VPSS_DB_CTRL.bits.nr_en,
               pstNodeReg->VPSS_CTRL.bits.dei_en,
               pstNodeReg->VPSS_CTRL.bits.mcdi_en,

               pstNodeReg->VPSS_CTRL.bits.rgme_en,
               pstNodeReg->VPSS_CTRL.bits.ifmd_en,
               pstNodeReg->VPSS_CTRL.bits.igbm_en,
               pstNodeReg->VPSS_DB_CTRL.bits.db_en,
               pstNodeReg->VPSS_DB_CTRL.bits.dm_en,
               pstNodeReg->VPSS_CTRL.bits.blk_det_en,
               pstNodeReg->VPSS_LCHDR_CTRL.bits.lchdr_en,

               pstNodeReg->VPSS_DI_RFR_CTRL.bits.di_rfr_en,
               pstNodeReg->VPSS_RPRJH_CTRL.bits.rprjh_en,
               pstNodeReg->VPSS_WPRJH_CTRL.bits.wprjh_en,
               pstNodeReg->VPSS_RPRJV_CTRL.bits.rprjv_en,
               pstNodeReg->VPSS_WPRJV_CTRL.bits.wprjv_en,

               pstNodeReg->VPSS_P1RGMV_CTRL.bits.p1rgmv_en,
               pstNodeReg->VPSS_P2RGMV_CTRL.bits.p2rgmv_en,
               pstNodeReg->VPSS_CFRGMV_CTRL.bits.cfrgmv_en,
               pstNodeReg->VPSS_P2MV_CTRL.bits.p2mv_en,
               pstNodeReg->VPSS_P3MV_CTRL.bits.p3mv_en,
               pstNodeReg->VPSS_CFMV_CTRL.bits.cfmv_en,
               pstNodeReg->VPSS_P3MT_CTRL.bits.p3mt_en,
               pstNodeReg->VPSS_P2MT_CTRL.bits.p2mt_en,

               pstNodeReg->VPSS_DI_RST_CNT_CTRL.bits.di_rst_cnt_en,
               pstNodeReg->VPSS_DI_WST_CNT_CTRL.bits.di_wst_cnt_en,
               pstNodeReg->VPSS_DI_RST_CTRL.bits.di_rst_en,
               pstNodeReg->VPSS_DI_WST_CTRL.bits.di_wst_en,

               pstNodeReg->VPSS_NR_WMAD_CTRL.bits.nr_wmad_en,
               pstNodeReg->VPSS_NR_RMAD_CTRL.bits.nr_rmad_en,

               pstNodeReg->VPSS_DIECTRL.bits.ma_only,
               pstNodeReg->VPSS_DIECTRL.bits.mc_only,

               pstNodeReg->VPSS_P1RGMV_ADDR_LOW.u32,
               pstNodeReg->VPSS_P2RGMV_ADDR_LOW.u32,
               pstNodeReg->VPSS_CFRGMV_ADDR_LOW.u32,


               pstNodeReg->VPSS_DIELMA2.bits.chroma_mf_max,
               pstNodeReg->VPSS_DIELMA2.bits.luma_mf_max,
               pstNodeReg->VPSS_DIEMTNADJ.bits.motion_adjust_gain,
               pstNodeReg->VPSS_DB_CTRL.bits.dbm_out_mode
              );
#endif
}

HI_S32 VPSS_HAL_GetNodeAddr(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstVpssHalInfo, HI_U32 u32NodeId, HI_U8 **pstRegAddr, HI_CHAR **ppNodeName)
{
    HI_U32 u32Idx = 0;

    if (u32NodeId >= VPSS_HAL_NODE_BUTT)
    {
        return HI_FAILURE;
    }

    for (u32Idx = 0; u32Idx < VPSS_HAL_NODE_BUTT; u32Idx++)
    {
        if (pstVpssHalInfo->stNodeList[u32Idx].u32NodeId == u32NodeId)
        {
            *pstRegAddr = pstVpssHalInfo->stNodeList[u32Idx].pu8AppVir;
            *ppNodeName = g_pcHalNodeString[u32NodeId];
            return HI_SUCCESS;
        }
    }

    return HI_FAILURE;
}
#endif
HI_S32 VPSS_HAL_H265RefListDeInit(VPSS_HAL_RefList_S *pstRefList)
{
    HI_S32 s32Idx;
    HI_U32 u32BaseAddr = 0;
#ifdef HI_VPSS_SMMU_SUPPORT
#ifdef HI_TEE_SUPPORT
    HI_S32 s32Ret = HI_SUCCESS;
#endif
#endif

    if (pstRefList->bRefListValid)
    {
#ifdef HI_VPSS_SMMU_SUPPORT
#ifdef HI_TEE_SUPPORT
        if (0 != pstRefList->stRefListBuf_tee.u32Size)
        {
            u32BaseAddr = pstRefList->stRefListBuf_tee.u32StartSmmuAddr;
            s32Ret = HI_DRV_SECSMMU_Release(&(pstRefList->stRefListBuf_tee));
            if (s32Ret != HI_SUCCESS)
            {
                VPSS_FATAL("Free VPSS_H265RefBuf_TEE Failed\n");
                return HI_FAILURE;
            }
            memset(&pstRefList->stRefListBuf_tee, 0, sizeof(pstRefList->stRefListBuf_tee));
        }
#endif
        if (0 != pstRefList->stRefListBuf_mmu.u32Size)
        {
            u32BaseAddr = pstRefList->stRefListBuf_mmu.u32StartSmmuAddr;
            HI_DRV_SMMU_Release(&(pstRefList->stRefListBuf_mmu));
            memset(&pstRefList->stRefListBuf_mmu, 0, sizeof(pstRefList->stRefListBuf_mmu));
        }
#else
        u32BaseAddr = pstRefList->stRefListBuf_mmz.u32StartPhyAddr;
        HI_DRV_MMZ_Release(&(pstRefList->stRefListBuf_mmz));
        memset(&pstRefList->stRefListBuf_mmz, 0, sizeof(pstRefList->stRefListBuf_mmz));
#endif

        VPSS_DBG_INFO("VPSS_HAL_H265RefListDeInit free %x\n", u32BaseAddr);

        for (s32Idx = 0; s32Idx < DEF_VPSS_HAL_REF_LIST_NUM; s32Idx++)
        {
            memset(&(pstRefList->stRefListAddr[s32Idx]), 0x0, sizeof(pstRefList->stRefListAddr[s32Idx]));
            pstRefList->abRefNodeValid[s32Idx] = HI_FALSE;
        }
    }

    pstRefList->bRefListValid = HI_FALSE;
    pstRefList->u32RefListHead = 0;

    return HI_SUCCESS;
}


HI_S32 VPSS_HAL_H265RefListInit(VPSS_HAL_RefList_S *pstRefList, HI_S32 s32Width, HI_S32 s32Height, HI_DRV_PIX_FORMAT_E
                                enFormat, HI_BOOL bSecure)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32StartAddr;
    HI_U32 u32YSize;
    HI_U32 u32FstFrameOffset;
    HI_U32 u32FieldOffset;
    HI_U32 u32FieldIdx;

    if (pstRefList->bRefListValid)
    {
        VPSS_DBG_INFO("VPSS_HAL_H265RefListInit has been called!\n");

        VPSS_HAL_H265RefListDeInit(pstRefList);
        pstRefList->bRefListValid = HI_FALSE;
    }

    if ((HI_DRV_PIX_FMT_NV12 != enFormat)
        && (HI_DRV_PIX_FMT_NV21 != enFormat)
        && (HI_DRV_PIX_FMT_NV12_CMP != enFormat)
        && (HI_DRV_PIX_FMT_NV21_CMP != enFormat)
        && (HI_DRV_PIX_FMT_NV12_TILE_CMP != enFormat)
        && (HI_DRV_PIX_FMT_NV21_TILE_CMP != enFormat))
    {
        VPSS_ERROR("Unsupport pixel format:%d\n", enFormat);
        return HI_FAILURE;
    }

#ifdef HI_VPSS_SMMU_SUPPORT
    if (bSecure)
    {
#ifdef HI_TEE_SUPPORT
        s32Ret = HI_DRV_SECSMMU_Alloc("VPSS_H265RefBuf_TEE",
                                      s32Width * s32Height * 3 / 2 * DEF_VPSS_HAL_REF_LIST_NUM,
                                      0,
                                      &(pstRefList->stRefListBuf_tee));
        u32StartAddr = pstRefList->stRefListBuf_tee.u32StartSmmuAddr;
#else
        s32Ret = HI_DRV_SMMU_Alloc( "VPSS_H265RefBuf_MMU",
                                    s32Width * s32Height * 3 / 2 * DEF_VPSS_HAL_REF_LIST_NUM,
                                    0,
                                    &(pstRefList->stRefListBuf_mmu));
        u32StartAddr = pstRefList->stRefListBuf_mmu.u32StartSmmuAddr;
#endif
    }
    else
    {
        s32Ret = HI_DRV_SMMU_Alloc("VPSS_H265RefBuf_MMU",
                                   s32Width * s32Height * 3 / 2 * DEF_VPSS_HAL_REF_LIST_NUM,
                                   0,
                                   &(pstRefList->stRefListBuf_mmu));
        u32StartAddr = pstRefList->stRefListBuf_mmu.u32StartSmmuAddr;
    }

    if (s32Ret != HI_SUCCESS)
    {
        VPSS_FATAL("Alloc VPSS_H265RefBuf_MMU Failed\n");
        return HI_FAILURE;
    }

#else
    s32Ret = HI_DRV_MMZ_Alloc("VPSS_H265RefBuf_MMZ",
                              "VPSS",
                              s32Width * s32Height * 3 / 2 * DEF_VPSS_HAL_REF_LIST_NUM,
                              0,
                              &(pstRefList->stRefListBuf_mmz));
    if (s32Ret != HI_SUCCESS)
    {
        VPSS_FATAL("Alloc VPSS_H265RefBuf_MMZ Failed\n");
        return HI_FAILURE;
    }
    u32StartAddr = pstRefList->stRefListBuf_mmz.u32StartPhyAddr;
#endif

    VPSS_DBG_INFO("VPSS_HAL_H265RefListInit malloc W H adr %d %d %x\n", s32Width, s32Height, u32StartAddr);

    for (u32FieldIdx = 0; u32FieldIdx < DEF_VPSS_HAL_REF_LIST_NUM; u32FieldIdx++)
    {
        pstRefList->abRefNodeValid[u32FieldIdx] = HI_FALSE;
    }

    u32YSize = s32Width * s32Height;
    u32FieldOffset = s32Width * s32Height * 3 / 2;
    pstRefList->stRefListAddr[0].u32PhyAddr_Y = u32StartAddr;
    pstRefList->stRefListAddr[0].u32PhyAddr_C = u32StartAddr + u32YSize;
    pstRefList->stRefListAddr[0].u32Stride_Y = s32Width;
    pstRefList->stRefListAddr[0].u32Stride_C = s32Width;

    pstRefList->stRefListAddr[1].u32PhyAddr_Y = u32StartAddr + u32FieldOffset;
    pstRefList->stRefListAddr[1].u32PhyAddr_C = u32StartAddr + u32FieldOffset + u32YSize;
    pstRefList->stRefListAddr[1].u32Stride_Y = s32Width;
    pstRefList->stRefListAddr[1].u32Stride_C = s32Width;

    u32FstFrameOffset = u32FieldOffset * 2;

    pstRefList->stRefListAddr[2].u32PhyAddr_Y = u32StartAddr + u32FstFrameOffset;
    pstRefList->stRefListAddr[2].u32PhyAddr_C = u32StartAddr + u32FstFrameOffset + u32YSize;
    pstRefList->stRefListAddr[2].u32Stride_Y = s32Width;
    pstRefList->stRefListAddr[2].u32Stride_C = s32Width;

    pstRefList->stRefListAddr[3].u32PhyAddr_Y = u32StartAddr + u32FstFrameOffset + u32FieldOffset;
    pstRefList->stRefListAddr[3].u32PhyAddr_C = u32StartAddr + u32FstFrameOffset + u32FieldOffset + u32YSize;
    pstRefList->stRefListAddr[3].u32Stride_Y = s32Width;
    pstRefList->stRefListAddr[3].u32Stride_C = s32Width;

    pstRefList->bRefListValid = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_SetMacCfg(VPSS_IP_E enIP)
{
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
    CBB_OUTSTANDING_S   stOutStd;
    CBB_REG_ADDR_S      stRegAddr;

    VPSS_HAL_CHECK_IP_VAILD(enIP);

    VPSS_MEM_CLEAR(stRegAddr);
    pstHalCtx = &stHalCtx[enIP][0];
    VPSS_HAL_CHECK_INIT(pstHalCtx->bInit);

    stRegAddr.pu8BaseVirAddr = pstHalCtx->pu8BaseRegVir;
    stRegAddr.u32BasePhyAddr = pstHalCtx->u32BaseRegPhy;

    stOutStd.u32ROutStd = 0xF;
    stOutStd.u32WOutStd = 0x7;
    stOutStd.u32Arb_mode = 0x1;
    stOutStd.u32Mid_enable = 0x1;
    stOutStd.enSplitMode = VPSS_SPLITE_MODE_256;

    VPSS_CBB_BASE_Operating(stRegAddr, CBB_BASEOPT_CONFIG_AXI, &stOutStd, HI_NULL);

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_SetClockEn(VPSS_IP_E enIP, HI_BOOL bClockEn)
{
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;

    VPSS_HAL_CHECK_IP_VAILD(enIP);

    pstHalCtx = &stHalCtx[enIP][0];
    VPSS_HAL_CHECK_INIT(pstHalCtx->bInit);

    if (pstHalCtx->bClockEn == bClockEn)
    {
        return HI_SUCCESS;
    }

    if (bClockEn)
    {
        VPSS_DRV_SetClockEn(HI_TRUE);
        VPSS_HAL_SetMacCfg(enIP);
        VPSS_DRV_SetTimeOut((S_VPSS_REGS_TYPE *)pstHalCtx->pu8BaseRegVir, DEF_LOGIC_TIMEOUT);
        VPSS_DRV_SetIntMask((S_VPSS_REGS_TYPE *)pstHalCtx->pu8BaseRegVir, 0x7e);
        VPSS_DRV_ClrInt((S_VPSS_REGS_TYPE *)pstHalCtx->pu8BaseRegVir, 0x7e);

        //low power
        VPSS_Sys_SetCkGtEn((S_VPSS_REGS_TYPE *)pstHalCtx->pu8BaseRegVir, 0, 0x1);
        VPSS_Sys_SetHardCkGtEn((S_VPSS_REGS_TYPE *)pstHalCtx->pu8BaseRegVir, 0, 0x1, 0x0);
    }
    else
    {
        VPSS_DRV_SetClockEn(HI_FALSE);
    }

    pstHalCtx->bClockEn = bClockEn;

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_CfgAXI(VPSS_IP_E enIP)
{
    /* cfg axi in VPSS_HAL_SetMacCfg  */

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_GetSystemTickCounter(VPSS_IP_E enIP, HI_U32 *ptickcnt, HI_U32 *pSystemClock)
{
    CBB_REG_ADDR_S  stRegAddr = {0};
    HI_U32          u32TickCnt = 0;
    HI_U32          u32SystemClock = 0;
    VPSS_HAL_CTX_S  *pstHalCtx;
    VPSS_MEM_CLEAR(stRegAddr);

    VPSS_CHECK_NULL(ptickcnt);
    VPSS_CHECK_NULL(pSystemClock);

    pstHalCtx = &stHalCtx[enIP][0];
    VPSS_HAL_CHECK_INIT(pstHalCtx->bInit);

    stRegAddr.pu8BaseVirAddr = pstHalCtx->pu8BaseRegVir;
    stRegAddr.u32BasePhyAddr = pstHalCtx->u32BaseRegPhy;


    VPSS_CBB_BASE_Operating(stRegAddr, CBB_BASEOPT_GET_TICK_STAT, (HI_VOID *)&u32TickCnt, (HI_VOID *)&u32SystemClock);

    *ptickcnt = u32TickCnt;
    *pSystemClock = u32SystemClock;
    return HI_SUCCESS;
}

HI_BOOL VPSS_HAL_NeedStartVirtual(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo)
{
    HI_U32 u32PortId;
    VPSS_HAL_PORT_INFO_S *pstPortInfo;
    HI_U32 u32PortCnt;

    //search from port0 to DEF_HI_DRV_VPSS_PORT_MAX_NUMBER
    for (u32PortId = 0, u32PortCnt = 0; u32PortId < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32PortId++)
    {
        pstPortInfo = &(pstHalInfo->astPortInfo[u32PortId]);

        if (pstPortInfo->bEnable == HI_TRUE
            && pstPortInfo->bConfig == HI_FALSE)
        {
            u32PortCnt++;
        }
    }

    switch (u32PortCnt)
    {
        case 1:
        {
            return HI_FALSE;
        }

        case 2:
        {
            return HI_TRUE;
        }

        default:
        {
            VPSS_ERROR("Invalid port count:%d\n", u32PortCnt);
        }
        break;
    }

    return HI_FALSE;
}

HI_BOOL VPSS_HAL_NeedRotation(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo)
{
    VPSS_HAL_PORT_INFO_S   *pstPortInfo;
    HI_S32                  s32PortId;
    HI_BOOL                 bNeedRota;

    bNeedRota = HI_FALSE;

    for ( s32PortId = 0; s32PortId < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; s32PortId++ )
    {
        pstPortInfo = &(pstHalInfo->astPortInfo[s32PortId]);

        if (((HI_DRV_VPSS_ROTATION_90 == pstPortInfo->enRotation)
             || (HI_DRV_VPSS_ROTATION_270 == pstPortInfo->enRotation))
            && (pstPortInfo->bEnable) ) // && (!pstPortInfo->bConfig))
        {
            pstPortInfo->bNeedRota  = HI_TRUE;
            bNeedRota               = HI_TRUE;
        }
        else
        {
            pstPortInfo->bNeedRota = HI_FALSE;
        }
    }

    return bNeedRota;
}

HI_BOOL VPSS_HAL_RotaBufConfig(HI_DRV_VIDEO_FRAME_S *pstFrm, VPSS_BUFFER_S *pstBuf)
{
    HI_U32 u32PhyAddr, u32Stride;
    HI_DRV_BUF_ADDR_E enBufLR = HI_DRV_BUF_ADDR_LEFT;

    /* 填充地址信息 */
    u32PhyAddr = pstBuf->stMemBuf.u32StartPhyAddr;
    u32Stride  = pstBuf->u32Stride;

    pstFrm->stBufAddr[enBufLR].u32Stride_Y  =  u32Stride;
    pstFrm->stBufAddr[enBufLR].u32Stride_C  =  u32Stride;


    /* stride 在buffer申请时是使用height计算的, 此时计算偏移时stride*width */

    if (pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV12_CMP
        || pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV21_CMP
        || pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV16_2X1_CMP
        || pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV61_2X1_CMP
       )
    {
        pstFrm->stBufAddr[enBufLR].u32PhyAddr_YHead = u32PhyAddr;
        pstFrm->stBufAddr[enBufLR].u32PhyAddr_Y =
            pstFrm->stBufAddr[enBufLR].u32PhyAddr_YHead + pstFrm->u32Height * 16;
        pstFrm->stBufAddr[enBufLR].u32PhyAddr_CHead =
            pstFrm->stBufAddr[enBufLR].u32PhyAddr_Y + u32Stride * pstFrm->u32Height;

        if (pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV12_CMP
            || pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV21_CMP)
        {
            pstFrm->stBufAddr[enBufLR].u32PhyAddr_C =
                pstFrm->stBufAddr[enBufLR].u32PhyAddr_CHead + pstFrm->u32Height * 16 / 2;
        }
        else
        {
            pstFrm->stBufAddr[enBufLR].u32PhyAddr_C =
                pstFrm->stBufAddr[enBufLR].u32PhyAddr_CHead + pstFrm->u32Height * 16;
        }
    }
    else if (pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV12
             || pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV21
             || pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV61_2X1
             || pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV16_2X1)
    {
        pstFrm->stBufAddr[enBufLR].u32PhyAddr_Y =  u32PhyAddr;
        pstFrm->stBufAddr[enBufLR].u32PhyAddr_C =  u32PhyAddr + u32Stride * pstFrm->u32Height;
        pstFrm->stBufAddr[enBufLR].vir_addr_y = (HI_U64)(HI_SIZE_T)(pstBuf->stMemBuf.pu8StartVirAddr);
        pstFrm->stBufAddr[enBufLR].vir_addr_c = (HI_U64)(HI_SIZE_T)
                                                (pstBuf->stMemBuf.pu8StartVirAddr + u32Stride * pstFrm->u32Height);
    }
    else if (pstFrm->ePixFormat == HI_DRV_PIX_FMT_ARGB8888
             || pstFrm->ePixFormat == HI_DRV_PIX_FMT_ABGR8888)
    {
        pstFrm->stBufAddr[enBufLR].u32PhyAddr_Y =  u32PhyAddr;
    }
    else
    {
        VPSS_ERROR("Invalid Out pixFormat %d,can't get addr\n",
                   pstFrm->ePixFormat);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_BOOL VPSS_HAL_AllocateRotaBuf(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo)
{
    VPSS_HAL_PORT_INFO_S   *pstPortInfo;
    HI_S32                  s32PortId;
    HI_BOOL                 bNeedRota;
    HI_U32                  u32BufSize = 0;
    HI_U32                  u32BufStride = 0;
    HI_S32                  s32Ret;
    VPSS_FB_NODE_S          *pstBuf;
    HI_U32                  u32RotaWidth;
    HI_U32                  u32RotaHeight;


    bNeedRota = HI_FALSE;

    for ( s32PortId = 0; s32PortId < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; s32PortId++ )
    {
        pstPortInfo = &(pstHalInfo->astPortInfo[s32PortId]);
        pstBuf = &(pstPortInfo->stFrmNodeRoBuf);

        if ((pstPortInfo->bEnable) && (!pstPortInfo->bConfig) && (pstPortInfo->bNeedRota))
        {
            /* 以Node1(W*H->ZME(H*W))时的输出的信息为依据, 此时stride要根据H计算.  Node2 H*W->W*H */

            u32RotaWidth = pstPortInfo->stOutInfo.u32Height;
            u32RotaHeight = pstPortInfo->stOutInfo.u32Width;
            VPSS_OSAL_CalBufSize(&u32BufSize,
                                 &u32BufStride,
                                 u32RotaHeight,
                                 u32RotaWidth,
                                 pstPortInfo->stOutInfo.enFormat,
                                 pstPortInfo->stOutInfo.enBitWidth);

            if ((pstBuf->stBuffer.stMemBuf.u32Size != u32BufSize)
                || (pstBuf->stBuffer.u32Stride != u32BufStride))
            {
                if (pstBuf->stBuffer.stMemBuf.u32Size != 0)
                {
                    VPSS_OSAL_FreeMem(&(pstBuf->stBuffer.stMemBuf));
                }

                if (!pstHalInfo->stInInfo.bSecure)
                {
                    s32Ret = VPSS_OSAL_AllocateMem(VPSS_MEM_FLAG_NORMAL, u32BufSize,
                                                   HI_NULL,
                                                   "VPSS_RotaBuf_ns",
                                                   &(pstBuf->stBuffer.stMemBuf));
                }
                else
                {
                    s32Ret = VPSS_OSAL_AllocateMem(VPSS_MEM_FLAG_SECURE, u32BufSize,
                                                   HI_NULL,
                                                   "VPSS_RotaBuf_s",
                                                   &(pstBuf->stBuffer.stMemBuf));
                }

                if (s32Ret != HI_SUCCESS)
                {
                    VPSS_ERROR("Alloc VPSS_RotaBuf_%s Failed\n",
                               (pstHalInfo->stInInfo.bSecure) ? "secure" : "normal");

                    return HI_FAILURE;
                }

                pstBuf->stBuffer.u32Stride = u32BufStride;

                pstBuf->stOutFrame.u32Width  = pstPortInfo->stOutInfo.u32Height;
                pstBuf->stOutFrame.u32Height = pstPortInfo->stOutInfo.u32Width;
                pstBuf->stOutFrame.enBitWidth = pstPortInfo->stOutInfo.enBitWidth;
                pstBuf->stOutFrame.ePixFormat = pstPortInfo->stOutInfo.enFormat;

                VPSS_DBG_INFO("RotaBuf  malloc W H Sride %d %d %d\n",
                              pstBuf->stOutFrame.u32Width,
                              pstBuf->stOutFrame.u32Height,
                              u32BufStride);

                pstBuf->stOutFrame.ePixFormat = pstPortInfo->stOutInfo.enFormat;
                VPSS_HAL_RotaBufConfig(&(pstBuf->stOutFrame), &(pstBuf->stBuffer));
            }
        }
        else
        {
            if (pstBuf->stBuffer.stMemBuf.u32Size != 0)
            {
                VPSS_OSAL_FreeMem(&(pstBuf->stBuffer.stMemBuf));
                pstBuf->stBuffer.stMemBuf.u32Size = 0;
                pstBuf->stBuffer.u32Stride = 0;
            }
        }
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_FreeRotaBuf(VPSS_HAL_INFO_S *pstHalInfo)
{
    VPSS_HAL_PORT_INFO_S   *pstPortInfo;
    HI_S32                  s32PortId;
    HI_S32                  s32Ret;
    VPSS_FB_NODE_S          *pstBuf;
    for ( s32PortId = 0; s32PortId < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; s32PortId++ )
    {
        pstPortInfo = &(pstHalInfo->astPortInfo[s32PortId]);
        pstBuf = &(pstPortInfo->stFrmNodeRoBuf);
        if ((pstBuf->stBuffer.stMemBuf.u32Size != 0)
            && (pstBuf->stBuffer.stMemBuf.u32StartPhyAddr != 0))
        {
            s32Ret = VPSS_OSAL_FreeMem(&(pstBuf->stBuffer.stMemBuf));
            if (HI_SUCCESS == s32Ret)
            {
                pstBuf->stBuffer.stMemBuf.u32Size = 0;
                pstBuf->stBuffer.stMemBuf.pu8StartVirAddr = HI_NULL;
                pstBuf->stBuffer.stMemBuf.u32StartPhyAddr = 0;
                pstBuf->stBuffer.u32Stride = 0;
            }
            else
            {
                VPSS_ERROR("Free rota buf fail!\n");
                return s32Ret;
            }
        }
    }
    return HI_SUCCESS;
}
HI_S32 VPSS_HAL_Task2NodeProc(VPSS_IP_E enIP,
                              VPSS_HAL_INFO_S *pstHalInfo,
                              VPSS_HAL_TASK_TYPE_E enTaskNodeId,
                              HI_BOOL bNodeList[VPSS_HAL_NODE_BUTT],
                              HI_BOOL bNeedVirtualNode,
                              HI_BOOL bNeedRota)
{
    switch ( enTaskNodeId )
    {
        case VPSS_HAL_TASK_NODE_2D_FIELD:
            if (pstHalInfo->u32DetileFieldIdx < 3)
            {
                VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_DEI_FIRST_3FIELD);
                if (bNeedVirtualNode)
                {
                    VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_DEI_FIRST_3FIELD_VIRTUAL);
                }
            }
            else if ((HI_FALSE == pstHalInfo->stInInfo.bProgressive)
                     && VPSS_ALG_IS_SD(pstHalInfo->stInInfo.u32Width, pstHalInfo->stInInfo.u32Height))
            {
                VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_SD_FIRST);
                VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_SD_SECOND);

                if (bNeedVirtualNode)
                {
                    VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_SD_VIRTUAL);
                }
            }
            else
            {
                if (pstHalInfo->stInInfo.bProgressive)
                {
                    VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_FIELD);

                    if (bNeedVirtualNode)
                    {
                        VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_FIELD_VIRTUAL);
                    }
                }
                else
                {
                    VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_DEI);

                    if (bNeedVirtualNode)
                    {
                        VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_DEI_VIRTUAL);
                    }
                }
            }

            if (bNeedRota)
            {
                if (HI_SUCCESS == VPSS_HAL_AllocateRotaBuf(enIP, pstHalInfo))
                {
                    VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_ROTATION_Y);
                    VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_ROTATION_C);
                }
            }

            break;

        case VPSS_HAL_TASK_NODE_2D_FRAME:
            if (HI_DRV_PIXEL_BITWIDTH_10BIT_CTS == pstHalInfo->astPortInfo[0].stOutInfo.enBitWidth)
            {
                VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_CTS10);

                if (bNeedVirtualNode)
                {
                    VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_CTS10_VIRTUAL);
                }
            }
            else if ((HI_DRV_PIXEL_BITWIDTH_8BIT == pstHalInfo->stInInfo.enBitWidth)
                     || (HI_DRV_PIXEL_BITWIDTH_10BIT == pstHalInfo->stInInfo.enBitWidth))

            {
                VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_FRAME);

                if (bNeedVirtualNode)
                {
                    VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_FRAME_VIRTUAL);
                }

                if (bNeedRota)
                {
                    if (HI_SUCCESS == VPSS_HAL_AllocateRotaBuf(enIP, pstHalInfo))
                    {
                        VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_ROTATION_Y);
                        VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_ROTATION_C);
                    }
                }
            }
            break;

        case VPSS_HAL_TASK_NODE_3D:
            VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_3D_FRAME_R);
            break;

        case VPSS_HAL_TASK_NODE_HDR:
#if 0
            VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_HDR_LC);
#else
            VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_HDR_DETILE_NOALG);

            if (bNeedRota)
            {
                if (HI_SUCCESS == VPSS_HAL_AllocateRotaBuf(enIP, pstHalInfo))
                {
                    VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_ROTATION_Y);
                    VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_ROTATION_C);
                }
            }
#endif
            break;
        case VPSS_HAL_TASK_LOWQUALITY:
            VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_FIELD);
            if (bNeedVirtualNode)
            {
                VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_FIELD_VIRTUAL);
            }
            break;
        case VPSS_HAL_TASK_NODE_2D_LAST2FIELD:
            VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_DEI_LAST_2FIELD);
            if (bNeedVirtualNode)
            {
                VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_DEI_LAST_2FIELD_VIRTUAL);
            }
            break;
        default:
            return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_U32 VPSS_HAL_CalcSplitNum(HI_U32 u32Width)
{
    return VPSS_SPLIT_TOTAL_NODE_CNT;
}

HI_S32 VPSS_HAL_Task2Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, VPSS_HAL_TASK_TYPE_E enTaskNodeId, HI_BOOL bNodeList[VPSS_HAL_NODE_BUTT])
{
    HI_S32  s32NodeId;
    HI_BOOL bNeedVirtualNode;
    HI_BOOL bNeedRota;

    for (s32NodeId = 0; s32NodeId < VPSS_HAL_NODE_BUTT; s32NodeId++)
    {
        bNodeList[s32NodeId] = HI_FALSE;
    }

    bNeedVirtualNode = HI_FALSE;

    if (VPSS_HAL_NeedStartVirtual(enIP, pstHalInfo))
    {
        bNeedVirtualNode = HI_TRUE;
    }

    bNeedRota = HI_FALSE;

    if (VPSS_HAL_NeedRotation(enIP, pstHalInfo))
    {
        bNeedRota = HI_TRUE;
    }


#if defined(HI_NVR_SUPPORT)
    {
        VPSS_HAL_PORT_INFO_S   *pstPortInfo;

        VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_UHD);

        if (bNeedVirtualNode)
        {
            VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_UHD_VIRTUAL);
        }

        pstPortInfo = &(pstHalInfo->astPortInfo[0]);
        if (pstPortInfo->bNeedRota)
        {
            if (HI_SUCCESS == VPSS_HAL_AllocateRotaBuf(enIP, pstHalInfo))
            {
                VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_ROTATION_Y);
                VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_ROTATION_C);
            }
        }

        pstPortInfo = &(pstHalInfo->astPortInfo[1]);

        if (bNeedVirtualNode && pstPortInfo->bNeedRota)
        {
            if (HI_SUCCESS == VPSS_HAL_AllocateRotaBuf(enIP, pstHalInfo))
            {
                VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_ROTATION_Y_VIRTUAL);
                VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_ROTATION_C_VIRTUAL);
            }
        }

        return HI_SUCCESS;
    }
#else

    if (VPSS_HAL_TASK_NODE_H265_DEI == enTaskNodeId)
    {
        VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_H265_STEP1_INTERLACE);
        VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_H265_STEP2_DEI);

        if (bNeedRota)
        {
            if (HI_SUCCESS == VPSS_HAL_AllocateRotaBuf(enIP, pstHalInfo))
            {
                VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_ROTATION_Y);
                VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_ROTATION_C);
            }
        }
        return HI_SUCCESS;
    }

    if (VPSS_HAL_TASK_NODE_HDR != enTaskNodeId)
    {
        if ((pstHalInfo->stInInfo.u32Width > 1920)
            && (HI_DRV_PIXEL_BITWIDTH_10BIT_CTS != pstHalInfo->astPortInfo[0].stOutInfo.enBitWidth))
        {
            if (enTaskNodeId != VPSS_HAL_TASK_NODE_3D) //3D@4K also need VPSS_HAL_NODE_3D_FRAME_R
            {
                VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_UHD);

                if (bNeedVirtualNode) //virtual port can be 4K
                {
                    VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_2D_UHD_VIRTUAL);
                }

                if (HI_FALSE == bNeedRota) //think about rota@4K
                {
                    return HI_SUCCESS;
                }
            }

            if (bNeedRota)
            {
                if (HI_SUCCESS == VPSS_HAL_AllocateRotaBuf(enIP, pstHalInfo))
                {
                    VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_ROTATION_Y);
                    VPSS_HAL_ENABLE_NODE(VPSS_HAL_NODE_ROTATION_C);
                    return HI_SUCCESS;
                }
            }
        }
    }

    return VPSS_HAL_Task2NodeProc(enIP, pstHalInfo, enTaskNodeId, bNodeList, bNeedVirtualNode, bNeedRota);
#endif
}

HI_S32 VPSS_HAL_MallocNodeBuffer(VPSS_HAL_INFO_S *pstHalInfo, HI_U32 u32EmptyBufIdxBase,
                                 HI_S32  s32NodeId, VPSS_HAL_NODE_S *pstNODE )
{
    HI_S32 s32Ret = HI_FAILURE;

    if (HI_NULL == pstHalInfo->stNodeList[u32EmptyBufIdxBase].pu8AppVir)
    {
        HI_CHAR acBufName[32] = {'\0'};

        HI_OSAL_Snprintf(acBufName, 32, "VPSS_RegBuf%02d%02d", pstHalInfo->s32InstanceID, s32NodeId);
        /* malloc a new node buffer */
        s32Ret = HI_DRV_MMZ_AllocAndMap(acBufName,
                                        HI_NULL,
                                        VPSS_REG_SIZE,
                                        0,
                                        &pstHalInfo->stNodeList[u32EmptyBufIdxBase].stRegBuf);

        if (s32Ret != HI_SUCCESS)
        {
            VPSS_FATAL("Alloc VPSS_RegBuf Failed, Instance:%d Node:%d\n", pstHalInfo->s32InstanceID, s32NodeId);
            return HI_FAILURE;/*Do not free mmz that has been alloced here! */
        }

        pstHalInfo->stNodeList[u32EmptyBufIdxBase].u32AppPhy =
            pstHalInfo->stNodeList[u32EmptyBufIdxBase].stRegBuf.u32StartPhyAddr;
        pstHalInfo->stNodeList[u32EmptyBufIdxBase].pu8AppVir =
            pstHalInfo->stNodeList[u32EmptyBufIdxBase].stRegBuf.pu8StartVirAddr;
        VPSS_INFO("Malloc node: inst:%d nodeidx:%d phy:%#x vir:%p  size1:%u size2:%u\n",
                  pstHalInfo->s32InstanceID,
                  u32EmptyBufIdxBase,
                  pstHalInfo->stNodeList[u32EmptyBufIdxBase].u32AppPhy,
                  pstHalInfo->stNodeList[u32EmptyBufIdxBase].pu8AppVir,
                  (HI_U32)sizeof(VPSS_REG_S),
                  (HI_U32)VPSS_REG_SIZE);
    }

    pstHalInfo->stNodeList[u32EmptyBufIdxBase].u32NodeId = s32NodeId;
    pstNODE->pu8AppVir = pstHalInfo->stNodeList[u32EmptyBufIdxBase].pu8AppVir;
    pstNODE->u32AppPhy = pstHalInfo->stNodeList[u32EmptyBufIdxBase].u32AppPhy;
    pstNODE->u32NodeId = s32NodeId;

    return HI_SUCCESS;

}
HI_S32 VPSS_HAL_SetTaskInfo(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, VPSS_HAL_TASK_TYPE_E enTaskId,
                            HI_BOOL abNodeVaild[VPSS_HAL_NODE_BUTT])
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32  *pu32AppVir, u32AppPhy;
    HI_S32  s32NodeId;
    HI_BOOL abNodeList[VPSS_HAL_NODE_BUTT];
    HI_U32 u32EmptyBufIdxBase;

    VPSS_HAL_CHECK_IP_VAILD(enIP);
    VPSS_HAL_CHECK_NULL_PTR(pstHalInfo);
    VPSS_HAL_CHECK_TASKNODE_ID_VAILD(enTaskId);

    s32Ret = VPSS_HAL_Task2Node(enIP, pstHalInfo, enTaskId, abNodeList);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_FATAL("Task %d translate to node fail!\n", enTaskId);
    }

    u32EmptyBufIdxBase = pstHalInfo->u32NodeCount;

    for (s32NodeId = 0; s32NodeId < VPSS_HAL_NODE_BUTT; s32NodeId++)
    {
        if (abNodeList[s32NodeId])
        {
            if (HI_NULL == pstHalInfo->stNodeList[u32EmptyBufIdxBase].pu8AppVir)
            {
                HI_CHAR acBufName[32] = {'\0'};

                HI_OSAL_Snprintf(acBufName, 32, "VPSS_RegBuf%02d%02d", pstHalInfo->s32InstanceID, s32NodeId);
                /* malloc a new node buffer */
                s32Ret = HI_DRV_MMZ_AllocAndMap(acBufName,
                                                HI_NULL,
                                                VPSS_REG_SIZE,
                                                0,
                                                &pstHalInfo->stNodeList[u32EmptyBufIdxBase].stRegBuf);

                if (s32Ret != HI_SUCCESS)
                {
                    VPSS_FATAL("Alloc VPSS_RegBuf Failed, Instance:%d Node:%d\n", pstHalInfo->s32InstanceID, s32NodeId);
                    return HI_FAILURE;/*Do not free mmz that has been alloced here! */
                }

                pstHalInfo->stNodeList[u32EmptyBufIdxBase].u32AppPhy =
                    pstHalInfo->stNodeList[u32EmptyBufIdxBase].stRegBuf.u32StartPhyAddr;
                pstHalInfo->stNodeList[u32EmptyBufIdxBase].pu8AppVir =
                    pstHalInfo->stNodeList[u32EmptyBufIdxBase].stRegBuf.pu8StartVirAddr;
                VPSS_INFO("Malloc node: inst:%d nodeidx:%d phy:%#x vir:%p  size1:%u size2:%u\n",
                          pstHalInfo->s32InstanceID,
                          u32EmptyBufIdxBase,
                          pstHalInfo->stNodeList[u32EmptyBufIdxBase].u32AppPhy,
                          pstHalInfo->stNodeList[u32EmptyBufIdxBase].pu8AppVir,
                          (HI_U32)sizeof(VPSS_REG_S),
                          (HI_U32)VPSS_REG_SIZE);
            }

            pstHalInfo->stNodeList[u32EmptyBufIdxBase].u32NodeId = s32NodeId;
            pu32AppVir = (HI_U32 *)pstHalInfo->stNodeList[u32EmptyBufIdxBase].pu8AppVir;
            u32AppPhy = pstHalInfo->stNodeList[u32EmptyBufIdxBase].u32AppPhy;

            abNodeVaild[s32NodeId] = HI_TRUE;

            if (HI_NULL != pfSetNodeInfo[s32NodeId])
            {
                pstHalInfo->enNodeType = s32NodeId;
                s32Ret = pfSetNodeInfo[s32NodeId](enIP, pstHalInfo, pu32AppVir, u32AppPhy);

                if (HI_SUCCESS != s32Ret)
                {
                    VPSS_FATAL("Config node fail, id=%d\n", s32NodeId);
                    return s32Ret;
                }

                if (((VPSS_HAL_NODE_2D_DEI == s32NodeId)
                     || (VPSS_HAL_NODE_2D_DEI_LAST_2FIELD == s32NodeId)
                     || (VPSS_HAL_NODE_2D_DEI_FIRST_3FIELD == s32NodeId))
                    && (HI_TRUE == pstHalInfo->bSplitEnable))
                {
                    HI_U32 u32SplitCnt;
                    HI_S32 s32SplitId;
                    VPSS_HAL_NODE_S astNODE[VPSS_SPLIT_TOTAL_NODE_CNT] = {{0, 0, HI_NULL}};

                    u32SplitCnt = VPSS_HAL_CalcSplitNum(pstHalInfo->stInInfo.u32Width);
                    if (pstHalInfo->u32DetileFieldIdx < 3) //first 3 field, only enable node 0~4
                    {
                        u32SplitCnt = 5;
                    }

                    abNodeList[VPSS_HAL_NODE_2D_DEI] = HI_FALSE;
                    abNodeList[VPSS_HAL_NODE_2D_DEI_LAST_2FIELD] = HI_FALSE;
                    abNodeList[VPSS_HAL_NODE_2D_DEI_FIRST_3FIELD] = HI_FALSE;

                    for (s32SplitId = 0; s32SplitId < u32SplitCnt; s32SplitId++)
                    {
                        s32Ret |= VPSS_HAL_MallocNodeBuffer(pstHalInfo, u32EmptyBufIdxBase,
                                                            s32SplitId + VPSS_HAL_NODE_2D_MC_SPLIT_NODE1,
                                                            &astNODE[s32SplitId]);

                        abNodeVaild[s32SplitId + VPSS_HAL_NODE_2D_MC_SPLIT_NODE1] = HI_TRUE;
#ifndef VPSS_OUT_TMPBUF
                        if (s32SplitId > 4)
                        {
                            abNodeVaild[s32SplitId + VPSS_HAL_NODE_2D_MC_SPLIT_NODE1] = 0;
                        }
#endif
                        u32EmptyBufIdxBase++;
                    }

                    s32Ret |= VPSS_HAL_NodeSplit((S_VPSS_REGS_TYPE *)pu32AppVir,
                                                 &astNODE[0], u32SplitCnt, pstHalInfo->u32DetileFieldIdx);
                    if (HI_SUCCESS != s32Ret)
                    {
                        VPSS_FATAL("Config node fail, id=%d\n", s32SplitId + VPSS_HAL_NODE_2D_MC_SPLIT_NODE1);
                        return s32Ret;
                    }
#ifdef VPSS_OUT_TMPBUF
                    pstHalInfo->u32NodeCount = u32EmptyBufIdxBase;
#else
                    pstHalInfo->u32NodeCount = 5;
#endif
                    return HI_SUCCESS;
                }
#if !defined(HI_NVR_SUPPORT)
                VPSS_HAL_Assert(s32NodeId, (volatile S_VPSS_REGS_TYPE *)pu32AppVir, HI_FALSE);
#endif
            }
            else if (HI_FALSE == pstHalInfo->bSplitEnable)
            {
                VPSS_FATAL("Config node func is NULL, id=%d\n", s32NodeId);
                return HI_FAILURE;
            }

            u32EmptyBufIdxBase++;
            pstHalInfo->u32NodeCount = u32EmptyBufIdxBase;
        }
    }

    return s32Ret;
}

HI_S32 VPSS_HAL_SetDeiCfg(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, CBB_REG_ADDR_S stRegAddr)
{
    HI_U32              VPSS_DEI_ADDR;
    VPSS_DIESTCFG_S     *pstDeiSt;
    CBB_INFO_S          stDeiSttCfg;
    CBB_ALG_INFO_S      stDeiAlgCfg;
    S_VPSS_REGS_TYPE    *pstVpssNode;  //DDR中节点首地址


    VPSS_HAL_CHECK_IP_VAILD(enIP);
    VPSS_HAL_CHECK_NULL_PTR(pstHalInfo);

    VPSS_MEM_CLEAR(stDeiSttCfg);
    VPSS_MEM_CLEAR(stDeiAlgCfg);

    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    VPSS_DEI_ADDR = stRegAddr.u32NodePhyAddr + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DIECTRL) - sizeof(HI_U32);
    //HI_PRINT("stRegAddr.u32NodePhyAddr: %x, offset:%d ", stRegAddr.u32NodePhyAddr,  VPSS_REG_SIZE_CALC(VPSS_CTRL,VPSS_DIECTRL)-sizeof(HI_U32));

    //VPSS_DRV_Set_VPSS_DIECTRL_lc_mode(pstVpssNode, 1, 1); // 4 field mode
    VPSS_Die_SetDieLMode(pstVpssNode, 1);
    VPSS_Die_SetDieCMode(pstVpssNode, 1);


    pstDeiSt = &pstHalInfo->stDieInfo.stDieStCfg;

    stDeiSttCfg.bEn = HI_TRUE;//deiEn
    stDeiSttCfg.u32Wth = (pstHalInfo->stInInfo.u32Width + 2) / 4;
    stDeiSttCfg.u32Hgt = pstHalInfo->stInInfo.u32Height / 2;
    if (VPSS_HAL_NODE_2D_H265_STEP2_DEI == pstHalInfo->enNodeType)
    {
        stDeiSttCfg.u32Hgt = pstHalInfo->stInInfo.u32Height;
    }
    stDeiSttCfg.u32RPhyAddr = pstDeiSt->u32PPreAddr;
    stDeiSttCfg.u32WPhyAddr = pstDeiSt->u32CurAddr;
    stDeiSttCfg.u32Stride = pstDeiSt->u32Stride;

#ifdef HI_VPSS_SMMU_SUPPORT
    stDeiSttCfg.bSmmu_R = HI_TRUE;
    stDeiSttCfg.bSmmu_W = HI_TRUE;
#else
    stDeiSttCfg.bSmmu_R = HI_FALSE;
    stDeiSttCfg.bSmmu_W = HI_FALSE;
#endif

#if 0
    HI_PRINT("DEI st cfg : ppre:%x  pre:%x cur:%x stride:%u\n",
             pstDeiSt->u32PPreAddr,
             pstDeiSt->u32PreAddr,
             pstDeiSt->u32CurAddr,
             pstDeiSt->u32Stride);
#endif

    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_DEI_ST, (HI_VOID *)&stDeiSttCfg, HI_NULL);
    VPSS_Die_SetPreInfoEn(pstVpssNode, 0);

    stDeiAlgCfg.u32ParaAddr = VPSS_DEI_ADDR;
    stDeiAlgCfg.bEnable     = HI_TRUE;
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_DEI, (HI_VOID *)&stDeiAlgCfg, HI_NULL);
    if ((VPSS_HAL_IS_0X66(pstHalInfo->stRwzbInfo.u32IsRwzb)) || (VPSS_HAL_IS_0X67(pstHalInfo->stRwzbInfo.u32IsRwzb)))
    {
        VPSS_Die_SetMaOnly(pstVpssNode, 1);
        VPSS_Die_SetRecModeEn(pstVpssNode, 0);
        VPSS_Die_SetHisMotionEn(pstVpssNode, 0);
        VPSS_Die_SetPpreInfoEn(pstVpssNode, 1);
    }

    return HI_SUCCESS;
}

HI_U32 VPSS_HAL_TransPixelZMEFormat(HI_DRV_PIX_FORMAT_E enFormat)
{
    if (enFormat == HI_DRV_PIX_FMT_NV21_CMP
        || enFormat == HI_DRV_PIX_FMT_NV12_CMP
        || enFormat == HI_DRV_PIX_FMT_NV21
        || enFormat == HI_DRV_PIX_FMT_NV12
        || enFormat == HI_DRV_PIX_FMT_NV21_TILE
        || enFormat == HI_DRV_PIX_FMT_NV12_TILE
        || enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP
        || enFormat == HI_DRV_PIX_FMT_NV61
        || enFormat == HI_DRV_PIX_FMT_NV16
        || enFormat == HI_DRV_PIX_FMT_YUV422_1X2
        || enFormat == HI_DRV_PIX_FMT_YUV420p
        || enFormat == HI_DRV_PIX_FMT_YUV410p)
    {
        return 0;
    }

    return 1;
}

HI_BOOL VPSS_HAL_NeedVPZMEEnable(VPSS_HAL_NODE_TYPE_E enNodeType)
{
    if ( (enNodeType == VPSS_HAL_NODE_2D_DEI_FIRST_3FIELD)
         || (enNodeType == VPSS_HAL_NODE_2D_DEI_FIRST_3FIELD_VIRTUAL)
         || (enNodeType == VPSS_HAL_NODE_2D_FIELD)
         || (enNodeType == VPSS_HAL_NODE_2D_FIELD_VIRTUAL)
       )
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

HI_S32 VPSS_HAL_SetMcDeiCfg(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, CBB_REG_ADDR_S stRegAddr)
{
    HI_DRV_VID_FRAME_ADDR_S *pstBlendRef;
    HI_DRV_VID_FRAME_ADDR_S *pstBlendWbc;

    CBB_ALG_INFO_S      stMcDeiAlgCfg;
    CBB_FRAME_S         stFrameCfg;
    CBB_INFO_BLKMV_S    stBlkmvCfg;
    CBB_INFO_RGMV_S     stRgmvCfg;
    CBB_INFO_PRJV_S     stPrjVCfg;
    CBB_INFO_PRJH_S     stPrjHCfg;
    CBB_INFO_BLKMT_S    stBlkmtCfg;
    CBB_INFO_DI_S       stDiCfg;
    HI_U32 u32WthReal;
    HI_U32 u32HgtReal;
    HI_BOOL bMedsEn;

    VPSS_HAL_CHECK_IP_VAILD(enIP);
    VPSS_HAL_CHECK_NULL_PTR(pstHalInfo);

    VPSS_MEM_CLEAR(stMcDeiAlgCfg);
    VPSS_MEM_CLEAR(stFrameCfg);
    VPSS_MEM_CLEAR(stBlkmvCfg);
    VPSS_MEM_CLEAR(stRgmvCfg);
    VPSS_MEM_CLEAR(stPrjVCfg);
    VPSS_MEM_CLEAR(stPrjHCfg);
    VPSS_MEM_CLEAR(stBlkmtCfg);
    VPSS_MEM_CLEAR(stDiCfg);

    stMcDeiAlgCfg.bEnable   = HI_TRUE;

    bMedsEn = stMcDeiAlgCfg.bEnable;

    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_MCDEI, (HI_VOID *)&stMcDeiAlgCfg, &bMedsEn);

    pstBlendRef = &(pstHalInfo->stMcdeiRfrInfo.stBlendRef.stAddr);
    pstBlendWbc = &(pstHalInfo->stMcdeiRfrInfo.stBlendWbc.stAddr);

    u32WthReal   = pstHalInfo->stInInfo.u32Width;
    u32HgtReal   = pstHalInfo->stInInfo.u32Height / 2;

    stFrameCfg.bEn = HI_TRUE;
    stFrameCfg.u32Width = u32WthReal;
    stFrameCfg.u32Height = u32HgtReal;
    stFrameCfg.enPixelFmt = pstHalInfo->stInInfo.enFormat;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y  = pstBlendRef->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C  = pstBlendRef->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y   = pstBlendRef->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C   = pstBlendRef->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif

    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_REE, (HI_VOID *)&stFrameCfg, HI_NULL);

    stFrameCfg.bEn = HI_TRUE;//dieEn&mcdiEn
    stFrameCfg.u32Width = u32WthReal;
    stFrameCfg.u32Height = u32HgtReal;
    stFrameCfg.enPixelFmt = HI_DRV_PIX_FMT_NV21;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y  = pstBlendWbc->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C  = pstBlendWbc->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y   = pstBlendWbc->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C   = pstBlendWbc->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_WRITE_CUE, (HI_VOID *)&stFrameCfg, HI_NULL);


    stDiCfg.bEn = HI_TRUE;//deiEn&mcdiEn
    stDiCfg.u32Width = (u32WthReal + 2) / 4; //pstHalInfo->stMcdeiStInfo.stDiCfg.u32Width;
    stDiCfg.u32Hight = u32HgtReal;//pstHalInfo->stMcdeiStInfo.stDiCfg.u32Height;
    stDiCfg.u32WriteAddr = pstHalInfo->stMcdeiStInfo.stDiCntCfg.u32WriteAddr;
    stDiCfg.u32ReadAddr = pstHalInfo->stMcdeiStInfo.stDiCntCfg.u32ReadAddr;
    stDiCfg.u32Stride = pstHalInfo->stMcdeiStInfo.stDiCntCfg.u32Stride;
#ifdef HI_VPSS_SMMU_SUPPORT
    stDiCfg.bSmmu_w = HI_TRUE;
    stDiCfg.bSmmu_r = HI_TRUE;
#else
    stDiCfg.bSmmu_w = HI_FALSE;
    stDiCfg.bSmmu_r = HI_FALSE;
#endif
    //    VPSS_DBG_INFO("DI : CurR(%#x), Nx2W(%#x), Str(%#x).\n", stDiCfg.u32CurReadAddr, stDiCfg.u32Nx2WriteAddr, stDiCfg.u32Stride);
    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_DI, (HI_VOID *)&stDiCfg, HI_NULL);

    stBlkmvCfg.bEn = HI_TRUE;//deiEn&mcdiEn

    stBlkmvCfg.u32Wth = (u32WthReal + 7) / 8;
    stBlkmvCfg.u32Hgt = (u32HgtReal + 3) / 4;
    stBlkmvCfg.u32CurReadAddr   = pstHalInfo->stMcdeiStInfo.stBlkmvCfg.u32CurReadAddr;
    stBlkmvCfg.u32RefReadAddr   = pstHalInfo->stMcdeiStInfo.stBlkmvCfg.u32RefReadAddr;
    stBlkmvCfg.u32Nx1WriteAddr  = pstHalInfo->stMcdeiStInfo.stBlkmvCfg.u32Nx1WriteAddr;
    stBlkmvCfg.u32Stride        = pstHalInfo->stMcdeiStInfo.stBlkmvCfg.u32Stride;
#ifdef HI_VPSS_SMMU_SUPPORT
    stBlkmvCfg.bSmmu_Cur = HI_TRUE;
    stBlkmvCfg.bSmmu_Ref = HI_TRUE;
    stBlkmvCfg.bSmmu_Nx1 = HI_TRUE;
#else
    stBlkmvCfg.bSmmu_Cur = HI_FALSE;
    stBlkmvCfg.bSmmu_Ref = HI_FALSE;
    stBlkmvCfg.bSmmu_Nx1 = HI_FALSE;
#endif
    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_BLKMV, (HI_VOID *)&stBlkmvCfg, HI_NULL);

    stBlkmtCfg.bEn = HI_TRUE;//deiEn&mcdiEn
    stBlkmtCfg.u32Wth = (u32WthReal + 7) / 8;
    stBlkmtCfg.u32Hgt = (u32HgtReal + 3) / 4;
    stBlkmtCfg.u32CurWriteAddr  = pstHalInfo->stMcdeiStInfo.stBlkmtCfg.u32CurWriteAddr;
    stBlkmtCfg.u32RefReadAddr   = pstHalInfo->stMcdeiStInfo.stBlkmtCfg.u32RefReadAddr;
    stBlkmtCfg.u32Stride        = pstHalInfo->stMcdeiStInfo.stBlkmtCfg.u32Stride;
#ifdef HI_VPSS_SMMU_SUPPORT
    stBlkmtCfg.bSmmu_Cur = HI_TRUE;
    stBlkmtCfg.bSmmu_Ref = HI_TRUE;
#else
    stBlkmtCfg.bSmmu_Cur = HI_FALSE;
    stBlkmtCfg.bSmmu_Ref = HI_FALSE;
#endif
    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_BLKMT, (HI_VOID *)&stBlkmtCfg, HI_NULL);


    //use VPSS_HAL_SetRgmvCfg
    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_SetRgmvCfg(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, CBB_REG_ADDR_S stRegAddr)
{
    CBB_INFO_RGMV_S     stRgmvCfg;
    CBB_INFO_PRJV_S     stPrjVCfg;
    CBB_INFO_PRJH_S     stPrjHCfg;

    HI_U32 u32RgmvNumH;
    HI_U32 u32RgmvNumV;

    HI_U32 u32WthReal;
    HI_U32 u32HgtReal;

    VPSS_HAL_CHECK_IP_VAILD(enIP);
    VPSS_HAL_CHECK_NULL_PTR(pstHalInfo);

    VPSS_MEM_CLEAR(stRgmvCfg);
    VPSS_MEM_CLEAR(stPrjVCfg);
    VPSS_MEM_CLEAR(stPrjHCfg);

    u32WthReal   = pstHalInfo->stInInfo.u32Width;
    u32HgtReal   = (pstHalInfo->stInInfo.bProgressive) ? pstHalInfo->stInInfo.u32Height : pstHalInfo->stInInfo.u32Height / 2 ;

    u32RgmvNumH = (u32WthReal + 33) / 64 ;
    u32RgmvNumV = (u32HgtReal +  5) / 8 ;

    stRgmvCfg.bEn = HI_TRUE;//rmgvEn
    stRgmvCfg.u32Wth = u32RgmvNumH;
    stRgmvCfg.u32Hgt = u32RgmvNumV;
    stRgmvCfg.u32CurReadAddr    = pstHalInfo->stMcdeiStInfo.stRgmeCfg.u32CurReadAddr;
    stRgmvCfg.u32Nx1ReadAddr    = pstHalInfo->stMcdeiStInfo.stRgmeCfg.u32Nx1ReadAddr;
    stRgmvCfg.u32Nx2WriteAddr   = pstHalInfo->stMcdeiStInfo.stRgmeCfg.u32Nx2WriteAddr;
    stRgmvCfg.u32Stride         = pstHalInfo->stMcdeiStInfo.stRgmeCfg.u32Stride;
#ifdef HI_VPSS_SMMU_SUPPORT
    stRgmvCfg.bSmmu_Cur = HI_TRUE;
    stRgmvCfg.bSmmu_Nx2 = HI_TRUE;
    stRgmvCfg.bSmmu_Nx1 = HI_TRUE;
#else
    stRgmvCfg.bSmmu_Cur = HI_FALSE;
    stRgmvCfg.bSmmu_Nx2 = HI_FALSE;
    stRgmvCfg.bSmmu_Nx1 = HI_FALSE;
#endif
    VPSS_DBG_INFO("INFO_RGMV : CurR(%#x), Nx1R(%#x), Nx2(%#x), Str(%#x).\n",
                  stRgmvCfg.u32CurReadAddr, stRgmvCfg.u32Nx1ReadAddr, stRgmvCfg.u32Nx2WriteAddr, stRgmvCfg.u32Stride);
    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_RGMV, (HI_VOID *)&stRgmvCfg, HI_NULL);


    stPrjVCfg.bEn = HI_TRUE;//rmgvEn
    stPrjVCfg.u32Wth = u32RgmvNumH * 16;
    stPrjVCfg.u32Hgt = u32RgmvNumV;
    stPrjVCfg.u32CurReadAddr    = pstHalInfo->stMcdeiStInfo.stPrjvCfg.u32CurReadAddr;
    stPrjVCfg.u32Nx2WriteAddr   = pstHalInfo->stMcdeiStInfo.stPrjvCfg.u32Nx2WriteAddr;
    stPrjVCfg.u32Stride         = pstHalInfo->stMcdeiStInfo.stPrjvCfg.u32Stride;
#ifdef HI_VPSS_SMMU_SUPPORT
    stPrjVCfg.bSmmu_Cur = HI_TRUE;
    stPrjVCfg.bSmmu_Nx2 = HI_TRUE;
#else
    stPrjVCfg.bSmmu_Cur = HI_FALSE;
    stPrjVCfg.bSmmu_Nx2 = HI_FALSE;
#endif
    VPSS_DBG_INFO("PRJ_V : CurR(%#x), Nx2W(%#x), Str(%#x).\n",
                  stPrjVCfg.u32CurReadAddr, stPrjVCfg.u32Nx2WriteAddr,
                  stPrjVCfg.u32Stride);
    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_PRJ_V, (HI_VOID *)&stPrjVCfg, HI_NULL);



    stPrjHCfg.bEn = HI_TRUE;//rmgvEn
    stPrjHCfg.u32Wth = u32RgmvNumH * 128;
    stPrjHCfg.u32Hgt = u32RgmvNumV;
    stPrjHCfg.u32CurReadAddr    = pstHalInfo->stMcdeiStInfo.stPrjhCfg.u32CurReadAddr;
    stPrjHCfg.u32Nx2WriteAddr   = pstHalInfo->stMcdeiStInfo.stPrjhCfg.u32Nx2WriteAddr;
    stPrjHCfg.u32Stride         = pstHalInfo->stMcdeiStInfo.stPrjhCfg.u32Stride;
#ifdef HI_VPSS_SMMU_SUPPORT
    stPrjHCfg.bSmmu_Cur = HI_TRUE;
    stPrjHCfg.bSmmu_Nx2 = HI_TRUE;
#else
    stPrjHCfg.bSmmu_Cur = HI_FALSE;
    stPrjHCfg.bSmmu_Nx2 = HI_FALSE;
#endif
    VPSS_DBG_INFO("PRJ_H : CurR(%#x), Nx2W(%#x), Str(%#x).\n",
                  stPrjHCfg.u32CurReadAddr, stPrjHCfg.u32Nx2WriteAddr, stPrjHCfg.u32Stride);
    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_PRJ_H, (HI_VOID *)&stPrjHCfg, HI_NULL);


    return HI_SUCCESS;
}


HI_S32 LoadLut(HI_U32 *reg, const HI_U16 *lut, HI_U32 u32Size)
{
    HI_U32 u32Index;

    for (u32Index = 0; u32Index < u32Size / 2; u32Index++)
    {
        *(reg + u32Index) = ((*(lut + u32Index * 2) & 0xffff) << 16) +  (*(lut + u32Index * 2 + 1) & 0xffff);
    }

    if (0 != u32Size % 2)
    {
        *(reg + u32Size - 1) = *(lut + u32Size - 1);
    }
    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_SetHDRCfg_HDR10_2_SDR(VPSS_IP_E enIP, CBB_REG_ADDR_S stRegAddr, VPSS_HAL_INFO_S *pstHalInfo)
{
    {
        S_VPSS_REGS_TYPE *pstVpssReg = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;
        HI_DRV_COLOR_SPACE_E enInCS = HI_DRV_CS_BT2020_YUV_LIMITED;
#define TM_LUT_SIZE 64
#define SatM_LUT_SIZE 65

        const HI_U16 hdr102sdrtypc_ylutlim[TM_LUT_SIZE] = //12bit
        {
            256 ,       256 ,       268 ,       278 ,       288 ,       298 ,       320 ,       343 ,
            368 ,       395 ,       425 ,       457 ,       491 ,       529 ,       569 ,       612 ,
            659 ,       709 ,       763 ,       821 ,       882 ,       949 ,      1019 ,      1095 ,
            1175 ,      1261 ,      1352 ,      1448 ,      1551 ,      1658 ,      1772 ,      1890 ,
            2014 ,      2143 ,      2276 ,      2412 ,      2551 ,      2690 ,      2828 ,      2964 ,
            3095 ,      3219 ,      3333 ,      3435 ,      3523 ,      3596 ,      3653 ,      3695 ,
            3724 ,      3742 ,      3752 ,      3757 ,      3759 ,      3760 ,      3760 ,      3760 ,
            3760 ,      3760 ,      3760 ,      3760 ,      3760 ,      3760 ,      3760 ,      3760 ,
        };

        const HI_U16 hdr102sdrtypc_ylutfull[TM_LUT_SIZE] = //12bit
        {
            0 ,        13 ,        23 ,        32 ,        42 ,        53 ,        63 ,        74 ,
            86 ,        97 ,       109 ,       122 ,       135 ,       148 ,       162 ,       177 ,
            192 ,       207 ,       223 ,       240 ,       257 ,       274 ,       293 ,       372 ,
            462 ,       564 ,       678 ,       807 ,       952 ,      1114 ,      1293 ,      1491 ,
            1709 ,      1945 ,      2199 ,      2467 ,      2744 ,      3021 ,      3157 ,      3289 ,
            3414 ,      3533 ,      3641 ,      3739 ,      3825 ,      3897 ,      3956 ,      4002 ,
            4036 ,      4060 ,      4075 ,      4084 ,      4088 ,      4091 ,      4092 ,      4092 ,
            4092 ,      4092 ,      4092 ,      4092 ,      4092 ,      4092 ,      4092 ,      4092 ,
        };

        const HI_U16 hdr102sdrtypc_satlutlimit[SatM_LUT_SIZE] =   // 10bit
        {

            102 ,       102 ,       102 ,       102 ,       102 ,       115 ,       136 ,       160 ,
            179 ,       191 ,       197 ,       200 ,       203 ,       208 ,       217 ,       227 ,
            236 ,       241 ,       244 ,       243 ,       241 ,       244 ,       259 ,       289 ,
            332 ,       384 ,       441 ,       499 ,       558 ,       614 ,       666 ,       711 ,
            746 ,       772 ,       791 ,       807 ,       824 ,       846 ,       872 ,       898 ,
            922 ,       941 ,       961 ,       986 ,      1015 ,      1023 ,      1023 ,      1023 ,
            1023 ,      1023 ,      1023 ,      1023 ,      1023 ,      1023 ,      1023 ,      1023 ,
            1023 ,      1023 ,      1023 ,      1023 ,      1023 ,      1023 ,      1023 ,      1023 ,
            1023 ,
        } ;

        const HI_U16 hdr102sdrtypc_satlutfull[SatM_LUT_SIZE] =   // 10bit
        {
            307 ,       314 ,       321 ,       327 ,       331 ,       334 ,       335 ,       336 ,
            337 ,       337 ,       338 ,       340 ,       343 ,       345 ,       346 ,       347 ,
            350 ,       361 ,       379 ,       402 ,       426 ,       448 ,       466 ,       482 ,
            496 ,       508 ,       518 ,       529 ,       539 ,       550 ,       562 ,       576 ,
            592 ,       610 ,       628 ,       645 ,       658 ,       667 ,       670 ,       672 ,
            677 ,       689 ,       712 ,       741 ,       769 ,       791 ,       807 ,       819 ,
            828 ,       835 ,       839 ,       842 ,       844 ,       845 ,       845 ,       845 ,
            845 ,       846 ,       847 ,       849 ,       853 ,       858 ,       866 ,       876 ,
            888 ,
        } ;

        /*
            drv ctrl
        */
        pstVpssReg->VPSS_CTRL.bits.hdr_in = 1;

        /* LCHDR en control */
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_en           = 1;
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_tmen         = 1;
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_dithen       = 1;
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_satmapyen    = 1;
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_cscen        = 1;

        /* 当前处理是按照 输入limit->limit, full->full  处理的*/
        if ((HI_DRV_CS_BT2020_YUV_LIMITED == enInCS) || (HI_DRV_CS_BT709_YUV_LIMITED == enInCS))
        {
            pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt   = 0;   /* limit/full 表示输入源 */
        }
        else
        {
            pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt   = 1;   /* limit/full 表示输入源 */
        }

        pstVpssReg->VPSS_LCHDR_SCALE2P.bits.lchdr_satsclcoef = 8;
        pstVpssReg->VPSS_LCHDR_SCALE2P.bits.lchdr_csc_scale  = 13;

        pstVpssReg->VPSS_LCHDR_CSC_COEF0.bits.lchdr_csc_coef11 = 5461;
        pstVpssReg->VPSS_LCHDR_CSC_COEF0.bits.lchdr_csc_coef12 = 0;
        pstVpssReg->VPSS_LCHDR_CSC_COEF1.bits.lchdr_csc_coef21 = 8192;
        pstVpssReg->VPSS_LCHDR_CSC_COEF1.bits.lchdr_csc_coef22 = 0;

        pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x1_step = 6;
        pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x2_step = 3;
        pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x3_step = 4;
        pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x4_step = 1;

        pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x1_num = 1;
        pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x2_num = 4;
        pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x3_num = 52;
        pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x4_num = 6;

        pstVpssReg->VPSS_LCHDR_TMAP_POS0.bits.gmm_x1_pos = 64;
        pstVpssReg->VPSS_LCHDR_TMAP_POS0.bits.gmm_x2_pos = 96;
        pstVpssReg->VPSS_LCHDR_TMAP_POS1.bits.gmm_x3_pos = 928;
        pstVpssReg->VPSS_LCHDR_TMAP_POS1.bits.gmm_x4_pos = 940;

        /* Dither */
        pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_round = 0;
        pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_domain_mode = 0;
        pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_tap_mode = 0;
        pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_round_unlim = 0;

        pstVpssReg->VPSS_LCHDR_DITHER_THR.bits.lchdr_dither_thr_max = 65535;
        pstVpssReg->VPSS_LCHDR_DITHER_THR.bits.lchdr_dither_thr_min = 0;

        if (1 == pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt)
        {
            LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_TMAP_LUT0, hdr102sdrtypc_ylutfull, TM_LUT_SIZE);
            LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_SMAP_LUT0, hdr102sdrtypc_satlutfull, SatM_LUT_SIZE);
        }
        else
        {
            LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_TMAP_LUT0, hdr102sdrtypc_ylutlim, TM_LUT_SIZE);
            LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_SMAP_LUT0, hdr102sdrtypc_satlutlimit, SatM_LUT_SIZE);
        }

        return HI_SUCCESS;
    }


}

HI_S32 VPSS_HAL_SetPortCfg(VPSS_IP_E enIP, CBB_REG_ADDR_S stRegAddr, VPSS_HAL_INFO_S *pstHalInfo)
{
    CBB_FRAME_S             stFrmCfg;
    VPSS_HAL_PORT_INFO_S   *pstHalPort;
    HI_U32                  u32PortId;
    HI_BOOL                 bUVInver;
    CBB_FUNC_FLIP_S         stFlipInfo;
    CBB_FUNC_CROP_S         stFuncCropCfg;
    CBB_FUNC_ZME_S          stFuncZmeCfg;
    CBB_FUNC_LBOX_S         stLBox;
    CBB_FUNC_VPZME_S        stFuncVPZmeCfg;
    CBB_FUNC_4PIXEL_S       stFunc4PixelCfg;
    HI_RECT_S               *pstCropRect;
    HI_PQ_ZME_PARA_IN_S     *pstZmeDrvPara;
    VPSS_HAL_FRAME_S        *pstInInfo;
    VPSS_HAL_FRAME_S        *pstOutFrm;
    HI_DRV_VID_FRAME_ADDR_S *pstOutAddr;
    CBB_FUNC_TUNNELOUT_S    stFuncTunnelOutCfg;
    CBB_FUNC_TRANS_S        stTransInfo;
    VPSS_HAL_CTX_S          *pstHalCtx;
    HI_BOOL                 b4PixelClk;
    HI_BOOL                 bAlgEnable;
    HI_BOOL                 bVPZMEEnable;


    VPSS_MEM_CLEAR(stFrmCfg);
    VPSS_MEM_CLEAR(stFlipInfo);
    VPSS_MEM_CLEAR(stFuncCropCfg);
    VPSS_MEM_CLEAR(stFuncZmeCfg);
    VPSS_MEM_CLEAR(stLBox);
    VPSS_MEM_CLEAR(stFuncVPZmeCfg);
    VPSS_MEM_CLEAR(stFunc4PixelCfg);
    VPSS_MEM_CLEAR(stFuncTunnelOutCfg);
    VPSS_MEM_CLEAR(stTransInfo);

    VPSS_HAL_CHECK_INST_VAILD(pstHalInfo->s32InstanceID);
    VPSS_HAL_CHECK_IP_VAILD(enIP);

    pstHalCtx = &stHalCtx[enIP][pstHalInfo->s32InstanceID];

    b4PixelClk = HI_FALSE;
    bAlgEnable = HI_TRUE;
    if ((VPSS_HAL_NODE_2D_UHD == pstHalInfo->enNodeType)
        || (VPSS_HAL_NODE_2D_UHD_VIRTUAL == pstHalInfo->enNodeType)
        || (VPSS_HAL_NODE_HDR_DETILE_NOALG == pstHalInfo->enNodeType)
        || (VPSS_HAL_NODE_HDR_LC == pstHalInfo->enNodeType))
    {
        b4PixelClk = HI_TRUE;
    }

    for (u32PortId = 0; u32PortId < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32PortId++)
    {
        pstHalPort = &pstHalInfo->astPortInfo[u32PortId];

        if ((pstHalPort->bEnable)  && (pstHalPort->bConfig == HI_FALSE))
        {
            pstOutFrm = &pstHalPort->stOutInfo;
            pstOutAddr = &pstOutFrm->stAddr;
            pstInInfo = &(pstHalInfo->stInInfo);

            if ((pstHalInfo->stInInfo.enBitWidth ==  HI_DRV_PIXEL_BITWIDTH_10BIT)
                && (pstOutFrm->enBitWidth == HI_DRV_PIXEL_BITWIDTH_10BIT))
            {
                bAlgEnable = HI_FALSE;
                b4PixelClk = HI_TRUE;
            }
            else
            {
                VPSS_PIXLE_UPALIGN_W(pstOutFrm->u32Width, b4PixelClk);
                VPSS_PIXLE_UPALIGN_H(pstOutFrm->u32Height, b4PixelClk);
            }

#ifdef VPSS_SUPPORT_OUT_TUNNEL
            /*tunnel*/
            stFuncTunnelOutCfg.bEnable = HI_FALSE;
            if (HI_TRUE == pstHalPort->bOutLowDelay)
            {
                stFuncTunnelOutCfg.bEnable          = HI_TRUE;
                stFuncTunnelOutCfg.eMode            = CBB_TUNOUT_2;
                stFuncTunnelOutCfg.u32FinishLine    = pstOutFrm->u32Height * 30 / 100;
#ifdef HI_VPSS_SUPPORT_OUTTUNNEL_SMMU
                stFuncTunnelOutCfg.u32WriteAddr     = pstHalInfo->stLowDelayBuf_MMU.u32StartSmmuAddr;
#else
                stFuncTunnelOutCfg.u32WriteAddr     = pstHalInfo->stLowDelayBuf_MMZ.u32StartPhyAddr;
#endif
            }
            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_TUNNEL_OUT, (HI_VOID *)&stFuncTunnelOutCfg, HI_NULL);
#endif

            if (pstHalInfo->enNodeType == VPSS_HAL_NODE_HDR_DETILE_NOALG)
            {
                //if EL carries no metadata, EL NODE donot need to trans metadata
                stTransInfo.bEnable    = (pstHalInfo->stInInfo.u32MetaSize == 0) ? HI_FALSE : HI_TRUE;
                stTransInfo.u32SrcAddr = pstInInfo->stAddr_META.u32PhyAddr_Y;
                stTransInfo.u32DstAddr = pstOutFrm->stAddr_META.u32PhyAddr_Y;
                stTransInfo.u32Size    = (pstInInfo->u32MetaSize / 256) + 1;
                stTransInfo.bSecure    = pstInInfo->bSecure;
#ifdef HI_VPSS_SMMU_SUPPORT
                stTransInfo.bSmmu      = HI_TRUE;
#else
                stTransInfo.bSmmu      = HI_FALSE;
#endif
                if (stTransInfo.bEnable)
                {
                    if (stTransInfo.u32SrcAddr == 0 || stTransInfo.u32DstAddr == 0 || stTransInfo.u32Size == 0)
                    {
                        VPSS_ERROR("metadata config error.u32SrcAddr %#x u32DstAddr %#x u32TranSize %d\n",
                                   stTransInfo.u32SrcAddr,
                                   stTransInfo.u32DstAddr,
                                   stTransInfo.u32Size);
                        return HI_FAILURE;
                    }
                }
                VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_TRANS, (HI_VOID *)&stTransInfo, HI_NULL);
            }


            /*Pre-ZME*/
            bVPZMEEnable = VPSS_HAL_NeedVPZMEEnable(pstHalInfo->enNodeType);
            stFuncVPZmeCfg.bEnable = bVPZMEEnable;
            if (HI_TRUE == bVPZMEEnable)
            {
                stFuncVPZmeCfg.eFirMode = PREZME_VFIELD;
                if (pstHalInfo->stInInfo.enFieldMode == HI_DRV_FIELD_TOP)
                {
                    stFuncVPZmeCfg.eFirMode = PREZME_2X;
                }
            }
            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_VPZME, (HI_VOID *)&stFuncVPZmeCfg, HI_NULL);

            //  VPSS_ERROR("node %d vpzme %d\n", pstHalInfo->enNodeType, bVPZMEEnable);

            /* Flip&Mirro */
            stFlipInfo.bFlipH = pstHalPort->bNeedMirror;
            stFlipInfo.bFlipV = pstHalPort->bNeedFlip;
            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_FLIP, (HI_VOID *)&stFlipInfo, HI_NULL);

            /* UV反转 */
            bUVInver = pstOutFrm->bUVInver;
            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_UV, (HI_VOID *)&bUVInver, HI_NULL);

            /* VHD0's Crop */
            pstCropRect = &(pstHalPort->stOutCropRect);
#if 0
            if ((pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_DEI_LAST_2FIELD)
                || (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_DEI_LAST_2FIELD_VIRTUAL))
            {
                pstCropRect->s32Height = pstCropRect->s32Height / 2;
                pstCropRect->s32Y     = pstCropRect->s32Y / 2;
            }
#endif
            VPSS_PIXLE_DOWNALIGN_W(pstCropRect->s32Width, HI_TRUE);//w is 4pixel align for ZME(align4 limit)
            VPSS_PIXLE_DOWNALIGN_H(pstCropRect->s32Height, b4PixelClk);
            VPSS_PIXLE_DOWNALIGN_W(pstCropRect->s32X, HI_TRUE);
            VPSS_PIXLE_DOWNALIGN_H(pstCropRect->s32Y, b4PixelClk);

            stFuncCropCfg.stInRect.s32X     = pstCropRect->s32X;
            stFuncCropCfg.stInRect.s32Y     = pstCropRect->s32Y;
            stFuncCropCfg.stInRect.s32Width = pstCropRect->s32Width;
            stFuncCropCfg.stInRect.s32Height = pstCropRect->s32Height;
            stFuncCropCfg.stCropCfg = stFuncCropCfg.stInRect;
            stFuncCropCfg.bEnable = bAlgEnable;

            if (HI_TRUE == bVPZMEEnable)
            {
                stFuncCropCfg.stInRect.s32Y         /= 2;
                stFuncCropCfg.stInRect.s32Height    /= 2;
                stFuncCropCfg.stCropCfg.s32Height   /= 2;
                VPSS_PIXLE_DOWNALIGN_H(stFuncCropCfg.stCropCfg.s32Height, HI_FALSE);//2pixel align when 4p/c is disable
            }

            /*
                src:10bit dst:10bit-> disable crop , disable zme
                src:10bit dst:8bit -> cfg src as 8bit, enable crop , enable zme
                src:10bit dst:cst 10bit -> disable crop, disable zme, enable CTS[CTS10 Node]
            */
#ifdef VPSS_SUPPORT_AUTOASP
            if ((0 == stFuncCropCfg.stCropCfg.s32X)
                && (0 == stFuncCropCfg.stCropCfg.s32Y)
                && (stFuncCropCfg.stCropCfg.s32Width == pstInInfo->u32Width)
                && (stFuncCropCfg.stCropCfg.s32Height == pstInInfo->u32Height)
               )
            {
                stFuncCropCfg.bEnable = HI_FALSE;
            }
#endif
            VPSS_DBG_INFO("CROP(%d) X Y W H %d %d %d %d En:%d\n",
                          stFuncCropCfg.bEnable,
                          pstCropRect->s32X,
                          pstCropRect->s32Y,
                          pstCropRect->s32Width,
                          pstCropRect->s32Height,
                          stFuncCropCfg.bEnable);
            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_CROP, (HI_VOID *)&stFuncCropCfg, HI_NULL);

            /*ZME*/
            stFuncZmeCfg.u32ParAddr = stRegAddr.u32NodePhyAddr + 0x2000;
            stFuncZmeCfg.bEnable    = bAlgEnable;
            stFuncZmeCfg.eMode      = CBB_ZME_MODE_ALL;

            pstZmeDrvPara  = &(stFuncZmeCfg.stZmeDrvPara);
            memset(pstZmeDrvPara, 0, sizeof(HI_PQ_ZME_PARA_IN_S));
            pstZmeDrvPara->bZmeFrmFmtIn = 1;
            if (HI_TRUE == bVPZMEEnable)
            {
                pstZmeDrvPara->bZmeFrmFmtIn = 0; //field
            }
            pstZmeDrvPara->bZmeFrmFmtOut = 1;
            pstZmeDrvPara->bZmeBFIn = 0;
            pstZmeDrvPara->bZmeBFOut = 0;
            pstZmeDrvPara->u32PortID = u32PortId;
            pstZmeDrvPara->u32HandleNo = pstHalInfo->s32InstanceID;
            pstZmeDrvPara->enSceneMode = pstHalInfo->enSceneMode;
            pstZmeDrvPara->u8ZmeYCFmtIn = VPSS_HAL_TransPixelZMEFormat(pstInInfo->enFormat);
            pstZmeDrvPara->u8ZmeYCFmtOut = VPSS_HAL_TransPixelZMEFormat(pstHalPort->stOutInfo.enFormat);
            pstZmeDrvPara->u32ZmeFrmHIn = pstCropRect->s32Height;
            pstZmeDrvPara->u32ZmeFrmWIn = pstCropRect->s32Width;
            VPSS_PIXLE_UPALIGN_W(pstZmeDrvPara->u32ZmeFrmWIn, HI_TRUE);
            VPSS_PIXLE_UPALIGN_H(pstZmeDrvPara->u32ZmeFrmHIn, HI_FALSE);

            pstZmeDrvPara->u32ZmeFrmHOut = pstHalPort->stVideoRect.s32Height;
            pstZmeDrvPara->u32ZmeFrmWOut = pstHalPort->stVideoRect.s32Width;

            VPSS_PIXLE_UPALIGN_H(pstZmeDrvPara->u32ZmeFrmHOut, b4PixelClk);
            VPSS_PIXLE_UPALIGN_W(pstZmeDrvPara->u32ZmeFrmWOut, b4PixelClk);

            pstZmeDrvPara->stOriRect.s32X = 0;
            pstZmeDrvPara->stOriRect.s32Y = 0;
            pstZmeDrvPara->stOriRect.s32Width = pstInInfo->u32Width;
            pstZmeDrvPara->stOriRect.s32Height = pstInInfo->u32Height;
            if (HI_TRUE == bVPZMEEnable)
            {
                pstZmeDrvPara->stOriRect.s32Height = pstZmeDrvPara->stOriRect.s32Height / 2;
            }

#if 0
            if ((pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_DEI_LAST_2FIELD)
                || (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_DEI_LAST_2FIELD_VIRTUAL))
            {
                pstZmeDrvPara->stOriRect.s32Height = pstZmeDrvPara->stOriRect.s32Height / 2;
            }
#endif
            pstZmeDrvPara->u32InRate = 25000;
            pstZmeDrvPara->u32OutRate = 25000;
            pstZmeDrvPara->bDispProgressive = HI_TRUE;
            pstZmeDrvPara->u32Fidelity = 0;

            if (pstZmeDrvPara->u32ZmeFrmWOut > VPSS_ALG_ZME_W_MAX)
            {
                stFuncZmeCfg.bEnable = HI_FALSE;
            }

#ifdef VPSS_SUPPORT_AUTOASP
            if ((stFuncCropCfg.stCropCfg.s32Height == pstZmeDrvPara->u32ZmeFrmHOut)
                && (stFuncCropCfg.stCropCfg.s32Width == pstZmeDrvPara->u32ZmeFrmWOut)
                && (pstZmeDrvPara->u8ZmeYCFmtIn == pstZmeDrvPara->u8ZmeYCFmtOut))
            {
                stFuncZmeCfg.bEnable = HI_FALSE;
            }
#endif
            if ((VPSS_HAL_NODE_HDR_LC == pstHalInfo->enNodeType) && (HI_TRUE == b4PixelClk))
            {
                stFuncZmeCfg.bEnable    = HI_TRUE;
            }

            VPSS_DBG_INFO("zme(%d) in w h %d %d out w h %d %d ori w h %d %d\n",

                          stFuncZmeCfg.bEnable,
                          stFuncZmeCfg.stZmeDrvPara.u32ZmeFrmWIn,
                          stFuncZmeCfg.stZmeDrvPara.u32ZmeFrmHIn,
                          stFuncZmeCfg.stZmeDrvPara.u32ZmeFrmWOut,
                          stFuncZmeCfg.stZmeDrvPara.u32ZmeFrmHOut,
                          stFuncZmeCfg.stZmeDrvPara.stOriRect.s32Width,
                          stFuncZmeCfg.stZmeDrvPara.stOriRect.s32Height);

            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_ZME, (HI_VOID *)&stFuncZmeCfg, HI_NULL);

            /* LBX */
            stLBox.eBGColor          = pstHalPort->eLetterBoxColor;
            stLBox.stLBoxRect.s32X   = pstHalPort->stVideoRect.s32X;
            stLBox.stLBoxRect.s32Y   = pstHalPort->stVideoRect.s32Y;

            if (pstHalPort->bNeedRota)
            {
                stLBox.stLBoxRect.s32Height = pstOutFrm->u32Width;
                stLBox.stLBoxRect.s32Width  = pstOutFrm->u32Height;
                stLBox.stOutRect.s32Width   = pstOutFrm->u32Height;
                stLBox.stOutRect.s32Height  = pstOutFrm->u32Width;
            }
            else
            {
                stLBox.stLBoxRect.s32Height = pstOutFrm->u32Height;
                stLBox.stLBoxRect.s32Width  = pstOutFrm->u32Width;
                stLBox.stOutRect.s32Width   = pstOutFrm->u32Width;
                stLBox.stOutRect.s32Height  = pstOutFrm->u32Height;
            }

            stLBox.bEnable              = bAlgEnable;
#ifdef VPSS_SUPPORT_AUTOASP
            if ((0 == pstHalPort->stVideoRect.s32X)
                && (0 == pstHalPort->stVideoRect.s32Y)
               )
            {
                stLBox.bEnable = HI_FALSE;
            }
#endif
            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_LBOX, (HI_VOID *)&stLBox, HI_NULL);

            stFunc4PixelCfg.bEnable = b4PixelClk; //enable 4p/c to trans lsb2bit data
            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_SPEED_UP_4PIXEL, (HI_VOID *)&stFunc4PixelCfg, HI_NULL);


            if ((HI_FALSE == stFuncZmeCfg.bEnable)
                && (HI_FALSE == stLBox.bEnable))
            {

                VPSS_DBG_INFO(" use crop w h to vhd0 \n");

                //do not align up to 4pixel, equal to crop size
                pstOutFrm->u32Width  = stFuncCropCfg.stCropCfg.s32Width;
                pstOutFrm->u32Height = stFuncCropCfg.stCropCfg.s32Height;
            }

            /* vhd0 frame infomation */
            stFrmCfg.bEn = HI_TRUE;
            if (pstHalPort->bNeedRota)
            {
                stFrmCfg.u32Width   = pstOutFrm->u32Height;
                stFrmCfg.u32Height  = pstOutFrm->u32Width;
                pstOutAddr = &(pstHalPort->stFrmNodeRoBuf.stOutFrame.stBufAddr[HI_DRV_BUF_ADDR_LEFT]);
                pstOutAddr->u32Stride_Y = pstOutAddr->u32Stride_C = pstHalPort->stFrmNodeRoBuf.stBuffer.u32Stride;
            }
            else
            {
                stFrmCfg.u32Width   = pstOutFrm->u32Width;
                stFrmCfg.u32Height  = pstOutFrm->u32Height;
            }
            stFrmCfg.enBitWidth = pstOutFrm->enBitWidth;
            stFrmCfg.enPixelFmt = pstOutFrm->enFormat;
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstOutAddr->u32PhyAddr_Y;
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstOutAddr->u32PhyAddr_C;
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstOutAddr->u32Stride_Y;
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstOutAddr->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y   = HI_TRUE;
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C   = HI_TRUE;
#endif

            VPSS_DBG_INFO(
                "Vhd0 Y C StrideY StrideC W H %08x %08x %d %d %d %d bitw:%d\n",
                stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y,
                stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C,
                stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y,
                stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C,
                stFrmCfg.u32Width,
                stFrmCfg.u32Height,
                stFrmCfg.enBitWidth);

            if ((CBB_BITWIDTH_10BIT == stFrmCfg.enBitWidth)
                || (CBB_BITWIDTH_10BIT_CTS == stFrmCfg.enBitWidth))
            {
                stFrmCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_Y = pstOutFrm->stAddr_LB.u32PhyAddr_Y;
                stFrmCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_C = pstOutFrm->stAddr_LB.u32PhyAddr_C;
                stFrmCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_Y  = pstOutFrm->stAddr_LB.u32Stride_Y;
                stFrmCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_C  = pstOutFrm->stAddr_LB.u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
                stFrmCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y   = HI_TRUE;
                stFrmCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C   = HI_TRUE;
#endif
            }
            VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_WRITE_VHD0, (HI_VOID *)&stFrmCfg, HI_NULL);

            pstHalPort->bConfig = HI_TRUE;

            if (pstHalPort->bNeedRota)
            {
                pstHalPort->bConfig = HI_FALSE; //后面YC翻转的Node还要配置
            }

            if (VPSS_HAL_NODE_HDR_LC == pstHalInfo->enNodeType)
            {
                VPSS_HAL_SetHDRCfg_HDR10_2_SDR(enIP, stRegAddr, pstHalInfo);
            }

            break; //每次只处理一个port, Virtual port会再次调用
        }
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_SetPortCfg_Rota(CBB_REG_ADDR_S stRegAddr, VPSS_HAL_INFO_S *pstHalInfo,
                                HI_BOOL bRotateY, HI_U32 u32PortId)
{
    CBB_FRAME_S stFrmCfg;
    VPSS_HAL_PORT_INFO_S   *pstHalPort;
    HI_BOOL         bUVInver;
    CBB_FUNC_FLIP_S stFlipInfo;
    CBB_FUNC_CROP_S stFuncCropCfg;
    CBB_FUNC_ZME_S  stFuncZmeCfg;
    CBB_FUNC_LBOX_S stLBox;
    CBB_FUNC_ROTATION_YC_S stFuncRotatYCCfg;
    VPSS_HAL_FRAME_S       *pstOutFrm;
    HI_DRV_VID_FRAME_ADDR_S *pstOutAddr;
    HI_DRV_VPSS_ROTATION_E enRotation;
    HI_U32 u32Angle;
    HI_PQ_ZME_PARA_IN_S     *pstZmeDrvPara;
    VPSS_HAL_FRAME_S       *pstInInfo;
    HI_RECT_S      *pstCropRect;

    VPSS_MEM_CLEAR(stFrmCfg);
    VPSS_MEM_CLEAR(stFlipInfo);
    VPSS_MEM_CLEAR(stFuncCropCfg);
    VPSS_MEM_CLEAR(stFuncZmeCfg);
    VPSS_MEM_CLEAR(stLBox);

    //for (u32PortId = 0; u32PortId < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32PortId++)
    {
        pstHalPort = &pstHalInfo->astPortInfo[u32PortId];

        if (pstHalPort->bEnable) // && pstHalPort->bConfig == HI_FALSE)
        {
            pstOutFrm = &pstHalPort->stOutInfo;
            pstOutAddr = &pstOutFrm->stAddr;


            VPSS_PIXLE_UPALIGN_W(pstOutFrm->u32Width, HI_FALSE);
            VPSS_PIXLE_UPALIGN_H(pstOutFrm->u32Height, HI_FALSE);


            /* 旋转配置 */
            enRotation = pstHalInfo->astPortInfo[u32PortId].enRotation;

            switch (enRotation)
            {
                case HI_DRV_VPSS_ROTATION_90:
                    u32Angle = 0x0;
                    break;

                case HI_DRV_VPSS_ROTATION_270:
                    u32Angle = 0x1;
                    break;

                default:
                    u32Angle = 0x1;
                    VPSS_ERROR("Rota Error %d\n", u32Angle);
                    break;
            }

            stFuncRotatYCCfg.bEnable = HI_TRUE;
            stFuncRotatYCCfg.u32Angle = u32Angle;

            if (bRotateY)
            {
                stFuncRotatYCCfg.u32ImgProcessMode = 1;
                VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_ROTATION_Y, (HI_VOID *)&stFuncRotatYCCfg, HI_NULL);
            }
            else
            {
                stFuncRotatYCCfg.u32ImgProcessMode = 2;
                VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_ROTATION_C, (HI_VOID *)&stFuncRotatYCCfg, HI_NULL);
            }

            /* Flip&Mirro */
            stFlipInfo.bFlipH = HI_FALSE;
            stFlipInfo.bFlipV = HI_FALSE;
            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_FLIP, (HI_VOID *)&stFlipInfo, HI_NULL);

            /* UV反转 */
            bUVInver = HI_FALSE;
            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_UV, (HI_VOID *)&bUVInver, HI_NULL);

            /* VHD0's Crop */
            pstCropRect = &(pstHalPort->stOutCropRect);
            VPSS_PIXLE_DOWNALIGN_W(pstCropRect->s32Width, HI_TRUE);  //4pixel align, whatever 4p/c is enable or not
            VPSS_PIXLE_DOWNALIGN_H(pstCropRect->s32Height, HI_FALSE);//2pixel align when 4p/c is disable

            stFuncCropCfg.stInRect.s32X     = pstCropRect->s32X;
            stFuncCropCfg.stInRect.s32Y     = pstCropRect->s32Y;
            stFuncCropCfg.stInRect.s32Width = pstCropRect->s32Width;
            stFuncCropCfg.stInRect.s32Height    = pstCropRect->s32Height;
            stFuncCropCfg.stCropCfg = stFuncCropCfg.stInRect;
            stFuncCropCfg.bEnable = HI_FALSE;
            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_CROP, (HI_VOID *)&stFuncCropCfg, HI_NULL);

            /*ZME*/
            stFuncZmeCfg.u32ParAddr = stRegAddr.u32NodePhyAddr + 0x2000;
            stFuncZmeCfg.bEnable    = HI_FALSE;
            stFuncZmeCfg.eMode      = CBB_ZME_MODE_ALL;

            pstZmeDrvPara  = &(stFuncZmeCfg.stZmeDrvPara);
            memset(pstZmeDrvPara, 0, sizeof(HI_PQ_ZME_PARA_IN_S));
            pstZmeDrvPara->bZmeFrmFmtIn = 1;
            pstZmeDrvPara->bZmeFrmFmtOut = 1;
            pstZmeDrvPara->bZmeBFIn = 0;
            pstZmeDrvPara->bZmeBFOut = 0;
            pstZmeDrvPara->u32HandleNo = pstHalInfo->s32InstanceID;
            pstZmeDrvPara->enSceneMode = pstHalInfo->enSceneMode;
            pstInInfo = &(pstHalInfo->stInInfo);
            pstZmeDrvPara->u8ZmeYCFmtIn = VPSS_HAL_TransPixelZMEFormat(pstInInfo->enFormat);
            pstZmeDrvPara->u8ZmeYCFmtOut = VPSS_HAL_TransPixelZMEFormat(pstHalPort->stOutInfo.enFormat);

            if (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_FIELD)
            {
                pstZmeDrvPara->u32ZmeFrmHIn = (pstCropRect->s32Height / 2);
                pstZmeDrvPara->u32ZmeFrmWIn = pstCropRect->s32Width;

                VPSS_PIXLE_UPALIGN_W(pstZmeDrvPara->u32ZmeFrmWIn, HI_FALSE);
                VPSS_PIXLE_UPALIGN_H(pstZmeDrvPara->u32ZmeFrmHIn, HI_FALSE);
            }
            else
            {
                //ZME's input height/width is VHD0 Crop's output
                pstZmeDrvPara->u32ZmeFrmHIn = pstCropRect->s32Width;
                pstZmeDrvPara->u32ZmeFrmWIn = pstCropRect->s32Height;
            }

            pstZmeDrvPara->u32ZmeFrmHOut = pstHalPort->stVideoRect.s32Height;
            pstZmeDrvPara->u32ZmeFrmWOut = pstHalPort->stVideoRect.s32Width;
            pstZmeDrvPara->stOriRect.s32X = 0;
            pstZmeDrvPara->stOriRect.s32Y = 0;
            pstZmeDrvPara->stOriRect.s32Width = pstHalInfo->stInInfo.u32Height;
            pstZmeDrvPara->stOriRect.s32Height = pstHalInfo->stInInfo.u32Width;
            pstZmeDrvPara->u32InRate = 25000;
            pstZmeDrvPara->u32OutRate = 25000;
            pstZmeDrvPara->bDispProgressive = HI_TRUE;
            pstZmeDrvPara->u32Fidelity = 0;
            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_ZME, (HI_VOID *)&stFuncZmeCfg, HI_NULL);

            /* LBX */
            stLBox.eBGColor          = pstHalPort->eLetterBoxColor;
            stLBox.stLBoxRect.s32X   = pstHalPort->stVideoRect.s32X;
            stLBox.stLBoxRect.s32Y   = pstHalPort->stVideoRect.s32Y;
            stLBox.stLBoxRect.s32Height = pstOutFrm->u32Height;
            stLBox.stLBoxRect.s32Width = pstOutFrm->u32Width;
            stLBox.stOutRect.s32Width    = pstOutFrm->u32Width;
            stLBox.stOutRect.s32Height  = pstOutFrm->u32Height;
            stLBox.bEnable           = HI_FALSE;

            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_LBOX, (HI_VOID *)&stLBox, HI_NULL);

            /* vhd0 frame infomation */
            stFrmCfg.bEn        = HI_TRUE;
            stFrmCfg.u32Width   = pstHalPort->stOutInfo.u32Width;
            stFrmCfg.u32Height  = pstHalPort->stOutInfo.u32Height;

            stFrmCfg.enBitWidth = pstHalPort->stOutInfo.enBitWidth;
            stFrmCfg.enPixelFmt = pstHalPort->stOutInfo.enFormat;
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstHalPort->stOutInfo.stAddr.u32PhyAddr_Y;
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstHalPort->stOutInfo.stAddr.u32PhyAddr_C;
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstHalPort->stOutInfo.stAddr.u32Stride_Y;
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstHalPort->stOutInfo.stAddr.u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y   = HI_TRUE;
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C   = HI_TRUE;
#endif

            if (CBB_BITWIDTH_10BIT == stFrmCfg.enBitWidth)//judge by output bitwidth
            {
                stFrmCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_Y = pstHalPort->stOutInfo.stAddr_LB.u32PhyAddr_Y;
                stFrmCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_C = pstHalPort->stOutInfo.stAddr_LB.u32PhyAddr_C;
                stFrmCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_Y  = pstHalPort->stOutInfo.stAddr_LB.u32Stride_Y;
                stFrmCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_C  = pstHalPort->stOutInfo.stAddr_LB.u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
                stFrmCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y   = HI_TRUE;
                stFrmCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C   = HI_TRUE;
#endif
            }

            VPSS_DBG_INFO("RotaNode vhd0 save to %08x %08x %d %d\n",
                          stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y,
                          stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C,
                          stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y,
                          stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C);

            VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_WRITE_VHD0, (HI_VOID *)&stFrmCfg, HI_NULL);

            pstHalPort->bConfig = HI_TRUE;

            // break; //每次只处理一个port
        }
    }

    return HI_SUCCESS;
}


HI_S32 VPSS_HAL_SetPortCfg_CTS10Bit(CBB_REG_ADDR_S stRegAddr, VPSS_HAL_INFO_S *pstHalInfo)
{
    CBB_FRAME_S stFrmCfg;
    VPSS_HAL_PORT_INFO_S   *pstHalPort;
    HI_U32          u32PortId;
    HI_BOOL         bUVInver;
    CBB_FUNC_FLIP_S stFlipInfo;
    CBB_FUNC_CROP_S stFuncCropCfg;
    CBB_FUNC_ZME_S  stFuncZmeCfg;
    CBB_FUNC_LBOX_S stLBox;
    HI_RECT_S      *pstCropRect;
    HI_PQ_ZME_PARA_IN_S     *pstZmeDrvPara;
    VPSS_HAL_FRAME_S       *pstInInfo;
    VPSS_HAL_FRAME_S       *pstOutFrm;
    HI_DRV_VID_FRAME_ADDR_S *pstOutAddr;
    //VPSS_HAL_PORT_INFO_S  stPortTemp;


    VPSS_MEM_CLEAR(stFrmCfg);
    VPSS_MEM_CLEAR(stFlipInfo);
    VPSS_MEM_CLEAR(stFuncCropCfg);
    VPSS_MEM_CLEAR(stFuncZmeCfg);
    VPSS_MEM_CLEAR(stLBox);

    for (u32PortId = 0; u32PortId < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32PortId++)
    {
        pstHalPort = &pstHalInfo->astPortInfo[u32PortId];

        if (pstHalPort->bEnable && pstHalPort->bConfig == HI_FALSE)
        {
            pstOutFrm = &pstHalPort->stOutInfo;
            pstOutAddr = &pstOutFrm->stAddr;

            VPSS_PIXLE_UPALIGN_W(pstOutFrm->u32Width, HI_TRUE);
            VPSS_PIXLE_UPALIGN_H(pstOutFrm->u32Height, HI_TRUE);


            /* Flip&Mirro */
            stFlipInfo.bFlipH = HI_FALSE;
            stFlipInfo.bFlipV = HI_FALSE;
            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_FLIP, (HI_VOID *)&stFlipInfo, HI_NULL);

            /* UV反转 */
            bUVInver = HI_FALSE;
            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_UV, (HI_VOID *)&bUVInver, HI_NULL);

            /* VHD0's Crop */
            pstCropRect = &(pstHalPort->stOutCropRect);
            VPSS_PIXLE_DOWNALIGN_W(pstCropRect->s32Width, HI_TRUE);  //4pixel align, whatever 4p/c is enable or not
            VPSS_PIXLE_DOWNALIGN_H(pstCropRect->s32Height, HI_TRUE);//4p/c is enable

            stFuncCropCfg.stInRect.s32X     = pstCropRect->s32X;
            stFuncCropCfg.stInRect.s32Y     = pstCropRect->s32Y;
            stFuncCropCfg.stInRect.s32Width = pstCropRect->s32Width;
            stFuncCropCfg.stInRect.s32Height = pstCropRect->s32Height;
            stFuncCropCfg.stCropCfg = stFuncCropCfg.stInRect;
            stFuncCropCfg.bEnable = HI_FALSE;
            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_CROP, (HI_VOID *)&stFuncCropCfg, HI_NULL);

            /*ZME*/
            stFuncZmeCfg.u32ParAddr = stRegAddr.u32NodePhyAddr + 0x2000;
            stFuncZmeCfg.bEnable    = HI_FALSE;
            stFuncZmeCfg.eMode      = CBB_ZME_MODE_ALL;

            pstZmeDrvPara  = &(stFuncZmeCfg.stZmeDrvPara);
            memset(pstZmeDrvPara, 0, sizeof(HI_PQ_ZME_PARA_IN_S));
            pstZmeDrvPara->bZmeFrmFmtIn = 1;
            pstZmeDrvPara->bZmeFrmFmtOut = 1;
            pstZmeDrvPara->bZmeBFIn = 0;
            pstZmeDrvPara->bZmeBFOut = 0;
            pstZmeDrvPara->u32HandleNo = pstHalInfo->s32InstanceID;
            pstZmeDrvPara->enSceneMode = pstHalInfo->enSceneMode;
            pstInInfo = &(pstHalInfo->stInInfo);
            pstZmeDrvPara->u8ZmeYCFmtIn = VPSS_HAL_TransPixelZMEFormat(pstInInfo->enFormat);
            pstZmeDrvPara->u8ZmeYCFmtOut = VPSS_HAL_TransPixelZMEFormat(pstHalPort->stOutInfo.enFormat);

            //ZME's input height/width is VHD0 Crop's output
            pstZmeDrvPara->u32ZmeFrmHIn = pstCropRect->s32Height;
            pstZmeDrvPara->u32ZmeFrmWIn = pstCropRect->s32Width;

            if (pstHalPort->bNeedRota)
            {
                pstZmeDrvPara->u32ZmeFrmHOut = pstHalPort->stVideoRect.s32Width;
                pstZmeDrvPara->u32ZmeFrmWOut = pstHalPort->stVideoRect.s32Height;
            }
            else
            {
                pstZmeDrvPara->u32ZmeFrmHOut = pstHalPort->stVideoRect.s32Height;
                pstZmeDrvPara->u32ZmeFrmWOut = pstHalPort->stVideoRect.s32Width;
            }

            pstZmeDrvPara->stOriRect.s32X = 0;
            pstZmeDrvPara->stOriRect.s32Y = 0;
            pstZmeDrvPara->stOriRect.s32Width = pstHalInfo->stInInfo.u32Width;
            pstZmeDrvPara->stOriRect.s32Height = pstHalInfo->stInInfo.u32Height;
            pstZmeDrvPara->u32InRate = 25000;
            pstZmeDrvPara->u32OutRate = 25000;
            pstZmeDrvPara->bDispProgressive = HI_TRUE;
            pstZmeDrvPara->u32Fidelity = 0;

            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_ZME, (HI_VOID *)&stFuncZmeCfg, HI_NULL);

            /* LBX */
            stLBox.eBGColor          = pstHalPort->eLetterBoxColor;
            stLBox.stLBoxRect.s32X   = pstHalPort->stVideoRect.s32X;
            stLBox.stLBoxRect.s32Y   = pstHalPort->stVideoRect.s32Y;

            stLBox.stLBoxRect.s32Height = pstOutFrm->u32Height;
            stLBox.stLBoxRect.s32Width  = pstOutFrm->u32Width;
            stLBox.stOutRect.s32Width   = pstOutFrm->u32Width;
            stLBox.stOutRect.s32Height  = pstOutFrm->u32Height;
            stLBox.bEnable              = HI_FALSE;
            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_LBOX, (HI_VOID *)&stLBox, HI_NULL);
            stFrmCfg.bEn        = HI_TRUE;
            stFrmCfg.u32Width   = pstOutFrm->u32Width;
            stFrmCfg.u32Height  = pstOutFrm->u32Height;

            stFrmCfg.enBitWidth = pstOutFrm->enBitWidth;
            stFrmCfg.enPixelFmt = pstOutFrm->enFormat;
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstOutAddr->u32PhyAddr_Y;
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstOutAddr->u32PhyAddr_C;
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstOutAddr->u32Stride_Y;
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstOutAddr->u32Stride_C;

            VPSS_DBG_INFO(

                "2DNode vhd0 save to Y C StrideY StrideY %08x %08x %d %d\n",
                stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y,
                stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C,
                stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y,
                stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C);

            if ((CBB_BITWIDTH_10BIT == stFrmCfg.enBitWidth)
                || (CBB_BITWIDTH_10BIT_CTS == stFrmCfg.enBitWidth))
            {
                stFrmCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_Y = pstOutFrm->stAddr_LB.u32PhyAddr_Y;
                stFrmCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_C = pstOutFrm->stAddr_LB.u32PhyAddr_C;
                stFrmCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_Y  = pstOutFrm->stAddr_LB.u32Stride_Y;
                stFrmCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_C  = pstOutFrm->stAddr_LB.u32Stride_C;
            }

            VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_WRITE_VHD0, (HI_VOID *)&stFrmCfg, HI_NULL);

            pstHalPort->bConfig = HI_TRUE;

            if (pstHalPort->bNeedRota)
            {
                pstHalPort->bConfig = HI_FALSE;
            }

            break; //每次只处理一个port
        }
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_SetPortCfg_SD_First_dei(VPSS_IP_E enIP,  CBB_REG_ADDR_S stRegAddr, VPSS_HAL_INFO_S *pstHalInfo)
{
    CBB_FRAME_S stFrmCfg;
    VPSS_HAL_PORT_INFO_S   *pstHalPort;
    HI_U32          u32PortId;
    HI_BOOL         bUVInver;
    CBB_FUNC_FLIP_S stFlipInfo;
    CBB_FUNC_CROP_S stFuncCropCfg;
    CBB_FUNC_ZME_S  stFuncZmeCfg;
    CBB_FUNC_LBOX_S stLBox;
    HI_RECT_S      *pstCropRect;
    HI_PQ_ZME_PARA_IN_S     *pstZmeDrvPara;
    VPSS_HAL_FRAME_S       *pstInInfo;
    VPSS_HAL_FRAME_S       *pstOutFrm;
    HI_DRV_VID_FRAME_ADDR_S *pstOutAddr;
    HI_DRV_VID_FRAME_ADDR_S *pstOutAddr_LB;

    VPSS_MEM_CLEAR(stFrmCfg);
    VPSS_MEM_CLEAR(stFlipInfo);
    VPSS_MEM_CLEAR(stFuncCropCfg);
    VPSS_MEM_CLEAR(stFuncZmeCfg);
    VPSS_MEM_CLEAR(stLBox);

    for (u32PortId = 0; u32PortId < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32PortId++)
    {
        pstHalPort = &pstHalInfo->astPortInfo[u32PortId];

        if (pstHalPort->bEnable && pstHalPort->bConfig == HI_FALSE)
        {
            pstOutFrm = &pstHalPort->stOutInfo;
            //pstOutAddr = &pstOutFrm->stAddr;
            pstOutAddr = &(pstHalInfo->stSDDeiFrame.stAddr);
            pstOutAddr_LB = &(pstHalInfo->stSDDeiFrame.stAddr_LB);

            VPSS_PIXLE_UPALIGN_W(pstOutFrm->u32Width, HI_FALSE);
            VPSS_PIXLE_UPALIGN_H(pstOutFrm->u32Height, HI_FALSE);


            /* Flip&Mirro */
            stFlipInfo.bFlipH = HI_FALSE;
            stFlipInfo.bFlipV = HI_FALSE;
            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_FLIP, (HI_VOID *)&stFlipInfo, HI_NULL);

            /* UV反转 */
            bUVInver = HI_FALSE;
            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_UV, (HI_VOID *)&bUVInver, HI_NULL);

            /* VHD0's Crop */
            pstCropRect = &(pstHalPort->stOutCropRect);
            VPSS_PIXLE_DOWNALIGN_W(pstCropRect->s32Width, HI_TRUE);  //4pixel align, whatever 4p/c is enable or not
            VPSS_PIXLE_DOWNALIGN_H(pstCropRect->s32Height, HI_FALSE);//2pixel align when 4p/c is disable

            stFuncCropCfg.stInRect.s32X     = pstCropRect->s32X;
            stFuncCropCfg.stInRect.s32Y     = pstCropRect->s32Y;
            stFuncCropCfg.stInRect.s32Width = pstCropRect->s32Width;
            stFuncCropCfg.stInRect.s32Height    = pstCropRect->s32Height;
            stFuncCropCfg.stCropCfg = stFuncCropCfg.stInRect;

            stFuncCropCfg.bEnable = HI_FALSE;
            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_CROP, (HI_VOID *)&stFuncCropCfg, HI_NULL);

            /*ZME*/
            stFuncZmeCfg.u32ParAddr = stRegAddr.u32NodePhyAddr + 0x2000;
            stFuncZmeCfg.bEnable    = HI_FALSE;
            stFuncZmeCfg.eMode      = CBB_ZME_MODE_ALL;

            pstZmeDrvPara  = &(stFuncZmeCfg.stZmeDrvPara);
            memset(pstZmeDrvPara, 0, sizeof(HI_PQ_ZME_PARA_IN_S));
            pstZmeDrvPara->bZmeFrmFmtIn = 1;
            pstZmeDrvPara->bZmeFrmFmtOut = 1;
            pstZmeDrvPara->bZmeBFIn = 0;
            pstZmeDrvPara->bZmeBFOut = 0;
            pstZmeDrvPara->u32HandleNo = pstHalInfo->s32InstanceID;
            pstZmeDrvPara->enSceneMode = pstHalInfo->enSceneMode;
            pstInInfo = &(pstHalInfo->stInInfo);
            pstZmeDrvPara->u8ZmeYCFmtIn = VPSS_HAL_TransPixelZMEFormat(pstInInfo->enFormat);
            pstZmeDrvPara->u8ZmeYCFmtOut = VPSS_HAL_TransPixelZMEFormat(pstHalPort->stOutInfo.enFormat);

            //ZME's input height/width is VHD0 Crop's output
            pstZmeDrvPara->u32ZmeFrmHIn = pstCropRect->s32Height;
            pstZmeDrvPara->u32ZmeFrmWIn = pstCropRect->s32Width;
            pstZmeDrvPara->u32ZmeFrmHOut = pstHalPort->stVideoRect.s32Height;
            pstZmeDrvPara->u32ZmeFrmWOut = pstHalPort->stVideoRect.s32Width;

            pstZmeDrvPara->stOriRect.s32X = 0;
            pstZmeDrvPara->stOriRect.s32Y = 0;
            pstZmeDrvPara->stOriRect.s32Width = pstHalInfo->stInInfo.u32Width;
            pstZmeDrvPara->stOriRect.s32Height = pstHalInfo->stInInfo.u32Height;
            pstZmeDrvPara->u32InRate = 25000;
            pstZmeDrvPara->u32OutRate = 25000;
            pstZmeDrvPara->bDispProgressive = HI_TRUE;
            pstZmeDrvPara->u32Fidelity = 0;

            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_ZME, (HI_VOID *)&stFuncZmeCfg, HI_NULL);

            /* LBX */
            stLBox.eBGColor          = pstHalPort->eLetterBoxColor;
            stLBox.stLBoxRect.s32X   = pstHalPort->stVideoRect.s32X;
            stLBox.stLBoxRect.s32Y   = pstHalPort->stVideoRect.s32Y;
            stLBox.stLBoxRect.s32Height = pstOutFrm->u32Height;
            stLBox.stLBoxRect.s32Width = pstOutFrm->u32Width;
            stLBox.stOutRect.s32Width    = pstOutFrm->u32Width;
            stLBox.stOutRect.s32Height  = pstOutFrm->u32Height;
            stLBox.bEnable           = HI_FALSE;

            VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_LBOX, (HI_VOID *)&stLBox, HI_NULL);

            /* vhd0 frame infomation */
            // first node use w h same as input image w h. because zme/crop is disable
            stFrmCfg.bEn        = HI_TRUE;
            stFrmCfg.u32Width   = pstInInfo->u32Width ;
            stFrmCfg.u32Height  = pstInInfo->u32Height / 2;

            VPSS_PIXLE_UPALIGN_W(stFrmCfg.u32Width, HI_FALSE);
            VPSS_PIXLE_UPALIGN_H(stFrmCfg.u32Height, HI_FALSE);
            stFrmCfg.enBitWidth = pstHalInfo->stSDDeiFrame.enBitWidth;
            stFrmCfg.enPixelFmt = pstHalInfo->stSDDeiFrame.enFormat;
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstOutAddr->u32PhyAddr_Y;
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstOutAddr->u32PhyAddr_C;
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstOutAddr->u32Stride_Y;
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstOutAddr->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y   = HI_TRUE;
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C   = HI_TRUE;
#endif
            if (CBB_BITWIDTH_10BIT == stFrmCfg.enBitWidth)//judge by output bitwidth
            {
                stFrmCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_Y = pstOutAddr_LB->u32PhyAddr_Y;
                stFrmCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_C = pstOutAddr_LB->u32PhyAddr_C;
                stFrmCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_Y  = pstOutAddr_LB->u32Stride_Y;
                stFrmCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_C  = pstOutAddr_LB->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
                stFrmCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y   = HI_TRUE;
                stFrmCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C   = HI_TRUE;
#endif
            }

            VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_WRITE_VHD0, (HI_VOID *)&stFrmCfg, HI_NULL);

            //pstHalPort->bConfig = HI_TRUE; sd-dei-second node use
            break; //每次只处理一个port
        }
    }

    return HI_SUCCESS;
}

/*
HI_BOOL bYdata, 亮度或色度标识, 1:亮度, 0色度
HI_BOOL bField, 场,帧标志, 0:帧, 1:场
*/
HI_S32 VPSS_HAL_Get_RwzbPixel(HI_U8 *pu8PixelBaseAddr_vir,
                              VPSS_RWZB_INFO_S *pstRwzbInfo, HI_U32 u32YCMode, HI_BOOL bField)
{
    HI_U32 ii;
    HI_U32 jj;
    HI_U32 u32_blk_xpos;
    HI_U32 u32_blk_ypos;
    HI_U32 u32HeightTmp;

    if ((HI_NULL == pu8PixelBaseAddr_vir) || (HI_NULL == pstRwzbInfo))
    {
        VPSS_ERROR("VPSS get rwzb with null pointer(nx2)!\n");
        return HI_FAILURE;
    }


    u32HeightTmp = pstRwzbInfo->u32Height;

    for (ii = 0; ii < 6; ii++)
    {
        u32_blk_xpos = (pstRwzbInfo->u32Addr)[ii][0] << 3;
        u32_blk_ypos = (pstRwzbInfo->u32Addr)[ii][1] << 3;

        if (HI_TRUE == bField)
        {
            u32_blk_ypos = u32_blk_ypos / 2;
            u32HeightTmp = pstRwzbInfo->u32Height / 2;
        }

        if ((u32_blk_xpos < pstRwzbInfo->u32Width)
            && (u32_blk_ypos < u32HeightTmp))
        {
            if (0 == u32YCMode) //亮度
            {
                for (jj = 0; jj < 8; jj++)
                {
                    pstRwzbInfo->u8Data[ii][jj] =
                        *(pu8PixelBaseAddr_vir + ((u32_blk_ypos * pstRwzbInfo->u32Width) + u32_blk_xpos) + jj); //8bit
                }
            }
        }
        else
        {
            return HI_VPSS_RET_UNSUPPORT;
        }
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_GetDetPixel(HI_U8 *pDstData, HI_U8 *pSrcData)
{
    VPSS_SAFE_MEMCPY(pDstData, pSrcData, sizeof(HI_U8)*PIX_NUM_IN_PATTERN);

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_RWZB_Calc(VPSS_HAL_INFO_S *pstHalInfo, HI_DRV_VID_FRAME_ADDR_S *pstNext2)
{
    HI_U8 *pvir_addr_y = HI_NULL;
    HI_U8 *pvir_addr_y_header = HI_NULL;
    HI_BOOL bCmpInput;
    HI_S32 s32Ret;

    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_CMP)

    {
        bCmpInput = HI_TRUE;
    }
    else if ((pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21)
             || (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12)
             || (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE)
             || (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE))
    {
        bCmpInput = HI_FALSE;
    }
    else
    {
        return HI_FAILURE;//unsupport format
    }
    pstHalInfo->stRwzbInfo.u32Width = pstNext2->u32Stride_Y; //下面软件访问像素点时,要按照stride计算偏移

    if (HI_NULL == pstNext2->vir_addr_y)
    {
        if (bCmpInput)
        {
            pvir_addr_y_header = VPSS_OSAL_MEMMap(pstHalInfo->stInInfo.bSecure, pstNext2->u32PhyAddr_YHead);
            pvir_addr_y        = pvir_addr_y_header + pstNext2->u32Head_Size;
        }
        else
        {
            pvir_addr_y = VPSS_OSAL_MEMMap(pstHalInfo->stInInfo.bSecure, pstNext2->u32PhyAddr_Y);
            pvir_addr_y_header =  pvir_addr_y;
        }

        if (HI_NULL != pvir_addr_y_header)
        {
            s32Ret = VPSS_HAL_Get_RwzbPixel(pvir_addr_y, &pstHalInfo->stRwzbInfo, pstHalInfo->stRwzbInfo.u32Mode,
                                            (HI_FALSE == pstHalInfo->stInInfo.bProgressive));
            s32Ret |= VPSS_OSAL_MEMUnmap(pstHalInfo->stInInfo.bSecure,
                                         pstNext2->u32PhyAddr_Y, pvir_addr_y_header);

            if ((HI_SUCCESS != s32Ret) && (HI_VPSS_RET_UNSUPPORT != s32Ret))
            {
                VPSS_ERROR("VPSS_HAL_Get_RwzbPixel fail!\n");
                return HI_FAILURE;
            }
        }
        else
        {
            VPSS_ERROR("Nx2 phyaddr map to viraddr fail!\n");
            return HI_FAILURE;
        }
    }
    else
    {
        pvir_addr_y = (HI_U8 *)(HI_SIZE_T)pstNext2->vir_addr_y;
        s32Ret = VPSS_HAL_Get_RwzbPixel(pvir_addr_y, &pstHalInfo->stRwzbInfo, pstHalInfo->stRwzbInfo.u32Mode, (HI_FALSE == pstHalInfo->stInInfo.bProgressive));
        if ((HI_SUCCESS != s32Ret) && (HI_VPSS_RET_UNSUPPORT != s32Ret))
        {
            VPSS_ERROR("VPSS_HAL_Get_RwzbPixel fail!\n");
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}
#ifdef VPSS_SUPPORT_OUT_TUNNEL
HI_S32 VPSS_HAL_TunnelOut_GetBufAddr(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 u32PortID)
{
    HI_U32          u32WriteAddr;

    if (enIP >= VPSS_IP_BUTT)
    {
        VPSS_ERROR("VPSS IP%d, is Not Vaild\n", enIP);
        return HI_NULL;
    }

#ifdef HI_VPSS_SUPPORT_OUTTUNNEL_SMMU
    //Always pass MMZ addr to VENC
    u32WriteAddr = VPSS_OSAL_SmmuToPhyAddr(pstHalInfo->stLowDelayBuf_MMU.u32StartSmmuAddr);
#else
    u32WriteAddr = pstHalInfo->stLowDelayBuf_MMZ.u32StartPhyAddr;
#endif

    return u32WriteAddr;
}
#endif


//NODE configuration
//VPSS_HAL_NODE_2D_FRAME = 0,    //2D逐行
HI_S32 VPSS_HAL_Set_2DFrame_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy)
{
    HI_DRV_VID_FRAME_ADDR_S *pstNext2;
    HI_DRV_VID_FRAME_ADDR_S *pstNext2_LB;
    HI_DRV_VID_FRAME_ADDR_S *pstCur;
    HI_DRV_VID_FRAME_ADDR_S *pstRfr;
    //  HI_DRV_VID_FRAME_ADDR_S *pstRef;

    HI_BOOL bRfrEnableFlag;
    HI_U32 u32PageAddr;
    HI_U32 u32ErrReadAddr;
    HI_U32 u32ErrWriteAddr;

    CBB_REG_ADDR_S      stRegAddr;
    CBB_REG_ADDR_S      stRegAddr_MMU;
    CBB_FRAME_S         stFrameCfg;
    CBB_FUNC_TUNNELIN_S stTunnelIn;
    CBB_FUNC_SMMU_S     stSMMUCfg;
    CBB_INFO_S          stMadInfo_Tnr;
    CBB_INFO_S          stMadInfo_Snr;
    CBB_ALG_INFO_S      stDBInfo;
    CBB_ALG_INFO_S      stDBDETInfo;
    CBB_ALG_INFO_S      stNrInfo;
    CBB_ALG_INFO_S      stSnrInfo;
    CBB_ALG_INFO_S      stTnrInfo;
    CBB_ALG_INFO_S      stMcTnrInfo;
    CBB_ALG_INFO_S      stIfmdInfo;
    CBB_ALG_INFO_S      stHdrInfo;
    CBB_ALG_INFO_S      stAlgInfo;
    CBB_INFO_S          sttInfoCfg;

    VPSS_MEM_CLEAR(stRegAddr);
    VPSS_MEM_CLEAR(stRegAddr_MMU);
    VPSS_MEM_CLEAR(stFrameCfg);
    VPSS_MEM_CLEAR(stTunnelIn);
    VPSS_MEM_CLEAR(stSMMUCfg);
    VPSS_MEM_CLEAR(stMadInfo_Tnr);
    VPSS_MEM_CLEAR(stMadInfo_Snr);
    VPSS_MEM_CLEAR(stDBInfo);
    VPSS_MEM_CLEAR(stDBDETInfo);
    VPSS_MEM_CLEAR(stNrInfo);
    VPSS_MEM_CLEAR(stSnrInfo);
    VPSS_MEM_CLEAR(stTnrInfo);
    VPSS_MEM_CLEAR(stMcTnrInfo);
    VPSS_MEM_CLEAR(stIfmdInfo);
    VPSS_MEM_CLEAR(sttInfoCfg);
    VPSS_MEM_CLEAR(stHdrInfo);
    VPSS_MEM_CLEAR(stAlgInfo);

    stRegAddr.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr.u32NodePhyAddr = u32AppPhy;

    VPSS_REG_ResetAppReg((S_VPSS_REGS_TYPE *)pu32AppVir, pstHalInfo->pstPqCfg);

    /*tunnel*/
    if (pstHalInfo->stInInfo.u32TunnelAddr)
    {
        stTunnelIn.bEnable = HI_TRUE;
        //        stTunnelIn.bSmmu   = pstHalInfo->stInInfo.bTunlSmmu;
#ifdef HI_VPSS_SMMU_SUPPORT
        stTunnelIn.bSmmu = HI_TRUE;
#else
        stTunnelIn.bSmmu = HI_FALSE;
#endif

        stTunnelIn.u32ReadInterval = 0;
        stTunnelIn.u32ReadAddr = pstHalInfo->stInInfo.u32TunnelAddr;
    }
    else
    {
        stTunnelIn.bEnable = HI_FALSE;
    }
    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_TUNNEL_IN, (HI_VOID *)&stTunnelIn, HI_NULL);

    stDBDETInfo.bEnable = HI_FALSE;
    stDBInfo.bEnable    = HI_FALSE;
    stNrInfo.bEnable    = HI_FALSE;
    stSnrInfo.bEnable   = HI_FALSE;
    stTnrInfo.bEnable   = HI_TRUE;

    if (VPSS_IS_YUV422_FMT(pstHalInfo->stInInfo.enFormat))
    {
        stDBDETInfo.bEnable = HI_FALSE;
        stDBInfo.bEnable    = HI_FALSE;
        stSnrInfo.bEnable   = HI_FALSE;
    }

#ifdef VPSS_SUPPORT_ALG_MCNR
    if (VPSS_ALG_IS_MCNR_ENABLE(pstHalInfo->stInInfo.u32Width, pstHalInfo->stInInfo.u32Height)
        || pstHalInfo->bSplitEnable)
    {
        stMcTnrInfo.bEnable = HI_TRUE;
    }
    else
    {
        stMcTnrInfo.bEnable = HI_FALSE;
    }
#else
    stMcTnrInfo.bEnable = HI_FALSE;
#endif


    bRfrEnableFlag      = HI_TRUE;
    //snr_en 是db,dm, nr的总开关， SNR包括db,dm,nr

    if (VPSS_HAL_IS_RWZB(pstHalInfo->stRwzbInfo.u32IsRwzb))
    {
        stSnrInfo.bEnable   = HI_FALSE;
        stTnrInfo.bEnable   = HI_FALSE;
    }

    if (0x0 != (pstHalInfo->stInInfo.u32Width & 0x3))
    {
        stTnrInfo.bEnable   = HI_FALSE;
    }
    if ( HI_DRV_PIXEL_BITWIDTH_10BIT == pstHalInfo->stInInfo.enBitWidth )
    {
        stTnrInfo.bEnable = HI_FALSE;
    }

    if (HI_FALSE == stTnrInfo.bEnable)
    {
        stMcTnrInfo.bEnable = HI_FALSE;
    }

    /* snr, tnr */
    //In 98mv200 all of SNR,DB,DM use DB'coef addr(VPSS_DB_CTRL).
    stSnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DB_CTRL) - sizeof(HI_U32);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_SNR, (HI_VOID *)&stSnrInfo, HI_NULL);

    //TNR分为 MA-TNR,  MC-TNR, MC需要单独设置开关, MA的开关即全局tnr开关
    stTnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_TNR_CONTRL) - sizeof(HI_U32);

    if VPSS_IS_YUV420_FMT(pstHalInfo->stInInfo.enFormat)
    {
        stTnrInfo.u32Ymotionmode = 1;
    }
    else
    {
        stTnrInfo.u32Ymotionmode = 0;
    }

    if ( HI_DRV_PIXEL_BITWIDTH_10BIT == pstHalInfo->stInInfo.enBitWidth )
    {
        stTnrInfo.bEnable = HI_FALSE;
    }

    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_TNR, (HI_VOID *)&stTnrInfo, HI_NULL);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_TNR_MC, (HI_VOID *)&stMcTnrInfo, HI_NULL);

#ifdef VPSS_SUPPORT_ALG_MCNR
    if ((HI_TRUE == stMcTnrInfo.bEnable) && (HI_TRUE == stTnrInfo.bEnable))
    {
        VPSS_HAL_SetRgmvCfg(enIP, pstHalInfo, stRegAddr);
    }
#endif
    /* ifmd */
    stIfmdInfo.bEnable = HI_FALSE;
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_IFMD, (HI_VOID *)&stIfmdInfo, HI_NULL);

    /* next2 config */
    pstNext2 = &pstHalInfo->stInInfo.stAddr;
    pstNext2_LB = &pstHalInfo->stInInfo.stAddr_LB;

    stFrameCfg.bEn              = HI_TRUE;
    stFrameCfg.bSecure          = pstHalInfo->stInInfo.bSecure;
    stFrameCfg.enBitWidth       = pstHalInfo->stInInfo.enBitWidth;
    stFrameCfg.enPixelFmt       = pstHalInfo->stInInfo.enFormat;
    stFrameCfg.u32Width         = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height        = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.bProgressive     = pstHalInfo->stInInfo.bProgressive;
    stFrameCfg.stOffset.s32X    = 0;
    stFrameCfg.stOffset.s32Y    = 0;


    stFrameCfg.bTopFirst = pstHalInfo->stInInfo.bTopFirst;

    if (HI_DRV_FIELD_TOP == pstHalInfo->stInInfo.enFieldMode)
    {
        stFrameCfg.bTop = HI_TRUE;
    }
    else
    {
        stFrameCfg.bTop = HI_FALSE;
    }

    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y  = pstNext2->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C  = pstNext2->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y   = pstNext2->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C   = pstNext2->u32Stride_C;

#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif

    if ( HI_DRV_PIXEL_BITWIDTH_10BIT == pstHalInfo->stInInfo.enBitWidth )
    {
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_Y   = pstNext2_LB->u32PhyAddr_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_C   = pstNext2_LB->u32PhyAddr_C;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_Y    = pstNext2_LB->u32Stride_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_C    = pstNext2_LB->u32Stride_C;

#ifdef HI_VPSS_SMMU_SUPPORT
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_TRUE;
#else
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_FALSE;
#endif
    }

    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_CMP)

    {
        stFrameCfg.bCompress = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_YHead  = pstNext2->u32PhyAddr_YHead;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_CHead  = pstNext2->u32PhyAddr_CHead;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Head_Size      = pstNext2->u32Head_Size;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Head_Stride    = pstNext2->u32Head_Stride;
#ifdef HI_VPSS_SMMU_SUPPORT
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y   = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C   = HI_TRUE;

        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y    = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C    = HI_TRUE;
#else
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;

        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_FALSE;
#endif
    }
    else
    {
        stFrameCfg.bCompress = HI_FALSE;
    }

    VPSS_DBG_INFO("2DNode nx2 read from %08x %08x %d %d\n",
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y,
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C,
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y,
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C);

    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_NX2, (HI_VOID *)&stFrameCfg, HI_NULL);

    /* rwzb */
    if (pstHalInfo->stRwzbInfo.u32EnRwzb)
    {
        if (VPSS_IS_TILE_FMT(pstHalInfo->stInInfo.enFormat))
        {
            VPSS_HAL_RWZB_Calc(pstHalInfo, &pstHalInfo->stInRefInfo[0].stAddr); //use wbc data(nx1,has been detiled)
        }
        else
        {
            VPSS_HAL_RWZB_Calc(pstHalInfo, pstNext2); //use nx2 data
        }
    }

    /* nx1 config */
    /* no need to config nx1 in 2DFrame */
#if 1
    /* cur config */
    pstCur = &pstHalInfo->stInRefInfo[0].stAddr;
    stFrameCfg.bEn = ( HI_DRV_PIXEL_BITWIDTH_10BIT == pstHalInfo->stInInfo.enBitWidth ) ? HI_FALSE : HI_TRUE;
    stFrameCfg.u32Width     = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height    = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstCur->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstCur->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstCur->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstCur->u32Stride_C;

    stFrameCfg.enPixelFmt = pstHalInfo->stInRefInfo[0].enFormat;
    stFrameCfg.enBitWidth = pstHalInfo->stInRefInfo[0].enBitWidth;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_CUR, (HI_VOID *)&stFrameCfg, HI_NULL);
#endif
    /* rfr config */
    pstRfr = &pstHalInfo->stInWbcInfo.stAddr;
    stFrameCfg.bEn = ( HI_DRV_PIXEL_BITWIDTH_10BIT == pstHalInfo->stInInfo.enBitWidth ) ? HI_FALSE : HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstRfr->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstRfr->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstRfr->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstRfr->u32Stride_C;
    stFrameCfg.enBitWidth = pstHalInfo->stInWbcInfo.enBitWidth;
    stFrameCfg.enPixelFmt = pstHalInfo->stInWbcInfo.enFormat;
    stFrameCfg.u32Width   = pstHalInfo->stInWbcInfo.u32Width;
    stFrameCfg.u32Height  = pstHalInfo->stInWbcInfo.u32Height;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_WRITE_RFR, (HI_VOID *)&stFrameCfg, &bRfrEnableFlag);



#if 0

    /* ref config */
    pstRef      = &pstHalInfo->stInRefInfo[0].stAddr;
    stFrameCfg.u32Width     = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height    = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstRef->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstRef->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstRef->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstRef->u32Stride_C;

    stFrameCfg.enPixelFmt = pstHalInfo->stInRefInfo[0].enFormat;
    stFrameCfg.enBitWidth = pstHalInfo->stInRefInfo[0].enBitWidth;
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_REF, (HI_VOID *)&stFrameCfg, HI_NULL);
#endif

    stHdrInfo.bEnable = pstHalInfo->stHdrInfo.bEnable;
    stHdrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_LCHDR_CTRL) - sizeof(HI_U32);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_HDR, (HI_VOID *)&stHdrInfo, &pstHalInfo->stHdrInfo.bHdrIn);


    /* vhd0 config */
    VPSS_HAL_SetPortCfg(enIP, stRegAddr, pstHalInfo);

    //逐隔行都要配置
    sttInfoCfg.u32WPhyAddr = pstHalInfo->stSttAddr.u32stt_w_phy_addr;
    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_STT, (HI_VOID *)&sttInfoCfg, (HI_VOID *)HI_NULL);

    /* smmu */

#ifdef HI_VPSS_SMMU_SUPPORT
    stSMMUCfg.bGlobalBypass = HI_FALSE;
    stSMMUCfg.bIntEnable = HI_TRUE;
    stSMMUCfg.u32Ptw_pf = 0x3;
    //stSMMUCfg.u32BypassFlag_RCH = 0x0;
    //stSMMUCfg.u32BypassFlag_WCH = 0x0;

    HI_DRV_SMMU_GetPageTableAddr(&u32PageAddr, &u32ErrReadAddr, &u32ErrWriteAddr);
    stSMMUCfg.u32CB_TTBR = stSMMUCfg.u32SCB_TTBR = u32PageAddr;
    stSMMUCfg.u32Err_s_rd_addr = stSMMUCfg.u32Err_ns_rd_addr = u32ErrReadAddr;
    stSMMUCfg.u32Err_s_wr_addr = stSMMUCfg.u32Err_ns_wr_addr = u32ErrWriteAddr;
#else
    stSMMUCfg.bGlobalBypass = HI_TRUE;
    stSMMUCfg.bIntEnable = HI_FALSE;
    //stSMMUCfg.u32BypassFlag_RCH = 0xffffffff;
    //stSMMUCfg.u32BypassFlag_WCH = 0xffffffff;
#endif
    stRegAddr_MMU.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr_MMU.pu8BaseVirAddr = stHalCtx[enIP][0].pu8BaseRegVir;
    VPSS_CBB_FUNC_SetConfig(stRegAddr_MMU, CBB_FUNC_SMMU, (HI_VOID *)&stSMMUCfg, HI_NULL);

    /* tnr mad */
    // stMadInfo_Tnr.bEn = ( HI_DRV_PIXEL_BITWIDTH_10BIT == pstHalInfo->stInInfo.enBitWidth ) ? HI_FALSE : HI_TRUE;
    stMadInfo_Tnr.bEn  = HI_FALSE;

    stMadInfo_Tnr.u32Wth = pstHalInfo->stInInfo.u32Width;
    stMadInfo_Tnr.u32Hgt = pstHalInfo->stInInfo.u32Height;
    stMadInfo_Tnr.u32RPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Tnrmad_raddr;
    stMadInfo_Tnr.u32WPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Tnrmad_waddr;
    stMadInfo_Tnr.u32Stride   = pstHalInfo->stNrInfo.stNrMadCfg.u32madstride;
#ifdef HI_VPSS_SMMU_SUPPORT
    stMadInfo_Tnr.bSmmu_R = HI_TRUE;
    stMadInfo_Tnr.bSmmu_W = HI_TRUE;
#else
    stMadInfo_Tnr.bSmmu_R = HI_FALSE;
    stMadInfo_Tnr.bSmmu_W = HI_FALSE;
#endif
    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_TNR_MAD, (HI_VOID *)&stMadInfo_Tnr, HI_NULL);
    stAlgInfo.bEnable = HI_FALSE;
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_IGBM, (HI_VOID *)&stAlgInfo, HI_NULL);

#if 1
    {
        /* tnr mad */
        stMadInfo_Tnr.bEn    = stTnrInfo.bEnable;
        stMadInfo_Tnr.u32Wth = pstHalInfo->stInInfo.u32Width;
        stMadInfo_Tnr.u32Hgt = pstHalInfo->stInInfo.u32Height; // / 2;
        stMadInfo_Tnr.u32RPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Tnrmad_raddr;
        stMadInfo_Tnr.u32WPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Tnrmad_waddr;
        stMadInfo_Tnr.u32Stride   = pstHalInfo->stNrInfo.stNrMadCfg.u32madstride;
        VPSS_DBG_INFO("TnrMad.RP : %#x, TnrMad.WP : %#x. stride%d\n", stMadInfo_Tnr.u32RPhyAddr, stMadInfo_Tnr.u32WPhyAddr, stMadInfo_Tnr.u32Stride);
#ifdef HI_VPSS_SMMU_SUPPORT
        stMadInfo_Tnr.bSmmu_R = HI_TRUE;
        stMadInfo_Tnr.bSmmu_W = HI_TRUE;
#else
        stMadInfo_Tnr.bSmmu_R = HI_FALSE;
        stMadInfo_Tnr.bSmmu_W = HI_FALSE;
#endif
        VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_TNR_MAD, (HI_VOID *)&stMadInfo_Tnr, HI_NULL);
    }
#endif
    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_Set_2DDei_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy)
{
    HI_DRV_VID_FRAME_ADDR_S *pstNext2;
    HI_DRV_VID_FRAME_ADDR_S *pstNext2_LB;

    HI_DRV_VID_FRAME_ADDR_S *pstRef;
    HI_DRV_VID_FRAME_ADDR_S *pstNxt1;

    HI_DRV_VID_FRAME_ADDR_S *pstCur;
    HI_DRV_VID_FRAME_ADDR_S *pstRfr;

    HI_BOOL bRfrEnableFlag;
    HI_U32 u32PageAddr;
    HI_U32 u32ErrReadAddr;
    HI_U32 u32ErrWriteAddr;

    CBB_REG_ADDR_S      stRegAddr;
    CBB_REG_ADDR_S      stRegAddr_MMU;
    CBB_FRAME_S         stFrameCfg;
    CBB_FUNC_TUNNELIN_S stTunnelIn;
    CBB_FUNC_SMMU_S     stSMMUCfg;
    CBB_INFO_S          stMadInfo_Tnr;
    CBB_INFO_S          stMadInfo_Snr;
    CBB_ALG_INFO_S      stDBInfo;
    CBB_ALG_INFO_S      stDBDETInfo;
    CBB_ALG_INFO_S      stNrInfo;
    CBB_ALG_INFO_S      stSnrInfo;
    CBB_ALG_INFO_S      stTnrInfo;
    CBB_ALG_INFO_S      stMcTnrInfo;
    CBB_ALG_INFO_S      stAlgInfo;
    CBB_INFO_S          sttInfoCfg;
    CBB_ALG_INFO_S      stMcDeiAlgCfg;
    CBB_ALG_INFO_S      stHdrInfo;
    CBB_FUNC_FDIFRO_S   stFuncFdIFdOCfg;
    HI_BOOL             bMedsEn = HI_FALSE;

    VPSS_MEM_CLEAR(stRegAddr);
    VPSS_MEM_CLEAR(stRegAddr_MMU);
    VPSS_MEM_CLEAR(stFrameCfg);
    VPSS_MEM_CLEAR(stTunnelIn);
    VPSS_MEM_CLEAR(stSMMUCfg);
    VPSS_MEM_CLEAR(stMadInfo_Tnr);
    VPSS_MEM_CLEAR(stMadInfo_Snr);
    VPSS_MEM_CLEAR(stDBInfo);
    VPSS_MEM_CLEAR(stDBDETInfo);
    VPSS_MEM_CLEAR(stNrInfo);
    VPSS_MEM_CLEAR(stSnrInfo);
    VPSS_MEM_CLEAR(stTnrInfo);
    VPSS_MEM_CLEAR(stMcTnrInfo);
    VPSS_MEM_CLEAR(stAlgInfo);
    VPSS_MEM_CLEAR(sttInfoCfg);
    VPSS_MEM_CLEAR(stMcDeiAlgCfg);
    VPSS_MEM_CLEAR(stHdrInfo);
    VPSS_MEM_CLEAR(stFuncFdIFdOCfg);

    stRegAddr.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr.u32NodePhyAddr = u32AppPhy;

    VPSS_REG_ResetAppReg((S_VPSS_REGS_TYPE *)pu32AppVir, pstHalInfo->pstPqCfg);

    /* channel config */
    pstRef      = &pstHalInfo->stInRefInfo[0].stAddr;
    pstCur      = &pstHalInfo->stInRefInfo[1].stAddr;
    pstNxt1     = &pstHalInfo->stInRefInfo[2].stAddr;
    pstNext2    = &pstHalInfo->stInInfo.stAddr;
    pstNext2_LB = &pstHalInfo->stInInfo.stAddr_LB;
    pstRfr      = &pstHalInfo->stInWbcInfo.stAddr;
#if 0
    VPSS_DBG_INFO("Ref  phy:%08x, vir:%x\n", pstRef->u32PhyAddr_Y, (HI_U32)pstRef->vir_addr_y);
    VPSS_DBG_INFO("Cur  phy:%08x, vir:%x\n", pstCur->u32PhyAddr_Y, (HI_U32)pstCur->vir_addr_y);
    VPSS_DBG_INFO("Nx1  phy:%08x, vir:%x\n", pstNxt1->u32PhyAddr_Y, (HI_U32)pstNxt1->vir_addr_y);
    VPSS_DBG_INFO("Nx2  phy:%08x, vir:%x\n", pstNext2->u32PhyAddr_Y, (HI_U32)pstNext2->vir_addr_y);
    VPSS_DBG_INFO("Rfr  phy:%08x, vir:%x stid:%d %d\n", pstRfr->u32PhyAddr_Y, (HI_U32)pstRfr->vir_addr_y,
                  pstRfr->u32Stride_Y, pstRfr->u32Stride_C);
#endif

    //pstRef = pstCur = pstNxt1 = pstNext2; //Debug use. all ref to nx2



    /*tunnel*/
    if (pstHalInfo->stInInfo.u32TunnelAddr)
    {
        stTunnelIn.bEnable = HI_TRUE;
        stTunnelIn.u32ReadInterval = 0;
        stTunnelIn.u32ReadAddr = pstHalInfo->stInInfo.u32TunnelAddr;
    }
    else
    {
        stTunnelIn.bEnable = HI_FALSE;
    }

    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_TUNNEL_IN, (HI_VOID *)&stTunnelIn, HI_NULL);

    //>SD < FHD时, 只开MA-TNR, DEI

    /* db */
    /* db_det */

    bRfrEnableFlag      = HI_TRUE;
    //snr_en 是db,dm, nr的总开关， SNR包括db,dm,nr
    stSnrInfo.bEnable   = HI_FALSE; //只支持标清的SNR
    stTnrInfo.bEnable   = HI_TRUE;  //只需开MA-TNR, 关闭MC-TNR
    stMcTnrInfo.bEnable = HI_FALSE;

    if (VPSS_IS_YUV422_FMT(pstHalInfo->stInInfo.enFormat))
    {
        stDBDETInfo.bEnable = HI_FALSE;
        stDBInfo.bEnable    = HI_FALSE;
        stSnrInfo.bEnable   = HI_FALSE;
    }

    if ((VPSS_HAL_IS_RWZB(pstHalInfo->stRwzbInfo.u32IsRwzb)) && (HI_FALSE == pstHalInfo->bSplitEnable))
    {
        stSnrInfo.bEnable   = HI_FALSE;
        stTnrInfo.bEnable   = HI_FALSE;
    }

    /* snr, tnr */
    //In 98mv200 all of SNR,DB,DM use DB'coef addr(VPSS_DB_CTRL).
    stSnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DB_CTRL) - sizeof(HI_U32);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_SNR, (HI_VOID *)&stSnrInfo, HI_NULL);

    //TNR分为 MA-TNR,  MC-TNR, MC需要单独设置开关, MA的开关即全局tnr开关
    stTnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_TNR_CONTRL) - sizeof(HI_U32);

    if VPSS_IS_YUV420_FMT(pstHalInfo->stInInfo.enFormat)
    {
        stTnrInfo.u32Ymotionmode = 1;
    }
    else
    {
        stTnrInfo.u32Ymotionmode = 0;
    }

    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_TNR, (HI_VOID *)&stTnrInfo, HI_NULL);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_TNR_MC, (HI_VOID *)&stMcTnrInfo, HI_NULL);

    stHdrInfo.bEnable = pstHalInfo->stHdrInfo.bEnable;
    stHdrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL,
                            VPSS_LCHDR_CTRL) - sizeof(HI_U32);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_HDR, (HI_VOID *)&stHdrInfo, &
                         pstHalInfo->stHdrInfo.bHdrIn);


    /* next2 config */
    stFrameCfg.bEn              = HI_TRUE;
    stFrameCfg.bSecure          = pstHalInfo->stInInfo.bSecure;
    stFrameCfg.enBitWidth       = pstHalInfo->stInInfo.enBitWidth;
    stFrameCfg.enPixelFmt       = pstHalInfo->stInInfo.enFormat;    // TODO: 做格式转换
    stFrameCfg.u32Width         = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height        = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.bProgressive     = pstHalInfo->stInInfo.bProgressive;
    stFrameCfg.bSpecialTile     = HI_FALSE;
    stFrameCfg.stOffset.s32X    = 0;
    stFrameCfg.stOffset.s32Y    = 0;


    stFrameCfg.bTopFirst = pstHalInfo->stInInfo.bTopFirst;

    if (HI_DRV_FIELD_TOP == pstHalInfo->stInInfo.enFieldMode)
    {
        stFrameCfg.bTop = HI_TRUE;
    }
    else
    {
        stFrameCfg.bTop = HI_FALSE;
    }

    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y  = pstNext2->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C  = pstNext2->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y   = pstNext2->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C   = pstNext2->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif

    if ( HI_DRV_PIXEL_BITWIDTH_10BIT == pstHalInfo->stInInfo.enBitWidth )
    {
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_Y   = pstNext2_LB->u32PhyAddr_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_C   = pstNext2_LB->u32PhyAddr_C;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_Y    = pstNext2_LB->u32Stride_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_C    = pstNext2_LB->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_TRUE;
#else
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_FALSE;
#endif
    }

    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_CMP)
    {
        stFrameCfg.bCompress = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_YHead  = pstNext2->u32PhyAddr_YHead;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_CHead  = pstNext2->u32PhyAddr_CHead;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Head_Size      = pstNext2->u32Head_Size;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Head_Stride    = pstNext2->u32Head_Stride;
#ifdef HI_VPSS_SMMU_SUPPORT
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y   = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C   = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y    = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C    = HI_TRUE;
#else
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_FALSE;
#endif
    }
    else
    {
        stFrameCfg.bCompress = HI_FALSE;
    }

    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_NX2, (HI_VOID *)&stFrameCfg, HI_NULL);

    stFuncFdIFdOCfg.bEnable = HI_FALSE; //pstHalInfo->stInInfo.bSpecField;
    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_FDIFRO, (HI_VOID *)&stFuncFdIFdOCfg, HI_NULL);

    /* rwzb */
    if (pstHalInfo->stRwzbInfo.u32EnRwzb)
    {
        if (VPSS_IS_TILE_FMT(pstHalInfo->stInInfo.enFormat))
        {
            VPSS_HAL_RWZB_Calc(pstHalInfo, &pstHalInfo->stInRefInfo[0].stAddr); //use wbc data(nx1,has been detiled)
        }
        else
        {
            VPSS_HAL_RWZB_Calc(pstHalInfo, pstNext2); //use nx2 data
        }
    }

    /* nx1 config */
    stFrameCfg.bEn          = HI_TRUE;
    stFrameCfg.u32Width     = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height    = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y  = pstNxt1->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C  = pstNxt1->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y   = pstNxt1->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C   = pstNxt1->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif
    stFrameCfg.enPixelFmt = pstHalInfo->stInRefInfo[2].enFormat;
    stFrameCfg.enBitWidth = pstHalInfo->stInRefInfo[2].enBitWidth;
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_NX1, (HI_VOID *)&stFrameCfg, HI_NULL);

    /* cur config */
    stFrameCfg.bEn          = HI_TRUE;
    stFrameCfg.u32Width     = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height    = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstCur->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstCur->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstCur->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstCur->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif
    stFrameCfg.enPixelFmt = pstHalInfo->stInRefInfo[1].enFormat;
    stFrameCfg.enBitWidth = pstHalInfo->stInRefInfo[1].enBitWidth;
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_CUR, (HI_VOID *)&stFrameCfg, HI_NULL);

    /* ref config */
    stFrameCfg.bEn          = HI_TRUE;
    stFrameCfg.u32Width     = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height    = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstRef->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstRef->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstRef->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstRef->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif
    stFrameCfg.enPixelFmt = pstHalInfo->stInRefInfo[0].enFormat;
    stFrameCfg.enBitWidth = pstHalInfo->stInRefInfo[0].enBitWidth;
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_REF, (HI_VOID *)&stFrameCfg, HI_NULL);

    /* rfr config */
    stFrameCfg.bEn = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstRfr->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstRfr->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstRfr->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstRfr->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif
    stFrameCfg.enBitWidth = pstHalInfo->stInWbcInfo.enBitWidth;
    stFrameCfg.enPixelFmt = pstHalInfo->stInWbcInfo.enFormat;
    stFrameCfg.u32Width   = pstHalInfo->stInWbcInfo.u32Width;
    stFrameCfg.u32Height  = pstHalInfo->stInWbcInfo.u32Height;
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_WRITE_RFR, (HI_VOID *)&stFrameCfg, &bRfrEnableFlag);

    /* vhd0 config */
    VPSS_HAL_SetPortCfg(enIP, stRegAddr, pstHalInfo);

    //逐隔行都要配置
    sttInfoCfg.u32WPhyAddr = pstHalInfo->stSttAddr.u32stt_w_phy_addr;
    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_STT, (HI_VOID *)&sttInfoCfg, (HI_VOID *)HI_NULL);

    VPSS_HAL_SetDeiCfg(enIP, pstHalInfo, stRegAddr);

    bMedsEn = (stMcTnrInfo.bEnable || stMcDeiAlgCfg.bEnable);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_MCDEI, (HI_VOID *)&stMcDeiAlgCfg, &bMedsEn);

    if (bMedsEn)
    {
        VPSS_HAL_SetRgmvCfg(enIP, pstHalInfo, stRegAddr);
    }

    if ((pstHalInfo->bSplitEnable) || (stMcDeiAlgCfg.bEnable))
    {
        VPSS_HAL_SetMcDeiCfg(enIP, pstHalInfo, stRegAddr);
        VPSS_HAL_SetRgmvCfg(enIP, pstHalInfo, stRegAddr);
    }


    /* igbm */
    stAlgInfo.bEnable = HI_TRUE;
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_IGBM, (HI_VOID *)&stAlgInfo, HI_NULL);

    /* ifmd */
    stAlgInfo.bEnable = HI_TRUE;
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_IFMD, (HI_VOID *)&stAlgInfo, HI_NULL);

    /* smmu */
#ifdef HI_VPSS_SMMU_SUPPORT
    stSMMUCfg.bGlobalBypass = HI_FALSE;
    stSMMUCfg.bIntEnable = HI_TRUE;
    stSMMUCfg.u32Ptw_pf = 0x3;
    HI_DRV_SMMU_GetPageTableAddr(&u32PageAddr, &u32ErrReadAddr, &u32ErrWriteAddr);
    stSMMUCfg.u32CB_TTBR = stSMMUCfg.u32SCB_TTBR = u32PageAddr;
    stSMMUCfg.u32Err_s_rd_addr = stSMMUCfg.u32Err_ns_rd_addr = u32ErrReadAddr;
    stSMMUCfg.u32Err_s_wr_addr = stSMMUCfg.u32Err_ns_wr_addr = u32ErrWriteAddr;
#else
    stSMMUCfg.bGlobalBypass = HI_TRUE;
    stSMMUCfg.bIntEnable = HI_FALSE;
#endif

    stRegAddr_MMU.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr_MMU.pu8BaseVirAddr = stHalCtx[enIP][0].pu8BaseRegVir;
    VPSS_CBB_FUNC_SetConfig(stRegAddr_MMU, CBB_FUNC_SMMU, (HI_VOID *)&stSMMUCfg, HI_NULL);

    /* tnr mad */
    if (HI_TRUE == stTnrInfo.bEnable)
    {
        /* tnr mad */
        stMadInfo_Tnr.bEn    = stTnrInfo.bEnable;
        stMadInfo_Tnr.u32Wth = pstHalInfo->stInInfo.u32Width;
        stMadInfo_Tnr.u32Hgt = pstHalInfo->stInInfo.u32Height / 2;
        stMadInfo_Tnr.u32RPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Tnrmad_raddr;
        stMadInfo_Tnr.u32WPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Tnrmad_waddr;
        stMadInfo_Tnr.u32Stride   = pstHalInfo->stNrInfo.stNrMadCfg.u32madstride;
#ifdef HI_VPSS_SMMU_SUPPORT
        stMadInfo_Tnr.bSmmu_R = HI_TRUE;
        stMadInfo_Tnr.bSmmu_W = HI_TRUE;
#else
        stMadInfo_Tnr.bSmmu_R = HI_FALSE;
        stMadInfo_Tnr.bSmmu_W = HI_FALSE;
#endif
        VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_TNR_MAD, (HI_VOID *)&stMadInfo_Tnr, HI_NULL);
    }

    return HI_SUCCESS;
}



HI_S32 VPSS_HAL_Set_2DField_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy)
{
    //VPZME, 单场模式开

    HI_DRV_VID_FRAME_ADDR_S *pstNext2;
    HI_DRV_VID_FRAME_ADDR_S *pstNext2_LB;
    HI_DRV_VID_FRAME_ADDR_S *pstCur;
    HI_DRV_VID_FRAME_ADDR_S *pstRfr;

    HI_BOOL bRfrEnableFlag;
    HI_U32 u32PageAddr;
    HI_U32 u32ErrReadAddr;
    HI_U32 u32ErrWriteAddr;

    CBB_REG_ADDR_S      stRegAddr;
    CBB_REG_ADDR_S      stRegAddr_MMU;
    CBB_FRAME_S         stFrameCfg;
    CBB_FUNC_TUNNELIN_S stTunnelIn;
    CBB_FUNC_SMMU_S     stSMMUCfg;
    CBB_INFO_S          stMadInfo_Tnr;
    CBB_INFO_S          stMadInfo_Snr;
    CBB_ALG_INFO_S      stDBInfo;
    CBB_ALG_INFO_S      stDBDETInfo;
    CBB_ALG_INFO_S      stNrInfo;
    CBB_ALG_INFO_S      stSnrInfo;
    CBB_ALG_INFO_S      stTnrInfo;
    CBB_ALG_INFO_S      stMcTnrInfo;
    CBB_ALG_INFO_S      stIfmdInfo;
    CBB_INFO_S          sttInfoCfg;

    VPSS_MEM_CLEAR(stRegAddr);
    VPSS_MEM_CLEAR(stRegAddr_MMU);
    VPSS_MEM_CLEAR(stFrameCfg);
    VPSS_MEM_CLEAR(stTunnelIn);
    VPSS_MEM_CLEAR(stSMMUCfg);
    VPSS_MEM_CLEAR(stMadInfo_Tnr);
    VPSS_MEM_CLEAR(stMadInfo_Snr);
    VPSS_MEM_CLEAR(stDBInfo);
    VPSS_MEM_CLEAR(stDBDETInfo);
    VPSS_MEM_CLEAR(stNrInfo);
    VPSS_MEM_CLEAR(stSnrInfo);
    VPSS_MEM_CLEAR(stTnrInfo);
    VPSS_MEM_CLEAR(stMcTnrInfo);
    VPSS_MEM_CLEAR(stIfmdInfo);
    VPSS_MEM_CLEAR(sttInfoCfg);

    stRegAddr.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr.u32NodePhyAddr = u32AppPhy;

    VPSS_REG_ResetAppReg((S_VPSS_REGS_TYPE *)pu32AppVir, pstHalInfo->pstPqCfg);

    /*tunnel*/
    if (pstHalInfo->stInInfo.u32TunnelAddr)
    {
        stTunnelIn.bEnable = HI_TRUE;
        stTunnelIn.u32ReadInterval = 0;
        stTunnelIn.u32ReadAddr = pstHalInfo->stInInfo.u32TunnelAddr;
    }
    else
    {
        stTunnelIn.bEnable = HI_FALSE;
    }

    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_TUNNEL_IN, (HI_VOID *)&stTunnelIn, HI_NULL);

    if ((pstHalInfo->stInInfo.u32Width > 128
         && pstHalInfo->stInInfo.u32Height > 64)
        && (VPSS_ALG_IS_SD(pstHalInfo->stInInfo.u32Width, pstHalInfo->stInInfo.u32Height)))
    {
        stDBDETInfo.bEnable = HI_TRUE;
        stDBInfo.bEnable        = HI_TRUE;
        stTnrInfo.bEnable   = HI_TRUE;
    }
    else
    {
        stDBDETInfo.bEnable = HI_FALSE;
        stDBInfo.bEnable    = HI_FALSE;
        stTnrInfo.bEnable   = HI_FALSE;
    }

    if (pstHalInfo->bSplitEnable)
    {
        stTnrInfo.bEnable   = HI_TRUE;
    }
    if (0 == pstHalInfo->u32DetileFieldIdx) //cur channel date is un-detiled
    {
        stTnrInfo.bEnable   = HI_FALSE;
    }
    if (VPSS_IS_YUV422_FMT(pstHalInfo->stInInfo.enFormat))
    {
        stDBDETInfo.bEnable = HI_FALSE;
        stDBInfo.bEnable    = HI_FALSE;
        stSnrInfo.bEnable   = HI_FALSE;
    }

    stNrInfo.bEnable    = HI_FALSE;
    bRfrEnableFlag      = HI_FALSE;
    stMcTnrInfo.bEnable = HI_FALSE;

    // stDBInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DB_CTRL) - sizeof(HI_U32);
    //  VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_DB, (HI_VOID *)&stDBInfo, HI_NULL);
    //  VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_DB_DET, (HI_VOID *)&stDBDETInfo, HI_NULL);
    //  VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_NR, (HI_VOID *)&stNrInfo, HI_NULL);

    //snr_en 是db,dm, nr的总开关， SNR包括db,dm,nr

    /* snr, tnr */
    //In 98mv200 all of SNR,DB,DM use DB'coef addr(VPSS_DB_CTRL).
    stSnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DB_CTRL) - sizeof(HI_U32);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_SNR, (HI_VOID *)&stSnrInfo, HI_NULL);

    //TNR分为 MA-TNR,  MC-TNR, MC需要单独设置开关, MA的开关即全局tnr开关
    stTnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_TNR_CONTRL) - sizeof(HI_U32);

    if VPSS_IS_YUV420_FMT(pstHalInfo->stInInfo.enFormat)
    {
        stTnrInfo.u32Ymotionmode = 1;
    }
    else
    {
        stTnrInfo.u32Ymotionmode = 0;
    }

    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_TNR, (HI_VOID *)&stTnrInfo, HI_NULL);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_TNR_MC, (HI_VOID *)&stMcTnrInfo, HI_NULL);

    /* ifmd */
    stIfmdInfo.bEnable = HI_FALSE;
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_IFMD, (HI_VOID *)&stIfmdInfo, HI_NULL);

    /* next2 config */
    pstNext2 = &pstHalInfo->stInInfo.stAddr;
    pstNext2_LB = &pstHalInfo->stInInfo.stAddr_LB;
    stFrameCfg.bEn              = HI_TRUE;
    stFrameCfg.bSecure          = pstHalInfo->stInInfo.bSecure;
    stFrameCfg.enBitWidth       = pstHalInfo->stInInfo.enBitWidth;
    stFrameCfg.enPixelFmt       = pstHalInfo->stInInfo.enFormat;    // TODO: 做格式转换
    stFrameCfg.u32Width         = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height        = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.bProgressive     = HI_FALSE;
    stFrameCfg.stOffset.s32X    = 0;
    stFrameCfg.stOffset.s32Y    = 0;


    stFrameCfg.bTopFirst = pstHalInfo->stInInfo.bTopFirst;

    if (HI_DRV_FIELD_TOP == pstHalInfo->stInInfo.enFieldMode)
    {
        stFrameCfg.bTop = HI_TRUE;
    }
    else
    {
        stFrameCfg.bTop = HI_FALSE;
    }

    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y  = pstNext2->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C  = pstNext2->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y   = pstNext2->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C   = pstNext2->u32Stride_C;

    if ( HI_DRV_PIXEL_BITWIDTH_10BIT == pstHalInfo->stInInfo.enBitWidth )
    {
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_Y   = pstNext2_LB->u32PhyAddr_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_C   = pstNext2_LB->u32PhyAddr_C;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_Y    = pstNext2_LB->u32Stride_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_C    = pstNext2_LB->u32Stride_C;
    }

    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_CMP)

    {
        stFrameCfg.bCompress = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_YHead  = pstNext2->u32PhyAddr_YHead;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_CHead  = pstNext2->u32PhyAddr_CHead;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Head_Size      = pstNext2->u32Head_Size;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Head_Stride    = pstNext2->u32Head_Stride;
    }
    else
    {
        stFrameCfg.bCompress = HI_FALSE;
    }
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif

    VPSS_DBG_INFO("2DNode nx2 read from %08x %08x %d %d\n",
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y,
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C,
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y,
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C);

    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_NX2, (HI_VOID *)&stFrameCfg, HI_NULL);

    /* nx1 config */
    /* no need to config nx1 in 2DFrame */

    /* cur config */
    pstCur = &pstHalInfo->stInRefInfo[0].stAddr;
    stFrameCfg.bEn          = stTnrInfo.bEnable;
    stFrameCfg.u32Width     = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height    = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstCur->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstCur->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstCur->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstCur->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif

    stFrameCfg.enPixelFmt = pstHalInfo->stInRefInfo[0].enFormat;
    stFrameCfg.enBitWidth = pstHalInfo->stInRefInfo[0].enBitWidth;
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_CUR, (HI_VOID *)&stFrameCfg, HI_NULL);

    /* rfr config */
    pstRfr = &pstHalInfo->stInWbcInfo.stAddr;
    stFrameCfg.bEn = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstRfr->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstRfr->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstRfr->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstRfr->u32Stride_C;
    // TODO: ref. rfr 都 固定10bit回写, 计算buffer大小时也要按照10bit算
    stFrameCfg.enBitWidth = pstHalInfo->stInWbcInfo.enBitWidth;
    stFrameCfg.enPixelFmt = pstHalInfo->stInWbcInfo.enFormat;
    stFrameCfg.u32Width   = pstHalInfo->stInWbcInfo.u32Width;
    // stFrameCfg.u32Height  = pstHalInfo->stInWbcInfo.u32Height / 2;
    stFrameCfg.u32Height  = pstHalInfo->stInWbcInfo.u32Height;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_WRITE_RFR, (HI_VOID *)&stFrameCfg, &bRfrEnableFlag);

    /* vhd0 config */
    VPSS_HAL_SetPortCfg(enIP, stRegAddr, pstHalInfo);

    //逐隔行都要配置
    sttInfoCfg.u32WPhyAddr = pstHalInfo->stSttAddr.u32stt_w_phy_addr;
    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_STT, (HI_VOID *)&sttInfoCfg, (HI_VOID *)HI_NULL);

    /* smmu */
#ifdef HI_VPSS_SMMU_SUPPORT
    stSMMUCfg.bGlobalBypass = HI_FALSE;
    stSMMUCfg.bIntEnable = HI_TRUE;
    stSMMUCfg.u32Ptw_pf = 0x3;
    stSMMUCfg.u32BypassFlag_RCH = 0x0;
    stSMMUCfg.u32BypassFlag_WCH = 0x0;

    HI_DRV_SMMU_GetPageTableAddr(&u32PageAddr, &u32ErrReadAddr, &u32ErrWriteAddr);
    stSMMUCfg.u32CB_TTBR = stSMMUCfg.u32SCB_TTBR = u32PageAddr;
    stSMMUCfg.u32Err_s_rd_addr = stSMMUCfg.u32Err_ns_rd_addr = u32ErrReadAddr;
    stSMMUCfg.u32Err_s_wr_addr = stSMMUCfg.u32Err_ns_wr_addr = u32ErrWriteAddr;
#else
    stSMMUCfg.bGlobalBypass = HI_TRUE;
    stSMMUCfg.bIntEnable = HI_FALSE;
    stSMMUCfg.u32BypassFlag_RCH = 0xffffffff;
    stSMMUCfg.u32BypassFlag_WCH = 0xffffffff;
#endif

    stRegAddr_MMU.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr_MMU.pu8BaseVirAddr = stHalCtx[enIP][0].pu8BaseRegVir;
    VPSS_CBB_FUNC_SetConfig(stRegAddr_MMU, CBB_FUNC_SMMU, (HI_VOID *)&stSMMUCfg, HI_NULL);

    VPSS_Sys_SetOutProEn((S_VPSS_REGS_TYPE *)pu32AppVir, 0x0, 0x1);

    /* tnr mad */
    //if ((HI_TRUE == stTnrInfo.bEnable) || (HI_TRUE == stSnrInfo.bEnable))
    {
        /* tnr mad */
        stMadInfo_Tnr.bEn    = stTnrInfo.bEnable || stSnrInfo.bEnable;
        stMadInfo_Tnr.u32Wth = pstHalInfo->stInInfo.u32Width;
        stMadInfo_Tnr.u32Hgt = pstHalInfo->stInInfo.u32Height / 2;
        stMadInfo_Tnr.u32RPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Tnrmad_raddr;
        stMadInfo_Tnr.u32WPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Tnrmad_waddr;
        stMadInfo_Tnr.u32Stride   = pstHalInfo->stNrInfo.stNrMadCfg.u32madstride;
#ifdef HI_VPSS_SMMU_SUPPORT
        stMadInfo_Tnr.bSmmu_R = HI_TRUE;
        stMadInfo_Tnr.bSmmu_W = HI_TRUE;
#else
        stMadInfo_Tnr.bSmmu_R = HI_FALSE;
        stMadInfo_Tnr.bSmmu_W = HI_FALSE;
#endif
        VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_TNR_MAD, (HI_VOID *)&stMadInfo_Tnr, HI_NULL);
    }

    return HI_SUCCESS;

}

HI_S32 VPSS_HAL_SDDeiBuffer_Alloc(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstVpssHalInfo, HI_BOOL bSecure)
{
    HI_S32 s32Ret = HI_SUCCESS;
    VPSS_HAL_CHECK_IP_VAILD(enIP);

#ifdef HI_VPSS_SMMU_SUPPORT

    if (bSecure)
    {
        if (pstVpssHalInfo->stSDDeiBuf_TEE.u32Size == 0)
        {
#ifdef HI_TEE_SUPPORT
            s32Ret = HI_DRV_SECSMMU_Alloc("VPSS_DEI_MMU_S", 720 * 576 * 2, 0, &pstVpssHalInfo->stSDDeiBuf_TEE);
#else
            s32Ret = HI_DRV_SMMU_AllocAndMap("VPSS_DEI_MMU_NS", 720 * 576 * 2, 0, &(pstVpssHalInfo->stSDDeiBuf_TEE));
#endif
        }
    }
    else
    {
        if (pstVpssHalInfo->stSDDeiBuf_MMU.u32Size == 0)
        {
            s32Ret = HI_DRV_SMMU_AllocAndMap("VPSS_DEI_MMU_NS", 720 * 576 * 2, 0, &(pstVpssHalInfo->stSDDeiBuf_MMU));
        }
    }

    if (s32Ret != HI_SUCCESS)
    {
        VPSS_FATAL("Alloc sd dei mmu buffer failed\n");
        return HI_FAILURE;
    }

#else

    if (pstVpssHalInfo->stSDDeiBuf_MMZ.u32Size == 0)
    {
        s32Ret = HI_DRV_MMZ_AllocAndMap("VPSS_SDDEI_MMZ", "VPSS", 720 * 576 * 2, 0, &(pstVpssHalInfo->stSDDeiBuf_MMZ));

        if (s32Ret != HI_SUCCESS)
        {
            VPSS_FATAL("Alloc sd dei mmz buffer failed\n");
            return HI_FAILURE;
        }
    }

#endif

    return HI_SUCCESS;
}
HI_VOID VPSS_HAL_SDDeiBuffer_Free(VPSS_HAL_INFO_S *pstVpssHalInfo)
{
#ifdef HI_VPSS_SMMU_SUPPORT
    if (pstVpssHalInfo->stSDDeiBuf_MMU.u32Size != 0)
    {
        HI_DRV_SMMU_UnmapAndRelease(&(pstVpssHalInfo->stSDDeiBuf_MMU));
        memset(&(pstVpssHalInfo->stSDDeiBuf_MMU), 0, sizeof(SMMU_BUFFER_S));
    }

    if (pstVpssHalInfo->stSDDeiBuf_TEE.u32Size != 0)
    {
#ifdef HI_TEE_SUPPORT
        (HI_VOID)HI_DRV_SECSMMU_Release(&(pstVpssHalInfo->stSDDeiBuf_TEE));
#else
        HI_DRV_SMMU_UnmapAndRelease(&(pstVpssHalInfo->stSDDeiBuf_TEE));
#endif
        memset(&(pstVpssHalInfo->stSDDeiBuf_TEE), 0, sizeof(SMMU_BUFFER_S));
    }

#else
    if (pstVpssHalInfo->stSDDeiBuf_MMZ.u32Size != 0)
    {
        HI_DRV_MMZ_UnmapAndRelease(&(pstVpssHalInfo->stSDDeiBuf_MMZ));
        memset(&(pstVpssHalInfo->stSDDeiBuf_MMZ), 0, sizeof(MMZ_BUFFER_S));
    }
#endif

    return;
}

HI_S32 VPSS_HAL_ConfigSDDeiFrame(   VPSS_HAL_FRAME_S *pstDeTileFrame,
                                    HI_U32 u32BufferStartAddr,
                                    HI_U32 u32Width,
                                    HI_U32 u32Height,
                                    HI_DRV_PIX_FORMAT_E ePixFormat,
                                    HI_DRV_PIXEL_BITWIDTH_E enBitWidth)
{
    HI_U32 u32Stride;
    HI_U32 u32RetStride;
    HI_U32 u32PhyAddr;

    if (HI_DRV_PIX_FMT_NV21_TILE_CMP == ePixFormat
        || HI_DRV_PIX_FMT_NV12_TILE_CMP == ePixFormat
        || HI_DRV_PIX_FMT_NV21_TILE == ePixFormat
        || HI_DRV_PIX_FMT_NV12_TILE == ePixFormat
        || HI_DRV_PIX_FMT_NV21 == ePixFormat
        || HI_DRV_PIX_FMT_NV12 == ePixFormat)
    {
        ePixFormat = HI_DRV_PIX_FMT_NV21;
    }
    else
    {
        ePixFormat = HI_DRV_PIX_FMT_NV61_2X1;
    }

    if (HI_DRV_PIXEL_BITWIDTH_8BIT == enBitWidth)
    {
        u32RetStride = HI_ALIGN_8BIT_YSTRIDE(u32Width);
    }
    else if (HI_DRV_PIXEL_BITWIDTH_10BIT == enBitWidth)
    {
        u32RetStride = HI_ALIGN_10BIT_COMP_YSTRIDE(u32Width);
    }
    else
    {
        VPSS_ERROR("Unsupport BitWidth %d.\n", enBitWidth);
        return HI_FAILURE;
    }

    u32Stride = u32RetStride;
    u32PhyAddr = u32BufferStartAddr;

    pstDeTileFrame->u32Width = u32Width;
    pstDeTileFrame->u32Height = u32Height;
    pstDeTileFrame->enBitWidth = enBitWidth;
    pstDeTileFrame->enFormat = ePixFormat;
    pstDeTileFrame->stAddr.u32Stride_Y = u32Stride;
    pstDeTileFrame->stAddr.u32Stride_C = u32Stride;

    pstDeTileFrame->stAddr.u32PhyAddr_Y = u32PhyAddr;
    pstDeTileFrame->stAddr.u32PhyAddr_C = u32PhyAddr + u32Stride * u32Height;

    return HI_SUCCESS;
}


HI_S32 VPSS_HAL_Set_2DSDFirst_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy)
{
    HI_DRV_VID_FRAME_ADDR_S *pstNext2;
    HI_DRV_VID_FRAME_ADDR_S *pstNext2_LB;

    HI_DRV_VID_FRAME_ADDR_S *pstRef;
    HI_DRV_VID_FRAME_ADDR_S *pstNxt1;

    HI_DRV_VID_FRAME_ADDR_S *pstCur;
    HI_DRV_VID_FRAME_ADDR_S *pstRfr;

    HI_BOOL             bRfrEnableFlag;
    HI_U32              u32PageAddr;
    HI_U32              u32ErrReadAddr;
    HI_U32              u32ErrWriteAddr;
    HI_S32              s32Ret;
    HI_U32              u32DetileBufferAddr;
    VPSS_HAL_FRAME_S    *pInInfo;

    CBB_REG_ADDR_S      stRegAddr;
    CBB_REG_ADDR_S      stRegAddr_MMU;
    CBB_FRAME_S         stFrameCfg;
    CBB_FUNC_TUNNELIN_S stTunnelIn;
    CBB_FUNC_SMMU_S     stSMMUCfg;
    CBB_INFO_S          stMadInfo_Tnr;
    CBB_ALG_INFO_S      stDBInfo;
    CBB_ALG_INFO_S      stDBDETInfo;
    CBB_ALG_INFO_S      stNrInfo;
    CBB_ALG_INFO_S      stSnrInfo;
    CBB_ALG_INFO_S      stTnrInfo;
    CBB_ALG_INFO_S      stMcTnrInfo;
    CBB_ALG_INFO_S      stAlgInfo;
    CBB_ALG_INFO_S      stMcDeiAlgCfg;
    CBB_INFO_S          sttInfoCfg;
    HI_BOOL             bMedsEn = HI_FALSE;

    VPSS_MEM_CLEAR(stRegAddr);
    VPSS_MEM_CLEAR(stRegAddr_MMU);
    VPSS_MEM_CLEAR(stFrameCfg);
    VPSS_MEM_CLEAR(stTunnelIn);
    VPSS_MEM_CLEAR(stSMMUCfg);
    VPSS_MEM_CLEAR(stMadInfo_Tnr);
    VPSS_MEM_CLEAR(stDBInfo);
    VPSS_MEM_CLEAR(stDBDETInfo);
    VPSS_MEM_CLEAR(stNrInfo);
    VPSS_MEM_CLEAR(stSnrInfo);
    VPSS_MEM_CLEAR(stTnrInfo);
    VPSS_MEM_CLEAR(stMcTnrInfo);
    VPSS_MEM_CLEAR(stAlgInfo);
    VPSS_MEM_CLEAR(sttInfoCfg);
    VPSS_MEM_CLEAR(stMcDeiAlgCfg);

    stRegAddr.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr.u32NodePhyAddr = u32AppPhy;
    pInInfo = &(pstHalInfo->stInInfo);

    VPSS_REG_ResetAppReg((S_VPSS_REGS_TYPE *)pu32AppVir, pstHalInfo->pstPqCfg);

    s32Ret = VPSS_HAL_SDDeiBuffer_Alloc(enIP, pstHalInfo, pInInfo->bSecure);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_FATAL("VPSS_HAL_SDDeiBuffer_Alloc fail!\n");
        return s32Ret;
    }

#ifdef HI_VPSS_SMMU_SUPPORT
    if (pInInfo->bSecure)
    {
        u32DetileBufferAddr = pstHalInfo->stSDDeiBuf_TEE.u32StartSmmuAddr;
    }
    else
    {
        u32DetileBufferAddr = pstHalInfo->stSDDeiBuf_MMU.u32StartSmmuAddr;
    }

#else
    u32DetileBufferAddr = pstHalInfo->stSDDeiBuf_MMZ.u32StartPhyAddr;
#endif

    s32Ret = VPSS_HAL_ConfigSDDeiFrame(&(pstHalInfo->stSDDeiFrame),
                                       u32DetileBufferAddr,
                                       pInInfo->u32Width,
                                       pInInfo->u32Height,
                                       pInInfo->enFormat,
                                       pInInfo->enBitWidth);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_FATAL("VPSS_HAL_ConfigSDDeiFrame fail!\n");
        return s32Ret;
    }

    VPSS_REG_ResetAppReg((S_VPSS_REGS_TYPE *)pu32AppVir, pstHalInfo->pstPqCfg);

    /* channel config */
    pstRef      = &pstHalInfo->stInRefInfo[0].stAddr;
    pstCur      = &pstHalInfo->stInRefInfo[1].stAddr;
    pstNxt1     = &pstHalInfo->stInRefInfo[2].stAddr;
    pstNext2    = &pstHalInfo->stInInfo.stAddr;
    pstNext2_LB = &pstHalInfo->stInInfo.stAddr_LB;

#if 0
    HI_PRINT("\n--------------------------------------------\n");
    HI_PRINT("pstRef	phy:%u, vir:%u\n", pstRef->u32PhyAddr_Y, (HI_U32)pstRef->vir_addr_y);
    HI_PRINT("pstCur	phy:%u, vir:%u\n", pstCur->u32PhyAddr_Y, (HI_U32)pstCur->vir_addr_y);
    HI_PRINT("pstNxt1  phy:%u, vir:%u\n", pstNxt1->u32PhyAddr_Y, (HI_U32)pstNxt1->vir_addr_y);
    HI_PRINT("pstNext2  phy:%u, vir:%u\n", pstNext2->u32PhyAddr_Y, (HI_U32)pstNext2->vir_addr_y);
#endif


    VPSS_DBG_INFO("2DSDFst NX2 read from %08x stride %d \n", pstNext2->u32PhyAddr_Y, pstNext2->u32Stride_Y);

    /*tunnel*/
    if (pstHalInfo->stInInfo.u32TunnelAddr)
    {
        stTunnelIn.bEnable = HI_TRUE;
        stTunnelIn.u32ReadInterval = 0;
        stTunnelIn.u32ReadAddr = pstHalInfo->stInInfo.u32TunnelAddr;
    }
    else
    {
        stTunnelIn.bEnable = HI_FALSE;
    }

    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_TUNNEL_IN, (HI_VOID *)&stTunnelIn, HI_NULL);

    //>SD < FHD时, 只开MA-TNR, DEI

    /* db */
    /* db_det */
    stNrInfo.bEnable = HI_FALSE;

    bRfrEnableFlag      = HI_TRUE;
    //snr_en 是db,dm, nr的总开关， SNR包括db,dm,nr
    stSnrInfo.bEnable   = HI_FALSE; //node-seconed enable snr
    stTnrInfo.bEnable   = HI_TRUE;  //开MA-TNR, MC-TNR
    stMcTnrInfo.bEnable = HI_TRUE;

    if (VPSS_HAL_IS_RWZB(pstHalInfo->stRwzbInfo.u32IsRwzb))
    {
        stSnrInfo.bEnable   = HI_FALSE;
        stTnrInfo.bEnable   = HI_FALSE;
    }
    if (HI_FALSE == stTnrInfo.bEnable)
    {
        stMcTnrInfo.bEnable = HI_FALSE;
    }

    /* snr, tnr */
    //In 98mv200 all of SNR,DB,DM use DB'coef addr(VPSS_DB_CTRL).
    stSnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DB_CTRL) - sizeof(HI_U32);
    stSnrInfo.bMad_vfir_en = HI_FALSE;
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_SNR, (HI_VOID *)&stSnrInfo, HI_NULL);

    //TNR分为 MA-TNR,  MC-TNR, MC需要单独设置开关, MA的开关即全局tnr开关
    stTnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_TNR_CONTRL) - sizeof(HI_U32);

    if VPSS_IS_YUV420_FMT(pstHalInfo->stInInfo.enFormat)
    {
        stTnrInfo.u32Ymotionmode = 1;
    }
    else
    {
        stTnrInfo.u32Ymotionmode = 0;
    }

    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_TNR, (HI_VOID *)&stTnrInfo, HI_NULL);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_TNR_MC, (HI_VOID *)&stMcTnrInfo, HI_NULL);

    /* next2 config */
    stFrameCfg.bEn              = HI_TRUE;
    stFrameCfg.bSecure          = pstHalInfo->stInInfo.bSecure;
    stFrameCfg.enBitWidth       = pstHalInfo->stInInfo.enBitWidth;
    stFrameCfg.enPixelFmt       = pstHalInfo->stInInfo.enFormat;    // TODO: 做格式转换
    stFrameCfg.u32Width         = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height        = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.bProgressive     = pstHalInfo->stInInfo.bProgressive;
    stFrameCfg.stOffset.s32X    = 0;
    stFrameCfg.stOffset.s32Y    = 0;
    //   stFrameCfg.bSpecialTile     = pstHalInfo->stInInfo.bSpecField;
    stFrameCfg.bSpecialTile     = HI_FALSE;
    stFrameCfg.bTopFirst = pstHalInfo->stInInfo.bTopFirst;

    if (HI_DRV_FIELD_TOP == pstHalInfo->stInInfo.enFieldMode)
    {
        stFrameCfg.bTop = HI_TRUE;
    }
    else
    {
        stFrameCfg.bTop = HI_FALSE;
    }

    //    HI_PRINT("stFrameCfg.bTopFirst : %u\n", stFrameCfg.bTopFirst);
    //   HI_PRINT("stFrameCfg.bTop : %u\n", stFrameCfg.bTop);

    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y  = pstNext2->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C  = pstNext2->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y   = pstNext2->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C   = pstNext2->u32Stride_C;

#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif

    if ( HI_DRV_PIXEL_BITWIDTH_10BIT == pstHalInfo->stInInfo.enBitWidth )
    {
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_Y   = pstNext2_LB->u32PhyAddr_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_C   = pstNext2_LB->u32PhyAddr_C;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_Y    = pstNext2_LB->u32Stride_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_C    = pstNext2_LB->u32Stride_C;

#ifdef HI_VPSS_SMMU_SUPPORT
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_TRUE;
#else
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_FALSE;
#endif
    }

    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_CMP)
    {
        stFrameCfg.bCompress = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_YHead  = pstNext2->u32PhyAddr_YHead;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_CHead  = pstNext2->u32PhyAddr_CHead;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Head_Size      = pstNext2->u32Head_Size;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Head_Stride    = pstNext2->u32Head_Stride;
#ifdef HI_VPSS_SMMU_SUPPORT
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y   = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C   = HI_TRUE;

        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y    = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C    = HI_TRUE;
#else
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;

        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_FALSE;
#endif
    }
    else
    {
        stFrameCfg.bCompress = HI_FALSE;
    }

    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_NX2, (HI_VOID *)&stFrameCfg, HI_NULL);

    /* rwzb */
    if (pstHalInfo->stRwzbInfo.u32EnRwzb)
    {
        if (VPSS_IS_TILE_FMT(pstHalInfo->stInInfo.enFormat))
        {
            VPSS_HAL_RWZB_Calc(pstHalInfo, &pstHalInfo->stInRefInfo[0].stAddr); //use wbc data(nx1,has been detiled)
        }
        else
        {
            VPSS_HAL_RWZB_Calc(pstHalInfo, pstNext2); //use nx2 data
        }
    }

    /* nx1 config */
    stFrameCfg.bEn              = HI_TRUE;
    stFrameCfg.u32Width     = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height    = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y  = pstNxt1->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C  = pstNxt1->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y   = pstNxt1->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C   = pstNxt1->u32Stride_C;
    stFrameCfg.enPixelFmt = pstHalInfo->stInRefInfo[2].enFormat;
    stFrameCfg.enBitWidth = pstHalInfo->stInRefInfo[2].enBitWidth;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_NX1, (HI_VOID *)&stFrameCfg, HI_NULL);

    /* cur config */
    stFrameCfg.bEn          = HI_TRUE;
    stFrameCfg.u32Width     = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height    = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstCur->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstCur->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstCur->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstCur->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif
    stFrameCfg.enPixelFmt = pstHalInfo->stInRefInfo[1].enFormat;
    stFrameCfg.enBitWidth = pstHalInfo->stInRefInfo[1].enBitWidth;
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_CUR, (HI_VOID *)&stFrameCfg, HI_NULL);

    /* ref config */
    stFrameCfg.bEn          = HI_TRUE;
    stFrameCfg.u32Width     = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height    = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstRef->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstRef->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstRef->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstRef->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif
    stFrameCfg.enPixelFmt = pstHalInfo->stInRefInfo[0].enFormat;
    stFrameCfg.enBitWidth = pstHalInfo->stInRefInfo[0].enBitWidth;
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_REF, (HI_VOID *)&stFrameCfg, HI_NULL);

    /* rfr config */
    stFrameCfg.bEn = HI_TRUE;
    pstRfr = &pstHalInfo->stInWbcInfo.stAddr;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstRfr->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstRfr->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstRfr->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstRfr->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif

    stFrameCfg.enBitWidth = pstHalInfo->stInWbcInfo.enBitWidth;
    stFrameCfg.enPixelFmt = pstHalInfo->stInWbcInfo.enFormat;
    stFrameCfg.u32Width   = pstHalInfo->stInWbcInfo.u32Width;
    stFrameCfg.u32Height  = pstHalInfo->stInWbcInfo.u32Height;
    //    HI_PRINT("wbc   phy:%u, vir:%u\n", pstRfr->u32PhyAddr_Y, (HI_U32)pstRfr->vir_addr_y);
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_WRITE_RFR, (HI_VOID *)&stFrameCfg, &bRfrEnableFlag);

    /* vhd0 config */
    VPSS_HAL_SetPortCfg_SD_First_dei(enIP, stRegAddr, pstHalInfo);

    //逐隔行都要配置
    sttInfoCfg.u32WPhyAddr = pstHalInfo->stSttAddr.u32stt_w_phy_addr;
    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_STT, (HI_VOID *)&sttInfoCfg, (HI_VOID *)HI_NULL);

    VPSS_HAL_SetDeiCfg(enIP, pstHalInfo, stRegAddr);

    if (!VPSS_HAL_IS_RWZB(pstHalInfo->stRwzbInfo.u32IsRwzb))
    {
        VPSS_HAL_SetMcDeiCfg(enIP, pstHalInfo, stRegAddr);
        /* mcdei */
        stMcDeiAlgCfg.bEnable   = HI_TRUE;
        bMedsEn = (stMcTnrInfo.bEnable || stMcDeiAlgCfg.bEnable);
        VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_MCDEI, (HI_VOID *)&stMcDeiAlgCfg, &bMedsEn);
    }

    if (bMedsEn)
    {
        VPSS_HAL_SetRgmvCfg(enIP, pstHalInfo, stRegAddr);
    }
    if (!VPSS_HAL_IS_RWZB(pstHalInfo->stRwzbInfo.u32IsRwzb))
    {
        /* igbm */
        stAlgInfo.bEnable = HI_TRUE;
        VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_IGBM, (HI_VOID *)&stAlgInfo, HI_NULL);

        /* ifmd */
        stAlgInfo.bEnable = HI_TRUE;
        VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_IFMD, (HI_VOID *)&stAlgInfo, HI_NULL);
    }
    /* smmu */
#ifdef HI_VPSS_SMMU_SUPPORT
    stSMMUCfg.bGlobalBypass = HI_FALSE;
    stSMMUCfg.bIntEnable = HI_TRUE;
    stSMMUCfg.u32Ptw_pf = 0x3;

    HI_DRV_SMMU_GetPageTableAddr(&u32PageAddr, &u32ErrReadAddr, &u32ErrWriteAddr);
    stSMMUCfg.u32CB_TTBR = stSMMUCfg.u32SCB_TTBR = u32PageAddr;
    stSMMUCfg.u32Err_s_rd_addr = stSMMUCfg.u32Err_ns_rd_addr = u32ErrReadAddr;
    stSMMUCfg.u32Err_s_wr_addr = stSMMUCfg.u32Err_ns_wr_addr = u32ErrWriteAddr;
#else
    stSMMUCfg.bGlobalBypass = HI_TRUE;
    stSMMUCfg.bIntEnable = HI_FALSE;
#endif
    stRegAddr_MMU.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr_MMU.pu8BaseVirAddr = stHalCtx[enIP][0].pu8BaseRegVir;
    VPSS_CBB_FUNC_SetConfig(stRegAddr_MMU, CBB_FUNC_SMMU, (HI_VOID *)&stSMMUCfg, HI_NULL);

    /* tnr mad */
    stMadInfo_Tnr.bEn    = stTnrInfo.bEnable;
    stMadInfo_Tnr.u32Wth = pstHalInfo->stInInfo.u32Width;
    stMadInfo_Tnr.u32Hgt = pstHalInfo->stInInfo.u32Height / 2;
    stMadInfo_Tnr.u32RPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Tnrmad_raddr;
    stMadInfo_Tnr.u32WPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Tnrmad_waddr;
    stMadInfo_Tnr.u32Stride   = pstHalInfo->stNrInfo.stNrMadCfg.u32madstride;
    VPSS_DBG_INFO("TnrMad.RP : %#x, TnrMad.WP : %#x. stride%d\n", stMadInfo_Tnr.u32RPhyAddr, stMadInfo_Tnr.u32WPhyAddr, stMadInfo_Tnr.u32Stride);
#ifdef HI_VPSS_SMMU_SUPPORT
    stMadInfo_Tnr.bSmmu_R = HI_TRUE;
    stMadInfo_Tnr.bSmmu_W = HI_TRUE;
#else
    stMadInfo_Tnr.bSmmu_R = HI_FALSE;
    stMadInfo_Tnr.bSmmu_W = HI_FALSE;
#endif
    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_TNR_MAD, (HI_VOID *)&stMadInfo_Tnr, HI_NULL);

    return HI_SUCCESS;
}

//HI_U32 g_u32DbgTemCnt = 0;
//HI_DRV_VIDEO_FRAME_S g_DbgstFrame;

HI_S32 VPSS_HAL_Set_2DSDSecond_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy)
{
    HI_DRV_VID_FRAME_ADDR_S *pstNext2;
    HI_DRV_VID_FRAME_ADDR_S *pstNext2_LB;

    HI_BOOL bRfrEnableFlag;
    HI_U32 u32PageAddr;
    HI_U32 u32ErrReadAddr;
    HI_U32 u32ErrWriteAddr;

    CBB_REG_ADDR_S      stRegAddr;
    CBB_REG_ADDR_S      stRegAddr_MMU;
    CBB_FRAME_S         stFrameCfg;
    CBB_FUNC_TUNNELIN_S stTunnelIn;
    CBB_FUNC_SMMU_S     stSMMUCfg;
    CBB_INFO_S          stMadInfo_Tnr;
    CBB_INFO_S          stMadInfo_Snr;
    CBB_ALG_INFO_S      stDBInfo;
    CBB_ALG_INFO_S      stDBDETInfo;
    CBB_ALG_INFO_S      stNrInfo;
    CBB_ALG_INFO_S      stSnrInfo;
    CBB_ALG_INFO_S      stTnrInfo;
    CBB_ALG_INFO_S      stMcTnrInfo;
    CBB_ALG_INFO_S      stAlgInfo;
    CBB_INFO_S          sttInfoCfg;
    CBB_ALG_INFO_S      stMcDeiAlgCfg;
    CBB_ALG_INFO_S      stDeiAlgCfg;
    CBB_ALG_INFO_S      stHdrInfo;


    VPSS_MEM_CLEAR(stRegAddr);
    VPSS_MEM_CLEAR(stRegAddr_MMU);
    VPSS_MEM_CLEAR(stFrameCfg);
    VPSS_MEM_CLEAR(stTunnelIn);
    VPSS_MEM_CLEAR(stSMMUCfg);
    VPSS_MEM_CLEAR(stMadInfo_Tnr);
    VPSS_MEM_CLEAR(stMadInfo_Snr);
    VPSS_MEM_CLEAR(stDBInfo);
    VPSS_MEM_CLEAR(stDBDETInfo);
    VPSS_MEM_CLEAR(stNrInfo);
    VPSS_MEM_CLEAR(stSnrInfo);
    VPSS_MEM_CLEAR(stTnrInfo);
    VPSS_MEM_CLEAR(stMcTnrInfo);
    VPSS_MEM_CLEAR(stAlgInfo);
    VPSS_MEM_CLEAR(sttInfoCfg);
    VPSS_MEM_CLEAR(stMcDeiAlgCfg);
    VPSS_MEM_CLEAR(stDeiAlgCfg);
    VPSS_MEM_CLEAR(stHdrInfo);

    stRegAddr.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr.u32NodePhyAddr = u32AppPhy;

    VPSS_REG_ResetAppReg((S_VPSS_REGS_TYPE *)pu32AppVir, pstHalInfo->pstPqCfg);

    /* channel config */
    pstNext2    = &(pstHalInfo->stSDDeiFrame.stAddr);
    pstNext2_LB = &(pstHalInfo->stSDDeiFrame.stAddr_LB);

#if 0

    if (g_u32DbgTemCnt++ == 200)
    {
        HI_U8 chFile[32] = "vpss_sddei_node2_in.yuv";
        VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
        HI_U64  u64Addr;


        pstHalCtx = &stHalCtx[enIP][0];

        g_DbgstFrame.u32Width = pstHalInfo->stSDDeiFrame.u32Width;
        g_DbgstFrame.u32Height = pstHalInfo->stSDDeiFrame.u32Height;
        g_DbgstFrame.ePixFormat = HI_DRV_PIX_FMT_NV21;
        g_DbgstFrame.enBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;

        u64Addr = (unsigned long)pstHalCtx->stSDDeiBuf_MMU.pu8StartVirAddr;
        g_DbgstFrame.stBufAddr[0].vir_addr_y = u64Addr;
        g_DbgstFrame.stBufAddr[0].vir_addr_c = (u64Addr + 720 * 576);

        g_DbgstFrame.stBufAddr[0].u32Stride_Y = pstHalInfo->stSDDeiFrame.stAddr.u32Stride_Y;
        g_DbgstFrame.stBufAddr[0].u32Stride_C = pstHalInfo->stSDDeiFrame.stAddr.u32Stride_C;

        VPSS_OSAL_WRITEYUV(&g_DbgstFrame, chFile);
    }

#endif

#if 0
    HI_PRINT("pstRef	phy:%u, vir:%u\n", pstRef->u32PhyAddr_Y, (HI_U32)pstRef->vir_addr_y);
    HI_PRINT("pstCur	phy:%u, vir:%u\n", pstCur->u32PhyAddr_Y, (HI_U32)pstCur->vir_addr_y);
    HI_PRINT("pstNxt1  phy:%u, vir:%u\n", pstNxt1->u32PhyAddr_Y, (HI_U32)pstNxt1->vir_addr_y);
    HI_PRINT("pstNext2  phy:%u, vir:%u\n", pstNext2->u32PhyAddr_Y, (HI_U32)pstNext2->vir_addr_y);
#endif

    /*tunnel*/
    stTunnelIn.bEnable = HI_FALSE; //second node's tunnel-in fix to disable
    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_TUNNEL_IN, (HI_VOID *)&stTunnelIn, HI_NULL);

    //>SD < FHD时, 只开MA-TNR, DEI

    /* db */
    /* db_det */
    stDBDETInfo.bEnable = HI_TRUE;
    stDBInfo.bEnable = HI_TRUE;
    stNrInfo.bEnable = HI_TRUE;

    if (VPSS_HAL_IS_RWZB(pstHalInfo->stRwzbInfo.u32IsRwzb))
    {
        stDBDETInfo.bEnable = HI_FALSE;
        stDBInfo.bEnable = HI_FALSE;
        stNrInfo.bEnable = HI_FALSE;
    }
    /* 各模块使能 */
    bRfrEnableFlag      = HI_FALSE;
    //snr_en 是db,dm, nr的总开关， SNR包括db,dm,nr
    stSnrInfo.bEnable   = HI_TRUE;
    stTnrInfo.bEnable   = HI_FALSE;
    stMcTnrInfo.bEnable = HI_FALSE;

    if (VPSS_IS_YUV422_FMT(pstHalInfo->stInInfo.enFormat))
    {
        stDBDETInfo.bEnable = HI_FALSE;
        stDBInfo.bEnable    = HI_FALSE;
        stSnrInfo.bEnable   = HI_FALSE;
    }

    if (VPSS_HAL_IS_RWZB(pstHalInfo->stRwzbInfo.u32IsRwzb))
    {
        stSnrInfo.bEnable   = HI_FALSE;
        stTnrInfo.bEnable   = HI_FALSE;
    }
    //------------------------------------------------------
    //stSnrInfo.bEnable = pstHalInfo->stNrInfo.bSnrEn | pstHalInfo->stNrInfo.bDbEn | pstHalInfo->stNrInfo.bDmEn;
    //u32SnrCfg = pstHalInfo->stNrInfo.bDbDEn + (pstHalInfo->stDieInfo.bEnable << 1);
    //VPSS_INFO("bDbDEn = %d, bDieEn = %d, u32SnrCfg = %d.\n", pstHalInfo->stNrInfo.bDbDEn, pstHalInfo->stDieInfo.bEnable, u32SnrCfg);
    //    stSnrInfo.bEnable = HI_TRUE;
    stSnrInfo.bMad_vfir_en = HI_TRUE;
    stSnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL,
                            VPSS_DB_CTRL) - sizeof(HI_U32);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_SNR, (HI_VOID *)&stSnrInfo, HI_NULL);

    stHdrInfo.bEnable = pstHalInfo->stHdrInfo.bEnable;
    stHdrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_LCHDR_CTRL) - sizeof(HI_U32);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_HDR, (HI_VOID *)&stHdrInfo, & pstHalInfo->stHdrInfo.bHdrIn);
    //------------------------------------------------------

    /* snr, tnr */
    //In 98mv200 all of SNR,DB,DM use DB'coef addr(VPSS_DB_CTRL).
    // stSnrInfo.u32ParaAddr = u32AppPhy +  u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL,  VPSS_DB_CTRL);;
    // VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_SNR, (HI_VOID *)&stSnrInfo, HI_NULL);

    //TNR分为 MA-TNR,  MC-TNR, MC需要单独设置开关, MA的开关即全局tnr开关
    stTnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_TNR_CONTRL) - sizeof(HI_U32);

    if VPSS_IS_YUV420_FMT(pstHalInfo->stInInfo.enFormat)
    {
        stTnrInfo.u32Ymotionmode = 1;
    }
    else
    {
        stTnrInfo.u32Ymotionmode = 0;
    }

    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_TNR, (HI_VOID *)&stTnrInfo, HI_NULL);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_TNR_MC, (HI_VOID *)&stMcTnrInfo, HI_NULL);


    /* next2 config */
    stFrameCfg.bEn              = HI_TRUE;
    stFrameCfg.bSecure          = pstHalInfo->stInInfo.bSecure;
    stFrameCfg.enBitWidth       = pstHalInfo->stSDDeiFrame.enBitWidth;
    stFrameCfg.enPixelFmt       = pstHalInfo->stSDDeiFrame.enFormat;

    stFrameCfg.u32Width         = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height        = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.bProgressive     = HI_TRUE;
    stFrameCfg.stOffset.s32X    = 0;
    stFrameCfg.stOffset.s32Y    = 0;


    stFrameCfg.bTopFirst = pstHalInfo->stInInfo.bTopFirst;

    if (HI_DRV_FIELD_TOP == pstHalInfo->stInInfo.enFieldMode)
    {
        stFrameCfg.bTop = HI_TRUE;
    }
    else
    {
        stFrameCfg.bTop = HI_FALSE;
    }

    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y  = pstNext2->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C  = pstNext2->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y   = pstNext2->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C   = pstNext2->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif
#if 0
    HI_PRINT("VPSS sd snd read addr Y C stridY stridC %x %x %d %d\n",
             stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y,
             stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C,
             stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y,
             stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C);
#endif

    if ( HI_DRV_PIXEL_BITWIDTH_10BIT == pstHalInfo->stInInfo.enBitWidth )
    {
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_Y   = pstNext2_LB->u32PhyAddr_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_C   = pstNext2_LB->u32PhyAddr_C;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_Y    = pstNext2_LB->u32Stride_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_C    = pstNext2_LB->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_TRUE;
#else
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_FALSE;
#endif
    }

    stFrameCfg.bCompress = HI_FALSE;
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_NX2, (HI_VOID *)&stFrameCfg, HI_NULL);


    /* nx1 config */
    //no need to cfg nx1
    /* cur config */
    //no need to cfg cur
    /* ref config */
    //no need to cfg ref

    /* rfr config */
    //DO　NOT!!! cfg rfr

    /* vhd0 config */
    VPSS_HAL_SetPortCfg(enIP, stRegAddr, pstHalInfo);

    //逐隔行都要配置
    sttInfoCfg.u32WPhyAddr = pstHalInfo->stSttAddr.u32stt_w_phy_addr;
    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_STT, (HI_VOID *)&sttInfoCfg, (HI_VOID *)HI_NULL);


    stDeiAlgCfg.bEnable     = HI_FALSE;
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_DEI, (HI_VOID *)&stDeiAlgCfg, HI_NULL);

    stMcDeiAlgCfg.bEnable   = HI_FALSE;
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_MCDEI, (HI_VOID *)&stMcDeiAlgCfg, HI_NULL);

    /* igbm */
    stAlgInfo.bEnable = HI_FALSE;
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_IGBM, (HI_VOID *)&stAlgInfo, HI_NULL);

    /* ifmd */
    stAlgInfo.bEnable = HI_FALSE;
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_IFMD, (HI_VOID *)&stAlgInfo, HI_NULL);

    /* smmu */
#ifdef HI_VPSS_SMMU_SUPPORT
    stSMMUCfg.bGlobalBypass = HI_FALSE;
    stSMMUCfg.bIntEnable = HI_TRUE;
    stSMMUCfg.u32Ptw_pf = 0x3;

    HI_DRV_SMMU_GetPageTableAddr(&u32PageAddr, &u32ErrReadAddr, &u32ErrWriteAddr);
    stSMMUCfg.u32CB_TTBR = stSMMUCfg.u32SCB_TTBR = u32PageAddr;
    stSMMUCfg.u32Err_s_rd_addr = stSMMUCfg.u32Err_ns_rd_addr = u32ErrReadAddr;
    stSMMUCfg.u32Err_s_wr_addr = stSMMUCfg.u32Err_ns_wr_addr = u32ErrWriteAddr;
#else
    stSMMUCfg.bGlobalBypass = HI_TRUE;
    stSMMUCfg.bIntEnable = HI_FALSE;
#endif

    stRegAddr_MMU.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr_MMU.pu8BaseVirAddr = stHalCtx[enIP][0].pu8BaseRegVir;
    VPSS_CBB_FUNC_SetConfig(stRegAddr_MMU, CBB_FUNC_SMMU, (HI_VOID *)&stSMMUCfg, HI_NULL);

    /* snr mad */
    stMadInfo_Snr.bEn    = HI_TRUE;
    stMadInfo_Snr.u32Wth = pstHalInfo->stInInfo.u32Width;
    // stMadInfo_Snr.u32Hgt = (pstHalInfo->stDieInfo.bEnable) ? pstHalInfo->stInInfo.u32Height / 2 : pstHalInfo->stInInfo.u32Height;
    stMadInfo_Snr.u32Hgt =  pstHalInfo->stInInfo.u32Height / 2 ;
    if (pstHalInfo->stInInfo.bProgressive)
    {
        stMadInfo_Snr.u32RPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Tnrmad_waddr;
    }
    else
    {
        stMadInfo_Snr.u32RPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Tnrmad_raddr;
    }
    stMadInfo_Snr.u32Stride   = pstHalInfo->stNrInfo.stNrMadCfg.u32madstride;

    //VPSS_FATAL("SnrMad.RP : %#x  stride:%d.\n", stMadInfo_Snr.u32RPhyAddr, stMadInfo_Snr.u32Stride );

#ifdef HI_VPSS_SMMU_SUPPORT
    stMadInfo_Snr.bSmmu_R = HI_TRUE;
    stMadInfo_Snr.bSmmu_W = HI_TRUE;
#else
    stMadInfo_Snr.bSmmu_R = HI_FALSE;
    stMadInfo_Snr.bSmmu_W = HI_FALSE;
#endif
    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_SNR_MAD, (HI_VOID *)&stMadInfo_Snr, HI_NULL);


    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_Set_CTS10_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy)
{
    HI_DRV_VID_FRAME_ADDR_S *pstNext2;
    HI_DRV_VID_FRAME_ADDR_S *pstNext2_LB;
    //  HI_DRV_VID_FRAME_ADDR_S *pstCur;
    //  HI_DRV_VID_FRAME_ADDR_S *pstRfr;

    HI_BOOL bRfrEnableFlag;
    HI_U32 u32PageAddr;
    HI_U32 u32ErrReadAddr;
    HI_U32 u32ErrWriteAddr;

    CBB_REG_ADDR_S      stRegAddr;
    CBB_REG_ADDR_S      stRegAddr_MMU;
    CBB_FRAME_S         stFrameCfg;
    CBB_FUNC_TUNNELIN_S stTunnelIn;
    CBB_FUNC_SMMU_S     stSMMUCfg;
    CBB_INFO_S          stMadInfo_Tnr;
    CBB_INFO_S          stMadInfo_Snr;
    CBB_ALG_INFO_S      stDBInfo;
    CBB_ALG_INFO_S      stDBDETInfo;
    CBB_ALG_INFO_S      stNrInfo;
    CBB_ALG_INFO_S      stSnrInfo;
    CBB_ALG_INFO_S      stTnrInfo;
    CBB_ALG_INFO_S      stMcTnrInfo;
    CBB_ALG_INFO_S      stIfmdInfo;
    CBB_INFO_S          sttInfoCfg;
    CBB_FUNC_CTS10BIT_S stFuncCTS10bitCfg;
    CBB_FUNC_4PIXEL_S   stFunc4PixelCfg;

    VPSS_MEM_CLEAR(stRegAddr);
    VPSS_MEM_CLEAR(stRegAddr_MMU);
    VPSS_MEM_CLEAR(stFrameCfg);
    VPSS_MEM_CLEAR(stTunnelIn);
    VPSS_MEM_CLEAR(stSMMUCfg);
    VPSS_MEM_CLEAR(stMadInfo_Tnr);
    VPSS_MEM_CLEAR(stMadInfo_Snr);
    VPSS_MEM_CLEAR(stDBInfo);
    VPSS_MEM_CLEAR(stDBDETInfo);
    VPSS_MEM_CLEAR(stNrInfo);
    VPSS_MEM_CLEAR(stSnrInfo);
    VPSS_MEM_CLEAR(stTnrInfo);
    VPSS_MEM_CLEAR(stMcTnrInfo);
    VPSS_MEM_CLEAR(stIfmdInfo);
    VPSS_MEM_CLEAR(sttInfoCfg);
    VPSS_MEM_CLEAR(stFuncCTS10bitCfg);
    VPSS_MEM_CLEAR(stFunc4PixelCfg);

    stRegAddr.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr.u32NodePhyAddr = u32AppPhy;

    //4p/c 区分不同的NODE 开关, cts. 4k缩放

    VPSS_REG_ResetAppReg((S_VPSS_REGS_TYPE *)pu32AppVir, pstHalInfo->pstPqCfg);

    /*tunnel*/

    stTunnelIn.bEnable = HI_FALSE;
    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_TUNNEL_IN, (HI_VOID *)&stTunnelIn, HI_NULL);

    /* db */
    /* db_det */
    stDBDETInfo.bEnable = HI_FALSE;
    stDBInfo.bEnable    = HI_FALSE;
    stNrInfo.bEnable    = HI_FALSE;
    stSnrInfo.bEnable   = HI_FALSE;  //此时打开SNR也没有意义
    stTnrInfo.bEnable   = HI_FALSE;

    stDBInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DB_CTRL) - sizeof(HI_U32);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_DB, (HI_VOID *)&stDBInfo, HI_NULL);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_DB_DET, (HI_VOID *)&stDBDETInfo, HI_NULL);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_NR, (HI_VOID *)&stNrInfo, HI_NULL);

    bRfrEnableFlag      = HI_FALSE;
    //snr_en 是db,dm, nr的总开关， SNR包括db,dm,nr
    stMcTnrInfo.bEnable = HI_FALSE;

    switch (pstHalInfo->stInInfo.enFormat)
    {
        case HI_DRV_PIX_FMT_NV12_TILE: /* 12 tile  */
        case HI_DRV_PIX_FMT_NV21_TILE: /* 21 tile  */
        case HI_DRV_PIX_FMT_YUV400_TILE: /* 21 tile  */
        case HI_DRV_PIX_FMT_NV12_TILE_CMP:
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:
            stTnrInfo.bEnable = HI_FALSE;
            break;

        default:
            break;
    }

    /* snr, tnr */
    //In 98mv200 all of SNR,DB,DM use DB'coef addr(VPSS_DB_CTRL).
    stSnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DB_CTRL) - sizeof(HI_U32);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_SNR, (HI_VOID *)&stSnrInfo, HI_NULL);

    //TNR分为 MA-TNR,  MC-TNR, MC需要单独设置开关, MA的开关即全局tnr开关
    stTnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_TNR_CONTRL) - sizeof(HI_U32);

    if VPSS_IS_YUV420_FMT(pstHalInfo->stInInfo.enFormat)
    {
        stTnrInfo.u32Ymotionmode = 1;
    }
    else
    {
        stTnrInfo.u32Ymotionmode = 0;
    }

    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_TNR, (HI_VOID *)&stTnrInfo, HI_NULL);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_TNR_MC, (HI_VOID *)&stMcTnrInfo, HI_NULL);

    /* ifmd */
    stIfmdInfo.bEnable = HI_FALSE;
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_IFMD, (HI_VOID *)&stIfmdInfo, HI_NULL);

    /* next2 config */
    pstNext2 = &pstHalInfo->stInInfo.stAddr;
    pstNext2_LB = &pstHalInfo->stInInfo.stAddr_LB;

    stFrameCfg.bSecure          = pstHalInfo->stInInfo.bSecure;
    stFrameCfg.enBitWidth       = pstHalInfo->stInInfo.enBitWidth;
    stFrameCfg.enPixelFmt       = pstHalInfo->stInInfo.enFormat;    // TODO: 做格式转换
    stFrameCfg.u32Width         = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height        = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.bProgressive     = pstHalInfo->stInInfo.bProgressive;
    stFrameCfg.stOffset.s32X    = 0;
    stFrameCfg.stOffset.s32Y    = 0;


    stFrameCfg.bTopFirst = pstHalInfo->stInInfo.bTopFirst;

    if (HI_DRV_FIELD_TOP == pstHalInfo->stInInfo.enFieldMode)
    {
        stFrameCfg.bTop = HI_TRUE;
    }
    else
    {
        stFrameCfg.bTop = HI_FALSE;
    }

    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y  = pstNext2->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C  = pstNext2->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y   = pstNext2->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C   = pstNext2->u32Stride_C;

    if (( HI_DRV_PIXEL_BITWIDTH_10BIT == pstHalInfo->stInInfo.enBitWidth )
        || ( HI_DRV_PIXEL_BITWIDTH_10BIT_CTS == pstHalInfo->stInInfo.enBitWidth ))
    {
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_Y   = pstNext2_LB->u32PhyAddr_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_C   = pstNext2_LB->u32PhyAddr_C;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_Y    = pstNext2_LB->u32Stride_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_C    = pstNext2_LB->u32Stride_C;
    }

    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_CMP)

    {
        stFrameCfg.bCompress = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_YHead  = pstNext2->u32PhyAddr_YHead;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_CHead  = pstNext2->u32PhyAddr_CHead;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Head_Size      = pstNext2->u32Head_Size;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Head_Stride    = pstNext2->u32Head_Stride;
    }
    else
    {
        stFrameCfg.bCompress = HI_FALSE;
    }

    VPSS_DBG_INFO("NX2 read from %x %x %d %d\n",
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y,
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C,
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y,
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C);

    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_NX2, (HI_VOID *)&stFrameCfg, HI_NULL);


    stFuncCTS10bitCfg.bEnable = HI_TRUE;
    stFuncCTS10bitCfg.bBitSel_LOW10 = HI_FALSE;
    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_CTS10BIT, (HI_VOID *)&stFuncCTS10bitCfg, HI_NULL);

    stFunc4PixelCfg.bEnable = HI_TRUE;
    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_SPEED_UP_4PIXEL, (HI_VOID *)&stFunc4PixelCfg, HI_NULL);

    /* vhd0 config */
    VPSS_HAL_SetPortCfg_CTS10Bit(stRegAddr, pstHalInfo);

    //逐隔行都要配置
    sttInfoCfg.u32WPhyAddr = pstHalInfo->stSttAddr.u32stt_w_phy_addr;
    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_STT, (HI_VOID *)&sttInfoCfg, (HI_VOID *)HI_NULL);

    /* smmu */
#ifdef HI_VPSS_SMMU_SUPPORT
    stSMMUCfg.bGlobalBypass = HI_FALSE;
    stSMMUCfg.bIntEnable = HI_TRUE;
    stSMMUCfg.u32Ptw_pf = 0x3;
    stSMMUCfg.u32BypassFlag_RCH = 0x0;
    stSMMUCfg.u32BypassFlag_WCH = 0x0;

    HI_DRV_SMMU_GetPageTableAddr(&u32PageAddr, &u32ErrReadAddr, &u32ErrWriteAddr);
    stSMMUCfg.u32CB_TTBR = stSMMUCfg.u32SCB_TTBR = u32PageAddr;
    stSMMUCfg.u32Err_s_rd_addr = stSMMUCfg.u32Err_ns_rd_addr = u32ErrReadAddr;
    stSMMUCfg.u32Err_s_wr_addr = stSMMUCfg.u32Err_ns_wr_addr = u32ErrWriteAddr;
#else
    stSMMUCfg.bGlobalBypass = HI_TRUE;
    stSMMUCfg.bIntEnable = HI_FALSE;
    stSMMUCfg.u32BypassFlag_RCH = 0xffffffff;
    stSMMUCfg.u32BypassFlag_WCH = 0xffffffff;
#endif

    stRegAddr_MMU.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr_MMU.pu8BaseVirAddr = stHalCtx[enIP][0].pu8BaseRegVir;
    VPSS_CBB_FUNC_SetConfig(stRegAddr_MMU, CBB_FUNC_SMMU, (HI_VOID *)&stSMMUCfg, HI_NULL);


    /* tnr mad */
    stMadInfo_Tnr.u32RPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Tnrmad_raddr;
    stMadInfo_Tnr.u32WPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Tnrmad_waddr;
    stMadInfo_Tnr.u32Stride   = pstHalInfo->stNrInfo.stNrMadCfg.u32madstride;
    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_TNR_MAD, (HI_VOID *)&stMadInfo_Tnr, HI_NULL);

    if (stSnrInfo.bEnable)
    {
        /* snr mad */
        stMadInfo_Snr.u32RPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Snrmad_raddr;
        stMadInfo_Snr.u32Stride   = pstHalInfo->stNrInfo.stNrMadCfg.u32madstride;
        VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_SNR_MAD, (HI_VOID *)&stMadInfo_Snr, HI_NULL);
    }

    return HI_SUCCESS;
}


//VPSS_HAL_NODE_2D_UHD = 11,     //4K
HI_S32 VPSS_HAL_Set_2D_UHDFrame_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy)
{
    HI_DRV_VID_FRAME_ADDR_S *pstNext2;
    HI_DRV_VID_FRAME_ADDR_S *pstNext2_LB;
    //    HI_DRV_VID_FRAME_ADDR_S *pstCur;
    //    HI_DRV_VID_FRAME_ADDR_S *pstRfr;

    HI_U32 u32PageAddr;
    HI_U32 u32ErrReadAddr;
    HI_U32 u32ErrWriteAddr;

    CBB_REG_ADDR_S      stRegAddr;
    CBB_REG_ADDR_S      stRegAddr_MMU;
    CBB_FRAME_S         stFrameCfg;
    CBB_FUNC_TUNNELIN_S stTunnelIn;
    CBB_FUNC_SMMU_S     stSMMUCfg;
    CBB_INFO_S          stMadInfo_Tnr;
    CBB_INFO_S          stMadInfo_Snr;
    CBB_ALG_INFO_S      stDBInfo;
    CBB_ALG_INFO_S      stDBDETInfo;
    CBB_ALG_INFO_S      stNrInfo;
    CBB_ALG_INFO_S      stSnrInfo;
    CBB_ALG_INFO_S      stTnrInfo;
    CBB_ALG_INFO_S      stMcTnrInfo;
    CBB_ALG_INFO_S      stIfmdInfo;
    CBB_FUNC_4PIXEL_S   stFunc4PixelCfg;
    CBB_INFO_S          sttInfoCfg;

    VPSS_MEM_CLEAR(stRegAddr);
    VPSS_MEM_CLEAR(stRegAddr_MMU);
    VPSS_MEM_CLEAR(stFrameCfg);
    VPSS_MEM_CLEAR(stTunnelIn);
    VPSS_MEM_CLEAR(stSMMUCfg);
    VPSS_MEM_CLEAR(stMadInfo_Tnr);
    VPSS_MEM_CLEAR(stMadInfo_Snr);
    VPSS_MEM_CLEAR(stDBInfo);
    VPSS_MEM_CLEAR(stDBDETInfo);
    VPSS_MEM_CLEAR(stNrInfo);
    VPSS_MEM_CLEAR(stSnrInfo);
    VPSS_MEM_CLEAR(stTnrInfo);
    VPSS_MEM_CLEAR(stMcTnrInfo);
    VPSS_MEM_CLEAR(stIfmdInfo);
    VPSS_MEM_CLEAR(sttInfoCfg);
    VPSS_MEM_CLEAR(stFunc4PixelCfg);

    stRegAddr.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr.u32NodePhyAddr = u32AppPhy;

    VPSS_REG_ResetAppReg((S_VPSS_REGS_TYPE *)pu32AppVir, pstHalInfo->pstPqCfg);

    /*tunnel*/
    if (pstHalInfo->stInInfo.u32TunnelAddr)
    {
        stTunnelIn.bEnable = HI_TRUE;
        stTunnelIn.u32ReadInterval = 0;
        stTunnelIn.u32ReadAddr = pstHalInfo->stInInfo.u32TunnelAddr;
    }
    else
    {
        stTunnelIn.bEnable = HI_FALSE;
    }

    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_TUNNEL_IN, (HI_VOID *)&stTunnelIn, HI_NULL);

    /* db */
    /* db_det */
    stDBDETInfo.bEnable = HI_FALSE;
    stDBInfo.bEnable = HI_FALSE;
    stNrInfo.bEnable = HI_FALSE;
    stSnrInfo.bEnable   = HI_FALSE; //D1 720以上都是逐行，不开
    stTnrInfo.bEnable   = HI_FALSE;
    stMcTnrInfo.bEnable = HI_FALSE;

    stDBInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DB_CTRL) - sizeof(HI_U32);
    // VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_DB, (HI_VOID *)&stDBInfo, HI_NULL);
    // VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_DB_DET, (HI_VOID *)&stDBDETInfo, HI_NULL);
    // VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_NR, (HI_VOID *)&stNrInfo, HI_NULL);


    /* snr, tnr */
    //In 98mv200 all of SNR,DB,DM use DB'coef addr(VPSS_DB_CTRL).
    stSnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DB_CTRL) - sizeof(HI_U32);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_SNR, (HI_VOID *)&stSnrInfo, HI_NULL);

    //TNR分为 MA-TNR,  MC-TNR, MC需要单独设置开关, MA的开关即全局tnr开关
    stTnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_TNR_CONTRL) - sizeof(HI_U32);

    if VPSS_IS_YUV420_FMT(pstHalInfo->stInInfo.enFormat)
    {
        stTnrInfo.u32Ymotionmode = 1;
    }
    else
    {
        stTnrInfo.u32Ymotionmode = 0;
    }

    if ( HI_DRV_PIXEL_BITWIDTH_10BIT == pstHalInfo->stInInfo.enBitWidth )
    {
        stTnrInfo.bEnable = HI_FALSE;
    }

    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_TNR, (HI_VOID *)&stTnrInfo, HI_NULL);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_TNR_MC, (HI_VOID *)&stMcTnrInfo, HI_NULL);

    /* ifmd */
    stIfmdInfo.bEnable = HI_FALSE;
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_IFMD, (HI_VOID *)&stIfmdInfo, HI_NULL);

    /* next2 config */
    pstNext2 = &pstHalInfo->stInInfo.stAddr;
    pstNext2_LB = &pstHalInfo->stInInfo.stAddr_LB;
    stFrameCfg.bEn              = HI_TRUE;
    stFrameCfg.bSecure          = pstHalInfo->stInInfo.bSecure;
    stFrameCfg.enBitWidth       = pstHalInfo->stInInfo.enBitWidth;
    stFrameCfg.enPixelFmt       = pstHalInfo->stInInfo.enFormat;    // TODO: 做格式转换
    stFrameCfg.u32Width         = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height        = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.bProgressive     = pstHalInfo->stInInfo.bProgressive;
    stFrameCfg.stOffset.s32X    = 0;
    stFrameCfg.stOffset.s32Y    = 0;


    stFrameCfg.bTopFirst = pstHalInfo->stInInfo.bTopFirst;

    if (HI_DRV_FIELD_TOP == pstHalInfo->stInInfo.enFieldMode)
    {
        stFrameCfg.bTop = HI_TRUE;
    }
    else
    {
        stFrameCfg.bTop = HI_FALSE;
    }

    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y  = pstNext2->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C  = pstNext2->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y   = pstNext2->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C   = pstNext2->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif

    if ( HI_DRV_PIXEL_BITWIDTH_10BIT == pstHalInfo->stInInfo.enBitWidth )
    {
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_Y   = pstNext2_LB->u32PhyAddr_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_C   = pstNext2_LB->u32PhyAddr_C;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_Y    = pstNext2_LB->u32Stride_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_C    = pstNext2_LB->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_TRUE;
#else
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_FALSE;
#endif

    }

    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_CMP)

    {
        stFrameCfg.bCompress = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_YHead  = pstNext2->u32PhyAddr_YHead;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_CHead  = pstNext2->u32PhyAddr_CHead;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Head_Size      = pstNext2->u32Head_Size;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Head_Stride    = pstNext2->u32Head_Stride;
    }
    else
    {
        stFrameCfg.bCompress = HI_FALSE;
    }

    VPSS_DBG_INFO("2DNode nx2 read from %08x %08x %d %d\n",
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y,
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C,
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y,
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C);

    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_NX2, (HI_VOID *)&stFrameCfg, HI_NULL);

    /* rwzb */
    if (pstHalInfo->stRwzbInfo.u32EnRwzb)
    {
        if (VPSS_IS_TILE_FMT(pstHalInfo->stInInfo.enFormat))
        {
            VPSS_HAL_RWZB_Calc(pstHalInfo, &pstHalInfo->stInRefInfo[0].stAddr); //use wbc data(nx1,has been detiled)
        }
        else
        {
            VPSS_HAL_RWZB_Calc(pstHalInfo, pstNext2); //use nx2 data
        }
    }

    /* nx1 config */
    /* no need to config nx1 in 2DFrame */
#if 0

    /* cur config */
    pstCur = &pstHalInfo->stInRefInfo[0].stAddr;
    stFrameCfg.bEn = HI_TRUE;
    stFrameCfg.u32Width     = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height    = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstCur->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstCur->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstCur->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstCur->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif

    stFrameCfg.enPixelFmt = pstHalInfo->stInRefInfo[0].enFormat;
    stFrameCfg.enBitWidth = pstHalInfo->stInRefInfo[0].enBitWidth;
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_CUR, (HI_VOID *)&stFrameCfg, HI_NULL);


    /* rfr config */
    stFrameCfg.bEn = HI_FALSE;
    if (HI_DRV_PIXEL_BITWIDTH_10BIT != pstHalInfo->stInInfo.enBitWidth)
    {
        pstRfr = &pstHalInfo->stInWbcInfo.stAddr;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstRfr->u32PhyAddr_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstRfr->u32PhyAddr_C;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstRfr->u32Stride_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstRfr->u32Stride_C;
        // TODO: ref. rfr 都 固定10bit回写, 计算buffer大小时也要按照10bit算
        stFrameCfg.enBitWidth = pstHalInfo->stInWbcInfo.enBitWidth;
        stFrameCfg.enPixelFmt = pstHalInfo->stInWbcInfo.enFormat;
        stFrameCfg.u32Width   = pstHalInfo->stInWbcInfo.u32Width;
        stFrameCfg.u32Height  = pstHalInfo->stInWbcInfo.u32Height;
    }
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_WRITE_RFR, (HI_VOID *)&stFrameCfg, HI_NULL);
#endif

    /* vhd0 config */
    VPSS_HAL_SetPortCfg(enIP, stRegAddr, pstHalInfo);

    stFunc4PixelCfg.bEnable = HI_TRUE;
    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_SPEED_UP_4PIXEL, (HI_VOID *)&stFunc4PixelCfg, HI_NULL);


    //逐隔行都要配置
    sttInfoCfg.u32WPhyAddr = pstHalInfo->stSttAddr.u32stt_w_phy_addr;
    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_STT, (HI_VOID *)&sttInfoCfg, (HI_VOID *)HI_NULL);

    /* smmu */
#ifdef HI_VPSS_SMMU_SUPPORT
    stSMMUCfg.bGlobalBypass = HI_FALSE;
    stSMMUCfg.bIntEnable = HI_TRUE;
    stSMMUCfg.u32Ptw_pf = 0x3;

    HI_DRV_SMMU_GetPageTableAddr(&u32PageAddr, &u32ErrReadAddr, &u32ErrWriteAddr);
    stSMMUCfg.u32CB_TTBR = stSMMUCfg.u32SCB_TTBR = u32PageAddr;
    stSMMUCfg.u32Err_s_rd_addr = stSMMUCfg.u32Err_ns_rd_addr = u32ErrReadAddr;
    stSMMUCfg.u32Err_s_wr_addr = stSMMUCfg.u32Err_ns_wr_addr = u32ErrWriteAddr;
#else
    stSMMUCfg.bGlobalBypass = HI_TRUE;
    stSMMUCfg.bIntEnable = HI_FALSE;
#endif

    stRegAddr_MMU.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr_MMU.pu8BaseVirAddr = stHalCtx[enIP][0].pu8BaseRegVir;
    VPSS_CBB_FUNC_SetConfig(stRegAddr_MMU, CBB_FUNC_SMMU, (HI_VOID *)&stSMMUCfg, HI_NULL);


    /* tnr mad */
    stMadInfo_Tnr.u32RPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Tnrmad_raddr;
    stMadInfo_Tnr.u32WPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Tnrmad_waddr;
    stMadInfo_Tnr.u32Stride   = pstHalInfo->stNrInfo.stNrMadCfg.u32madstride;
    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_TNR_MAD, (HI_VOID *)&stMadInfo_Tnr, HI_NULL);

    if (stSnrInfo.bEnable)
    {
        /* snr mad */
        stMadInfo_Snr.u32RPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Snrmad_raddr;
        stMadInfo_Snr.u32Stride   = pstHalInfo->stNrInfo.stNrMadCfg.u32madstride;
        VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_SNR_MAD, (HI_VOID *)&stMadInfo_Snr, HI_NULL);
    }

    return HI_SUCCESS;
}




HI_S32 VPSS_HAL_Set_3DFrameL_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy)
{
    HI_S32 s32RetCode = HI_SUCCESS;
    s32RetCode = VPSS_HAL_Set_2DFrame_Node(enIP, pstHalInfo, pu32AppVir, u32AppPhy);
    return s32RetCode;
}

HI_S32 VPSS_HAL_Set_3DFrameR_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy)
{
    HI_S32 s32RetCode = HI_SUCCESS;
    if (pstHalInfo->stInInfo.u32Width > VPSS_FHD_WIDTH)
    {
        pstHalInfo->enNodeType = VPSS_HAL_NODE_2D_UHD;
        s32RetCode = VPSS_HAL_Set_2D_UHDFrame_Node(enIP, pstHalInfo, pu32AppVir, u32AppPhy);
    }
    else
    {
        s32RetCode = VPSS_HAL_Set_2DFrame_Node(enIP, pstHalInfo, pu32AppVir, u32AppPhy);
    }

    return s32RetCode;
}

#if 0
HI_U32 g_DBGFramCnt = 0;
HI_DRV_VIDEO_FRAME_S g_DBGstFrame;
#endif

HI_S32 VPSS_HAL_SetRotateNode(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy, HI_BOOL bRotateY, HI_U32 u32PortId)
{
    HI_DRV_VID_FRAME_ADDR_S *pstNext2;
    HI_DRV_VIDEO_FRAME_S    *pRotaFrame;

    HI_BOOL bRfrEnableFlag;
    HI_U32 u32PageAddr;
    HI_U32 u32ErrReadAddr;
    HI_U32 u32ErrWriteAddr;

    CBB_REG_ADDR_S      stRegAddr;
    CBB_REG_ADDR_S      stRegAddr_MMU;
    CBB_FRAME_S         stFrameCfg;
    CBB_FUNC_TUNNELIN_S stTunnelIn;
    CBB_FUNC_SMMU_S     stSMMUCfg;
    CBB_INFO_S          stMadInfo_Tnr;
    CBB_INFO_S          stMadInfo_Snr;
    CBB_ALG_INFO_S      stDBInfo;
    CBB_ALG_INFO_S      stDBDETInfo;
    CBB_ALG_INFO_S      stNrInfo;
    CBB_ALG_INFO_S      stSnrInfo;
    CBB_ALG_INFO_S      stTnrInfo;
    CBB_ALG_INFO_S      stMcTnrInfo;
    CBB_ALG_INFO_S      stAlgInfo;
    CBB_INFO_S          sttInfoCfg;
    CBB_ALG_INFO_S      stMcDeiAlgCfg;
    CBB_ALG_INFO_S      stDeiAlgCfg;


    VPSS_MEM_CLEAR(stRegAddr);
    VPSS_MEM_CLEAR(stRegAddr_MMU);
    VPSS_MEM_CLEAR(stFrameCfg);
    VPSS_MEM_CLEAR(stTunnelIn);
    VPSS_MEM_CLEAR(stSMMUCfg);
    VPSS_MEM_CLEAR(stMadInfo_Tnr);
    VPSS_MEM_CLEAR(stMadInfo_Snr);
    VPSS_MEM_CLEAR(stDBInfo);
    VPSS_MEM_CLEAR(stDBDETInfo);
    VPSS_MEM_CLEAR(stNrInfo);
    VPSS_MEM_CLEAR(stSnrInfo);
    VPSS_MEM_CLEAR(stTnrInfo);
    VPSS_MEM_CLEAR(stMcTnrInfo);
    VPSS_MEM_CLEAR(stAlgInfo);
    VPSS_MEM_CLEAR(sttInfoCfg);
    VPSS_MEM_CLEAR(stMcDeiAlgCfg);
    VPSS_MEM_CLEAR(stDeiAlgCfg);

    stRegAddr.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr.u32NodePhyAddr = u32AppPhy;

    VPSS_REG_ResetAppReg((S_VPSS_REGS_TYPE *)pu32AppVir, pstHalInfo->pstPqCfg);

    /* channel config */
    pstNext2    = &(pstHalInfo->astPortInfo[u32PortId].stFrmNodeRoBuf.stOutFrame.stBufAddr[HI_DRV_BUF_ADDR_LEFT]);
    pRotaFrame = &(pstHalInfo->astPortInfo[u32PortId].stFrmNodeRoBuf.stOutFrame);

    VPSS_DBG_INFO(

        "RotaNode read from Y C StrideY StrideY %08x %08x %d %d\n",
        pstNext2->u32PhyAddr_Y,
        pstNext2->u32PhyAddr_C,
        pstNext2->u32Stride_Y,
        pstNext2->u32Stride_C
    );

#if 0

    if (g_DBGFramCnt++ == 200)
    {
        HI_U8 chFile[32] = "vpss_rota_in.yuv";

        g_DBGstFrame.u32Width = pRotaFrame->u32Width;
        g_DBGstFrame.u32Height = pRotaFrame->u32Height;
        g_DBGstFrame.ePixFormat = HI_DRV_PIX_FMT_NV21;
        g_DBGstFrame.enBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;
        g_DBGstFrame.stBufAddr[0] = *pstNext2;

        g_DBGstFrame.stBufAddr[0].u32Stride_Y = pstNext2->u32Stride_Y;
        g_DBGstFrame.stBufAddr[0].u32Stride_C = pstNext2->u32Stride_C;

        VPSS_FATAL("RotaNode save temp img  W H stridY stridC %d %d %d %d\n",
                   g_DBGstFrame.u32Width, g_DBGstFrame.u32Height,
                   g_DBGstFrame.stBufAddr[0].u32Stride_Y,
                   g_DBGstFrame.stBufAddr[0].u32Stride_C);
        VPSS_OSAL_WRITEYUV(&g_DBGstFrame, chFile);
    }

#endif

    /*tunnel*/
    if (pstHalInfo->stInInfo.u32TunnelAddr)
    {
        stTunnelIn.bEnable = HI_TRUE;
        stTunnelIn.u32ReadInterval = 0;
        stTunnelIn.u32ReadAddr = pstHalInfo->stInInfo.u32TunnelAddr;
    }
    else
    {
        stTunnelIn.bEnable = HI_FALSE;
    }

    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_TUNNEL_IN, (HI_VOID *)&stTunnelIn, HI_NULL);

    //>SD < FHD时, 只开MA-TNR, DEI

    /* db */
    /* db_det */
    stDBDETInfo.bEnable = HI_FALSE;
    stDBInfo.bEnable = HI_FALSE;
    stNrInfo.bEnable = HI_FALSE;

    stDBInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DB_CTRL) - sizeof(HI_U32);
    //VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_DB, (HI_VOID *)&stDBInfo, HI_NULL);
    //VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_DB_DET, (HI_VOID *)&stDBDETInfo, HI_NULL);
    //VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_NR, (HI_VOID *)&stNrInfo, HI_NULL);

    bRfrEnableFlag      = HI_FALSE;
    //snr_en 是db,dm, nr的总开关， SNR包括db,dm,nr
    stSnrInfo.bEnable   = HI_FALSE;
    stTnrInfo.bEnable   = HI_FALSE;
    stMcTnrInfo.bEnable = HI_FALSE;

    /* snr, tnr */
    //In 98mv200 all of SNR,DB,DM use DB'coef addr(VPSS_DB_CTRL).
    stSnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DB_CTRL) - sizeof(HI_U32);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_SNR, (HI_VOID *)&stSnrInfo, HI_NULL);

    //TNR分为 MA-TNR,  MC-TNR, MC需要单独设置开关, MA的开关即全局tnr开关
    stTnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_TNR_CONTRL) - sizeof(HI_U32);

    if VPSS_IS_YUV420_FMT(pstHalInfo->stInInfo.enFormat)
    {
        stTnrInfo.u32Ymotionmode = 1;
    }
    else
    {
        stTnrInfo.u32Ymotionmode = 0;
    }

    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_TNR, (HI_VOID *)&stTnrInfo, HI_NULL);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_TNR_MC, (HI_VOID *)&stMcTnrInfo, HI_NULL);


    /* next2 config */
    stFrameCfg.bEn              = HI_TRUE;
    stFrameCfg.bSecure          = pstHalInfo->stInInfo.bSecure;
    stFrameCfg.enBitWidth       = pstHalInfo->stInInfo.enBitWidth;
    stFrameCfg.enPixelFmt       = HI_DRV_PIX_FMT_NV21; //pstHalInfo->stInInfo.enFormat; // TODO: 做格式转换

    stFrameCfg.u32Width         = pRotaFrame->u32Width;
    stFrameCfg.u32Height        = pRotaFrame->u32Height;
    stFrameCfg.bProgressive     = HI_TRUE; //pstHalInfo->stInInfo.bProgressive;
    stFrameCfg.stOffset.s32X    = 0;
    stFrameCfg.stOffset.s32Y    = 0;


    stFrameCfg.bTopFirst = pstHalInfo->stInInfo.bTopFirst;

    if (HI_DRV_FIELD_TOP == pstHalInfo->stInInfo.enFieldMode)
    {
        stFrameCfg.bTop = HI_TRUE;
    }
    else
    {
        stFrameCfg.bTop = HI_FALSE;
    }

    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y  = pstNext2->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C  = pstNext2->u32PhyAddr_C;

    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y   = pstNext2->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C   = pstNext2->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif

    stFrameCfg.bCompress = HI_FALSE;
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_NX2, (HI_VOID *)&stFrameCfg, HI_NULL);

    /* nx1 config */
    //no need to cfg nx1
    /* cur config */
    //no need to cfg cur
    /* ref config */
    //no need to cfg ref

    /* rfr config */
    //DO　NOT!!! cfg rfr

    /* vhd0 config */
    VPSS_HAL_SetPortCfg_Rota(stRegAddr, pstHalInfo, bRotateY, u32PortId);

    //逐隔行都要配置
    sttInfoCfg.u32WPhyAddr = pstHalInfo->stSttAddr.u32stt_w_phy_addr;
    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_STT, (HI_VOID *)&sttInfoCfg, (HI_VOID *)HI_NULL);


    stDeiAlgCfg.bEnable     = HI_FALSE;
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_DEI, (HI_VOID *)&stDeiAlgCfg, HI_NULL);

    stMcDeiAlgCfg.bEnable   = HI_FALSE;
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_MCDEI, (HI_VOID *)&stMcDeiAlgCfg, HI_NULL);

    /* igbm */
    stAlgInfo.bEnable = HI_FALSE;
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_IGBM, (HI_VOID *)&stAlgInfo, HI_NULL);

    /* ifmd */
    stAlgInfo.bEnable = HI_FALSE;
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_IFMD, (HI_VOID *)&stAlgInfo, HI_NULL);

    /* smmu */
#ifdef HI_VPSS_SMMU_SUPPORT
    stSMMUCfg.bGlobalBypass = HI_FALSE;
    stSMMUCfg.bIntEnable = HI_TRUE;
    stSMMUCfg.u32Ptw_pf = 0x3;

    HI_DRV_SMMU_GetPageTableAddr(&u32PageAddr, &u32ErrReadAddr, &u32ErrWriteAddr);
    stSMMUCfg.u32CB_TTBR = stSMMUCfg.u32SCB_TTBR = u32PageAddr;
    stSMMUCfg.u32Err_s_rd_addr = stSMMUCfg.u32Err_ns_rd_addr = u32ErrReadAddr;
    stSMMUCfg.u32Err_s_wr_addr = stSMMUCfg.u32Err_ns_wr_addr = u32ErrWriteAddr;
#else
    stSMMUCfg.bGlobalBypass = HI_TRUE;
    stSMMUCfg.bIntEnable = HI_FALSE;
#endif

    stRegAddr_MMU.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr_MMU.pu8BaseVirAddr = stHalCtx[enIP][0].pu8BaseRegVir;
    VPSS_CBB_FUNC_SetConfig(stRegAddr_MMU, CBB_FUNC_SMMU, (HI_VOID *)&stSMMUCfg, HI_NULL);

    /* snr mad */
    stMadInfo_Snr.u32RPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Snrmad_raddr;
    stMadInfo_Snr.u32Stride   = pstHalInfo->stNrInfo.stNrMadCfg.u32madstride;
    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_SNR_MAD, (HI_VOID *)&stMadInfo_Snr, HI_NULL);

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_Set_RotaY_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy)
{
    VPSS_HAL_SetRotateNode(enIP, pstHalInfo, pu32AppVir, u32AppPhy, HI_TRUE, 0);
    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_Set_RotaC_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy)
{
    VPSS_HAL_SetRotateNode(enIP, pstHalInfo, pu32AppVir, u32AppPhy, HI_FALSE, 0);
    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_Set_RotaY_VIRTUAL_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy)
{
    VPSS_HAL_SetRotateNode(enIP, pstHalInfo, pu32AppVir, u32AppPhy, HI_TRUE, 1);
    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_Set_RotaC_VIRTUAL_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy)
{
    VPSS_HAL_SetRotateNode(enIP, pstHalInfo, pu32AppVir, u32AppPhy, HI_FALSE, 1);
    return HI_SUCCESS;
}


HI_S32 VPSS_HAL_Set_HDR_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy)
{
    HI_DRV_VID_FRAME_ADDR_S *pstNext2;
    HI_DRV_VID_FRAME_ADDR_S *pstNext2_LB;

    HI_U32 u32PageAddr;
    HI_U32 u32ErrReadAddr;
    HI_U32 u32ErrWriteAddr;

    CBB_REG_ADDR_S      stRegAddr;
    CBB_REG_ADDR_S      stRegAddr_MMU;
    CBB_FRAME_S         stFrameCfg;
    CBB_FUNC_TUNNELIN_S stTunnelIn;
    CBB_FUNC_SMMU_S     stSMMUCfg;
    CBB_ALG_INFO_S      stDBInfo;
    CBB_ALG_INFO_S      stDBDETInfo;
    CBB_ALG_INFO_S      stNrInfo;
    CBB_ALG_INFO_S      stSnrInfo;
    CBB_ALG_INFO_S      stTnrInfo;
    CBB_ALG_INFO_S      stMcTnrInfo;
    CBB_ALG_INFO_S      stIfmdInfo;
    CBB_ALG_INFO_S      stHdrInfo;
    CBB_FUNC_4PIXEL_S   stFunc4PixelCfg;
    CBB_INFO_S          sttInfoCfg;

    VPSS_MEM_CLEAR(stRegAddr);
    VPSS_MEM_CLEAR(stRegAddr_MMU);
    VPSS_MEM_CLEAR(stFrameCfg);
    VPSS_MEM_CLEAR(stTunnelIn);
    VPSS_MEM_CLEAR(stSMMUCfg);
    VPSS_MEM_CLEAR(stDBInfo);
    VPSS_MEM_CLEAR(stDBDETInfo);
    VPSS_MEM_CLEAR(stNrInfo);
    VPSS_MEM_CLEAR(stSnrInfo);
    VPSS_MEM_CLEAR(stTnrInfo);
    VPSS_MEM_CLEAR(stHdrInfo);
    VPSS_MEM_CLEAR(stMcTnrInfo);
    VPSS_MEM_CLEAR(stIfmdInfo);
    VPSS_MEM_CLEAR(sttInfoCfg);
    VPSS_MEM_CLEAR(stFunc4PixelCfg);

    stRegAddr.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr.u32NodePhyAddr = u32AppPhy;

    VPSS_REG_ResetAppReg((S_VPSS_REGS_TYPE *)pu32AppVir, pstHalInfo->pstPqCfg);

    /*tunnel*/
    if (pstHalInfo->stInInfo.u32TunnelAddr)
    {
        stTunnelIn.bEnable = HI_TRUE;
        stTunnelIn.u32ReadInterval = 0;
        stTunnelIn.u32ReadAddr = pstHalInfo->stInInfo.u32TunnelAddr;
    }
    else
    {
        stTunnelIn.bEnable = HI_FALSE;
    }

    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_TUNNEL_IN, (HI_VOID *)&stTunnelIn, HI_NULL);

    stSnrInfo.bEnable = HI_FALSE;
    stSnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DB_CTRL) - sizeof(HI_U32);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_SNR, (HI_VOID *)&stSnrInfo, HI_NULL);

    stHdrInfo.bEnable = HI_FALSE; //lchdr
    stHdrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_LCHDR_CTRL) - sizeof(HI_U32);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_HDR, (HI_VOID *)&stHdrInfo, HI_NULL);

    /* next2 config */
    pstNext2 = &pstHalInfo->stInInfo.stAddr;
    pstNext2_LB = &pstHalInfo->stInInfo.stAddr_LB;
    stFrameCfg.bEn              = HI_TRUE;
    stFrameCfg.bSecure          = pstHalInfo->stInInfo.bSecure;
    stFrameCfg.enBitWidth       = pstHalInfo->stInInfo.enBitWidth;
    stFrameCfg.enPixelFmt       = pstHalInfo->stInInfo.enFormat;
    stFrameCfg.u32Width         = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height        = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.bProgressive     = pstHalInfo->stInInfo.bProgressive;
    stFrameCfg.stOffset.s32X    = 0;
    stFrameCfg.stOffset.s32Y    = 0;


    stFrameCfg.bTopFirst = pstHalInfo->stInInfo.bTopFirst;

    if (HI_DRV_FIELD_TOP == pstHalInfo->stInInfo.enFieldMode)
    {
        stFrameCfg.bTop = HI_TRUE;
    }
    else
    {
        stFrameCfg.bTop = HI_FALSE;
    }

    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y  = pstNext2->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C  = pstNext2->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y   = pstNext2->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C   = pstNext2->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif

    if ( HI_DRV_PIXEL_BITWIDTH_10BIT == pstHalInfo->stInInfo.enBitWidth )
    {
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_Y   = pstNext2_LB->u32PhyAddr_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_C   = pstNext2_LB->u32PhyAddr_C;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_Y    = pstNext2_LB->u32Stride_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_C    = pstNext2_LB->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_TRUE;
#else
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_FALSE;
#endif
    }

    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_CMP)
    {
        stFrameCfg.bCompress = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_YHead  = pstNext2->u32PhyAddr_YHead;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_CHead  = pstNext2->u32PhyAddr_CHead;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Head_Size      = pstNext2->u32Head_Size;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Head_Stride    = pstNext2->u32Head_Stride;
#ifdef HI_VPSS_SMMU_SUPPORT
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y   = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C   = HI_TRUE;

        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y    = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C    = HI_TRUE;
#else
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;

        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_FALSE;
#endif

    }
    else
    {
        stFrameCfg.bCompress = HI_FALSE;
    }

    VPSS_DBG_INFO("HDREL nx2 read from %08x %08x %d %d\n",
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y,
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C,
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y,
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C);

    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_NX2, (HI_VOID *)&stFrameCfg, HI_NULL);

    /* nx1 config */
    /* no need to config nx1 in HDRFrame */
    /* cur config */
    /* vhd0 config */
    VPSS_HAL_SetPortCfg(enIP, stRegAddr, pstHalInfo);

    /* smmu */
#ifdef HI_VPSS_SMMU_SUPPORT
    stSMMUCfg.bGlobalBypass = HI_FALSE;
    stSMMUCfg.bIntEnable = HI_TRUE;
    stSMMUCfg.u32Ptw_pf = 0x3;
    HI_DRV_SMMU_GetPageTableAddr(&u32PageAddr, &u32ErrReadAddr, &u32ErrWriteAddr);
    stSMMUCfg.u32CB_TTBR = stSMMUCfg.u32SCB_TTBR = u32PageAddr;
    stSMMUCfg.u32Err_s_rd_addr = stSMMUCfg.u32Err_ns_rd_addr = u32ErrReadAddr;
    stSMMUCfg.u32Err_s_wr_addr = stSMMUCfg.u32Err_ns_wr_addr = u32ErrWriteAddr;
#else
    stSMMUCfg.bGlobalBypass = HI_TRUE;
    stSMMUCfg.bIntEnable = HI_FALSE;
#endif
    stRegAddr_MMU.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr_MMU.pu8BaseVirAddr = stHalCtx[enIP][0].pu8BaseRegVir;
    VPSS_CBB_FUNC_SetConfig(stRegAddr_MMU, CBB_FUNC_SMMU, (HI_VOID *)&stSMMUCfg, HI_NULL);

    return HI_SUCCESS;
}


HI_S32 VPSS_HAL_Set_LCHDR_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy)
{
    HI_DRV_VID_FRAME_ADDR_S *pstNext2;
    HI_DRV_VID_FRAME_ADDR_S *pstNext2_LB;

    HI_U32 u32PageAddr;
    HI_U32 u32ErrReadAddr;
    HI_U32 u32ErrWriteAddr;

    CBB_REG_ADDR_S      stRegAddr;
    CBB_REG_ADDR_S      stRegAddr_MMU;
    CBB_FRAME_S         stFrameCfg;
    CBB_FUNC_TUNNELIN_S stTunnelIn;
    CBB_FUNC_SMMU_S     stSMMUCfg;
    CBB_ALG_INFO_S      stDBInfo;
    CBB_ALG_INFO_S      stDBDETInfo;
    CBB_ALG_INFO_S      stNrInfo;
    CBB_ALG_INFO_S      stSnrInfo;
    CBB_ALG_INFO_S      stTnrInfo;
    CBB_ALG_INFO_S      stMcTnrInfo;
    CBB_ALG_INFO_S      stIfmdInfo;
    CBB_ALG_INFO_S      stHdrInfo;
    CBB_FUNC_4PIXEL_S   stFunc4PixelCfg;
    CBB_INFO_S          sttInfoCfg;

    VPSS_MEM_CLEAR(stRegAddr);
    VPSS_MEM_CLEAR(stRegAddr_MMU);
    VPSS_MEM_CLEAR(stFrameCfg);
    VPSS_MEM_CLEAR(stTunnelIn);
    VPSS_MEM_CLEAR(stSMMUCfg);
    VPSS_MEM_CLEAR(stDBInfo);
    VPSS_MEM_CLEAR(stDBDETInfo);
    VPSS_MEM_CLEAR(stNrInfo);
    VPSS_MEM_CLEAR(stSnrInfo);
    VPSS_MEM_CLEAR(stTnrInfo);
    VPSS_MEM_CLEAR(stHdrInfo);
    VPSS_MEM_CLEAR(stMcTnrInfo);
    VPSS_MEM_CLEAR(stIfmdInfo);
    VPSS_MEM_CLEAR(sttInfoCfg);
    VPSS_MEM_CLEAR(stFunc4PixelCfg);

    stRegAddr.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr.u32NodePhyAddr = u32AppPhy;

    VPSS_REG_ResetAppReg((S_VPSS_REGS_TYPE *)pu32AppVir, pstHalInfo->pstPqCfg);

    /*tunnel*/
    if (pstHalInfo->stInInfo.u32TunnelAddr)
    {
        stTunnelIn.bEnable = HI_TRUE;
        stTunnelIn.u32ReadInterval = 0;
        stTunnelIn.u32ReadAddr = pstHalInfo->stInInfo.u32TunnelAddr;
    }
    else
    {
        stTunnelIn.bEnable = HI_FALSE;
    }

    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_TUNNEL_IN, (HI_VOID *)&stTunnelIn, HI_NULL);

    stSnrInfo.bEnable = HI_FALSE;
    stSnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DB_CTRL) - sizeof(HI_U32);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_SNR, (HI_VOID *)&stSnrInfo, HI_NULL);

    stHdrInfo.bEnable = HI_TRUE;
    stHdrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_LCHDR_CTRL) - sizeof(HI_U32);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_HDR, (HI_VOID *)&stHdrInfo, HI_NULL);

    /* next2 config */
    pstNext2 = &pstHalInfo->stInInfo.stAddr;
    pstNext2_LB = &pstHalInfo->stInInfo.stAddr_LB;
    stFrameCfg.bEn              = HI_TRUE;
    stFrameCfg.bSecure          = pstHalInfo->stInInfo.bSecure;
    stFrameCfg.enBitWidth       = pstHalInfo->stInInfo.enBitWidth;
    stFrameCfg.enPixelFmt       = pstHalInfo->stInInfo.enFormat;
    stFrameCfg.u32Width         = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height        = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.bProgressive     = pstHalInfo->stInInfo.bProgressive;
    stFrameCfg.stOffset.s32X    = 0;
    stFrameCfg.stOffset.s32Y    = 0;


    stFrameCfg.bTopFirst = pstHalInfo->stInInfo.bTopFirst;

    if (HI_DRV_FIELD_TOP == pstHalInfo->stInInfo.enFieldMode)
    {
        stFrameCfg.bTop = HI_TRUE;
    }
    else
    {
        stFrameCfg.bTop = HI_FALSE;
    }

    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y  = pstNext2->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C  = pstNext2->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y   = pstNext2->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C   = pstNext2->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif

    if ( HI_DRV_PIXEL_BITWIDTH_10BIT == pstHalInfo->stInInfo.enBitWidth )
    {
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_Y   = pstNext2_LB->u32PhyAddr_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_C   = pstNext2_LB->u32PhyAddr_C;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_Y    = pstNext2_LB->u32Stride_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_C    = pstNext2_LB->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_TRUE;
#else
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_FALSE;
#endif
    }

    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_CMP)
    {
        stFrameCfg.bCompress = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_YHead  = pstNext2->u32PhyAddr_YHead;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_CHead  = pstNext2->u32PhyAddr_CHead;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Head_Size      = pstNext2->u32Head_Size;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Head_Stride    = pstNext2->u32Head_Stride;
#ifdef HI_VPSS_SMMU_SUPPORT
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y   = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C   = HI_TRUE;

        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y    = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C    = HI_TRUE;
#else
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;

        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_FALSE;
#endif

    }
    else
    {
        stFrameCfg.bCompress = HI_FALSE;
    }

    VPSS_DBG_INFO("HDREL nx2 read from %08x %08x %d %d\n",
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y,
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C,
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y,
                  stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C);

    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_NX2, (HI_VOID *)&stFrameCfg, HI_NULL);

    /* nx1 config */
    /* no need to config nx1 in HDRFrame */
    /* cur config */
    /* vhd0 config */
    VPSS_HAL_SetPortCfg(enIP, stRegAddr, pstHalInfo);

    /* smmu */
#ifdef HI_VPSS_SMMU_SUPPORT
    stSMMUCfg.bGlobalBypass = HI_FALSE;
    stSMMUCfg.bIntEnable = HI_TRUE;
    stSMMUCfg.u32Ptw_pf = 0x3;
    HI_DRV_SMMU_GetPageTableAddr(&u32PageAddr, &u32ErrReadAddr, &u32ErrWriteAddr);
    stSMMUCfg.u32CB_TTBR = stSMMUCfg.u32SCB_TTBR = u32PageAddr;
    stSMMUCfg.u32Err_s_rd_addr = stSMMUCfg.u32Err_ns_rd_addr = u32ErrReadAddr;
    stSMMUCfg.u32Err_s_wr_addr = stSMMUCfg.u32Err_ns_wr_addr = u32ErrWriteAddr;
#else
    stSMMUCfg.bGlobalBypass = HI_TRUE;
    stSMMUCfg.bIntEnable = HI_FALSE;
#endif
    stRegAddr_MMU.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr_MMU.pu8BaseVirAddr = stHalCtx[enIP][0].pu8BaseRegVir;
    VPSS_CBB_FUNC_SetConfig(stRegAddr_MMU, CBB_FUNC_SMMU, (HI_VOID *)&stSMMUCfg, HI_NULL);

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_SetNode_H265_Step1_Interlace(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo,
        HI_U32 *pu32AppVir, HI_U32 u32AppPhy)
{
    HI_DRV_VID_FRAME_ADDR_S *pstNext2;
    HI_DRV_VID_FRAME_ADDR_S *pstNext2_LB;

    HI_DRV_VID_FRAME_ADDR_S *pstRef;
    HI_DRV_VID_FRAME_ADDR_S *pstNxt1;

    HI_DRV_VID_FRAME_ADDR_S *pstCur;
    HI_DRV_VID_FRAME_ADDR_S *pstRfr;

    HI_U32 u32PageAddr;
    HI_U32 u32ErrReadAddr;
    HI_U32 u32ErrWriteAddr;

    CBB_REG_ADDR_S      stRegAddr;
    CBB_REG_ADDR_S      stRegAddr_MMU;
    CBB_FRAME_S         stFrameCfg;

    CBB_FUNC_SMMU_S     stSMMUCfg;
    CBB_ALG_INFO_S      stSnrInfo;
    CBB_ALG_INFO_S      stMcTnrInfo;
    CBB_ALG_INFO_S      stAlgInfo;
    CBB_INFO_S          sttInfoCfg;
    CBB_ALG_INFO_S      stMcDeiAlgCfg;
    CBB_FRAME_S             stFrmCfg;
    VPSS_HAL_PORT_INFO_S   *pstHalPort;
    CBB_FUNC_CROP_S         stFuncCropCfg;
    CBB_FUNC_LBOX_S         stLBox;
    CBB_FUNC_4PIXEL_S       stFunc4PixelCfg;
    CBB_FUNC_TUNNELOUT_S    stFuncTunnelOutCfg;
    CBB_FUNC_TRANS_S        stTransInfo;
    VPSS_HAL_FRAME_S        *pstInInfo;

    VPSS_MEM_CLEAR(stFrmCfg);
    VPSS_MEM_CLEAR(stFuncCropCfg);
    VPSS_MEM_CLEAR(stLBox);
    VPSS_MEM_CLEAR(stFunc4PixelCfg);
    VPSS_MEM_CLEAR(stFuncTunnelOutCfg);
    VPSS_MEM_CLEAR(stTransInfo);
    VPSS_MEM_CLEAR(stRegAddr);
    VPSS_MEM_CLEAR(stRegAddr_MMU);
    VPSS_MEM_CLEAR(stFrameCfg);

    VPSS_MEM_CLEAR(stSMMUCfg);
    VPSS_MEM_CLEAR(stSnrInfo);
    VPSS_MEM_CLEAR(stMcTnrInfo);
    VPSS_MEM_CLEAR(stAlgInfo);
    VPSS_MEM_CLEAR(sttInfoCfg);
    VPSS_MEM_CLEAR(stMcDeiAlgCfg);


    stRegAddr.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr.u32NodePhyAddr = u32AppPhy;

    VPSS_REG_ResetAppReg((S_VPSS_REGS_TYPE *)pu32AppVir, pstHalInfo->pstPqCfg);

    /* channel config */
    pstRef      = &pstHalInfo->stInRefInfo[0].stAddr;
    pstCur      = &pstHalInfo->stInRefInfo[1].stAddr;
    pstNxt1     = &pstHalInfo->stInRefInfo[2].stAddr;
    pstNext2    = &pstHalInfo->stInInfo.stAddr;
    pstNext2_LB = &pstHalInfo->stInInfo.stAddr_LB;
    pstRfr      = &pstHalInfo->stInWbcInfo.stAddr;
    pstInInfo   = &(pstHalInfo->stInInfo);
#if 0
    VPSS_DBG_INFO("Ref  phy:%08x, vir:%x\n", pstRef->u32PhyAddr_Y, (HI_U32)pstRef->vir_addr_y);
    VPSS_DBG_INFO("Cur  phy:%08x, vir:%x\n", pstCur->u32PhyAddr_Y, (HI_U32)pstCur->vir_addr_y);
    VPSS_DBG_INFO("Nx1  phy:%08x, vir:%x\n", pstNxt1->u32PhyAddr_Y, (HI_U32)pstNxt1->vir_addr_y);
    VPSS_DBG_INFO("Nx2  phy:%08x, vir:%x\n", pstNext2->u32PhyAddr_Y, (HI_U32)pstNext2->vir_addr_y);
    VPSS_DBG_INFO("Rfr  phy:%08x, vir:%x\n", pstRfr->u32PhyAddr_Y, (HI_U32)pstRfr->vir_addr_y);
#endif
#if 0
    /*tunnel*/
    if (pstHalInfo->stInInfo.u32TunnelAddr)
    {
        stTunnelIn.bEnable = HI_TRUE;
        stTunnelIn.u32ReadInterval = 0;
        stTunnelIn.u32ReadAddr = pstHalInfo->stInInfo.u32TunnelAddr;
    }
    else
    {
        stTunnelIn.bEnable = HI_FALSE;
    }

    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_TUNNEL_IN, (HI_VOID *)&stTunnelIn, HI_NULL);

    /* db */
    /* db_det */
    stDBDETInfo.bEnable = HI_FALSE;
    stDBInfo.bEnable = HI_FALSE;
    stNrInfo.bEnable = HI_FALSE;

    stDBInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DB_CTRL) - sizeof(HI_U32);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_DB, (HI_VOID *)&stDBInfo, HI_NULL);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_DB_DET, (HI_VOID *)&stDBDETInfo, HI_NULL);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_NR, (HI_VOID *)&stNrInfo, HI_NULL);
#endif

    stSnrInfo.bEnable   = HI_FALSE;
    stSnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DB_CTRL) - sizeof(HI_U32);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_SNR, (HI_VOID *)&stSnrInfo, HI_NULL);


    /* snr, tnr */
    //In 98mv200 all of SNR,DB,DM use DB'coef addr(VPSS_DB_CTRL).
    // stSnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DB_CTRL) - sizeof(HI_U32);
    //  VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_SNR, (HI_VOID *)&stSnrInfo, HI_NULL);

    //TNR分为 MA-TNR,  MC-TNR, MC需要单独设置开关, MA的开关即全局tnr开关
    //   stTnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_TNR_CONTRL) - sizeof(HI_U32);

    if VPSS_IS_YUV420_FMT(pstHalInfo->stInInfo.enFormat)
    {
        //      stTnrInfo.u32Ymotionmode = 1;
    }
    else
    {
        //     stTnrInfo.u32Ymotionmode = 0;
    }


    /* next2 config */
    stFrameCfg.bEn              = HI_TRUE;
    stFrameCfg.bSecure          = pstHalInfo->stInInfo.bSecure;
    stFrameCfg.enBitWidth       = pstHalInfo->stInInfo.enBitWidth;
    stFrameCfg.enPixelFmt       = pstHalInfo->stInInfo.enFormat;    // TODO: 做格式转换
    stFrameCfg.u32Width         = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height        = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.bProgressive     = HI_TRUE; //pstHalInfo->stInInfo.bProgressive;
    stFrameCfg.stOffset.s32X    = 0;
    stFrameCfg.stOffset.s32Y    = 0;

    stFrameCfg.bTopFirst = pstHalInfo->stInInfo.bTopFirst;

    if (HI_DRV_FIELD_TOP == pstHalInfo->stInInfo.enFieldMode)
    {
        stFrameCfg.bTop = HI_TRUE;
    }
    else
    {
        stFrameCfg.bTop = HI_FALSE;
    }

    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y  = pstNext2->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C  = pstNext2->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y   = pstNext2->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C   = pstNext2->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif

    if ( HI_DRV_PIXEL_BITWIDTH_10BIT == pstHalInfo->stInInfo.enBitWidth )
    {
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_Y   = pstNext2_LB->u32PhyAddr_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_C   = pstNext2_LB->u32PhyAddr_C;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_Y    = pstNext2_LB->u32Stride_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_C    = pstNext2_LB->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_TRUE;
#else
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_FALSE;
#endif

    }

    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_CMP)
    {
        stFrameCfg.bCompress = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_YHead  = pstNext2->u32PhyAddr_YHead;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_CHead  = pstNext2->u32PhyAddr_CHead;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Head_Size      = pstNext2->u32Head_Size;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Head_Stride    = pstNext2->u32Head_Stride;
#ifdef HI_VPSS_SMMU_SUPPORT
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y   = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C   = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y    = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C    = HI_TRUE;
#else
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_FALSE;
#endif
    }
    else
    {
        stFrameCfg.bCompress = HI_FALSE;
    }

    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_NX2, (HI_VOID *)&stFrameCfg, HI_NULL);



    VPSS_DBG_INFO("STEP1: Read nx2 YAddr YS CS %x %d %d\n",
                  pstNext2->u32PhyAddr_Y,
                  pstNext2->u32Stride_Y, pstNext2->u32Stride_C);

    pstHalPort = &pstHalInfo->astPortInfo[0];
    if (pstHalPort->bEnable && pstHalPort->bConfig == HI_FALSE)
    {
        VPSS_REG_PORT_E enPort = VPSS_REG_BUTT;
        VPSS_HAL_FRAME_S *pstOutFrm = HI_NULL;
        HI_DRV_VID_FRAME_ADDR_S *pstOutAddr = HI_NULL;

        enPort = VPSS_REG_HD;

        pstOutFrm = &pstHalInfo->stInInfo;
        pstOutAddr = &(pstHalInfo->pstH265RefList->stRefListAddr[pstHalInfo->pstH265RefList->u32RefListHead]);
        pstHalInfo->pstH265RefList->abRefNodeValid[pstHalInfo->pstH265RefList->u32RefListHead] = HI_TRUE;

        /*
                {
                    HI_U8 chFile[64] = "vpss_detile.yuv";
                    HI_DRV_VIDEO_FRAME_S stFrame;

                    memset(&stFrame, 0x0, sizeof(stFrame));

                    stFrame.u32Width = pstHalInfo->stInInfo.u32Width;
                    stFrame.u32Height = pstHalInfo->stInInfo.u32Height;
                    stFrame.ePixFormat = HI_DRV_PIX_FMT_NV21;
                    stFrame.enBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;
                    stFrame.bSecure = HI_FALSE;
                    stFrame.stBufAddr[0] = *pstOutAddr;
                    stFrame.stBufAddr[0].u32Stride_Y = pstOutAddr->u32Stride_Y * 2;
                    stFrame.stBufAddr[0].u32Stride_C = pstOutAddr->u32Stride_C * 2;

                    VPSS_DBG_INFO("STEP1: tmp img save: Yaddr w h YS CS %x %d %d %d %d",
                                  stFrame.stBufAddr[0].u32PhyAddr_Y,
                                  stFrame.u32Width, stFrame.u32Height, stFrame.stBufAddr[0].u32Stride_Y,
                                  stFrame.stBufAddr[0].u32Stride_C);
                    VPSS_OSAL_WRITEYUV(&stFrame, chFile);
                }
        */
        stFuncTunnelOutCfg.bEnable = HI_FALSE;
        VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_TUNNEL_OUT, (HI_VOID *)&stFuncTunnelOutCfg, HI_NULL);

        stFuncCropCfg.bEnable = HI_FALSE;
        VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_CROP, (HI_VOID *)&stFuncCropCfg, HI_NULL);
        stLBox.bEnable = HI_FALSE;
        VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_LBOX, (HI_VOID *)&stLBox, HI_NULL);

#if 0
        /*ZME*/
        stFuncZmeCfg.u32ParAddr = stRegAddr.u32NodePhyAddr + 0x2000;
        stFuncZmeCfg.bEnable    = HI_FALSE;
        stFuncZmeCfg.eMode      = CBB_ZME_MODE_ALL;

        pstZmeDrvPara  = &(stFuncZmeCfg.stZmeDrvPara);
        memset(pstZmeDrvPara, 0, sizeof(HI_PQ_ZME_PARA_IN_S));
        pstZmeDrvPara->bZmeFrmFmtIn = 1;
        pstZmeDrvPara->bZmeFrmFmtOut = 1;
        pstZmeDrvPara->bZmeBFIn = 0;
        pstZmeDrvPara->bZmeBFOut = 0;

        pstZmeDrvPara->u8ZmeYCFmtIn = VPSS_HAL_TransPixelZMEFormat(pstInInfo->enFormat);
        pstZmeDrvPara->u8ZmeYCFmtOut = VPSS_HAL_TransPixelZMEFormat(pstHalPort->stOutInfo.enFormat);

        pstZmeDrvPara->u32ZmeFrmHIn = pstInInfo->u32Height;
        pstZmeDrvPara->u32ZmeFrmWIn = pstInInfo->u32Width;

        pstZmeDrvPara->u32ZmeFrmHOut = pstZmeDrvPara->u32ZmeFrmHIn;
        pstZmeDrvPara->u32ZmeFrmWOut = pstZmeDrvPara->u32ZmeFrmWIn;
        VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_ZME, (HI_VOID *)&stFuncZmeCfg, HI_NULL);

        stLBox.bEnable = HI_FALSE;
        VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VHD0_LBOX, (HI_VOID *)&stLBox, HI_NULL);
#endif
        stFrmCfg.bEn        = HI_TRUE;
        stFrmCfg.enBitWidth = pstOutFrm->enBitWidth;
        stFrmCfg.enPixelFmt = HI_DRV_PIX_FMT_NV21;
        stFrmCfg.u32Width   = pstOutFrm->u32Width;
        stFrmCfg.u32Height  = pstOutFrm->u32Height;
        stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstOutAddr->u32PhyAddr_Y;
        stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstOutAddr->u32PhyAddr_C;
        stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstOutAddr->u32Stride_Y;
        stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstOutAddr->u32Stride_C;

#ifdef HI_VPSS_SMMU_SUPPORT
        stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
        stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
        stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
        stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif

        VPSS_DBG_INFO(
            "Vhd0 Y C StrideY StrideC W H %08x %08x %d %d %d %d\n",
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y,
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C,
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y,
            stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C,
            stFrmCfg.u32Width,
            stFrmCfg.u32Height);

        VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_WRITE_VHD0, (HI_VOID *)&stFrmCfg, HI_NULL);
        VPSS_DBG_INFO("STEP1: vhd0 addr W H YS CS %x %d %d %d %d\n",
                      pstOutAddr->u32PhyAddr_Y,
                      pstOutFrm->u32Width, pstOutFrm->u32Height,
                      stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y,
                      stFrmCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C);
    }

    /* smmu */
#ifdef HI_VPSS_SMMU_SUPPORT
    stSMMUCfg.bGlobalBypass = HI_FALSE;
    stSMMUCfg.bIntEnable = HI_TRUE;
    stSMMUCfg.u32Ptw_pf = 0x3;

    HI_DRV_SMMU_GetPageTableAddr(&u32PageAddr, &u32ErrReadAddr, &u32ErrWriteAddr);
    stSMMUCfg.u32CB_TTBR = stSMMUCfg.u32SCB_TTBR = u32PageAddr;
    stSMMUCfg.u32Err_s_rd_addr = stSMMUCfg.u32Err_ns_rd_addr = u32ErrReadAddr;
    stSMMUCfg.u32Err_s_wr_addr = stSMMUCfg.u32Err_ns_wr_addr = u32ErrWriteAddr;
#else
    stSMMUCfg.bGlobalBypass = HI_TRUE;
    stSMMUCfg.bIntEnable = HI_FALSE;
#endif

    stRegAddr_MMU.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr_MMU.pu8BaseVirAddr = stHalCtx[enIP][0].pu8BaseRegVir;
    VPSS_CBB_FUNC_SetConfig(stRegAddr_MMU, CBB_FUNC_SMMU, (HI_VOID *)&stSMMUCfg, HI_NULL);

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_SetNode_H265_Step2_Dei(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo,
                                       HI_U32 *pu32AppVir, HI_U32 u32AppPhy)
{
    HI_U32 u32Head;
    HI_DRV_VID_FRAME_ADDR_S *pstRef  = HI_NULL;
    HI_DRV_VID_FRAME_ADDR_S *pstCur  = HI_NULL;
    HI_DRV_VID_FRAME_ADDR_S *pstNxt1 = HI_NULL;
    HI_DRV_VID_FRAME_ADDR_S *pstNxt2 = HI_NULL;
    HI_DRV_VID_FRAME_ADDR_S *pstRfr  = HI_NULL;

    HI_BOOL bRfrEnableFlag;
    HI_U32 u32PageAddr;
    HI_U32 u32ErrReadAddr;
    HI_U32 u32ErrWriteAddr;

    CBB_REG_ADDR_S      stRegAddr;
    CBB_REG_ADDR_S      stRegAddr_MMU;
    CBB_FRAME_S         stFrameCfg;
    CBB_FUNC_TUNNELIN_S stTunnelIn;
    CBB_FUNC_SMMU_S     stSMMUCfg;
    CBB_INFO_S          stMadInfo_Tnr;
    CBB_INFO_S          stMadInfo_Snr;
    CBB_ALG_INFO_S      stDBInfo;
    CBB_ALG_INFO_S      stDBDETInfo;
    CBB_ALG_INFO_S      stNrInfo;
    CBB_ALG_INFO_S      stSnrInfo;
    CBB_ALG_INFO_S      stTnrInfo;
    CBB_ALG_INFO_S      stMcTnrInfo;
    CBB_ALG_INFO_S      stAlgInfo;
    CBB_INFO_S          sttInfoCfg;
    CBB_ALG_INFO_S      stMcDeiAlgCfg;

    VPSS_MEM_CLEAR(stRegAddr);
    VPSS_MEM_CLEAR(stRegAddr_MMU);
    VPSS_MEM_CLEAR(stFrameCfg);
    VPSS_MEM_CLEAR(stTunnelIn);
    VPSS_MEM_CLEAR(stSMMUCfg);
    VPSS_MEM_CLEAR(stMadInfo_Tnr);
    VPSS_MEM_CLEAR(stMadInfo_Snr);
    VPSS_MEM_CLEAR(stDBInfo);
    VPSS_MEM_CLEAR(stDBDETInfo);
    VPSS_MEM_CLEAR(stNrInfo);
    VPSS_MEM_CLEAR(stSnrInfo);
    VPSS_MEM_CLEAR(stTnrInfo);
    VPSS_MEM_CLEAR(stMcTnrInfo);
    VPSS_MEM_CLEAR(stAlgInfo);
    VPSS_MEM_CLEAR(sttInfoCfg);
    VPSS_MEM_CLEAR(stMcDeiAlgCfg);


    VPSS_HAL_CHECK_IP_VAILD(enIP);

    stRegAddr.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr.u32NodePhyAddr = u32AppPhy;

    VPSS_REG_ResetAppReg((S_VPSS_REGS_TYPE *)pu32AppVir, pstHalInfo->pstPqCfg);


    u32Head = pstHalInfo->pstH265RefList->u32RefListHead;

    //需要考虑前4场时，每个缓冲BUFFER的有效性
    if (!pstHalInfo->pstH265RefList->abRefNodeValid[0])
    {
        VPSS_ERROR("!!pstHalInfo->pstH265RefList->abRefNodeValid[0]!");
    }

    if (!pstHalInfo->pstH265RefList->abRefNodeValid[1])
    {
        pstRef  = &pstHalInfo->pstH265RefList->stRefListAddr[0];
        pstCur  = &pstHalInfo->pstH265RefList->stRefListAddr[0];
        pstNxt1 = &pstHalInfo->pstH265RefList->stRefListAddr[0];
        pstNxt2 = &pstHalInfo->pstH265RefList->stRefListAddr[0];
    }
    else if (!pstHalInfo->pstH265RefList->abRefNodeValid[2])
    {
        pstRef  = &pstHalInfo->pstH265RefList->stRefListAddr[0];
        pstCur  = &pstHalInfo->pstH265RefList->stRefListAddr[0];
        pstNxt1 = &pstHalInfo->pstH265RefList->stRefListAddr[0];
        pstNxt2 = &pstHalInfo->pstH265RefList->stRefListAddr[1];
    }
    else if (!pstHalInfo->pstH265RefList->abRefNodeValid[3])
    {
        pstRef  = &pstHalInfo->pstH265RefList->stRefListAddr[0];
        pstCur  = &pstHalInfo->pstH265RefList->stRefListAddr[0];
        pstNxt1 = &pstHalInfo->pstH265RefList->stRefListAddr[1];
        pstNxt2 = &pstHalInfo->pstH265RefList->stRefListAddr[2];
    }
    else
    {
        pstRef  = &pstHalInfo->pstH265RefList->stRefListAddr[(u32Head + 1) % DEF_VPSS_HAL_REF_LIST_NUM];
        pstCur  = &pstHalInfo->pstH265RefList->stRefListAddr[(u32Head + 2) % DEF_VPSS_HAL_REF_LIST_NUM];
        pstNxt1 = &pstHalInfo->pstH265RefList->stRefListAddr[(u32Head + 3) % DEF_VPSS_HAL_REF_LIST_NUM];
        pstNxt2 = &pstHalInfo->pstH265RefList->stRefListAddr[(u32Head)];
    }

    //pstRef = pstCur = pstNxt1 = pstNxt2;

    VPSS_DBG_INFO("Ref Cur Nx1 Nx2 %x %x %x %x\n", pstRef->u32PhyAddr_Y,
                  pstCur->u32PhyAddr_Y, pstNxt1->u32PhyAddr_Y, pstNxt2->u32PhyAddr_Y);

    /*
        {
            HI_U8 chFile[64] = "vpss_detile2.yuv";
            HI_DRV_VIDEO_FRAME_S stFrame;

            memset(&stFrame, 0x0, sizeof(stFrame));

            stFrame.u32Width = 1920;
            stFrame.u32Height = 1080;
            stFrame.ePixFormat = HI_DRV_PIX_FMT_NV21;
            stFrame.enBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;
            stFrame.bSecure = HI_FALSE;
            stFrame.stBufAddr[0] = *pstNxt2;
            stFrame.stBufAddr[0].u32Stride_Y = pstNxt2->u32Stride_Y;
            stFrame.stBufAddr[0].u32Stride_C = pstNxt2->u32Stride_C;

            VPSS_DBG_INFO("STEP1: tmp img save: Yaddr w h YS CS %x %d %d %d %d",
                          stFrame.stBufAddr[0].u32PhyAddr_Y,
                          stFrame.u32Width, stFrame.u32Height, stFrame.stBufAddr[0].u32Stride_Y,
                          stFrame.stBufAddr[0].u32Stride_C);
            VPSS_OSAL_WRITEYUV(&stFrame, chFile);
        }
    */
    stTunnelIn.bEnable = HI_FALSE;
    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_TUNNEL_IN, (HI_VOID *)&stTunnelIn, HI_NULL);

    /* db */
    /* db_det */
    stDBDETInfo.bEnable = HI_FALSE;
    stDBInfo.bEnable = HI_FALSE;
    stNrInfo.bEnable = HI_FALSE;

    stDBInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DB_CTRL) - sizeof(HI_U32);

    bRfrEnableFlag      = HI_FALSE;
    //snr_en 是db,dm, nr的总开关， SNR包括db,dm,nr
    stSnrInfo.bEnable   = HI_FALSE; //DEI与SNR共用BUFFER, 开DEI则关闭SNR
    stTnrInfo.bEnable   = HI_TRUE;  //只需开MA-TNR, 关闭MC-TNR
    stMcTnrInfo.bEnable = HI_FALSE;

#if 0 //98mv200 do rwzb in software, no need to disable tnr,snr
    if (pstHalInfo->stRwzbInfo.u32IsRwzb > 0)
    {
        stSnrInfo.bEnable   = HI_FALSE;
        stTnrInfo.bEnable   = HI_FALSE;
    }
#endif

    /* snr, tnr */
    //In 98mv200 all of SNR,DB,DM use DB'coef addr(VPSS_DB_CTRL).
    stSnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DB_CTRL) - sizeof(HI_U32);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_SNR, (HI_VOID *)&stSnrInfo, HI_NULL);

    //TNR分为 MA-TNR,  MC-TNR, MC需要单独设置开关, MA的开关即全局tnr开关
    stTnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_TNR_CONTRL) - sizeof(HI_U32);

    if VPSS_IS_YUV420_FMT(pstHalInfo->stInInfo.enFormat)
    {
        stTnrInfo.u32Ymotionmode = 1;
    }
    else
    {
        stTnrInfo.u32Ymotionmode = 0;
    }

    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_TNR, (HI_VOID *)&stTnrInfo, HI_NULL);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_TNR_MC, (HI_VOID *)&stMcTnrInfo, HI_NULL);


    /* next2 config */
    stFrameCfg.bEn              = HI_TRUE;
    stFrameCfg.bSecure          = pstHalInfo->stInInfo.bSecure;
    stFrameCfg.enBitWidth       = pstHalInfo->stInInfo.enBitWidth;
    stFrameCfg.enPixelFmt       = HI_DRV_PIX_FMT_NV21;
    stFrameCfg.u32Width         = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height        = pstHalInfo->stInInfo.u32Height * 2;
    stFrameCfg.bProgressive     = HI_FALSE;
    stFrameCfg.stOffset.s32X    = 0;
    stFrameCfg.stOffset.s32Y    = 0;
    /*
        4：逐行读取顶场,本项目表示tile格式的场图按帧存
        5：逐行读取底场,本项目表示tile格式的场图按帧存
    */
    stFrameCfg.bSpecialTile     = HI_TRUE;

    stFrameCfg.bTopFirst = pstHalInfo->stInInfo.bTopFirst;

    if (HI_DRV_FIELD_TOP == pstHalInfo->stInInfo.enFieldMode)
    {
        stFrameCfg.bTop = HI_TRUE;
    }
    else
    {
        stFrameCfg.bTop = HI_FALSE;
    }

    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y  = pstNxt2->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C  = pstNxt2->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y   = pstNxt2->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C   = pstNxt2->u32Stride_C;
    stFrameCfg.bCompress = HI_FALSE;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif

    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_NX2, (HI_VOID *)&stFrameCfg, HI_NULL);

    /* nx1 config */
    stFrameCfg.bEn           = HI_TRUE;
    stFrameCfg.u32Width     = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height    = pstHalInfo->stInInfo.u32Height * 2;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y  = pstNxt1->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C  = pstNxt1->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y   = pstNxt1->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C   = pstNxt1->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif

    stFrameCfg.enPixelFmt = HI_DRV_PIX_FMT_NV21;
    stFrameCfg.enBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_NX1, (HI_VOID *)&stFrameCfg, HI_NULL);

    /* cur config */
    stFrameCfg.bEn          = HI_TRUE;
    stFrameCfg.u32Width     = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height    =  pstHalInfo->stInInfo.u32Height * 2;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstCur->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstCur->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstCur->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstCur->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif

    stFrameCfg.enPixelFmt = HI_DRV_PIX_FMT_NV21;
    stFrameCfg.enBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_CUR, (HI_VOID *)&stFrameCfg, HI_NULL);

    /* ref config */
    stFrameCfg.bEn          = HI_TRUE;
    stFrameCfg.u32Width     = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height    =  pstHalInfo->stInInfo.u32Height * 2;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstRef->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstRef->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstRef->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstRef->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif

    stFrameCfg.enPixelFmt = HI_DRV_PIX_FMT_NV21;
    stFrameCfg.enBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_REF, (HI_VOID *)&stFrameCfg, HI_NULL);

    /* rfr config */
    pstRfr         = &pstHalInfo->stInWbcInfo.stAddr;
    bRfrEnableFlag = HI_TRUE;
    stFrameCfg.bEn = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstRfr->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstRfr->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstRfr->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstRfr->u32Stride_C;
    stFrameCfg.enBitWidth = pstHalInfo->stInWbcInfo.enBitWidth;
    stFrameCfg.enPixelFmt = pstHalInfo->stInWbcInfo.enFormat;
    stFrameCfg.u32Width   = pstHalInfo->stInWbcInfo.u32Width;
    stFrameCfg.u32Height  = pstHalInfo->stInWbcInfo.u32Height;
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_WRITE_RFR, (HI_VOID *)&stFrameCfg, &bRfrEnableFlag);

    /* vhd0 config */
    VPSS_HAL_SetPortCfg(enIP, stRegAddr, pstHalInfo);


    //逐隔行都要配置
    sttInfoCfg.u32WPhyAddr = pstHalInfo->stSttAddr.u32stt_w_phy_addr;
    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_STT, (HI_VOID *)&sttInfoCfg, (HI_VOID *)HI_NULL);

    VPSS_HAL_SetDeiCfg(enIP, pstHalInfo, stRegAddr);

    stMcDeiAlgCfg.bEnable = HI_FALSE;
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_MCDEI, (HI_VOID *)&stMcDeiAlgCfg, HI_NULL);

    /* igbm */
    stAlgInfo.bEnable = HI_TRUE;
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_IGBM, (HI_VOID *)&stAlgInfo, HI_NULL);

    /* ifmd */
    stAlgInfo.bEnable = HI_TRUE;
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_IFMD, (HI_VOID *)&stAlgInfo, HI_NULL);

    /* smmu */
#ifdef HI_VPSS_SMMU_SUPPORT
    stSMMUCfg.bGlobalBypass = HI_FALSE;
    stSMMUCfg.bIntEnable = HI_TRUE;
    stSMMUCfg.u32Ptw_pf = 0x3;
    HI_DRV_SMMU_GetPageTableAddr(&u32PageAddr, &u32ErrReadAddr, &u32ErrWriteAddr);
    stSMMUCfg.u32CB_TTBR = stSMMUCfg.u32SCB_TTBR = u32PageAddr;
    stSMMUCfg.u32Err_s_rd_addr = stSMMUCfg.u32Err_ns_rd_addr = u32ErrReadAddr;
    stSMMUCfg.u32Err_s_wr_addr = stSMMUCfg.u32Err_ns_wr_addr = u32ErrWriteAddr;
#else
    stSMMUCfg.bGlobalBypass = HI_TRUE;
    stSMMUCfg.bIntEnable = HI_FALSE;
#endif

    stRegAddr_MMU.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr_MMU.pu8BaseVirAddr = stHalCtx[enIP][0].pu8BaseRegVir;
    VPSS_CBB_FUNC_SetConfig(stRegAddr_MMU, CBB_FUNC_SMMU, (HI_VOID *)&stSMMUCfg, HI_NULL);
    /* tnr mad */
    if (HI_TRUE == stTnrInfo.bEnable)
    {
        /* tnr mad */
        stMadInfo_Tnr.bEn    = stTnrInfo.bEnable;
        stMadInfo_Tnr.u32Wth = pstHalInfo->stInInfo.u32Width;
        stMadInfo_Tnr.u32Hgt = pstHalInfo->stInInfo.u32Height ;// / 2;
        stMadInfo_Tnr.u32RPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Tnrmad_raddr;
        stMadInfo_Tnr.u32WPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Tnrmad_waddr;
        stMadInfo_Tnr.u32Stride   = pstHalInfo->stNrInfo.stNrMadCfg.u32madstride;
#ifdef HI_VPSS_SMMU_SUPPORT
        stMadInfo_Tnr.bSmmu_R = HI_TRUE;
        stMadInfo_Tnr.bSmmu_W = HI_TRUE;
#else
        stMadInfo_Tnr.bSmmu_R = HI_FALSE;
        stMadInfo_Tnr.bSmmu_W = HI_FALSE;
#endif
        VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_TNR_MAD, (HI_VOID *)&stMadInfo_Tnr, HI_NULL);
    }

    pstHalInfo->pstH265RefList->u32RefListHead = (pstHalInfo->pstH265RefList->u32RefListHead + 1) %
            DEF_VPSS_HAL_REF_LIST_NUM;

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_Set_2DDei_Last2Field_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy)
{
    HI_DRV_VID_FRAME_ADDR_S *pstNext2;
    HI_DRV_VID_FRAME_ADDR_S *pstNext2_LB;

    HI_DRV_VID_FRAME_ADDR_S *pstRef;
    HI_DRV_VID_FRAME_ADDR_S *pstNxt1;

    HI_DRV_VID_FRAME_ADDR_S *pstCur;
    HI_DRV_VID_FRAME_ADDR_S *pstRfr;

    HI_BOOL bRfrEnableFlag;
    HI_U32 u32PageAddr;
    HI_U32 u32ErrReadAddr;
    HI_U32 u32ErrWriteAddr;

    CBB_REG_ADDR_S      stRegAddr;
    CBB_REG_ADDR_S      stRegAddr_MMU;
    CBB_FRAME_S         stFrameCfg;
    CBB_FUNC_TUNNELIN_S stTunnelIn;
    CBB_FUNC_SMMU_S     stSMMUCfg;
    CBB_INFO_S          stMadInfo_Tnr;
    CBB_INFO_S          stMadInfo_Snr;
    CBB_ALG_INFO_S      stDBInfo;
    CBB_ALG_INFO_S      stDBDETInfo;
    CBB_ALG_INFO_S      stNrInfo;
    CBB_ALG_INFO_S      stSnrInfo;
    CBB_ALG_INFO_S      stTnrInfo;
    CBB_ALG_INFO_S      stMcTnrInfo;
    CBB_ALG_INFO_S      stAlgInfo;
    CBB_INFO_S          sttInfoCfg;
    CBB_ALG_INFO_S      stMcDeiAlgCfg;
    CBB_ALG_INFO_S      stHdrInfo;
    CBB_FUNC_FDIFRO_S   stFuncFdIFdOCfg;
    HI_BOOL             bMedsEn = HI_FALSE;

    VPSS_MEM_CLEAR(stRegAddr);
    VPSS_MEM_CLEAR(stRegAddr_MMU);
    VPSS_MEM_CLEAR(stFrameCfg);
    VPSS_MEM_CLEAR(stTunnelIn);
    VPSS_MEM_CLEAR(stSMMUCfg);
    VPSS_MEM_CLEAR(stMadInfo_Tnr);
    VPSS_MEM_CLEAR(stMadInfo_Snr);
    VPSS_MEM_CLEAR(stDBInfo);
    VPSS_MEM_CLEAR(stDBDETInfo);
    VPSS_MEM_CLEAR(stNrInfo);
    VPSS_MEM_CLEAR(stSnrInfo);
    VPSS_MEM_CLEAR(stTnrInfo);
    VPSS_MEM_CLEAR(stMcTnrInfo);
    VPSS_MEM_CLEAR(stAlgInfo);
    VPSS_MEM_CLEAR(sttInfoCfg);
    VPSS_MEM_CLEAR(stMcDeiAlgCfg);
    VPSS_MEM_CLEAR(stHdrInfo);
    VPSS_MEM_CLEAR(stFuncFdIFdOCfg);

    stRegAddr.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr.u32NodePhyAddr = u32AppPhy;

    VPSS_REG_ResetAppReg((S_VPSS_REGS_TYPE *)pu32AppVir, pstHalInfo->pstPqCfg);

    if (VPSS_FRAME_NO_LAST1  == pstHalInfo->u32DetileFieldIdx)
    {
        /* channel config */
        pstRef      = &pstHalInfo->stInRefInfo[0].stAddr;
        pstCur      = &pstHalInfo->stInRefInfo[1].stAddr;
        pstNxt1     = pstRef;
        pstNext2    = &pstHalInfo->stInInfo.stAddr;
        pstNext2_LB = &pstHalInfo->stInInfo.stAddr_LB;
        pstRfr      = &pstHalInfo->stInWbcInfo.stAddr;
    }
    else //(VPSS_FRAME_NO_LAST2  == pstHalInfo->u32DetileFieldIdx)
    {
        /* channel config */
        pstRef      = &pstHalInfo->stInRefInfo[0].stAddr;
        pstCur      = &pstHalInfo->stInRefInfo[1].stAddr;
        pstNxt1     = &pstHalInfo->stInRefInfo[2].stAddr;
        pstNext2    = &pstHalInfo->stInInfo.stAddr;
        pstNext2_LB = &pstHalInfo->stInInfo.stAddr_LB;
        pstRfr      = &pstHalInfo->stInWbcInfo.stAddr;
    }

#if 0
    HI_PRINT("Index %#x \n", pstHalInfo->u32DetileFieldIdx);
    HI_PRINT("Ref  phy:%08x, vir:%x\n", pstRef->u32PhyAddr_Y, (HI_U32)pstRef->vir_addr_y);
    HI_PRINT("Cur  phy:%08x, vir:%x\n", pstCur->u32PhyAddr_Y, (HI_U32)pstCur->vir_addr_y);
    HI_PRINT("Nx1  phy:%08x, vir:%x\n", pstNxt1->u32PhyAddr_Y, (HI_U32)pstNxt1->vir_addr_y);
    HI_PRINT("Nx2  phy:%08x, vir:%x\n", pstNext2->u32PhyAddr_Y, (HI_U32)pstNext2->vir_addr_y);
    HI_PRINT("Rfr  phy:%08x, vir:%x stid:%d %d\n", pstRfr->u32PhyAddr_Y, (HI_U32)pstRfr->vir_addr_y,
             pstRfr->u32Stride_Y, pstRfr->u32Stride_C);
#endif

    //pstRef = pstCur = pstNxt1 = pstNext2; //Debug use. all ref to nx2


    /*tunnel*/

    stTunnelIn.bEnable = HI_FALSE;
    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_TUNNEL_IN, (HI_VOID *)&stTunnelIn, HI_NULL);

    bRfrEnableFlag      = HI_FALSE;
    //snr_en 是db,dm, nr的总开关， SNR包括db,dm,nr
    stSnrInfo.bEnable   = HI_FALSE; //只支持标清的SNR
    stTnrInfo.bEnable   = HI_FALSE;  //只需开MA-TNR, 关闭MC-TNR
    stMcTnrInfo.bEnable = HI_FALSE;

    if (VPSS_IS_YUV422_FMT(pstHalInfo->stInInfo.enFormat))
    {
        stDBDETInfo.bEnable = HI_FALSE;
        stDBInfo.bEnable    = HI_FALSE;
        stSnrInfo.bEnable   = HI_FALSE;
    }

    if ((VPSS_HAL_IS_RWZB(pstHalInfo->stRwzbInfo.u32IsRwzb)) && (HI_FALSE == pstHalInfo->bSplitEnable))
    {
        stSnrInfo.bEnable   = HI_FALSE;
        stTnrInfo.bEnable   = HI_FALSE;
    }

    /* snr, tnr */
    //In 98mv200 all of SNR,DB,DM use DB'coef addr(VPSS_DB_CTRL).
    stSnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DB_CTRL) - sizeof(HI_U32);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_SNR, (HI_VOID *)&stSnrInfo, HI_NULL);

    //TNR分为 MA-TNR,  MC-TNR, MC需要单独设置开关, MA的开关即全局tnr开关
    stTnrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_TNR_CONTRL) - sizeof(HI_U32);

    if VPSS_IS_YUV420_FMT(pstHalInfo->stInInfo.enFormat)
    {
        stTnrInfo.u32Ymotionmode = 1;
    }
    else
    {
        stTnrInfo.u32Ymotionmode = 0;
    }

    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_TNR, (HI_VOID *)&stTnrInfo, HI_NULL);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_TNR_MC, (HI_VOID *)&stMcTnrInfo, HI_NULL);

    stHdrInfo.bEnable = HI_FALSE;
    stHdrInfo.u32ParaAddr = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL,
                            VPSS_LCHDR_CTRL) - sizeof(HI_U32);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_HDR, (HI_VOID *)&stHdrInfo, &
                         pstHalInfo->stHdrInfo.bHdrIn);


    /* next2 config */
    stFrameCfg.bEn              = HI_TRUE;
    stFrameCfg.bSecure          = pstHalInfo->stInInfo.bSecure;
    stFrameCfg.enBitWidth       = pstHalInfo->stInInfo.enBitWidth;
    stFrameCfg.enPixelFmt       = pstHalInfo->stInInfo.enFormat;    // TODO: 做格式转换
    stFrameCfg.u32Width         = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height        = pstHalInfo->stInInfo.u32Height;

    pstHalInfo->stInInfo.bProgressive = HI_FALSE; //fix false

    stFrameCfg.bProgressive     = HI_FALSE;
    stFrameCfg.bSpecialTile     = HI_TRUE;
    stFrameCfg.stOffset.s32X    = 0;
    stFrameCfg.stOffset.s32Y    = 0;


    stFrameCfg.bTopFirst = pstHalInfo->stInInfo.bTopFirst;

    if (HI_DRV_FIELD_TOP == pstHalInfo->stInInfo.enFieldMode)
    {
        stFrameCfg.bTop = HI_TRUE;
    }
    else
    {
        stFrameCfg.bTop = HI_FALSE;
    }

    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y  = pstNext2->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C  = pstNext2->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y   = pstNext2->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C   = pstNext2->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif

    if ( HI_DRV_PIXEL_BITWIDTH_10BIT == pstHalInfo->stInInfo.enBitWidth )
    {
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_Y   = pstNext2_LB->u32PhyAddr_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_C   = pstNext2_LB->u32PhyAddr_C;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_Y    = pstNext2_LB->u32Stride_Y;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_C    = pstNext2_LB->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_TRUE;
#else
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_FALSE;
#endif
    }

    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_CMP)
    {
        stFrameCfg.bCompress = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_YHead  = pstNext2->u32PhyAddr_YHead;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_CHead  = pstNext2->u32PhyAddr_CHead;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Head_Size      = pstNext2->u32Head_Size;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Head_Stride    = pstNext2->u32Head_Stride;
#ifdef HI_VPSS_SMMU_SUPPORT
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y   = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C   = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y    = HI_TRUE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C    = HI_TRUE;
#else
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y = HI_FALSE;
        stFrameCfg.stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C = HI_FALSE;
#endif
    }
    else
    {
        stFrameCfg.bCompress = HI_FALSE;
    }

    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_NX2, (HI_VOID *)&stFrameCfg, HI_NULL);

    stFuncFdIFdOCfg.bEnable = HI_FALSE; //pstHalInfo->stInInfo.bSpecField;
    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_FDIFRO, (HI_VOID *)&stFuncFdIFdOCfg, HI_NULL);

    /* rwzb */
    if (pstHalInfo->stRwzbInfo.u32EnRwzb)
    {
        if (VPSS_IS_TILE_FMT(pstHalInfo->stInInfo.enFormat))
        {
            VPSS_HAL_RWZB_Calc(pstHalInfo, &pstHalInfo->stInRefInfo[0].stAddr); //use wbc data(nx1,has been detiled)
        }
        else
        {
            VPSS_HAL_RWZB_Calc(pstHalInfo, pstNext2); //use nx2 data
        }
    }

    /* nx1 config */
    stFrameCfg.bEn          = HI_TRUE;
    stFrameCfg.u32Width     = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height    = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y  = pstNxt1->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C  = pstNxt1->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y   = pstNxt1->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C   = pstNxt1->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif
    stFrameCfg.enPixelFmt = pstHalInfo->stInRefInfo[2].enFormat;
    stFrameCfg.enBitWidth = pstHalInfo->stInRefInfo[2].enBitWidth;
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_NX1, (HI_VOID *)&stFrameCfg, HI_NULL);

    /* cur config */
    stFrameCfg.bEn          = HI_TRUE;
    stFrameCfg.u32Width     = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height    = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstCur->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstCur->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstCur->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstCur->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif
    stFrameCfg.enPixelFmt = pstHalInfo->stInRefInfo[1].enFormat;
    stFrameCfg.enBitWidth = pstHalInfo->stInRefInfo[1].enBitWidth;
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_CUR, (HI_VOID *)&stFrameCfg, HI_NULL);

    /* ref config */
    stFrameCfg.bEn          = HI_TRUE;
    stFrameCfg.u32Width     = pstHalInfo->stInInfo.u32Width;
    stFrameCfg.u32Height    = pstHalInfo->stInInfo.u32Height;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstRef->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstRef->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstRef->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstRef->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif
    stFrameCfg.enPixelFmt = pstHalInfo->stInRefInfo[0].enFormat;
    stFrameCfg.enBitWidth = pstHalInfo->stInRefInfo[0].enBitWidth;
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_REF, (HI_VOID *)&stFrameCfg, HI_NULL);

    /* rfr config */
    //stFrameCfg.bEn = HI_FALSE;
    stFrameCfg.bEn = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y = pstRfr->u32PhyAddr_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C = pstRfr->u32PhyAddr_C;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y  = pstRfr->u32Stride_Y;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C  = pstRfr->u32Stride_C;
#ifdef HI_VPSS_SMMU_SUPPORT
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_TRUE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_TRUE;
#else
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = HI_FALSE;
    stFrameCfg.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C = HI_FALSE;
#endif
    stFrameCfg.enBitWidth = pstHalInfo->stInWbcInfo.enBitWidth;
    stFrameCfg.enPixelFmt = pstHalInfo->stInWbcInfo.enFormat;
    stFrameCfg.u32Width   = pstHalInfo->stInWbcInfo.u32Width;
    stFrameCfg.u32Height  = pstHalInfo->stInWbcInfo.u32Height;
    VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_WRITE_RFR, (HI_VOID *)&stFrameCfg, &bRfrEnableFlag);

    /* vhd0 config */
    VPSS_HAL_SetPortCfg(enIP, stRegAddr, pstHalInfo);

    //逐隔行都要配置
    sttInfoCfg.u32WPhyAddr = pstHalInfo->stSttAddr.u32stt_w_phy_addr;
    VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_STT, (HI_VOID *)&sttInfoCfg, (HI_VOID *)HI_NULL);

    VPSS_HAL_SetDeiCfg(enIP, pstHalInfo, stRegAddr);

    bMedsEn = (stMcTnrInfo.bEnable || stMcDeiAlgCfg.bEnable);
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_MCDEI, (HI_VOID *)&stMcDeiAlgCfg, &bMedsEn);

    if (bMedsEn)
    {
        VPSS_HAL_SetRgmvCfg(enIP, pstHalInfo, stRegAddr);
    }

    if ((pstHalInfo->bSplitEnable) || (stMcDeiAlgCfg.bEnable))
    {
        VPSS_HAL_SetMcDeiCfg(enIP, pstHalInfo, stRegAddr);
        VPSS_HAL_SetRgmvCfg(enIP, pstHalInfo, stRegAddr);
    }

    /* igbm */
    stAlgInfo.bEnable = HI_TRUE;
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_IGBM, (HI_VOID *)&stAlgInfo, HI_NULL);

    /* ifmd */
    stAlgInfo.bEnable = HI_TRUE;
    VPSS_AlgCfg_BaseFunc(stRegAddr, CBB_ALG_IFMD, (HI_VOID *)&stAlgInfo, HI_NULL);

    /* smmu */
#ifdef HI_VPSS_SMMU_SUPPORT
    stSMMUCfg.bGlobalBypass = HI_FALSE;
    stSMMUCfg.bIntEnable = HI_TRUE;
    stSMMUCfg.u32Ptw_pf = 0x3;
    HI_DRV_SMMU_GetPageTableAddr(&u32PageAddr, &u32ErrReadAddr, &u32ErrWriteAddr);
    stSMMUCfg.u32CB_TTBR = stSMMUCfg.u32SCB_TTBR = u32PageAddr;
    stSMMUCfg.u32Err_s_rd_addr = stSMMUCfg.u32Err_ns_rd_addr = u32ErrReadAddr;
    stSMMUCfg.u32Err_s_wr_addr = stSMMUCfg.u32Err_ns_wr_addr = u32ErrWriteAddr;
#else
    stSMMUCfg.bGlobalBypass = HI_TRUE;
    stSMMUCfg.bIntEnable = HI_FALSE;
#endif

    stRegAddr_MMU.pu8NodeVirAddr = (HI_U8 *)pu32AppVir;
    stRegAddr_MMU.pu8BaseVirAddr = stHalCtx[enIP][0].pu8BaseRegVir;
    VPSS_CBB_FUNC_SetConfig(stRegAddr_MMU, CBB_FUNC_SMMU, (HI_VOID *)&stSMMUCfg, HI_NULL);

    /* tnr mad */
    //if (HI_TRUE == stTnrInfo.bEnable)
    {
        /* tnr mad */
        stMadInfo_Tnr.bEn    = stTnrInfo.bEnable;
        stMadInfo_Tnr.u32Wth = pstHalInfo->stInInfo.u32Width;
        stMadInfo_Tnr.u32Hgt = pstHalInfo->stInInfo.u32Height / 2;
        stMadInfo_Tnr.u32RPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Tnrmad_raddr;
        stMadInfo_Tnr.u32WPhyAddr = pstHalInfo->stNrInfo.stNrMadCfg.u32Tnrmad_waddr;
        stMadInfo_Tnr.u32Stride   = pstHalInfo->stNrInfo.stNrMadCfg.u32madstride;
#ifdef HI_VPSS_SMMU_SUPPORT
        stMadInfo_Tnr.bSmmu_R = HI_TRUE;
        stMadInfo_Tnr.bSmmu_W = HI_TRUE;
#else
        stMadInfo_Tnr.bSmmu_R = HI_FALSE;
        stMadInfo_Tnr.bSmmu_W = HI_FALSE;
#endif
        VPSS_CBB_INFO_SetConfig(stRegAddr, CBB_INFO_TNR_MAD, (HI_VOID *)&stMadInfo_Tnr, HI_NULL);
    }

    return HI_SUCCESS;
}



HI_BOOL VPSS_HAL_SupportMcSplit(VPSS_MCDI_SPLIT_MODE_E enSplitMode, HI_U32 u32Width, HI_BOOL bProgressive)
{
#ifdef VPSS_SUPPORT_SPLIT_MCDI
    if ((VPSS_MCDI_SPLIT_MODE_5 == enSplitMode) && (HI_FALSE == bProgressive) && (u32Width == 1920))
    {
        return HI_TRUE ;
    }
    return HI_FALSE;
#else
    return HI_FALSE;
#endif
}

HI_VOID VPSS_HAL_CalcSplitWth(HI_U32 u32Width, HI_U32 *pu32FirstWth, HI_U32 *pu32MidWth, HI_U32 *pu32LastWth, HI_U32 *pu32SplitCnt)
{
    (*pu32SplitCnt) = 4;//(u32Width + VPSS_SPLIT_WTH - 1) / VPSS_SPLIT_WTH;
    (*pu32FirstWth) = 9 * VPSS_RGMV_WTH * 2 + VPSS_RGMV_WTH * 2; //(VPSS_SPLIT_WTH + VPSS_RGMV_WTH * 2);
    (*pu32MidWth)   = ((*pu32SplitCnt) > 2) ? (6 * VPSS_RGMV_WTH * 2 + VPSS_RGMV_WTH * 4) : 0;
    (*pu32LastWth)  = ((*pu32SplitCnt) > 1) ? ((u32Width - ((*pu32SplitCnt) - 2) * 6 * VPSS_RGMV_WTH * 2  - 9 * VPSS_RGMV_WTH * 2) + VPSS_RGMV_WTH * 2) : 0;
}

HI_S32 VPSS_HAL_MCDINRBuffer_Alloc(SMMU_BUFFER_S *pstSBuf, HI_BOOL bSecure)
{
    HI_S32 s32Ret = HI_SUCCESS;

#define VPSS_SPLIT_TMPBUF_SIZE  (1920*(1080+32)) //y.c has same size

#ifdef HI_VPSS_SMMU_SUPPORT

    if (bSecure)
    {
        if (pstSBuf->u32Size == 0)
        {
#ifdef HI_TEE_SUPPORT
            s32Ret = HI_DRV_SECSMMU_Alloc("VPSS_MCDI_MCNR_MMU_S", VPSS_SPLIT_TMPBUF_SIZE, 0, pstSBuf);
#else
            s32Ret = HI_DRV_SMMU_AllocAndMap("VPSS_MCDI_MCNR_MMU_NS", VPSS_SPLIT_TMPBUF_SIZE, 0, pstSBuf);
#endif
        }
    }
    else
    {
        if (pstSBuf->u32Size == 0)
        {
            s32Ret = HI_DRV_SMMU_AllocAndMap("VPSS_MCDI_MCNR_MMU_NS", VPSS_SPLIT_TMPBUF_SIZE, 0, pstSBuf);
        }
    }

    if (s32Ret != HI_SUCCESS)
    {
        VPSS_FATAL("Alloc mmu buffer failed\n");
        return HI_FAILURE;
    }

#else
    VPSS_FATAL("Alloc mmz buffer failed\n");
    return HI_FAILURE;
#endif

    return HI_SUCCESS;
}
HI_VOID VPSS_HAL_MCDINRBuffer_Free(SMMU_BUFFER_S *pstSBuf)
{
#ifdef HI_VPSS_SMMU_SUPPORT
    if (pstSBuf->u32Size != 0)
    {
        HI_DRV_SMMU_UnmapAndRelease(pstSBuf);
        memset(pstSBuf, 0, sizeof(SMMU_BUFFER_S));
    }

    if (pstSBuf->u32Size != 0)
    {
#ifdef HI_TEE_SUPPORT
        (HI_VOID)HI_DRV_SECSMMU_Release(pstSBuf);
#else
        HI_DRV_SMMU_UnmapAndRelease(pstSBuf);
#endif
        memset(pstSBuf, 0, sizeof(SMMU_BUFFER_S));
    }

#else
    VPSS_FATAL("Alloc mmz buffer failed\n");
#endif

    return;
}

HI_S32 VPSS_HAL_NodeSplit(S_VPSS_REGS_TYPE *pstVirAddrBasePara,
                          VPSS_HAL_NODE_S *stNODE,
                          HI_U32 u32NodeCount,
                          HI_U32 u32FrameIdx)
{
    S_VPSS_REGS_TYPE *pstVirAddrNodeX;
    HI_U32 u32PhyAddrNodeX;
    HI_U32 u32Idx;

    S_VPSS_REGS_TYPE *pstVirAddrBase;

    HI_U32 u32SrcImgWth;
    HI_U32 u32SrcImgHgt;
    HI_U32 u32SrcImgHgtReal;
    HI_U32 u32SrcImgHgtC;

    HI_U32 u32NodeImgWth;
    HI_U32 u32NodeImgHgt;
    HI_U32 u32NodeImgCHgt;

    HI_U32 u32ImgChmHgt;

    HI_U32 u32AddrOffsetCurY = 0;
    HI_U32 u32AddrOffsetCurC = 0;

    HI_U32 u32AddrOffsetP1Y = 0;
    HI_U32 u32AddrOffsetP1C = 0;

    HI_U32 u32AddrOffsetP2Y = 0;
    HI_U32 u32AddrOffsetP2C = 0;

    HI_U32 u32AddrOffsetP3Y = 0;
    HI_U32 u32AddrOffsetP3C = 0;

    HI_U32 u32AddrOffsetP3IY = 0;
    HI_U32 u32AddrOffsetP3IC = 0;

    HI_U32 u32AddrOffsetRfrY = 0;
    HI_U32 u32AddrOffsetRfrC = 0;

    HI_U32 u32AddrOffsetDiRfrY = 0;
    HI_U32 u32AddrOffsetDiRfrC = 0;

    HI_U32 u32AddrOffsetOutY = 0;
    HI_U32 u32AddrOffsetOutC = 0;

    HI_U32 u32AddrOffsetBlkmv = 0;

    HI_U32 u32AddrOffsetRgmv = 0;

    HI_U32 u32AddrOffsetMt = 0;

    HI_U32 u32AddrOffsetPrjh = 0;

    HI_U32 u32AddrOffsetPrjv = 0;

    HI_U32 u32AddrOffsetMad = 0;

    HI_U32 u32AddrOffsetStCnt = 0;

    HI_U32 u32AddrOffsetSt = 0;

    HI_U32 u32FirstWth = 0;
    HI_U32 u32MidWth = 0;
    HI_U32 u32LastWth = 0;
    HI_U32 u32SplitCnt = 0;

    HI_U32 u32CurOffset = 0;
    HI_U32 u32OutOffset = 0;

    HI_U32 u32TmpWth[5] = {0};

    HI_U32 u32CurPixWth = 0;
    HI_U32 u32P1PixWth = 0;
    HI_U32 u32P2PixWth = 0;
    HI_U32 u32P3PixWth = 0;
    HI_U32 u32RfrPixWth = 0;

    HI_U32 u32RgmvNumH  = 0;
    HI_U32 u32RgmvNumV  = 0;
    HI_U32 u32FirstFieldFlag = 0;
    HI_U32 u32LastFieldFlag = 0;

    HI_U32 u32RegValue = 0;



#ifdef VPSS_OUT_TMPBUF
    HI_U32 u32CAddrOffsetNode1_5 = 0;
#endif

    //    VPSS_ERROR("frame idx %d \n", u32FrameIdx);


    if ((VPSS_FRAME_NO_LAST2 == u32FrameIdx) || (VPSS_FRAME_NO_LAST1 == u32FrameIdx))
    {
        u32LastFieldFlag = 1;
    }
    else if (u32FrameIdx < 3)
    {
        u32FirstFieldFlag = 1;
    }


    VPSS_HAL_MCDINRBuffer_Alloc(&g_VPSSMCDIBuf, HI_FALSE);
    //VPSS_ERROR("Get buf addr %#x\n", g_VPSSMCDIBuf.u32StartSmmuAddr);

    memcpy((HI_U8 *)((HI_ULONG)&g_stVirAddrBaseBackUp),        (HI_U8 *)((HI_ULONG)pstVirAddrBasePara), 0x4C);
    memcpy((HI_U8 *)((HI_ULONG)&g_stVirAddrBaseBackUp + 0x688),  (HI_U8 *)((HI_ULONG)pstVirAddrBasePara + 0x688), (0x11CC - 0x688));
    memcpy((HI_U8 *)((HI_ULONG)&g_stVirAddrBaseBackUp + 0x2000),  (HI_U8 *)((HI_ULONG)pstVirAddrBasePara + 0x2000), 0x600);
    memcpy((HI_U8 *)((HI_ULONG)&g_stVirAddrBaseBackUp + 0x3800), (HI_U8 *)((HI_ULONG)pstVirAddrBasePara + 0x3800), 0x200);
    memcpy((HI_U8 *)((HI_ULONG)&g_stVirAddrBaseBackUp + 0x5000), (HI_U8 *)((HI_ULONG)pstVirAddrBasePara + 0x5000), 0x1000);
    memcpy((HI_U8 *)((HI_ULONG)&g_stVirAddrBaseBackUp + 0xF000), (HI_U8 *)((HI_ULONG)pstVirAddrBasePara + 0xF000), 0x600);

    pstVirAddrBase = &g_stVirAddrBaseBackUp;

    u32SrcImgWth = pstVirAddrBase->VPSS_CF_SIZE.bits.cf_width + 1;
    u32SrcImgHgt = pstVirAddrBase->VPSS_CF_SIZE.bits.cf_height + 1;

    VPSS_HAL_CalcSplitWth(u32SrcImgWth, &u32FirstWth, &u32MidWth, &u32LastWth, &u32SplitCnt);

    for (u32Idx = 0; u32Idx < u32SplitCnt; u32Idx++)
    {
        u32TmpWth[u32Idx] = (u32Idx == 0) ? u32FirstWth :
                            ((u32Idx == (u32SplitCnt - 1)) ? u32LastWth : u32MidWth);
    }

    for (u32Idx = 0; u32Idx < u32NodeCount; u32Idx++)
    {
        pstVirAddrNodeX =  (S_VPSS_REGS_TYPE *)stNODE[u32Idx].pu8AppVir;
        u32PhyAddrNodeX = stNODE[u32Idx].u32AppPhy;

        //先复制所有寄存器配置
        memcpy((HI_U8 *)((HI_ULONG)pstVirAddrNodeX),        (HI_U8 *)((HI_ULONG)pstVirAddrBase), 0x4C);
        memcpy((HI_U8 *)((HI_ULONG)pstVirAddrNodeX + 0x688),  (HI_U8 *)((HI_ULONG)pstVirAddrBase + 0x688), (0x11CC - 0x688));
        memcpy((HI_U8 *)((HI_ULONG)pstVirAddrNodeX + 0x2000),  (HI_U8 *)((HI_ULONG)pstVirAddrBase + 0x2000), 0x600);
        memcpy((HI_U8 *)((HI_ULONG)pstVirAddrNodeX + 0x3800), (HI_U8 *)((HI_ULONG)pstVirAddrBase + 0x3800), 0x200);
        memcpy((HI_U8 *)((HI_ULONG)pstVirAddrNodeX + 0x5000), (HI_U8 *)((HI_ULONG)pstVirAddrBase + 0x5000), 0x1000);
        memcpy((HI_U8 *)((HI_ULONG)pstVirAddrNodeX + 0xF000), (HI_U8 *)((HI_ULONG)pstVirAddrBase + 0xF000), 0x600);
        //获取当前节点宽度
        if (0 == u32Idx) //0
        {
            u32NodeImgWth = u32SrcImgWth;
        }
        else if (0 == (u32Idx - 1) % 4) // 1,5
        {
            u32NodeImgWth = u32FirstWth;
        }
        else if ((4 == u32Idx) || (u32Idx == 8))//4,8
        {
            u32NodeImgWth = u32LastWth;
        }
        else//2,3
        {
            u32NodeImgWth = u32MidWth;
        }



        u32NodeImgHgt = (u32SrcImgHgt + VPSS_OVERLAP_HEIGHT) / 2;
        u32NodeImgCHgt = (pstVirAddrNodeX->VPSS_CF_CTRL.bits.cf_format == 0) ? u32NodeImgHgt / 2 : u32NodeImgHgt;

        u32SrcImgHgtC = (pstVirAddrNodeX->VPSS_CF_CTRL.bits.cf_format == 0) ? u32SrcImgHgt / 2 : u32SrcImgHgt;
        u32SrcImgHgtReal = u32NodeImgHgt >> (pstVirAddrNodeX->VPSS_CF_CTRL.bits.cf_lm_rmode > 1);


        // printk("node %d width %d height %d rel %d\n", u32Idx, u32NodeImgWth, u32NodeImgHgt, u32SrcImgHgtReal);




        u32RgmvNumH = ( u32NodeImgWth + 33) / 64 ;
        u32RgmvNumV = ( u32SrcImgHgtReal +  5) / 8 ;

        pstVirAddrNodeX->VPSS_NODEID.u32 = u32Idx + 100;

        //NX2 配置，由于地址较多，使用offset，因此除了offset和宽度，其他配置不变
        pstVirAddrNodeX->VPSS_CF_SIZE.bits.cf_width  = u32NodeImgWth - 1;
        pstVirAddrNodeX->VPSS_CF_SIZE.bits.cf_height = u32NodeImgHgt - 1;

        u32CurPixWth = (0 == pstVirAddrNodeX->VPSS_CF_CTRL.bits.cf_bitw) ? 8 : 10;
        u32P1PixWth  = u32CurPixWth;
        u32P2PixWth  = (0 == pstVirAddrNodeX->VPSS_P2_CTRL.bits.p2_bitw) ? 8 : 10;
        u32P3PixWth  = u32CurPixWth;
        u32RfrPixWth = (0 == pstVirAddrNodeX->VPSS_NR_RFR_CTRL.bits.nr_rfr_bitw) ? 8 : 10;

        //计算色度高度
        u32ImgChmHgt = (pstVirAddrNodeX->VPSS_CF_CTRL.bits.cf_format == 0) ? u32SrcImgHgtReal / 2 : u32SrcImgHgtReal;
        if ((u32Idx == 0) || (u32Idx > 4))
        {
            pstVirAddrNodeX->VPSS_DIECTRL.bits.ma_only = 1;
            pstVirAddrNodeX->VPSS_CTRL.bits.mcdi_en = 0;
        }
        if (1 == u32FirstFieldFlag)
        {
            if (u32Idx < 5)
            {
                pstVirAddrNodeX->VPSS_DI_RFR_CTRL.bits.di_rfr_en = 0;
                pstVirAddrNodeX->VPSS_RPRJH_CTRL.bits.rprjh_en = 0;
                pstVirAddrNodeX->VPSS_WPRJH_CTRL.bits.wprjh_en = 0;
                pstVirAddrNodeX->VPSS_RPRJV_CTRL.bits.rprjv_en = 0;
                pstVirAddrNodeX->VPSS_WPRJV_CTRL.bits.wprjv_en = 0;
                pstVirAddrNodeX->VPSS_P1RGMV_CTRL.bits.p1rgmv_en = 0;
                pstVirAddrNodeX->VPSS_P2RGMV_CTRL.bits.p2rgmv_en = 0;
                pstVirAddrNodeX->VPSS_CFRGMV_CTRL.bits.cfrgmv_en = 0;
                pstVirAddrNodeX->VPSS_P2MV_CTRL.bits.p2mv_en = 0;
                pstVirAddrNodeX->VPSS_P3MV_CTRL.bits.p3mv_en = 0;
                pstVirAddrNodeX->VPSS_CFMV_CTRL.bits.cfmv_en = 0;
                pstVirAddrNodeX->VPSS_P3MT_CTRL.bits.p3mt_en = 0;
                pstVirAddrNodeX->VPSS_P2MT_CTRL.bits.p2mt_en = 0;
                pstVirAddrNodeX->VPSS_DI_RST_CNT_CTRL.bits.di_rst_cnt_en = 0;
                pstVirAddrNodeX->VPSS_DI_WST_CNT_CTRL.bits.di_wst_cnt_en = 0;
                pstVirAddrNodeX->VPSS_DI_RST_CTRL.bits.di_rst_en = 0;
                pstVirAddrNodeX->VPSS_DI_WST_CTRL.bits.di_wst_en = 0;
                u32RegValue = pstVirAddrNodeX->VPSS_CTRL.u32;
                pstVirAddrNodeX->VPSS_CTRL.u32 = 0;
                pstVirAddrNodeX->VPSS_CTRL.bits.out_pro_en = 1;
                pstVirAddrNodeX->VPSS_CTRL.bits.bfield_first = (u32RegValue & 0x20000000) >> 29;

#if 0
                VPSS_ERROR("VPSS_CFY_ADDR_LOW %d \n", pstVirAddrNodeX->VPSS_CFY_ADDR_LOW.u32);
                VPSS_ERROR("VPSS_P2Y_ADDR_LOW %d \n", pstVirAddrNodeX->VPSS_P2Y_ADDR_LOW.u32);
                VPSS_ERROR("VPSS_NR_RFRY_ADDR_LOW %d \n", pstVirAddrNodeX->VPSS_NR_RFRY_ADDR_LOW.u32);
                VPSS_ERROR("VPSS_OUT0Y_ADDR_LOW %d \n", pstVirAddrNodeX->VPSS_OUT0Y_ADDR_LOW.u32);
#endif
                pstVirAddrNodeX->VPSS_CTRL3.u32 = 0;

                if (u32Idx > 0)
                {
                    if (u32Idx > 1)
                    {
                        u32CurOffset = 9 * VPSS_RGMV_WTH * 2 + 6 * VPSS_RGMV_WTH * 2 * (u32Idx - 2) - VPSS_RGMV_WTH * 2;
                    }
                    pstVirAddrNodeX->VPSS_CF_OFFSET.bits.cf_hor_offset  = u32CurOffset; //pstVirAddrNodeX->VPSS_REFSTRIDE.bits.refy_stride * u32SrcImgHgtReal*2;  //回写是间插的
                    pstVirAddrNodeX->VPSS_CF_OFFSET.bits.cf_ver_offset  = (u32SrcImgHgt - VPSS_OVERLAP_HEIGHT) / 2; //pstVirAddrNodeX->VPSS_REFSTRIDE.bits.refy_stride * u32SrcImgHgtReal*2;  //回写是间插的
                }

                pstVirAddrNodeX->VPSS_P2Y_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_P2Y_ADDR_LOW.u32 + u32AddrOffsetP2Y;
                pstVirAddrNodeX->VPSS_P2C_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_P2C_ADDR_LOW.u32 + u32AddrOffsetP2C;

                pstVirAddrNodeX->VPSS_P2_STRIDE.bits.p2y_stride = HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32P2PixWth + 7) / 8);
                pstVirAddrNodeX->VPSS_P2_STRIDE.bits.p2c_stride = HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32P2PixWth + 7) / 8);

                u32AddrOffsetP2Y += HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32P2PixWth + 7) / 8) * u32SrcImgHgtReal; //pstVirAddrNodeX->VPSS_REFSTRIDE.bits.refy_stride * u32SrcImgHgtReal*2;  //回写是间插的
                u32AddrOffsetP2C += HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32P2PixWth + 7) / 8) * u32ImgChmHgt; //pstVirAddrNodeX->VPSS_REFSTRIDE.bits.refc_stride * u32ImgChmHgt*2;

                //MAD

                pstVirAddrNodeX->VPSS_NR_RMAD_SIZE.bits.nr_rmad_width  = u32NodeImgWth - 1;
                pstVirAddrNodeX->VPSS_NR_RMAD_SIZE.bits.nr_rmad_height = u32SrcImgHgtReal  - 1;
                pstVirAddrNodeX->VPSS_NR_RMAD_STRIDE.bits.nr_rmad_stride = HI_ALIGN_8BIT_YSTRIDE(((((pstVirAddrNodeX->VPSS_NR_RMAD_SIZE.bits.nr_rmad_width + 1) * 5 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_NR_RMAD_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_NR_RMAD_ADDR_LOW.u32 + u32AddrOffsetMad;

                pstVirAddrNodeX->VPSS_NR_WMAD_SIZE.bits.nr_wmad_width  = u32NodeImgWth - 1;
                pstVirAddrNodeX->VPSS_NR_WMAD_SIZE.bits.nr_wmad_height = u32SrcImgHgtReal - 1 ;
                pstVirAddrNodeX->VPSS_NR_WMAD_STRIDE.bits.nr_wmad_stride = HI_ALIGN_8BIT_YSTRIDE(((((pstVirAddrNodeX->VPSS_NR_WMAD_SIZE.bits.nr_wmad_width + 1) * 5 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_NR_WMAD_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_NR_WMAD_ADDR_LOW.u32 + u32AddrOffsetMad;

                u32AddrOffsetMad += pstVirAddrNodeX->VPSS_NR_RMAD_STRIDE.bits.nr_rmad_stride * u32SrcImgHgtReal;

                pstVirAddrNodeX->VPSS_NR_RFRY_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_NR_RFRY_ADDR_LOW.u32 + u32AddrOffsetRfrY;
                pstVirAddrNodeX->VPSS_NR_RFRC_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_NR_RFRC_ADDR_LOW.u32 + u32AddrOffsetRfrC;
                pstVirAddrNodeX->VPSS_NR_RFR_SIZE.bits.nr_rfr_width = pstVirAddrNodeX->VPSS_CF_SIZE.bits.cf_width;
                pstVirAddrNodeX->VPSS_NR_RFR_SIZE.bits.nr_rfr_height = pstVirAddrNodeX->VPSS_CF_SIZE.bits.cf_height;

                pstVirAddrNodeX->VPSS_NR_RFR_STRIDE.bits.nr_rfry_stride = HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32RfrPixWth + 7) / 8);
                pstVirAddrNodeX->VPSS_NR_RFR_STRIDE.bits.nr_rfrc_stride = HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32RfrPixWth + 7) / 8);

                u32AddrOffsetRfrY += HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32RfrPixWth + 7) / 8) * u32SrcImgHgtReal; //pstVirAddrNodeX->VPSS_RFRSTRIDE.bits.rfry_stride * u32SrcImgHgtReal*2; //回写是间插的
                u32AddrOffsetRfrC += HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32RfrPixWth + 7) / 8) * u32ImgChmHgt; //pstVirAddrNodeX->VPSS_RFRSTRIDE.bits.rfrc_stride * u32ImgChmHgt*2;

                if (u32Idx == 0)
                {
                    pstVirAddrNodeX->VPSS_OUT0_SIZE.bits.out0_width  = u32NodeImgWth - 1;
                    pstVirAddrNodeX->VPSS_OUT0_SIZE.bits.out0_height = u32NodeImgHgt / 2  - 1;
                }
                else
                {

                    pstVirAddrNodeX->VPSS_CTRL3.bits.vhd0_crop_en = 1;
                    pstVirAddrNodeX->VPSS_OUT0_SIZE.bits.out0_width  = ((u32Idx == 1) || (u32Idx == 4)) ? (u32NodeImgWth  - 1 - VPSS_RGMV_WTH * 2) : (u32NodeImgWth  - 1 - VPSS_RGMV_WTH * 2 * 2);
                    pstVirAddrNodeX->VPSS_OUT0_SIZE.bits.out0_height = (u32NodeImgHgt   - VPSS_OVERLAP_HEIGHT / 2) / 2 - 1;

                    pstVirAddrNodeX->VPSS_VHD0CROP_POS.bits.vhd0_crop_x = (u32Idx == 1) ? 0 : VPSS_RGMV_WTH * 2 ;
                    pstVirAddrNodeX->VPSS_VHD0CROP_POS.bits.vhd0_crop_y = VPSS_OVERLAP_HEIGHT / 2 / 2;

                    pstVirAddrNodeX->VPSS_VHD0CROP_SIZE.bits.vhd0_crop_width  = (((u32Idx == 1) || (u32Idx == 4)) ? (u32NodeImgWth  - 1 - VPSS_RGMV_WTH * 2) : (u32NodeImgWth  - 1 - VPSS_RGMV_WTH * 2 * 2));
                    pstVirAddrNodeX->VPSS_VHD0CROP_SIZE.bits.vhd0_crop_height = (u32NodeImgHgt   - VPSS_OVERLAP_HEIGHT /
                            2) / 2 - 1;

                    if (u32Idx > 1)
                    {
                        u32OutOffset = 9 * VPSS_RGMV_WTH * 2 + 6 * VPSS_RGMV_WTH * 2 * (u32Idx - 2);
                    }
                    pstVirAddrNodeX->VPSS_OUT0_OFFSET.bits.out0_hor_offset  = u32OutOffset;
                    pstVirAddrNodeX->VPSS_OUT0_OFFSET.bits.out0_ver_offset  = u32SrcImgHgt / 2 / 2;


                }
            }
        }
        else
        {

            if (u32Idx < 5)
            {
                if (0 == u32Idx)
                {
                    pstVirAddrNodeX->VPSS_DI_RFR_CTRL.bits.di_rfr_en = 0;
                    pstVirAddrNodeX->VPSS_RPRJH_CTRL.bits.rprjh_en = 0;
                    pstVirAddrNodeX->VPSS_WPRJH_CTRL.bits.wprjh_en = 0;
                    pstVirAddrNodeX->VPSS_RPRJV_CTRL.bits.rprjv_en = 0;
                    pstVirAddrNodeX->VPSS_WPRJV_CTRL.bits.wprjv_en = 0;
                    pstVirAddrNodeX->VPSS_P1RGMV_CTRL.bits.p1rgmv_en = 0;
                    pstVirAddrNodeX->VPSS_P2RGMV_CTRL.bits.p2rgmv_en = 0;
                    pstVirAddrNodeX->VPSS_CFRGMV_CTRL.bits.cfrgmv_en = 0;
                    pstVirAddrNodeX->VPSS_P2MV_CTRL.bits.p2mv_en = 0;
                    pstVirAddrNodeX->VPSS_P3MV_CTRL.bits.p3mv_en = 0;
                    pstVirAddrNodeX->VPSS_CFMV_CTRL.bits.cfmv_en = 0;
                    pstVirAddrNodeX->VPSS_P3MT_CTRL.bits.p3mt_en = 0;
                    pstVirAddrNodeX->VPSS_P2MT_CTRL.bits.p2mt_en = 0;
                    pstVirAddrNodeX->VPSS_DI_RST_CNT_CTRL.bits.di_rst_cnt_en = 0;
                    pstVirAddrNodeX->VPSS_DI_WST_CNT_CTRL.bits.di_wst_cnt_en = 0;
                    pstVirAddrNodeX->VPSS_DI_RST_CTRL.bits.di_rst_en = 1;
                    pstVirAddrNodeX->VPSS_DI_WST_CTRL.bits.di_wst_en = 1;

                    pstVirAddrNodeX->VPSS_CTRL.u32 = 0;
                    pstVirAddrNodeX->VPSS_CTRL.bits.dei_en = 1;
                    pstVirAddrNodeX->VPSS_CTRL.bits.vhd0_en = 1;
#if 1
                    pstVirAddrNodeX->VPSS_CTRL.bits.tnr_en = 1;
                    pstVirAddrNodeX->VPSS_NR_WMAD_CTRL.bits.nr_wmad_en = 1;
                    pstVirAddrNodeX->VPSS_NR_RMAD_CTRL.bits.nr_rmad_en  = 1;
#else
                    pstVirAddrNodeX->VPSS_CTRL.bits.tnr_en = 0;
                    pstVirAddrNodeX->VPSS_NR_WMAD_CTRL.bits.nr_wmad_en = 0;
                    pstVirAddrNodeX->VPSS_NR_RMAD_CTRL.bits.nr_rmad_en  = 0;
#endif
                    u32AddrOffsetCurY = 0; u32AddrOffsetCurC = 0; u32AddrOffsetP1Y = 0;
                    u32AddrOffsetP1C = 0; u32AddrOffsetP2Y = 0; u32AddrOffsetP2C = 0;
                    u32AddrOffsetP3Y = 0; u32AddrOffsetP3C = 0; u32AddrOffsetP3IY = 0;
                    u32AddrOffsetP3IC = 0; u32AddrOffsetRfrY = 0; u32AddrOffsetRfrC = 0;
                    u32AddrOffsetDiRfrY = 0; u32AddrOffsetDiRfrC = 0; u32AddrOffsetOutY = 0;
                    u32AddrOffsetOutC = 0;
                }


                pstVirAddrNodeX->VPSS_P1Y_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_P1Y_ADDR_LOW.u32 + u32AddrOffsetP1Y;
                pstVirAddrNodeX->VPSS_P1C_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_P1C_ADDR_LOW.u32 + u32AddrOffsetP1C;

                pstVirAddrNodeX->VPSS_P1_STRIDE.bits.p1y_stride = HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32P1PixWth + 7) / 8);
                pstVirAddrNodeX->VPSS_P1_STRIDE.bits.p1c_stride = HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32P1PixWth + 7) / 8);

                pstVirAddrNodeX->VPSS_P2Y_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_P2Y_ADDR_LOW.u32 + u32AddrOffsetP2Y;
                pstVirAddrNodeX->VPSS_P2C_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_P2C_ADDR_LOW.u32 + u32AddrOffsetP2C;

                pstVirAddrNodeX->VPSS_P2_STRIDE.bits.p2y_stride = HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32P2PixWth + 7) / 8);
                pstVirAddrNodeX->VPSS_P2_STRIDE.bits.p2c_stride = HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32P2PixWth + 7) / 8);

                pstVirAddrNodeX->VPSS_P3Y_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_P3Y_ADDR_LOW.u32 + u32AddrOffsetP3Y;
                pstVirAddrNodeX->VPSS_P3C_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_P3C_ADDR_LOW.u32 + u32AddrOffsetP3C;

                pstVirAddrNodeX->VPSS_P3_STRIDE.bits.p3y_stride = HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32P3PixWth + 7) / 8);
                pstVirAddrNodeX->VPSS_P3_STRIDE.bits.p3c_stride = HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32P3PixWth + 7) / 8);

                pstVirAddrNodeX->VPSS_P3IY_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_P3IY_ADDR_LOW.u32 + u32AddrOffsetP3IY;
                pstVirAddrNodeX->VPSS_P3IC_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_P3IC_ADDR_LOW.u32 + u32AddrOffsetP3IC;

                pstVirAddrNodeX->VPSS_P3I_STRIDE.bits.p3iy_stride = HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * 8 + 7) / 8);
                pstVirAddrNodeX->VPSS_P3I_STRIDE.bits.p3ic_stride = HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * 8 + 7) / 8);


                if (1 == u32LastFieldFlag)
                {
                    pstVirAddrNodeX->VPSS_CFY_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_CFY_ADDR_LOW.u32 + u32AddrOffsetCurY;
                    pstVirAddrNodeX->VPSS_CFC_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_CFC_ADDR_LOW.u32 + u32AddrOffsetCurC;

                    pstVirAddrNodeX->VPSS_CF_STRIDE.bits.cfy_stride = HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32CurPixWth + 7) / 8);
                    pstVirAddrNodeX->VPSS_CF_STRIDE.bits.cfc_stride = HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32CurPixWth + 7) / 8);

                    u32AddrOffsetCurY += HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32CurPixWth + 7) / 8) * u32SrcImgHgtReal; //pstVirAddrNodeX->VPSS_RFRSTRIDE.bits.rfry_stride * u32SrcImgHgtReal*2; //回写是间插的
                    u32AddrOffsetCurC += HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32CurPixWth + 7) / 8) * u32ImgChmHgt; //pstVirAddrNodeX->VPSS_RFRSTRIDE.bits.rfrc_stride * u32ImgChmHgt*2;

                    //pstVirAddrNodeX->VPSS_CF_CTRL.bits.cf_lm_rmode = pstVirAddrNodeX->VPSS_CF_CTRL.bits.cf_lm_rmode;
                }
                else
                {
                    if (u32Idx > 0)
                    {
                        if (u32Idx > 1)
                        {
                            u32CurOffset = 9 * VPSS_RGMV_WTH * 2 + 6 * VPSS_RGMV_WTH * 2 * (u32Idx - 2) - VPSS_RGMV_WTH * 2;
                        }
                        pstVirAddrNodeX->VPSS_CF_OFFSET.bits.cf_hor_offset  = u32CurOffset; //pstVirAddrNodeX->VPSS_REFSTRIDE.bits.refy_stride * u32SrcImgHgtReal*2;  //回写是间插的
                        pstVirAddrNodeX->VPSS_CF_OFFSET.bits.cf_ver_offset  = (u32SrcImgHgt - VPSS_OVERLAP_HEIGHT) / 2; //pstVirAddrNodeX->VPSS_REFSTRIDE.bits.refy_stride * u32SrcImgHgtReal*2;  //回写是间插的
                    }
                }
                u32AddrOffsetP1Y += HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32P1PixWth + 7) / 8) * u32SrcImgHgtReal; //pstVirAddrNodeX->VPSS_REFSTRIDE.bits.refy_stride * u32SrcImgHgtReal*2;  //回写是间插的
                u32AddrOffsetP1C += HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32P1PixWth + 7) / 8) * u32ImgChmHgt; //pstVirAddrNodeX->VPSS_REFSTRIDE.bits.refc_stride * u32ImgChmHgt*2;

                u32AddrOffsetP2Y += HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32P2PixWth + 7) / 8) * u32SrcImgHgtReal; //pstVirAddrNodeX->VPSS_REFSTRIDE.bits.refy_stride * u32SrcImgHgtReal*2;  //回写是间插的
                u32AddrOffsetP2C += HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32P2PixWth + 7) / 8) * u32ImgChmHgt; //pstVirAddrNodeX->VPSS_REFSTRIDE.bits.refc_stride * u32ImgChmHgt*2;

                u32AddrOffsetP3Y += HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32P3PixWth + 7) / 8) * u32SrcImgHgtReal; //pstVirAddrNodeX->VPSS_REFSTRIDE.bits.refy_stride * u32SrcImgHgtReal*2;  //回写是间插的
                u32AddrOffsetP3C += HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32P3PixWth + 7) / 8) * u32ImgChmHgt; //pstVirAddrNodeX->VPSS_REFSTRIDE.bits.refc_stride * u32ImgChmHgt*2;

                u32AddrOffsetP3IY += HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * 8 + 7) / 8) * u32SrcImgHgtReal; //pstVirAddrNodeX->VPSS_REFSTRIDE.bits.refy_stride * u32SrcImgHgtReal*2;  //回写是间插的
                u32AddrOffsetP3IC += HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * 8 + 7) / 8) * u32ImgChmHgt; //pstVirAddrNodeX->VPSS_REFSTRIDE.bits.refc_stride * u32ImgChmHgt*2;

                pstVirAddrNodeX->VPSS_NR_RFRY_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_NR_RFRY_ADDR_LOW.u32 + u32AddrOffsetRfrY;
                pstVirAddrNodeX->VPSS_NR_RFRC_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_NR_RFRC_ADDR_LOW.u32 + u32AddrOffsetRfrC;
                pstVirAddrNodeX->VPSS_NR_RFR_SIZE.bits.nr_rfr_width = pstVirAddrNodeX->VPSS_CF_SIZE.bits.cf_width;
                pstVirAddrNodeX->VPSS_NR_RFR_SIZE.bits.nr_rfr_height = pstVirAddrNodeX->VPSS_CF_SIZE.bits.cf_height;

                pstVirAddrNodeX->VPSS_NR_RFR_STRIDE.bits.nr_rfry_stride = HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32RfrPixWth + 7) / 8);
                pstVirAddrNodeX->VPSS_NR_RFR_STRIDE.bits.nr_rfrc_stride = HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32RfrPixWth + 7) / 8);

                u32AddrOffsetRfrY += HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32RfrPixWth + 7) / 8) * u32SrcImgHgtReal; //pstVirAddrNodeX->VPSS_RFRSTRIDE.bits.rfry_stride * u32SrcImgHgtReal*2; //回写是间插的
                u32AddrOffsetRfrC += HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * u32RfrPixWth + 7) / 8) * u32ImgChmHgt; //pstVirAddrNodeX->VPSS_RFRSTRIDE.bits.rfrc_stride * u32ImgChmHgt*2;

                pstVirAddrNodeX->VPSS_DI_RFRY_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_DI_RFRY_ADDR_LOW.u32 + u32AddrOffsetDiRfrY;
                pstVirAddrNodeX->VPSS_DI_RFRC_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_DI_RFRC_ADDR_LOW.u32 + u32AddrOffsetDiRfrC;

                pstVirAddrNodeX->VPSS_DI_RFR_STRIDE.bits.di_rfry_stride = HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * 8 + 7) / 8);
                pstVirAddrNodeX->VPSS_DI_RFR_STRIDE.bits.di_rfrc_stride = HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * 8 + 7) / 8);

                u32AddrOffsetDiRfrY += HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * 8 + 7) / 8) * u32SrcImgHgtReal; //pstVirAddrNodeX->VPSS_RFRSTRIDE.bits.rfry_stride * u32SrcImgHgtReal*2; //回写是间插的
                u32AddrOffsetDiRfrC += HI_ALIGN_8BIT_YSTRIDE((u32NodeImgWth * 8 + 7) / 8) * u32ImgChmHgt; //pstVirAddrNodeX->VPSS_RFRSTRIDE.bits.rfrc_stride * u32ImgChmHgt*2;

                //PRJ
#if 0
                pstVirAddrNodeX->VPSS_RPRJH_SIZE.bits.rprjh_width  = u32RgmvNumH * 128 - 1;
                pstVirAddrNodeX->VPSS_RPRJH_SIZE.bits.rprjh_height = u32RgmvNumV - 1 ;
                pstVirAddrNodeX->VPSS_RPRJH_STRIDE.bits.rprjh_stride = HI_ALIGN_8BIT_YSTRIDE((((u32RgmvNumH * 128 * 16 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_RPRJH_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_RPRJH_ADDR_LOW.u32 + u32AddrOffsetPrjh;

                pstVirAddrNodeX->VPSS_WPRJH_SIZE.bits.wprjh_width  = u32RgmvNumH * 128 - 1;
                pstVirAddrNodeX->VPSS_WPRJH_SIZE.bits.wprjh_height = u32RgmvNumV - 1 ;
                pstVirAddrNodeX->VPSS_WPRJH_STRIDE.bits.wprjh_stride = HI_ALIGN_8BIT_YSTRIDE((((u32RgmvNumH * 128 * 16 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_WPRJH_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_RPRJH_ADDR_LOW.u32 + u32AddrOffsetPrjh;

                u32AddrOffsetPrjh += pstVirAddrNodeX->VPSS_RPRJH_STRIDE.bits.rprjh_stride * u32RgmvNumV;

                pstVirAddrNodeX->VPSS_RPRJV_SIZE.bits.rprjv_width  = u32RgmvNumH * 16 - 1;
                pstVirAddrNodeX->VPSS_RPRJV_SIZE.bits.rprjv_height = u32RgmvNumV - 1;
                pstVirAddrNodeX->VPSS_RPRJV_STRIDE.bits.rprjv_stride = HI_ALIGN_8BIT_YSTRIDE((((u32RgmvNumH * 16 * 16 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_RPRJV_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_RPRJV_ADDR_LOW.u32 + u32AddrOffsetPrjv;

                pstVirAddrNodeX->VPSS_WPRJV_SIZE.bits.wprjv_width  = u32RgmvNumH * 16 - 1;
                pstVirAddrNodeX->VPSS_WPRJV_SIZE.bits.wprjv_height = u32RgmvNumV - 1;
                pstVirAddrNodeX->VPSS_WPRJV_STRIDE.bits.wprjv_stride = HI_ALIGN_8BIT_YSTRIDE((((u32RgmvNumH * 16 * 16 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_WPRJV_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_RPRJH_ADDR_LOW.u32 + u32AddrOffsetPrjh;

                u32AddrOffsetPrjv += pstVirAddrNodeX->VPSS_RPRJV_STRIDE.bits.rprjv_stride * u32RgmvNumV;
#endif
                pstVirAddrNodeX->VPSS_RPRJH_SIZE.bits.rprjh_width  = u32RgmvNumH * 128 - 1;
                pstVirAddrNodeX->VPSS_RPRJH_SIZE.bits.rprjh_height = u32RgmvNumV - 1 ;
                pstVirAddrNodeX->VPSS_RPRJH_STRIDE.bits.rprjh_stride = HI_ALIGN_8BIT_YSTRIDE((((u32RgmvNumH * 128 * 16 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_RPRJH_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_RPRJH_ADDR_LOW.u32 + u32AddrOffsetPrjh;

                pstVirAddrNodeX->VPSS_WPRJH_SIZE.bits.wprjh_width  = u32RgmvNumH * 128 - 1;
                pstVirAddrNodeX->VPSS_WPRJH_SIZE.bits.wprjh_height = u32RgmvNumV - 1 ;
                pstVirAddrNodeX->VPSS_WPRJH_STRIDE.bits.wprjh_stride = HI_ALIGN_8BIT_YSTRIDE((((u32RgmvNumH * 128 * 16 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_WPRJH_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_WPRJH_ADDR_LOW.u32 + u32AddrOffsetPrjh;

                u32AddrOffsetPrjh += pstVirAddrNodeX->VPSS_RPRJH_STRIDE.bits.rprjh_stride * u32RgmvNumV;
                /*printk("node %d 0x%x %d 0x%x %d\n", u32Idx, \
                       pstVirAddrNodeX->VPSS_RPRJH_ADDR_LOW.u32, pstVirAddrNodeX->VPSS_RPRJH_STRIDE.bits.rprjh_stride , \
                       pstVirAddrNodeX->VPSS_WPRJH_ADDR_LOW.u32, pstVirAddrNodeX->VPSS_WPRJH_STRIDE.bits.wprjh_stride);*/

                pstVirAddrNodeX->VPSS_RPRJV_SIZE.bits.rprjv_width  = u32RgmvNumH * 16 - 1;
                pstVirAddrNodeX->VPSS_RPRJV_SIZE.bits.rprjv_height = u32RgmvNumV - 1;
                pstVirAddrNodeX->VPSS_RPRJV_STRIDE.bits.rprjv_stride = HI_ALIGN_8BIT_YSTRIDE((((u32RgmvNumH * 16 * 16 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_RPRJV_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_RPRJV_ADDR_LOW.u32 + u32AddrOffsetPrjv;

                pstVirAddrNodeX->VPSS_WPRJV_SIZE.bits.wprjv_width  = u32RgmvNumH * 16 - 1;
                pstVirAddrNodeX->VPSS_WPRJV_SIZE.bits.wprjv_height = u32RgmvNumV - 1;
                pstVirAddrNodeX->VPSS_WPRJV_STRIDE.bits.wprjv_stride = HI_ALIGN_8BIT_YSTRIDE((((u32RgmvNumH * 16 * 16 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_WPRJV_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_WPRJV_ADDR_LOW.u32 + u32AddrOffsetPrjv;

                u32AddrOffsetPrjv += pstVirAddrNodeX->VPSS_RPRJV_STRIDE.bits.rprjv_stride * u32RgmvNumV;

                //RGMV

                pstVirAddrNodeX->VPSS_P1RGMV_SIZE.bits.p1rgmv_width  = u32RgmvNumH - 1;
                pstVirAddrNodeX->VPSS_P1RGMV_SIZE.bits.p1rgmv_height = u32RgmvNumV - 1;
                pstVirAddrNodeX->VPSS_P1RGMV_STRIDE.bits.p1rgmv_stride = HI_ALIGN_8BIT_YSTRIDE((((u32RgmvNumH * 64 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_P1RGMV_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_P1RGMV_ADDR_LOW.u32 + u32AddrOffsetRgmv;

                pstVirAddrNodeX->VPSS_P2RGMV_STRIDE.bits.p2rgmv_stride = HI_ALIGN_8BIT_YSTRIDE((((u32RgmvNumH * 64 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_P2RGMV_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_P2RGMV_ADDR_LOW.u32 + u32AddrOffsetRgmv;

                pstVirAddrNodeX->VPSS_CFRGMV_SIZE.bits.cfrgmv_width  = u32RgmvNumH - 1;
                pstVirAddrNodeX->VPSS_CFRGMV_SIZE.bits.cfrgmv_height = u32RgmvNumV - 1;
                pstVirAddrNodeX->VPSS_CFRGMV_STRIDE.bits.cfrgmv_stride = HI_ALIGN_8BIT_YSTRIDE((((u32RgmvNumH * 64 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_CFRGMV_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_CFRGMV_ADDR_LOW.u32 + u32AddrOffsetRgmv;

                u32AddrOffsetRgmv += pstVirAddrNodeX->VPSS_P1RGMV_STRIDE.bits.p1rgmv_stride * u32RgmvNumV;
#if 0
                VPSS_ERROR("u32RgmvNumH u32RgmvNumV %d %d %d stride %d addr %#x %#x %#x\n", u32RgmvNumH, u32RgmvNumV,
                           u32AddrOffsetRgmv,
                           pstVirAddrNodeX->VPSS_P1RGMV_STRIDE.bits.p1rgmv_stride,
                           pstVirAddrNodeX->VPSS_P1RGMV_ADDR_LOW.u32,
                           pstVirAddrNodeX->VPSS_P2RGMV_ADDR_LOW.u32,
                           pstVirAddrNodeX->VPSS_CFRGMV_ADDR_LOW.u32
                          );
#endif

                //BLKMV
                pstVirAddrNodeX->VPSS_P2MV_SIZE.bits.p2mv_width  = (u32NodeImgWth + 7) / 8 - 1;
                pstVirAddrNodeX->VPSS_P2MV_SIZE.bits.p2mv_height = (u32SrcImgHgtReal + 3) / 4 - 1;
                pstVirAddrNodeX->VPSS_P2MV_STRIDE.bits.p2mv_stride = HI_ALIGN_8BIT_YSTRIDE(((((pstVirAddrNodeX->VPSS_P2MV_SIZE.bits.p2mv_width + 1)
                        * 32 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_P2MV_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_P2MV_ADDR_LOW.u32 + u32AddrOffsetBlkmv;

                pstVirAddrNodeX->VPSS_P3MV_STRIDE.bits.p3mv_stride = pstVirAddrNodeX->VPSS_P2MV_STRIDE.bits.p2mv_stride;
                pstVirAddrNodeX->VPSS_P3MV_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_P3MV_ADDR_LOW.u32 + u32AddrOffsetBlkmv;

                pstVirAddrNodeX->VPSS_CFMV_SIZE.bits.cfmv_width  = (u32NodeImgWth + 7) / 8 - 1;
                pstVirAddrNodeX->VPSS_CFMV_SIZE.bits.cfmv_height = (u32SrcImgHgtReal + 3) / 4 - 1;
                pstVirAddrNodeX->VPSS_CFMV_STRIDE.bits.cfmv_stride = HI_ALIGN_8BIT_YSTRIDE(((((pstVirAddrNodeX->VPSS_CFMV_SIZE.bits.cfmv_width + 1)
                        * 32 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_CFMV_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_CFMV_ADDR_LOW.u32 + u32AddrOffsetBlkmv;

                u32AddrOffsetBlkmv += pstVirAddrNodeX->VPSS_P2MV_STRIDE.bits.p2mv_stride * (pstVirAddrNodeX->VPSS_P2MV_SIZE.bits.p2mv_height + 1);

                //MT
                pstVirAddrNodeX->VPSS_P3MT_SIZE.bits.p3mt_width  = (u32NodeImgWth + 7) / 8 - 1;
                pstVirAddrNodeX->VPSS_P3MT_SIZE.bits.p3mt_height = (u32SrcImgHgtReal + 3) / 4 - 1;
                pstVirAddrNodeX->VPSS_P3MT_STRIDE.bits.p3mt_stride = HI_ALIGN_8BIT_YSTRIDE(((((pstVirAddrNodeX->VPSS_P3MT_SIZE.bits.p3mt_width + 1) * 8 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_P3MT_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_P3MT_ADDR_LOW.u32 + u32AddrOffsetMt;

                pstVirAddrNodeX->VPSS_P2MT_SIZE.bits.p2mt_width  = (u32NodeImgWth + 7) / 8 - 1;
                pstVirAddrNodeX->VPSS_P2MT_SIZE.bits.p2mt_height = (u32SrcImgHgtReal + 3) / 4 - 1;
                pstVirAddrNodeX->VPSS_P2MT_STRIDE.bits.p2mt_stride = HI_ALIGN_8BIT_YSTRIDE(((((pstVirAddrNodeX->VPSS_P2MT_SIZE.bits.p2mt_width + 1) * 8 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_P2MT_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_P2MT_ADDR_LOW.u32 + u32AddrOffsetMt;

                u32AddrOffsetMt += pstVirAddrNodeX->VPSS_P2MT_STRIDE.bits.p2mt_stride * (pstVirAddrNodeX->VPSS_P2MT_SIZE.bits.p2mt_height + 1);

                //STCNT
                pstVirAddrNodeX->VPSS_DI_RST_CNT_SIZE.bits.di_rst_cnt_width  = (u32NodeImgWth + 2) / 4 - 1;
                pstVirAddrNodeX->VPSS_DI_RST_CNT_SIZE.bits.di_rst_cnt_height =  u32SrcImgHgtReal  - 1;
                pstVirAddrNodeX->VPSS_DI_RST_CNT_STRIDE.bits.di_rst_cnt_stride = HI_ALIGN_8BIT_YSTRIDE(((((pstVirAddrNodeX->VPSS_DI_RST_CNT_SIZE.bits.di_rst_cnt_width + 1) * 8 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_DI_RST_CNT_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_DI_RST_CNT_ADDR_LOW.u32 + u32AddrOffsetStCnt;

                pstVirAddrNodeX->VPSS_DI_WST_CNT_SIZE.bits.di_wst_cnt_width  = (u32NodeImgWth + 2) / 4 - 1;
                pstVirAddrNodeX->VPSS_DI_WST_CNT_SIZE.bits.di_wst_cnt_height =  u32SrcImgHgtReal - 1 ;
                pstVirAddrNodeX->VPSS_DI_WST_CNT_STRIDE.bits.di_wst_cnt_stride = HI_ALIGN_8BIT_YSTRIDE(((((pstVirAddrNodeX->VPSS_DI_WST_CNT_SIZE.bits.di_wst_cnt_width + 1) * 8 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_DI_WST_CNT_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_DI_WST_CNT_ADDR_LOW.u32 + u32AddrOffsetStCnt;

                u32AddrOffsetStCnt += pstVirAddrNodeX->VPSS_DI_WST_CNT_STRIDE.bits.di_wst_cnt_stride * u32SrcImgHgtReal;

                //ST
                pstVirAddrNodeX->VPSS_DI_RST_SIZE.bits.di_rst_width  = (u32NodeImgWth + 2) / 4 - 1;
                pstVirAddrNodeX->VPSS_DI_RST_SIZE.bits.di_rst_height =  u32SrcImgHgtReal - 1 ;
                pstVirAddrNodeX->VPSS_DI_RST_STRIDE.bits.di_rst_stride = HI_ALIGN_8BIT_YSTRIDE(((((pstVirAddrNodeX->VPSS_DI_RST_SIZE.bits.di_rst_width + 1) * 16 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_DI_RST_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_DI_RST_ADDR_LOW.u32 + u32AddrOffsetSt;

                pstVirAddrNodeX->VPSS_DI_WST_SIZE.bits.di_wst_width  = (u32NodeImgWth + 2) / 4 - 1;
                pstVirAddrNodeX->VPSS_DI_WST_SIZE.bits.di_wst_height =  u32SrcImgHgtReal - 1 ;
                pstVirAddrNodeX->VPSS_DI_WST_STRIDE.bits.di_wst_stride = HI_ALIGN_8BIT_YSTRIDE(((((pstVirAddrNodeX->VPSS_DI_WST_SIZE.bits.di_wst_width + 1) * 16 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_DI_WST_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_DI_WST_ADDR_LOW.u32 + u32AddrOffsetSt;

                u32AddrOffsetSt += pstVirAddrNodeX->VPSS_DI_WST_STRIDE.bits.di_wst_stride * u32SrcImgHgtReal;

                //MAD

                pstVirAddrNodeX->VPSS_NR_RMAD_SIZE.bits.nr_rmad_width  = u32NodeImgWth - 1;
                pstVirAddrNodeX->VPSS_NR_RMAD_SIZE.bits.nr_rmad_height = u32SrcImgHgtReal  - 1;
                pstVirAddrNodeX->VPSS_NR_RMAD_STRIDE.bits.nr_rmad_stride = HI_ALIGN_8BIT_YSTRIDE(((((pstVirAddrNodeX->VPSS_NR_RMAD_SIZE.bits.nr_rmad_width + 1) * 5 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_NR_RMAD_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_NR_RMAD_ADDR_LOW.u32 + u32AddrOffsetMad;

                pstVirAddrNodeX->VPSS_NR_WMAD_SIZE.bits.nr_wmad_width  = u32NodeImgWth - 1;
                pstVirAddrNodeX->VPSS_NR_WMAD_SIZE.bits.nr_wmad_height = u32SrcImgHgtReal - 1 ;
                pstVirAddrNodeX->VPSS_NR_WMAD_STRIDE.bits.nr_wmad_stride = HI_ALIGN_8BIT_YSTRIDE(((((pstVirAddrNodeX->VPSS_NR_WMAD_SIZE.bits.nr_wmad_width + 1) * 5 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_NR_WMAD_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_NR_WMAD_ADDR_LOW.u32 + u32AddrOffsetMad;

                u32AddrOffsetMad += pstVirAddrNodeX->VPSS_NR_RMAD_STRIDE.bits.nr_rmad_stride * u32SrcImgHgtReal;

                pstVirAddrNodeX->VPSS_OUT0_SIZE.bits.out0_width  = u32NodeImgWth - 1;
                pstVirAddrNodeX->VPSS_OUT0_SIZE.bits.out0_height = u32NodeImgHgt  - 1;

                if (u32Idx == 0)
                {
                    pstVirAddrNodeX->VPSS_OUT0_SIZE.bits.out0_width  = u32NodeImgWth - 1;
                    pstVirAddrNodeX->VPSS_OUT0_SIZE.bits.out0_height = u32NodeImgHgt  - 1;
                }
                else
                {
                    pstVirAddrNodeX->VPSS_CTRL3.bits.vhd0_crop_en = 1;
                    pstVirAddrNodeX->VPSS_OUT0_SIZE.bits.out0_width  = ((u32Idx == 1) || (u32Idx == 4)) ? (u32NodeImgWth  - 1 - VPSS_RGMV_WTH * 2) : (u32NodeImgWth  - 1 - VPSS_RGMV_WTH * 2 * 2);
                    pstVirAddrNodeX->VPSS_OUT0_SIZE.bits.out0_height = (u32NodeImgHgt  - 1);

                    pstVirAddrNodeX->VPSS_VHD0CROP_POS.bits.vhd0_crop_x = (u32Idx == 1) ? 0 : VPSS_RGMV_WTH * 2 ;
                    pstVirAddrNodeX->VPSS_VHD0CROP_POS.bits.vhd0_crop_y = 0;

                    pstVirAddrNodeX->VPSS_VHD0CROP_SIZE.bits.vhd0_crop_width  = (((u32Idx == 1) || (u32Idx == 4)) ? (u32NodeImgWth  - 1 - VPSS_RGMV_WTH * 2) : (u32NodeImgWth  - 1 - VPSS_RGMV_WTH * 2 * 2));
                    pstVirAddrNodeX->VPSS_VHD0CROP_SIZE.bits.vhd0_crop_height = (u32NodeImgHgt  - 1);

                    if (u32Idx > 1)
                    {
                        u32OutOffset = 9 * VPSS_RGMV_WTH * 2 + 6 * VPSS_RGMV_WTH * 2 * (u32Idx - 2);
                    }
#ifdef VPSS_OUT_TMPBUF
                    pstVirAddrNodeX->VPSS_OUT0_OFFSET.bits.out0_hor_offset  = u32OutOffset;
                    pstVirAddrNodeX->VPSS_OUT0_OFFSET.bits.out0_ver_offset  = 0;

                    u32CAddrOffsetNode1_5 =
                        pstVirAddrNodeX->VPSS_OUT0_STRIDE.bits.out0y_stride
                        * (pstVirAddrNodeX->VPSS_OUT0_SIZE.bits.out0_height + 1);

                    pstVirAddrNodeX->VPSS_OUT0Y_ADDR_LOW.u32 = g_VPSSMCDIBuf.u32StartSmmuAddr;
                    pstVirAddrNodeX->VPSS_OUT0C_ADDR_LOW.u32 = g_VPSSMCDIBuf.u32StartSmmuAddr + u32CAddrOffsetNode1_5;

#else
                    if (! u32FirstFieldFlag)
                    {
                        pstVirAddrNodeX->VPSS_OUT0_OFFSET.bits.out0_hor_offset  = u32OutOffset;
                        pstVirAddrNodeX->VPSS_OUT0_OFFSET.bits.out0_ver_offset  = u32SrcImgHgt / 2 - (VPSS_OVERLAP_HEIGHT / 2);
                    }
#endif
                }

                pstVirAddrNodeX->VPSS_STT_W_ADDR_LOW.u32 = pstVirAddrBase->VPSS_STT_W_ADDR_LOW.u32 + VPSS_WBCREG_SIZE * u32Idx;


                pstVirAddrNodeX->VPSS_TNR_ADDR.u32 = u32PhyAddrNodeX + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_TNR_CONTRL) - sizeof(HI_U32);
                pstVirAddrNodeX->VPSS_SNR_ADDR.u32 = u32PhyAddrNodeX + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DB_CTRL) - sizeof(HI_U32);
                pstVirAddrNodeX->VPSS_ZME_ADDR.u32 = u32PhyAddrNodeX + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_VHD0_HSP) - sizeof(HI_U32);
                pstVirAddrNodeX->VPSS_DEI_ADDR.u32 = u32PhyAddrNodeX + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DIECTRL) - sizeof(HI_U32);
            }
            else //5.6.7.8
            {
                pstVirAddrNodeX->VPSS_P1_CTRL.bits.p1_en = 0;
                pstVirAddrNodeX->VPSS_P2_CTRL.bits.p2_en = 0;
                pstVirAddrNodeX->VPSS_P3_CTRL.bits.p3_en = 0;
                pstVirAddrNodeX->VPSS_P3I_CTRL.bits.p3i_en = 0;

                pstVirAddrNodeX->VPSS_NR_RFR_CTRL.bits.nr_rfr_en = 0;
                pstVirAddrNodeX->VPSS_DI_RFR_CTRL.bits.di_rfr_en = 0;
                pstVirAddrNodeX->VPSS_RPRJH_CTRL.bits.rprjh_en = 0;
                pstVirAddrNodeX->VPSS_WPRJH_CTRL.bits.wprjh_en = 0;
                pstVirAddrNodeX->VPSS_RPRJV_CTRL.bits.rprjv_en = 0;
                pstVirAddrNodeX->VPSS_WPRJV_CTRL.bits.wprjv_en = 0;
                pstVirAddrNodeX->VPSS_P1RGMV_CTRL.bits.p1rgmv_en = 0;
                pstVirAddrNodeX->VPSS_P2RGMV_CTRL.bits.p2rgmv_en = 0;
                pstVirAddrNodeX->VPSS_CFRGMV_CTRL.bits.cfrgmv_en = 0;

                pstVirAddrNodeX->VPSS_P1RGMV_CTRL.bits.p1rgmv_en1 = 0;

                pstVirAddrNodeX->VPSS_P2RGMV_CTRL.bits.p2rgmv_en1 = 0;


                pstVirAddrNodeX->VPSS_P2MV_CTRL.bits.p2mv_en = 0;
                pstVirAddrNodeX->VPSS_P3MV_CTRL.bits.p3mv_en = 0;
                pstVirAddrNodeX->VPSS_CFMV_CTRL.bits.cfmv_en = 0;
                pstVirAddrNodeX->VPSS_P3MT_CTRL.bits.p3mt_en = 0;
                pstVirAddrNodeX->VPSS_P2MT_CTRL.bits.p2mt_en = 0;
                pstVirAddrNodeX->VPSS_DI_RST_CNT_CTRL.bits.di_rst_cnt_en = 0;
                pstVirAddrNodeX->VPSS_DI_WST_CNT_CTRL.bits.di_wst_cnt_en = 0;
                pstVirAddrNodeX->VPSS_DI_RST_CTRL.bits.di_rst_en = 0;
                pstVirAddrNodeX->VPSS_DI_WST_CTRL.bits.di_wst_en = 0;
                pstVirAddrNodeX->VPSS_NR_WMAD_CTRL.bits.nr_wmad_en = 0;
                pstVirAddrNodeX->VPSS_NR_RMAD_CTRL.bits.nr_rmad_en  = 1;

                pstVirAddrNodeX->VPSS_CTRL.u32 = 0;
                pstVirAddrNodeX->VPSS_CTRL.bits.snr_en = 1;
                pstVirAddrNodeX->VPSS_CTRL.bits.mad_vfir_en = 1;
                pstVirAddrNodeX->VPSS_CTRL.bits.vhd0_en = 1;
#if 1
                pstVirAddrNodeX->VPSS_DB_CTRL.bits.dm_en = 1;
#endif
                pstVirAddrNodeX->VPSS_CF_CTRL.bits.cf_lm_rmode = 1; // frame
                pstVirAddrNodeX->VPSS_CF_CTRL.bits.cf_type = 0; //linear

                if (u32Idx == 5)
                {
                    u32AddrOffsetOutY = HI_ALIGN_8BIT_YSTRIDE((u32SrcImgWth * u32CurPixWth + 7) / 8) * (u32SrcImgHgt / 2); //pstVirAddrNodeX->VPSS_REFSTRIDE.bits.refy_stride * u32SrcImgHgtReal*2;  //回写是间插的
                    u32AddrOffsetOutC = HI_ALIGN_8BIT_YSTRIDE((u32SrcImgWth * u32CurPixWth + 7) / 8) * (u32SrcImgHgtC / 2); //pstVirAddrNodeX->VPSS_REFSTRIDE.bits.refc_stride * u32ImgChmHgt*2;
                    u32CurOffset = 0;
                    u32OutOffset = 0;
                    u32AddrOffsetMad = 0;
                }


                if (u32Idx > 5)
                {
                    u32CurOffset = 9 * VPSS_RGMV_WTH * 2 + 6 * VPSS_RGMV_WTH * 2 * (u32Idx - 6) - VPSS_RGMV_WTH * 2;
                }
                pstVirAddrNodeX->VPSS_CF_OFFSET.bits.cf_hor_offset  = u32CurOffset; //pstVirAddrNodeX->VPSS_REFSTRIDE.bits.refy_stride * u32SrcImgHgtReal*2;  //回写是间插的

                pstVirAddrNodeX->VPSS_CF_STRIDE.bits.cfy_stride =
                    pstVirAddrNodeX->VPSS_OUT0_STRIDE.bits.out0y_stride;
                pstVirAddrNodeX->VPSS_CF_STRIDE.bits.cfc_stride =
                    pstVirAddrNodeX->VPSS_OUT0_STRIDE.bits.out0c_stride;

#ifdef VPSS_OUT_TMPBUF
                pstVirAddrNodeX->VPSS_CF_OFFSET.bits.cf_ver_offset  = 0;
                pstVirAddrNodeX->VPSS_CFY_ADDR_LOW.u32 =  g_VPSSMCDIBuf.u32StartSmmuAddr;
                pstVirAddrNodeX->VPSS_CFC_ADDR_LOW.u32 =  g_VPSSMCDIBuf.u32StartSmmuAddr +
                        (  pstVirAddrNodeX->VPSS_OUT0_STRIDE.bits.out0y_stride * (pstVirAddrNodeX->VPSS_OUT0_SIZE.bits.out0_height +
                                1 + VPSS_OVERLAP_HEIGHT) / 2);
#else
                pstVirAddrNodeX->VPSS_CF_OFFSET.bits.cf_ver_offset  = (u32SrcImgHgt - VPSS_OVERLAP_HEIGHT) / 2; //pstVirAddrNodeX->VPSS_REFSTRIDE.bits.refy_stride * u32SrcImgHgtReal*2;  //回写是间插的

#endif
                pstVirAddrNodeX->VPSS_NR_RMAD_SIZE.bits.nr_rmad_width  = u32NodeImgWth - 1;
                pstVirAddrNodeX->VPSS_NR_RMAD_SIZE.bits.nr_rmad_height = u32SrcImgHgtReal  - 1;
                pstVirAddrNodeX->VPSS_NR_RMAD_STRIDE.bits.nr_rmad_stride = HI_ALIGN_8BIT_YSTRIDE(((((pstVirAddrNodeX->VPSS_NR_RMAD_SIZE.bits.nr_rmad_width + 1) * 5 + 7) / 8 + 15) / 16 * 16) & 0xFFFFFFF0);
                pstVirAddrNodeX->VPSS_NR_RMAD_ADDR_LOW.u32 =  pstVirAddrBase->VPSS_NR_WMAD_ADDR_LOW.u32 + u32AddrOffsetMad;

                u32AddrOffsetMad += pstVirAddrNodeX->VPSS_NR_RMAD_STRIDE.bits.nr_rmad_stride * u32SrcImgHgtReal;


                pstVirAddrNodeX->VPSS_CTRL3.bits.vhd0_crop_en = 1;
                pstVirAddrNodeX->VPSS_OUT0_SIZE.bits.out0_width  = ((u32Idx == 5) || (u32Idx == 8)) ? (u32NodeImgWth  - 1 - VPSS_RGMV_WTH * 2) : (u32NodeImgWth  - 1 - VPSS_RGMV_WTH * 2 * 2);
                pstVirAddrNodeX->VPSS_OUT0_SIZE.bits.out0_height = (u32NodeImgHgt  - 1 - VPSS_OVERLAP_HEIGHT / 2);

                pstVirAddrNodeX->VPSS_VHD0CROP_POS.bits.vhd0_crop_x = (u32Idx == 5) ? 0 : VPSS_RGMV_WTH * 2 ;
                pstVirAddrNodeX->VPSS_VHD0CROP_POS.bits.vhd0_crop_y = VPSS_OVERLAP_HEIGHT / 2;

                pstVirAddrNodeX->VPSS_VHD0CROP_SIZE.bits.vhd0_crop_width  = (((u32Idx == 5) || (u32Idx == 8)) ? (u32NodeImgWth  - 1 - VPSS_RGMV_WTH * 2) : (u32NodeImgWth  - 1 - VPSS_RGMV_WTH * 2 * 2));
                pstVirAddrNodeX->VPSS_VHD0CROP_SIZE.bits.vhd0_crop_height = (u32NodeImgHgt  - 1 - VPSS_OVERLAP_HEIGHT / 2);

                if (u32Idx > 5)
                {
                    u32OutOffset = 9 * VPSS_RGMV_WTH * 2 + 6 * VPSS_RGMV_WTH * 2 * (u32Idx - 6);
                }
                pstVirAddrNodeX->VPSS_OUT0_OFFSET.bits.out0_hor_offset  = u32OutOffset; //pstVirAddrNodeX->VPSS_REFSTRIDE.bits.refy_stride * u32SrcImgHgtReal*2;  //回写是间插的
                pstVirAddrNodeX->VPSS_OUT0_OFFSET.bits.out0_ver_offset  = u32SrcImgHgt / 2; //pstVirAddrNodeX->VPSS_REFSTRIDE.bits.refy_stride * u32SrcImgHgtReal*2;  //回写是间插的

                // pstVirAddrNodeX->VPSS_OUT0Y_ADDR_LOW.u32 = pstVirAddrNodeX->VPSS_OUT0Y_ADDR_LOW.u32  + u32AddrOffsetOutY;
                // pstVirAddrNodeX->VPSS_OUT0C_ADDR_LOW.u32 = pstVirAddrNodeX->VPSS_OUT0C_ADDR_LOW.u32  + u32AddrOffsetOutC;
#if 1
                pstVirAddrNodeX->VPSS_TNR_ADDR.u32 = u32PhyAddrNodeX + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_TNR_CONTRL) - sizeof(HI_U32);
                pstVirAddrNodeX->VPSS_SNR_ADDR.u32 = u32PhyAddrNodeX + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_DB_CTRL) - sizeof(HI_U32);
                pstVirAddrNodeX->VPSS_ZME_ADDR.u32 = u32PhyAddrNodeX + VPSS_REG_SIZE_CALC(VPSS_CTRL, VPSS_VHD0_HSP) - sizeof(HI_U32);
#endif
            }
            //ST
        }
    }

    return HI_SUCCESS;
}






