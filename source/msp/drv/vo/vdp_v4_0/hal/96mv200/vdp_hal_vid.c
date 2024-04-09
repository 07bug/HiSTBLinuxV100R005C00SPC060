#include "vdp_hal_comm.h"
#include "vdp_hal_vid.h"

#include "vdp_drv_func.h"
extern S_VDP_REGS_TYPE *pVdpReg;


HI_VOID  VDP_VID_SetPreReadEnable    (HI_U32 u32Data, HI_U32 u32Enable )
{
    U_V0_PRERD     V0_PRERD;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetPreReadEnable() Select Wrong Video Layer ID\n");
        return ;
    }


    V0_PRERD.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_PRERD.u32) + u32Data * VID_OFFSET));
#ifdef VDP_HI3798MV200
    V0_PRERD.bits.pre_rd_en = 1;
#else
    V0_PRERD.bits.pre_rd_en = u32Enable ;
#endif
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_PRERD.u32) + u32Data * VID_OFFSET), V0_PRERD.u32);

    return ;
}

HI_VOID  VDP_VID_SetUvorder(HI_U32 u32Data, HI_U32 u32bUvorder)
{
    U_V0_CTRL V0_CTRL;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetUvorder() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET));
    V0_CTRL.bits.uv_order = u32bUvorder;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET), V0_CTRL.u32);


    return ;
}

HI_VOID  VDP_VID_SetNoSecFlag    (HI_U32 u32Data, HI_U32 u32Enable )
{
    U_V0_CTRL  V0_CTRL;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetNoSecFlag() Select Wrong Video Layer ID\n");
        return ;
    }


    V0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET));
    V0_CTRL.bits.nosec_flag = u32Enable ;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET), V0_CTRL.u32);

    return ;
}

HI_VOID  VDP_VID_SetLayerEnable    (HI_U32 u32Data, HI_U32 u32bEnable )
{
    U_V0_CTRL V0_CTRL;
    //U_V0_16REGIONENL V0_16REGIONENL;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetLayerEnable() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET));
    V0_CTRL.bits.surface_en = u32bEnable ;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET), V0_CTRL.u32);


    //    V0_16REGIONENL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_16REGIONENL.u32) + u32Data * VID_OFFSET));
    //    V0_16REGIONENL.u32 = 1;
    //    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_16REGIONENL.u32) + u32Data * VID_OFFSET), V0_16REGIONENL.u32);

    return ;
}

HI_VOID VDP_VID_SetTileStride (HI_U32 u32Data, HI_U32 u32LStr, HI_U32 u32CStr)
{
    U_V0_TILE_STRIDE V0_TILE_STRIDE;

    if (u32Data != VDP_LAYER_VID0)
    {
        VDP_PRINT("Error, VDP_VID_SetTileStride() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_TILE_STRIDE.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_TILE_STRIDE.u32) + u32Data * VID_OFFSET));
    V0_TILE_STRIDE.bits.tile_stride = u32LStr;
    V0_TILE_STRIDE.bits.tile_cstride = u32CStr;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_TILE_STRIDE.u32) + u32Data * VID_OFFSET), V0_TILE_STRIDE.u32);

    return ;
}

HI_VOID  VDP_VID_SetLayerAddr   (HI_U32 u32Data, HI_U32 u32Chan, HI_U32 u32LAddr, HI_U32 u32CAddr, HI_U32 u32LStr, HI_U32 u32CStr)
{
    U_V0_P0STRIDE V0_P0STRIDE;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetLayerAddr() Select Wrong Video Layer ID\n");
        return ;
    }

    if (u32Chan == 0)
    {
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_P0LADDR.u32) + u32Data * VID_OFFSET), u32LAddr);
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_P0CADDR.u32) + u32Data * VID_OFFSET), u32CAddr);
    }
    else if (u32Chan == 1)
    {
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_NADDR.u32) + u32Data * VID_OFFSET), u32LAddr);
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_NCADDR.u32) + u32Data * VID_OFFSET), u32CAddr);
    }
    else
    {
        VDP_PRINT("Error,VDP_VID_SetLayerAddr() Select Wrong Addr ID\n");
    }

    V0_P0STRIDE.bits.surface_stride = u32LStr;
    V0_P0STRIDE.bits.surface_cstride = u32CStr;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_P0STRIDE.u32) + u32Data * VID_OFFSET), V0_P0STRIDE.u32);

    return ;
}

HI_VOID  VDP_VID_SetHeadAddr   (HI_U32 u32Data, HI_U32 u32LHeadAddr, HI_U32 u32CHeadAddr)
{
    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetHeadAddr() Select Wrong Video Layer ID\n");
        return ;
    }

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_LHEAD_ADDR.u32) + u32Data * VID_OFFSET), u32LHeadAddr);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CHEAD_ADDR.u32) + u32Data * VID_OFFSET), u32CHeadAddr);

    return ;
}

HI_VOID  VDP_VID_SetHeadSize   (HI_U32 u32Data, HI_U32 u32HeadSize)
{
    U_V0_HEAD_SIZE V0_HEAD_SIZE;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetHeadSize() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_HEAD_SIZE.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HEAD_SIZE.u32) + u32Data * VID_OFFSET));
    V0_HEAD_SIZE.bits.head_size = u32HeadSize;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HEAD_SIZE.u32) + u32Data * VID_OFFSET), V0_HEAD_SIZE.u32);

    return ;
}

HI_VOID  VDP_VID_SetHeadStride  (HI_U32 u32Data, HI_U32 u32HeadStride)
{
    U_V0_HEAD_STRIDE       V0_HEAD_STRIDE                    ; /* 0xf38 */

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetHeadStride() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_HEAD_STRIDE.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HEAD_STRIDE.u32) + u32Data * VID_OFFSET));
    V0_HEAD_STRIDE.bits.head_stride = u32HeadStride;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HEAD_STRIDE.u32) + u32Data * VID_OFFSET), V0_HEAD_STRIDE.u32);

    return ;
}

HI_VOID  VDP_VID_SetInDataFmt       (HI_U32 u32Data, VDP_VID_IFMT_E  enDataFmt)
{
    U_V0_CTRL V0_CTRL;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetInDataFmt() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET));

#ifdef VDP_HI3798CV200
    if (u32Data == VDP_LAYER_VID3)
    {
        V0_CTRL.bits.ifmt = VDP_VID_IFMT_SP_422;
    }
    else
#endif
        V0_CTRL.bits.ifmt = enDataFmt;

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET), V0_CTRL.u32);

    return ;
}

HI_VOID  VDP_VID_SetDataWidth    (HI_U32 u32Data, HI_U32 DataWidth)
{
    U_V0_CTRL V0_CTRL;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetDataWidth() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET));
    V0_CTRL.bits.data_width = DataWidth;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET), V0_CTRL.u32);

    return ;
}

HI_VOID  VDP_VID_SetReadMode    (HI_U32 u32Data, VDP_DATA_RMODE_E enLRMode, VDP_DATA_RMODE_E enCRMode)
{
    U_V0_CTRL V0_CTRL;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetReadMode() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET));
    V0_CTRL.bits.lm_rmode = enLRMode;
    V0_CTRL.bits.chm_rmode = enCRMode;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET), V0_CTRL.u32);

    return ;
}

HI_VOID  VDP_VID_SetMuteEnable   (HI_U32 u32Data, HI_U32 bEnable)
{
    U_V0_CTRL V0_CTRL;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_LayerMuteEnable() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET));
    V0_CTRL.bits.mute_en = bEnable;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET), V0_CTRL.u32);

    return ;
}

HI_VOID  VDP_VID_SetInReso      (HI_U32 u32Data, VDP_RECT_S  stRect)
{
    U_V0_IRESO V0_IRESO;

#if VID_CROP_EN
    U_V0_CPOS  V0_CPOS;
#endif

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetInReso() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_IRESO.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_IRESO.u32) + u32Data * VID_OFFSET));
    V0_IRESO.bits.iw = stRect.u32Wth - 1;
    V0_IRESO.bits.ih = stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_IRESO.u32) + u32Data * VID_OFFSET), V0_IRESO.u32);

#if VID_CROP_EN
    V0_CPOS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_CPOS.u32) + u32Data * VID_OFFSET));
    V0_CPOS.bits.src_xfpos = 0;
    V0_CPOS.bits.src_xlpos = stRect.u32Wth - 1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CPOS.u32) + u32Data * VID_OFFSET), V0_CPOS.u32);
#endif

    return ;
}

HI_VOID  VDP_VID_SetOutReso     (HI_U32 u32Data, VDP_RECT_S  stRect)
{
    U_V0_ORESO V0_ORESO;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetOutReso() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_ORESO.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_ORESO.u32) + u32Data * VID_OFFSET));
    V0_ORESO.bits.ow = stRect.u32Wth - 1;
    V0_ORESO.bits.oh = stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_ORESO.u32) + u32Data * VID_OFFSET), V0_ORESO.u32);

    return ;
}

HI_VOID  VDP_VID_SetVideoPos     (HI_U32 u32Data, VDP_RECT_S  stRect)
{
    U_V0_VFPOS V0_VFPOS;
    U_V0_VLPOS V0_VLPOS;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetVideoPos() Select Wrong Video Layer ID\n");
        return ;
    }

    /*video position */
    V0_VFPOS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VFPOS.u32) + u32Data * VID_OFFSET));
    V0_VFPOS.bits.video_xfpos = stRect.u32X;
    V0_VFPOS.bits.video_yfpos = stRect.u32Y;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VFPOS.u32) + u32Data * VID_OFFSET), V0_VFPOS.u32);

    V0_VLPOS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VLPOS.u32) + u32Data * VID_OFFSET));
    V0_VLPOS.bits.video_xlpos = stRect.u32X + stRect.u32Wth - 1;
    V0_VLPOS.bits.video_ylpos = stRect.u32Y + stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VLPOS.u32) + u32Data * VID_OFFSET), V0_VLPOS.u32);
    return ;
}

HI_VOID  VDP_VID_SetDispPos     (HI_U32 u32Data, VDP_RECT_S  stRect)
{
    U_V0_DFPOS V0_DFPOS;
    U_V0_DLPOS V0_DLPOS;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetDispPos() Select Wrong Video Layer ID\n");
        return ;
    }

    /*video position */
    V0_DFPOS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_DFPOS.u32) + u32Data * VID_OFFSET));
    V0_DFPOS.bits.disp_xfpos = stRect.u32X;
    V0_DFPOS.bits.disp_yfpos = stRect.u32Y;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_DFPOS.u32) + u32Data * VID_OFFSET), V0_DFPOS.u32);

    V0_DLPOS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_DLPOS.u32) + u32Data * VID_OFFSET));
    V0_DLPOS.bits.disp_xlpos = stRect.u32X + stRect.u32Wth - 1;
    V0_DLPOS.bits.disp_ylpos = stRect.u32Y + stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_DLPOS.u32) + u32Data * VID_OFFSET), V0_DLPOS.u32);
    return ;
}

HI_VOID VDP_VID_SetSrOutReso (HI_U32 u32Data, VDP_RECT_S stRect)
{
    U_V0_SRORESO  V0_SRORESO;

    if (u32Data >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetSrOutReso() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_SRORESO.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_SRORESO.u32) + u32Data * VID_OFFSET));
    V0_SRORESO.bits.ow = stRect.u32Wth - 1;
    V0_SRORESO.bits.oh = stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_SRORESO.u32) + u32Data * VID_OFFSET), V0_SRORESO.u32);
}

//#if DCMP_EN
HI_VOID  VDP_VID_SetTileDcmpEnable    (HI_U32 u32Data, HI_U32 u32bEnable )
{
    U_V0_CTRL V0_CTRL;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetTileDcmpEnable() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET));
    V0_CTRL.bits.dcmp_en = u32bEnable ;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET), V0_CTRL.u32);


    return ;
}

HI_VOID VDP_VID_SetIfirMode(HI_U32 u32Data, VDP_IFIRMODE_E enMode)
{
    U_V0_CTRL V0_CTRL;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_SetIfirMode() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET));
    V0_CTRL.bits.ifir_mode = enMode;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET), V0_CTRL.u32);

    return ;
}

HI_VOID  VDP_VID_SetIfirCoef    (HI_U32 u32Data, HI_S32 *s32Coef)
{
    U_V0_IFIRCOEF01 V0_IFIRCOEF01;
    U_V0_IFIRCOEF23 V0_IFIRCOEF23;
    U_V0_IFIRCOEF45 V0_IFIRCOEF45;
    U_V0_IFIRCOEF67 V0_IFIRCOEF67;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetIfirCoef() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_IFIRCOEF01.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_IFIRCOEF01.u32) + u32Data * VID_OFFSET));
    V0_IFIRCOEF23.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_IFIRCOEF23.u32) + u32Data * VID_OFFSET));
    V0_IFIRCOEF45.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_IFIRCOEF45.u32) + u32Data * VID_OFFSET));
    V0_IFIRCOEF67.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_IFIRCOEF67.u32) + u32Data * VID_OFFSET));

    V0_IFIRCOEF01.bits.coef0 = s32Coef[0];
    V0_IFIRCOEF01.bits.coef1 = s32Coef[1];
    V0_IFIRCOEF23.bits.coef2 = s32Coef[2];
    V0_IFIRCOEF23.bits.coef3 = s32Coef[3];
    V0_IFIRCOEF45.bits.coef4 = s32Coef[4];
    V0_IFIRCOEF45.bits.coef5 = s32Coef[5];
    V0_IFIRCOEF67.bits.coef6 = s32Coef[6];
    V0_IFIRCOEF67.bits.coef7 = s32Coef[7];

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_IFIRCOEF01.u32) + u32Data * VID_OFFSET), V0_IFIRCOEF01.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_IFIRCOEF23.u32) + u32Data * VID_OFFSET), V0_IFIRCOEF23.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_IFIRCOEF45.u32) + u32Data * VID_OFFSET), V0_IFIRCOEF45.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_IFIRCOEF67.u32) + u32Data * VID_OFFSET), V0_IFIRCOEF67.u32);

    return ;
}

HI_VOID  VDP_VID_SetLayerGalpha (HI_U32 u32Data, HI_U32 u32Alpha0)
{
    U_V0_CBMPARA V0_CBMPARA;
    U_V0_ALPHA V0_ALPHA;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error, VDP_VID_SetLayerGalpha() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_CBMPARA.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_CBMPARA.u32) + u32Data * VID_OFFSET));
    V0_CBMPARA.bits.galpha = u32Alpha0;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CBMPARA.u32) + u32Data * VID_OFFSET), V0_CBMPARA.u32);

    V0_ALPHA.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_ALPHA.u32) + u32Data * VID_OFFSET));
    V0_ALPHA.bits.vbk_alpha = u32Alpha0;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_ALPHA.u32) + u32Data * VID_OFFSET), V0_ALPHA.u32);
    return ;
}

HI_VOID  VDP_VID_SetCropReso    (HI_U32 u32Data, VDP_RECT_S stRect)
{
#if VID_CROP_EN
    U_V0_CPOS V0_CPOS;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetCropReso() Select Wrong Video Layer ID\n");
        return ;
    }

    /* crop position */
    V0_CPOS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_CPOS.u32) + u32Data * VID_OFFSET));
    V0_CPOS.bits.src_xfpos = stRect.u32X;
    V0_CPOS.bits.src_xlpos = stRect.u32X + stRect.u32Wth - 1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CPOS.u32) + u32Data * VID_OFFSET), V0_CPOS.u32);

    return ;
#endif
}

HI_VOID  VDP_VID_SetLayerBkg    (HI_U32 u32Data, VDP_BKG_S stBkg)
{
    U_V0_BK    V0_BK;
    U_V0_ALPHA V0_ALPHA;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetLayerBkg() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_BK.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_BK.u32) + u32Data * VID_OFFSET));
    V0_BK.bits.vbk_y  = stBkg.u32BkgY;
    V0_BK.bits.vbk_cb = stBkg.u32BkgU;
    V0_BK.bits.vbk_cr = stBkg.u32BkgV;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_BK.u32) + u32Data * VID_OFFSET), V0_BK.u32);

    V0_ALPHA.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_ALPHA.u32) + u32Data * VID_OFFSET));
    V0_ALPHA.bits.vbk_alpha = stBkg.u32BkgA;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_ALPHA.u32) + u32Data * VID_OFFSET), V0_ALPHA.u32);

    return;
}

HI_VOID  VDP_VID_SetCscDcCoef   (HI_U32 u32Data, VDP_CSC_DC_COEF_S pstCscCoef)
{
    U_V0_CSC_IDC  V0_CSC_IDC;
    U_V0_CSC_ODC  V0_CSC_ODC;
    U_V0_CSC_IODC V0_CSC_IODC;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetCscDcCoef() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_CSC_IDC.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_CSC_IDC.u32) + u32Data * VID_OFFSET));
    V0_CSC_IDC.bits.cscidc1  = pstCscCoef.csc_in_dc1;
    V0_CSC_IDC.bits.cscidc0  = pstCscCoef.csc_in_dc0;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CSC_IDC.u32) + u32Data * VID_OFFSET), V0_CSC_IDC.u32);

    V0_CSC_ODC.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_CSC_ODC.u32) + u32Data * VID_OFFSET));
    V0_CSC_ODC.bits.cscodc1 = pstCscCoef.csc_out_dc1;
    V0_CSC_ODC.bits.cscodc0 = pstCscCoef.csc_out_dc0;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CSC_ODC.u32) + u32Data * VID_OFFSET), V0_CSC_ODC.u32);

    V0_CSC_IODC.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_CSC_IODC.u32) + u32Data * VID_OFFSET));
    V0_CSC_IODC.bits.cscodc2 = pstCscCoef.csc_out_dc2;
    V0_CSC_IODC.bits.cscidc2 = pstCscCoef.csc_in_dc2;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CSC_IODC.u32) + u32Data * VID_OFFSET), V0_CSC_IODC.u32);

    return ;
}

HI_VOID   VDP_VID_SetCscCoef(HI_U32 u32Data, VDP_CSC_COEF_S stCscCoef)
{
    U_V0_CSC_P0 V0_CSC_P0;
    U_V0_CSC_P1 V0_CSC_P1;
    U_V0_CSC_P2 V0_CSC_P2;
    U_V0_CSC_P3 V0_CSC_P3;
    U_V0_CSC_P4 V0_CSC_P4;
    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetCscCoef Select Wrong video ID\n");
        return ;
    }


    V0_CSC_P0.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_CSC_P0.u32) + u32Data * VID_OFFSET));
    V0_CSC_P0.bits.cscp00 = stCscCoef.csc_coef00;
    V0_CSC_P0.bits.cscp01 = stCscCoef.csc_coef01;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CSC_P0.u32) + u32Data * VID_OFFSET), V0_CSC_P0.u32);

    V0_CSC_P1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_CSC_P1.u32) + u32Data * VID_OFFSET));
    V0_CSC_P1.bits.cscp02 = stCscCoef.csc_coef02;
    V0_CSC_P1.bits.cscp10 = stCscCoef.csc_coef10;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CSC_P1.u32) + u32Data * VID_OFFSET), V0_CSC_P1.u32);

    V0_CSC_P2.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_CSC_P2.u32) + u32Data * VID_OFFSET));
    V0_CSC_P2.bits.cscp11 = stCscCoef.csc_coef11;
    V0_CSC_P2.bits.cscp12 = stCscCoef.csc_coef12;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CSC_P2.u32) + u32Data * VID_OFFSET), V0_CSC_P2.u32);

    V0_CSC_P3.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_CSC_P3.u32) + u32Data * VID_OFFSET));
    V0_CSC_P3.bits.cscp20 = stCscCoef.csc_coef20;
    V0_CSC_P3.bits.cscp21 = stCscCoef.csc_coef21;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CSC_P3.u32) + u32Data * VID_OFFSET), V0_CSC_P3.u32);

    V0_CSC_P4.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_CSC_P4.u32) + u32Data * VID_OFFSET));
    V0_CSC_P4.bits.cscp22 = stCscCoef.csc_coef22;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CSC_P4.u32) + u32Data * VID_OFFSET), V0_CSC_P4.u32);

}

HI_VOID  VDP_VID_SetCscEnable   (HI_U32 u32Data, HI_U32 u32bCscEn)
{
    U_V0_CSC_IDC V0_CSC_IDC;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetCscEnable() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_CSC_IDC.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_CSC_IDC.u32) + u32Data * VID_OFFSET));
    V0_CSC_IDC.bits.csc_en = u32bCscEn;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CSC_IDC.u32) + u32Data * VID_OFFSET), V0_CSC_IDC.u32);

    return ;
}

HI_VOID VDP_VID_SetDrawMode (HI_U32 u32Data, HI_U32 u32ModeLuma, HI_U32 u32ModeChroma)
{
#if VID_DRAW_EN
    U_V0_DRAWMODE V0_DRAWMODE;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetDrawMode() Select Wrong Video Layer ID\n");
        return ;
    }


    V0_DRAWMODE.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_DRAWMODE.u32) + u32Data * VID_OFFSET));
    V0_DRAWMODE.bits.draw_mode   = u32ModeLuma;
    V0_DRAWMODE.bits.draw_mode_c = u32ModeChroma;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_DRAWMODE.u32) + u32Data * VID_OFFSET), V0_DRAWMODE.u32);

    return ;
#endif
}

HI_VOID VDP_VID_SetDrawPixelMode (HI_U32 u32Data, HI_U32 u32DrawPixelMode)
{
    U_V0_DRAWMODE V0_DRAWMODE;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetDrawMode() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_DRAWMODE.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_DRAWMODE.u32) + u32Data * VID_OFFSET));
    V0_DRAWMODE.bits.draw_pixel_mode   = u32DrawPixelMode;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_DRAWMODE.u32) + u32Data * VID_OFFSET), V0_DRAWMODE.u32);

    return ;
}

HI_VOID VDP_VID_SetMultiModeEnable(HI_U32 u32Data, HI_U32 u32Enable )
{
    U_V0_MULTI_MODE      V0_MULTI_MODE;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetMultiModeEnable() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_MULTI_MODE.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_MULTI_MODE.u32) + u32Data * VID_OFFSET));
    V0_MULTI_MODE.bits.mrg_mode = u32Enable;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_MULTI_MODE.u32) + u32Data * VID_OFFSET), V0_MULTI_MODE.u32);

    return ;
}

HI_VOID VDP_VID_SetRegionEnable(HI_U32 u32Data, HI_U32 u32Num, HI_U32 u32bEnable )
{
    U_V0_16REGIONENL V0_16REGIONENL;
    U_V0_P0CTRL      V0_P0CTRL;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetRegionEnable() Select Wrong Video Layer ID\n");
        return ;
    }

    if (u32Num >= VID_REGION_NUM)
    {
        VDP_PRINT("Error,VDP_VID_SetRegionEnable() Select Wrong region ID\n");
        return ;
    }

    V0_16REGIONENL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_16REGIONENL.u32) + u32Data * VID_OFFSET));
    if (u32bEnable)
    {
        V0_16REGIONENL.u32 = (1 << u32Num) | V0_16REGIONENL.u32;
    }
    else
    {
        V0_16REGIONENL.u32 = (~(1 << u32Num)) & V0_16REGIONENL.u32;
    }

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_16REGIONENL.u32) + u32Data * VID_OFFSET), V0_16REGIONENL.u32);


    V0_P0CTRL.u32   =   VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_P0CTRL.u32) + u32Data * VID_OFFSET + u32Num * REGION_OFFSET));
    V0_P0CTRL.bits.region_en    =   u32bEnable;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_P0CTRL.u32) + u32Data * VID_OFFSET + u32Num * REGION_OFFSET), V0_P0CTRL.u32);

    return ;
}

HI_VOID VDP_VID_SetAllRegionDisable(HI_U32 u32Data )
{
    HI_U32           u32Num;
    U_V0_P0CTRL      V0_P0CTRL;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetAllRegionDisable() Select Wrong Video Layer ID\n");
        return ;
    }

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_16REGIONENL.u32) + u32Data * VID_OFFSET), 0);

    for (u32Num = 0; u32Num < VID_REGION_NUM; u32Num++)
    {
        V0_P0CTRL.u32   =   VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_P0CTRL.u32) + u32Data * VID_OFFSET + u32Num * REGION_OFFSET));
        V0_P0CTRL.bits.region_en    =   HI_FALSE;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_P0CTRL.u32) + u32Data * VID_OFFSET + u32Num * REGION_OFFSET), V0_P0CTRL.u32);
    }

    return ;
}

HI_BOOL VDP_VID_CheckRegionState(HI_U32 u32Data)
{
    HI_U32           u32Num = 0, u32RegValue = 0;
    U_V0_P0CTRL      V0_P0CTRL;

    for (u32Num = 0; u32Num < VID_REGION_NUM; u32Num++)
    {
        V0_P0CTRL.u32   =   VDP_RegRead((HI_ULONG) & (pVdpReg->V0_P0CTRL.u32) + u32Data * VID_OFFSET + u32Num * REGION_OFFSET);
        u32RegValue     |= V0_P0CTRL.bits.region_en;
    }

    if (u32RegValue)
    {
        return HI_TRUE;
    }
    else
    {
        return HI_FALSE;
    }

}

HI_VOID VDP_VID_SetRegionAddr(HI_U32 u32Data, HI_U32 u32Num, HI_U32 u32LAddr, HI_U32 u32CAddr, HI_U32 u32LStr, HI_U32 u32CStr)
{
    U_V0_P0STRIDE V0_P0STRIDE;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetRegionAddr() Select Wrong Video Layer ID\n");
        return ;
    }

    if (u32Num >= VID_REGION_NUM)
    {
        VDP_PRINT("Error,VDP_VID_SetRegionAddr() Select Wrong region ID\n");
        return ;
    }

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_P0LADDR.u32) + u32Data * VID_OFFSET + u32Num * REGION_OFFSET), u32LAddr);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_P0CADDR.u32) + u32Data * VID_OFFSET + u32Num * REGION_OFFSET), u32CAddr);

    V0_P0STRIDE.bits.surface_stride = u32LStr;
    V0_P0STRIDE.bits.surface_cstride = u32CStr;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_P0STRIDE.u32) + u32Data * VID_OFFSET + u32Num * REGION_OFFSET), V0_P0STRIDE.u32);

    return ;
}

HI_VOID VDP_VID_SetRegionReso(HI_U32 u32Data, HI_U32 u32Num, VDP_RECT_S  stRect)
{
    U_V0_P0RESO          V0_P0RESO;
    U_V0_P0VFPOS         V0_P0VFPOS;
    U_V0_P0VLPOS         V0_P0VLPOS;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetRegionReso() Select Wrong Video Layer ID\n");
        return ;
    }

    if (u32Num >= VID_REGION_NUM)
    {
        VDP_PRINT("Error,VDP_VID_SetRegionReso() Select Wrong region ID\n");
        return ;
    }

    /*video position */
    V0_P0VFPOS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_P0VFPOS.u32) + u32Data * VID_OFFSET + u32Num * REGION_OFFSET));
    V0_P0VFPOS.bits.video_xfpos = stRect.u32X;
    V0_P0VFPOS.bits.video_yfpos = stRect.u32Y;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_P0VFPOS.u32) + u32Data * VID_OFFSET + u32Num * REGION_OFFSET), V0_P0VFPOS.u32);

    V0_P0VLPOS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_P0VLPOS.u32) + u32Data * VID_OFFSET + u32Num * REGION_OFFSET));
    V0_P0VLPOS.bits.video_xlpos = stRect.u32X + stRect.u32Wth - 1;
    V0_P0VLPOS.bits.video_ylpos = stRect.u32Y + stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_P0VLPOS.u32) + u32Data * VID_OFFSET + u32Num * REGION_OFFSET), V0_P0VLPOS.u32);

    V0_P0RESO.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_P0RESO.u32) + u32Data * VID_OFFSET + u32Num * REGION_OFFSET));
    V0_P0RESO.bits.w = stRect.u32Wth - 1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_P0RESO.u32) + u32Data * VID_OFFSET + u32Num * REGION_OFFSET), V0_P0RESO.u32);

    return ;
}

HI_VOID VDP_VID_SetRegionMuteEnable(HI_U32 u32Data, HI_U32 u32Num, HI_U32 bEnable)
{
    U_V0_16MUTE V0_16MUTE;
    U_V0_P0CTRL V0_P0CTRL;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetRegionMuteEnable() Select Wrong VID Layer ID\n");
        return ;
    }

    if (u32Num >= VID_REGION_NUM)
    {
        VDP_PRINT("Error,VDP_VID_SetRegionMuteEnable() Select Wrong region ID\n");
        return ;
    }

    V0_16MUTE.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_16MUTE.u32) + u32Data * VID_OFFSET));
    if (bEnable)
    {
        V0_16MUTE.u32 = (1 << u32Num) | V0_16MUTE.u32;
    }
    else
    {
        V0_16MUTE.u32 = (~(1 << u32Num)) & V0_16MUTE.u32;
    }

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_16MUTE.u32) + u32Data * VID_OFFSET), V0_16MUTE.u32);

    V0_P0CTRL.u32               =   VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_P0CTRL.u32) + u32Data * VID_OFFSET + u32Num * REGION_OFFSET));
    V0_P0CTRL.bits.mute_en      =   bEnable;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_P0CTRL.u32) + u32Data * VID_OFFSET + u32Num * REGION_OFFSET), V0_P0CTRL.u32);

    return ;
}

HI_VOID  VDP_VID_SetRegUp       (HI_U32 u32Data)
{
    U_V0_UPD V0_UPD;

    /* VHD layer register update */
    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetRegup() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_UPD.bits.regup = 0x1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_UPD.u32) + u32Data * VID_OFFSET), V0_UPD.u32);

    return ;
}

///////////////////////////////////
//ZME BEGIN
///////////////////////////////////
HI_VOID  VDP_VID_SetZmeEnable   (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable)
{
    U_V0_HSP V0_HSP;
    U_V0_VSP V0_VSP;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetZmeEnable() Select Wrong Video Layer ID\n");
        return ;
    }

    /* VHD layer zoom enable */
    if ((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
        V0_HSP.bits.hlmsc_en = u32bEnable;
        V0_HSP.bits.hlfir_en = 1;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);
    }

    if ((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
        V0_HSP.bits.hchmsc_en = u32bEnable;
        V0_HSP.bits.hchfir_en = 1;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);
    }
#if 1
    if ((enMode == VDP_ZME_MODE_NONL) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32)));
        V0_HSP.bits.non_lnr_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32)), V0_HSP.u32);
    }
#endif

    if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
        V0_VSP.bits.vlmsc_en = u32bEnable;
        V0_VSP.bits.vlfir_en = 1;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);
    }

    if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
        V0_VSP.bits.vchmsc_en = u32bEnable;
        V0_VSP.bits.vchfir_en = 1;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);
    }

#ifdef VDP_HI3798MV200T
#else
    if (u32Data == VDP_LAYER_VID1)
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
        V0_HSP.bits.hlmsc_en = 0;
        V0_HSP.bits.hlfir_en = 0;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);

        V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
        V0_HSP.bits.hchmsc_en = 0;
        V0_HSP.bits.hchfir_en = 0;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);

        V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
        V0_VSP.bits.vlmsc_en = 0;
        V0_VSP.bits.vlfir_en = 0;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);
    }
#endif

#ifdef VDP_HI3798CV200
    if (u32Data == VDP_LAYER_VID3)
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
        V0_HSP.bits.hlmsc_en = 0;
        V0_HSP.bits.hlfir_en = 0;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);

        V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
        V0_HSP.bits.hchmsc_en = 0;
        V0_HSP.bits.hchfir_en = 0;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);

        V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
        V0_VSP.bits.vlmsc_en = 0;
        V0_VSP.bits.vlfir_en = 0;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);

        V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
        V0_VSP.bits.vchmsc_en = 0;
        V0_VSP.bits.vchfir_en = 0;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);
    }
#endif

    return;
}

HI_VOID  VDP_VID_SetVtapReduce   (HI_U32 u32Data, HI_U32 u32bEnable)
{
    U_V0_VSP V0_VSP;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetVtapReduce() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
#ifdef VDP_HI3798MV200
    V0_VSP.bits.vtap_reduce = 0;
#else
    V0_VSP.bits.vtap_reduce = u32bEnable;
#endif
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);

    return ;
}

HI_VOID  VDP_VID_SetZmeShootCtrlEnable  (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable, HI_U32 u32bMode)
{
    U_V0_ZME_SHOOTCTRL_HL V0_ZME_SHOOTCTRL_HL;
    U_V0_ZME_SHOOTCTRL_HC V0_ZME_SHOOTCTRL_HC;
    U_V0_ZME_SHOOTCTRL_VL V0_ZME_SHOOTCTRL_VL;
    U_V0_ZME_SHOOTCTRL_VC V0_ZME_SHOOTCTRL_VC;


    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetZmeShootCtrlEnable() Select Wrong Video Layer ID\n");
        return ;
    }

    if (u32Data != VDP_LAYER_VID0)
    {
        VDP_PRINT("Error,VDP_VID_SetZmeShootCtrlEnable() Select Wrong Video Layer ID\n");
        return;
    }

    /* VHD layer zoom enable */
    if ((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_ZME_SHOOTCTRL_HL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_ZME_SHOOTCTRL_HL.u32) + u32Data * VID_OFFSET));
        V0_ZME_SHOOTCTRL_HL.bits.hl_shootctrl_en   = u32bEnable;
        V0_ZME_SHOOTCTRL_HL.bits.hl_shootctrl_mode = 0;
        //V0_ZME_SHOOTCTRL_HL.bits.hl_shootctrl_mode = u32bMode;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_ZME_SHOOTCTRL_HL.u32) + u32Data * VID_OFFSET), V0_ZME_SHOOTCTRL_HL.u32);
    }

    if ((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_ZME_SHOOTCTRL_HC.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_ZME_SHOOTCTRL_HC.u32) + u32Data * VID_OFFSET));
        V0_ZME_SHOOTCTRL_HC.bits.hc_shootctrl_en   = u32bEnable;
        //         V0_ZME_SHOOTCTRL_HC.bits.hc_shootctrl_mode = u32bMode;
        V0_ZME_SHOOTCTRL_HC.bits.hc_shootctrl_mode = 1;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_ZME_SHOOTCTRL_HC.u32) + u32Data * VID_OFFSET), V0_ZME_SHOOTCTRL_HC.u32);
    }

    if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_ZME_SHOOTCTRL_VL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_ZME_SHOOTCTRL_VL.u32) + u32Data * VID_OFFSET));
        V0_ZME_SHOOTCTRL_VL.bits.vl_shootctrl_en   = u32bEnable;
        V0_ZME_SHOOTCTRL_VL.bits.vl_shootctrl_mode = 0;
        //V0_ZME_SHOOTCTRL_VL.bits.vl_shootctrl_mode = u32bMode;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_ZME_SHOOTCTRL_VL.u32) + u32Data * VID_OFFSET), V0_ZME_SHOOTCTRL_VL.u32);
    }

    if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_ZME_SHOOTCTRL_VC.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_ZME_SHOOTCTRL_VC.u32) + u32Data * VID_OFFSET));
        V0_ZME_SHOOTCTRL_VC.bits.vc_shootctrl_en   = u32bEnable;
        //         V0_ZME_SHOOTCTRL_VC.bits.vc_shootctrl_mode = u32bMode;
        V0_ZME_SHOOTCTRL_VC.bits.vc_shootctrl_mode = 1;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_ZME_SHOOTCTRL_VC.u32) + u32Data * VID_OFFSET), V0_ZME_SHOOTCTRL_VC.u32);
    }

    return ;
}

HI_VOID  VDP_VID_SetZmePhase    (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_S32 s32Phase)
{
    U_V0_HLOFFSET  V0_HLOFFSET;
    U_V0_HCOFFSET  V0_HCOFFSET;
    U_V0_VOFFSET   V0_VOFFSET;
    U_V0_VBOFFSET  V0_VBOFFSET;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetZmePhase() Select Wrong Video Layer ID\n");
        return ;
    }

    /* VHD layer zoom enable */
    if ((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_HLOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HLOFFSET.u32) + u32Data * VID_OFFSET));
        V0_HLOFFSET.bits.hor_loffset = s32Phase;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HLOFFSET.u32) + u32Data * VID_OFFSET), V0_HLOFFSET.u32);
    }

    if ((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_HCOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HCOFFSET.u32) + u32Data * VID_OFFSET));
        V0_HCOFFSET.bits.hor_coffset = s32Phase;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HCOFFSET.u32) + u32Data * VID_OFFSET), V0_HCOFFSET.u32);
    }

    if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_VOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VOFFSET.u32) + u32Data * VID_OFFSET));
        V0_VOFFSET.bits.vluma_offset = s32Phase;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VOFFSET.u32) + u32Data * VID_OFFSET), V0_VOFFSET.u32);
    }

    if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_VOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VOFFSET.u32) + u32Data * VID_OFFSET));
        V0_VOFFSET.bits.vchroma_offset = s32Phase;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VOFFSET.u32) + u32Data * VID_OFFSET), V0_VOFFSET.u32);
    }

    if ((enMode == VDP_ZME_MODE_VERBL) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_VBOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VBOFFSET.u32) + u32Data * VID_OFFSET));
        V0_VBOFFSET.bits.vbluma_offset = s32Phase;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VBOFFSET.u32) + u32Data * VID_OFFSET), V0_VBOFFSET.u32);
    }

    if ((enMode == VDP_ZME_MODE_VERBC) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_VBOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VBOFFSET.u32) + u32Data * VID_OFFSET));
        V0_VBOFFSET.bits.vbchroma_offset = s32Phase;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VBOFFSET.u32) + u32Data * VID_OFFSET), V0_VBOFFSET.u32);
    }

    return ;
}

HI_VOID  VDP_VID_SetHdrElZme(HI_U32 u32Data, HI_U32 u32bEnable)
{
    U_V0_VSP V0_VSP;

    if (u32Data != VDP_LAYER_VID1)
    {
        VDP_PRINT("Error,VDP_VID_SetHdrElZme() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
    V0_VSP.bits.hdr_el_zme = u32bEnable;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);

    return ;
}


HI_VOID  VDP_VID_SetZmeFirEnable(HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable)
{
    U_V0_HSP V0_HSP;
    U_V0_VSP V0_VSP;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetZmeFirEnable() Select Wrong Video Layer ID\n");
        return ;
    }

    if ((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
        V0_HSP.bits.hlfir_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);
    }

    if ((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
        V0_HSP.bits.hchfir_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);
    }

    if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
        V0_VSP.bits.vlfir_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);
    }

    if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
        V0_VSP.bits.vchfir_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);
    }

    return ;
}

HI_VOID  VDP_VID_SetZmeMidEnable   (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable)
{
    U_V0_HSP V0_HSP;
    U_V0_VSP V0_VSP;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetZmeMidEnable() Select Wrong Video Layer ID\n");
        return ;
    }

    if (u32Data == VDP_LAYER_VID0)
    {
        /* VHD layer zoom enable */
        if ((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
            //             V0_HSP.bits.hlmid_en = u32bEnable;
            V0_HSP.bits.hlmid_en = 0;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
            //             V0_HSP.bits.hchmid_en = u32bEnable;
            V0_HSP.bits.hchmid_en = 0;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
            //             V0_VSP.bits.vlmid_en = u32bEnable;
            V0_VSP.bits.vlmid_en = 0;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
            //             V0_VSP.bits.vchmid_en = u32bEnable;
            V0_VSP.bits.vchmid_en = 0;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);
        }
    }
    else
    {
        /* VHD layer zoom enable */
        if ((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
            V0_HSP.bits.hlmid_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
            V0_HSP.bits.hchmid_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
            V0_VSP.bits.vlmid_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
            V0_VSP.bits.vchmid_en = u32bEnable;
            // cout << "V0_VSP.bits.vchmid_en = " << V0_VSP.bits.vchmid_en << endl;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);
        }
    }

    return ;
}

HI_VOID VDP_VID_SetZmeHorRatio(HI_U32 u32Data, HI_U32 u32Ratio)
{
    U_V0_HSP V0_HSP;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetZmeHorRatio() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
    V0_HSP.bits.hratio = u32Ratio;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);

    return ;
}

HI_VOID  VDP_VID_SetZmeVerRatio(HI_U32 u32Data, HI_U32 u32Ratio)
{
    U_V0_VSR V0_VSR;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetZmeVerRatio() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_VSR.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSR.u32) + u32Data * VID_OFFSET));
    V0_VSR.bits.vratio = u32Ratio;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSR.u32) + u32Data * VID_OFFSET), V0_VSR.u32);

    return ;
}

HI_VOID VDP_VID_SetZmeHfirOrder(HI_U32 u32Data, HI_U32 u32HfirOrder)
{
    U_V0_HSP V0_HSP;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetZmeHfirOrder() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
#ifdef VDP_HI3798CV200
    V0_HSP.bits.hfir_order = 1;     //u32HfirOrder;
#else
    V0_HSP.bits.hfir_order = u32HfirOrder;
#endif
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);

    return ;
}

HI_VOID VDP_VID_SetZmeCoefAddr(HI_U32 u32Data, HI_U32 u32Mode, HI_U32 u32Addr)
{
    U_V0_HLCOEFAD V0_HLCOEFAD;
    U_V0_HCCOEFAD V0_HCCOEFAD;
    U_V0_VLCOEFAD V0_VLCOEFAD;
    U_V0_VCCOEFAD V0_VCCOEFAD;

    HI_U32 ADDR_OFFSET = 0x100 ;
    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetZmeCoefAddr() Select Wrong Video Layer ID\n");
        return ;
    }

    if (u32Mode == VDP_VID_PARA_ZME_HOR)
    {
        V0_HLCOEFAD.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HLCOEFAD.u32) + u32Data * VID_OFFSET));
        V0_HLCOEFAD.bits.coef_addr = u32Addr;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HLCOEFAD.u32) + u32Data * VID_OFFSET), V0_HLCOEFAD.u32);

        V0_HCCOEFAD.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HCCOEFAD.u32) + u32Data * VID_OFFSET));
        V0_HCCOEFAD.bits.coef_addr = (u32Addr + ADDR_OFFSET) & 0xfffffff0;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HCCOEFAD.u32) + u32Data * VID_OFFSET), V0_HCCOEFAD.u32);

    }
    else if (u32Mode == VDP_VID_PARA_ZME_VER)
    {
        V0_VLCOEFAD.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VLCOEFAD.u32) + u32Data * VID_OFFSET));
        V0_VLCOEFAD.bits.coef_addr = u32Addr;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VLCOEFAD.u32) + u32Data * VID_OFFSET), V0_VLCOEFAD.u32);

        V0_VCCOEFAD.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VCCOEFAD.u32) + u32Data * VID_OFFSET));
        V0_VCCOEFAD.bits.coef_addr = (u32Addr + ADDR_OFFSET)  & 0xfffffff0;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VCCOEFAD.u32) + u32Data * VID_OFFSET), V0_VCCOEFAD.u32);


    }
    else
    {
        VDP_PRINT("Error,VDP_VID_SetZmeCoefAddr() Select a Wrong Mode!\n");
    }

    return ;
}

HI_VOID VDP_VID_SetZme2CoefAddr(HI_U32 u32Data, HI_U32 u32Mode, HI_U32 u32Addr)
{
    U_V0_ZME2_HLCOEFAD V0_ZME2_HLCOEFAD;
    U_V0_ZME2_HCCOEFAD V0_ZME2_HCCOEFAD;
    U_V0_ZME2_VLCOEFAD V0_ZME2_VLCOEFAD;
    U_V0_ZME2_VCCOEFAD V0_ZME2_VCCOEFAD;

    HI_U32 ADDR_OFFSET = 0x100 ;
    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetZmeCoefAddr() Select Wrong Video Layer ID\n");
        return ;
    }

    if (u32Mode == VDP_VID_PARA_ZME2_HOR)
    {
        V0_ZME2_HLCOEFAD.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_ZME2_HLCOEFAD.u32) + u32Data * VID_OFFSET));
        V0_ZME2_HLCOEFAD.bits.coef_addr = u32Addr;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_ZME2_HLCOEFAD.u32) + u32Data * VID_OFFSET), V0_ZME2_HLCOEFAD.u32);

        V0_ZME2_HCCOEFAD.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_ZME2_HCCOEFAD.u32) + u32Data * VID_OFFSET));
        V0_ZME2_HCCOEFAD.bits.coef_addr = (u32Addr + ADDR_OFFSET) & 0xfffffff0;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_ZME2_HCCOEFAD.u32) + u32Data * VID_OFFSET), V0_ZME2_HCCOEFAD.u32);

    }
    else if (u32Mode == VDP_VID_PARA_ZME2_VER)
    {
        V0_ZME2_VLCOEFAD.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_ZME2_VLCOEFAD.u32) + u32Data * VID_OFFSET));
        V0_ZME2_VLCOEFAD.bits.coef_addr = u32Addr;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_ZME2_VLCOEFAD.u32) + u32Data * VID_OFFSET), V0_ZME2_VLCOEFAD.u32);

        V0_ZME2_VCCOEFAD.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_ZME2_VCCOEFAD.u32) + u32Data * VID_OFFSET));
        V0_ZME2_VCCOEFAD.bits.coef_addr = (u32Addr + ADDR_OFFSET)  & 0xfffffff0;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_ZME2_VCCOEFAD.u32) + u32Data * VID_OFFSET), V0_ZME2_VCCOEFAD.u32);


    }
    else
    {
        VDP_PRINT("Error,VDP_VID_SetZmeCoefAddr() Select a Wrong Mode!\n");
    }

    return ;
}

HI_VOID  VDP_VID_SetZmeInFmt(HI_U32 u32Data, VDP_PROC_FMT_E u32Fmt)
{
    U_V0_VSP V0_VSP;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetZmeInFmt() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
    V0_VSP.bits.zme_in_fmt = u32Fmt;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);

    return ;
}

HI_VOID  VDP_VID_SetZmeOutFmt(HI_U32 u32Data, VDP_PROC_FMT_E u32Fmt)
{
    U_V0_VSP V0_VSP;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetZmeInFmt() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
    V0_VSP.bits.zme_out_fmt = u32Fmt;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);

    return ;
}

////////////////////////////////////
//ZME END
////////////////////////////////////

#if VID_ZME2_EN
///////////////////////////////////
//ZME2 BEGIN
///////////////////////////////////
HI_VOID  VDP_VID_SetZme2Enable   (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable)
{
    U_V0_HSP V0_HSP;
    U_V0_VSP V0_VSP;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetZmeEnable() Select Wrong Video Layer ID\n");
        return ;
    }

    /* VHD layer zoom enable */
    if ((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET));
        V0_HSP.bits.hlmsc_en = u32bEnable;
        V0_HSP.bits.hlfir_en = 1;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET), V0_HSP.u32);
    }

    if ((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET));
        V0_HSP.bits.hchmsc_en = u32bEnable;
        V0_HSP.bits.hchfir_en = 1;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET), V0_HSP.u32);
    }
#if 1
    if ((enMode == VDP_ZME_MODE_NONL) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32)));
        V0_HSP.bits.non_lnr_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32)), V0_HSP.u32);
    }
#endif

    if (u32Data == VDP_LAYER_VID1 || u32Data == VDP_LAYER_VID4)
    {
        if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
            V0_VSP.bits.vlmsc_en = 0;//u32bEnable;
            V0_VSP.bits.vlfir_en = 1;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
            V0_VSP.bits.vchmsc_en = u32bEnable;
            V0_VSP.bits.vchfir_en = 1;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);
        }
    }
    else
    {
        if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
            V0_VSP.bits.vlmsc_en = u32bEnable;
            V0_VSP.bits.vlfir_en = 1;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
            V0_VSP.bits.vchmsc_en = u32bEnable;
            V0_VSP.bits.vchfir_en = 1;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);
        }
    }

#ifdef HI3798CV200
    if (u32Data == VDP_LAYER_VID3)
    {

        V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
        V0_VSP.bits.vlmsc_en = 0;//u32bEnable;
        V0_VSP.bits.vlfir_en = 0;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);

        V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
        V0_VSP.bits.vchmsc_en = 0;
        V0_VSP.bits.vchfir_en = 0;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);
    }
#endif

    return;
}

HI_VOID  VDP_VID_SetZme2Phase    (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_S32 s32Phase)
{
    U_V0_HLOFFSET  V0_HLOFFSET;
    U_V0_HCOFFSET  V0_HCOFFSET;
    U_V0_VOFFSET   V0_VOFFSET;
    U_V0_VBOFFSET  V0_VBOFFSET;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetZmePhase() Select Wrong Video Layer ID\n");
        return ;
    }

    /* VHD layer zoom enable */
    if ((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_HLOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HLOFFSET.u32) + VID_ZME_OFFSET));
        V0_HLOFFSET.bits.hor_loffset = s32Phase;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HLOFFSET.u32) + VID_ZME_OFFSET), V0_HLOFFSET.u32);
    }

    if ((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_HCOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HCOFFSET.u32) + VID_ZME_OFFSET));
        V0_HCOFFSET.bits.hor_coffset = s32Phase;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HCOFFSET.u32) + VID_ZME_OFFSET), V0_HCOFFSET.u32);
    }

    //if((enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_VOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VOFFSET.u32) + VID_ZME_OFFSET));
        V0_VOFFSET.bits.vluma_offset = s32Phase;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VOFFSET.u32) + VID_ZME_OFFSET), V0_VOFFSET.u32);
    }

    //if((enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_VOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VOFFSET.u32) + VID_ZME_OFFSET));
        V0_VOFFSET.bits.vchroma_offset = s32Phase;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VOFFSET.u32) + VID_ZME_OFFSET), V0_VOFFSET.u32);
    }

    //if((enMode == VDP_ZME_MODE_VERBL)||(enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_ALL))
    if ((enMode == VDP_ZME_MODE_VERBL) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_VBOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VBOFFSET.u32) + VID_ZME_OFFSET));
        V0_VBOFFSET.bits.vbluma_offset = s32Phase;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VBOFFSET.u32) + VID_ZME_OFFSET), V0_VBOFFSET.u32);
    }

    //if((enMode == VDP_ZME_MODE_VERBC)||(enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_ALL))
    if ((enMode == VDP_ZME_MODE_VERBC) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_VBOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VBOFFSET.u32) + VID_ZME_OFFSET));
        V0_VBOFFSET.bits.vbchroma_offset = s32Phase;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VBOFFSET.u32) + VID_ZME_OFFSET), V0_VBOFFSET.u32);
    }

    return ;
}

HI_VOID  VDP_VID_SetZme2FirEnable(HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable)
{
    U_V0_HSP V0_HSP;
    U_V0_VSP V0_VSP;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetZmeFirEnable() Select Wrong Video Layer ID\n");
        return ;
    }

    if ((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET));
        V0_HSP.bits.hlfir_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET), V0_HSP.u32);
    }

    if ((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET));
        V0_HSP.bits.hchfir_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET), V0_HSP.u32);
    }

    if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
        V0_VSP.bits.vlfir_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);
    }

    if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
    {
        V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
        V0_VSP.bits.vchfir_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);
    }

    return ;
}

HI_VOID  VDP_VID_SetZme2MidEnable   (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable)
{
    U_V0_HSP V0_HSP;
    U_V0_VSP V0_VSP;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetZmeMidEnable() Select Wrong Video Layer ID\n");
        return ;
    }

    if (u32Data == VDP_LAYER_VID0)
    {
        /* VHD layer zoom enable */
        if ((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET));
            //             V0_HSP.bits.hlmid_en = u32bEnable;
            V0_HSP.bits.hlmid_en = 0;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET), V0_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET));
            //             V0_HSP.bits.hchmid_en = u32bEnable;
            V0_HSP.bits.hchmid_en = 0;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET), V0_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
            //             V0_VSP.bits.vlmid_en = u32bEnable;
            V0_VSP.bits.vlmid_en = 0;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
            //             V0_VSP.bits.vchmid_en = u32bEnable;
            V0_VSP.bits.vchmid_en = 0;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);
        }
    }
    else
    {
        /* VHD layer zoom enable */
        if ((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET));
            V0_HSP.bits.hlmid_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET), V0_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET));
            V0_HSP.bits.hchmid_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET), V0_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
            V0_VSP.bits.vlmid_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            V0_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
            V0_VSP.bits.vchmid_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);
        }
    }

    return ;
}

HI_VOID VDP_VID_SetZme2HorRatio(HI_U32 u32Data, HI_U32 u32Ratio)
{
    U_V0_HSP V0_HSP;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetZmeHorRatio() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET));
    V0_HSP.bits.hratio = u32Ratio;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET), V0_HSP.u32);

    return ;
}

HI_VOID  VDP_VID_SetZme2VerRatio(HI_U32 u32Data, HI_U32 u32Ratio)
{
    U_V0_VSR V0_VSR;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetZmeVerRatio() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_VSR.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_VSR.u32) + VID_ZME_OFFSET));
    V0_VSR.bits.vratio = u32Ratio;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_VSR.u32) + VID_ZME_OFFSET), V0_VSR.u32);

    return ;
}


////////////////////////////////////
//ZME2 END
////////////////////////////////////
#endif

HI_VOID  VDP_VID_SetParaUpd       (HI_U32 u32Data, VDP_VID_PARA_E enMode)
{
    U_V0_PARAUP V0_PARAUP;
    U_V0_DWM_SYB_PARAUP V0_DWM_SYB_PARAUP ;
    if (enMode == VDP_VID_PARA_C6)
    {
        V0_DWM_SYB_PARAUP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_DWM_SYB_PARAUP.u32) + u32Data * VID_C6_OFFSET));
    }
    else
    {
        V0_PARAUP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_PARAUP.u32) + u32Data * VID_OFFSET));
    }

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("error,VDP_VID_SetParaUpd() select wrong video layer id\n");
        return ;
    }

    if (enMode == VDP_VID_PARA_ZME_HOR)
    {
#ifdef VDP_HI3798MV200
        if (u32Data == VDP_LAYER_VID1)
        {
            V0_PARAUP.bits.v0_hlcoef_upd = 0x1;
            V0_PARAUP.bits.v0_hccoef_upd = 0x1;
        }
        else
        {
            V0_PARAUP.bits.v0_hlcoef_upd = 0x1;
            V0_PARAUP.bits.v0_hccoef_upd = 0x1;
        }
#else
        V0_PARAUP.bits.v0_hlcoef_upd = 0x1;
        V0_PARAUP.bits.v0_hccoef_upd = 0x1;
#endif

    }
    else if (enMode == VDP_VID_PARA_ZME_VER)
    {
#ifdef VDP_HI3798MV200
        if (u32Data == VDP_LAYER_VID1)
        {
            V0_PARAUP.bits.v0_vlcoef_upd = 0x1;
            V0_PARAUP.bits.v0_vccoef_upd = 0x1;
        }
        else
        {
            V0_PARAUP.bits.v0_vlcoef_upd = 0x1;
            V0_PARAUP.bits.v0_vccoef_upd = 0x1;
        }
#else
        V0_PARAUP.bits.v0_vlcoef_upd = 0x1;
        V0_PARAUP.bits.v0_vccoef_upd = 0x1;
#endif
    }
    else if (enMode == VDP_VID_PARA_DCI)
    {
        V0_PARAUP.bits.v0_dcicoef_upd = 0x1;
    }
    else if (enMode == VDP_VID_PARA_TNR)
    {
        V0_PARAUP.bits.tnr_upd = 0x1;
    }
    else if (enMode == VDP_VID_PARA_TNR_LUT)
    {
        V0_PARAUP.bits.tnr_lut_upd = 0x1;
    }
    else if (enMode == VDP_VID_PARA_SNR)
    {
        V0_PARAUP.bits.snr_upd = 0x0;
    }
    else if (enMode == VDP_VID_PARA_DBM)
    {
        V0_PARAUP.bits.dbm_upd = 0x1;
    }
    else if (enMode == VDP_VID_PARA_C6)
    {
        V0_DWM_SYB_PARAUP.bits.para_up = 0x1;
    }
    else if (enMode == VDP_VID_PARA_ZME2_HOR)
    {

        V0_PARAUP.bits.zme2_hlcoef_upd = 0x1;
        V0_PARAUP.bits.zme2_hccoef_upd = 0x1;

    }
    else if (enMode == VDP_VID_PARA_ZME2_VER)
    {
        V0_PARAUP.bits.zme2_vlcoef_upd = 0x1;
        V0_PARAUP.bits.zme2_vccoef_upd = 0x1;
    }
    else
    {
        VDP_PRINT("error,VDP_VID_SetParaUpd() select wrong mode!\n");
    }

    if (enMode == VDP_VID_PARA_C6)
    {
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_DWM_SYB_PARAUP.u32) + u32Data * VID_C6_OFFSET), V0_DWM_SYB_PARAUP.u32);
    }
    else
    {
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_PARAUP.u32) + u32Data * VID_OFFSET), V0_PARAUP.u32);
    }

    return ;
}

//------------------------------------------------------------------
//driver for VP layer
//------------------------------------------------------------------

#if VP0_EN
HI_VOID  VDP_VP_SetVideoPos     (HI_U32 u32Data, VDP_RECT_S  stRect)
{
    U_VP0_VFPOS VP0_VFPOS;
    U_VP0_VLPOS VP0_VLPOS;

    if (u32Data >= VP_MAX)
    {
        VDP_PRINT("Error,VDP_VP_SetVideoPos() Select Wrong Video Layer ID\n");
        return ;
    }

    /*video position */
    VP0_VFPOS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VP0_VFPOS.u32) + u32Data * VP_OFFSET));
    VP0_VFPOS.bits.video_xfpos = stRect.u32X;
    VP0_VFPOS.bits.video_yfpos = stRect.u32Y;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->VP0_VFPOS.u32) + u32Data * VP_OFFSET), VP0_VFPOS.u32);

    VP0_VLPOS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VP0_VLPOS.u32) + u32Data * VP_OFFSET));
    VP0_VLPOS.bits.video_xlpos = stRect.u32X + stRect.u32Wth - 1;
    VP0_VLPOS.bits.video_ylpos = stRect.u32Y + stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->VP0_VLPOS.u32) + u32Data * VP_OFFSET), VP0_VLPOS.u32);

    return ;
}

HI_VOID  VDP_VP_SetDispPos     (HI_U32 u32Data, VDP_RECT_S  stRect)
{
    U_VP0_DFPOS VP0_DFPOS;
    U_VP0_DLPOS VP0_DLPOS;

    if (u32Data >= VP_MAX)
    {
        VDP_PRINT("Error,VDP_VP_SetDispPos() Select Wrong Video Layer ID\n");
        return ;
    }

    /*video position */
    VP0_DFPOS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VP0_DFPOS.u32) + u32Data * VP_OFFSET));
    VP0_DFPOS.bits.disp_xfpos = stRect.u32X;
    VP0_DFPOS.bits.disp_yfpos = stRect.u32Y;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->VP0_DFPOS.u32) + u32Data * VP_OFFSET), VP0_DFPOS.u32);

    VP0_DLPOS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VP0_DLPOS.u32) + u32Data * VP_OFFSET));
    VP0_DLPOS.bits.disp_xlpos = stRect.u32X + stRect.u32Wth - 1;
    VP0_DLPOS.bits.disp_ylpos = stRect.u32Y + stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->VP0_DLPOS.u32) + u32Data * VP_OFFSET), VP0_DLPOS.u32);
    return ;
}

HI_VOID  VDP_VP_SetInReso      (HI_U32 u32Data, VDP_RECT_S  stRect)
{
    U_VP0_IRESO VP0_IRESO;

    if (u32Data >= VP_MAX)
    {
        VDP_PRINT("Error,VDP_VP_SetInReso() Select Wrong Video Layer ID\n");
        return ;
    }

    VP0_IRESO.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VP0_IRESO.u32) + u32Data * VP_OFFSET));
    VP0_IRESO.bits.iw = stRect.u32Wth - 1;
    VP0_IRESO.bits.ih = stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->VP0_IRESO.u32) + u32Data * VP_OFFSET), VP0_IRESO.u32);

    return ;
}

HI_VOID  VDP_VP_SetRegUp  (HI_U32 u32Data)
{
    U_VP0_UPD VP0_UPD;

    /* VP layer register update */
    if (u32Data >= VP_MAX)
    {
        VDP_PRINT("Error,VDP_VP_SetRegUp() Select Wrong VP Layer ID\n");
        return ;
    }

    VP0_UPD.bits.regup = 0x1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->VP0_UPD.u32) + u32Data * VP_OFFSET), VP0_UPD.u32);

    return ;
}

HI_VOID  VDP_VP_SetLayerGalpha (HI_U32 u32Data, HI_U32 u32Alpha)
{
    U_VP0_GALPHA VP0_GALPHA;

    //special for bk alpha = video alpha
    U_VP0_ALPHA     VP0_ALPHA;

    if (u32Data >= VP_MAX)
    {
        VDP_PRINT("Error,VDP_VP_SetLayerGalpha() Select Wrong vp Layer ID\n");
        return ;
    }


    VP0_GALPHA.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VP0_GALPHA.u32) + u32Data * VP_OFFSET));
    VP0_GALPHA.bits.galpha = u32Alpha;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->VP0_GALPHA.u32) + u32Data * VP_OFFSET), VP0_GALPHA.u32);


    VP0_ALPHA.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VP0_ALPHA.u32)));
    VP0_ALPHA.bits.vbk_alpha = u32Alpha;
    VDP_RegWrite((HI_ULONG) & (pVdpReg->VP0_ALPHA.u32), VP0_ALPHA.u32);

    return ;
}

HI_VOID VDP_VP_SetMuteEnable     (HI_U32 u32Data, HI_U32 bEnable)
{
    U_VP0_CTRL VP0_CTRL;

    if (u32Data >= VP_MAX)
    {
        VDP_PRINT("Error,VDP_VP_SetMuteEnable() Select Wrong VP Layer ID\n");
        return ;
    }

    VP0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VP0_CTRL.u32) + u32Data * VP_OFFSET));
    VP0_CTRL.bits.mute_en = bEnable;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->VP0_CTRL.u32) + u32Data * VP_OFFSET), VP0_CTRL.u32);

    return ;
}

HI_VOID  VDP_VP_SetMuteBkg(HI_U32 u32Data, VDP_VP_MUTE_BK_S stVpMuteBkg)
{
    U_VP0_MUTE_BK VP0_MUTE_BK;

    if (u32Data >= VP_MAX)
    {
        VDP_PRINT("Error,VDP_VP_SetMuteBkg() Select Wrong VP Layer ID\n");
        return ;
    }

    VP0_MUTE_BK.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VP0_MUTE_BK.u32) + u32Data * VP_OFFSET));
    VP0_MUTE_BK.bits.mute_y  = stVpMuteBkg.u32VpMuteBkgY;
    VP0_MUTE_BK.bits.mute_cb = stVpMuteBkg.u32VpMuteBkgU;
    VP0_MUTE_BK.bits.mute_cr = stVpMuteBkg.u32VpMuteBkgV;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->VP0_MUTE_BK.u32) + u32Data * VP_OFFSET), VP0_MUTE_BK.u32);

    return ;
}

HI_VOID VDP_VP_SetAcmEnable (HI_U32 u32Data, HI_U32 u32bAcmEn)
{
    U_VP0_ACM_CTRL  VP0_ACM_CTRL;

    if (u32Data >= VP_MAX)
    {
        VDP_PRINT("Error,VDP_VP_SetAcmEnable() Select Wrong CHANNEL ID\n");
        return ;
    }

    VP0_ACM_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VP0_ACM_CTRL.u32) + u32Data * VP_OFFSET));
    VP0_ACM_CTRL.bits.acm_en = u32bAcmEn;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->VP0_ACM_CTRL.u32) + u32Data * VP_OFFSET), VP0_ACM_CTRL.u32);

    return ;

}

#endif //end VP0_EN

HI_VOID VDP_VP_SetDciEnable(HI_U32 u32Data, HI_U32 u32DciEn)
{
    U_VP0_DCICTRL VP0_DCICTRL;

    if(u32Data >= VP_MAX)
    {
        VDP_PRINT("Error,VDP_VP_SetDciEnable() Select Wrong VP ID\n");
        return ;
    }

    VP0_DCICTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VP0_DCICTRL.u32)+ u32Data * VP_OFFSET));
#ifdef VDP_HI3798MV200
	VP0_DCICTRL.bits.dci_en = 0;
#else
	VP0_DCICTRL.bits.dci_en = u32DciEn;
#endif
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VP0_DCICTRL.u32)+ u32Data * VP_OFFSET), VP0_DCICTRL.u32);

}

//WCG_BEGING

HI_VOID VDP_VID_SetSrcCropReso    (HI_U32 u32Data, VDP_RECT_S stRect)
{
    U_V0_TILE_LOFFSET V0_TILE_LOFFSET;
    U_V0_TILE_COFFSET V0_TILE_COFFSET;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetSrcCropReso() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_TILE_LOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_TILE_LOFFSET.u32) + u32Data * VID_OFFSET));
    V0_TILE_LOFFSET.bits.l_x_offset = stRect.u32X;
    V0_TILE_LOFFSET.bits.l_y_offset = stRect.u32Y;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_TILE_LOFFSET.u32) + u32Data * VID_OFFSET), V0_TILE_LOFFSET.u32);

    V0_TILE_COFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_TILE_COFFSET.u32) + u32Data * VID_OFFSET));
    V0_TILE_COFFSET.bits.c_x_offset = stRect.u32X;
    V0_TILE_COFFSET.bits.c_y_offset = stRect.u32Y / 2;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_TILE_COFFSET.u32) + u32Data * VID_OFFSET), V0_TILE_COFFSET.u32);
    return ;
}

//add for testpattern cfg

//HZME
HI_VOID VDP_VID_SetHpzmeHpzmeEn(HI_U32 u32Data, HI_U32 hpzme_en)
{
    U_V0_HPZME V0_HPZME;
    //  cout << "v0 hzmeen =" << hpzme_en << endl;
    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error, VDP_VID_SetHpzmeHpzmeEn Select Wrong Layer ID\n");
    }

    V0_HPZME.u32 = VDP_RegRead( ((HI_ULONG) & (pVdpReg->V0_HPZME.u32) + u32Data * VID_OFFSET));
    V0_HPZME.bits.hpzme_en = hpzme_en;
    VDP_RegWrite( ((HI_ULONG) & (pVdpReg->V0_HPZME.u32) + u32Data * VID_OFFSET), V0_HPZME.u32);

    return ;
}

HI_VOID VDP_VID_SetHpzmeHpzmeMode(HI_U32 u32Data, HI_U32 hpzme_mode)
{
    U_V0_HPZME V0_HPZME;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error, VDP_VID_SetHpzmeHpzmeMode Select Wrong Layer ID\n");
    }

    V0_HPZME.u32 = VDP_RegRead( ((HI_ULONG) & (pVdpReg->V0_HPZME.u32) + u32Data * VID_OFFSET));
    V0_HPZME.bits.hpzme_mode = hpzme_mode;
    VDP_RegWrite( ((HI_ULONG) & (pVdpReg->V0_HPZME.u32) + u32Data * VID_OFFSET), V0_HPZME.u32);

    return ;
}


HI_VOID VDP_VID_SetHpzmeCoef2(HI_U32 u32Data, HI_U32 coef2)
{
    U_V0_HPZME_COEF V0_HPZME_COEF;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error, VDP_VID_SetHpzmeCoef2 Select Wrong Layer ID\n");
    }

    V0_HPZME_COEF.u32 = VDP_RegRead( ((HI_ULONG) & (pVdpReg->V0_HPZME_COEF.u32) + u32Data * VID_OFFSET));
    V0_HPZME_COEF.bits.coef2 = coef2;
    VDP_RegWrite( ((HI_ULONG) & (pVdpReg->V0_HPZME_COEF.u32) + u32Data * VID_OFFSET), V0_HPZME_COEF.u32);

    return ;
}


HI_VOID VDP_VID_SetHpzmeCoef1(HI_U32 u32Data, HI_U32 coef1)
{
    U_V0_HPZME_COEF V0_HPZME_COEF;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error, VDP_VID_SetHpzmeCoef1 Select Wrong Layer ID\n");
    }

    V0_HPZME_COEF.u32 = VDP_RegRead( ((HI_ULONG) & (pVdpReg->V0_HPZME_COEF.u32) + u32Data * VID_OFFSET));
    V0_HPZME_COEF.bits.coef1 = coef1;
    VDP_RegWrite( ((HI_ULONG) & (pVdpReg->V0_HPZME_COEF.u32) + u32Data * VID_OFFSET), V0_HPZME_COEF.u32);

    return ;
}


HI_VOID VDP_VID_SetHpzmeCoef0(HI_U32 u32Data, HI_U32 coef0)
{
    U_V0_HPZME_COEF V0_HPZME_COEF;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error, VDP_VID_SetHpzmeCoef0 Select Wrong Layer ID\n");
    }

    V0_HPZME_COEF.u32 = VDP_RegRead( ((HI_ULONG) & (pVdpReg->V0_HPZME_COEF.u32) + u32Data * VID_OFFSET));
    V0_HPZME_COEF.bits.coef0 = coef0;
    VDP_RegWrite( ((HI_ULONG) & (pVdpReg->V0_HPZME_COEF.u32) + u32Data * VID_OFFSET), V0_HPZME_COEF.u32);

    return ;
}

