#===============================================================================
# rules
#===============================================================================
include config.mak

.PHONY: all clean

all:
	echo "$(SDK_DIR)"
ifeq ($(EGL_API_WAYLAND),1)
	$(AT)make -C es20_eglCreateWindowSurface
else
	$(AT)make -C es20_eglCreateWindowSurface
	$(AT)make -C es20_eglCreatePixmapSurface
	$(AT)make -C es20_eglCreatePbufferSurface
	$(AT)make -C es20_eglCreateSyncKHR
	$(AT)make -C es20_glBlendFunc
	$(AT)make -C es20_glEGLImageTargetTexture2DOES
	$(AT)make -C es20_eglCreateFramebufeerObject
	$(AT)make -C es20_yuv420sp_to_rgba8888_windowsurface
	#$(AT)make -C es20_yuv420sp_to_yuv420sp_framebufferobject
endif

clean:

ifeq ($(EGL_API_WAYLAND),1)
	$(AT)make -C es20_eglCreateWindowSurface clean
else
	$(AT)make -C es20_eglCreateWindowSurface clean
	$(AT)make -C es20_eglCreatePixmapSurface clean
	$(AT)make -C es20_eglCreatePbufferSurface clean
	$(AT)make -C es20_eglCreateSyncKHR clean
	$(AT)make -C es20_glBlendFunc clean
	$(AT)make -C es20_glEGLImageTargetTexture2DOES clean
	$(AT)make -C es20_eglCreateFramebufeerObject clean
	$(AT)make -C es20_yuv420sp_to_rgba8888_windowsurface clean
	#$(AT)make -C es20_yuv420sp_to_yuv420sp_framebufferobject clean
endif
