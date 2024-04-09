/******************************************************************************

  Copyright (C), 2015-2016, Hisilicon Tech. Co., Ltd.

******************************************************************************
******************************************************************************
  File Name     	: es20_common.c
  Version       	: Initial Draft
  Author        	: Hisilicon Device Chipset Key Technologies GPU group
  Created       	: 2015/11/19
  Description   	:
  History       	:
  1.Date        	: 2016/05/25
    Author      	:
    Modification	: group review file
  2.Date        	: 2016/06/03
    Author      	:
    Modification: change MMZ_Malloc method
  3.Date        	: 2016/06/22
    Author      	:
    Modification	: modify HI_COMMON_DestroyPixmapFromMmz @ Midgard 64Bit compatibility
  4.Date        	: 2018/04/02
    Author      	:
    Modification	:
******************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/time.h>

#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "hifb.h"
#include "hi_dbe.h"
#include "es20_common.h"

#include "mpi_mmz.h"

#ifdef FRAMEBUFFER_DEVICE_OPEN
#include "hi_unf_disp.h"
#include "hi_adp_mpi.h"

int HI_COMMON_OpenFramebufferDevice(int width, int height, display_format display_fmt)
{
    HIFB_ALPHA_S stAlpha;
    struct fb_var_screeninfo vinfo;
    const char* file = "/dev/fb0";
    int fd, err;

    HIADP_Disp_Init(HI_UNF_ENC_FMT_1080P_60);

    HI_UNF_DISP_SetVirtualScreen(HI_UNF_DISPLAY1, width, height);

    HI_SYS_Init();
    HI_UNF_DISP_Init();

    memset(&stAlpha, 0, sizeof(stAlpha));
    stAlpha.bAlphaEnable  = HI_TRUE;
    stAlpha.bAlphaChannel = HI_TRUE;
    stAlpha.u8Alpha0 = 0xff;
    stAlpha.u8Alpha1 = 0xff;
    stAlpha.u8GlobalAlpha = 0x90;

    fd = open(file, O_RDWR, 0);
    if (-1 == fd)
    {
        fprintf(stderr, "open /dev/fb0 failed\n");
        return -1;
    }

    if (ioctl(fd, FBIOPUT_ALPHA_HIFB, &stAlpha) < 0)
    {
        fprintf(stderr, "Unable to set alpha!\n");
        return -1;
    }

    if ((err = ioctl(fd, FBIOGET_VSCREENINFO, &vinfo)) < 0)
    {
        fprintf(stderr, "Unable to FBIOGET_VSCREENINFO!, err=0x%x\n", err);
        return -1;
    }

    switch(display_fmt)
    {
        case DISPLAY_FORMAT_RGB565:
            vinfo.bits_per_pixel = 16;
            vinfo.red.length    = 5;
            vinfo.green.length  = 6;
            vinfo.blue.length   = 5;
            vinfo.blue.offset  = 0;
            vinfo.green.offset = 5;
            vinfo.red.offset = 11;
            break;

        case DISPLAY_FORMAT_ARGB8888:
            vinfo.bits_per_pixel = 32;
            vinfo.red.length    = 8;
            vinfo.green.length  = 8;
            vinfo.blue.length   = 8;
            vinfo.transp.length = 8;
            vinfo.blue.offset  = 0;
            vinfo.green.offset = 8;
            vinfo.red.offset = 16;
            vinfo.transp.offset = 24;
            break;

        case DISPLAY_FORMAT_ARGB4444:
            vinfo.bits_per_pixel = 16;
            vinfo.red.length    = 4;
            vinfo.green.length  = 4;
            vinfo.blue.length   = 4;
            vinfo.transp.length = 4;
            vinfo.blue.offset  = 0;
            vinfo.green.offset = 4;
            vinfo.red.offset = 8;
            vinfo.transp.offset = 12;
            break;

        case DISPLAY_FORMAT_ARGB1555:
            vinfo.bits_per_pixel = 16;
            vinfo.red.length    = 5;
            vinfo.green.length  = 5;
            vinfo.blue.length   = 5;
            vinfo.transp.length = 1;
            vinfo.blue.offset  = 0;
            vinfo.green.offset = 5;
            vinfo.red.offset = 10;
            vinfo.transp.offset = 15;
            break;

        default:
            fprintf(stderr, "display format invalid\n");
            return -1;
            break;
    }

    vinfo.xres = vinfo.xres_virtual = width;
    vinfo.yres = height;
    vinfo.yres_virtual = 2 * vinfo.yres;

    if ((err = ioctl(fd, FBIOPUT_VSCREENINFO, &vinfo)) < 0)
    {
        fprintf(stderr, "Unable to set double buffer mode!, err=0x%x\n", err);
        vinfo.yres_virtual = vinfo.yres;
        if ((err = ioctl(fd, FBIOPUT_VSCREENINFO, &vinfo)) < 0)
        {
            fprintf(stderr, "Unable to FBIOPUT_VSCREENINFO!, err=0x%x\n", err);
            return -1;
        }

        return -1;
    }

    return fd;
}

void HI_COMMON_CloseFramebufferDevice(int fd)
{
    close(fd);

    HIADP_Disp_DeInit();

    HI_SYS_DeInit();
}
#endif

/*EGL API Function*/

#if defined(EGL_API_DIRECTFB)

static IDirectFB *pdfb;
static IDirectFBDisplayLayer *pdfb_layer;
static IDirectFBWindow *pdfb_window;

#endif

#if defined(EGL_API_WAYLAND)

static struct wl_display *global_display = NULL;
static struct wl_registry *global_registry = NULL;
static struct wl_compositor *global_compositor = NULL;
static struct wl_shell *global_shell = NULL;

typedef struct WaylandWindow
{
	struct wl_region *region;
	struct wl_shell_surface *shell_surface;
	struct wl_surface *surface;

	wl_egl_window *egl_window;
}WaylandWindow;

static WaylandWindow *s_wayland_window = NULL;

extern const struct wl_interface wl_compositor_interface;
extern const struct wl_interface wl_shell_interface;

static void egl_registry_global(void *data, struct wl_registry *registry, unsigned int name, const char *interface, unsigned int version)
{
	if (strncmp(interface, "wl_compositor", 14) == 0)
	{
		global_compositor = (struct wl_compositor *)wl_registry_bind(registry, name, &wl_compositor_interface, version);
	}
	else if (strncmp(interface, "wl_shell", 9) == 0)
	{
		global_shell = (struct wl_shell *)wl_registry_bind(registry, name, &wl_shell_interface, version);
	}

	return;
}

static void egl_registry_global_remove(void *data, struct wl_registry *registry, unsigned int name)
{
	return;
}

static const struct wl_registry_listener egl_registry_listener =
{
	egl_registry_global,
	egl_registry_global_remove
};
#endif

NativeDisplayType HI_COMMON_CreateNativeDisplay(int width, int height)
{
#if defined(EGL_API_FBDEV)

    return (NativeDisplayType)EGL_DEFAULT_DISPLAY;

#elif defined(EGL_API_DIRECTFB)

    int ret;
    DFBDisplayLayerConfig dfb_layer_config;

    int argc = 0;
    char **argv = (char**)malloc(sizeof(char**));

    ret = DirectFBInit(&argc, &argv);
    ASSERT_EQUAL(ret, DFB_OK);

    ret = DirectFBCreate(&pdfb);
    ASSERT_EQUAL(ret, DFB_OK);

    ret = pdfb->GetDisplayLayer(pdfb, DLID_PRIMARY, &pdfb_layer);
    ASSERT_EQUAL(ret, DFB_OK);

    ret = pdfb_layer->SetCooperativeLevel(pdfb_layer, DLSCL_ADMINISTRATIVE);
    ASSERT_EQUAL(ret, DFB_OK);

    ret = pdfb_layer->GetConfiguration(pdfb_layer, &dfb_layer_config);
    ASSERT_EQUAL(ret, DFB_OK);

    dfb_layer_config.flags = (DFBDisplayLayerConfigFlags)(DLCONF_WIDTH | DLCONF_HEIGHT | DLCONF_PIXELFORMAT);
    dfb_layer_config.width = width;
    dfb_layer_config.height = height;
    dfb_layer_config.pixelformat = DSPF_ARGB;

    ret = pdfb_layer->SetConfiguration(pdfb_layer, &dfb_layer_config);
    ASSERT_EQUAL(ret, DFB_OK);

    fprintf(stderr, "create directfb layer = %p\n", pdfb_layer);

    return (NativeDisplayType)pdfb_layer;

#elif defined(EGL_API_WAYLAND)

    global_display = wl_display_connect(NULL);
    ASSERT_NOT_EQUAL(global_display, NULL);

    global_registry = wl_display_get_registry(global_display);
    ASSERT_NOT_EQUAL(global_registry, NULL);

    wl_registry_add_listener(global_registry, &egl_registry_listener, NULL);

    wl_display_dispatch(global_display);

    fprintf(stderr, "create wayland display = %p\n", global_display);

    return (NativeDisplayType)global_display;

#endif
}

void HI_COMMON_DestroyNativeDisplay(NativeDisplayType native_display)
{
#if defined(EGL_API_FBDEV)

    return;

#elif defined(EGL_API_DIRECTFB)

    int ret;

    ret = pdfb_layer->Release(pdfb_layer);
    ASSERT_EQUAL(ret, DFB_OK);

    ret = pdfb->Release(pdfb);
    ASSERT_EQUAL(ret, DFB_OK);

#elif defined(EGL_API_WAYLAND)

    wl_compositor_destroy(global_compositor);
    global_compositor = NULL;

    wl_shell_destroy(global_shell);
    global_shell = NULL;

    wl_registry_destroy(global_registry);
    global_registry = NULL;

    wl_display_disconnect(global_display);
    global_display = NULL;

    return;

#endif
}

NativeWindowType HI_COMMON_CreateNativeWindow(int width,int height)
{
#if defined(EGL_API_FBDEV)

    fbdev_window * fb_window = (fbdev_window *)malloc(sizeof(fbdev_window));

    fb_window->width = width;
    fb_window->height = height;

    return (NativeWindowType)fb_window;

#elif defined(EGL_API_DIRECTFB)

    int ret;
    DFBWindowDescription  dfb_window_desc;
    IDirectFBSurface *dfb_window_surface ;

    memset(&dfb_window_desc, 0, sizeof(DFBWindowDescription) );

    dfb_window_desc.flags  = (DFBWindowDescriptionFlags)(DWDESC_POSX | DWDESC_POSY | DWDESC_WIDTH | DWDESC_HEIGHT \
    					| DWDESC_PIXELFORMAT | DWDESC_OPTIONS | DWDESC_CAPS | DWDESC_SURFACE_CAPS);
    dfb_window_desc.posx   = 0;
    dfb_window_desc.posy   = 0;
    dfb_window_desc.width  = width;
    dfb_window_desc.height = height;
    dfb_window_desc.options = DWOP_ALPHACHANNEL;
    dfb_window_desc.caps = DWCAPS_ALPHACHANNEL;

    dfb_window_desc.caps = (DFBWindowCapabilities)((int)dfb_window_desc.caps | DWCAPS_DOUBLEBUFFER);
    dfb_window_desc.surface_caps = (DFBSurfaceCapabilities)(DSCAPS_PRIMARY | DSCAPS_VIDEOONLY | DSCAPS_DOUBLE);
    dfb_window_desc.pixelformat = DSPF_ARGB;

    ret = pdfb_layer->CreateWindow(pdfb_layer, &dfb_window_desc, &pdfb_window);
    ASSERT_EQUAL(ret, DFB_OK);

    ret = pdfb_window->SetOpacity(pdfb_window, 0xff);
    ASSERT_EQUAL(ret, DFB_OK);

    ret = pdfb_window->GetSurface(pdfb_window, &dfb_window_surface);
    ASSERT_EQUAL(ret, DFB_OK);

    fprintf(stderr, "create directfb window = %p\n", dfb_window_surface);

    return (NativeWindowType)dfb_window_surface;

#elif defined(EGL_API_WAYLAND)

    s_wayland_window = (WaylandWindow*)malloc(sizeof(WaylandWindow));

    s_wayland_window->surface = wl_compositor_create_surface(global_compositor);
    ASSERT_NOT_EQUAL(s_wayland_window->surface, NULL);

    s_wayland_window->region = wl_compositor_create_region(global_compositor);
    ASSERT_NOT_EQUAL(s_wayland_window->region, NULL);

    wl_surface_set_opaque_region(s_wayland_window->surface, s_wayland_window->region);

    s_wayland_window->shell_surface = wl_shell_get_shell_surface(global_shell, s_wayland_window->surface);
    ASSERT_NOT_EQUAL(s_wayland_window->shell_surface, NULL);

    wl_shell_surface_set_title(s_wayland_window->shell_surface, "Internal tests");

    wl_shell_surface_set_toplevel(s_wayland_window->shell_surface);

    s_wayland_window->egl_window = (wl_egl_window*)wl_egl_window_create(s_wayland_window->surface, width, height);

    fprintf(stderr, "create wayland window = %p\n", s_wayland_window->egl_window);

    return (NativeWindowType)(s_wayland_window->egl_window);

#endif
}

void HI_COMMON_DestroyNativeWindow(NativeWindowType native_window)
{
#if defined(EGL_API_FBDEV)

    fbdev_window *window = (fbdev_window*)native_window;
    free(window);

#elif defined(EGL_API_DIRECTFB)

    IDirectFBSurface *dfb_window_surface = (IDirectFBSurface*)native_window;
    int ret;

    ret = dfb_window_surface->Release(dfb_window_surface);
    ASSERT_EQUAL(ret, DFB_OK);

    ret = pdfb_window->Release(pdfb_window);
    ASSERT_EQUAL(ret, DFB_OK);

#elif defined(EGL_API_WAYLAND)

    wl_region_destroy(s_wayland_window->region);

    wl_shell_surface_destroy(s_wayland_window->shell_surface);

    wl_surface_destroy(s_wayland_window->surface);

    wl_egl_window_destroy(s_wayland_window->egl_window);

    free(s_wayland_window);

#endif
}

NativePixmapType HI_COMMON_CreateNativePixmap(int width,int height)
{
#if defined(EGL_API_FBDEV) && defined(EGL_API_UTGARD)

    unsigned int mmz_addr;
    struct fbdev_dma_buf *pixmap_dma = (struct fbdev_dma_buf *)malloc(sizeof(struct fbdev_dma_buf));
    fbdev_pixmap *pixmap = (fbdev_pixmap*)malloc(sizeof(fbdev_pixmap));

    mmz_addr = HI_COMMON_CreateMMZMemory(width * height * 4);

    pixmap->flags = (fbdev_pixmap_flags)0;
    pixmap->width = width;
    pixmap->height = height;
    pixmap->red_size = 8;
    pixmap->green_size = 8;
    pixmap->blue_size = 8;
    pixmap->alpha_size = 8;
    pixmap->luminance_size = 0;
    pixmap->buffer_size = pixmap->red_size + pixmap->green_size + pixmap->blue_size + pixmap->alpha_size + pixmap->luminance_size;
    pixmap->bytes_per_pixel = pixmap->buffer_size / 8;

    pixmap_dma->size = width * height * pixmap->bytes_per_pixel;
    pixmap_dma->fd = HI_COMMON_WrapDmaBufFD(mmz_addr, pixmap_dma->size);

    pixmap->data = (unsigned short *)pixmap_dma;
    pixmap->flags = (fbdev_pixmap_flags)(pixmap->flags | FBDEV_PIXMAP_DMA_BUF);

    return (NativePixmapType)pixmap;

#elif defined(EGL_API_FBDEV) && defined(EGL_API_MIDGARD)

    unsigned int mmz_addr;
    int i;
    struct egl_linux_pixmap *pixmap_dma = (struct egl_linux_pixmap*)malloc(sizeof(struct egl_linux_pixmap));

    memset(pixmap_dma, 0, sizeof(*pixmap_dma));

    mmz_addr = HI_COMMON_CreateMMZMemory(width * height * 4);

    for(i = 0; i < 3; i++)
    {
        pixmap_dma->handles[i].fd = -1;
    }

    pixmap_dma->width = width;
    pixmap_dma->height = height;

    pixmap_dma->pixmap_format = EGL_PIXMAP_FORMAT_ARGB8888;

    pixmap_dma->planes[0].stride = width * 4;
    pixmap_dma->planes[0].size = pixmap_dma->planes[0].stride * height;
    pixmap_dma->planes[0].offset = 0;
    pixmap_dma->handles[0].fd = HI_COMMON_WrapDmaBufFD(mmz_addr, pixmap_dma->planes[0].size);
/*
    pixmap_dma->pixmap_format = EGL_PIXMAP_FORMAT_NV21_BT709_WIDE:

    pixmap_dma->planes[0].stride = width * 1;
    pixmap_dma->planes[0].size = pixmap_dma->planes[0].stride * height;
    pixmap_dma->planes[0].offset = 0;
    pixmap_dma->handles[0].fd = HI_COMMON_WrapDmaBufFD(mmz_addr, pixmap_dma->planes[0].size);

    pixmap_dma->planes[1].stride = width * 1;
    pixmap_dma->planes[1].size = pixmap_dma->planes[0].stride * height/2;
    pixmap_dma->planes[1].offset = 0;
    pixmap_dma->handles[1].fd = HI_COMMON_WrapDmaBufFD(mmz_addr + pixmap_dma->planes[0].size, pixmap_dma->planes[1].size);
*/
    return (NativePixmapType)egl_create_pixmap_ID_mapping(pixmap_dma);

#elif defined(EGL_API_DIRECTFB)

    int ret;
    IDirectFBSurface *pdfb_pixmap;
    DFBSurfaceDescription dfb_surface_dec;

    dfb_surface_dec.flags = (DFBSurfaceDescriptionFlags)(DSDESC_CAPS | DSDESC_WIDTH | DSDESC_HEIGHT | DSDESC_PIXELFORMAT);
    dfb_surface_dec.caps = (DFBSurfaceCapabilities)DSCAPS_VIDEOONLY;

    dfb_surface_dec.width = width;
    dfb_surface_dec.height = height;
    dfb_surface_dec.pixelformat = DSPF_ARGB;

    ret = pdfb->CreateSurface(pdfb, &dfb_surface_dec, &pdfb_pixmap);
    ASSERT_EQUAL(ret, DFB_OK);

    fprintf(stderr, "create directfb pixmap = %p\n", pdfb_pixmap);

    return (EGLNativePixmapType)pdfb_pixmap;

#endif
}

#if defined(EGL_API_FBDEV) && defined(EGL_API_UTGARD)

NativePixmapType HI_COMMON_CreateYuvNativePixmap(unsigned int phy_addr, int width,int height, unsigned char red_size,
          unsigned char green_size,unsigned char blue_size, unsigned char alpha_size, unsigned char luminance_size)
{
    struct fbdev_dma_buf *pixmap_dma = (struct fbdev_dma_buf *)malloc(sizeof(struct fbdev_dma_buf));
    fbdev_pixmap *pixmap = (fbdev_pixmap*)malloc(sizeof(fbdev_pixmap));

    pixmap->flags = (fbdev_pixmap_flags)0;
    pixmap->width = width;
    pixmap->height = height;
    pixmap->red_size = red_size;
    pixmap->green_size = green_size;
    pixmap->blue_size = blue_size;
    pixmap->alpha_size = alpha_size;
    pixmap->luminance_size = luminance_size;
    pixmap->buffer_size = pixmap->red_size + pixmap->green_size + pixmap->blue_size + pixmap->alpha_size + pixmap->luminance_size;
    pixmap->bytes_per_pixel = pixmap->buffer_size / 8;

    pixmap_dma->size = width * height * pixmap->bytes_per_pixel;
    pixmap_dma->fd = HI_COMMON_WrapDmaBufFD(phy_addr, pixmap_dma->size);

    pixmap->data = (unsigned short *)pixmap_dma;
    pixmap->flags = (fbdev_pixmap_flags)(pixmap->flags | FBDEV_PIXMAP_DMA_BUF);

    return (NativePixmapType)pixmap;
}
#endif

void HI_COMMON_DestroyNativePixmap(NativePixmapType native_pixmap)
{
#if defined(EGL_API_FBDEV) && defined(EGL_API_UTGARD)

    struct fbdev_dma_buf *pixmap_dma;
    fbdev_pixmap *fbpixmap = (fbdev_pixmap *)native_pixmap;

    pixmap_dma = (struct fbdev_dma_buf *)(fbpixmap->data);
    close(pixmap_dma->fd);

    free(fbpixmap);

#elif defined(EGL_API_FBDEV) && defined(EGL_API_MIDGARD)

    int i;
    struct egl_linux_pixmap *pixmap_dma = (struct egl_linux_pixmap *)egl_lookup_pixmap_ID_mapping((int)(unsigned long)native_pixmap);

    egl_destroy_pixmap_ID_mapping((int)(unsigned long)native_pixmap);

    for(i = 0; i < 3; i++)
    {
        close(pixmap_dma->handles[i].fd);
    }

    free(pixmap_dma);

#elif defined(EGL_API_DIRECTFB)

    int ret;
    IDirectFBSurface *pdfb_pixmap = (IDirectFBSurface*)native_pixmap;

    ret = pdfb_pixmap->Release(pdfb_pixmap);
    ASSERT_EQUAL(ret, DFB_OK);

#endif
}

/*OpenGL ES API Function*/

unsigned int HI_COMMON_CreateShader(const char * shader_path, unsigned int shader_type)
{
    unsigned int shader_id;
    char* shader_data;
    int compiled;

    shader_data = (char *)HI_COMMON_LoadFile(shader_path, 0, 0, "r");

    shader_id = glCreateShader(shader_type);
    glShaderSource(shader_id, 1, (const char**) &shader_data, NULL);
    glCompileShader(shader_id);

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);
    ASSERT_EQUAL(compiled, GL_TRUE);

    free(shader_data);

    return shader_id;
}

void HI_COMMON_DestroyShader(unsigned int shader_id)
{
    glDeleteShader(shader_id);
}

unsigned int HI_COMMON_CreateProgram(unsigned int vshader_id, unsigned int fshader_id)
{
    unsigned int program_id;
    int ret = GL_FALSE;

    program_id = glCreateProgram();
    glAttachShader(program_id, vshader_id);
    glAttachShader(program_id, fshader_id);
    glLinkProgram(program_id);

    glGetProgramiv(program_id, GL_LINK_STATUS, &ret);
    ASSERT_EQUAL(ret, GL_TRUE);

    glUseProgram(program_id);

    return program_id;
}

void HI_COMMON_DestroyProgram(unsigned int program_id)
{
    glDeleteProgram(program_id);
}

unsigned int HI_COMMON_CreateTexture(unsigned int tex_num, unsigned int tex_target, int tex_wrap_mode, int tex_filter)
{
    unsigned int texture_id;

    glActiveTexture(tex_num);
    glGenTextures(1, &texture_id);
    glBindTexture(tex_target, texture_id);

    glTexParameteri(tex_target, GL_TEXTURE_WRAP_S, tex_wrap_mode);
    glTexParameteri(tex_target, GL_TEXTURE_WRAP_T, tex_wrap_mode);
    glTexParameteri(tex_target, GL_TEXTURE_MIN_FILTER, tex_filter);
    glTexParameteri(tex_target, GL_TEXTURE_MAG_FILTER, tex_filter);

    return texture_id;
}

void HI_COMMON_DestroyTexture(unsigned int texture_id)
{
    glDeleteTextures(1, &texture_id);
}

unsigned int HI_COMMON_CreateBuffer(unsigned int buffer_type, GLsizeiptr size, const void *data)
{
    unsigned int buffer_id;

    glGenBuffers(1, &buffer_id);
    glBindBuffer(buffer_type, buffer_id);
    glBufferData(buffer_type, size, data, GL_STATIC_DRAW);

    return buffer_id;
}

void HI_COMMON_DestroyBuffer(unsigned int buffer_id)
{
    glDeleteBuffers(1, &buffer_id);
}

unsigned int HI_COMMON_CreateFBO(unsigned int texture_id, unsigned int tex_target, unsigned int attachment)
{
    int ret;
    unsigned int fbo_id;

    glGenFramebuffers(1, &fbo_id);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, tex_target, texture_id, 0);
    ret = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    ASSERT_EQUAL(ret, GL_FRAMEBUFFER_COMPLETE);

    return fbo_id;
}

void HI_COMMON_DestroyFBO(unsigned int fbo_id)
{
    glDeleteFramebuffers(1, &fbo_id);
}

/*Other Function*/

int HI_COMMON_WrapDmaBufFD(unsigned int physical_address, unsigned int size)
{
    struct hidbe_ioctl_wrap phywrap;
    int dmabuf_fd;

    int fd = open("/dev/hi_dbe", O_RDWR);

    phywrap.dbe_phyaddr = physical_address;
    phywrap.dbe_size = size;

#if defined(HI_SMMU_SUPPORT)
    phywrap.dbe_smmuflag = 1;
#else
    phywrap.dbe_smmuflag = 0;
#endif

    dmabuf_fd = ioctl(fd, DBE_COMMAND_WRAP_ADDRESS, &phywrap);

    close(fd);
    fprintf(stderr, "IN~ mem fd = 0x%x\n", dmabuf_fd);

    return dmabuf_fd;
}

void * HI_COMMON_LoadFile(const char *f_path, unsigned long skip, unsigned long f_size, const char *f_type)
{
    /* read resource file */
    unsigned char *retval = NULL;
    FILE *fptr = NULL;

    fptr = fopen(f_path, f_type);
    if (fptr == NULL)
    {
        fprintf(stderr, "Can not open file: %s\n", f_path);
        return NULL;
    }

    /* auto check file size when size is 0 */
    if(f_size == 0)
    {
        fseek(fptr, 0, SEEK_END);
        f_size = ftell(fptr);
    }
    fseek(fptr, skip, SEEK_SET);

    do
    {
        if((retval = (unsigned char *)malloc(sizeof(unsigned char) * f_size + 1)) == NULL)
        {
            fprintf(stderr, "malloc failed\n");
            break;
        }

        memset(retval, 0, f_size+1);

        if(fread(retval, sizeof(unsigned char), f_size, fptr) != f_size)
        {
            fprintf(stderr, "read failed\n");
            break;
        }

        fclose(fptr);
        return retval;
    }while (0);

    /* error handle */
    fprintf(stderr, "error while read resource file!\n");

    fclose(fptr);
    free(retval);

    return NULL;
}

void HI_COMMON_ModifyVirtualMemory(void **vir_addr, unsigned int color, unsigned long size)
{
    int i = 0;
    unsigned int *viraddr = (unsigned int*)*vir_addr;

    for(i=0; i < size; i++)
    {
        *viraddr = color;
        viraddr++;
    }
}

void HI_COMMON_PostMemoryToFramebuffer(void *virtual_addr, int memsize)
{
    struct fb_fix_screeninfo finfo;
    struct fb_var_screeninfo vinfo;
    unsigned long mapped_memlen = 0;
    void * mapped_mem = NULL;

    int console_fd = open("/dev/fb0", O_RDWR, 0);
    if (-1 == console_fd)
    {
        fprintf(stderr, "open /dev/fb0 failed\n");
        return;
    }

    /* Get the fix screen info of hardware */
    if (ioctl(console_fd, FBIOGET_FSCREENINFO, &finfo) < 0)
    {
        fprintf(stderr, "Couldn't get console hardware info\n");
        goto CLOSEFD;
    }

    mapped_memlen = finfo.smem_len;
    if(memsize > mapped_memlen)
    {
        fprintf(stderr, "out of memsize !\n");
        goto CLOSEFD;
    }

    mapped_mem = mmap(NULL, mapped_memlen, PROT_READ | PROT_WRITE, MAP_SHARED, console_fd, 0);
    if(mapped_mem == (char *)-1)
    {
        fprintf(stderr, "Unable to memory map the video hardware\n");
        mapped_mem = NULL;
        goto CLOSEFD;
    }

    /* Determine the current screen depth */
    if (ioctl(console_fd, FBIOGET_VSCREENINFO, &vinfo) < 0)
    {
        fprintf(stderr, "Couldn't get vscreeninfo\n");
        goto UNMAP;
    }

    memcpy(mapped_mem, virtual_addr, memsize);

UNMAP:
    munmap(mapped_mem, mapped_memlen);

CLOSEFD:
    close(console_fd);
}
unsigned int HI_COMMON_CreateMMZMemory(unsigned int size)
{
    unsigned int phy_addr;

#if defined(HI_SMMU_SUPPORT)
    phy_addr = HI_MPI_SMMU_New((HI_CHAR*)"GPU", size);
#else
    phy_addr = HI_MPI_MMZ_New(size, 0, "ddr", "GPU");
#endif

    return phy_addr;
}

void HI_COMMON_DestroyMMZMemory(unsigned int phy_addr)
{
#if defined(HI_SMMU_SUPPORT)
    HI_MPI_SMMU_Delete(phy_addr);
#else
    HI_MPI_MMZ_Delete(phy_addr);
#endif

    return;
}

void* HI_COMMON_MapMMZMemory(unsigned int phy_addr)
{
    void *vir_addr = NULL;

#if defined(HI_SMMU_SUPPORT)
    vir_addr = HI_MPI_SMMU_Map(phy_addr, (HI_BOOL)0);
#else
    vir_addr = HI_MPI_MMZ_Map(phy_addr, (HI_BOOL)0);
#endif

    return vir_addr;
}

void HI_COMMON_UnmapMMZMemory(unsigned int phy_addr)
{
#if defined(HI_SMMU_SUPPORT)
    HI_MPI_SMMU_Unmap(phy_addr);
#else
    HI_MPI_MMZ_Unmap(phy_addr);
#endif

    return;
}

