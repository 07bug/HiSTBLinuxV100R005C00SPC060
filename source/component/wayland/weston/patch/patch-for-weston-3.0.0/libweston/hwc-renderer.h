/*
 * Copyright © 2013 Vasily Khoruzhick <anarsoul@gmail.com>
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

#include "compositor.h"

//HISILICON add begin
//tag, support hwc compose, revise from pixman-renderer.h
struct hwc_renderer_interface {
	int  (*display_create)           (struct weston_compositor *ec);
	int  (*output_create)            (struct weston_output *output, int fb_fd);
    void (*output_surface)           (struct weston_output *output, pixman_image_t *buffer);
	void (*output_destroy)           (struct weston_output *output);
};

struct gl_hwc_renderer_interface {
	int  (*output_window_create)     (void **window_output, int fb_fd, int width, int height);
	void (*output_window_destroy)    (void *window_output);
    void (*output_surface_create)    (void **surface_output);
    void (*output_surface_destory)   (void *surface_output);
    int  (*read_pixels)              (struct weston_output *output,pixman_format_code_t format, void *pixels,uint32_t x, uint32_t y,uint32_t width, uint32_t height);
	void (*repaint_output)           (struct weston_view *ev, void *window_output,void *surface_output,pixman_region32_t *repaint_output,pixman_region32_t *source_clip);
	void (*flush_damage)             (void *surface_output);
    int  (*prepare)                  (void *surface_output, char *buffer, int w, int h, int stride, int format);
	void (*attach)                   (void *surface_output);
	void (*surface_set_color)        (void *surface_output, int w, int h,float red, float green,float blue, float alpha);
	void (*destroy)                  (struct weston_compositor *ec);
	void (*surface_get_content_size) (struct weston_surface *surface,int *width, int *height);
	int  (*surface_copy_content)     (struct weston_surface *surface,void *target, size_t size,int src_x, int src_y,int width, int height);
};
//HISILICON add end
