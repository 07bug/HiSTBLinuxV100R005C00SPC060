/******************************************************************************

  Copyright (C), 2015-2016, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     	: es20_yuv420sp_to_yuv420sp_framebufferobject.c
  Version       	: Initial Draft
  Author        	: Hisilicon Device Chipset Key Technologies GPU group
  Created       	: 2016/12/15
  Description   	:
  History       	:
  1.Date        	: 2018/04/02
    Author      	:
    Modification	: group review file

******************************************************************************/
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"
#include "GLES2/gl2ext.h"
#include "hifb.h"
#include "es20_common.h"

#define FHD_WIDTH  1920
#define FHD_HEIGHT 1080
#define HD_WIDTH  1280
#define HD_HEIGHT 720

#define TEXTURE_WIDTH  800
#define TEXTURE_HEIGHT 600

#define YUV_FILE_IN  "yuv420sp_in.yuv"
#define YUV_FILE_OUT "yuv420sp_out.yuv"

#define VERT_SRC     "../res/shaders/pass_two_attribs.vert.glsl"
#define FRAG_SRC_Y   "../res/shaders/texture_2plane_yuv_2_y.frag.glsl"
#define FRAG_SRC_UV  "../res/shaders/texture_2plane_yuv_2_uv.frag.glsl"

int attribute0_location = 0;    /* vetex coordinate */
int attribute1_location = 0;    /* texture coordinate */
int uniform0_location   = 0;
int uniform1_location   = 0;
int fshader_id_y        = 0;
int fshader_id_uv       = 0;
unsigned int buffer0_id = 0;    /* glGenBuffers used */
unsigned int buffer1_id = 0;
unsigned int program_id = 0;
unsigned int vshader_id = 0;
unsigned int fshader_id = 0;
unsigned int texture_id_yuv_in[2];
unsigned int texture_id_yuv_out[2];
unsigned int fbo_id_yuv_out[2];

GLfloat texturecoords_data[] =
{
    0.0, 1.0,
    1.0, 1.0,
    1.0, 0.0,
    0.0, 0.0
};

GLfloat vetexcoords_data[] =
{
    -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
};

static void HI_OUTYUV_RawFileClear(const char *file)
{
    FILE* raw = fopen(file, "w");
    fclose(raw);
}

static void HI_OUTYUV_RawDataSave(const char *file, void *src, int size)
{
    FILE* raw = fopen(file, "a");
    fwrite(src, size, 1, raw);
    fclose(raw);
}

int main(int argc, char * argv[])
{
    fprintf(stderr, "\n>>>>>>>>>>>>>>>>start>>>>>>>>>>>>>>>>\n");

    NativeDisplayType native_display;
    EGLConfig egl_config;
    EGLContext egl_context;
    EGLDisplay egl_display;
    EGLSurface egl_surface;
    EGLImageKHR egl_image_yuv_in[2];
    EGLImageKHR egl_image_yuv_out[2];
    NativePixmapType native_pixmap_yuv_in[2];
    NativePixmapType native_pixmap_yuv_out[2];
    NativeWindowType native_window;
    unsigned int mmz_addr_in[2];
    unsigned int mmz_addr_out[2];
    void *vir_addr_in[2];
    void *vir_addr_out[2];
    int matching_configs;
    int ret, i;
    int window_width = HD_WIDTH, window_height = HD_HEIGHT;
    int texture_width = TEXTURE_WIDTH, texture_height = TEXTURE_HEIGHT;

    int configAttribs[] =
    {
        EGL_SAMPLES,      0,
        EGL_RED_SIZE,     8,
        EGL_GREEN_SIZE,   8,
        EGL_BLUE_SIZE,    8,
        EGL_ALPHA_SIZE,   8,
        EGL_DEPTH_SIZE,   0,
        EGL_STENCIL_SIZE, 0,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_NONE,
    };

    int ctxAttribs[] =
    {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

#ifdef FRAMEBUFFER_DEVICE_OPEN
    int framebuffer_fd = HI_COMMON_OpenFramebufferDevice(window_width, window_height, DISPLAY_FORMAT_ARGB8888);
    if (-1 == framebuffer_fd)
    {
        HI_COMMON_CloseFramebufferDevice(framebuffer_fd);
        fprintf(stderr, "open framebuffer device failed\n");
        return 0;
    }
#endif

    native_display = HI_COMMON_CreateNativeDisplay(window_width, window_height);

    native_window = HI_COMMON_CreateNativeWindow(window_width, window_height);

    /* create native pixmap*/
    for(i = 0; i < 2; i++)
    {
        mmz_addr_in[i] = HI_COMMON_CreateMMZMemory(texture_width * texture_height / (i+1));
        mmz_addr_out[i] = HI_COMMON_CreateMMZMemory(texture_width * texture_height / (i+1));

        native_pixmap_yuv_in[i] = HI_COMMON_CreateYuvNativePixmap(mmz_addr_in[i], texture_width/(1+i), texture_height/(1+i), 0, 0, 0, 8*i, 8);
        native_pixmap_yuv_out[i] = HI_COMMON_CreateYuvNativePixmap(mmz_addr_out[i], texture_width/(1+i), texture_height/(1+i), 0, 0, 0, 8*i, 8);
    }

    /* >>>>>>>>>>>>>>>>>>>>>>>>> EGL process >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
    egl_display = eglGetDisplay(native_display);

    ret = eglBindAPI(EGL_OPENGL_ES_API);
    ASSERT_EQUAL(ret, EGL_TRUE);

    ret = eglInitialize(egl_display, NULL, NULL);
    ASSERT_EQUAL(ret, EGL_TRUE);

    ret = eglChooseConfig(egl_display, configAttribs, &egl_config, 1, &matching_configs);
    ASSERT_EQUAL(ret, EGL_TRUE);

    /* create egl surfaces */
    egl_surface = eglCreateWindowSurface(egl_display, egl_config, native_window, NULL);
    ASSERT_NOT_EQUAL((unsigned long)egl_surface, (unsigned long)EGL_NO_SURFACE);

    egl_context = eglCreateContext(egl_display, egl_config, NULL, ctxAttribs);
    ASSERT_EQUAL(ret,EGL_TRUE);

    ret = eglMakeCurrent(egl_display, egl_surface, egl_surface, egl_context);
    ASSERT_EQUAL(ret,EGL_TRUE);

    /* >>>>>>>>>>>>>>>>>>>>>>>>> opengles process >>>>>>>>>>>>>>>>>>>>>>>>>>> */

    /* step 1: create vetex shader and fragment shader */
    vshader_id     = HI_COMMON_CreateShader(VERT_SRC,    GL_VERTEX_SHADER);
    fshader_id_y   = HI_COMMON_CreateShader(FRAG_SRC_Y,  GL_FRAGMENT_SHADER);
    fshader_id_uv  = HI_COMMON_CreateShader(FRAG_SRC_UV, GL_FRAGMENT_SHADER);

    /* step 2: create program */
    program_id = HI_COMMON_CreateProgram(vshader_id, fshader_id_y);

    /* step 3: create buffer */
    buffer0_id = HI_COMMON_CreateBuffer(GL_ARRAY_BUFFER, sizeof(float)*3*4, (const void*)vetexcoords_data);
    buffer1_id = HI_COMMON_CreateBuffer(GL_ARRAY_BUFFER, sizeof(float)*2*4, (const void*)texturecoords_data);

    /* step 4: create eglimage */
    for (i = 0; i < 2; i++)
    {
        vir_addr_in[i] = HI_COMMON_MapMMZMemory(mmz_addr_in[i]);

        memcpy(
            (void*)vir_addr_in[i],
            (void*)HI_COMMON_LoadFile(YUV_FILE_IN, texture_width*texture_height*i, texture_width*texture_height/(i+1), "r"), 
            texture_width*texture_height/(i+1)
        );

        HI_COMMON_UnmapMMZMemory(mmz_addr_in[i]);
    }

    for(i = 0; i < 2; i++)
    {
        egl_image_yuv_in[i] = eglCreateImageKHR(egl_display, NULL, EGL_NATIVE_PIXMAP_KHR, (EGLClientBuffer)native_pixmap_yuv_in[i], NULL);
        egl_image_yuv_out[i] = eglCreateImageKHR(egl_display, NULL, EGL_NATIVE_PIXMAP_KHR, (EGLClientBuffer)native_pixmap_yuv_out[i], NULL);
    }

    /* step 5: create texture */
    for(i = 0; i < 2; i++)
    {
        texture_id_yuv_in[i] = HI_COMMON_CreateTexture(GL_TEXTURE0+i, GL_TEXTURE_EXTERNAL_OES, GL_CLAMP_TO_EDGE, GL_NEAREST);
        glEGLImageTargetTexture2DOES(GL_TEXTURE_EXTERNAL_OES, egl_image_yuv_in[i]);

        texture_id_yuv_out[i] = HI_COMMON_CreateTexture(GL_TEXTURE2+i, GL_TEXTURE_2D, GL_CLAMP_TO_EDGE, GL_LINEAR);
        glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, (GLeglImageOES)egl_image_yuv_out[i]);
    }

    /* step 6: create framebuffer object */
    for(i = 0; i < 2; i++)
    {
        fbo_id_yuv_out[i] = HI_COMMON_CreateFBO(texture_id_yuv_out[i], GL_TEXTURE_2D, GL_COLOR_ATTACHMENT0);
    }

    HI_OUTYUV_RawFileClear(YUV_FILE_OUT);

	/* step 7: start to draw */
    for(i = 0; i < 2; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo_id_yuv_out[i]);

        /* step 7: get the location of attribute and uniform */
        HI_COMMON_DestroyProgram(program_id);
        program_id = HI_COMMON_CreateProgram(vshader_id, fshader_id_y + i);

        attribute0_location = glGetAttribLocation(program_id, "aposition");
        glEnableVertexAttribArray(attribute0_location);

        attribute1_location = glGetAttribLocation(program_id, "atexcoord");
        glEnableVertexAttribArray(attribute1_location);

        uniform0_location = glGetUniformLocation(program_id, "luminance");
        glUniform1i(uniform0_location, 0);

        uniform1_location = glGetUniformLocation(program_id, "luminance_alpha");
        glUniform1i(uniform1_location, 1);

        /* step 8: start opengles process */
        glViewport(0,0, texture_width/(i+1), texture_height/(i+1));
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, buffer0_id);
        glVertexAttribPointer(attribute0_location, 3, GL_FLOAT, 0, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, buffer1_id);
        glVertexAttribPointer(attribute1_location, 2, GL_FLOAT, 0, 0, 0);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glFinish();
    }

    for(i = 0; i < 2; i++)
    {
        vir_addr_out[i] = HI_COMMON_MapMMZMemory(mmz_addr_out[i]);

        HI_OUTYUV_RawDataSave("yuv420sp_out.yuv", vir_addr_out[i], texture_width * texture_height / (i+1));

        HI_COMMON_UnmapMMZMemory(mmz_addr_out[i]);
    }

    HI_COMMON_DestroyBuffer(buffer0_id);
    HI_COMMON_DestroyBuffer(buffer1_id);

    for(i = 0; i < 2; i++)
    {
        HI_COMMON_DestroyFBO(fbo_id_yuv_out[i]);
        HI_COMMON_DestroyTexture(texture_id_yuv_in[i]);
        HI_COMMON_DestroyTexture(texture_id_yuv_out[i]);
    }

    HI_COMMON_DestroyProgram(program_id);
    HI_COMMON_DestroyShader(vshader_id);
    HI_COMMON_DestroyShader(fshader_id_y);
    HI_COMMON_DestroyShader(fshader_id_uv);

    ret = eglMakeCurrent(egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    ASSERT_EQUAL(ret,EGL_TRUE);

    ret = eglDestroyContext(egl_display, egl_context);
    ASSERT_EQUAL(ret,EGL_TRUE);

    ret = eglDestroySurface(egl_display, egl_surface);
    ASSERT_EQUAL(ret,EGL_TRUE);

    ret = eglTerminate(egl_display);
    ASSERT_EQUAL(ret,EGL_TRUE);

    for(i = 0; i < 2; i++)
    {
        HI_COMMON_DestroyMMZMemory(mmz_addr_in[i]);
        HI_COMMON_DestroyMMZMemory(mmz_addr_out[i]);
        HI_COMMON_DestroyNativePixmap(native_pixmap_yuv_in[i]);
        HI_COMMON_DestroyNativePixmap(native_pixmap_yuv_out[i]);
    }

    HI_COMMON_DestroyNativeWindow(native_window);
    HI_COMMON_DestroyNativeDisplay(native_display);

#if defined(FRAMEBUFFER_DEVICE_OPEN)
    HI_COMMON_CloseFramebufferDevice(framebuffer_fd);
#endif

    fprintf(stderr, "\n>>>>>>>>>>>>>>>>end>>>>>>>>>>>>>>>>\n");

    return 0;
}
