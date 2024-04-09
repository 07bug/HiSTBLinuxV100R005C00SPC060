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
#include "hi_common.h"


#define CONFIG_GFX_HWC_LAYER_NUM	7
#define CONFIG_GFX_DISP_BUFF_NUM	2

struct hwc_output_state {
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

struct hwc_surface_state {
	struct weston_surface *surface;

    /** canvase surface **/
    void *pCanvasBuffer;
	HI_GFX2D_SURFACE_S *pCanvasSurface;

	struct weston_buffer_reference buffer_ref;

	struct wl_listener buffer_destroy_listener;
	struct wl_listener surface_destroy_listener;
	struct wl_listener renderer_destroy_listener;
};

struct hwc_renderer {
	struct weston_renderer base;

	int repaint_debug;
	pixman_image_t *debug_color;
	struct weston_binding *debug_binding;

	struct wl_signal destroy_signal;
};

static int
hwc_get_next_fb_index(int index)
{
	int	next;

	next = index + 1;
	if(next >= CONFIG_GFX_DISP_BUFF_NUM)
	{
		next = 0;
	}

	return next;
}

static inline struct hwc_output_state *
hwc_get_output_state(struct weston_output *output)
{
	return (struct hwc_output_state *)output->renderer_state;
}

static int
hwc_renderer_create_surface(struct weston_surface *surface);

static inline struct hwc_surface_state *
get_surface_state(struct weston_surface *surface)
{
	if (!surface->renderer_state)
		hwc_renderer_create_surface(surface);

	return (struct hwc_surface_state *)surface->renderer_state;
}

static inline struct hwc_renderer *
get_renderer(struct weston_compositor *ec)
{
	return (struct hwc_renderer *)ec->renderer;
}

static int
hwc_renderer_read_pixels(struct weston_output *output,
			       pixman_format_code_t format, void *pixels,
			       uint32_t x, uint32_t y,
			       uint32_t width, uint32_t height)
{
	return -1;
}

static void
region_global_to_output(struct weston_output *output, pixman_region32_t *region)
{
	if (output->zoom.active) {
		weston_matrix_transform_region(region, &output->matrix, region);
	} else {
		pixman_region32_translate(region, -output->x, -output->y);
		weston_transformed_region(output->width, output->height,
					  output->transform,
					  output->current_scale,
					  region, region);
	}
}

#define D2F(v) pixman_double_to_fixed((double)v)

static void
weston_matrix_to_pixman_transform(pixman_transform_t *pt,
				  const struct weston_matrix *wm)
{
	/* Pixman supports only 2D transform matrix, but Weston uses 3D, *
	 * so we're omitting Z coordinate here. */
	pt->matrix[0][0] = pixman_double_to_fixed(wm->d[0]);
	pt->matrix[0][1] = pixman_double_to_fixed(wm->d[4]);
	pt->matrix[0][2] = pixman_double_to_fixed(wm->d[12]);
	pt->matrix[1][0] = pixman_double_to_fixed(wm->d[1]);
	pt->matrix[1][1] = pixman_double_to_fixed(wm->d[5]);
	pt->matrix[1][2] = pixman_double_to_fixed(wm->d[13]);
	pt->matrix[2][0] = pixman_double_to_fixed(wm->d[3]);
	pt->matrix[2][1] = pixman_double_to_fixed(wm->d[7]);
	pt->matrix[2][2] = pixman_double_to_fixed(wm->d[15]);
}

static void
hwc_renderer_compute_transform(pixman_transform_t *transform_out,
				  struct weston_view *ev,
				  struct weston_output *output)
{
	struct weston_matrix matrix;

	/* Set up the source transformation based on the surface
	   position, the output position/transform/scale and the client
	   specified buffer transform/scale */
	matrix = output->inverse_matrix;

	if (ev->transform.enabled) {
		weston_matrix_multiply(&matrix, &ev->transform.inverse);
	} else {
		weston_matrix_translate(&matrix,
					-ev->geometry.x, -ev->geometry.y, 0);
	}

	weston_matrix_multiply(&matrix, &ev->surface->surface_to_buffer_matrix);

	weston_matrix_to_pixman_transform(transform_out, &matrix);
}

static bool
view_transformation_is_translation(struct weston_view *view)
{
	if (!view->transform.enabled)
		return true;

	if (view->transform.matrix.type <= WESTON_MATRIX_TRANSFORM_TRANSLATE)
		return true;

	return false;
}

static void
region_intersect_only_translation(pixman_region32_t *result_global,
				  pixman_region32_t *global,
				  pixman_region32_t *surf,
				  struct weston_view *view)
{
	float view_x, view_y;

	assert(view_transformation_is_translation(view));

	/* Convert from surface to global coordinates */
	pixman_region32_copy(result_global, surf);
	weston_view_to_global_float(view, 0, 0, &view_x, &view_y);
	pixman_region32_translate(result_global, (int)view_x, (int)view_y);

	pixman_region32_intersect(result_global, result_global, global);
}

static void
hwc_add_rect(HI_GFX2D_RECT_S *dst, HI_GFX2D_RECT_S *src)
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
hwc_sub_surface(HI_GFX2D_SURFACE_S *surface, HI_GFX2D_RECT_S *rect, int w, void *buffer)
{
	surface->u32Phyaddr[0] = (HI_U32)(char*)(buffer + w * rect->s32YPos * 4 + rect->s32XPos * 4);
	surface->u32Width  = rect->u32Width;
	surface->u32Height = rect->u32Height;
    return;
}

static void
hwc_canvas_composer_to_display(struct hwc_output_state *po)
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
		hwc_add_rect(&dst_rect, &po->compose[i].stOutRect);
	}

	next_fb = hwc_get_next_fb_index(po->CurDispIndex);

	if (1 == po->change)
	{
		//last rect
		temp_rect = dst_rect;
		hwc_add_rect(&dst_rect, &po->s_fb_rect);
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
		hwc_add_rect(&po->s_fb_rect, &dst_rect);
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
	hwc_sub_surface(&po->DstSurface, &dst_rect, po->w, po->DispBuffer[next_fb]);

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
#endif

	po->CurHwcLayerIndex = 1;
}

static void
hwc_composite_hwc(HI_GFX2D_SURFACE_S *pCanvasSurface, struct hwc_output_state *po, HI_GFX2D_RECT_S *pInRect, HI_GFX2D_RECT_S *pDstRect)
{
	if (po->CurHwcLayerIndex >= CONFIG_GFX_HWC_LAYER_NUM)
	{
		hwc_canvas_composer_to_display(po);
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

/** Paint an intersected region
 *
 * \param ev The view to be painted.
 * \param output The output being painted.
 * \param repaint_output The region to be painted in output coordinates.
 * \param source_clip The region of the source image to use, in source image
 *                    coordinates. If NULL, use the whole source image.
 * \param pixman_op Compositing operator, either SRC or OVER.
 */
static void
repaint_region(struct weston_view *ev, struct weston_output *output,
	       pixman_region32_t *repaint_output,
	       pixman_region32_t *source_clip,
	       pixman_op_t pixman_op)
{
	struct hwc_renderer *pr =
		(struct hwc_renderer *) output->compositor->renderer;
	struct hwc_surface_state *ps = get_surface_state(ev->surface);
	struct hwc_output_state *po = hwc_get_output_state(output);
	struct weston_buffer_viewport *vp = &ev->surface->buffer_viewport;
	pixman_transform_t transform;
	pixman_filter_t filter;
	HI_GFX2D_RECT_S	sInRect, sDstRect;
	pixman_color_t mask = { 0, };

	int	i;
	int	box_count;
	pixman_box32_t	*pbox;

	/* Clip rendering to the damaged output region */
	//pixman_image_set_clip_region32(po->shadow_image, repaint_output);

	hwc_renderer_compute_transform(&transform, ev, output);

	if (ev->transform.enabled || output->current_scale != vp->buffer.scale)
		filter = PIXMAN_FILTER_BILINEAR;
	else
		filter = PIXMAN_FILTER_NEAREST;

	if (ps->buffer_ref.buffer)
		wl_shm_buffer_begin_access(ps->buffer_ref.buffer->shm_buffer);

#if 0
	if (ev->alpha < 1.0) {
		mask.alpha = 0xffff * ev->alpha;
		mask_image = pixman_image_create_solid_fill(&mask);
	} else {
		mask_image = NULL;
	}

	if (source_clip)
		composite_clipped(ps->image, mask_image, po->shadow_image,
				  &transform, filter, source_clip);
	else
		composite_whole(pixman_op, ps->image, mask_image,
				po->shadow_image, &transform, filter);

	if (mask_image)
		pixman_image_unref(mask_image);
#else
    sDstRect.s32XPos = repaint_output->extents.x1;
    sDstRect.s32YPos = repaint_output->extents.y1;
    sDstRect.u32Width = repaint_output->extents.x2 - repaint_output->extents.x1;
    sDstRect.u32Height = repaint_output->extents.y2 - repaint_output->extents.y1;

    if (source_clip)
    {
      sInRect.s32XPos = source_clip->extents.x1;
      sInRect.s32YPos = source_clip->extents.y1;
      sInRect.u32Width = source_clip->extents.x2 - source_clip->extents.x1;
      sInRect.u32Height = source_clip->extents.y2 - source_clip->extents.y1;

      if((sInRect.u32Width != 0) || (sInRect.u32Height != 0))
      {
          hwc_composite_hwc(ps->pCanvasSurface, po, &sInRect, &sDstRect);
      }
    }
    else
    {
      pbox = pixman_region32_rectangles(repaint_output, &box_count);

      for(i = 0; i < box_count; i++)
      {
          sDstRect.s32XPos = pbox[i].x1;
          sDstRect.s32YPos = pbox[i].y1;
          sDstRect.u32Width = pbox[i].x2 - pbox[i].x1;
          sDstRect.u32Height = pbox[i].y2 - pbox[i].y1;

          sInRect = sDstRect;
          sInRect.s32XPos = sInRect.s32XPos - ev->geometry.x;
          sInRect.s32YPos = sInRect.s32YPos - ev->geometry.y;

          if((sInRect.u32Width != 0) || (sInRect.u32Height != 0))
          {
              hwc_composite_hwc(ps->pCanvasSurface, po, &sInRect, &sDstRect);
          }
      }
    }
#endif
	if (ps->buffer_ref.buffer)
		wl_shm_buffer_end_access(ps->buffer_ref.buffer->shm_buffer);

#if 0
	if (pr->repaint_debug)
		pixman_image_composite32(PIXMAN_OP_OVER,
					 pr->debug_color, /* src */
					 NULL /* mask */,
					 po->shadow_image, /* dest */
					 0, 0, /* src_x, src_y */
					 0, 0, /* mask_x, mask_y */
					 0, 0, /* dest_x, dest_y */
					 pixman_image_get_width (po->shadow_image), /* width */
					 pixman_image_get_height (po->shadow_image) /* height */);

	pixman_image_set_clip_region32 (po->shadow_image, NULL);
#endif
}

static void
draw_view_translated(struct weston_view *view, struct weston_output *output,
		     pixman_region32_t *repaint_global)
{
	struct weston_surface *surface = view->surface;
	/* non-opaque region in surface coordinates: */
	pixman_region32_t surface_blend;
	/* region to be painted in output coordinates: */
	pixman_region32_t repaint_output;

	pixman_region32_init(&repaint_output);

	/* Blended region is whole surface minus opaque region,
	 * unless surface alpha forces us to blend all.
	 */
	pixman_region32_init_rect(&surface_blend, 0, 0,
				  surface->width, surface->height);

	if (!(view->alpha < 1.0)) {
		pixman_region32_subtract(&surface_blend, &surface_blend,
					 &surface->opaque);

		if (pixman_region32_not_empty(&surface->opaque)) {
			region_intersect_only_translation(&repaint_output,
							  repaint_global,
							  &surface->opaque,
							  view);
			region_global_to_output(output, &repaint_output);

			repaint_region(view, output, &repaint_output, NULL,
				       PIXMAN_OP_SRC);
		}
	}

	if (pixman_region32_not_empty(&surface_blend)) {
		region_intersect_only_translation(&repaint_output,
						  repaint_global,
						  &surface_blend, view);
		region_global_to_output(output, &repaint_output);

		repaint_region(view, output, &repaint_output, NULL,
			       PIXMAN_OP_OVER);
	}

	pixman_region32_fini(&surface_blend);
	pixman_region32_fini(&repaint_output);
}

static void
draw_view_source_clipped(struct weston_view *view,
			 struct weston_output *output,
			 pixman_region32_t *repaint_global)
{
	struct weston_surface *surface = view->surface;
	pixman_region32_t surf_region;
	pixman_region32_t buffer_region;
	pixman_region32_t repaint_output;

	/* Do not bother separating the opaque region from non-opaque.
	 * Source clipping requires PIXMAN_OP_OVER in all cases, so painting
	 * opaque separately has no benefit.
	 */

	pixman_region32_init_rect(&surf_region, 0, 0,
				  surface->width, surface->height);
	if (view->geometry.scissor_enabled)
		pixman_region32_intersect(&surf_region, &surf_region,
					  &view->geometry.scissor);

	pixman_region32_init(&buffer_region);
	weston_surface_to_buffer_region(surface, &surf_region, &buffer_region);

	pixman_region32_init(&repaint_output);
	pixman_region32_copy(&repaint_output, repaint_global);
	region_global_to_output(output, &repaint_output);

	repaint_region(view, output, &repaint_output, &buffer_region,
		       PIXMAN_OP_OVER);

	pixman_region32_fini(&repaint_output);
	pixman_region32_fini(&buffer_region);
	pixman_region32_fini(&surf_region);
}

static void
draw_view(struct weston_view *ev, struct weston_output *output,
	  pixman_region32_t *damage) /* in global coordinates */
{
	struct hwc_surface_state *ps = get_surface_state(ev->surface);
	/* repaint bounding region in global coordinates: */
	pixman_region32_t repaint;

	/* No buffer attached */
	if (!ps->pCanvasSurface)
		return;

	pixman_region32_init(&repaint);
	pixman_region32_intersect(&repaint,
				  &ev->transform.boundingbox, damage);
	pixman_region32_subtract(&repaint, &repaint, &ev->clip);

	if (!pixman_region32_not_empty(&repaint))
		goto out;

	if (view_transformation_is_translation(ev)) {
		/* The simple case: The surface regions opaque, non-opaque,
		 * etc. are convertible to global coordinate space.
		 * There is no need to use a source clip region.
		 * It is possible to paint opaque region as PIXMAN_OP_SRC.
		 * Also the boundingbox is accurate rather than an
		 * approximation.
		 */
		draw_view_translated(ev, output, &repaint);
	} else {
		/* The complex case: the view transformation does not allow
		 * converting opaque etc. regions into global coordinate space.
		 * Therefore we need source clipping to avoid sampling from
		 * unwanted source image areas, unless the source image is
		 * to be used whole. Source clipping does not work with
		 * PIXMAN_OP_SRC.
		 */
		draw_view_source_clipped(ev, output, &repaint);
	}

out:
	pixman_region32_fini(&repaint);
}
static void
hwc_repaint_surfaces(struct weston_output *output, pixman_region32_t *damage)
{
	struct weston_compositor *compositor = output->compositor;
	struct weston_view *view;

	wl_list_for_each_reverse(view, &compositor->view_list, link)
		if (view->plane == &compositor->primary_plane)
			draw_view(view, output, damage);
}

static void
hwc_copy_to_hw_buffer(struct weston_output *output, pixman_region32_t *region)
{
	int	next_fb = 0;
	struct hwc_output_state *po = hwc_get_output_state(output);
	pixman_region32_t output_region;

	pixman_region32_init(&output_region);
	pixman_region32_copy(&output_region, region);

	region_global_to_output(output, &output_region);

	pixman_region32_fini(&output_region);

    hwc_canvas_composer_to_display(po);

    next_fb = hwc_get_next_fb_index(po->CurDispIndex);
    po->varinfo.yoffset = next_fb * po->h;
    ioctl(po->fb_fd, FBIOPAN_DISPLAY, &po->varinfo);

#if 0
    /**create canvase surface **/
    weston_log("\n======================================================================\n");
    weston_log("display\n");
    weston_log("CurDispIndex     = %d\n",   next_fb);
    weston_log("CurDrawIndex     = %d\n",   po->CurDispIndex);
    weston_log("display height   = %d\n",   po->h);
    weston_log("\n======================================================================\n");
#endif

    po->CurDispIndex = next_fb;
    po->change = 1;
}

static void
hwc_renderer_repaint_output(struct weston_output *output,
			     pixman_region32_t *output_damage)
{
	struct hwc_output_state *po = hwc_get_output_state(output);

	hwc_repaint_surfaces(output, output_damage);
	hwc_copy_to_hw_buffer(output, output_damage);

	pixman_region32_copy(&output->previous_damage, output_damage);
	wl_signal_emit(&output->frame_signal, output);

	/* Actual flip should be done by caller */
}

static void
hwc_renderer_flush_damage(struct weston_surface *surface)
{
	/* No-op for pixman renderer */
}


static void
hwc_src_surface_set_format(HI_GFX2D_SURFACE_S *pSurface, int shm_format)
{
    if (NULL == pSurface)
    {
        return;
    }

    if (WL_SHM_FORMAT_RGB565 == shm_format)
    {
        pSurface->enFmt = HI_GFX2D_FMT_RGB565;
    }
    else if (WL_SHM_FORMAT_ARGB8888 == shm_format)
    {
        pSurface->enFmt = HI_GFX2D_FMT_ARGB8888;
    }
    else if (WL_SHM_FORMAT_XRGB8888 == shm_format)
    {
        pSurface->enFmt = HI_GFX2D_FMT_ARGB8888;
    }
    else
    {
        pSurface->enFmt = HI_GFX2D_FMT_ARGB8888;
    }

    return;
}

static void
hwc_src_surface_set_stride(HI_GFX2D_SURFACE_S *pSurface, int canvas_w)
{
    if (NULL == pSurface)
    {
        return;
    }

    if (HI_GFX2D_FMT_RGB565 == pSurface->enFmt)
    {
        pSurface->u32Stride[0] =  (canvas_w * 2 + 16 - 1) & (~(16 - 1));
    }
    else if (HI_GFX2D_FMT_ARGB8888 == pSurface->enFmt)
    {
        pSurface->u32Stride[0] =  (canvas_w * 4 + 16 - 1) & (~(16 - 1));
    }
    else
    {
        pSurface->u32Stride[0] = 0;
    }

    return;
}

static int
hwc_src_surface_re_create(HI_GFX2D_SURFACE_S *pSurface, int canvas_w, int canvas_h, int shm_format)
{
    int stride = 0;
    int cur_size = 0;
    int pre_size = 0;

    if (NULL == pSurface)
    {
        return 1;
    }

    if (WL_SHM_FORMAT_RGB565 == shm_format)
    {
        stride =  (canvas_w * 2 + 16 - 1) & (~(16 - 1));
    }
    else if (WL_SHM_FORMAT_ARGB8888 == shm_format)
    {
        stride =  (canvas_w * 4 + 16 - 1) & (~(16 - 1));
    }
    else if (WL_SHM_FORMAT_XRGB8888 == shm_format)
    {
        stride =  (canvas_w * 4 + 16 - 1) & (~(16 - 1));
    }
    else
    {
        stride = 0;
    }

    cur_size = stride * canvas_h;
    pre_size = pSurface->u32Stride[0] * pSurface->u32Height;

    if ((cur_size == pre_size) && (0 != pSurface->u32Phyaddr[0]))
    {
        return 0;
    }

    return 1;
}

static void*
hwc_src_surface_create(void)
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
hwc_src_surface_destory(HI_GFX2D_SURFACE_S *pSurface)
{
    if (NULL == pSurface)
    {
        return;
    }

    free(pSurface);

    return;
}

static void
hwc_src_surface_free(struct hwc_surface_state *ps)
{
    if (NULL != ps->pCanvasBuffer)
    {
        HI_MMZ_Unmap((HI_U32)(ps->pCanvasSurface->u32Phyaddr[0]));
    }

    if (0 != ps->pCanvasSurface->u32Phyaddr[0])
    {
        HI_MMZ_Delete((HI_U32)(ps->pCanvasSurface->u32Phyaddr[0]));
    }

    return;
}

static int
hwc_src_surface_alloc(struct weston_surface *es, int w, int h, void *buffer, int stride, int format)
{
    int mem_size;
    struct hwc_surface_state *ps = get_surface_state(es);

    hwc_src_surface_set_format(ps->pCanvasSurface, format);

    hwc_src_surface_set_stride(ps->pCanvasSurface, w);

    mem_size = ps->pCanvasSurface->u32Stride[0] * h;

    ps->pCanvasSurface->u32Phyaddr[0] = (HI_U32)HI_MMZ_New(mem_size, 16, NULL, "wayland_p_mem");
    if (0 == ps->pCanvasSurface->u32Phyaddr[0])
    {
        return 0;
    }

    ps->pCanvasBuffer = HI_MMZ_Map((HI_U32)ps->pCanvasSurface->u32Phyaddr[0], 0);
    if (NULL == ps->pCanvasBuffer)
    {
        HI_MMZ_Delete((HI_U32)ps->pCanvasSurface->u32Phyaddr[0]);
        return 0;
    }

    ps->pCanvasSurface->enType    = HI_GFX2D_SURFACE_TYPE_MEM;
    ps->pCanvasSurface->u32Width  = w;
    ps->pCanvasSurface->u32Height = h;

#if 0
    /**create canvase surface **/
    weston_log("\n======================================================================\n");
    weston_log("canvas surface\n");
    weston_log("width              = %d\n",   ps->pCanvasSurface->u32Width);
    weston_log("height             = %d\n",   ps->pCanvasSurface->u32Height);
    weston_log("stride             = %d\n",   ps->pCanvasSurface->u32Stride[0]);
    weston_log("ddr                = 0x%x\n", ps->pCanvasSurface->u32Phyaddr[0]);
    weston_log("\n======================================================================\n");
#endif

    return 1;
}


static void
hwc_blit_data_to_surface(struct hwc_surface_state *ps, int w, int h, void *buffer, int stride, int format)
{
    void *tmp_src = NULL;
    void *tmp_dst = NULL;
    int offset = 0;

    if (stride * h > ps->pCanvasSurface->u32Stride[0] * ps->pCanvasSurface->u32Height)
    {
        return;
    }

	tmp_src = buffer;
	tmp_dst = ps->pCanvasBuffer;

	for (offset = 0; offset < h; offset++)
	{
		memcpy(tmp_dst, tmp_src, stride);
		tmp_dst += ps->pCanvasSurface->u32Stride[0];
		tmp_src += stride;
	}

	return;
}


static void
buffer_state_handle_buffer_destroy(struct wl_listener *listener, void *data)
{
	struct hwc_surface_state *ps;

	ps = container_of(listener, struct hwc_surface_state,
			  buffer_destroy_listener);

    memset(ps->pCanvasBuffer, 0x0, ps->pCanvasSurface->u32Stride[0] * ps->pCanvasSurface->u32Height);

	ps->buffer_destroy_listener.notify = NULL;
}

static void
hwc_renderer_attach(struct weston_surface *es, struct weston_buffer *buffer)
{
	int	ret = 0;
	struct hwc_surface_state *ps = get_surface_state(es);
	struct wl_shm_buffer *shm_buffer;
    int w, h, stride, format;
    int re_create_canvas_surface;
    void *data_buffer = NULL;

	weston_buffer_reference(&ps->buffer_ref, buffer);

	if (ps->buffer_destroy_listener.notify) {
		wl_list_remove(&ps->buffer_destroy_listener.link);
		ps->buffer_destroy_listener.notify = NULL;
	}

	if (!buffer)
		return;

	shm_buffer = wl_shm_buffer_get(buffer->resource);

	if (! shm_buffer) {
		weston_log("Pixman renderer supports only SHM buffers\n");
		weston_buffer_reference(&ps->buffer_ref, NULL);
		return;
	}

	switch (wl_shm_buffer_get_format(shm_buffer)) {
        case WL_SHM_FORMAT_XRGB8888:
        case WL_SHM_FORMAT_ARGB8888:
            break;
        default:
        	weston_log("Unsupported gfx2d canvase buffer format\n");
        	weston_buffer_reference(&ps->buffer_ref, NULL);
        	return;
	}

	buffer->shm_buffer = shm_buffer;
	buffer->width = wl_shm_buffer_get_width(shm_buffer);
	buffer->height = wl_shm_buffer_get_height(shm_buffer);

    w = buffer->width;
    h = buffer->height;
    stride = wl_shm_buffer_get_stride(shm_buffer);
    format = wl_shm_buffer_get_format(shm_buffer);
    data_buffer = wl_shm_buffer_get_data(shm_buffer);

    re_create_canvas_surface = hwc_src_surface_re_create(ps->pCanvasSurface, w, h, format);
    if (0 == re_create_canvas_surface)
	{
        goto HWC_RENDERER_OK;
    }

    hwc_src_surface_free(ps);

	memset(ps->pCanvasSurface, 0x0, sizeof(HI_GFX2D_SURFACE_S));

	ret = hwc_src_surface_alloc(es, w, h, data_buffer,stride, format);
	if (0 == ret)
	{
		goto HWC_RENDERER_ERR;
	}

HWC_RENDERER_OK:
    hwc_blit_data_to_surface(ps, w, h, data_buffer, stride, format);

	ps->buffer_destroy_listener.notify =
		buffer_state_handle_buffer_destroy;
	wl_signal_add(&buffer->destroy_signal,
		      &ps->buffer_destroy_listener);

    return;

HWC_RENDERER_ERR:

    return;
}

static void
hwc_renderer_surface_state_destroy(struct hwc_surface_state *ps)
{
	wl_list_remove(&ps->surface_destroy_listener.link);
	wl_list_remove(&ps->renderer_destroy_listener.link);
	if (ps->buffer_destroy_listener.notify) {
		wl_list_remove(&ps->buffer_destroy_listener.link);
		ps->buffer_destroy_listener.notify = NULL;
	}

	ps->surface->renderer_state = NULL;

    hwc_src_surface_free(ps);
    hwc_src_surface_destory(ps->pCanvasSurface);
    ps->pCanvasSurface = NULL;

	weston_buffer_reference(&ps->buffer_ref, NULL);
	free(ps);
}

static void
surface_state_handle_surface_destroy(struct wl_listener *listener, void *data)
{
	struct hwc_surface_state *ps;

	ps = container_of(listener, struct hwc_surface_state,
			  surface_destroy_listener);

	hwc_renderer_surface_state_destroy(ps);
}

static void
surface_state_handle_renderer_destroy(struct wl_listener *listener, void *data)
{
	struct hwc_surface_state *ps;

	ps = container_of(listener, struct hwc_surface_state,
			  renderer_destroy_listener);

	hwc_renderer_surface_state_destroy(ps);
}

static int
hwc_renderer_create_surface(struct weston_surface *surface)
{
	struct hwc_surface_state *ps;
	struct hwc_renderer *pr = get_renderer(surface->compositor);

	ps = zalloc(sizeof *ps);
	if (ps == NULL)
		return -1;

	surface->renderer_state = ps;

	ps->surface = surface;

    ps->pCanvasSurface = hwc_src_surface_create();
    if (NULL == ps->pCanvasSurface)
    {
        free(ps);
        return -1;
    }

	ps->surface_destroy_listener.notify =
		surface_state_handle_surface_destroy;
	wl_signal_add(&surface->destroy_signal,
		      &ps->surface_destroy_listener);

	ps->renderer_destroy_listener.notify =
		surface_state_handle_renderer_destroy;
	wl_signal_add(&pr->destroy_signal,
		      &ps->renderer_destroy_listener);

	return 0;
}

static void
hwc_renderer_surface_set_color(struct weston_surface *es,
		 float red, float green, float blue, float alpha)
{
	struct hwc_surface_state *ps = get_surface_state(es);
	pixman_color_t color;

	color.red   = red   * 0xffff;
	color.green = green * 0xffff;
	color.blue  = blue  * 0xffff;
	color.alpha = alpha * 0xffff;

	memset(ps->pCanvasSurface, 0x0, sizeof(HI_GFX2D_SURFACE_S));

	ps->pCanvasSurface->enType    = HI_GFX2D_SURFACE_TYPE_COLOR;
	ps->pCanvasSurface->u32Width  = es->width;
	ps->pCanvasSurface->u32Height = es->height;
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

static void
hwc_renderer_destroy(struct weston_compositor *ec)
{
	struct hwc_renderer *pr = get_renderer(ec);

	wl_signal_emit(&pr->destroy_signal, pr);
	weston_binding_destroy(pr->debug_binding);
	free(pr);

	ec->renderer = NULL;
}

static void
hwc_renderer_surface_get_content_size(struct weston_surface *surface,
					 int *width, int *height)
{
	struct hwc_surface_state *ps = get_surface_state(surface);

	if (ps->pCanvasSurface)
    {
		*width  = ps->pCanvasSurface->u32Width;
		*height = ps->pCanvasSurface->u32Height;
	}
    else
    {
		*width  = 0;
		*height = 0;
	}
#if 0
    weston_log("\n======================================================================\n");
    weston_log("width  = %d\n",   *width);
    weston_log("height = %d\n",   *height);
    weston_log("\n======================================================================\n");
#endif
}

static int
hwc_renderer_surface_copy_content(struct weston_surface *surface,
				     void *target, size_t size,
				     int src_x, int src_y,
				     int width, int height)
{
	return 0;
}

static void
debug_binding(struct weston_keyboard *keyboard, uint32_t time, uint32_t key,
	      void *data)
{
	struct weston_compositor *ec = data;
	struct hwc_renderer *pr = (struct hwc_renderer *) ec->renderer;

	pr->repaint_debug ^= 1;

	if (pr->repaint_debug) {
		pixman_color_t red = {
			0x3fff, 0x0000, 0x0000, 0x3fff
		};

		pr->debug_color = pixman_image_create_solid_fill(&red);
	} else {
		pixman_image_unref(pr->debug_color);
		weston_compositor_damage_all(ec);
	}
}

static int
hwc_renderer_display_create(struct weston_compositor *ec)
{
	struct hwc_renderer *renderer;

	renderer = zalloc(sizeof *renderer);
	if (renderer == NULL)
	{
		return -1;
	}

	renderer->repaint_debug = 0;
	renderer->debug_color   = NULL;

    renderer->base.read_pixels              = hwc_renderer_read_pixels;
	renderer->base.repaint_output           = hwc_renderer_repaint_output;
	renderer->base.flush_damage             = hwc_renderer_flush_damage;
	renderer->base.attach                   = hwc_renderer_attach;
	renderer->base.surface_set_color        = hwc_renderer_surface_set_color;
	renderer->base.destroy                  = hwc_renderer_destroy;
	renderer->base.surface_get_content_size = hwc_renderer_surface_get_content_size;
	renderer->base.surface_copy_content     = hwc_renderer_surface_copy_content;

    ec->renderer = &renderer->base;
	ec->capabilities |= WESTON_CAP_ROTATION_ANY;
	ec->capabilities |= WESTON_CAP_CAPTURE_YFLIP;
	ec->capabilities |= WESTON_CAP_VIEW_CLIP_MASK;

	renderer->debug_binding = weston_compositor_add_debug_binding(ec, KEY_R, debug_binding, ec);

	wl_display_add_shm_format(ec->wl_display, WL_SHM_FORMAT_RGB565);

	wl_signal_init(&renderer->destroy_signal);

	return 0;
}

WL_EXPORT void
hwc_renderer_output_set_buffer(struct weston_output *output, pixman_image_t *buffer)
{
	struct hwc_output_state *po = hwc_get_output_state(output);
    /** this buffer is come from fbdev_frame_buffer_map() in compositor-fbdev.c
     ** is output to frame buffer surface
     **/
	if (buffer)
    {
		output->compositor->read_format = pixman_image_get_format(buffer);
	}
#if 0
    weston_log("\n======================================================================\n");
    weston_log("display surface infromation\n");
    weston_log("output->compositor->read_format = %d\n",   output->compositor->read_format);
#endif

    if (PIXMAN_a8r8g8b8 != output->compositor->read_format)
    {
        weston_log("hwc only support argb8888 format\n");
    }

    //output->compositor->read_format = PIXMAN_a8r8g8b8;
#if 0
    weston_log("output->compositor->read_format = %d\n",   output->compositor->read_format);
    weston_log("\n======================================================================\n");
#endif

    return;
}

WL_EXPORT int
hwc_renderer_output_create(struct weston_output *output,int fb_fd)
{
	struct hwc_output_state *po;
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
	po->compose[0].stInRect.u32Width       = output->current_mode->width;
	po->compose[0].stInRect.u32Height      = output->current_mode->height;
	po->compose[0].stOutRect               = po->compose[0].stInRect;
	po->compose[0].stOpt.stBlend.bCovBlend = 1;
	po->compose[0].stSurface.enType        = HI_GFX2D_SURFACE_TYPE_MEM;
	po->compose[0].stSurface.enFmt         = HI_GFX2D_FMT_ARGB8888;
	po->compose[0].stSurface.u32Width      = output->current_mode->width;
	po->compose[0].stSurface.u32Height     = output->current_mode->height;
	po->compose[0].stSurface.u32Phyaddr[0] = (unsigned long)po->DispBuffer[0];
	po->compose[0].stSurface.u32Stride[0]  = fixinfo.line_length;

    memcpy(&po->DstSurface, &po->compose[0].stSurface, sizeof(HI_GFX2D_SURFACE_S));

	po->w = output->current_mode->width;
    po->h = output->current_mode->height;

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

	output->renderer_state = po;

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

WL_EXPORT void
hwc_renderer_output_destroy(struct weston_output *output)
{
	struct hwc_output_state *po = hwc_get_output_state(output);
    if (NULL != po)
    {
	   free(po);
    }

	HI_GFX2D_Close(HI_GFX2D_DEV_ID_0);

    return;
}

//HISILICON add begin
//tag, support hwc compose, hwc-renderer.c revise from pixman-renderer.c and gl-renderer.c
WL_EXPORT struct hwc_renderer_interface hwc_renderer_interface = {
	.display_create = hwc_renderer_display_create,
	.output_create  = hwc_renderer_output_create,
	.output_surface = hwc_renderer_output_set_buffer,
	.output_destroy = hwc_renderer_output_destroy,
};
//HISILICON add end
