/*
 * Copyright © 2016 Benoit Gschwind
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

#ifndef WESTON_COMPOSITOR_FBDEV_H
#define WESTON_COMPOSITOR_FBDEV_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "compositor.h"

#define WESTON_FBDEV_BACKEND_CONFIG_VERSION 2

struct libinput_device;

struct weston_fbdev_backend_config {
	struct weston_backend_config base;

	int tty;
	char *device;

//HISILICON add begin
//tag, support hwc compose
    int use_pixman;
	int use_gl;
	int use_hwc;
//HISILICON add end

	/** Callback used to configure input devices.
	 *
	 * This function will be called by the backend when a new input device
	 * needs to be configured.
	 * If NULL the device will use the default configuration.
	 */
	void (*configure_device)(struct weston_compositor *compositor,
				 struct libinput_device *device);
};

#ifdef  __cplusplus
}
#endif

#endif /* WESTON_COMPOSITOR_FBDEV_H */
