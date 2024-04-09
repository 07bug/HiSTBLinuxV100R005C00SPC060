/*
 * Copyright © 2012 Intel Corporation
 * Copyright © 2013 Vasily Khoruzhick <anarsoul@gmail.com>
 * Copyright © 2015 Collabora, Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "config.h"

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "hwc-renderer.h"
#include "shared/helpers.h"

#include <linux/input.h>

#include <string.h>

#include <linux/fb.h>
#include "hi_gfx2d_api.h"


#define CONFIG_GFX_HWC_LAYER_NUM	7
#define CONFIG_GFX_DISP_BUFF_NUM	2

struct gl_hwc_output_state {
	int	h;
	int	w;
	int	change;
	int	fb_fd;

    struct fb_var_screeninfo varinfo;

	int CurDispIndex;
	char *DispBuffer[CONFIG_GFX_DISP_BUFF_NUM];
	int CurHwcLayerIndex;
	HI_GFX2D_COMPOSE_S compose[CONFIG_GFX_HWC_LAYER_NUM];
	HI_GFX2D_SURFACE_S DstSurface;
	HI_GFX2D_RECT_S s_fb_rect;
};

struct gl_hwc_surface_state {
    /** canvase surface **/
    void *pCanvasBuffer;
	HI_GFX2D_SURFACE_S *pCanvasSurface;
};

static int
gl_hwc_get_next_fb_index(int index)
{
	int	next;

	next = index + 1;
	if(next >= CONFIG_GFX_DISP_BUFF_NUM)
	{
		next = 0;
	}

	return next;
}

static void*
gl_hwc_src_surface_create(void)
{
    HI_GFX2D_SURFACE_S *pSurface = NULL;

    pSurface = (HI_GFX2D_SURFACE_S*)malloc(sizeof(HI_GFX2D_SURFACE_S));
    if (NULL == pSurface)
	{
		return NULL;
	}

    memset(pSurface, 0x0, sizeof(HI_GFX2D_SURFACE_S));

    return pSurface;
}

static void
gl_hwc_src_surface_destory(HI_GFX2D_SURFACE_S *pSurface)
{
    if (NULL == pSurface)
    {
        return;
    }

    free(pSurface);

    return;
}

static int
gl_hwc_renderer_output_create(void **window_output,int fb_fd, int width, int height)
{
	struct gl_hwc_output_state *po;
    int	i = 0;

	struct fb_fix_screeninfo fixinfo;

	po = zalloc(sizeof *po);
	if (po == NULL)
	{
		return -1;
	}

	po->fb_fd  = fb_fd;
	po->change = 1;

	if (ioctl(fb_fd, FBIOGET_FSCREENINFO, &fixinfo) < 0)
	{
		goto ERROR_EXIT;
	}

    if (ioctl(fb_fd, FBIOGET_VSCREENINFO, &po->varinfo) < 0)
	{
		goto ERROR_EXIT;
	}

	for(i = 0; i < CONFIG_GFX_DISP_BUFF_NUM; i++)
	{
		po->DispBuffer[i] = (char*)fixinfo.smem_start + fixinfo.line_length * po->varinfo.yres * i;
	}

	memset(po->compose, 0, sizeof(HI_GFX2D_COMPOSE_S) * CONFIG_GFX_HWC_LAYER_NUM);
	po->compose[0].stInRect.s32XPos        = 0;
	po->compose[0].stInRect.s32YPos        = 0;
	po->compose[0].stInRect.u32Width       = width;
	po->compose[0].stInRect.u32Height      = height;
	po->compose[0].stOutRect               = po->compose[0].stInRect;
	po->compose[0].stOpt.stBlend.bCovBlend = 1;
	po->compose[0].stSurface.enType        = HI_GFX2D_SURFACE_TYPE_MEM;
	po->compose[0].stSurface.enFmt         = HI_GFX2D_FMT_ARGB8888;
	po->compose[0].stSurface.u32Width      = width;
	po->compose[0].stSurface.u32Height     = height;
	po->compose[0].stSurface.u32Phyaddr[0] = (unsigned long)po->DispBuffer[0];
	po->compose[0].stSurface.u32Stride[0]  = fixinfo.line_length;

    memcpy(&po->DstSurface, &po->compose[0].stSurface, sizeof(HI_GFX2D_SURFACE_S));

    po->w = width;
    po->h = height;

    po->CurDispIndex     = 0;
    po->CurHwcLayerIndex = 1;

    memset(&po->s_fb_rect, 0x0, sizeof(HI_GFX2D_RECT_S));
#if 0
    /** use frame buffer default information **/
    weston_log("\n======================================================================\n");
    weston_log("display surface\n");
    weston_log("width              = %d\n",   po->DstSurface.u32Width);
    weston_log("height             = %d\n",   po->DstSurface.u32Height);
    weston_log("stride             = %d\n",   po->DstSurface.u32Stride[0]);
    weston_log("fmt                = %d\n",   po->DstSurface.enFmt);
    weston_log("address            = 0x%x\n", po->DstSurface.u32Phyaddr[0]);
    weston_log("\n======================================================================\n");
#endif


    *window_output = (void *)po;

    if (HI_SUCCESS != HI_GFX2D_Open(HI_GFX2D_DEV_ID_0))
    {
       weston_log("initial hwc HI_GFX2D_Open failure\n");
       goto ERROR_EXIT;
    }

    return 0;

ERROR_EXIT:
    if (NULL != po)
    {
        free(po);
    }

	return -1;
}

static void
gl_hwc_renderer_output_destroy(void *window_output)
{
	struct gl_hwc_output_state *po = (struct gl_hwc_output_state *)window_output;
    if (NULL != po)
    {
	   free(po);
    }

	HI_GFX2D_Close(HI_GFX2D_DEV_ID_0);

    return;
}

static void
gl_hwc_output_surface_create(void **surface_output)
{
    struct gl_hwc_surface_state *ps = NULL;

	ps = zalloc(sizeof *ps);
	if (ps == NULL)
	{
		return;
	}

    ps->pCanvasSurface = gl_hwc_src_surface_create();
    if (NULL == ps->pCanvasSurface)
    {
        free(ps);
        return;
    }

    *surface_output = (void *)ps;

    return;
}

static void
gl_hwc_output_surface_destory(void *surface_output)
{
    struct gl_hwc_surface_state *ps = (struct gl_hwc_surface_state *)surface_output;

    if (!surface_output)
    {
       return;
    }

    gl_hwc_src_surface_destory(ps->pCanvasSurface);
    ps->pCanvasSurface = NULL;

    free(surface_output);

    return;
}

static int
gl_hwc_renderer_prepare(void *surface_output, char *buffer, int w, int h, int stride, int format)
{
    int align_stride = 0;
    struct gl_hwc_surface_state *ps = (struct gl_hwc_surface_state *)surface_output;

    if (WL_SHM_FORMAT_ARGB8888 != format && WL_SHM_FORMAT_XRGB8888 != format && WL_SHM_FORMAT_RGB565 != format)
    {
        weston_log("++++++++can not support format\n");
        return 0;
    }

    if (WL_SHM_FORMAT_RGB565 == format)
    {
        align_stride =  (w * 2 + 16 - 1) & (~(16 - 1));
        ps->pCanvasSurface->enFmt = HI_GFX2D_FMT_RGB565;
    }

    if (WL_SHM_FORMAT_ARGB8888 == format || WL_SHM_FORMAT_XRGB8888 == format)
    {
        align_stride =  (w * 4 + 16 - 1) & (~(16 - 1));
        ps->pCanvasSurface->enFmt = HI_GFX2D_FMT_ARGB8888;
    }

    if (align_stride != stride)
    {
        weston_log("++++++++can not support stride, input %d need %d\n",stride,align_stride);
        return 0;
    }

    if ((w > 4096) || (h > 2160))
    {
        weston_log("++++++++can not support input size [%d %d]\n",w,h);
        return 0;
    }

    ps->pCanvasSurface->u32Width      = w;
    ps->pCanvasSurface->u32Height     = h;
    ps->pCanvasSurface->u32Stride[0]  = stride;
    ps->pCanvasSurface->u32Phyaddr[0] = (unsigned long)buffer;

    ps->pCanvasSurface->enType = HI_GFX2D_SURFACE_TYPE_MEM;

    return 1;
}

static void
gl_hwc_renderer_attach(void *surface_output)
{
#if 0
    struct gl_hwc_surface_state *ps = (struct gl_hwc_surface_state *)surface_output;
    /**create canvase surface **/
    weston_log("\n======================================================================\n");
    weston_log("canvas surface %p\n",ps);
    weston_log("width              = %d\n",   ps->pCanvasSurface->u32Width);
    weston_log("height             = %d\n",   ps->pCanvasSurface->u32Height);
    weston_log("stride             = %d\n",   ps->pCanvasSurface->u32Stride[0]);
    weston_log("ddr                = 0x%x\n", ps->pCanvasSurface->u32Phyaddr[0]);
    weston_log("\n======================================================================\n");
#endif
    return;
}

static void
gl_hwc_renderer_flush_damage(void *surface_output)
{
    return;
}

static void
gl_hwc_add_rect(HI_GFX2D_RECT_S *dst, HI_GFX2D_RECT_S *src)
{
    if ((0 == dst->u32Height) && (0 == dst->u32Width))
	{
        *dst = *src;
		return;
 	}

    if ((0 == src->u32Height) && (0 == src->u32Width))
	{
		return;
	}

	if (dst->s32XPos > src->s32XPos)
	{
		dst->u32Width += dst->s32XPos - src->s32XPos;
		dst->s32XPos = src->s32XPos;

	}

	if (dst->s32YPos > src->s32YPos)
	{
		dst->u32Height += dst->s32YPos - src->s32YPos;
		dst->s32YPos = src->s32YPos;
	}

	if ((dst->u32Width + dst->s32XPos) < (src->u32Width + src->s32XPos))
	{
		dst->u32Width = src->u32Width + src->s32XPos - dst->s32XPos;
	}

	if ((dst->u32Height + dst->s32YPos) < (src->u32Height + src->s32YPos))
	{
		dst->u32Height = src->u32Height + src->s32YPos - dst->s32YPos;
	}
}

static void
gl_hwc_sub_surface(HI_GFX2D_SURFACE_S *surface, HI_GFX2D_RECT_S *rect, int w, void *buffer)
{
	surface->u32Phyaddr[0] = (HI_U32)(char*)(buffer + w * rect->s32YPos * 4 + rect->s32XPos * 4);
	surface->u32Width  = rect->u32Width;
	surface->u32Height = rect->u32Height;
    return;
}

static void
gl_hwc_canvas_composer_to_display(struct gl_hwc_output_state *po)
{
	int	i = 0;
	int	next_fb = 0;

	HI_GFX2D_RECT_S dst_rect;
    HI_GFX2D_RECT_S temp_rect;
	HI_GFX2D_COMPOSE_LIST_S	sList;

    memset(&dst_rect, 0x0, sizeof(HI_GFX2D_RECT_S));
    memset(&temp_rect, 0x0, sizeof(HI_GFX2D_RECT_S));
	memset(&sList, 0, sizeof(HI_GFX2D_COMPOSE_LIST_S));

	for (i = 1; i < po->CurHwcLayerIndex; i++)
	{
		gl_hwc_add_rect(&dst_rect, &po->compose[i].stOutRect);
	}

	next_fb = gl_hwc_get_next_fb_index(po->CurDispIndex);

	if (1 == po->change)
	{
		//last rect
		temp_rect = dst_rect;
		gl_hwc_add_rect(&dst_rect, &po->s_fb_rect);
		po->s_fb_rect = temp_rect;

		//use show addr
		po->compose[0].stSurface.u32Phyaddr[0] = (unsigned long)po->DispBuffer[po->CurDispIndex];
		po->change = 0;
	}
	else
	{
		//use next addr
		po->compose[0].stSurface.u32Phyaddr[0] = (unsigned long)po->DispBuffer[next_fb];
		//record rect
		gl_hwc_add_rect(&po->s_fb_rect, &dst_rect);
	}

	//x of rect must begin with 16 align, and width must 16 align
	dst_rect.u32Width += dst_rect.s32XPos - dst_rect.s32XPos / 16 * 16;
	dst_rect.s32XPos = dst_rect.s32XPos / 16 * 16;

	//because img is 16 align, width can not above img's width
	dst_rect.u32Width = (dst_rect.u32Width + 15) / 16 * 16;

	//change dst rect
	for (i = 1; i < po->CurHwcLayerIndex; i++)
	{
		po->compose[i].stOutRect.s32XPos -= dst_rect.s32XPos;
		po->compose[i].stOutRect.s32YPos -= dst_rect.s32YPos;
	}

	//first img use full
	po->compose[0].stInRect = dst_rect;
	po->compose[0].stOutRect.s32XPos   = 0;
	po->compose[0].stOutRect.s32YPos   = 0;
	po->compose[0].stOutRect.u32Width  = dst_rect.u32Width;
	po->compose[0].stOutRect.u32Height = dst_rect.u32Height;

	//build dst surface
	gl_hwc_sub_surface(&po->DstSurface, &dst_rect, po->w, po->DispBuffer[next_fb]);

	sList.pstCompose    = po->compose;
	sList.u32ComposeCnt = po->CurHwcLayerIndex;

	HI_GFX2D_ComposeSync(HI_GFX2D_DEV_ID_0, &sList, &po->DstSurface, 2000);

#if 0
    weston_log("\n======================================================================\n");
    weston_log("po->CurHwcLayerIndex = %d\n",po->CurHwcLayerIndex);
    for (i = 0; i < po->CurHwcLayerIndex; i++)
	{
        weston_log("compose %d\n",i);
        weston_log("inrect  [%d %d %d %d]\n",po->compose[i].stInRect.s32XPos,
                                             po->compose[i].stInRect.s32YPos,
                                             po->compose[i].stInRect.u32Width,
                                             po->compose[i].stInRect.u32Height);
        weston_log("outrect [%d %d %d %d]\n",po->compose[i].stInRect.s32XPos,
                                             po->compose[i].stInRect.s32YPos,
                                             po->compose[i].stInRect.u32Width,
                                             po->compose[i].stInRect.u32Height);
        weston_log("stSurface width  %d\n",  po->compose[i].stSurface.u32Width);
        weston_log("stSurface height %d\n",  po->compose[i].stSurface.u32Height);
        weston_log("stSurface stride %d\n",  po->compose[i].stSurface.u32Stride[0]);
        weston_log("stSurface ddr    0x%x\n",po->compose[i].stSurface.u32Phyaddr[0]);
        weston_log("stSurface format %d\n",  po->compose[i].stSurface.enFmt);
	}
    weston_log("======================================================================\n");
    usleep(600 * 1000);
#endif

	po->CurHwcLayerIndex = 1;
}

static void
gl_hwc_composite_hwc(HI_GFX2D_SURFACE_S *pCanvasSurface, struct gl_hwc_output_state *po, HI_GFX2D_RECT_S *pInRect, HI_GFX2D_RECT_S *pDstRect)
{
    if (po->CurHwcLayerIndex >= CONFIG_GFX_HWC_LAYER_NUM)
	{
		gl_hwc_canvas_composer_to_display(po);
	}

	if (pInRect->s32XPos + pInRect->u32Width > pCanvasSurface->u32Width)
	{
		return;
	}

	if (pInRect->s32YPos + pInRect->u32Height > pCanvasSurface->u32Height)
	{
		return;
	}

    memcpy(&po->compose[po->CurHwcLayerIndex].stSurface, pCanvasSurface, sizeof(HI_GFX2D_SURFACE_S));
    memcpy(&po->compose[po->CurHwcLayerIndex].stInRect,  pInRect,        sizeof(HI_GFX2D_RECT_S));
    memcpy(&po->compose[po->CurHwcLayerIndex].stOutRect, pDstRect,       sizeof(HI_GFX2D_RECT_S));

    po->compose[po->CurHwcLayerIndex].stOpt.stBlend.bCovBlend         = 0;
	po->compose[po->CurHwcLayerIndex].stOpt.stBlend.bPixelAlphaEnable = 1;
	po->compose[po->CurHwcLayerIndex].stOpt.stResize.bResizeEnable    = 1;

#if 0
    /**create canvase surface **/
    weston_log("\n======================================================================\n");
    weston_log("updata index %d\n",po->CurHwcLayerIndex);
    weston_log("inrect  [%d %d %d %d]\n",   pInRect->s32XPos, pInRect->s32YPos, pInRect->u32Width, pInRect->u32Height);
    weston_log("outrect [%d %d %d %d]\n",   pDstRect->s32XPos,pDstRect->s32YPos,pDstRect->u32Width,pDstRect->u32Height);
    weston_log("\n======================================================================\n");
#endif

	po->CurHwcLayerIndex++;
}

static void
gl_hwc_renderer_repaint_output(struct weston_view *ev,
                               void *window_output,
                               void *surface_output,
                               pixman_region32_t *repaint_output,
	                           pixman_region32_t *source_clip)
{
    int i;
    int box_count;
    int	next_fb = 0;
    pixman_box32_t  *pbox;
    HI_GFX2D_RECT_S sInRect, sDstRect;

    struct gl_hwc_output_state  *po_output  = (struct gl_hwc_output_state *)window_output;
    struct gl_hwc_surface_state *po_surface = (struct gl_hwc_surface_state *)surface_output;

#if 1
    sInRect.s32XPos    = 0;
    sInRect.s32YPos    = 0;
    sInRect.u32Width   = 1920;
    sInRect.u32Height  = 1080;
    sDstRect.s32XPos    = 0;
    sDstRect.s32YPos    = 0;
    sDstRect.u32Width   = 1920;
    sDstRect.u32Height  = 1080;

    gl_hwc_composite_hwc(po_surface->pCanvasSurface, po_output, &sInRect, &sDstRect);
#else

    sDstRect.s32XPos   = repaint_output->extents.x1;
    sDstRect.s32YPos   = repaint_output->extents.y1;
    sDstRect.u32Width  = repaint_output->extents.x2 - repaint_output->extents.x1;
    sDstRect.u32Height = repaint_output->extents.y2 - repaint_output->extents.y1;

    if (source_clip)
    {
       sInRect.s32XPos   = source_clip->extents.x1;
       sInRect.s32YPos   = source_clip->extents.y1;
       sInRect.u32Width  = source_clip->extents.x2 - source_clip->extents.x1;
       sInRect.u32Height = source_clip->extents.y2 - source_clip->extents.y1;

       if((sInRect.u32Width != 0) || (sInRect.u32Height != 0))
       {
           gl_hwc_composite_hwc(po_surface->pCanvasSurface, po_output, &sInRect, &sDstRect);
       }
    }
    else
    {
       pbox = pixman_region32_rectangles(repaint_output, &box_count);

       for(i = 0; i < box_count; i++)
       {
           sDstRect.s32XPos   = pbox[i].x1;
           sDstRect.s32YPos   = pbox[i].y1;
           sDstRect.u32Width  = pbox[i].x2 - pbox[i].x1;
           sDstRect.u32Height = pbox[i].y2 - pbox[i].y1;

           sInRect = sDstRect;
           sInRect.s32XPos = sInRect.s32XPos - ev->geometry.x;
           sInRect.s32YPos = sInRect.s32YPos - ev->geometry.y;

           if((sInRect.u32Width != 0) || (sInRect.u32Height != 0))
           {
               gl_hwc_composite_hwc(po_surface->pCanvasSurface, po_output, &sInRect, &sDstRect);
           }
       }
    }
#endif

    gl_hwc_canvas_composer_to_display(po_output);

    next_fb = gl_hwc_get_next_fb_index(po_output->CurDispIndex);
    po_output->varinfo.yoffset = next_fb * po_output->h;
    ioctl(po_output->fb_fd, FBIOPAN_DISPLAY, &po_output->varinfo);

    po_output->CurDispIndex = next_fb;
    po_output->change = 1;

#if 0
    weston_log("\n======================================================================\n");
    weston_log("canvas surface\n");
    weston_log("display %d\n",next_fb);
    weston_log("display height %d\n",po_output->h);
    weston_log("+++++[%d %d %d %d]\n",sDstRect.s32XPos,sDstRect.s32YPos,sDstRect.u32Width,sDstRect.u32Height);
    weston_log("+++++[%d %d %d %d]\n",sInRect.s32XPos,sInRect.s32YPos,sInRect.u32Width,sInRect.u32Height);
    weston_log("\n======================================================================\n");
#endif

    return;
}

static void
gl_hwc_renderer_surface_set_color(void *surface_output,int w, int h,
		 float red, float green, float blue, float alpha)
{
	pixman_color_t color;
    struct gl_hwc_surface_state *ps = (struct gl_hwc_surface_state *)surface_output;

	color.red   = red   * 0xffff;
	color.green = green * 0xffff;
	color.blue  = blue  * 0xffff;
	color.alpha = alpha * 0xffff;

	memset(ps->pCanvasSurface, 0x0, sizeof(HI_GFX2D_SURFACE_S));

	ps->pCanvasSurface->enType    = HI_GFX2D_SURFACE_TYPE_COLOR;
	ps->pCanvasSurface->u32Width  = w;
	ps->pCanvasSurface->u32Height = h;
	ps->pCanvasSurface->u32Color  = (((HI_U32)(alpha) & 0xff) << 24)
                                  | (((HI_U32)(red)   & 0xff) << 16)
                                  | (((HI_U32)(green) & 0xff) << 8)
                                  | (((HI_U32)(blue)  & 0xff));
#if 0
    /**fill rect color for surface **/
    weston_log("\n======================================================================\n");
    weston_log("canvas surface\n");
    weston_log("width              = %d\n",   ps->pCanvasSurface->u32Width);
    weston_log("height             = %d\n",   ps->pCanvasSurface->u32Height);
    weston_log("color              = 0x%x\n", ps->pCanvasSurface->u32Color);
    weston_log("\n======================================================================\n");
#endif

	return;
}

//HISILICON add begin
//tag, support hwc compose, hwc-renderer.c revise from pixman-renderer.c and gl-renderer.c
WL_EXPORT struct gl_hwc_renderer_interface gl_hwc_renderer_interface = {
	.output_window_create     = gl_hwc_renderer_output_create,
	.output_window_destroy    = gl_hwc_renderer_output_destroy,
    .output_surface_create    = gl_hwc_output_surface_create,
    .output_surface_destory   = gl_hwc_output_surface_destory,
    .prepare                  = gl_hwc_renderer_prepare,
	.attach                   = gl_hwc_renderer_attach,
	.flush_damage             = gl_hwc_renderer_flush_damage,
	.repaint_output           = gl_hwc_renderer_repaint_output,
	.surface_set_color        = gl_hwc_renderer_surface_set_color,
#if 0
	.read_pixels              = hwc_renderer_read_pixels,
	.destroy                  = hwc_renderer_destroy,
	.surface_get_content_size = hwc_renderer_surface_get_content_size,
	.surface_copy_content     = hwc_renderer_surface_copy_content
#endif
};
//HISILICON add end
