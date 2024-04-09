/*
 * Copyright © 2012 Intel Corporation
 * Copyright © 2015 Collabora, Ltd.
 * Copyright © 2016 NVIDIA Corporation
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

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <float.h>
#include <assert.h>
#include <linux/input.h>
#include <drm_fourcc.h>

#include "gl-renderer.h"
#include "vertex-clipping.h"
#include "linux-dmabuf.h"
#include "linux-dmabuf-unstable-v1-server-protocol.h"

#include "shared/helpers.h"
#include "shared/platform.h"
#include "weston-egl-ext.h"

//HISILICON add begin
//tag, support hwc compose
#define BUILD_HWC_RENDERER
#ifdef BUILD_HWC_RENDERER
#include "hwc-renderer.h"
#endif
typedef struct
{
	unsigned int width;
	unsigned int height;
	unsigned int pitch;
	unsigned int format;
	unsigned int name;
	unsigned int flags;
}wayland_egl_buffer_info;

typedef struct hiGL_RECT_S
{
    int s32XPos;
    int s32YPos;
    unsigned int u32Width;
    unsigned int u32Height;
}GL_RECT_S;

static int gs_hwc_compositor_surpport = 0;
//HISILICON add end

struct gl_shader {
	GLuint program;
	GLuint vertex_shader, fragment_shader;
	GLint proj_uniform;
	GLint tex_uniforms[3];
	GLint alpha_uniform;
	GLint color_uniform;
	const char *vertex_source, *fragment_source;
};

#define BUFFER_DAMAGE_COUNT 2

enum gl_border_status {
	BORDER_STATUS_CLEAN = 0,
	BORDER_TOP_DIRTY = 1 << GL_RENDERER_BORDER_TOP,
	BORDER_LEFT_DIRTY = 1 << GL_RENDERER_BORDER_LEFT,
	BORDER_RIGHT_DIRTY = 1 << GL_RENDERER_BORDER_RIGHT,
	BORDER_BOTTOM_DIRTY = 1 << GL_RENDERER_BORDER_BOTTOM,
	BORDER_ALL_DIRTY = 0xf,
	BORDER_SIZE_CHANGED = 0x10
};

struct gl_border_image {
	GLuint tex;
	int32_t width, height;
	int32_t tex_width;
	void *data;
};

struct gl_output_state {
//HISILICON add begin
//tag, support hwc compose
    void *hwc_renderer_output;
//HISILICON add end
	EGLSurface egl_surface;
	pixman_region32_t buffer_damage[BUFFER_DAMAGE_COUNT];
	int buffer_damage_index;
	enum gl_border_status border_damage[BUFFER_DAMAGE_COUNT];
	struct gl_border_image borders[4];
	enum gl_border_status border_status;

	struct weston_matrix output_matrix;
};

enum buffer_type {
	BUFFER_TYPE_NULL,
	BUFFER_TYPE_SOLID, /* internal solid color surfaces without a buffer */
	BUFFER_TYPE_SHM,
	BUFFER_TYPE_EGL
};

struct gl_renderer;

struct egl_image {
	struct gl_renderer *renderer;
	EGLImageKHR image;
	int refcount;
};

enum import_type {
	IMPORT_TYPE_INVALID,
	IMPORT_TYPE_DIRECT,
	IMPORT_TYPE_GL_CONVERSION
};

struct dmabuf_image {
	struct linux_dmabuf_buffer *dmabuf;
	int num_images;
	struct egl_image *images[3];
	struct wl_list link;

	enum import_type import_type;
	GLenum target;
	struct gl_shader *shader;
};

struct yuv_plane_descriptor {
	int width_divisor;
	int height_divisor;
	uint32_t format;
	int plane_index;
};

struct yuv_format_descriptor {
	uint32_t format;
	int input_planes;
	int output_planes;
	int texture_type;
	struct yuv_plane_descriptor plane[4];
};

struct gl_surface_state {
//HISILICON add begin
//tag, support hwc compose
    void *hwc_renderer_surface;
    int hwcompose_support;
//HISILICON add end
	GLfloat color[4];
	struct gl_shader *shader;

	GLuint textures[3];
	int num_textures;
	bool needs_full_upload;
	pixman_region32_t texture_damage;

	/* These are only used by SHM surfaces to detect when we need
	 * to do a full upload to specify a new internal texture
	 * format */
	GLenum gl_format[3];
	GLenum gl_pixel_type;

	struct egl_image* images[3];
	GLenum target;
	int num_images;

	struct weston_buffer_reference buffer_ref;
	enum buffer_type buffer_type;
	int pitch; /* in pixels */
	int height; /* in pixels */
	int y_inverted;

	/* Extension needed for SHM YUV texture */
	int offset[3]; /* offset per plane */
	int hsub[3];  /* horizontal subsampling per plane */
	int vsub[3];  /* vertical subsampling per plane */

	struct weston_surface *surface;

	struct wl_listener surface_destroy_listener;
	struct wl_listener renderer_destroy_listener;
};

struct gl_renderer {
	struct weston_renderer base;
//HISILICON add begin
//tag, support hwc compose
    int use_gl_hwc;
    int fb_fd;
//HISILICON add end
	int fragment_shader_debug;
	int fan_debug;
	struct weston_binding *fragment_binding;
	struct weston_binding *fan_binding;

	EGLDisplay egl_display;
	EGLContext egl_context;
	EGLConfig egl_config;

	EGLSurface dummy_surface;

	struct wl_array vertices;
	struct wl_array vtxcnt;

	PFNGLEGLIMAGETARGETTEXTURE2DOESPROC image_target_texture_2d;
	PFNEGLCREATEIMAGEKHRPROC create_image;
	PFNEGLDESTROYIMAGEKHRPROC destroy_image;
	PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC swap_buffers_with_damage;
	PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC create_platform_window;

	int has_unpack_subimage;

	PFNEGLBINDWAYLANDDISPLAYWL bind_display;
	PFNEGLUNBINDWAYLANDDISPLAYWL unbind_display;
	PFNEGLQUERYWAYLANDBUFFERWL query_buffer;
	int has_bind_display;

	int has_egl_image_external;

	int has_egl_buffer_age;

	int has_configless_context;

	int has_surfaceless_context;

	int has_dmabuf_import;
	struct wl_list dmabuf_images;

	int has_gl_texture_rg;

	struct gl_shader texture_shader_rgba;
	struct gl_shader texture_shader_rgbx;
	struct gl_shader texture_shader_egl_external;
	struct gl_shader texture_shader_y_uv;
	struct gl_shader texture_shader_y_u_v;
	struct gl_shader texture_shader_y_xuxv;
	struct gl_shader invert_color_shader;
	struct gl_shader solid_shader;
	struct gl_shader *current_shader;

	struct wl_signal destroy_signal;

	struct wl_listener output_destroy_listener;

	int has_dmabuf_import_modifiers;
	PFNEGLQUERYDMABUFFORMATSEXTPROC query_dmabuf_formats;
	PFNEGLQUERYDMABUFMODIFIERSEXTPROC query_dmabuf_modifiers;
};

static PFNEGLGETPLATFORMDISPLAYEXTPROC get_platform_display = NULL;

//HISILICON add begin
//tag, support hwc compose
#ifdef BUILD_HWC_RENDERER
struct gl_hwc_renderer_interface *gs_hwc_renderer = NULL;
#endif
//HISILICON add end

static inline const char *
dump_format(uint32_t format, char out[4])
{
#if BYTE_ORDER == BIG_ENDIAN
	format = __builtin_bswap32(format);
#endif
	memcpy(out, &format, 4);
	return out;
}

static inline struct gl_output_state *
get_output_state(struct weston_output *output)
{
	return (struct gl_output_state *)output->renderer_state;
}

static int
gl_renderer_create_surface(struct weston_surface *surface);

//HISILICON add begin
//tag, support hwc compose
static inline struct gl_renderer *
get_renderer(struct weston_compositor *ec);
//HISILICON add end

static inline struct gl_surface_state *
get_surface_state(struct weston_surface *surface)
{
	if (!surface->renderer_state)
		gl_renderer_create_surface(surface);

	return (struct gl_surface_state *)surface->renderer_state;
}

static inline struct gl_renderer *
get_renderer(struct weston_compositor *ec)
{
	return (struct gl_renderer *)ec->renderer;
}

static struct egl_image*
egl_image_create(struct gl_renderer *gr, EGLenum target,
		 EGLClientBuffer buffer, const EGLint *attribs)
{
	struct egl_image *img;

	img = zalloc(sizeof *img);
	img->renderer = gr;
	img->refcount = 1;
	img->image = gr->create_image(gr->egl_display, EGL_NO_CONTEXT,
				      target, buffer, attribs);

	if (img->image == EGL_NO_IMAGE_KHR) {
		free(img);
		return NULL;
	}

	return img;
}

static struct egl_image*
egl_image_ref(struct egl_image *image)
{
	image->refcount++;

	return image;
}

static int
egl_image_unref(struct egl_image *image)
{
	struct gl_renderer *gr = image->renderer;

	assert(image->refcount > 0);

	image->refcount--;
	if (image->refcount > 0)
		return image->refcount;

	gr->destroy_image(gr->egl_display, image->image);
	free(image);

	return 0;
}

static struct dmabuf_image*
dmabuf_image_create(void)
{
	struct dmabuf_image *img;

	img = zalloc(sizeof *img);
	wl_list_init(&img->link);

	return img;
}

static void
dmabuf_image_destroy(struct dmabuf_image *image)
{
	int i;

	for (i = 0; i < image->num_images; ++i)
		egl_image_unref(image->images[i]);

	if (image->dmabuf)
		linux_dmabuf_buffer_set_user_data(image->dmabuf, NULL, NULL);

	wl_list_remove(&image->link);
}

static const char *
egl_error_string(EGLint code)
{
#define MYERRCODE(x) case x: return #x;
	switch (code) {
	MYERRCODE(EGL_SUCCESS)
	MYERRCODE(EGL_NOT_INITIALIZED)
	MYERRCODE(EGL_BAD_ACCESS)
	MYERRCODE(EGL_BAD_ALLOC)
	MYERRCODE(EGL_BAD_ATTRIBUTE)
	MYERRCODE(EGL_BAD_CONTEXT)
	MYERRCODE(EGL_BAD_CONFIG)
	MYERRCODE(EGL_BAD_CURRENT_SURFACE)
	MYERRCODE(EGL_BAD_DISPLAY)
	MYERRCODE(EGL_BAD_SURFACE)
	MYERRCODE(EGL_BAD_MATCH)
	MYERRCODE(EGL_BAD_PARAMETER)
	MYERRCODE(EGL_BAD_NATIVE_PIXMAP)
	MYERRCODE(EGL_BAD_NATIVE_WINDOW)
	MYERRCODE(EGL_CONTEXT_LOST)
	default:
		return "unknown";
	}
#undef MYERRCODE
}

static void
gl_renderer_print_egl_error_state(void)
{
	EGLint code;

	code = eglGetError();
	weston_log("EGL error state: %s (0x%04lx)\n",
		egl_error_string(code), (long)code);
}

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) > (b)) ? (b) : (a))

/*
 * Compute the boundary vertices of the intersection of the global coordinate
 * aligned rectangle 'rect', and an arbitrary quadrilateral produced from
 * 'surf_rect' when transformed from surface coordinates into global coordinates.
 * The vertices are written to 'ex' and 'ey', and the return value is the
 * number of vertices. Vertices are produced in clockwise winding order.
 * Guarantees to produce either zero vertices, or 3-8 vertices with non-zero
 * polygon area.
 */
static int
calculate_edges(struct weston_view *ev, pixman_box32_t *rect,
		pixman_box32_t *surf_rect, GLfloat *ex, GLfloat *ey)
{

	struct clip_context ctx;
	int i, n;
	GLfloat min_x, max_x, min_y, max_y;
	struct polygon8 surf = {
		{ surf_rect->x1, surf_rect->x2, surf_rect->x2, surf_rect->x1 },
		{ surf_rect->y1, surf_rect->y1, surf_rect->y2, surf_rect->y2 },
		4
	};

	ctx.clip.x1 = rect->x1;
	ctx.clip.y1 = rect->y1;
	ctx.clip.x2 = rect->x2;
	ctx.clip.y2 = rect->y2;

	/* transform surface to screen space: */
	for (i = 0; i < surf.n; i++)
		weston_view_to_global_float(ev, surf.x[i], surf.y[i],
					    &surf.x[i], &surf.y[i]);

	/* find bounding box: */
	min_x = max_x = surf.x[0];
	min_y = max_y = surf.y[0];

	for (i = 1; i < surf.n; i++) {
		min_x = min(min_x, surf.x[i]);
		max_x = max(max_x, surf.x[i]);
		min_y = min(min_y, surf.y[i]);
		max_y = max(max_y, surf.y[i]);
	}

	/* First, simple bounding box check to discard early transformed
	 * surface rects that do not intersect with the clip region:
	 */
	if ((min_x >= ctx.clip.x2) || (max_x <= ctx.clip.x1) ||
	    (min_y >= ctx.clip.y2) || (max_y <= ctx.clip.y1))
		return 0;

	/* Simple case, bounding box edges are parallel to surface edges,
	 * there will be only four edges.  We just need to clip the surface
	 * vertices to the clip rect bounds:
	 */
	if (!ev->transform.enabled)
		return clip_simple(&ctx, &surf, ex, ey);

	/* Transformed case: use a general polygon clipping algorithm to
	 * clip the surface rectangle with each side of 'rect'.
	 * The algorithm is Sutherland-Hodgman, as explained in
	 * http://www.codeguru.com/cpp/misc/misc/graphics/article.php/c8965/Polygon-Clipping.htm
	 * but without looking at any of that code.
	 */
	n = clip_transformed(&ctx, &surf, ex, ey);

	if (n < 3)
		return 0;

	return n;
}

static bool
merge_down(pixman_box32_t *a, pixman_box32_t *b, pixman_box32_t *merge)
{
	if (a->x1 == b->x1 && a->x2 == b->x2 && a->y1 == b->y2) {
		merge->x1 = a->x1;
		merge->x2 = a->x2;
		merge->y1 = b->y1;
		merge->y2 = a->y2;
		return true;
	}
	return false;
}

static int
compress_bands(pixman_box32_t *inrects, int nrects,
		   pixman_box32_t **outrects)
{
	bool merged = false;
	pixman_box32_t *out, merge_rect;
	int i, j, nout;

	if (!nrects) {
		*outrects = NULL;
		return 0;
	}

	/* nrects is an upper bound - we're not too worried about
	 * allocating a little extra
	 */
	out = malloc(sizeof(pixman_box32_t) * nrects);
	out[0] = inrects[0];
	nout = 1;
	for (i = 1; i < nrects; i++) {
		for (j = 0; j < nout; j++) {
			merged = merge_down(&inrects[i], &out[j], &merge_rect);
			if (merged) {
				out[j] = merge_rect;
				break;
			}
		}
		if (!merged) {
			out[nout] = inrects[i];
			nout++;
		}
	}
	*outrects = out;
	return nout;
}

static int
texture_region(struct weston_view *ev, pixman_region32_t *region,
		pixman_region32_t *surf_region)
{
	struct gl_surface_state *gs = get_surface_state(ev->surface);
	struct weston_compositor *ec = ev->surface->compositor;
	struct gl_renderer *gr = get_renderer(ec);
	GLfloat *v, inv_width, inv_height;
	unsigned int *vtxcnt, nvtx = 0;
	pixman_box32_t *rects, *surf_rects;
	pixman_box32_t *raw_rects;
	int i, j, k, nrects, nsurf, raw_nrects;
	bool used_band_compression;
	raw_rects = pixman_region32_rectangles(region, &raw_nrects);
	surf_rects = pixman_region32_rectangles(surf_region, &nsurf);

	if (raw_nrects < 4) {
		used_band_compression = false;
		nrects = raw_nrects;
		rects = raw_rects;
	} else {
		nrects = compress_bands(raw_rects, raw_nrects, &rects);
		used_band_compression = true;
	}
	/* worst case we can have 8 vertices per rect (ie. clipped into
	 * an octagon):
	 */
	v = wl_array_add(&gr->vertices, nrects * nsurf * 8 * 4 * sizeof *v);
	vtxcnt = wl_array_add(&gr->vtxcnt, nrects * nsurf * sizeof *vtxcnt);

	inv_width = 1.0 / gs->pitch;
        inv_height = 1.0 / gs->height;

	for (i = 0; i < nrects; i++) {
		pixman_box32_t *rect = &rects[i];
		for (j = 0; j < nsurf; j++) {
			pixman_box32_t *surf_rect = &surf_rects[j];
			GLfloat sx, sy, bx, by;
			GLfloat ex[8], ey[8];          /* edge points in screen space */
			int n;

			/* The transformed surface, after clipping to the clip region,
			 * can have as many as eight sides, emitted as a triangle-fan.
			 * The first vertex in the triangle fan can be chosen arbitrarily,
			 * since the area is guaranteed to be convex.
			 *
			 * If a corner of the transformed surface falls outside of the
			 * clip region, instead of emitting one vertex for the corner
			 * of the surface, up to two are emitted for two corresponding
			 * intersection point(s) between the surface and the clip region.
			 *
			 * To do this, we first calculate the (up to eight) points that
			 * form the intersection of the clip rect and the transformed
			 * surface.
			 */
			n = calculate_edges(ev, rect, surf_rect, ex, ey);
			if (n < 3)
				continue;

			/* emit edge points: */
			for (k = 0; k < n; k++) {
				weston_view_from_global_float(ev, ex[k], ey[k],
							      &sx, &sy);
				/* position: */
				*(v++) = ex[k];
				*(v++) = ey[k];
				/* texcoord: */
				weston_surface_to_buffer_float(ev->surface,
							       sx, sy,
							       &bx, &by);
				*(v++) = bx * inv_width;
				if (gs->y_inverted) {
					*(v++) = by * inv_height;
				} else {
					*(v++) = (gs->height - by) * inv_height;
				}
			}

			vtxcnt[nvtx++] = n;
		}
	}

	if (used_band_compression)
		free(rects);
	return nvtx;
}

static void
triangle_fan_debug(struct weston_view *view, int first, int count)
{
	struct weston_compositor *compositor = view->surface->compositor;
	struct gl_renderer *gr = get_renderer(compositor);
	int i;
	GLushort *buffer;
	GLushort *index;
	int nelems;
	static int color_idx = 0;
	static const GLfloat color[][4] = {
			{ 1.0, 0.0, 0.0, 1.0 },
			{ 0.0, 1.0, 0.0, 1.0 },
			{ 0.0, 0.0, 1.0, 1.0 },
			{ 1.0, 1.0, 1.0, 1.0 },
	};

	nelems = (count - 1 + count - 2) * 2;

	buffer = malloc(sizeof(GLushort) * nelems);
	index = buffer;

	for (i = 1; i < count; i++) {
		*index++ = first;
		*index++ = first + i;
	}

	for (i = 2; i < count; i++) {
		*index++ = first + i - 1;
		*index++ = first + i;
	}

	glUseProgram(gr->solid_shader.program);
	glUniform4fv(gr->solid_shader.color_uniform, 1,
			color[color_idx++ % ARRAY_LENGTH(color)]);
	glDrawElements(GL_LINES, nelems, GL_UNSIGNED_SHORT, buffer);
	glUseProgram(gr->current_shader->program);
	free(buffer);
}

static void
repaint_region(struct weston_view *ev, pixman_region32_t *region,
		pixman_region32_t *surf_region)
{
	struct weston_compositor *ec = ev->surface->compositor;
	struct gl_renderer *gr = get_renderer(ec);
	GLfloat *v;
	unsigned int *vtxcnt;
	int i, first, nfans;

	/* The final region to be painted is the intersection of
	 * 'region' and 'surf_region'. However, 'region' is in the global
	 * coordinates, and 'surf_region' is in the surface-local
	 * coordinates. texture_region() will iterate over all pairs of
	 * rectangles from both regions, compute the intersection
	 * polygon for each pair, and store it as a triangle fan if
	 * it has a non-zero area (at least 3 vertices, actually).
	 */

//HISILICON add begin
//tag, support hwc compose
    struct gl_output_state  *go_output  = get_output_state(ev->output);
    struct gl_surface_state *go_surface = get_surface_state(ev->surface);
    if (go_surface->hwcompose_support)
    {
        gs_hwc_renderer->repaint_output(ev,go_output->hwc_renderer_output,go_surface->hwc_renderer_surface,region,surf_region);
        gs_hwc_compositor_surpport = 1;
        return;
    }
//HISILICON add end

	nfans = texture_region(ev, region, surf_region);

	v = gr->vertices.data;
	vtxcnt = gr->vtxcnt.data;

	/* position: */
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof *v, &v[0]);
	glEnableVertexAttribArray(0);

	/* texcoord: */
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof *v, &v[2]);
	glEnableVertexAttribArray(1);

	for (i = 0, first = 0; i < nfans; i++) {
		glDrawArrays(GL_TRIANGLE_FAN, first, vtxcnt[i]);
		if (gr->fan_debug)
			triangle_fan_debug(ev, first, vtxcnt[i]);
		first += vtxcnt[i];
	}

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	gr->vertices.size = 0;
	gr->vtxcnt.size = 0;
}

static int
use_output(struct weston_output *output)
{
	static int errored;
	struct gl_output_state *go = get_output_state(output);
	struct gl_renderer *gr = get_renderer(output->compositor);
	EGLBoolean ret;

	ret = eglMakeCurrent(gr->egl_display, go->egl_surface,
			     go->egl_surface, gr->egl_context);

	if (ret == EGL_FALSE) {
		if (errored)
			return -1;
		errored = 1;
		weston_log("Failed to make EGL context current.\n");
		gl_renderer_print_egl_error_state();
		return -1;
	}

	return 0;
}

static int
shader_init(struct gl_shader *shader, struct gl_renderer *gr,
		   const char *vertex_source, const char *fragment_source);

static void
use_shader(struct gl_renderer *gr, struct gl_shader *shader)
{
	if (!shader->program) {
		int ret;

		ret =  shader_init(shader, gr,
				   shader->vertex_source,
				   shader->fragment_source);

		if (ret < 0)
			weston_log("warning: failed to compile shader\n");
	}

	if (gr->current_shader == shader)
		return;
	glUseProgram(shader->program);
	gr->current_shader = shader;
}

static void
shader_uniforms(struct gl_shader *shader,
		struct weston_view *view,
		struct weston_output *output)
{
	int i;
	struct gl_surface_state *gs = get_surface_state(view->surface);
	struct gl_output_state *go = get_output_state(output);

	glUniformMatrix4fv(shader->proj_uniform,
			   1, GL_FALSE, go->output_matrix.d);
	glUniform4fv(shader->color_uniform, 1, gs->color);
	glUniform1f(shader->alpha_uniform, view->alpha);

	for (i = 0; i < gs->num_textures; i++)
		glUniform1i(shader->tex_uniforms[i], i);
}

static void
draw_view(struct weston_view *ev, struct weston_output *output,
	  pixman_region32_t *damage) /* in global coordinates */
{
	struct weston_compositor *ec = ev->surface->compositor;
	struct gl_renderer *gr = get_renderer(ec);
	struct gl_surface_state *gs = get_surface_state(ev->surface);
	/* repaint bounding region in global coordinates: */
	pixman_region32_t repaint;
	/* opaque region in surface coordinates: */
	pixman_region32_t surface_opaque;
	/* non-opaque region in surface coordinates: */
	pixman_region32_t surface_blend;
	GLint filter;
	int i;

	/* In case of a runtime switch of renderers, we may not have received
	 * an attach for this surface since the switch. In that case we don't
	 * have a valid buffer or a proper shader set up so skip rendering. */
	if (!gs->shader)
		return;

	pixman_region32_init(&repaint);
	pixman_region32_intersect(&repaint,
				  &ev->transform.boundingbox, damage);
	pixman_region32_subtract(&repaint, &repaint, &ev->clip);

	if (!pixman_region32_not_empty(&repaint))
		goto out;

	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	if (gr->fan_debug) {
		use_shader(gr, &gr->solid_shader);
		shader_uniforms(&gr->solid_shader, ev, output);
	}

	use_shader(gr, gs->shader);
	shader_uniforms(gs->shader, ev, output);

	if (ev->transform.enabled || output->zoom.active ||
	    output->current_scale != ev->surface->buffer_viewport.buffer.scale)
		filter = GL_LINEAR;
	else
		filter = GL_NEAREST;

	for (i = 0; i < gs->num_textures; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(gs->target, gs->textures[i]);
		glTexParameteri(gs->target, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(gs->target, GL_TEXTURE_MAG_FILTER, filter);
	}

	/* blended region is whole surface minus opaque region: */
	pixman_region32_init_rect(&surface_blend, 0, 0,
				  ev->surface->width, ev->surface->height);
	if (ev->geometry.scissor_enabled)
		pixman_region32_intersect(&surface_blend, &surface_blend,
					  &ev->geometry.scissor);
	pixman_region32_subtract(&surface_blend, &surface_blend,
				 &ev->surface->opaque);

	/* XXX: Should we be using ev->transform.opaque here? */
	pixman_region32_init(&surface_opaque);
	if (ev->geometry.scissor_enabled)
		pixman_region32_intersect(&surface_opaque,
					  &ev->surface->opaque,
					  &ev->geometry.scissor);
	else
		pixman_region32_copy(&surface_opaque, &ev->surface->opaque);

	if (pixman_region32_not_empty(&surface_opaque)) {
		if (gs->shader == &gr->texture_shader_rgba) {
			/* Special case for RGBA textures with possibly
			 * bad data in alpha channel: use the shader
			 * that forces texture alpha = 1.0.
			 * Xwayland surfaces need this.
			 */
			use_shader(gr, &gr->texture_shader_rgbx);
			shader_uniforms(&gr->texture_shader_rgbx, ev, output);
		}

		if (ev->alpha < 1.0)
			glEnable(GL_BLEND);
		else
			glDisable(GL_BLEND);

		repaint_region(ev, &repaint, &surface_opaque);
	}

	if (pixman_region32_not_empty(&surface_blend)) {
		use_shader(gr, gs->shader);
		glEnable(GL_BLEND);
		repaint_region(ev, &repaint, &surface_blend);
	}

	pixman_region32_fini(&surface_blend);
	pixman_region32_fini(&surface_opaque);

out:
	pixman_region32_fini(&repaint);
}

static void
repaint_views(struct weston_output *output, pixman_region32_t *damage)
{
	struct weston_compositor *compositor = output->compositor;
	struct weston_view *view;

	wl_list_for_each_reverse(view, &compositor->view_list, link)
		if (view->plane == &compositor->primary_plane)
			draw_view(view, output, damage);
}

static void
draw_output_border_texture(struct gl_output_state *go,
			   enum gl_renderer_border_side side,
			   int32_t x, int32_t y,
			   int32_t width, int32_t height)
{
	struct gl_border_image *img = &go->borders[side];
	static GLushort indices [] = { 0, 1, 3, 3, 1, 2 };

	if (!img->data) {
		if (img->tex) {
			glDeleteTextures(1, &img->tex);
			img->tex = 0;
		}

		return;
	}

	if (!img->tex) {
		glGenTextures(1, &img->tex);
		glBindTexture(GL_TEXTURE_2D, img->tex);

		glTexParameteri(GL_TEXTURE_2D,
				GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,
				GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,
				GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,
				GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	} else {
		glBindTexture(GL_TEXTURE_2D, img->tex);
	}

	if (go->border_status & (1 << side)) {
		glPixelStorei(GL_UNPACK_ROW_LENGTH_EXT, 0);
		glPixelStorei(GL_UNPACK_SKIP_PIXELS_EXT, 0);
		glPixelStorei(GL_UNPACK_SKIP_ROWS_EXT, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_BGRA_EXT,
			     img->tex_width, img->height, 0,
			     GL_BGRA_EXT, GL_UNSIGNED_BYTE, img->data);
	}

	GLfloat texcoord[] = {
		0.0f, 0.0f,
		(GLfloat)img->width / (GLfloat)img->tex_width, 0.0f,
		(GLfloat)img->width / (GLfloat)img->tex_width, 1.0f,
		0.0f, 1.0f,
	};

	GLfloat verts[] = {
		x, y,
		x + width, y,
		x + width, y + height,
		x, y + height
	};

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, verts);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, texcoord);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

static int
output_has_borders(struct weston_output *output)
{
	struct gl_output_state *go = get_output_state(output);

	return go->borders[GL_RENDERER_BORDER_TOP].data ||
	       go->borders[GL_RENDERER_BORDER_RIGHT].data ||
	       go->borders[GL_RENDERER_BORDER_BOTTOM].data ||
	       go->borders[GL_RENDERER_BORDER_LEFT].data;
}

static void
draw_output_borders(struct weston_output *output,
		    enum gl_border_status border_status)
{
	struct gl_output_state *go = get_output_state(output);
	struct gl_renderer *gr = get_renderer(output->compositor);
	struct gl_shader *shader = &gr->texture_shader_rgba;
	struct gl_border_image *top, *bottom, *left, *right;
	struct weston_matrix matrix;
	int full_width, full_height;

	if (border_status == BORDER_STATUS_CLEAN)
		return; /* Clean. Nothing to do. */

	top = &go->borders[GL_RENDERER_BORDER_TOP];
	bottom = &go->borders[GL_RENDERER_BORDER_BOTTOM];
	left = &go->borders[GL_RENDERER_BORDER_LEFT];
	right = &go->borders[GL_RENDERER_BORDER_RIGHT];

	full_width = output->current_mode->width + left->width + right->width;
	full_height = output->current_mode->height + top->height + bottom->height;

	glDisable(GL_BLEND);
	use_shader(gr, shader);

	glViewport(0, 0, full_width, full_height);

	weston_matrix_init(&matrix);
	weston_matrix_translate(&matrix, -full_width/2.0, -full_height/2.0, 0);
	weston_matrix_scale(&matrix, 2.0/full_width, -2.0/full_height, 1);
	glUniformMatrix4fv(shader->proj_uniform, 1, GL_FALSE, matrix.d);

	glUniform1i(shader->tex_uniforms[0], 0);
	glUniform1f(shader->alpha_uniform, 1);
	glActiveTexture(GL_TEXTURE0);

	if (border_status & BORDER_TOP_DIRTY)
		draw_output_border_texture(go, GL_RENDERER_BORDER_TOP,
					   0, 0,
					   full_width, top->height);
	if (border_status & BORDER_LEFT_DIRTY)
		draw_output_border_texture(go, GL_RENDERER_BORDER_LEFT,
					   0, top->height,
					   left->width, output->current_mode->height);
	if (border_status & BORDER_RIGHT_DIRTY)
		draw_output_border_texture(go, GL_RENDERER_BORDER_RIGHT,
					   full_width - right->width, top->height,
					   right->width, output->current_mode->height);
	if (border_status & BORDER_BOTTOM_DIRTY)
		draw_output_border_texture(go, GL_RENDERER_BORDER_BOTTOM,
					   0, full_height - bottom->height,
					   full_width, bottom->height);
}

static void
output_get_border_damage(struct weston_output *output,
			 enum gl_border_status border_status,
			 pixman_region32_t *damage)
{
	struct gl_output_state *go = get_output_state(output);
	struct gl_border_image *top, *bottom, *left, *right;
	int full_width, full_height;

	if (border_status == BORDER_STATUS_CLEAN)
		return; /* Clean. Nothing to do. */

	top = &go->borders[GL_RENDERER_BORDER_TOP];
	bottom = &go->borders[GL_RENDERER_BORDER_BOTTOM];
	left = &go->borders[GL_RENDERER_BORDER_LEFT];
	right = &go->borders[GL_RENDERER_BORDER_RIGHT];

	full_width = output->current_mode->width + left->width + right->width;
	full_height = output->current_mode->height + top->height + bottom->height;
	if (border_status & BORDER_TOP_DIRTY)
		pixman_region32_union_rect(damage, damage,
					   0, 0,
					   full_width, top->height);
	if (border_status & BORDER_LEFT_DIRTY)
		pixman_region32_union_rect(damage, damage,
					   0, top->height,
					   left->width, output->current_mode->height);
	if (border_status & BORDER_RIGHT_DIRTY)
		pixman_region32_union_rect(damage, damage,
					   full_width - right->width, top->height,
					   right->width, output->current_mode->height);
	if (border_status & BORDER_BOTTOM_DIRTY)
		pixman_region32_union_rect(damage, damage,
					   0, full_height - bottom->height,
					   full_width, bottom->height);
}

static void
output_get_damage(struct weston_output *output,
		  pixman_region32_t *buffer_damage, uint32_t *border_damage)
{
	struct gl_output_state *go = get_output_state(output);
	struct gl_renderer *gr = get_renderer(output->compositor);
	EGLint buffer_age = 0;
	EGLBoolean ret;
	int i;

	if (gr->has_egl_buffer_age) {
		ret = eglQuerySurface(gr->egl_display, go->egl_surface,
				      EGL_BUFFER_AGE_EXT, &buffer_age);
		if (ret == EGL_FALSE) {
			weston_log("buffer age query failed.\n");
			gl_renderer_print_egl_error_state();
		}
	}

	if (buffer_age == 0 || buffer_age - 1 > BUFFER_DAMAGE_COUNT) {
		pixman_region32_copy(buffer_damage, &output->region);
		*border_damage = BORDER_ALL_DIRTY;
	} else {
		for (i = 0; i < buffer_age - 1; i++)
			*border_damage |= go->border_damage[(go->buffer_damage_index + i) % BUFFER_DAMAGE_COUNT];

		if (*border_damage & BORDER_SIZE_CHANGED) {
			/* If we've had a resize, we have to do a full
			 * repaint. */
			*border_damage |= BORDER_ALL_DIRTY;
			pixman_region32_copy(buffer_damage, &output->region);
		} else {
			for (i = 0; i < buffer_age - 1; i++)
				pixman_region32_union(buffer_damage,
						      buffer_damage,
						      &go->buffer_damage[(go->buffer_damage_index + i) % BUFFER_DAMAGE_COUNT]);
		}
	}
}

static void
output_rotate_damage(struct weston_output *output,
		     pixman_region32_t *output_damage,
		     enum gl_border_status border_status)
{
	struct gl_output_state *go = get_output_state(output);
	struct gl_renderer *gr = get_renderer(output->compositor);

	if (!gr->has_egl_buffer_age)
		return;

	go->buffer_damage_index += BUFFER_DAMAGE_COUNT - 1;
	go->buffer_damage_index %= BUFFER_DAMAGE_COUNT;

	pixman_region32_copy(&go->buffer_damage[go->buffer_damage_index], output_damage);
	go->border_damage[go->buffer_damage_index] = border_status;
}

/* NOTE: We now allow falling back to ARGB gl visuals when XRGB is
 * unavailable, so we're assuming the background has no transparency
 * and that everything with a blend, like drop shadows, will have something
 * opaque (like the background) drawn underneath it.
 *
 * Depending on the underlying hardware, violating that assumption could
 * result in seeing through to another display plane.
 */
static void
gl_renderer_repaint_output(struct weston_output *output,
			      pixman_region32_t *output_damage)
{
	struct gl_output_state *go = get_output_state(output);
	struct weston_compositor *compositor = output->compositor;
	struct gl_renderer *gr = get_renderer(compositor);
	EGLBoolean ret;
	static int errored;
	int i, nrects, buffer_height;
	EGLint *egl_damage, *d;
	pixman_box32_t *rects;
	pixman_region32_t buffer_damage, total_damage;
	enum gl_border_status border_damage = BORDER_STATUS_CLEAN;
//HISILICON add begin
//tag, support hwc compose
    int hwc_compositor_surpport = 0;
//HISILICON add end

	if (use_output(output) < 0)
		return;

	/* Calculate the viewport */
	glViewport(go->borders[GL_RENDERER_BORDER_LEFT].width,
		   go->borders[GL_RENDERER_BORDER_BOTTOM].height,
		   output->current_mode->width,
		   output->current_mode->height);

	/* Calculate the global GL matrix */
	go->output_matrix = output->matrix;
	weston_matrix_translate(&go->output_matrix,
				-(output->current_mode->width / 2.0),
				-(output->current_mode->height / 2.0), 0);
	weston_matrix_scale(&go->output_matrix,
			    2.0 / output->current_mode->width,
			    -2.0 / output->current_mode->height, 1);

	/* if debugging, redraw everything outside the damage to clean up
	 * debug lines from the previous draw on this buffer:
	 */
	if (gr->fan_debug) {
		pixman_region32_t undamaged;
		pixman_region32_init(&undamaged);
		pixman_region32_subtract(&undamaged, &output->region,
					 output_damage);
		gr->fan_debug = 0;
		repaint_views(output, &undamaged);
		gr->fan_debug = 1;
		pixman_region32_fini(&undamaged);
	}

	pixman_region32_init(&total_damage);
	pixman_region32_init(&buffer_damage);

	output_get_damage(output, &buffer_damage, &border_damage);
	output_rotate_damage(output, output_damage, go->border_status);

	pixman_region32_union(&total_damage, &buffer_damage, output_damage);
	border_damage |= go->border_status;

	repaint_views(output, &total_damage);

	pixman_region32_fini(&total_damage);
	pixman_region32_fini(&buffer_damage);

	draw_output_borders(output, border_damage);

	pixman_region32_copy(&output->previous_damage, output_damage);
	wl_signal_emit(&output->frame_signal, output);

	if (gr->swap_buffers_with_damage) {
		pixman_region32_init(&buffer_damage);
		weston_transformed_region(output->width, output->height,
					  output->transform,
					  output->current_scale,
					  output_damage, &buffer_damage);

		if (output_has_borders(output)) {
			pixman_region32_translate(&buffer_damage,
						  go->borders[GL_RENDERER_BORDER_LEFT].width,
						  go->borders[GL_RENDERER_BORDER_TOP].height);
			output_get_border_damage(output, go->border_status,
						 &buffer_damage);
		}

		rects = pixman_region32_rectangles(&buffer_damage, &nrects);
		egl_damage = malloc(nrects * 4 * sizeof(EGLint));

		buffer_height = go->borders[GL_RENDERER_BORDER_TOP].height +
				output->current_mode->height +
				go->borders[GL_RENDERER_BORDER_BOTTOM].height;

		d = egl_damage;
		for (i = 0; i < nrects; ++i) {
			*d++ = rects[i].x1;
			*d++ = buffer_height - rects[i].y2;
			*d++ = rects[i].x2 - rects[i].x1;
			*d++ = rects[i].y2 - rects[i].y1;
		}
//HISILICON add begin
//tag, support hwc compose
        if (!gs_hwc_compositor_surpport)
//HISILICON add end
        {
     		ret = gr->swap_buffers_with_damage(gr->egl_display,
     						   go->egl_surface,
     						   egl_damage, nrects);
        }
        gs_hwc_compositor_surpport = 0;

		free(egl_damage);
		pixman_region32_fini(&buffer_damage);
	} else {
		ret = eglSwapBuffers(gr->egl_display, go->egl_surface);
	}

	if (ret == EGL_FALSE && !errored) {
		errored = 1;
		weston_log("Failed in eglSwapBuffers.\n");
		gl_renderer_print_egl_error_state();
	}

	go->border_status = BORDER_STATUS_CLEAN;
}

static int
gl_renderer_read_pixels(struct weston_output *output,
			       pixman_format_code_t format, void *pixels,
			       uint32_t x, uint32_t y,
			       uint32_t width, uint32_t height)
{
	GLenum gl_format;
	struct gl_output_state *go = get_output_state(output);
    fprintf(stderr,"+++++++++++%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);

	x += go->borders[GL_RENDERER_BORDER_LEFT].width;
	y += go->borders[GL_RENDERER_BORDER_BOTTOM].height;

	switch (format) {
	case PIXMAN_a8r8g8b8:
		gl_format = GL_BGRA_EXT;
		break;
	case PIXMAN_a8b8g8r8:
		gl_format = GL_RGBA;
		break;
	default:
		return -1;
	}

	if (use_output(output) < 0)
		return -1;

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(x, y, width, height, gl_format,
		     GL_UNSIGNED_BYTE, pixels);

	return 0;
}

static void
gl_renderer_flush_damage(struct weston_surface *surface)
{
	struct gl_renderer *gr = get_renderer(surface->compositor);
	struct gl_surface_state *gs = get_surface_state(surface);
	struct weston_buffer *buffer = gs->buffer_ref.buffer;
	struct weston_view *view;
	bool texture_used;
	pixman_box32_t *rectangles;
	uint8_t *data;
	int i, j, n;

	pixman_region32_union(&gs->texture_damage,
			      &gs->texture_damage, &surface->damage);

	if (!buffer)
		return;

//HISILICON add begin
//tag, support hwc compose
    if (gs->hwcompose_support)
    {
        gs_hwc_renderer->flush_damage(gs->hwc_renderer_surface);
    }
//HISILICON add end

	/* Avoid upload, if the texture won't be used this time.
	 * We still accumulate the damage in texture_damage, and
	 * hold the reference to the buffer, in case the surface
	 * migrates back to the primary plane.
	 */
	texture_used = false;
	wl_list_for_each(view, &surface->views, surface_link) {
		if (view->plane == &surface->compositor->primary_plane) {
			texture_used = true;
			break;
		}
	}
	if (!texture_used)
		return;

	if (!pixman_region32_not_empty(&gs->texture_damage) &&
	    !gs->needs_full_upload)
		goto done;

	data = wl_shm_buffer_get_data(buffer->shm_buffer);

	if (!gr->has_unpack_subimage) {
		wl_shm_buffer_begin_access(buffer->shm_buffer);
		for (j = 0; j < gs->num_textures; j++) {
			glBindTexture(GL_TEXTURE_2D, gs->textures[j]);
			glTexImage2D(GL_TEXTURE_2D, 0,
				     gs->gl_format[j],
				     gs->pitch / gs->hsub[j],
				     buffer->height / gs->vsub[j],
				     0,
				     gs->gl_format[j],
				     gs->gl_pixel_type,
				     data + gs->offset[j]);
		}
		wl_shm_buffer_end_access(buffer->shm_buffer);

		goto done;
	}

	glPixelStorei(GL_UNPACK_ROW_LENGTH_EXT, gs->pitch);

	if (gs->needs_full_upload) {
		glPixelStorei(GL_UNPACK_SKIP_PIXELS_EXT, 0);
		glPixelStorei(GL_UNPACK_SKIP_ROWS_EXT, 0);
		wl_shm_buffer_begin_access(buffer->shm_buffer);
		for (j = 0; j < gs->num_textures; j++) {
			glBindTexture(GL_TEXTURE_2D, gs->textures[j]);
			glTexImage2D(GL_TEXTURE_2D, 0,
				     gs->gl_format[j],
				     gs->pitch / gs->hsub[j],
				     buffer->height / gs->vsub[j],
				     0,
				     gs->gl_format[j],
				     gs->gl_pixel_type,
				     data + gs->offset[j]);
		}
		wl_shm_buffer_end_access(buffer->shm_buffer);
		goto done;
	}

	rectangles = pixman_region32_rectangles(&gs->texture_damage, &n);
	wl_shm_buffer_begin_access(buffer->shm_buffer);
	for (i = 0; i < n; i++) {
		pixman_box32_t r;

		r = weston_surface_to_buffer_rect(surface, rectangles[i]);

		glPixelStorei(GL_UNPACK_SKIP_PIXELS_EXT, r.x1);
		glPixelStorei(GL_UNPACK_SKIP_ROWS_EXT, r.y1);
		for (j = 0; j < gs->num_textures; j++) {
			glBindTexture(GL_TEXTURE_2D, gs->textures[j]);
			glTexSubImage2D(GL_TEXTURE_2D, 0,
					r.x1 / gs->hsub[j],
					r.y1 / gs->vsub[j],
					(r.x2 - r.x1) / gs->hsub[j],
					(r.y2 - r.y1) / gs->vsub[j],
					gs->gl_format[j],
					gs->gl_pixel_type,
					data + gs->offset[j]);
		}
	}
	wl_shm_buffer_end_access(buffer->shm_buffer);

done:
	pixman_region32_fini(&gs->texture_damage);
	pixman_region32_init(&gs->texture_damage);
	gs->needs_full_upload = false;

	weston_buffer_reference(&gs->buffer_ref, NULL);
}

static void
ensure_textures(struct gl_surface_state *gs, int num_textures)
{
	int i;

	if (num_textures <= gs->num_textures)
		return;

	for (i = gs->num_textures; i < num_textures; i++) {
		glGenTextures(1, &gs->textures[i]);
		glBindTexture(gs->target, gs->textures[i]);
		glTexParameteri(gs->target,
				GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(gs->target,
				GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	gs->num_textures = num_textures;
	glBindTexture(gs->target, 0);
}

static void
gl_renderer_attach_shm(struct weston_surface *es, struct weston_buffer *buffer,
		       struct wl_shm_buffer *shm_buffer)
{
	struct weston_compositor *ec = es->compositor;
	struct gl_renderer *gr = get_renderer(ec);
	struct gl_surface_state *gs = get_surface_state(es);
	GLenum gl_format[3] = {0, 0, 0};
	GLenum gl_pixel_type;
	int pitch;
	int num_planes;

	buffer->shm_buffer = shm_buffer;
	buffer->width = wl_shm_buffer_get_width(shm_buffer);
	buffer->height = wl_shm_buffer_get_height(shm_buffer);

	num_planes = 1;
	gs->offset[0] = 0;
	gs->hsub[0] = 1;
	gs->vsub[0] = 1;

	switch (wl_shm_buffer_get_format(shm_buffer)) {
	case WL_SHM_FORMAT_XRGB8888:
		gs->shader = &gr->texture_shader_rgbx;
		pitch = wl_shm_buffer_get_stride(shm_buffer) / 4;
		gl_format[0] = GL_BGRA_EXT;
		gl_pixel_type = GL_UNSIGNED_BYTE;
		break;
	case WL_SHM_FORMAT_ARGB8888:
		gs->shader = &gr->texture_shader_rgba;
		pitch = wl_shm_buffer_get_stride(shm_buffer) / 4;
		gl_format[0] = GL_BGRA_EXT;
		gl_pixel_type = GL_UNSIGNED_BYTE;
		break;
	case WL_SHM_FORMAT_RGB565:
		gs->shader = &gr->texture_shader_rgbx;
		pitch = wl_shm_buffer_get_stride(shm_buffer) / 2;
		gl_format[0] = GL_RGB;
		gl_pixel_type = GL_UNSIGNED_SHORT_5_6_5;
		break;
	case WL_SHM_FORMAT_YUV420:
		gs->shader = &gr->texture_shader_y_u_v;
		pitch = wl_shm_buffer_get_stride(shm_buffer);
		gl_pixel_type = GL_UNSIGNED_BYTE;
		num_planes = 3;
		gs->offset[1] = gs->offset[0] + (pitch / gs->hsub[0]) *
				(buffer->height / gs->vsub[0]);
		gs->hsub[1] = 2;
		gs->vsub[1] = 2;
		gs->offset[2] = gs->offset[1] + (pitch / gs->hsub[1]) *
				(buffer->height / gs->vsub[1]);
		gs->hsub[2] = 2;
		gs->vsub[2] = 2;
		if (gr->has_gl_texture_rg) {
			gl_format[0] = GL_R8_EXT;
			gl_format[1] = GL_R8_EXT;
			gl_format[2] = GL_R8_EXT;
		} else {
			gl_format[0] = GL_LUMINANCE;
			gl_format[1] = GL_LUMINANCE;
			gl_format[2] = GL_LUMINANCE;
		}
		break;
	case WL_SHM_FORMAT_NV12:
		gs->shader = &gr->texture_shader_y_xuxv;
		pitch = wl_shm_buffer_get_stride(shm_buffer);
		gl_pixel_type = GL_UNSIGNED_BYTE;
		num_planes = 2;
		gs->offset[1] = gs->offset[0] + (pitch / gs->hsub[0]) *
				(buffer->height / gs->vsub[0]);
		gs->hsub[1] = 2;
		gs->vsub[1] = 2;
		if (gr->has_gl_texture_rg) {
			gl_format[0] = GL_R8_EXT;
			gl_format[1] = GL_RG8_EXT;
		} else {
			gl_format[0] = GL_LUMINANCE;
			gl_format[1] = GL_LUMINANCE_ALPHA;
		}
		break;
	case WL_SHM_FORMAT_YUYV:
		gs->shader = &gr->texture_shader_y_xuxv;
		pitch = wl_shm_buffer_get_stride(shm_buffer) / 2;
		gl_pixel_type = GL_UNSIGNED_BYTE;
		num_planes = 2;
		gs->hsub[1] = 2;
		gs->vsub[1] = 1;
		if (gr->has_gl_texture_rg)
			gl_format[0] = GL_RG8_EXT;
		else
			gl_format[0] = GL_LUMINANCE_ALPHA;
		gl_format[1] = GL_BGRA_EXT;
		break;
	default:
		weston_log("warning: unknown shm buffer format: %08x\n",
			   wl_shm_buffer_get_format(shm_buffer));
		return;
	}

	/* Only allocate a texture if it doesn't match existing one.
	 * If a switch from DRM allocated buffer to a SHM buffer is
	 * happening, we need to allocate a new texture buffer. */
	if (pitch != gs->pitch ||
	    buffer->height != gs->height ||
	    gl_format[0] != gs->gl_format[0] ||
	    gl_format[1] != gs->gl_format[1] ||
	    gl_format[2] != gs->gl_format[2] ||
	    gl_pixel_type != gs->gl_pixel_type ||
	    gs->buffer_type != BUFFER_TYPE_SHM) {
		gs->pitch = pitch;
		gs->height = buffer->height;
		gs->target = GL_TEXTURE_2D;
		gs->gl_format[0] = gl_format[0];
		gs->gl_format[1] = gl_format[1];
		gs->gl_format[2] = gl_format[2];
		gs->gl_pixel_type = gl_pixel_type;
		gs->buffer_type = BUFFER_TYPE_SHM;
		gs->needs_full_upload = true;
		gs->y_inverted = 1;

		gs->surface = es;

		ensure_textures(gs, num_planes);
	}
}

static void
gl_renderer_attach_egl(struct weston_surface *es, struct weston_buffer *buffer,
		       uint32_t format)
{
	struct weston_compositor *ec = es->compositor;
	struct gl_renderer *gr = get_renderer(ec);
	struct gl_surface_state *gs = get_surface_state(es);
	EGLint attribs[3];
	int i, num_planes;

	buffer->legacy_buffer = (struct wl_buffer *)buffer->resource;
	gr->query_buffer(gr->egl_display, buffer->legacy_buffer,
			 EGL_WIDTH, &buffer->width);
	gr->query_buffer(gr->egl_display, buffer->legacy_buffer,
			 EGL_HEIGHT, &buffer->height);
	gr->query_buffer(gr->egl_display, buffer->legacy_buffer,
			 EGL_WAYLAND_Y_INVERTED_WL, &buffer->y_inverted);
#if 0
	for (i = 0; i < gs->num_images; i++) {
		egl_image_unref(gs->images[i]);
		gs->images[i] = NULL;
	}
#endif
	gs->num_images = 0;
	gs->target = GL_TEXTURE_2D;
	switch (format) {
	case EGL_TEXTURE_RGB:
	case EGL_TEXTURE_RGBA:
	default:
		num_planes = 1;
		gs->shader = &gr->texture_shader_rgba;
		break;
	case EGL_TEXTURE_EXTERNAL_WL:
		num_planes = 1;
		gs->target = GL_TEXTURE_EXTERNAL_OES;
		gs->shader = &gr->texture_shader_egl_external;
		break;
	case EGL_TEXTURE_Y_UV_WL:
		num_planes = 2;
		gs->shader = &gr->texture_shader_y_uv;
		break;
	case EGL_TEXTURE_Y_U_V_WL:
		num_planes = 3;
		gs->shader = &gr->texture_shader_y_u_v;
		break;
	case EGL_TEXTURE_Y_XUXV_WL:
		num_planes = 2;
		gs->shader = &gr->texture_shader_y_xuxv;
		break;
	}

	ensure_textures(gs, num_planes);
	for (i = 0; i < num_planes; i++) {
		attribs[0] = EGL_WAYLAND_PLANE_WL;
		attribs[1] = i;
		attribs[2] = EGL_NONE;

        if (NULL == gs->images[i])
        {
     		gs->images[i] = egl_image_create(gr,
     						 EGL_WAYLAND_BUFFER_WL,
     						 buffer->legacy_buffer,
     						 attribs);
        }
		if (!gs->images[i]) {
			weston_log("failed to create img for plane %d\n", i);
			continue;
		}
		gs->num_images++;

		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(gs->target, gs->textures[i]);
		gr->image_target_texture_2d(gs->target,
					    gs->images[i]->image);
	}

	gs->pitch = buffer->width;
	gs->height = buffer->height;
	gs->buffer_type = BUFFER_TYPE_EGL;
	gs->y_inverted = buffer->y_inverted;
}

static void
gl_renderer_destroy_dmabuf(struct linux_dmabuf_buffer *dmabuf)
{
	struct dmabuf_image *image = dmabuf->user_data;

	dmabuf_image_destroy(image);
}

static struct egl_image *
import_simple_dmabuf(struct gl_renderer *gr,
                     struct dmabuf_attributes *attributes)
{
	struct egl_image *image;
	EGLint attribs[50];
	int atti = 0;

	/* This requires the Mesa commit in
	 * Mesa 10.3 (08264e5dad4df448e7718e782ad9077902089a07) or
	 * Mesa 10.2.7 (55d28925e6109a4afd61f109e845a8a51bd17652).
	 * Otherwise Mesa closes the fd behind our back and re-importing
	 * will fail.
	 * https://bugs.freedesktop.org/show_bug.cgi?id=76188
	 */

	attribs[atti++] = EGL_WIDTH;
	attribs[atti++] = attributes->width;
	attribs[atti++] = EGL_HEIGHT;
	attribs[atti++] = attributes->height;
	attribs[atti++] = EGL_LINUX_DRM_FOURCC_EXT;
	attribs[atti++] = attributes->format;

	if (attributes->n_planes > 0) {
		attribs[atti++] = EGL_DMA_BUF_PLANE0_FD_EXT;
		attribs[atti++] = attributes->fd[0];
		attribs[atti++] = EGL_DMA_BUF_PLANE0_OFFSET_EXT;
		attribs[atti++] = attributes->offset[0];
		attribs[atti++] = EGL_DMA_BUF_PLANE0_PITCH_EXT;
		attribs[atti++] = attributes->stride[0];
		if (gr->has_dmabuf_import_modifiers) {
			attribs[atti++] = EGL_DMA_BUF_PLANE0_MODIFIER_LO_EXT;
			attribs[atti++] = attributes->modifier[0] & 0xFFFFFFFF;
			attribs[atti++] = EGL_DMA_BUF_PLANE0_MODIFIER_HI_EXT;
			attribs[atti++] = attributes->modifier[0] >> 32;
		}
	}

	if (attributes->n_planes > 1) {
		attribs[atti++] = EGL_DMA_BUF_PLANE1_FD_EXT;
		attribs[atti++] = attributes->fd[1];
		attribs[atti++] = EGL_DMA_BUF_PLANE1_OFFSET_EXT;
		attribs[atti++] = attributes->offset[1];
		attribs[atti++] = EGL_DMA_BUF_PLANE1_PITCH_EXT;
		attribs[atti++] = attributes->stride[1];
		if (gr->has_dmabuf_import_modifiers) {
			attribs[atti++] = EGL_DMA_BUF_PLANE1_MODIFIER_LO_EXT;
			attribs[atti++] = attributes->modifier[1] & 0xFFFFFFFF;
			attribs[atti++] = EGL_DMA_BUF_PLANE1_MODIFIER_HI_EXT;
			attribs[atti++] = attributes->modifier[1] >> 32;
		}
	}

	if (attributes->n_planes > 2) {
		attribs[atti++] = EGL_DMA_BUF_PLANE2_FD_EXT;
		attribs[atti++] = attributes->fd[2];
		attribs[atti++] = EGL_DMA_BUF_PLANE2_OFFSET_EXT;
		attribs[atti++] = attributes->offset[2];
		attribs[atti++] = EGL_DMA_BUF_PLANE2_PITCH_EXT;
		attribs[atti++] = attributes->stride[2];
		if (gr->has_dmabuf_import_modifiers) {
			attribs[atti++] = EGL_DMA_BUF_PLANE2_MODIFIER_LO_EXT;
			attribs[atti++] = attributes->modifier[2] & 0xFFFFFFFF;
			attribs[atti++] = EGL_DMA_BUF_PLANE2_MODIFIER_HI_EXT;
			attribs[atti++] = attributes->modifier[2] >> 32;
		}
	}

	if (gr->has_dmabuf_import_modifiers) {
		if (attributes->n_planes > 3) {
			attribs[atti++] = EGL_DMA_BUF_PLANE3_FD_EXT;
			attribs[atti++] = attributes->fd[3];
			attribs[atti++] = EGL_DMA_BUF_PLANE3_OFFSET_EXT;
			attribs[atti++] = attributes->offset[3];
			attribs[atti++] = EGL_DMA_BUF_PLANE3_PITCH_EXT;
			attribs[atti++] = attributes->stride[3];
			attribs[atti++] = EGL_DMA_BUF_PLANE3_MODIFIER_LO_EXT;
			attribs[atti++] = attributes->modifier[3] & 0xFFFFFFFF;
			attribs[atti++] = EGL_DMA_BUF_PLANE3_MODIFIER_HI_EXT;
			attribs[atti++] = attributes->modifier[3] >> 32;
		}
	}

	attribs[atti++] = EGL_NONE;

    fprintf(stderr,"++++++++++++%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
	image = egl_image_create(gr, EGL_LINUX_DMA_BUF_EXT, NULL,
				 attribs);

	return image;
}

/* The kernel header drm_fourcc.h defines the DRM formats below.  We duplicate
 * some of the definitions here so that building Weston won't require
 * bleeding-edge kernel headers.
 */
#ifndef DRM_FORMAT_R8
#define DRM_FORMAT_R8            fourcc_code('R', '8', ' ', ' ') /* [7:0] R */
#endif

#ifndef DRM_FORMAT_GR88
#define DRM_FORMAT_GR88          fourcc_code('G', 'R', '8', '8') /* [15:0] G:R 8:8 little endian */
#endif

struct yuv_format_descriptor yuv_formats[] = {
	{
		.format = DRM_FORMAT_YUYV,
		.input_planes = 1,
		.output_planes = 2,
		.texture_type = EGL_TEXTURE_Y_XUXV_WL,
		{{
			.width_divisor = 1,
			.height_divisor = 1,
			.format = DRM_FORMAT_GR88,
			.plane_index = 0
		}, {
			.width_divisor = 2,
			.height_divisor = 1,
			.format = DRM_FORMAT_ARGB8888,
			.plane_index = 0
		}}
	}, {
		.format = DRM_FORMAT_NV12,
		.input_planes = 2,
		.output_planes = 2,
		.texture_type = EGL_TEXTURE_Y_UV_WL,
		{{
			.width_divisor = 1,
			.height_divisor = 1,
			.format = DRM_FORMAT_R8,
			.plane_index = 0
		}, {
			.width_divisor = 2,
			.height_divisor = 2,
			.format = DRM_FORMAT_GR88,
			.plane_index = 1
		}}
	}, {
		.format = DRM_FORMAT_YUV420,
		.input_planes = 3,
		.output_planes = 3,
		.texture_type = EGL_TEXTURE_Y_U_V_WL,
		{{
			.width_divisor = 1,
			.height_divisor = 1,
			.format = DRM_FORMAT_R8,
			.plane_index = 0
		}, {
			.width_divisor = 2,
			.height_divisor = 2,
			.format = DRM_FORMAT_R8,
			.plane_index = 1
		}, {
			.width_divisor = 2,
			.height_divisor = 2,
			.format = DRM_FORMAT_R8,
			.plane_index = 2
		}}
	}, {
		.format = DRM_FORMAT_YUV444,
		.input_planes = 3,
		.output_planes = 3,
		.texture_type = EGL_TEXTURE_Y_U_V_WL,
		{{
			.width_divisor = 1,
			.height_divisor = 1,
			.format = DRM_FORMAT_R8,
			.plane_index = 0
		}, {
			.width_divisor = 1,
			.height_divisor = 1,
			.format = DRM_FORMAT_R8,
			.plane_index = 1
		}, {
			.width_divisor = 1,
			.height_divisor = 1,
			.format = DRM_FORMAT_R8,
			.plane_index = 2
		}}
	}
};

static struct egl_image *
import_dmabuf_single_plane(struct gl_renderer *gr,
                           const struct dmabuf_attributes *attributes,
                           struct yuv_plane_descriptor *descriptor)
{
	struct dmabuf_attributes plane;
	struct egl_image *image;
	char fmt[4];

	plane.width = attributes->width / descriptor->width_divisor;
	plane.height = attributes->height / descriptor->height_divisor;
	plane.format = descriptor->format;
	plane.n_planes = 1;
	plane.fd[0] = attributes->fd[descriptor->plane_index];
	plane.offset[0] = attributes->offset[descriptor->plane_index];
	plane.stride[0] = attributes->stride[descriptor->plane_index];
	plane.modifier[0] = attributes->modifier[descriptor->plane_index];

	image = import_simple_dmabuf(gr, &plane);
	if (!image) {
		weston_log("Failed to import plane %d as %.4s\n",
		           descriptor->plane_index,
		           dump_format(descriptor->format, fmt));
		return NULL;
	}

	return image;
}

static bool
import_yuv_dmabuf(struct gl_renderer *gr,
                  struct dmabuf_image *image)
{
	unsigned i;
	int j;
	int ret;
	struct yuv_format_descriptor *format = NULL;
	struct dmabuf_attributes *attributes = &image->dmabuf->attributes;
	char fmt[4];

	for (i = 0; i < ARRAY_LENGTH(yuv_formats); ++i) {
		if (yuv_formats[i].format == attributes->format) {
			format = &yuv_formats[i];
			break;
		}
	}

	if (!format) {
		weston_log("Error during import, and no known conversion for format "
		           "%.4s in the renderer\n",
		           dump_format(attributes->format, fmt));
		return false;
	}

	if (attributes->n_planes != format->input_planes) {
		weston_log("%.4s dmabuf must contain %d plane%s (%d provided)\n",
		           dump_format(format->format, fmt),
		           format->input_planes,
		           (format->input_planes > 1) ? "s" : "",
		           attributes->n_planes);
		return false;
	}

	for (j = 0; j < format->output_planes; ++j) {
		image->images[j] = import_dmabuf_single_plane(gr, attributes,
		                                              &format->plane[j]);
		if (!image->images[j]) {
			while (j) {
				ret = egl_image_unref(image->images[--j]);
				assert(ret == 0);
			}
			return false;
		}
	}

	image->num_images = format->output_planes;

	switch (format->texture_type) {
	case EGL_TEXTURE_Y_XUXV_WL:
		image->shader = &gr->texture_shader_y_xuxv;
		break;
	case EGL_TEXTURE_Y_UV_WL:
		image->shader = &gr->texture_shader_y_uv;
		break;
	case EGL_TEXTURE_Y_U_V_WL:
		image->shader = &gr->texture_shader_y_u_v;
		break;
	default:
		assert(false);
	}

	return true;
}

static GLenum
choose_texture_target(struct dmabuf_attributes *attributes)
{
	if (attributes->n_planes > 1)
		return GL_TEXTURE_EXTERNAL_OES;

	switch (attributes->format & ~DRM_FORMAT_BIG_ENDIAN) {
	case DRM_FORMAT_YUYV:
	case DRM_FORMAT_YVYU:
	case DRM_FORMAT_UYVY:
	case DRM_FORMAT_VYUY:
	case DRM_FORMAT_AYUV:
		return GL_TEXTURE_EXTERNAL_OES;
	default:
		return GL_TEXTURE_2D;
	}
}

static struct dmabuf_image *
import_dmabuf(struct gl_renderer *gr,
	      struct linux_dmabuf_buffer *dmabuf)
{
	struct egl_image *egl_image;
	struct dmabuf_image *image;

	image = dmabuf_image_create();
	image->dmabuf = dmabuf;

	egl_image = import_simple_dmabuf(gr, &dmabuf->attributes);
	if (egl_image) {
		image->num_images = 1;
		image->images[0] = egl_image;
		image->import_type = IMPORT_TYPE_DIRECT;
		image->target = choose_texture_target(&dmabuf->attributes);

		switch (image->target) {
		case GL_TEXTURE_2D:
			image->shader = &gr->texture_shader_rgba;
			break;
		default:
			image->shader = &gr->texture_shader_egl_external;
		}
	} else {
		if (!import_yuv_dmabuf(gr, image)) {
			dmabuf_image_destroy(image);
			return NULL;
		}
		image->import_type = IMPORT_TYPE_GL_CONVERSION;
		image->target = GL_TEXTURE_2D;
	}

	return image;
}

static bool
gl_renderer_query_dmabuf_formats(struct weston_compositor *wc,
				int **formats, int *num_formats)
{
	struct gl_renderer *gr = get_renderer(wc);
	EGLint num;

	assert(gr->has_dmabuf_import);

	if (!gr->has_dmabuf_import_modifiers ||
	    !gr->query_dmabuf_formats(gr->egl_display, 0, NULL, &num)) {
		*num_formats = 0;
		return false;
	}

	*formats = calloc(num, sizeof(int));
	if (*formats == NULL) {
		*num_formats = 0;
		return false;
	}
	if (!gr->query_dmabuf_formats(gr->egl_display, num, *formats,
			(EGLint*) &num)) {
		*num_formats = 0;
		free(*formats);
		return false;
	}

	*num_formats = num;
	return true;
}

static bool
gl_renderer_query_dmabuf_modifiers(struct weston_compositor *wc, int format,
					uint64_t **modifiers,
					int *num_modifiers)
{
	struct gl_renderer *gr = get_renderer(wc);
	int num;

	assert(gr->has_dmabuf_import);

	if (!gr->has_dmabuf_import_modifiers ||
		!gr->query_dmabuf_modifiers(gr->egl_display, format, 0, NULL,
					    NULL, &num)) {
		*num_modifiers = 0;
		return false;
	}

	*modifiers = calloc(num, sizeof(uint64_t));
	if (*modifiers == NULL) {
		*num_modifiers = 0;
		return false;
	}
	if (!gr->query_dmabuf_modifiers(gr->egl_display, format,
				num, *modifiers, NULL, &num)) {
		*num_modifiers = 0;
		free(*modifiers);
		return false;
	}

	*num_modifiers = num;
	return true;
}

static bool
gl_renderer_import_dmabuf(struct weston_compositor *ec,
			  struct linux_dmabuf_buffer *dmabuf)
{
	struct gl_renderer *gr = get_renderer(ec);
	struct dmabuf_image *image;
	int i;

	assert(gr->has_dmabuf_import);

	for (i = 0; i < dmabuf->attributes.n_planes; i++) {
		/* return if EGL doesn't support import modifiers */
		if (dmabuf->attributes.modifier[i] != 0)
			if (!gr->has_dmabuf_import_modifiers)
				return false;

		/* return if modifiers passed are unequal */
		if (dmabuf->attributes.modifier[i] !=
		    dmabuf->attributes.modifier[0])
			return false;
	}

	/* reject all flags we do not recognize or handle */
	if (dmabuf->attributes.flags & ~ZWP_LINUX_BUFFER_PARAMS_V1_FLAGS_Y_INVERT)
		return false;

	image = import_dmabuf(gr, dmabuf);
	if (!image)
		return false;

	wl_list_insert(&gr->dmabuf_images, &image->link);
	linux_dmabuf_buffer_set_user_data(dmabuf, image,
		gl_renderer_destroy_dmabuf);

	return true;
}

static bool
import_known_dmabuf(struct gl_renderer *gr,
                    struct dmabuf_image *image)
{
	switch (image->import_type) {
	case IMPORT_TYPE_DIRECT:
		image->images[0] = import_simple_dmabuf(gr, &image->dmabuf->attributes);
		if (!image->images[0])
			return false;
		break;

	case IMPORT_TYPE_GL_CONVERSION:
		if (!import_yuv_dmabuf(gr, image))
			return false;
		break;

	default:
		weston_log("Invalid import type for dmabuf\n");
		return false;
	}

	return true;
}

static void
gl_renderer_attach_dmabuf(struct weston_surface *surface,
			  struct weston_buffer *buffer,
			  struct linux_dmabuf_buffer *dmabuf)
{
	struct gl_renderer *gr = get_renderer(surface->compositor);
	struct gl_surface_state *gs = get_surface_state(surface);
	struct dmabuf_image *image;
	int i;
	int ret;

	if (!gr->has_dmabuf_import) {
		linux_dmabuf_buffer_send_server_error(dmabuf,
				"EGL dmabuf import not supported");
		return;
	}

	buffer->width = dmabuf->attributes.width;
	buffer->height = dmabuf->attributes.height;

	/*
	 * GL-renderer uses the OpenGL convention of texture coordinates, where
	 * the origin is at bottom-left. Because dmabuf buffers have the origin
	 * at top-left, we must invert the Y_INVERT flag to get the image right.
	 */
	buffer->y_inverted =
		!(dmabuf->attributes.flags & ZWP_LINUX_BUFFER_PARAMS_V1_FLAGS_Y_INVERT);

	for (i = 0; i < gs->num_images; i++)
		egl_image_unref(gs->images[i]);
	gs->num_images = 0;

	/*
	 * We try to always hold an imported EGLImage from the dmabuf
	 * to prevent the client from preventing re-imports. But, we also
	 * need to re-import every time the contents may change because
	 * GL driver's caching may need flushing.
	 *
	 * Here we release the cache reference which has to be final.
	 */
	image = linux_dmabuf_buffer_get_user_data(dmabuf);

	/* The dmabuf_image should have been created during the import */
	assert(image != NULL);

	for (i = 0; i < image->num_images; ++i) {
		ret = egl_image_unref(image->images[i]);
		assert(ret == 0);
	}

	if (!import_known_dmabuf(gr, image)) {
		linux_dmabuf_buffer_send_server_error(dmabuf, "EGL dmabuf import failed");
		return;
	}

	gs->num_images = image->num_images;
	for (i = 0; i < gs->num_images; ++i)
		gs->images[i] = egl_image_ref(image->images[i]);

	gs->target = image->target;
	ensure_textures(gs, gs->num_images);
	for (i = 0; i < gs->num_images; ++i) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(gs->target, gs->textures[i]);
		gr->image_target_texture_2d(gs->target, gs->images[i]->image);
	}

	gs->shader = image->shader;
	gs->pitch = buffer->width;
	gs->height = buffer->height;
	gs->buffer_type = BUFFER_TYPE_EGL;
	gs->y_inverted = buffer->y_inverted;
}

//HISILICON add begin
//tag, support hwc compose
static int
gl_renderer_format_gpu_to_shm(int gl_format)
{
    int shm_format = 0;

    switch (gl_format)
    {
        case 0:
            shm_format = WL_SHM_FORMAT_RGB565;
            break;
        case 3:
            shm_format = WL_SHM_FORMAT_ARGB8888;
            break;
        default:
            break;
    }

    return shm_format;
}
//HISILICON add end

static void
gl_renderer_attach(struct weston_surface *es, struct weston_buffer *buffer)
{
	struct weston_compositor *ec = es->compositor;
	struct gl_renderer *gr = get_renderer(ec);
	struct gl_surface_state *gs = get_surface_state(es);
	struct wl_shm_buffer *shm_buffer;
	struct linux_dmabuf_buffer *dmabuf;
	EGLint format;
	int i;
//HISILICON add begin
//tag, support hwc compose
    int shm_format = 0;
    wayland_egl_buffer_info *buf_info = NULL;
//HISILICON add end

	weston_buffer_reference(&gs->buffer_ref, buffer);

//HISILICON add begin
//tag, support hwc compose
    shm_buffer = wl_shm_buffer_get(buffer->resource);
    if ((1 == gr->use_gl_hwc) && (NULL == shm_buffer))
    {/** user shm(virtual) buffer, hwcompose only support physical address **/
        buf_info = (wayland_egl_buffer_info *)wl_resource_get_user_data(buffer->resource);
        shm_format = gl_renderer_format_gpu_to_shm(buf_info->format);
        gs->hwcompose_support = gs_hwc_renderer->prepare(gs->hwc_renderer_surface,
                                                         (char*)buf_info->name,
                                                         buf_info->width,
                                                         buf_info->height,
                                                         buf_info->pitch,
                                                         shm_format);
    }
    if (gs->hwcompose_support)
    {
        gs_hwc_renderer->attach(gs->hwc_renderer_surface);
    }
//HISILICON add end

	if (!buffer) {
		for (i = 0; i < gs->num_images; i++) {
			egl_image_unref(gs->images[i]);
			gs->images[i] = NULL;
		}
		gs->num_images = 0;
		glDeleteTextures(gs->num_textures, gs->textures);
		gs->num_textures = 0;
		gs->buffer_type = BUFFER_TYPE_NULL;
		gs->y_inverted = 1;
		return;
	}

	shm_buffer = wl_shm_buffer_get(buffer->resource);

	if (shm_buffer)
		gl_renderer_attach_shm(es, buffer, shm_buffer);
	else if (gr->has_bind_display &&
		 gr->query_buffer(gr->egl_display, (void *)buffer->resource,
				  EGL_TEXTURE_FORMAT, &format))
		gl_renderer_attach_egl(es, buffer, format);
	else if ((dmabuf = linux_dmabuf_buffer_get(buffer->resource)))
		gl_renderer_attach_dmabuf(es, buffer, dmabuf);
	else {
		weston_log("unhandled buffer type!\n");
		weston_buffer_reference(&gs->buffer_ref, NULL);
		gs->buffer_type = BUFFER_TYPE_NULL;
		gs->y_inverted = 1;
	}
}

static void
gl_renderer_surface_set_color(struct weston_surface *surface,
		 float red, float green, float blue, float alpha)
{
	struct gl_surface_state *gs = get_surface_state(surface);
	struct gl_renderer *gr = get_renderer(surface->compositor);

	gs->color[0] = red;
	gs->color[1] = green;
	gs->color[2] = blue;
	gs->color[3] = alpha;
	gs->buffer_type = BUFFER_TYPE_SOLID;
	gs->pitch = 1;
	gs->height = 1;

	gs->shader = &gr->solid_shader;

//HISILICON add begin
//tag, support hwc compose
    if (gs->hwcompose_support)
    {
       gs_hwc_renderer->surface_set_color(gs->hwc_renderer_surface,surface->width,surface->height,red,green,blue,alpha);
    }
//HISILICON add end
}

static void
gl_renderer_surface_get_content_size(struct weston_surface *surface,
				     int *width, int *height)
{
	struct gl_surface_state *gs = get_surface_state(surface);
    fprintf(stderr,"+++++++++++%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);

	if (gs->buffer_type == BUFFER_TYPE_NULL) {
		*width = 0;
		*height = 0;
	} else {
		*width = gs->pitch;
		*height = gs->height;
	}
}

static uint32_t
pack_color(pixman_format_code_t format, float *c)
{
	uint8_t r = round(c[0] * 255.0f);
	uint8_t g = round(c[1] * 255.0f);
	uint8_t b = round(c[2] * 255.0f);
	uint8_t a = round(c[3] * 255.0f);

	switch (format) {
	case PIXMAN_a8b8g8r8:
		return (a << 24) | (b << 16) | (g << 8) | r;
	default:
		assert(0);
		return 0;
	}
}

static int
gl_renderer_surface_copy_content(struct weston_surface *surface,
				 void *target, size_t size,
				 int src_x, int src_y,
				 int width, int height)
{
	static const GLfloat verts[4 * 2] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};
	static const GLfloat projmat_normal[16] = { /* transpose */
		 2.0f,  0.0f, 0.0f, 0.0f,
		 0.0f,  2.0f, 0.0f, 0.0f,
		 0.0f,  0.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f, 1.0f
	};
	static const GLfloat projmat_yinvert[16] = { /* transpose */
		 2.0f,  0.0f, 0.0f, 0.0f,
		 0.0f, -2.0f, 0.0f, 0.0f,
		 0.0f,  0.0f, 1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f, 1.0f
	};
	const pixman_format_code_t format = PIXMAN_a8b8g8r8;
	const size_t bytespp = 4; /* PIXMAN_a8b8g8r8 */
	const GLenum gl_format = GL_RGBA; /* PIXMAN_a8b8g8r8 little-endian */
	struct gl_renderer *gr = get_renderer(surface->compositor);
	struct gl_surface_state *gs = get_surface_state(surface);
	int cw, ch;
	GLuint fbo;
	GLuint tex;
	GLenum status;
	const GLfloat *proj;
	int i;
    fprintf(stderr,"+++++++++++%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);

	gl_renderer_surface_get_content_size(surface, &cw, &ch);

	switch (gs->buffer_type) {
	case BUFFER_TYPE_NULL:
		return -1;
	case BUFFER_TYPE_SOLID:
		*(uint32_t *)target = pack_color(format, gs->color);
		return 0;
	case BUFFER_TYPE_SHM:
		gl_renderer_flush_damage(surface);
		/* fall through */
	case BUFFER_TYPE_EGL:
		break;
	}

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cw, ch,
		     0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			       GL_TEXTURE_2D, tex, 0);

	status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		weston_log("%s: fbo error: %#x\n", __func__, status);
		glDeleteFramebuffers(1, &fbo);
		glDeleteTextures(1, &tex);
		return -1;
	}

	glViewport(0, 0, cw, ch);
	glDisable(GL_BLEND);
	use_shader(gr, gs->shader);
	if (gs->y_inverted)
		proj = projmat_normal;
	else
		proj = projmat_yinvert;

	glUniformMatrix4fv(gs->shader->proj_uniform, 1, GL_FALSE, proj);
	glUniform1f(gs->shader->alpha_uniform, 1.0f);

	for (i = 0; i < gs->num_textures; i++) {
		glUniform1i(gs->shader->tex_uniforms[i], i);

		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(gs->target, gs->textures[i]);
		glTexParameteri(gs->target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(gs->target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	/* position: */
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, verts);
	glEnableVertexAttribArray(0);

	/* texcoord: */
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, verts);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glPixelStorei(GL_PACK_ALIGNMENT, bytespp);
	glReadPixels(src_x, src_y, width, height, gl_format,
		     GL_UNSIGNED_BYTE, target);

	glDeleteFramebuffers(1, &fbo);
	glDeleteTextures(1, &tex);

	return 0;
}

static void
surface_state_destroy(struct gl_surface_state *gs, struct gl_renderer *gr)
{
	int i;

//HISILICON add begin
//tag, support hwc compose
    if (gr->use_gl_hwc)
    {
        gs_hwc_renderer->output_surface_destory(gs->hwc_renderer_surface);
    }
//HISILICON add end

	wl_list_remove(&gs->surface_destroy_listener.link);
	wl_list_remove(&gs->renderer_destroy_listener.link);

	gs->surface->renderer_state = NULL;

	glDeleteTextures(gs->num_textures, gs->textures);

	for (i = 0; i < sizeof(gs->images) / sizeof(gs->images[0]); i++)
	{
        if (NULL != gs->images[i])
        {
           egl_image_unref(gs->images[i]);
        }
	}

	weston_buffer_reference(&gs->buffer_ref, NULL);
	pixman_region32_fini(&gs->texture_damage);
	free(gs);
}

static void
surface_state_handle_surface_destroy(struct wl_listener *listener, void *data)
{
	struct gl_surface_state *gs;
	struct gl_renderer *gr;

	gs = container_of(listener, struct gl_surface_state,
			  surface_destroy_listener);

	gr = get_renderer(gs->surface->compositor);

	surface_state_destroy(gs, gr);
}

static void
surface_state_handle_renderer_destroy(struct wl_listener *listener, void *data)
{
	struct gl_surface_state *gs;
	struct gl_renderer *gr;

	gr = data;

	gs = container_of(listener, struct gl_surface_state,
			  renderer_destroy_listener);

	surface_state_destroy(gs, gr);
}

static int
gl_renderer_create_surface(struct weston_surface *surface)
{
	struct gl_surface_state *gs;
	struct gl_renderer *gr = get_renderer(surface->compositor);
//HISILICON add begin
//tag, support hwc compose
    struct gl_surface_state *output_surface = NULL;
    struct weston_compositor *ec = surface->compositor;
//HISILICON add end

	gs = zalloc(sizeof *gs);
	if (gs == NULL)
		return -1;

	/* A buffer is never attached to solid color surfaces, yet
	 * they still go through texcoord computations. Do not divide
	 * by zero there.
	 */
	gs->pitch = 1;
	gs->y_inverted = 1;

	gs->surface = surface;

//HISILICON add begin
//tag, support hwc compose
    output_surface = (struct gl_surface_state *)gs;
    if (gr->use_gl_hwc && !output_surface->hwc_renderer_surface)
    {
        fprintf(stderr,"++++++++++++++%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
        gs_hwc_renderer->output_surface_create(&(output_surface->hwc_renderer_surface));
    }
//HISILICON add end

	pixman_region32_init(&gs->texture_damage);
	surface->renderer_state = gs;

	gs->surface_destroy_listener.notify =
		surface_state_handle_surface_destroy;
	wl_signal_add(&surface->destroy_signal,
		      &gs->surface_destroy_listener);

	gs->renderer_destroy_listener.notify =
		surface_state_handle_renderer_destroy;
	wl_signal_add(&gr->destroy_signal,
		      &gs->renderer_destroy_listener);

	if (surface->buffer_ref.buffer) {
		gl_renderer_attach(surface, surface->buffer_ref.buffer);
		gl_renderer_flush_damage(surface);
	}

	return 0;
}

static const char vertex_shader[] =
	"uniform mat4 proj;\n"
	"attribute vec2 position;\n"
	"attribute vec2 texcoord;\n"
	"varying vec2 v_texcoord;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = proj * vec4(position, 0.0, 1.0);\n"
	"   v_texcoord = texcoord;\n"
	"}\n";

/* Declare common fragment shader uniforms */
#define FRAGMENT_CONVERT_YUV						\
	"  y *= alpha;\n"						\
	"  u *= alpha;\n"						\
	"  v *= alpha;\n"						\
	"  gl_FragColor.r = y + 1.59602678 * v;\n"			\
	"  gl_FragColor.g = y - 0.39176229 * u - 0.81296764 * v;\n"	\
	"  gl_FragColor.b = y + 2.01723214 * u;\n"			\
	"  gl_FragColor.a = alpha;\n"

static const char fragment_debug[] =
	"  gl_FragColor = vec4(0.0, 0.3, 0.0, 0.2) + gl_FragColor * 0.8;\n";

static const char fragment_brace[] =
	"}\n";

static const char texture_fragment_shader_rgba[] =
	"precision mediump float;\n"
	"varying vec2 v_texcoord;\n"
	"uniform sampler2D tex;\n"
	"uniform float alpha;\n"
	"void main()\n"
	"{\n"
	"   gl_FragColor = alpha * texture2D(tex, v_texcoord)\n;"
	;

static const char texture_fragment_shader_rgbx[] =
	"precision mediump float;\n"
	"varying vec2 v_texcoord;\n"
	"uniform sampler2D tex;\n"
	"uniform float alpha;\n"
	"void main()\n"
	"{\n"
	"   gl_FragColor.rgb = alpha * texture2D(tex, v_texcoord).rgb\n;"
	"   gl_FragColor.a = alpha;\n"
	;

static const char texture_fragment_shader_egl_external[] =
	"#extension GL_OES_EGL_image_external : require\n"
	"precision mediump float;\n"
	"varying vec2 v_texcoord;\n"
	"uniform samplerExternalOES tex;\n"
	"uniform float alpha;\n"
	"void main()\n"
	"{\n"
	"   gl_FragColor = alpha * texture2D(tex, v_texcoord)\n;"
	;

static const char texture_fragment_shader_y_uv[] =
	"precision mediump float;\n"
	"uniform sampler2D tex;\n"
	"uniform sampler2D tex1;\n"
	"varying vec2 v_texcoord;\n"
	"uniform float alpha;\n"
	"void main() {\n"
	"  float y = 1.16438356 * (texture2D(tex, v_texcoord).x - 0.0625);\n"
	"  float u = texture2D(tex1, v_texcoord).r - 0.5;\n"
	"  float v = texture2D(tex1, v_texcoord).g - 0.5;\n"
	FRAGMENT_CONVERT_YUV
	;

static const char texture_fragment_shader_y_u_v[] =
	"precision mediump float;\n"
	"uniform sampler2D tex;\n"
	"uniform sampler2D tex1;\n"
	"uniform sampler2D tex2;\n"
	"varying vec2 v_texcoord;\n"
	"uniform float alpha;\n"
	"void main() {\n"
	"  float y = 1.16438356 * (texture2D(tex, v_texcoord).x - 0.0625);\n"
	"  float u = texture2D(tex1, v_texcoord).x - 0.5;\n"
	"  float v = texture2D(tex2, v_texcoord).x - 0.5;\n"
	FRAGMENT_CONVERT_YUV
	;

static const char texture_fragment_shader_y_xuxv[] =
	"precision mediump float;\n"
	"uniform sampler2D tex;\n"
	"uniform sampler2D tex1;\n"
	"varying vec2 v_texcoord;\n"
	"uniform float alpha;\n"
	"void main() {\n"
	"  float y = 1.16438356 * (texture2D(tex, v_texcoord).x - 0.0625);\n"
	"  float u = texture2D(tex1, v_texcoord).g - 0.5;\n"
	"  float v = texture2D(tex1, v_texcoord).a - 0.5;\n"
	FRAGMENT_CONVERT_YUV
	;

static const char solid_fragment_shader[] =
	"precision mediump float;\n"
	"uniform vec4 color;\n"
	"uniform float alpha;\n"
	"void main()\n"
	"{\n"
	"   gl_FragColor = alpha * color\n;"
	;

static int
compile_shader(GLenum type, int count, const char **sources)
{
	GLuint s;
	char msg[512];
	GLint status;

	s = glCreateShader(type);
	glShaderSource(s, count, sources, NULL);
	glCompileShader(s);
	glGetShaderiv(s, GL_COMPILE_STATUS, &status);
	if (!status) {
		glGetShaderInfoLog(s, sizeof msg, NULL, msg);
		weston_log("shader info: %s\n", msg);
		return GL_NONE;
	}

	return s;
}

static int
shader_init(struct gl_shader *shader, struct gl_renderer *renderer,
		   const char *vertex_source, const char *fragment_source)
{
	char msg[512];
	GLint status;
	int count;
	const char *sources[3];

	shader->vertex_shader =
		compile_shader(GL_VERTEX_SHADER, 1, &vertex_source);

	if (renderer->fragment_shader_debug) {
		sources[0] = fragment_source;
		sources[1] = fragment_debug;
		sources[2] = fragment_brace;
		count = 3;
	} else {
		sources[0] = fragment_source;
		sources[1] = fragment_brace;
		count = 2;
	}

	shader->fragment_shader =
		compile_shader(GL_FRAGMENT_SHADER, count, sources);

	shader->program = glCreateProgram();
	glAttachShader(shader->program, shader->vertex_shader);
	glAttachShader(shader->program, shader->fragment_shader);
	glBindAttribLocation(shader->program, 0, "position");
	glBindAttribLocation(shader->program, 1, "texcoord");

	glLinkProgram(shader->program);
	glGetProgramiv(shader->program, GL_LINK_STATUS, &status);
	if (!status) {
		glGetProgramInfoLog(shader->program, sizeof msg, NULL, msg);
		weston_log("link info: %s\n", msg);
		return -1;
	}

	shader->proj_uniform = glGetUniformLocation(shader->program, "proj");
	shader->tex_uniforms[0] = glGetUniformLocation(shader->program, "tex");
	shader->tex_uniforms[1] = glGetUniformLocation(shader->program, "tex1");
	shader->tex_uniforms[2] = glGetUniformLocation(shader->program, "tex2");
	shader->alpha_uniform = glGetUniformLocation(shader->program, "alpha");
	shader->color_uniform = glGetUniformLocation(shader->program, "color");

	return 0;
}

static void
shader_release(struct gl_shader *shader)
{
	glDeleteShader(shader->vertex_shader);
	glDeleteShader(shader->fragment_shader);
	glDeleteProgram(shader->program);

	shader->vertex_shader = 0;
	shader->fragment_shader = 0;
	shader->program = 0;
}

static void
log_extensions(const char *name, const char *extensions)
{
	const char *p, *end;
	int l;
	int len;

	l = weston_log("%s:", name);
	p = extensions;
	while (*p) {
		end = strchrnul(p, ' ');
		len = end - p;
		if (l + len > 78)
			l = weston_log_continue("\n" STAMP_SPACE "%.*s",
						len, p);
		else
			l += weston_log_continue(" %.*s", len, p);
		for (p = end; isspace(*p); p++)
			;
	}
	weston_log_continue("\n");
}

static void
log_egl_gl_info(EGLDisplay egldpy)
{
	const char *str;

	str = eglQueryString(egldpy, EGL_VERSION);
	weston_log("EGL version: %s\n", str ? str : "(null)");

	str = eglQueryString(egldpy, EGL_VENDOR);
	weston_log("EGL vendor: %s\n", str ? str : "(null)");

	str = eglQueryString(egldpy, EGL_CLIENT_APIS);
	weston_log("EGL client APIs: %s\n", str ? str : "(null)");

	str = eglQueryString(egldpy, EGL_EXTENSIONS);
	log_extensions("EGL extensions", str ? str : "(null)");

	str = (char *)glGetString(GL_VERSION);
	weston_log("GL version: %s\n", str ? str : "(null)");

	str = (char *)glGetString(GL_SHADING_LANGUAGE_VERSION);
	weston_log("GLSL version: %s\n", str ? str : "(null)");

	str = (char *)glGetString(GL_VENDOR);
	weston_log("GL vendor: %s\n", str ? str : "(null)");

	str = (char *)glGetString(GL_RENDERER);
	weston_log("GL renderer: %s\n", str ? str : "(null)");

	str = (char *)glGetString(GL_EXTENSIONS);
	log_extensions("GL extensions", str ? str : "(null)");
}

static void
log_egl_config_info(EGLDisplay egldpy, EGLConfig eglconfig)
{
	EGLint r, g, b, a;

	weston_log("Chosen EGL config details:\n");

	weston_log_continue(STAMP_SPACE "RGBA bits");
	if (eglGetConfigAttrib(egldpy, eglconfig, EGL_RED_SIZE, &r) &&
	    eglGetConfigAttrib(egldpy, eglconfig, EGL_GREEN_SIZE, &g) &&
	    eglGetConfigAttrib(egldpy, eglconfig, EGL_BLUE_SIZE, &b) &&
	    eglGetConfigAttrib(egldpy, eglconfig, EGL_ALPHA_SIZE, &a))
		weston_log_continue(": %d %d %d %d\n", r, g, b, a);
	else
		weston_log_continue(" unknown\n");

	weston_log_continue(STAMP_SPACE "swap interval range");
	if (eglGetConfigAttrib(egldpy, eglconfig, EGL_MIN_SWAP_INTERVAL, &a) &&
	    eglGetConfigAttrib(egldpy, eglconfig, EGL_MAX_SWAP_INTERVAL, &b))
		weston_log_continue(": %d - %d\n", a, b);
	else
		weston_log_continue(" unknown\n");
}

static int
match_config_to_visual(EGLDisplay egl_display,
		       EGLint visual_id,
		       EGLConfig *configs,
		       int count)
{
	int i;

	for (i = 0; i < count; ++i) {
		EGLint id;

		if (!eglGetConfigAttrib(egl_display,
				configs[i], EGL_NATIVE_VISUAL_ID,
				&id))
			continue;

		if (id == visual_id)
			return i;
	}

	return -1;
}

static int
egl_choose_config(struct gl_renderer *gr, const EGLint *attribs,
		  const EGLint *visual_id, const int n_ids,
		  EGLConfig *config_out)
{
	EGLint count = 0;
	EGLint matched = 0;
	EGLConfig *configs;
	int i, config_index = -1;

	if (!eglGetConfigs(gr->egl_display, NULL, 0, &count) || count < 1) {
		weston_log("No EGL configs to choose from.\n");
		return -1;
	}
	configs = calloc(count, sizeof *configs);
	if (!configs)
		return -1;

	if (!eglChooseConfig(gr->egl_display, attribs, configs,
			      count, &matched) || !matched) {
		weston_log("No EGL configs with appropriate attributes.\n");
		goto out;
	}

	if (!visual_id || n_ids == 0)
		config_index = 0;

	for (i = 0; config_index == -1 && i < n_ids; i++)
		config_index = match_config_to_visual(gr->egl_display,
						      visual_id[i],
						      configs,
						      matched);

	if (config_index != -1)
		*config_out = configs[config_index];

out:
	free(configs);
	if (config_index == -1)
		return -1;

	if (i > 1)
		weston_log("Unable to use first choice EGL config with id"
			   " 0x%x, succeeded with alternate id 0x%x.\n",
			   visual_id[0], visual_id[i - 1]);
	return 0;
}

static void
gl_renderer_output_set_border(struct weston_output *output,
			      enum gl_renderer_border_side side,
			      int32_t width, int32_t height,
			      int32_t tex_width, unsigned char *data)
{
	struct gl_output_state *go = get_output_state(output);

	if (go->borders[side].width != width ||
	    go->borders[side].height != height)
		/* In this case, we have to blow everything and do a full
		 * repaint. */
		go->border_status |= BORDER_SIZE_CHANGED | BORDER_ALL_DIRTY;

	if (data == NULL) {
		width = 0;
		height = 0;
	}

	go->borders[side].width = width;
	go->borders[side].height = height;
	go->borders[side].tex_width = tex_width;
	go->borders[side].data = data;
	go->border_status |= 1 << side;
}

static int
gl_renderer_setup(struct weston_compositor *ec, EGLSurface egl_surface);

static EGLSurface
gl_renderer_create_window_surface(struct gl_renderer *gr,
				  EGLNativeWindowType window_for_legacy,
				  void *window_for_platform,
				  const EGLint *config_attribs,
				  const EGLint *visual_id,
				  int n_ids)
{
	EGLSurface egl_surface = EGL_NO_SURFACE;
	EGLConfig egl_config;

	if (egl_choose_config(gr, config_attribs, visual_id,
			      n_ids, &egl_config) == -1) {
		weston_log("failed to choose EGL config for output\n");
		return EGL_NO_SURFACE;
	}

	if (egl_config != gr->egl_config &&
	    !gr->has_configless_context) {
		weston_log("attempted to use a different EGL config for an "
			   "output but EGL_KHR_no_config_context or "
			   "EGL_MESA_configless_context is not supported\n");
		return EGL_NO_SURFACE;
	}

	log_egl_config_info(gr->egl_display, egl_config);

	if (gr->create_platform_window)
		egl_surface = gr->create_platform_window(gr->egl_display,
							 egl_config,
							 window_for_platform,
							 NULL);
	else
		egl_surface = eglCreateWindowSurface(gr->egl_display,
						     egl_config,
						     window_for_legacy, NULL);

	return egl_surface;
}

static int
gl_renderer_output_create(struct weston_output *output,
			  EGLSurface surface)
{
	struct gl_output_state *go;
	int i;

	go = zalloc(sizeof *go);
	if (go == NULL)
		return -1;

	go->egl_surface = surface;

	for (i = 0; i < BUFFER_DAMAGE_COUNT; i++)
		pixman_region32_init(&go->buffer_damage[i]);

	output->renderer_state = go;

	return 0;
}

static int
gl_renderer_output_window_create(struct weston_output *output,
				 EGLNativeWindowType window_for_legacy,
				 void *window_for_platform,
				 const EGLint *config_attribs,
				 const EGLint *visual_id,
				 int n_ids,
//HISILICON add begin
//tag, support hwc compose
                 int fb_fd,
                 int width,
				 int height)
//HISILICON add end
{
	struct weston_compositor *ec = output->compositor;
	struct gl_renderer *gr = get_renderer(ec);
	EGLSurface egl_surface = EGL_NO_SURFACE;
	int ret = 0;
//HISILICON add begin
//tag, support hwc compose
    struct gl_output_state *go = NULL;
//HISILICON add end

	egl_surface = gl_renderer_create_window_surface(gr,
							window_for_legacy,
							window_for_platform,
							config_attribs,
							visual_id, n_ids);
	if (egl_surface == EGL_NO_SURFACE) {
		weston_log("failed to create egl surface\n");
		return -1;
	}

	ret = gl_renderer_output_create(output, egl_surface);
	if (ret < 0)
		weston_platform_destroy_egl_surface(gr->egl_display, egl_surface);

//HISILICON add begin
//tag, support hwc compose
    if (gr->use_gl_hwc)
    {
        gr->fb_fd = fb_fd;
        go = get_output_state(output);
        gs_hwc_renderer->output_window_create(&(go->hwc_renderer_output),fb_fd,width, height);
    }
//HISILICON add end

	return ret;
}

static void
gl_renderer_output_destroy(struct weston_output *output)
{
	struct gl_renderer *gr = get_renderer(output->compositor);
	struct gl_output_state *go = get_output_state(output);
	int i;

	for (i = 0; i < 2; i++)
		pixman_region32_fini(&go->buffer_damage[i]);

	eglMakeCurrent(gr->egl_display,
		       EGL_NO_SURFACE, EGL_NO_SURFACE,
		       EGL_NO_CONTEXT);

	weston_platform_destroy_egl_surface(gr->egl_display, go->egl_surface);

//HISILICON add begin
//tag, support hwc compose
    if (gr->use_gl_hwc)
    {
        gs_hwc_renderer->output_window_destroy(go->hwc_renderer_output);
    }
//HISILICON add end

	free(go);
}

static EGLSurface
gl_renderer_output_surface(struct weston_output *output)
{
	return get_output_state(output)->egl_surface;
}

static void
gl_renderer_destroy(struct weston_compositor *ec)
{
	struct gl_renderer *gr = get_renderer(ec);
	struct dmabuf_image *image, *next;
    fprintf(stderr,"+++++++++++%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);

	wl_signal_emit(&gr->destroy_signal, gr);

	if (gr->has_bind_display)
		gr->unbind_display(gr->egl_display, ec->wl_display);

	/* Work around crash in egl_dri2.c's dri2_make_current() - when does this apply? */
	eglMakeCurrent(gr->egl_display,
		       EGL_NO_SURFACE, EGL_NO_SURFACE,
		       EGL_NO_CONTEXT);


	wl_list_for_each_safe(image, next, &gr->dmabuf_images, link)
		dmabuf_image_destroy(image);

	if (gr->dummy_surface != EGL_NO_SURFACE)
		weston_platform_destroy_egl_surface(gr->egl_display,
						    gr->dummy_surface);

	eglTerminate(gr->egl_display);
	eglReleaseThread();

	wl_list_remove(&gr->output_destroy_listener.link);

	wl_array_release(&gr->vertices);
	wl_array_release(&gr->vtxcnt);

	if (gr->fragment_binding)
		weston_binding_destroy(gr->fragment_binding);
	if (gr->fan_binding)
		weston_binding_destroy(gr->fan_binding);

	free(gr);
}

static void
renderer_setup_egl_client_extensions(struct gl_renderer *gr)
{
	const char *extensions;

	extensions = eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);
	if (!extensions) {
		weston_log("Retrieving EGL client extension string failed.\n");
		return;
	}

	if (weston_check_egl_extension(extensions, "EGL_EXT_platform_base"))
		gr->create_platform_window =
			(void *) eglGetProcAddress("eglCreatePlatformWindowSurfaceEXT");
	else
		weston_log("warning: EGL_EXT_platform_base not supported.\n");
}

static int
gl_renderer_setup_egl_extensions(struct weston_compositor *ec)
{
	static const struct {
		char *extension, *entrypoint;
	} swap_damage_ext_to_entrypoint[] = {
		{
			.extension = "EGL_EXT_swap_buffers_with_damage",
			.entrypoint = "eglSwapBuffersWithDamageEXT",
		},
		{
			.extension = "EGL_KHR_swap_buffers_with_damage",
			.entrypoint = "eglSwapBuffersWithDamageKHR",
		},
	};
	struct gl_renderer *gr = get_renderer(ec);
	const char *extensions;
	EGLBoolean ret;
	unsigned i;

	gr->create_image = (void *) eglGetProcAddress("eglCreateImageKHR");
	gr->destroy_image = (void *) eglGetProcAddress("eglDestroyImageKHR");

	gr->bind_display =
		(void *) eglGetProcAddress("eglBindWaylandDisplayWL");
	gr->unbind_display =
		(void *) eglGetProcAddress("eglUnbindWaylandDisplayWL");
	gr->query_buffer =
		(void *) eglGetProcAddress("eglQueryWaylandBufferWL");

	extensions =
		(const char *) eglQueryString(gr->egl_display, EGL_EXTENSIONS);
	if (!extensions) {
		weston_log("Retrieving EGL extension string failed.\n");
		return -1;
	}

	if (weston_check_egl_extension(extensions, "EGL_WL_bind_wayland_display"))
		gr->has_bind_display = 1;
	if (gr->has_bind_display) {
		ret = gr->bind_display(gr->egl_display, ec->wl_display);
		if (!ret)
			gr->has_bind_display = 0;
	}

	if (weston_check_egl_extension(extensions, "EGL_EXT_buffer_age"))
		gr->has_egl_buffer_age = 1;
	else
		weston_log("warning: EGL_EXT_buffer_age not supported. "
			   "Performance could be affected.\n");

	for (i = 0; i < ARRAY_LENGTH(swap_damage_ext_to_entrypoint); i++) {
		if (weston_check_egl_extension(extensions,
				swap_damage_ext_to_entrypoint[i].extension)) {
			gr->swap_buffers_with_damage =
				(void *) eglGetProcAddress(
						swap_damage_ext_to_entrypoint[i].entrypoint);
			break;
		}
	}
	if (!gr->swap_buffers_with_damage)
		weston_log("warning: neither %s or %s is supported. "
			   "Performance could be affected.\n",
			   swap_damage_ext_to_entrypoint[0].extension,
			   swap_damage_ext_to_entrypoint[1].extension);

	if (weston_check_egl_extension(extensions, "EGL_KHR_no_config_context") ||
	    weston_check_egl_extension(extensions, "EGL_MESA_configless_context"))
		gr->has_configless_context = 1;

	if (weston_check_egl_extension(extensions, "EGL_KHR_surfaceless_context"))
		gr->has_surfaceless_context = 1;

	if (weston_check_egl_extension(extensions, "EGL_EXT_image_dma_buf_import"))
		gr->has_dmabuf_import = 1;

	if (weston_check_egl_extension(extensions,
				"EGL_EXT_image_dma_buf_import_modifiers")) {
		gr->query_dmabuf_formats =
			(void *) eglGetProcAddress("eglQueryDmaBufFormatsEXT");
		gr->query_dmabuf_modifiers =
			(void *) eglGetProcAddress("eglQueryDmaBufModifiersEXT");
		gr->has_dmabuf_import_modifiers = 1;
	}

	if (weston_check_egl_extension(extensions, "GL_EXT_texture_rg"))
		gr->has_gl_texture_rg = 1;

	renderer_setup_egl_client_extensions(gr);

	return 0;
}

static const EGLint gl_renderer_opaque_attribs[] = {
	EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
	EGL_RED_SIZE, 1,
	EGL_GREEN_SIZE, 1,
	EGL_BLUE_SIZE, 1,
	EGL_ALPHA_SIZE, 0,
	EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
	EGL_NONE
};

static const EGLint gl_renderer_alpha_attribs[] = {
	EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
	EGL_RED_SIZE, 1,
	EGL_GREEN_SIZE, 1,
	EGL_BLUE_SIZE, 1,
	EGL_ALPHA_SIZE, 1,
	EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
	EGL_NONE
};


/** Checks whether a platform EGL client extension is supported
 *
 * \param ec The weston compositor
 * \param extension_suffix The EGL client extension suffix
 * \return 1 if supported, 0 if using fallbacks, -1 unsupported
 *
 * This function checks whether a specific platform_* extension is supported
 * by EGL.
 *
 * The extension suffix should be the suffix of the platform extension (that
 * specifies a <platform> argument as defined in EGL_EXT_platform_base). For
 * example, passing "foo" will check whether either "EGL_KHR_platform_foo",
 * "EGL_EXT_platform_foo", or "EGL_MESA_platform_foo" is supported.
 *
 * The return value is 1:
 *   - if the supplied EGL client extension is supported.
 * The return value is 0:
 *   - if the platform_base client extension isn't supported so will
 *     fallback to eglGetDisplay and friends.
 * The return value is -1:
 *   - if the supplied EGL client extension is not supported.
 */
static int
gl_renderer_supports(struct weston_compositor *ec,
		     const char *extension_suffix)
{
	static const char *extensions = NULL;
	char s[64];

	if (!extensions) {
		extensions = (const char *) eglQueryString(
			EGL_NO_DISPLAY, EGL_EXTENSIONS);

		if (!extensions)
			return 0;

		log_extensions("EGL client extensions",
			       extensions);
	}

	if (!weston_check_egl_extension(extensions, "EGL_EXT_platform_base"))
		return 0;

	snprintf(s, sizeof s, "EGL_KHR_platform_%s", extension_suffix);
	if (weston_check_egl_extension(extensions, s))
		return 1;

	snprintf(s, sizeof s, "EGL_EXT_platform_%s", extension_suffix);
	if (weston_check_egl_extension(extensions, s))
		return 1;

	snprintf(s, sizeof s, "EGL_MESA_platform_%s", extension_suffix);
	if (weston_check_egl_extension(extensions, s))
		return 1;

	/* at this point we definitely have some platform extensions but
	 * haven't found the supplied platform, so chances are it's
	 * not supported. */

	return -1;
}

static const char *
platform_to_extension(EGLenum platform)
{
	switch (platform) {
	case EGL_PLATFORM_GBM_KHR:
		return "gbm";
	case EGL_PLATFORM_WAYLAND_KHR:
		return "wayland";
	case EGL_PLATFORM_X11_KHR:
		return "x11";
	default:
		assert(0 && "bad EGL platform enum");
	}
}

static void
output_handle_destroy(struct wl_listener *listener, void *data)
{
	struct gl_renderer *gr;
	struct weston_output *output = data;

	gr = container_of(listener, struct gl_renderer,
			  output_destroy_listener);

	if (wl_list_empty(&output->compositor->output_list))
		eglMakeCurrent(gr->egl_display, gr->dummy_surface,
			       gr->dummy_surface, gr->egl_context);
}

static int
gl_renderer_create_pbuffer_surface(struct gl_renderer *gr) {
	EGLConfig pbuffer_config;

	static const EGLint pbuffer_config_attribs[] = {
		EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
		EGL_RED_SIZE, 1,
		EGL_GREEN_SIZE, 1,
		EGL_BLUE_SIZE, 1,
		EGL_ALPHA_SIZE, 0,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_NONE
	};

	static const EGLint pbuffer_attribs[] = {
		EGL_WIDTH, 10,
		EGL_HEIGHT, 10,
		EGL_NONE
	};

	if (egl_choose_config(gr, pbuffer_config_attribs, NULL, 0, &pbuffer_config) < 0) {
		weston_log("failed to choose EGL config for PbufferSurface\n");
		return -1;
	}

	gr->dummy_surface = eglCreatePbufferSurface(gr->egl_display,
						    pbuffer_config,
						    pbuffer_attribs);

	if (gr->dummy_surface == EGL_NO_SURFACE) {
		weston_log("failed to create PbufferSurface\n");
		return -1;
	}

	return 0;
}

static int
gl_renderer_display_create(struct weston_compositor *ec, EGLenum platform,
	void *native_window, const EGLint *platform_attribs,
	const EGLint *config_attribs, const EGLint *visual_id, int n_ids,
//HISILICON add begin
//tag, support hwc compose
	int use_gl_hwc, void *hwc_renderer)
//HISILICON add end
{
	struct gl_renderer *gr;
	EGLint major, minor;
	int supports = 0;

	if (platform) {
		supports = gl_renderer_supports(
			ec, platform_to_extension(platform));
		if (supports < 0)
			return -1;
	}

	gr = zalloc(sizeof *gr);
	if (gr == NULL)
		return -1;

//HISILICON add begin
//tag, support hwc compose
    gr->use_gl_hwc = use_gl_hwc;
    if (gr->use_gl_hwc)
    {
        if (NULL == hwc_renderer)
        {
           return -1;
        }
        gs_hwc_renderer = (struct gl_hwc_renderer_interface *)hwc_renderer;
    }
//HISILICON add end
	gr->base.read_pixels = gl_renderer_read_pixels;
	gr->base.repaint_output = gl_renderer_repaint_output;
	gr->base.flush_damage = gl_renderer_flush_damage;
	gr->base.attach = gl_renderer_attach;
	gr->base.surface_set_color = gl_renderer_surface_set_color;
	gr->base.destroy = gl_renderer_destroy;
	gr->base.surface_get_content_size =
		gl_renderer_surface_get_content_size;
	gr->base.surface_copy_content = gl_renderer_surface_copy_content;
	gr->egl_display = NULL;

	/* extension_suffix is supported */
	if (supports) {
		if (!get_platform_display) {
			get_platform_display = (void *) eglGetProcAddress(
					"eglGetPlatformDisplayEXT");
		}

		/* also wrap this in the supports check because
		 * eglGetProcAddress can return non-NULL and still not
		 * support the feature at runtime, so ensure the
		 * appropriate extension checks have been done. */
		if (get_platform_display && platform) {
			gr->egl_display = get_platform_display(platform,
							       native_window,
							       platform_attribs);
		}
	}

	if (!gr->egl_display) {
		weston_log("warning: either no EGL_EXT_platform_base "
			   "support or specific platform support; "
			   "falling back to eglGetDisplay.\n");
		gr->egl_display = eglGetDisplay(native_window);
	}

	if (gr->egl_display == EGL_NO_DISPLAY) {
		weston_log("failed to create display\n");
		goto fail;
	}

	if (!eglInitialize(gr->egl_display, &major, &minor)) {
		weston_log("failed to initialize display\n");
		goto fail_with_error;
	}

	if (egl_choose_config(gr, config_attribs, visual_id,
			      n_ids, &gr->egl_config) < 0) {
		weston_log("failed to choose EGL config\n");
		goto fail_terminate;
	}

	ec->renderer = &gr->base;
	ec->capabilities |= WESTON_CAP_ROTATION_ANY;
	ec->capabilities |= WESTON_CAP_CAPTURE_YFLIP;
	ec->capabilities |= WESTON_CAP_VIEW_CLIP_MASK;

	if (gl_renderer_setup_egl_extensions(ec) < 0)
		goto fail_with_error;

	wl_list_init(&gr->dmabuf_images);
	if (gr->has_dmabuf_import) {
		gr->base.import_dmabuf = gl_renderer_import_dmabuf;
		gr->base.query_dmabuf_formats =
			gl_renderer_query_dmabuf_formats;
		gr->base.query_dmabuf_modifiers =
			gl_renderer_query_dmabuf_modifiers;
	}

	if (gr->has_surfaceless_context) {
		weston_log("EGL_KHR_surfaceless_context available\n");
		gr->dummy_surface = EGL_NO_SURFACE;
	} else {
		weston_log("EGL_KHR_surfaceless_context unavailable. "
			   "Trying PbufferSurface\n");

		if (gl_renderer_create_pbuffer_surface(gr) < 0)
			goto fail_with_error;
	}

	wl_display_add_shm_format(ec->wl_display, WL_SHM_FORMAT_RGB565);
	wl_display_add_shm_format(ec->wl_display, WL_SHM_FORMAT_YUV420);
	wl_display_add_shm_format(ec->wl_display, WL_SHM_FORMAT_NV12);
	wl_display_add_shm_format(ec->wl_display, WL_SHM_FORMAT_YUYV);

	wl_signal_init(&gr->destroy_signal);

	if (gl_renderer_setup(ec, gr->dummy_surface) < 0) {
		if (gr->dummy_surface != EGL_NO_SURFACE)
			weston_platform_destroy_egl_surface(gr->egl_display,
							    gr->dummy_surface);
		goto fail_with_error;
	}

	return 0;

fail_with_error:
	gl_renderer_print_egl_error_state();
fail_terminate:
	eglTerminate(gr->egl_display);
fail:
	free(gr);
	return -1;
}

static EGLDisplay
gl_renderer_display(struct weston_compositor *ec)
{
	return get_renderer(ec)->egl_display;
}

static int
compile_shaders(struct weston_compositor *ec)
{
	struct gl_renderer *gr = get_renderer(ec);

	gr->texture_shader_rgba.vertex_source = vertex_shader;
	gr->texture_shader_rgba.fragment_source = texture_fragment_shader_rgba;

	gr->texture_shader_rgbx.vertex_source = vertex_shader;
	gr->texture_shader_rgbx.fragment_source = texture_fragment_shader_rgbx;

	gr->texture_shader_egl_external.vertex_source = vertex_shader;
	gr->texture_shader_egl_external.fragment_source =
		texture_fragment_shader_egl_external;

	gr->texture_shader_y_uv.vertex_source = vertex_shader;
	gr->texture_shader_y_uv.fragment_source = texture_fragment_shader_y_uv;

	gr->texture_shader_y_u_v.vertex_source = vertex_shader;
	gr->texture_shader_y_u_v.fragment_source =
		texture_fragment_shader_y_u_v;

	gr->texture_shader_y_xuxv.vertex_source = vertex_shader;
	gr->texture_shader_y_xuxv.fragment_source =
		texture_fragment_shader_y_xuxv;

	gr->solid_shader.vertex_source = vertex_shader;
	gr->solid_shader.fragment_source = solid_fragment_shader;

	return 0;
}

static void
fragment_debug_binding(struct weston_keyboard *keyboard, uint32_t time,
		       uint32_t key, void *data)
{
	struct weston_compositor *ec = data;
	struct gl_renderer *gr = get_renderer(ec);
	struct weston_output *output;

	gr->fragment_shader_debug ^= 1;

	shader_release(&gr->texture_shader_rgba);
	shader_release(&gr->texture_shader_rgbx);
	shader_release(&gr->texture_shader_egl_external);
	shader_release(&gr->texture_shader_y_uv);
	shader_release(&gr->texture_shader_y_u_v);
	shader_release(&gr->texture_shader_y_xuxv);
	shader_release(&gr->solid_shader);

	/* Force use_shader() to call glUseProgram(), since we need to use
	 * the recompiled version of the shader. */
	gr->current_shader = NULL;

	wl_list_for_each(output, &ec->output_list, link)
		weston_output_damage(output);
}

static void
fan_debug_repaint_binding(struct weston_keyboard *keyboard, uint32_t time,
			  uint32_t key, void *data)
{
	struct weston_compositor *compositor = data;
	struct gl_renderer *gr = get_renderer(compositor);

	gr->fan_debug = !gr->fan_debug;
	weston_compositor_damage_all(compositor);
}

static int
gl_renderer_setup(struct weston_compositor *ec, EGLSurface egl_surface)
{
	struct gl_renderer *gr = get_renderer(ec);
	const char *extensions;
	EGLConfig context_config;
	EGLBoolean ret;

	static const EGLint context_attribs[] = {
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	if (!eglBindAPI(EGL_OPENGL_ES_API)) {
		weston_log("failed to bind EGL_OPENGL_ES_API\n");
		gl_renderer_print_egl_error_state();
		return -1;
	}

	context_config = gr->egl_config;

	if (gr->has_configless_context)
		context_config = EGL_NO_CONFIG_KHR;

	gr->egl_context = eglCreateContext(gr->egl_display, context_config,
					   EGL_NO_CONTEXT, context_attribs);
	if (gr->egl_context == NULL) {
		weston_log("failed to create context\n");
		gl_renderer_print_egl_error_state();
		return -1;
	}

	ret = eglMakeCurrent(gr->egl_display, egl_surface,
			     egl_surface, gr->egl_context);
	if (ret == EGL_FALSE) {
		weston_log("Failed to make EGL context current.\n");
		gl_renderer_print_egl_error_state();
		return -1;
	}

	log_egl_gl_info(gr->egl_display);

	gr->image_target_texture_2d =
		(void *) eglGetProcAddress("glEGLImageTargetTexture2DOES");

	extensions = (const char *) glGetString(GL_EXTENSIONS);
	if (!extensions) {
		weston_log("Retrieving GL extension string failed.\n");
		return -1;
	}

	if (!weston_check_egl_extension(extensions, "GL_EXT_texture_format_BGRA8888")) {
		weston_log("GL_EXT_texture_format_BGRA8888 not available\n");
		return -1;
	}

	if (weston_check_egl_extension(extensions, "GL_EXT_read_format_bgra"))
		ec->read_format = PIXMAN_a8r8g8b8;
	else
		ec->read_format = PIXMAN_a8b8g8r8;

	if (weston_check_egl_extension(extensions, "GL_EXT_unpack_subimage"))
		gr->has_unpack_subimage = 1;

	if (weston_check_egl_extension(extensions, "GL_OES_EGL_image_external"))
		gr->has_egl_image_external = 1;

	glActiveTexture(GL_TEXTURE0);

	if (compile_shaders(ec))
		return -1;

	gr->fragment_binding =
		weston_compositor_add_debug_binding(ec, KEY_S,
						    fragment_debug_binding,
						    ec);
	gr->fan_binding =
		weston_compositor_add_debug_binding(ec, KEY_F,
						    fan_debug_repaint_binding,
						    ec);

	gr->output_destroy_listener.notify = output_handle_destroy;
	wl_signal_add(&ec->output_destroyed_signal,
		      &gr->output_destroy_listener);

	weston_log("GL ES 2 renderer features:\n");
	weston_log_continue(STAMP_SPACE "read-back format: %s\n",
		ec->read_format == PIXMAN_a8r8g8b8 ? "BGRA" : "RGBA");
	weston_log_continue(STAMP_SPACE "wl_shm sub-image to texture: %s\n",
			    gr->has_unpack_subimage ? "yes" : "no");
	weston_log_continue(STAMP_SPACE "EGL Wayland extension: %s\n",
			    gr->has_bind_display ? "yes" : "no");


	return 0;
}

WL_EXPORT struct gl_renderer_interface gl_renderer_interface = {
	.opaque_attribs = gl_renderer_opaque_attribs,
	.alpha_attribs = gl_renderer_alpha_attribs,

	.display_create = gl_renderer_display_create,
	.display = gl_renderer_display,
	.output_window_create = gl_renderer_output_window_create,
	.output_destroy = gl_renderer_output_destroy,
	.output_surface = gl_renderer_output_surface,
	.output_set_border = gl_renderer_output_set_border,
	.print_egl_error_state = gl_renderer_print_egl_error_state
};
