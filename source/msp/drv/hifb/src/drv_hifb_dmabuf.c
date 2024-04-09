/*************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
**************************************************************************************************
File Name       : drv_hifb_dmabuf.c
Version         : Initial Draft
Author          :
Created         : 2018/01/01
Description     :
Function List   :


History         :
Date                      Author                  Modification
2018/01/01                 sdk                    Created file
**************************************************************************************************/
#ifdef CONFIG_DMA_SHARED_BUFFER

/*********************************add include here************************************************/
#include <linux/version.h>
#include <linux/dma-buf.h>
#include <linux/highmem.h>
#include <linux/memblock.h>
#include <linux/slab.h>
#include "hi_gfx_comm_k.h"
#include "drv_hifb_mem.h"
#include "drv_hifb_paracheck.h"

/***************************** Macro Definition **************************************************/

/*************************** Structure Definition ************************************************/
struct hifb_memblock_pdata{
    phys_addr_t phys_base;
    unsigned long size;
    struct device *dev;
    enum dma_data_direction direction;
    struct sg_table *pfbtable;
};

/********************** Global Variable declaration **********************************************/

/******************************* API declaration *************************************************/
static struct sg_table *hifb_memblock_map(struct dma_buf_attachment *attach, enum dma_data_direction direction)
{
    struct hifb_memblock_pdata *pfbdata = NULL;
    unsigned long pfbfn = 0;
    struct page *pfbage = NULL;
    struct sg_table *pfbtable = NULL;
    int s32Ret = 0;

    HIFB_CHECK_NULLPOINTER_RETURN(attach, NULL);
    HIFB_CHECK_NULLPOINTER_RETURN(attach->dmabuf, NULL);
    HIFB_CHECK_NULLPOINTER_RETURN(attach->dmabuf->priv, NULL);

    pfbdata = attach->dmabuf->priv;
    pfbfn   = PFN_DOWN(pfbdata->phys_base);
    pfbage  = pfn_to_page(pfbfn);
    HIFB_CHECK_NULLPOINTER_RETURN(pfbage, NULL);

    if (pfbdata->pfbtable != NULL)
    {
        if ((pfbdata->dev == attach->dev) && (pfbdata->direction == direction))
        {
            /* it has been map before, return directly */
            return pfbdata->pfbtable;
        }
        else
        {
            /* need to remap, so free the reserved map pointer */
            dma_unmap_sg(pfbdata->dev, pfbdata->pfbtable->sgl, 1, pfbdata->direction);
            sg_free_table(pfbdata->pfbtable);
            HI_GFX_KFREE(HIGFX_FB_ID,pfbdata->pfbtable);
            pfbdata->pfbtable = NULL;
        }
    }

    pfbtable = HI_GFX_KZALLOC(HIGFX_FB_ID,sizeof(*pfbtable), GFP_KERNEL);
    if (!pfbtable)
    {
        HIFB_ERROR("===func : %s line : %d error\n",__FUNCTION__,__LINE__);
        return ERR_PTR(-ENOMEM);
    }

    s32Ret = sg_alloc_table(pfbtable, 1, GFP_KERNEL);
    if (s32Ret < 0)
    {
        goto err;
    }

    (HI_VOID)sg_set_page(pfbtable->sgl, pfbage, attach->dmabuf->size, 0);
    (HI_VOID)dma_map_sg(attach->dev, pfbtable->sgl, 1, direction);

    /* save the map condition and table pointer */
    pfbdata->pfbtable = pfbtable;
    pfbdata->dev = attach->dev;
    pfbdata->direction = direction;

    return pfbtable;

err:
    HI_GFX_KFREE(HIGFX_FB_ID,pfbtable);
    return ERR_PTR(s32Ret);
}

static void hifb_memblock_unmap(struct dma_buf_attachment *attach, struct sg_table *pfbtable, enum dma_data_direction direction)
{
    HI_UNUSED(attach);
    HI_UNUSED(direction);
    HI_UNUSED(pfbtable);
    /* it will be unmap in release function */
    return ;
}

static void __init_memblock hifb_memblock_release(struct dma_buf *buf)
{
    struct hifb_memblock_pdata *pfbdata = NULL;

    HIFB_CHECK_NULLPOINTER_UNRETURN(buf);
    pfbdata = buf->priv;
    HIFB_CHECK_NULLPOINTER_UNRETURN(pfbdata);

    /* unmap the memory if mapped before */
    if (pfbdata->pfbtable != NULL)
    {
        dma_unmap_sg(pfbdata->dev, pfbdata->pfbtable->sgl, 1, pfbdata->direction);
        sg_free_table(pfbdata->pfbtable);
        HI_GFX_KFREE(HIGFX_FB_ID,pfbdata->pfbtable);
        pfbdata->pfbtable = NULL;
    }

    HI_GFX_KFREE(HIGFX_FB_ID,pfbdata);

    buf->priv = NULL;

    return;
}

static void *hifb_memblock_do_kmap(struct dma_buf *buf, unsigned long pgoffset,bool atomic)
{
    struct hifb_memblock_pdata *pfbdata = NULL;
    unsigned long pfbfn = 0;
    struct page *pfbage = NULL;

    HIFB_CHECK_NULLPOINTER_RETURN(buf, NULL);

    HIFB_CHECK_NULLPOINTER_RETURN(buf->priv, NULL);
    pfbdata = buf->priv;
    HIFB_CHECK_ARRAY_OVER_RETURN(pgoffset, pfbdata->size, NULL);

    pfbfn = PFN_DOWN(pfbdata->phys_base) + pgoffset;
    pfbage = pfn_to_page(pfbfn);
    HIFB_CHECK_NULLPOINTER_RETURN(pfbage, NULL);

    if (atomic)
    {
        return kmap_atomic(pfbage);
    }

    return kmap(pfbage);
}

static void *hifb_memblock_kmap_atomic(struct dma_buf *buf,unsigned long pgoffset)
{
    return hifb_memblock_do_kmap(buf, pgoffset, true);
}

static void hifb_memblock_kunmap_atomic(struct dma_buf *buf,unsigned long pgoffset, void *vaddr)
{
    HI_UNUSED(buf);
    HI_UNUSED(pgoffset);
    HIFB_CHECK_NULLPOINTER_UNRETURN(vaddr);
    kunmap_atomic(vaddr);
}

static void *hifb_memblock_kmap(struct dma_buf *buf, unsigned long pgoffset)
{
    return hifb_memblock_do_kmap(buf, pgoffset, false);
}

static void hifb_memblock_kunmap(struct dma_buf *buf, unsigned long pgoffset,void *vaddr)
{
    HI_UNUSED(buf);
    HI_UNUSED(pgoffset);
    HIFB_CHECK_NULLPOINTER_UNRETURN(vaddr);
    kunmap(vaddr);
}

static inline int hifb_valid_mmap_phys_addr_range(unsigned long pfn, size_t size)
{
    return (pfn + (size >> PAGE_SHIFT)) <= (1 + (PHYS_MASK >> PAGE_SHIFT));
}

static int hifb_memblock_mmap(struct dma_buf *buf, struct vm_area_struct *vma)
{
    HI_U32 Size = 0;
    struct hifb_memblock_pdata *pfbdata = NULL;

    HIFB_CHECK_NULLPOINTER_RETURN(buf, HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(vma, HI_FAILURE);

    pfbdata = buf->priv;
    HIFB_CHECK_NULLPOINTER_RETURN(pfbdata, HI_FAILURE);

    if (0 == pfbdata->phys_base)
    {
        return -1;
    }

    Size = vma->vm_end - vma->vm_start;
    if ((0 == Size) || (Size > pfbdata->size))
    {
        return -1;
    }

    if (!hifb_valid_mmap_phys_addr_range(vma->vm_pgoff,Size))
    {
        return -1;
    }

    vma->vm_page_prot =  pgprot_writecombine(vma->vm_page_prot);

    return remap_pfn_range(vma, vma->vm_start, PFN_DOWN(pfbdata->phys_base) + vma->vm_pgoff, Size, vma->vm_page_prot);
}


struct dma_buf_ops hifb_memblock_ops = {
    .map_dma_buf     = hifb_memblock_map,
    .unmap_dma_buf   = hifb_memblock_unmap,
    .release         = hifb_memblock_release,
    .kmap_atomic     = hifb_memblock_kmap_atomic,
    .kunmap_atomic   = hifb_memblock_kunmap_atomic,
    .kmap            = hifb_memblock_kmap,
    .kunmap          = hifb_memblock_kunmap,
    .mmap            = hifb_memblock_mmap,
};

/**
 * hifb_memblock_export - export a memblock reserved area as a dma-buf
 *
 * @base: base physical address
 * @size: memblock size
 * @flags: mode flags for the dma-buf's file
 *
 * @base and @size must be page-aligned.
 *
 * Returns a dma-buf on success or ERR_PTR(-errno) on failure.
 */
struct dma_buf *hifb_memblock_export(phys_addr_t phys_base, size_t size, int flags)
{
    struct hifb_memblock_pdata *pfbdata = NULL;
    struct dma_buf *pfbbuf = NULL;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 4, 0))
    struct dma_buf_export_info stExportInfo;
#endif

    if (PAGE_ALIGN(phys_base) != phys_base || PAGE_ALIGN(size) != size)
    {
        HIFB_ERROR("===func : %s line : %d error\n",__FUNCTION__,__LINE__);
        return ERR_PTR(-EINVAL);
    }

    pfbdata = HI_GFX_KZALLOC(HIGFX_FB_ID,sizeof(struct hifb_memblock_pdata), GFP_KERNEL);
    if (NULL == pfbdata)
    {
        HIFB_ERROR("===func : %s line : %d error\n",__FUNCTION__,__LINE__);
        return ERR_PTR(-ENOMEM);
    }

    pfbdata->phys_base = phys_base;
    pfbdata->size      = size;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 4, 0))
    stExportInfo.priv  = pfbdata;
    stExportInfo.ops   = &hifb_memblock_ops;
    stExportInfo.size  = size;
    stExportInfo.flags = flags;
    stExportInfo.resv  = NULL;
    stExportInfo.owner = NULL;
    stExportInfo.exp_name = NULL;
    pfbbuf = dma_buf_export(&stExportInfo);
#else
    pfbbuf = dma_buf_export(pfbdata, &hifb_memblock_ops, size, flags, NULL);
#endif
    if (IS_ERR(pfbbuf))
    {
        HI_GFX_KFREE(HIGFX_FB_ID,pfbdata);
    }

    return pfbbuf;
}
#endif
