/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name       : drv_hifb_proc.c
Version         : Initial Draft
Author          :
Created         : 2018/01/01
Description     :
Function List   :


History         :
Date                       Author                 Modification
2018/01/01                 sdk                    Created file
***************************************************************************************************/
#ifdef CONFIG_GFX_PROC_SUPPORT

/*********************************add include here*************************************************/
#include <linux/ctype.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/delay.h>
#include <linux/file.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/fb.h>
#include <asm/uaccess.h>
#include <asm/types.h>
#include <asm/stat.h>
#include <asm/fcntl.h>

#include "hi_drv_proc.h"
#include "drv_hifb_proc.h"
#include "drv_hifb_osr.h"
#include "drv_hifb_mem.h"
#include "drv_hifb_config.h"
#include "drv_hifb_paracheck.h"

#ifdef CFG_HIFB_FENCE_SUPPORT
#include "drv_hifb_fence.h"
#endif

/***************************** Macro Definition ***************************************************/


/*************************** Structure Definition *************************************************/


/********************** Global Variable declaration ***********************************************/
static const HI_CHAR* s_pszFmtName[] ={
                                        "RGB565",
                                        "RGB888",
                                        "KRGB444",
                                        "KRGB555",
                                        "KRGB888",
                                        "ARGB4444",
                                        "ARGB1555",
                                        "ARGB8888",
                                        "ARGB8565",
                                        "RGBA4444",
                                        "RGBA5551",
                                        "RGBA5658",
                                        "RGBA8888",
                                        "BGR565",
                                        "BGR888",
                                        "ABGR4444",
                                        "ABGR1555",
                                        "ABGR8888",
                                        "ABGR8565",
                                        "KBGR444",
                                        "KBGR555",
                                        "KBGR888",
                                        "1BPP",
                                        "2BPP",
                                        "4BPP",
                                        "8BPP",
                                        "ACLUT44",
                                        "ACLUT88",
                                        "PUYVY",
                                        "PYUYV",
                                        "PYVYU",
                                        "YUV888",
                                        "AYUV8888",
                                        "YUVA8888",
                                        "BUTT"
                                    };

const static HI_CHAR* gs_LayerName[] ={
                                            "layer_hd_0",
                                            "layer_hd_1",
                                            "layer_hd_2",
                                            "layer_hd_3",
                                            "layer_sd_0",
                                            "layer_sd_1",
                                            "layer_sd_2",
                                            "layer_sd_3",
                                            "layer_ad_0",
                                            "layer_ad_1",
                                            "layer_ad_2",
                                            "layer_ad_3",
                                            "layer_cursor"
                                      };

#ifdef CFG_HIFB_FENCE_SUPPORT
   extern HIFB_SYNC_INFO_S gs_SyncInfo;
#endif

/******************************* API declaration **************************************************/
extern HI_VOID HI_UNF_HIFB_CaptureImgFromLayer(HI_U32 u32LayerID, HI_CHAR* InputFmt);

static HI_VOID HIFB_CreateProc(HI_U32 LayerID);
static HI_VOID HIFB_DestoryProc(HI_U32 LayerID);

static HI_S32 DRV_HIFB_PrintProc(struct seq_file *p, HI_VOID *v);
static HI_S32 DRV_HIFB_WriteProc(struct file * file,const char __user * buf, size_t count, loff_t *ppos);
static HI_VOID HIFB_ParseProcEchoCmd(HI_U32 u32LayerId, HI_CHAR *pCmd);
static HI_VOID HIFB_PROC_SetRegister(HI_U32 LayerId, HI_CHAR *pCmd);

static HI_VOID HIFB_PrintHDProc(struct fb_info * info, struct seq_file *p, HI_VOID *v);
static inline HI_VOID HIFB_PROC_OpenLayer(HIFB_PAR_S *pstPar);
static inline HI_VOID HIFB_PROC_CloseLayer(HIFB_PAR_S *pstPar);

/******************************* API relese *******************************************************/
HI_S32 DRV_HIFB_CreateProc(HI_U32 LayerID)
{
    struct fb_info *info = NULL;
    HIFB_PAR_S *par = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(LayerID, HI_FAILURE);
    info = s_stLayer[LayerID].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    par  = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_RETURN(par, HI_FAILURE);

    HIFB_CreateProc(LayerID);

    return HI_SUCCESS;
}

static HI_VOID HIFB_CreateProc(HI_U32 LayerID)
{
    GFX_PROC_ITEM_S item;
    HI_CHAR entry_name[256] = {'\0'};
    struct fb_info *info = NULL;
    HIFB_PAR_S *par = NULL;

    if ((HI_FALSE == CONFIG_HIFB_SD0_COMPRESSION_SUPPORT) && (LayerID >= HIFB_LAYER_SD_0))
    {
       return;
    }

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(LayerID);
    info = s_stLayer[LayerID].pstInfo;
    HIFB_CHECK_NULLPOINTER_UNRETURN(info);

    par  = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_UNRETURN(par);
    if (HI_TRUE == par->stProcInfo.bCreateProc)
    {
       return;
    }

    snprintf(entry_name, sizeof(entry_name), "hifb%d", LayerID);
    entry_name[sizeof(entry_name) - 1] = '\0';

    item.fnRead   = DRV_HIFB_PrintProc;
    item.fnWrite  = DRV_HIFB_WriteProc;
    item.fnIoctl  = HI_NULL;

    HI_GFX_PROC_AddModule(entry_name, &item, (HI_VOID*)s_stLayer[LayerID].pstInfo);

    par->stProcInfo.bCreateProc = HI_TRUE;

    return;
}

HI_VOID DRV_HIFB_DestoryProc(HI_U32 LayerID)
{
   HI_U32 WbcLayerID = 0;
   struct fb_info *info = NULL;
   HIFB_PAR_S *par = NULL;

   HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(LayerID);
   info = s_stLayer[LayerID].pstInfo;
   HIFB_CHECK_NULLPOINTER_UNRETURN(info);

   par = (HIFB_PAR_S *)(info->par);
   HIFB_CHECK_NULLPOINTER_UNRETURN(par);

   HIFB_DestoryProc(LayerID);

   WbcLayerID = par->stProcInfo.WbcLayerID;

   HIFB_DestoryProc(WbcLayerID);

   return;
}

static HI_VOID HIFB_DestoryProc(HI_U32 LayerID)
{
    HIFB_PAR_S *par = NULL;
    struct fb_info *info = NULL;
    HI_CHAR entry_name[256] = {'\0'};

    if ((HI_FALSE == CONFIG_HIFB_SD0_COMPRESSION_SUPPORT) && (LayerID >= HIFB_LAYER_SD_0))
    {
      return;
    }

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(LayerID);
    info = s_stLayer[LayerID].pstInfo;
    HIFB_CHECK_NULLPOINTER_UNRETURN(info);

    par  = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_UNRETURN(par);
    if (HI_FALSE == par->stProcInfo.bCreateProc)
    {
        return;
    }

    snprintf(entry_name, sizeof(entry_name), "hifb%d", LayerID);
    entry_name[sizeof(entry_name) - 1] = '\0';

    HI_GFX_PROC_RemoveModule(entry_name);

    par->stProcInfo.bCreateProc = HI_FALSE;

    return;
}

static HI_S32 DRV_HIFB_WriteProc(struct file * file,const char __user * buf, size_t count, loff_t *ppos)
{
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar   = NULL;
    HI_CHAR buffer[256]  = {'\0'};
    struct seq_file *seq  = NULL;
    DRV_PROC_ITEM_S *item = NULL;

    HIFB_CHECK_NULLPOINTER_RETURN(file, 0);

    seq  = file->private_data;
    HIFB_CHECK_NULLPOINTER_RETURN(seq, 0);

    item = seq->private;
    HIFB_CHECK_NULLPOINTER_RETURN(item, 0);

    info = (struct fb_info *)(item->data);
    HIFB_CHECK_NULLPOINTER_RETURN(info, 0);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, 0);

    if (count >= sizeof(buffer))
    {
        HIFB_ERROR("The command string is out of buf space :%d bytes !\n", sizeof(buffer));
        return 0;
    }

    HIFB_CHECK_NULLPOINTER_RETURN(buf, 0);
    if (copy_from_user(buffer, buf, count))
    {
        HIFB_ERROR("failed to call copy_from_user !\n");
        return 0;
    }
    buffer[sizeof(buffer) - 1] = '\0';

    HIFB_ParseProcEchoCmd(pstPar->stBaseInfo.u32LayerID, (HI_CHAR*)buffer);

    return count;
}

static HI_VOID HIFB_ParseProcEchoCmd(HI_U32 u32LayerId, HI_CHAR *pCmd)
{
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;
    HI_S32 OpenDevCnt  = 0;

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(u32LayerId);
    info = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_UNRETURN(info);

    pstPar  = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);
    OpenDevCnt  = atomic_read(&(pstPar->stBaseInfo.ref_count));

    if ((0 == OpenDevCnt) && (pstPar->stBaseInfo.u32LayerID <= HIFB_LAYER_HD_3))
    {
        HIFB_INFO("err:device no open!\n");
        return;
    }

    if (HI_FALSE == pstPar->stProcInfo.bCreateProc)
    {
        HIFB_INFO("the hifb proc is not been created!\n");
        return;
    }

    HIFB_CHECK_NULLPOINTER_UNRETURN(pCmd);
    if (strncmp("help", pCmd, 4) == 0)
    {
        HI_DRV_PROC_EchoHelper("===============================================================\n");
        HI_DRV_PROC_EchoHelper("### help info:\n");
        HI_DRV_PROC_EchoHelper("### ***********************************************************\n");
        HI_DRV_PROC_EchoHelper("### cat /proc/msp/hifb*\n");
        HI_DRV_PROC_EchoHelper("### echo cmd > /proc/msp/hifb*\n");
        HI_DRV_PROC_EchoHelper("### for example,if you want to hide layer 0,you can input\n");
        HI_DRV_PROC_EchoHelper("### echo hide > /proc/msp/hifb0\n");
        HI_DRV_PROC_EchoHelper("### ***********************************************************\n");
        HI_DRV_PROC_EchoHelper("### hifb proc support cmd as follows:\n");
        HI_DRV_PROC_EchoHelper("###     show      : show layer\n");
        HI_DRV_PROC_EchoHelper("###     hide      : hide layer\n");
        HI_DRV_PROC_EchoHelper("###     debug on  : it can print more message for debug\n");
        HI_DRV_PROC_EchoHelper("###     debug off : it only print message for customer\n");
        HI_DRV_PROC_EchoHelper("###     capture   : capture image from frame buffer\n");
        HI_DRV_PROC_EchoHelper("===============================================================\n");
        return;
    }

    if (strncmp("show", pCmd, 4) == 0)
    {
        HIFB_PROC_OpenLayer(pstPar);
        return;
    }

    if (strncmp("hide", pCmd, 4) == 0)
    {
        HIFB_PROC_CloseLayer(pstPar);
        return;
    }

    if (strncmp("vblank on", pCmd, 9) == 0)
    {
        return;
    }

    if (strncmp("vblank off", pCmd, 10) == 0)
    {
        return;
    }

    if (strncmp("suspend on", pCmd, 10) == 0)
    {
        pstPar->bSuspendForPowerOff = HI_TRUE;
        return;
    }

    if (strncmp("debug on", pCmd, 8) == 0)
    {
        pstPar->debug = HI_TRUE;
        HI_PRINT("set proc debug on.\n");
        return;
    }

    if (strncmp("debug off", pCmd, 9) == 0)
    {
        pstPar->debug = HI_FALSE;
        HI_PRINT("set proc debug off.\n");
        return;
    }

    if (strncmp("capture", pCmd, 7) == 0)
    {
        if (pstPar->stExtendInfo.enColFmt < HIFB_FMT_BUTT)
        {
          HI_UNF_HIFB_CaptureImgFromLayer(pstPar->stBaseInfo.u32LayerID, (HI_CHAR*)s_pszFmtName[pstPar->stExtendInfo.enColFmt]);
        }
        return;
    }

    if (strncmp("offset", pCmd, 6) == 0)
    {
       HIFB_PROC_SetRegister(pstPar->stBaseInfo.u32LayerID,pCmd);
       return;
    }

    HIFB_ERROR("you can use help cmd to show help info!\n");

    return;
}

static HI_VOID HIFB_PROC_SetRegister(HI_U32 LayerId, HI_CHAR *pCmd)
{
    HI_CHAR *pReadStr = HI_NULL;
    HI_CHAR *pWriteStr = HI_NULL;
    HI_U32 Offset = 0x0;
#ifdef CONFIG_GFX_PROC_DEBUG
    HI_U32 Value  = 0x0;
#endif

    HIFB_CHECK_NULLPOINTER_UNRETURN(pCmd);

    pReadStr = strstr(pCmd, "=");
    if (HI_NULL == pReadStr)
    {
        return;
    }

    Offset = simple_strtoul((pReadStr + 1), (char **)NULL, 0);
    if (0 != (Offset % 4))
    {
        HIFB_ERROR("Offset should align 4 bytes");
        return;
    }

    pWriteStr = strstr((pReadStr + 1), "=");
    if (HI_NULL == pWriteStr)
    {
        g_stDrvAdpCallBackFunction.HIFB_DRV_ReadRegister(Offset);
        return;
    }

#ifdef CONFIG_GFX_PROC_DEBUG
    Value = simple_strtoul((pWriteStr + 1), (char **)NULL, 0);
    g_stDrvAdpCallBackFunction.HIFB_DRV_WriteRegister(Offset,Value);
#endif

    return;
}

static inline HI_VOID HIFB_PROC_CloseLayer(HIFB_PAR_S *pstPar)
{
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);

    if (HI_TRUE == pstPar->stExtendInfo.bShow)
    {
        pstPar->stRunInfo.bModifying = HI_TRUE;
        pstPar->stExtendInfo.bShow   = HI_FALSE;
        pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_SHOW;
        pstPar->stRunInfo.bModifying = HI_FALSE;
    }

    return;
}

static inline HI_VOID HIFB_PROC_OpenLayer(HIFB_PAR_S *pstPar)
{
   HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);

   if (HI_FALSE == pstPar->stExtendInfo.bShow)
   {
       pstPar->stRunInfo.bModifying = HI_TRUE;
       pstPar->stExtendInfo.bShow   = HI_TRUE;
       pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_SHOW;
       pstPar->stRunInfo.bModifying = HI_FALSE;
   }

   return;
}

static HI_S32 DRV_HIFB_PrintProc(struct seq_file *p, HI_VOID *v)
{
    DRV_PROC_ITEM_S *item = NULL;
    struct fb_info* info = NULL;
    HIFB_PAR_S *par =  NULL;

    HIFB_CHECK_NULLPOINTER_RETURN(p, HI_FAILURE);

    item = (DRV_PROC_ITEM_S *)(p->private);
    HIFB_CHECK_NULLPOINTER_RETURN(item, HI_FAILURE);

    info = (struct fb_info *)(item->data);
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    par = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_RETURN(par, HI_FAILURE);

    if (par->stBaseInfo.u32LayerID >= sizeof(gs_LayerName)/sizeof(*gs_LayerName))
    {
        HIFB_ERROR("unknow layer: layer_%d", par->stBaseInfo.u32LayerID);
        return HI_FAILURE;
    }

    HIFB_PrintHDProc(info, p, v);

    return HI_SUCCESS;
}

static HI_VOID HIFB_PrintHDProc(struct fb_info * info, struct seq_file *p, HI_VOID *v)
{
#ifdef CFG_HIFB_FENCE_SUPPORT
    HI_S32 Index = 0;
    HI_U32 RegUpdateCnt = 0;
#endif
    HI_U32  DispBufStride = 0;
    HI_U32  DispBufSize   = 0;
    HI_U32  CmpStride     = 0;
    HI_BOOL bHDR = HI_FALSE;
    HI_BOOL bPreMult = HI_FALSE;
    HIFB_PAR_S *par = NULL;

    HIFB_RECT  stOutputRect = {0};
    HIFB_RECT  stDispRect = {0};

    HIFB_CHECK_NULLPOINTER_UNRETURN(info);
    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_UNRETURN(par);

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(par->stBaseInfo.u32LayerID);

    g_stDrvAdpCallBackFunction.HIFB_DRV_GetLayerOutRect(par->stBaseInfo.u32LayerID, &stOutputRect);

    g_stDrvAdpCallBackFunction.HIFB_DRV_GetDispSize(par->stBaseInfo.u32LayerID, &stDispRect);

    g_stDrvAdpCallBackFunction.HIFB_DRV_GetLayerPreMult(par->stBaseInfo.u32LayerID, &bPreMult);

    g_stDrvAdpCallBackFunction.HIFB_DRV_GetLayerHdr(par->stBaseInfo.u32LayerID, &bHDR);

    DispBufStride = CONIFG_HIFB_GetMaxStride(par->stExtendInfo.u32DisplayWidth,info->var.bits_per_pixel,&CmpStride,CONFIG_HIFB_STRIDE_16ALIGN);
    DispBufSize = HI_HIFB_GetMemSize(DispBufStride,par->stExtendInfo.u32DisplayHeight);

    HIFB_CHECK_ARRAY_OVER_UNRETURN(par->stExtendInfo.enColFmt, HIFB_FMT_BUTT);
    HIFB_CHECK_NULLPOINTER_UNRETURN(p);

    PROC_PRINT(p,  "************************** hd layer information *****************************\n");
    PROC_PRINT(p,  "LayerId                      \t : %s\n", gs_LayerName[par->stBaseInfo.u32LayerID]);
    PROC_PRINT(p,  "ShowState                    \t : %s\n", par->stExtendInfo.bShow ? "ON" : "OFF");
    PROC_PRINT(p,  "IsDecompress                 \t : %s\n", par->bDeCompress ? "true" : "false");
    PROC_PRINT(p,  "IsStereo                     \t : %s\n", par->st3DInfo.IsStereo ? "true" : "false");
    PROC_PRINT(p,  "HDR                          \t : %s\n", bHDR ? "yes" : "no");
    PROC_PRINT(p,  "Register Open Premul         \t : %s\n", bPreMult ? "true" : "false");

    PROC_PRINT(p,  "[xres,yres]                  \t : (%d, %d)\n", info->var.xres, info->var.yres);
    PROC_PRINT(p,  "(xoffset,yoffset)            \t : (%d, %d)\n", info->var.xoffset, info->var.yoffset);
    PROC_PRINT(p,  "[xres_virtual,yres_virtual]  \t : (%d, %d)\n", info->var.xres_virtual, info->var.yres_virtual);
    PROC_PRINT(p,  "GP0 Output                   \t : (%d, %d,  %d, %d)\n",stDispRect.x, stDispRect.y, stDispRect.w, stDispRect.h);
    PROC_PRINT(p,  "Input ColorFormat            \t : %s\n",       s_pszFmtName[par->stExtendInfo.enColFmt]);
    PROC_PRINT(p,  "Cur HD Disp Addr             \t : 0x%x\n",     par->stRunInfo.CurScreenAddr);
    PROC_PRINT(p,  "fence and reality stride     \t : [%d, %d]\n", par->stProcInfo.HwcRefreshInDispStride,info->fix.line_length);
    PROC_PRINT(p,  "One HD Buffer Size           \t : %d\n",       DispBufSize);
    PROC_PRINT(p,  "Total HD Buffer MemSize      \t : %d KB\n",    info->fix.smem_len / 1024);

    if (3 == CONFIG_HIFB_LAYER_BUFFER_MAX_NUM)
    {
       PROC_PRINT(p,  "HD 3 SMMU BUFFER ADDR       \t : [0x%lx, 0x%lx, 0x%lx]\n", (unsigned long)info->fix.smem_start,\
                                                                                  (unsigned long)info->fix.smem_start + DispBufSize,\
                                                                                  (unsigned long)info->fix.smem_start + 2 * DispBufSize);
       PROC_PRINT(p,  "HD 3 MMZ BUFFER ADDR        \t : [0x%lx, 0x%lx, 0x%lx]\n", (unsigned long)par->u32SmemStartPhy,\
                                                                                  (unsigned long)par->u32SmemStartPhy + DispBufSize,    \
                                                                                  (unsigned long)par->u32SmemStartPhy + 2 * DispBufSize);
    }
    else if (2 == CONFIG_HIFB_LAYER_BUFFER_MAX_NUM)
    {
       PROC_PRINT(p,  "HD 2 SMMU BUFFER ADDR       \t : [0x%lx, 0x%lx]\n", (unsigned long)info->fix.smem_start,\
                                                                           (unsigned long)info->fix.smem_start + DispBufSize);
       PROC_PRINT(p,  "HD 2 MMZ BUFFER ADDR        \t : [0x%lx, 0x%lx]\n", (unsigned long)par->u32SmemStartPhy,\
                                                                           (unsigned long)par->u32SmemStartPhy + DispBufSize);
    }
    else
    {
       PROC_PRINT(p,  "HD 1 SMMU BUFFER ADDR       \t : [0x%lx]\n", (unsigned long)info->fix.smem_start);
       PROC_PRINT(p,  "HD 1 MMZ BUFFER ADDR        \t : [0x%lx]\n",(unsigned long)par->u32SmemStartPhy);
    }

    /**************************************************************************/
    /**                             display fence information                **/
    /**************************************************************************/
#ifdef CFG_HIFB_FENCE_SUPPORT
    DRV_HIFB_GetRegUpdateCnt(&RegUpdateCnt,0);
#endif
    PROC_PRINT(p,  "************************** fence information *****************************\n");
    /**
     **fence 同步还是 vsync同步
     **/
    PROC_PRINT(p,  "sync type                              \t : %s\n",    par->hifb_sync ? "fence" : "vblank");
    /**
     **显示帧率
     **/
    PROC_PRINT(p,  "flip fps                               \t : %d\n",    par->stFrameInfo.FlipFps);
    /**
     **绘制帧率
     **/
    PROC_PRINT(p,  "draw fps                               \t : %d\n",    par->stFrameInfo.DrawFps);
    /**
     **是否丢帧处理
     **/
    PROC_PRINT(p,  "whether discard frame                  \t : %s\n",    (HI_TRUE == par->DiscardFrame)? "true" : "false");
    /**
     **重复帧次数
     **/
    PROC_PRINT(p,  "repeat refresh frame times             \t : %ld\n",   par->stFrameInfo.RepeatFrameCnt);
    /**
     **VO CALLBACK 期望产生中断的行数
     **/
    PROC_PRINT(p,  "vo callback expect interrupt lines     \t : %ld\n",   par->stFrameInfo.ExpectIntLineNumsForVoCallBack);
    /**
     **VO CALLBACK 实际产生中断的行数
     **/
    PROC_PRINT(p,  "vo callback actual interrupt lines     \t : %ld\n",   par->stFrameInfo.ActualIntLineNumsForVoCallBack);
    /**
     **VO CALLBACK 函数执行的时间
     **/
    PROC_PRINT(p,  "vo callback run max cost times         \t : %dms\n",  par->stFrameInfo.RunMaxTimeMs);
    /**
     **VO CALLBACK 前后进入的时间差
     **/
    PROC_PRINT(p,  "vo callback cur - pre max cost times   \t : %dms\n",  par->stFrameInfo.MaxTimeMs);

    /**
     **FRAMEEND CALLBACK 期望产生中断的行数
     **/
    PROC_PRINT(p,  "frame callback expect interrupt lines  \t : %ld\n",   par->stFrameInfo.ExpectIntLineNumsForEndCallBack);
#ifdef CFG_HIFB_FENCE_SUPPORT
    /**
     **FRAMEEND CALLBACK 实际产生中断的行数
     **/
    PROC_PRINT(p,  "frame callback actual interrupt lines  \t : %ld\n",   gs_SyncInfo.ActualIntLineNumsForEndCallBack);
    /**
     **FRAMEEND CALLBACK 函数执行的时间
     **/
    PROC_PRINT(p,  "frame callback run max cost times      \t : %dms\n",  gs_SyncInfo.RunMaxTimeMs);
    /**
     **FRAMEEND CALLBACK 前后进入的时间差
     **/
    PROC_PRINT(p,  "frame callback cur - pre max cost times\t : %dms\n",  gs_SyncInfo.MaxTimeMs);
#endif
    /**
     **VO CALLBACK硬件中断函数执行的次数，只有8bit，所以最大是255，又从0开始统计
     **/
    PROC_PRINT(p,  "vo callback hard interupt times        \t : %ld\n",   par->stFrameInfo.HardIntCntForVoCallBack);
    /**
     **VO CALLBACK软件中断上报的次数
     **/
    PROC_PRINT(p,  "run vo callback func times             \t : %ld\n",   par->stFrameInfo.VoSoftCallBackCnt);
#ifdef CFG_HIFB_FENCE_SUPPORT
    /**
     **FRAMEEND CALLBACK硬件中断上报的次数，只有8bit，所以最大是255，又从0开始统计
     **/
    PROC_PRINT(p,  "frame callback hard interupt times     \t : %ld\n",   gs_SyncInfo.HardIntCntForEndCallBack);
    /**
     **FRAMEEND CALLBACK软件中断函数执行的次数
     **/
    PROC_PRINT(p,  "run frame callback func times          \t : %ld\n",   gs_SyncInfo.EndSoftCallBackCnt);
    /**
     **调用刷新的次数
     **/
    PROC_PRINT(p,  "refresh times                          \t : %d\n",    par->FenceRefreshCount);
    /**
     **寄存器更新的次数
     **/
    PROC_PRINT(p,  "updata regiter times                   \t : %d\n",    RegUpdateCnt);
    /**
     **AR数据解压出错的次数
     **/
    PROC_PRINT(p,  "ar data decompress err times           \t : %ld\n",   par->stFrameInfo.ARDataDecompressErrCnt);
    /**
     **GB数据解压出错的次数
     **/
    PROC_PRINT(p,  "gb data decompress err times           \t : %ld\n",   par->stFrameInfo.GBDataDecompressErrCnt);
    /**
     **fence信息
     **/
    for (Index = 0; Index < HIFB_DISP_TIMELINE_NUM_MAX; Index++)
    {
       PROC_PRINT(p,  "fence information                    \t : [%d][%d][%d,%d]\n",Index,\
                                                                                    gs_SyncInfo.ReleaseFenceFd[Index],\
                                                                                    gs_SyncInfo.FenceValue[Index],    \
                                                                                    gs_SyncInfo.TimeLine[Index]);
    }
#endif

    PROC_PRINT(p,  "**************************************************************************\n");

    return;
}
#endif
