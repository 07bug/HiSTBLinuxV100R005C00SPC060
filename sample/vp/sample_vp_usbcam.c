/******************************************************************************

  Copyright (C), 2001-2013, Hisilicon Tech. Co., Ltd.

******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <linux/videodev2.h>
#include <fcntl.h>
#include <string.h>
#include <net/if.h>
#include <sys/time.h>

#include "hi_unf_common.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_vi.h"
#include "hi_unf_venc.h"
#include "hi_unf_vp.h"
#include "hi_unf_hdmi.h"
#include "hi_adp.h"
#include "hi_adp_hdmi.h"
#include "hi_adp_mpi.h"

static pthread_t g_threadSampleStatics;
static HI_U32 g_stopGet = 1;

#define SAMPLE_USBCAM_FRAME_RATE 30
static HI_U32 g_u32FrameRate = SAMPLE_USBCAM_FRAME_RATE;
static HI_U32 g_u32VencWidth = 640;
static HI_U32 g_u32VencHeight = 480;
static HI_U32 g_u32CamWidth = 640;
static HI_U32 g_u32CamHeight = 480;

#define DFLT_SCOPE_ID  "eth0"  /* Default scope identifier.  */
#define DFLT_RTP_PORT  16384  /* Default RTP port.  */

static char* g_UsbCamDev = "/dev/video0";
static HI_BOOL g_UsbPlugFlag = HI_FALSE;

typedef struct hiUSB_CAM_THREAD_ARG_S
{
    HI_HANDLE hVP;
    HI_U32    u32USBCamFmt;
    HI_S32       UsbCamFd;
} USB_CAM_THREAD_ARG_S;

typedef enum tagRTP_PAYLOAD_TYPE_E
{
    RTP_PT_ULAW = 0,           /* mu-law */
    RTP_PT_GSM  = 3,           /* GSM */
    RTP_PT_G723 = 4,           /* G.723 */
    RTP_PT_ALAW = 8,           /* a-law */
    RTP_PT_G722 = 9,           /* G.722 */
    RTP_PT_S16BE_STEREO = 10,  /* linear 16, 44.1khz, 2 channel */
    RTP_PT_S16BE_MONO = 11,    /* linear 16, 44.1khz, 1 channel */
    RTP_PT_MPEGAUDIO = 14,     /* mpeg audio */
    RTP_PT_JPEG = 26,          /* jpeg */
    RTP_PT_H261 = 31,          /* h.261 */
    RTP_PT_MPEGVIDEO = 32,     /* mpeg video */
    RTP_PT_MPEG2TS = 33,       /* mpeg2 TS stream */
    RTP_PT_H263  = 34,         /* old H263 encapsulation */
    RTP_PT_H264  = 96,         /* hisilicon define as h.264 */
    RTP_PT_G726  = 97,         /* hisilicon define as G.726 */
    RTP_PT_ADPCM = 98,         /* hisilicon define as ADPCM */
    RTP_PT_AAC  = 99,          /* hisilicon define as AAC */
    RTP_PT_DATA = 100,         /* hisilicon define as md alarm data */
    RTP_PT_ARM     = 101,      /* hisilicon define as AMR */
    RTP_PT_MJPEG   = 102,      /* hisilicon define as MJPEG */
    RTP_PT_H265  = 103,
    RTP_PT_INVALID = 127
} RTP_PAYLOAD_TYPE_E;

static pthread_t g_threadUSBCam;
USB_CAM_THREAD_ARG_S g_stUSBCamArgs;
static HI_BOOL g_bUSBCamStop = HI_FALSE;

/*********************************************************************
 *******************************  USB cam *****************************
 **********************************************************************/
#define V4L2_CID_TILT_SPEED         (V4L2_CID_CAMERA_CLASS_BASE+33)

char ioctl_stream[64][64] =
{"V4L2_CID_EXPOSURE_AUTO",
"V4L2_CID_EXPOSURE_ABSOLUTE",
"V4L2_CID_EXPOSURE_AUTO_PRIORITY",
"V4L2_CID_PAN_RELATIVE",
"V4L2_CID_TILT_RELATIVE",
"V4L2_CID_PAN_RESET",
"V4L2_CID_TILT_RESET",
"V4L2_CID_PAN_ABSOLUTE",
"V4L2_CID_TILT_ABSOLUTE",
"V4L2_CID_FOCUS_ABSOLUTE",
"V4L2_CID_FOCUS_RELATIVE",
"V4L2_CID_FOCUS_AUTO",
"V4L2_CID_ZOOM_ABSOLUTE",
"V4L2_CID_ZOOM_RELATIVE",
"V4L2_CID_ZOOM_CONTINUOUS",
"V4L2_CID_PRIVACY",
"V4L2_CID_IRIS_ABSOLUTE",
"V4L2_CID_IRIS_RELATIVE",
"V4L2_CID_AUTO_EXPOSURE_BIAS",
"V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE",
"V4L2_CID_WIDE_DYNAMIC_RANGE",
"V4L2_CID_IMAGE_STABILIZATION",
"V4L2_CID_ISO_SENSITIVITY",
"V4L2_CID_ISO_SENSITIVITY_AUTO",
"V4L2_CID_EXPOSURE_METERING",
"V4L2_CID_SCENE_MODE",
"V4L2_CID_3A_LOCK",
"V4L2_CID_AUTO_FOCUS_START",
"V4L2_CID_AUTO_FOCUS_STOP",
"V4L2_CID_AUTO_FOCUS_STATUS",
"V4L2_CID_AUTO_FOCUS_RANGE",
"V4L2_CID_PAN_SPEED",
"V4L2_CID_TILT_SPEED"
};

char usr_ioctl_stream[64][64] =
{
"V4L2_CID_BRIGHTNESS",
"V4L2_CID_CONTRAST",
"V4L2_CID_SATURATION",
"V4L2_CID_HUE",
"V4L2_CID_AUDIO_VOLUME",
"V4L2_CID_AUDIO_BALANCE",
"V4L2_CID_AUDIO_BASS",
"V4L2_CID_AUDIO_TREBLE",
"V4L2_CID_AUDIO_MUTE",
"V4L2_CID_AUDIO_LOUDNESS",
"V4L2_CID_BLACK_LEVEL",
"V4L2_CID_AUTO_WHITE_BALANCE",
"V4L2_CID_DO_WHITE_BALANCE",
"V4L2_CID_RED_BALANCE",
"V4L2_CID_BLUE_BALANCE",
"V4L2_CID_GAMMA",
"V4L2_CID_EXPOSURE",
"V4L2_CID_AUTOGAIN",
"V4L2_CID_GAIN",
"V4L2_CID_HFLIP",
"V4L2_CID_VFLIP",
"V4L2_CID_POWER_LINE_FREQUENCY",
"V4L2_CID_HUE_AUTO",
"V4L2_CID_WHITE_BALANCE_TEMPERATURE",
"V4L2_CID_SHARPNESS",
"V4L2_CID_BACKLIGHT_COMPENSATION ",
"V4L2_CID_CHROMA_AGC",
"V4L2_CID_COLOR_KILLER",
"V4L2_CID_COLORFX",
"V4L2_CID_AUTOBRIGHTNESS",
"V4L2_CID_BAND_STOP_FILTER",
"V4L2_CID_ROTATE",
"V4L2_CID_BG_COLOR",
"V4L2_CID_CHROMA_GAIN",
"V4L2_CID_ILLUMINATORS_1",
"V4L2_CID_ILLUMINATORS_2",
"V4L2_CID_MIN_BUFFERS_FOR_CAPTURE",
"V4L2_CID_MIN_BUFFERS_FOR_OUTPUT",
"V4L2_CID_ALPHA_COMPONENT",
"V4L2_CID_COLORFX_CBCR",
"V4L2_CID_LASTP1"
};

int camera_open(int num)
{
    int fd;
    char devName[64] = {0};
    struct stat st;

    snprintf(devName, sizeof(devName), "/dev/video%d", num);
    fd = open(devName, O_RDWR | O_NONBLOCK, 0);
    if (fd < 0)
    {
        printf("open video%d failed[%d-%s]\n", num, errno, strerror(errno));
        return -101;
    }

    if (fstat(fd, &st) < 0)
    {
        close(fd);
        printf("fstat handle=%d failed[%d-%s]\n", fd, errno, strerror(errno));
        return -102;
    }

    if (!S_ISCHR(st.st_mode))
    {
        close(fd);
        return -103;
    }
    return fd;
}

int camera_set(int fd, char*str, int value)
{
    int ret = 0;
    int i = 0;
    int cmd = 0;
    if (fd < 0)
    {
        printf("open /dev/videox failed, fd=%d\n", fd);
        return -301;
    }
    for(i = 0; i < 64; i ++)
    {
        if(strcmp(ioctl_stream[i], str) == 0){
            cmd = V4L2_CID_EXPOSURE_AUTO + i;
            break;
        }
    }
    for(i = 0; i < 64; i ++)
    {
        if(strcmp(usr_ioctl_stream[i], str) == 0){
            cmd = V4L2_CID_BRIGHTNESS + i;
            break;
        }
    }

    if(cmd == 0)
    {
        ret = -301;
        goto RET;
    }

    struct v4l2_control ctrl;
    memset(&ctrl, 0, sizeof(ctrl));
    ctrl.id = cmd;
    if (ioctl(fd, VIDIOC_G_CTRL, &ctrl) < 0)
    {
        printf("    VIDIOC_G_CTRL  %s  id[%d] failed[%d-%s]\n", str, ctrl.id, errno, strerror(errno));
        ret = -302;
        goto RET;
    }else{
        printf("    VIDIOC_G_CTRL  %s id = 0x%x\n", str, ctrl.id);
        printf("    VIDIOC_G_CTRL  %s value = 0x%x\n", str, ctrl.value);
    }
    struct v4l2_queryctrl  setting;
    memset(&setting, 0, sizeof(setting));
    setting.id = cmd;
    if (ioctl(fd, VIDIOC_QUERYCTRL, &setting) < 0)
    {
        printf("    VIDIOC_QUERYCTRL %s  id[%d] failed[%d-%s]\n", str, ctrl.id, errno, strerror(errno));
        ret = -303;
        goto RET;
    }else{
        printf("    VIDIOC_QUERYCTRL  %s id = 0x%x\n", str, setting.id);
        printf("    VIDIOC_QUERYCTRL  %s type = 0x%x\n", str, setting.type);
        printf("    VIDIOC_QUERYCTRL  %s name = %s\n", str, setting.name);
        printf("    VIDIOC_QUERYCTRL  %s minimum = 0x%x\n", str, setting.minimum);
        printf("    VIDIOC_QUERYCTRL  %s maximum = 0x%x\n", str, setting.maximum);
        printf("    VIDIOC_QUERYCTRL  %s step = 0x%x\n", str, setting.step);
        printf("    VIDIOC_QUERYCTRL  %s default_value = 0x%x\n", str, setting.default_value);
        printf("    VIDIOC_QUERYCTRL  %s flags = 0x%x\n", str, setting.flags);
    }
    if (value < setting.minimum || value > setting.maximum || ((value - setting.minimum) % setting.step != 0))
    {
        printf("inivalid parameter, value=%d[limit:%d-%d, step=%d]\n", value, setting.minimum, setting.maximum, setting.step);
        ret = -304;
        goto RET;
    }
    memset(&ctrl, 0, sizeof(ctrl));
    ctrl.id = cmd;
    ctrl.value = value;
    if (ioctl(fd, VIDIOC_S_CTRL, &ctrl) < 0)
    {
        printf("VIDIOC_S_CTRL %s  id[%d] value[%d] failed[%d-%s]\n", str, ctrl.id, ctrl.value, errno, strerror(errno));
        ret = -305;
        goto RET;
    }
    memset(&ctrl, 0, sizeof(ctrl));
    ctrl.id = cmd;
    if (ioctl(fd, VIDIOC_G_CTRL, &ctrl) < 0)
    {
        printf("VIDIOC_G_CTRL %s  id[%d] failed[%d-%s]\n", str, ctrl.id, errno, strerror(errno));
        ret = -306;
        goto RET;
    }else{
        printf("VIDIOC_G_CTRL  %s id = 0x%x\n", str, ctrl.id);
        printf("VIDIOC_G_CTRL  %s value = 0x%x\n", str, ctrl.value);
    }
RET:
    return ret;
}


int camera_get(int fd, char*str)
{
    int ret = 0;
    int i = 0;
    int cmd = 0;
    if (fd < 0)
    {
        printf("open /dev/videox failed, fd=%d\n", fd);
        return -301;
    }
    for(i = 0; i < 64; i ++)
    {
        if(strcmp(ioctl_stream[i], str) == 0){
            cmd = V4L2_CID_EXPOSURE_AUTO + i;
            break;
        }
    }
    for(i = 0; i < 64; i ++)
    {
        if(strcmp(usr_ioctl_stream[i], str) == 0){
            cmd = V4L2_CID_BRIGHTNESS + i;
            break;
        }
    }

    if(cmd == 0)
    {
        ret = -301;
        goto RET;
    }

    struct v4l2_control ctrl;
    memset(&ctrl, 0, sizeof(ctrl));
    ctrl.id = cmd;
    if (ioctl(fd, VIDIOC_G_CTRL, &ctrl) < 0)
    {
        printf("    VIDIOC_G_CTRL  %s  id[%d] failed[%d-%s]\n", str, ctrl.id, errno, strerror(errno));
        ret = -302;
        goto RET;
    }else{
        printf("    VIDIOC_G_CTRL  %s id = 0x%x\n", str, ctrl.id);
        printf("    VIDIOC_G_CTRL  %s value = 0x%x\n", str, ctrl.value);
    }
    struct v4l2_queryctrl  setting;
    memset(&setting, 0, sizeof(setting));
    setting.id = cmd;
    if (ioctl(fd, VIDIOC_QUERYCTRL, &setting) < 0)
    {
        printf("    VIDIOC_QUERYCTRL %s  id[%d] failed[%d-%s]\n", str, ctrl.id, errno, strerror(errno));
        ret = -303;
        goto RET;
    }else{
        printf("    VIDIOC_QUERYCTRL  %s id = 0x%x\n", str, setting.id);
        printf("    VIDIOC_QUERYCTRL  %s type = 0x%x\n", str, setting.type);
        printf("    VIDIOC_QUERYCTRL  %s name = %s\n", str, setting.name);
        printf("    VIDIOC_QUERYCTRL  %s minimum = 0x%x\n", str, setting.minimum);
        printf("    VIDIOC_QUERYCTRL  %s maximum = 0x%x\n", str, setting.maximum);
        printf("    VIDIOC_QUERYCTRL  %s step = 0x%x\n", str, setting.step);
        printf("    VIDIOC_QUERYCTRL  %s default_value = 0x%x\n", str, setting.default_value);
        printf("    VIDIOC_QUERYCTRL  %s flags = 0x%x\n", str, setting.flags);
    }
RET:
    return ret;
}


int get_info(int fd)
{
    int ret = 0;
    int i = 0;

    if (fd < 0)
    {
        printf("open /dev/videox failed, fd=%d\n", fd);
        return -501;
    }
    struct v4l2_queryctrl  setting;
    struct v4l2_control ctrl;

    for(i = V4L2_CID_EXPOSURE_AUTO; i <= V4L2_CID_TILT_SPEED; i ++){
        printf("*************************%s********************************\n", ioctl_stream[i-V4L2_CID_EXPOSURE_AUTO]);
        memset(&ctrl, 0, sizeof(ctrl));
        ctrl.id = i;
        if (ioctl(fd, VIDIOC_G_CTRL, &ctrl) < 0)
        {
            printf("    VIDIOC_G_CTRL %s  id[%d] failed[%d-%s]\n", ioctl_stream[i-V4L2_CID_EXPOSURE_AUTO], ctrl.id, errno, strerror(errno));
            ret = -508;
            //goto RET;
        }
        else{
            printf("    VIDIOC_G_CTRL  %s id = 0x%x\n",ioctl_stream[i-V4L2_CID_EXPOSURE_AUTO], ctrl.id);
            printf("    VIDIOC_G_CTRL  %s value = 0x%x\n",ioctl_stream[i-V4L2_CID_EXPOSURE_AUTO], ctrl.value);
        }

        memset(&setting, 0, sizeof(setting));
        setting.id = i;
        if (ioctl(fd, VIDIOC_QUERYCTRL, &setting) < 0)
        {
            printf("    VIDIOC_QUERYCTRL %s id[%d] failed[%d-%s]\n", ioctl_stream[i-V4L2_CID_EXPOSURE_AUTO], ctrl.id, errno, strerror(errno));
            ret = -509;
            //goto RET;
        }
        else{
            printf("    VIDIOC_QUERYCTRL  %s id = 0x%x\n", ioctl_stream[i-V4L2_CID_EXPOSURE_AUTO], setting.id);
            printf("    VIDIOC_QUERYCTRL  %s type = 0x%x\n", ioctl_stream[i-V4L2_CID_EXPOSURE_AUTO], setting.type);
            printf("    VIDIOC_QUERYCTRL  %s name = %s\n", ioctl_stream[i-V4L2_CID_EXPOSURE_AUTO], setting.name);
            printf("    VIDIOC_QUERYCTRL  %s minimum = 0x%x\n", ioctl_stream[i-V4L2_CID_EXPOSURE_AUTO], setting.minimum);
            printf("    VIDIOC_QUERYCTRL  %s maximum = 0x%x\n", ioctl_stream[i-V4L2_CID_EXPOSURE_AUTO], setting.maximum);
            printf("    VIDIOC_QUERYCTRL  %s step = 0x%x\n", ioctl_stream[i-V4L2_CID_EXPOSURE_AUTO], setting.step);
            printf("    VIDIOC_QUERYCTRL  %s default_value = 0x%x\n", ioctl_stream[i-V4L2_CID_EXPOSURE_AUTO], setting.default_value);
            printf("    VIDIOC_QUERYCTRL  %s flags = 0x%x\n", ioctl_stream[i-V4L2_CID_EXPOSURE_AUTO], setting.flags);
        }
    }


    for(i = V4L2_CID_BRIGHTNESS; i <= V4L2_CID_LASTP1; i ++){
        printf("*************************%s********************************\n", usr_ioctl_stream[i-V4L2_CID_BRIGHTNESS]);
        memset(&ctrl, 0, sizeof(ctrl));
        ctrl.id = i;
        if (ioctl(fd, VIDIOC_G_CTRL, &ctrl) < 0)
        {
            printf("    VIDIOC_G_CTRL %s  id[%d] failed[%d-%s]\n", usr_ioctl_stream[i-V4L2_CID_BRIGHTNESS], ctrl.id, errno, strerror(errno));
            ret = -508;
            //goto RET;
        }
        else{
            printf("    VIDIOC_G_CTRL  %s id = 0x%x\n",usr_ioctl_stream[i-V4L2_CID_BRIGHTNESS], ctrl.id);
            printf("    VIDIOC_G_CTRL  %s value = 0x%x\n",usr_ioctl_stream[i-V4L2_CID_BRIGHTNESS], ctrl.value);
        }

        memset(&setting, 0, sizeof(setting));
        setting.id = i;
        if (ioctl(fd, VIDIOC_QUERYCTRL, &setting) < 0)
        {
            printf("    VIDIOC_QUERYCTRL %s id[%d] failed[%d-%s]\n", usr_ioctl_stream[i-V4L2_CID_BRIGHTNESS], ctrl.id, errno, strerror(errno));
            ret = -509;
            //goto RET;
        }
        else{
            printf("    VIDIOC_QUERYCTRL  %s id = 0x%x\n", usr_ioctl_stream[i-V4L2_CID_BRIGHTNESS], setting.id);
            printf("    VIDIOC_QUERYCTRL  %s type = 0x%x\n", usr_ioctl_stream[i-V4L2_CID_BRIGHTNESS], setting.type);
            printf("    VIDIOC_QUERYCTRL  %s name = %s\n", usr_ioctl_stream[i-V4L2_CID_BRIGHTNESS], setting.name);
            printf("    VIDIOC_QUERYCTRL  %s minimum = 0x%x\n", usr_ioctl_stream[i-V4L2_CID_BRIGHTNESS], setting.minimum);
            printf("    VIDIOC_QUERYCTRL  %s maximum = 0x%x\n", usr_ioctl_stream[i-V4L2_CID_BRIGHTNESS], setting.maximum);
            printf("    VIDIOC_QUERYCTRL  %s step = 0x%x\n", usr_ioctl_stream[i-V4L2_CID_BRIGHTNESS], setting.step);
            printf("    VIDIOC_QUERYCTRL  %s default_value = 0x%x\n", usr_ioctl_stream[i-V4L2_CID_BRIGHTNESS], setting.default_value);
            printf("    VIDIOC_QUERYCTRL  %s flags = 0x%x\n", usr_ioctl_stream[i-V4L2_CID_BRIGHTNESS], setting.flags);
        }
    }

//RET:
    return ret;
}
HI_U32 SampleUsbCamInit(USB_CAM_THREAD_ARG_S* pArgs)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 fdUsbCam  = 0;
    struct v4l2_streamparm* setfps;
    struct v4l2_capability stUsbCap;
    struct v4l2_format stUsbFmt = {0};
    HI_S32 fps = g_u32FrameRate;
    char*   TmpCamDev = "/dev/video1";

    /* open usb camera with non-block mode */
    fdUsbCam = open(g_UsbCamDev, O_RDWR | O_NONBLOCK, 0);

    if (HI_FAILURE == fdUsbCam)
    {
        fdUsbCam = open(TmpCamDev, O_RDWR | O_NONBLOCK, 0);

        if (HI_FAILURE == fdUsbCam)
        {
            printf("open %s failed\r\n", TmpCamDev);
            return HI_FAILURE;
        }
    }
    else
    {
        printf("open %s Ok\r\n", g_UsbCamDev);
    }

    s32Ret = ioctl(fdUsbCam, VIDIOC_QUERYCAP, &stUsbCap);
    printf("usb cam cap:0x%x.\n", stUsbCap.capabilities);

    if (s32Ret < 0)
    {
        printf("Error opening device %s: unable to query device.\n", g_UsbCamDev);
        close(fdUsbCam);
        return HI_FAILURE;
    }

    if ((stUsbCap.capabilities & V4L2_CAP_VIDEO_CAPTURE) == 0)
    {
        printf("Error opening device %s: video capture not supported.\n", g_UsbCamDev);
        close(fdUsbCam);
        return HI_FAILURE;
    }

    if (!(stUsbCap.capabilities & V4L2_CAP_STREAMING))
    {
        printf("%s Not support streaming i/o\n", g_UsbCamDev);
        close(fdUsbCam);
        return HI_FAILURE;
    }

    /* test format if it supports */
    memset(&stUsbFmt, 0, sizeof(struct v4l2_format));
    stUsbFmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if (ioctl(fdUsbCam, VIDIOC_G_FMT, &stUsbFmt) < 0)
    {
        PRINT_SMP("get format failed\n");
        close(fdUsbCam);
        return HI_FAILURE;
    }
    else
    {
        printf("USB CAM's orignal FMT:\n");
        printf("Width = %d\n", stUsbFmt.fmt.pix.width);
        printf("Height = %d\n", stUsbFmt.fmt.pix.height);
        printf("Image size = %d\n", stUsbFmt.fmt.pix.sizeimage);
        printf("pixelformat = %d\n", stUsbFmt.fmt.pix.pixelformat);
        printf("field = %d\n", stUsbFmt.fmt.pix.field);

        if (V4L2_PIX_FMT_MJPEG == stUsbFmt.fmt.pix.pixelformat)
        {
            printf("V4L2_PIX_FMT_MJPEG\r\n");
        }
        else if (V4L2_PIX_FMT_YUYV == stUsbFmt.fmt.pix.pixelformat)
        {
            printf("V4L2_PIX_FMT_YUYV\r\n");
        }
        else
        {
            printf("fmt unknown\r\n");
        }

        printf("\n");
    }

    /* set format */
    stUsbFmt.fmt.pix.width  = g_u32CamWidth;
    stUsbFmt.fmt.pix.height = g_u32CamHeight;
    stUsbFmt.fmt.pix.pixelformat = pArgs->u32USBCamFmt;
    s32Ret = ioctl(fdUsbCam, VIDIOC_S_FMT, &stUsbFmt);

    if (s32Ret < 0)
    {
        printf("Unable to set format: %d, err:%d.\n", stUsbFmt.fmt.pix.pixelformat, errno);
        close(fdUsbCam);
        return s32Ret;
    }

    if (ioctl(fdUsbCam, VIDIOC_G_FMT, &stUsbFmt) < 0)
    {
        printf("get format failed\n");
        close(fdUsbCam);
        return HI_FAILURE;
    }
    else
    {
        printf("After set attr:\r\nWidth = %d\n", stUsbFmt.fmt.pix.width);
        printf("Height = %d\n", stUsbFmt.fmt.pix.height);
        printf("Image size = %d\n", stUsbFmt.fmt.pix.sizeimage);
        printf("pixelformat = %d\n", stUsbFmt.fmt.pix.pixelformat);

        if (V4L2_PIX_FMT_MJPEG == stUsbFmt.fmt.pix.pixelformat)
        {
            printf("V4L2_PIX_FMT_MJPEG\r\n");
        }
        else if (V4L2_PIX_FMT_YUYV == stUsbFmt.fmt.pix.pixelformat)
        {
            printf("V4L2_PIX_FMT_YUYV\r\n");
        }
        else
        {
            printf("fmt unknown\r\n");
        }

        printf("\n");
    }

    setfps = (struct v4l2_streamparm*)calloc(1, sizeof(struct v4l2_streamparm));

    if (HI_NULL == setfps)
    {
        printf("calloc memory failed, %d, %s\n", __LINE__, __FUNCTION__);
        close(fdUsbCam);
        return HI_FAILURE;
    }

    memset(setfps, 0, sizeof(struct v4l2_streamparm));
    setfps->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    s32Ret = ioctl(fdUsbCam, VIDIOC_G_PARM, setfps);

    if (s32Ret == 0)
    {
        printf("\n  Frame rate:   %u/%u\n",
               setfps->parm.capture.timeperframe.denominator,
               setfps->parm.capture.timeperframe.numerator
              );
    }
    else
    {
        perror("Unable to read out current frame rate");
        free(setfps);
        close(fdUsbCam);
        return HI_FAILURE;
    }

    if ((setfps->parm.capture.timeperframe.numerator == 1)
        && (setfps->parm.capture.timeperframe.denominator == fps))
    {
        ; /* OK, fps is aready the value we want */
    }
    else
    {
        /* set frame rate */
        setfps->parm.capture.timeperframe.numerator   = 1;
        setfps->parm.capture.timeperframe.denominator = fps;
        s32Ret = ioctl(fdUsbCam, VIDIOC_S_PARM, setfps);

        if (HI_FAILURE == s32Ret)
        {
            perror("Unable to set frame rate");
            free(setfps);
            close(fdUsbCam);
            return HI_FAILURE;
        }

        s32Ret = ioctl(fdUsbCam, VIDIOC_G_PARM, setfps);

        if (s32Ret == 0)
        {
            if ((setfps->parm.capture.timeperframe.numerator != 1)
                || (setfps->parm.capture.timeperframe.denominator != fps))
            {
                printf("\n  Frame rate:   %u/%u fps (requested frame rate %u fps is "
                       "not supported by device)\n",
                       setfps->parm.capture.timeperframe.denominator,
                       setfps->parm.capture.timeperframe.numerator,
                       fps);
            }
            else
            {
                printf("\n  Frame rate:   %d fps\n", fps);
            }
        }
        else
        {
            perror("Unable to read out current frame rate");
            free(setfps);
            close(fdUsbCam);
            return HI_FAILURE;
        }
    }

    camera_set(fdUsbCam, "V4L2_CID_EXPOSURE_AUTO", 0x3);
    camera_set(fdUsbCam, "V4L2_CID_EXPOSURE_AUTO_PRIORITY", 0x0);
    camera_set(fdUsbCam, "V4L2_CID_FOCUS_AUTO", 0x0);
    camera_set(fdUsbCam, "V4L2_CID_FOCUS_ABSOLUTE", 0x0);

    printf("\nUSB CAM's output mode: %d \n", setfps->parm.output.outputmode);

    pArgs->UsbCamFd = fdUsbCam;

    return HI_SUCCESS;
}

HI_U32 SampleUsbCamDeinit(USB_CAM_THREAD_ARG_S* pArgs)
{
    close(pArgs->UsbCamFd);

    printf(" Deinit V4L2 \n");

    return HI_SUCCESS;
}

void* USB_ScheduleCheckPlug(void* args)
{
    HI_S32 s32Ret;
    struct v4l2_format stUsbFmt;
    HI_U32 fail_cnt = 0;
    HI_UNF_VP_SOURCE_ATTR_S stSrcAttr = {0};

    USB_CAM_THREAD_ARG_S* pArgs = (USB_CAM_THREAD_ARG_S*)args;
    HI_HANDLE hVP = pArgs->hVP;

    while (!g_bUSBCamStop)
    {
        /*check usb*/
        memset(&stUsbFmt, 0, sizeof(struct v4l2_format));
        stUsbFmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        s32Ret = ioctl(pArgs->UsbCamFd, VIDIOC_G_FMT, &stUsbFmt);

        if (s32Ret < 0)
        {
            usleep(10 * 1000);
            fail_cnt++;

            if (fail_cnt >= 300)
            {
                if (g_UsbPlugFlag)
                {
                    HI_UNF_VP_StopRemote(hVP, HI_UNF_VP_RMT_MODE_SEND);
                    HI_UNF_VP_StopPreView(hVP);
                    HI_UNF_VP_DetachSource(hVP);
                    g_UsbPlugFlag = HI_FALSE;
                }

                SampleUsbCamDeinit(pArgs);

                if (HI_SUCCESS == SampleUsbCamInit(pArgs))
                {
                    stSrcAttr.enSrcMode = HI_UNF_VP_SRC_MODE_USBCAM;
                    stSrcAttr.hSrc = pArgs->UsbCamFd;
                    stSrcAttr.u32VIBufNum = 4;
                    HI_UNF_VP_AttachSource(hVP, &stSrcAttr);
                    HI_UNF_VP_StartPreView(hVP);
                    HI_UNF_VP_StartRemote(hVP, HI_UNF_VP_RMT_MODE_SEND);
                    g_UsbPlugFlag = HI_TRUE;
                }

                fail_cnt = 0;
            }

            continue;
        }
        else
        {
            usleep(10 * 1000);
            fail_cnt = 0;
        }

    }

    return NULL;
}

static HI_S32 Checkipaddr(HI_BOOL bIpv4, HI_CHAR* ipaddr)
{
    struct sockaddr_in  stIpv4Attr;
    struct sockaddr_in6 stIpv6Attr;

    if (bIpv4)
    {
        return inet_pton(AF_INET, ipaddr, (void*)&stIpv4Attr.sin_addr);
    }
    else
    {
        return inet_pton(AF_INET6, ipaddr, (void*)&stIpv6Attr.sin6_addr);
    }
}

HI_VOID* Vp_ScheduleNetStatics(HI_VOID* args)
{
    HI_S32 s32Ret;
    HI_UNF_VP_NET_STA_S stNetStatics;
    HI_HANDLE* hVp = (HI_HANDLE*)args;

    while (!g_stopGet)
    {
        usleep(5000 * 1000);

        if (g_stopGet)
        {
            break;
        }

        s32Ret = HI_UNF_VP_GetNetStatics(*hVp, &stNetStatics);

        if (HI_SUCCESS == s32Ret)
        {
            printf("==================Get Vp Net Statics:===================\n");
            printf("recvbytes:        %u\n", stNetStatics.u32RecvBytes);
            printf("recvpacket:         %u\n", stNetStatics.u32RecvPacketNum);
            printf("sendbytes:        %u\n", stNetStatics.u32SendBytes);
            printf("sendpacket:         %u\n", stNetStatics.u32SendPacketNum);

            printf("LostRate(Recent 5s):        %u%%\n", stNetStatics.stRecvInfo.u32LossFraction);
            printf("Total Lost Packets:         %u\n", stNetStatics.stRecvInfo.u32TotalLostPacket);
            printf("Jitter:                     %u(ms)\n", stNetStatics.stRecvInfo.u32Jitter);
            printf("Delay(total sides):         %u(ms)\n", stNetStatics.stRecvInfo.u32Delay);

            printf("LostRate(Recent 5s):        %u%%\n", stNetStatics.stSendInfo.u32LossFraction);
            printf("Total Lost Packets:         %u\n", stNetStatics.stSendInfo.u32TotalLostPacket);
            printf("Jitter:                     %u(ms)\n", stNetStatics.stSendInfo.u32Jitter);
            printf("Delay(total sides):         %u(ms)\n", stNetStatics.stSendInfo.u32Delay);
            printf("=========================End============================\n");
        }
    }

    return NULL;
}

static HI_S32 Global_Init(HI_UNF_ENC_FMT_E voFormat)
{
    HI_S32 s32Ret;
    s32Ret = HI_SYS_Init();
    s32Ret |= HIADP_MCE_Exit();
    s32Ret |= HI_UNF_AVPLAY_Init();
    s32Ret |= HI_UNF_VI_Init();
    s32Ret |= HI_UNF_VENC_Init();
    s32Ret |= HIADP_Disp_Init(voFormat);
    s32Ret |= HIADP_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);
    s32Ret |= HI_UNF_VP_Init();

    return s32Ret;
}

static HI_S32 Global_DeInit()
{
    HI_S32 s32Ret;

    s32Ret = HI_UNF_AVPLAY_DeInit();
    s32Ret |= HIADP_VO_DeInit();
    s32Ret |= HIADP_Disp_DeInit();
    s32Ret |= HI_UNF_VI_DeInit();
    s32Ret |= HI_UNF_VENC_DeInit();
    s32Ret |= HI_UNF_VP_DeInit();
    s32Ret |= HI_SYS_DeInit();

    return s32Ret;
}
void help(void)
{
    printf("commonds:\n");
    printf("    l: local win display only\n");
    printf("    r: remote win display only\n");
    printf("    b: both local win and  remote win display.\n");
    printf("    lf:local win display full screen.\n");
    printf("    rf:remote win display full screen.\n");
    printf("    ts_b:record begin.\n");
    printf("    ts_e:record end.\n");
    printf("    q: quit.\n");
    printf("    h: help\n");

}

HI_U32 vp_time(void) {
   struct timeval start;
   HI_U32 timeuse;

   gettimeofday( &start, NULL );
   timeuse = 1000000 *  start.tv_sec + start.tv_usec;
   printf("time: %u us\n", timeuse);
   return timeuse;
}

HI_S32 main(HI_S32 argc, HI_CHAR* argv[])
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_HANDLE hVP;
    HI_HANDLE hLocalWin;
    HI_HANDLE hRemoteWin;
    HI_RECT_S stRect = {0};
    HI_UNF_VP_ATTR_S stDefAttr;
    HI_UNF_VP_SOURCE_ATTR_S stSrcAttr = {0};
    HI_UNF_ENC_FMT_E voFormat = HI_UNF_ENC_FMT_720P_50;
    HI_U32 u32CamFormat, u32af_inet, u32CamResolution, u32vencResolution, u32bitRate, u32frameRate;
    HI_FLOAT bitRate;
    HI_U32 u32Width, u32Height;
    HI_CHAR* localIpAddr;
    HI_CHAR* remoteIpAddr;
    HI_UNF_VCODEC_TYPE_E vdecType = HI_UNF_VCODEC_TYPE_H264;
    HI_CHAR             InputCmd[32];
    HI_BOOL             g_VpStop = HI_FALSE;
    HI_UNF_WINDOW_ATTR_S stLocalWinAttr, stRemoteWinAttr;
    HI_CHAR record_file[128] = {0};
    HI_U32 time = 0;
    HI_BOOL record_flag = HI_FALSE;

    if (argc >= 6)
    {
        voFormat = HIADP_Disp_StrToFmt(argv[5]);
    }
    else if (argc == 5)
    {
        voFormat = HI_UNF_ENC_FMT_720P_50;
    }

    else
    {
        printf("Usage: sample_vp_usbcam cam_format af_inet localIP remoteIP \n"
               "       [vo_format] [vtype] [cam_resolution] [venc_resolution] [venc_bitRate] [frame_rate]\n"
               "       cam_format: 1-YUV|0-MJPEG\n"
               "       af_inet: 1-ipv4|0-ipv6\n"
               "       vo_format:2160P_30|2160P_24|1080P_60|1080P_50|1080i_60|1080i_50|720P_60|[720P_50]\n"
               "       vtype: h264|h265.\n"
               "       cam_resolution: 0-1920*1080|1-1280*720|2-720*576|3-640*480|4-352*288|5-176*144|.\n"
               "       venc_type: 0-1920*1080|1-1280*720|2-720*576|3-640*480|4-352*288|5-176*144|.\n"
               "       venc_bitRate: xxM | xxK, float.\n"
               "       frame_rate: 1-60, default 30.\n"
               "Example:./sample_vp_usbcam 0 1 192.168.1.2 192.168.1.3 720p_50\n"
               "Example:./sample_vp_usbcam 1 0 fe80::228:1ff:fe19:777 fe80::228:2ff:fe19:777 720p_50\n"
               "Example:./sample_vp_usbcam 0 1 192.168.1.2 192.168.1.2\n"
               "Example:./sample_vp_usbcam 0 1 192.168.1.2 192.168.1.2 1080p_50 h265 0 0 1.5M 30\n");
        return 0;
    }

    printf("INFO: set vo format %d.\n", voFormat);
    u32CamFormat = strtol(argv[1], NULL, 0);

    if ((0 != u32CamFormat) && (1 != u32CamFormat))
    {
        printf("ERR: wrong camera format.\n");
        return HI_FAILURE;
    }

    u32af_inet = strtol(argv[2], NULL, 0);

    if ((0 != u32af_inet) && (1 != u32af_inet))
    {
        printf("ERR: wrong af inet.\n");
        return HI_FAILURE;
    }

    localIpAddr  = argv[3];
    remoteIpAddr = argv[4];

    if ((1 != Checkipaddr(u32af_inet, localIpAddr))
        || (1 != Checkipaddr(u32af_inet, remoteIpAddr))
       )

    {
        printf("ERR: wrong ip format.\n");
        return HI_FAILURE;
    }

    if (0 == memcmp(localIpAddr, remoteIpAddr, strlen(localIpAddr)))
    {
        system("ifconfig lo up");
    }

    if (argc >= 7)
    {
        if (!strcasecmp("h264", argv[6]))
        {
            vdecType = HI_UNF_VCODEC_TYPE_H264;
        }
        else if (!strcasecmp("h265", argv[6]))
        {
            vdecType = HI_UNF_VCODEC_TYPE_HEVC;
        }

#if    defined(CHIP_TYPE_hi3716mv410)   \
    || defined(CHIP_TYPE_hi3716mv420)   \
    || defined(CHIP_TYPE_hi3798cv200)   \
    || defined(CHIP_TYPE_hi3798mv100)   \
    || defined(CHIP_TYPE_hi3796mv100)

        if (vdecType == HI_UNF_VCODEC_TYPE_HEVC)
        {
            printf("WARN: This chipset not support H265 venc.\n");
            return 0;
        }

#endif
    }
    else if (argc == 6)
    {
        vdecType = HI_UNF_VCODEC_TYPE_H264;
    }

    printf("INFO: set vdec type %s \n", vdecType == HI_UNF_VCODEC_TYPE_HEVC ? "h.265" : "h.264");

    if (argc >= 8)
    {
        u32CamResolution = strtol(argv[7], NULL, 0);

        if (u32CamResolution > 5)
        {
            printf("ERR: wrong camera resolution.\n");
            return HI_FAILURE;
        }
        else if (u32CamResolution == 0)
        {
            g_u32CamWidth = 1920;
            g_u32CamHeight = 1080;
        }
        else if (u32CamResolution == 1)
        {
            g_u32CamWidth = 1280;
            g_u32CamHeight = 720;
        }
        else if (u32CamResolution == 2)
        {
            g_u32CamWidth = 720;
            g_u32CamHeight = 576;
        }
        else if (u32CamResolution == 3)
        {
            g_u32CamWidth = 640;
            g_u32CamHeight = 480;
        }
        else if (u32CamResolution == 4)
        {
            g_u32CamWidth = 352;
            g_u32CamHeight = 288;
        }
        else if (u32CamResolution == 5)
        {
            g_u32CamWidth = 176;
            g_u32CamHeight = 144;
        }
    }
    else if (argc == 7)
    {
        g_u32CamWidth = 1920;
        g_u32CamHeight = 1080;
    }

    printf("INFO: set camera resolution %d * %d.\n", g_u32CamWidth, g_u32CamHeight);

    if (argc >= 9)
    {
        u32vencResolution = strtol(argv[8], NULL, 0);

        if (u32vencResolution > 5)
        {
            printf("ERR: wrong venc resolution.\n");
            return HI_FAILURE;
        }
        else if (u32vencResolution == 0)
        {
            g_u32VencWidth = 1920;
            g_u32VencHeight = 1080;
        }
        else if (u32vencResolution == 1)
        {
            g_u32VencWidth = 1280;
            g_u32VencHeight = 720;
        }
        else if (u32vencResolution == 2)
        {
            g_u32VencWidth = 720;
            g_u32VencHeight = 576;
        }
        else if (u32vencResolution == 3)
        {
            g_u32VencWidth = 640;
            g_u32VencHeight = 480;
        }
        else if (u32vencResolution == 4)
        {
            g_u32VencWidth = 352;
            g_u32VencHeight = 288;
        }
        else if (u32vencResolution == 5)
        {
            g_u32VencWidth = 176;
            g_u32VencHeight = 144;
        }

    }
    else if (argc == 8)
    {
        g_u32VencWidth = 1920;
        g_u32VencHeight = 1080;
    }

    printf("INFO: set venc resolution %d * %d. \n", g_u32VencWidth, g_u32VencHeight);

    u32bitRate = 0;

    if (argc >= 10)
    {
        if (strstr(argv[9], "M"))
        {
            sscanf(argv[9], "%f", &bitRate);
            u32bitRate = (HI_U32)(bitRate * 1024 * 1024);
            printf("INFO: set bit rate %dK.\n", u32bitRate / 1024);
        }
        else if (strstr(argv[9], "K"))
        {
            sscanf(argv[9], "%f", &bitRate);
            u32bitRate = (HI_U32)(bitRate * 1024);
            printf("INFO: set bit rate %dK.\n", u32bitRate / 1024);
        }
        else
        {
            printf("ERR: wrong bit rate, set default value.\n");
        }
    }
    else
    {
        printf("INFO: set bit rate default value.\n");
    }

    u32frameRate = 30;

    if (argc >= 11)
    {
        u32frameRate = strtol(argv[10], NULL, 0);

        if (u32frameRate > 60)
        {
            printf("ERR: wrong frame rate.\n");
            return HI_FAILURE;
        }

        g_u32FrameRate = u32frameRate;
    }

    s32Ret = Global_Init(voFormat);

    if (HI_SUCCESS != s32Ret)
    {
        printf("ERR: call Global_Init failed.\n");
        goto Global_DEINIT;
    }

    stRect.s32X = 0;
    stRect.s32Y = 100;
    stRect.s32Width  = 640;
    stRect.s32Height = 480;
    s32Ret = HIADP_VO_CreatWin(&stRect, &hLocalWin);

    if (HI_SUCCESS != s32Ret)
    {
        printf("ERR: call HIADP_VO_CreatWin failed.\n");
        goto Global_DEINIT;
    }

    stRect.s32X = 640;
    stRect.s32Y = 100;
    stRect.s32Width  = 640;
    stRect.s32Height = 480;
    s32Ret |= HIADP_VO_CreatWin(&stRect, &hRemoteWin);

    if (HI_SUCCESS != s32Ret)
    {
        printf("ERR: call HIADP_VO_Init failed.\n");
        goto VO_DestroyWin;
    }

    if (1 == u32CamFormat)
    {
        g_stUSBCamArgs.u32USBCamFmt = V4L2_PIX_FMT_YUYV;
    }
    else if (0 == u32CamFormat)
    {
        g_stUSBCamArgs.u32USBCamFmt = V4L2_PIX_FMT_MJPEG;
    }

    s32Ret = SampleUsbCamInit(&g_stUSBCamArgs);

    if (HI_SUCCESS != s32Ret)
    {
        printf("ERR: call SampleUsbCamInit failed.\n");
        goto VO_DestroyWin;
    }

    memset(&stDefAttr, 0, sizeof(HI_UNF_VP_ATTR_S));
    s32Ret = HI_UNF_VP_GetDefaultAttr(&stDefAttr);

    if (HI_SUCCESS != s32Ret)
    {
        printf("ERR: call HI_UNF_VP_GetDefaultAttr failed.\n");
        goto UsbCam_DeInit;
    }

    if (vdecType == HI_UNF_VCODEC_TYPE_H264)
    {
        stDefAttr.stRtpAttr.u32PayLoadType = RTP_PT_H264;
    }
    else if (vdecType == HI_UNF_VCODEC_TYPE_HEVC)
    {
        stDefAttr.stRtpAttr.u32PayLoadType = RTP_PT_H265;
    }

    u32Width = g_u32VencWidth;
    u32Height = g_u32VencHeight;
    stDefAttr.stVencAttr.enVencType = vdecType;
    stDefAttr.stVencAttr.u32Width  = u32Width / 4 * 4;
    stDefAttr.stVencAttr.u32Height = u32Height / 4 * 4;
    stDefAttr.stVencAttr.u32InputFrmRate  = g_u32FrameRate;
    stDefAttr.stVencAttr.u32TargetFrmRate = g_u32FrameRate;
    stDefAttr.stVencAttr.u32Gop = 300;

    if (vdecType == HI_UNF_VCODEC_TYPE_H264)
    {
        if (stDefAttr.stVencAttr.u32Width > 1280)
        {
            stDefAttr.stVencAttr.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_FULLHD;
            stDefAttr.stVencAttr.u32StrmBufSize   = 1920 * 1080 * 2;
            stDefAttr.stVencAttr.u32TargetBitRate = 5 * 1024 * 1024;
        }
        else if (stDefAttr.stVencAttr.u32Width > 720)
        {
            stDefAttr.stVencAttr.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_720P;
            stDefAttr.stVencAttr.u32StrmBufSize   = 1280 * 720 * 2;
            stDefAttr.stVencAttr.u32TargetBitRate = 3 * 1024 * 1024;
        }
        else if (stDefAttr.stVencAttr.u32Width > 352)
        {
            stDefAttr.stVencAttr.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_D1;
            stDefAttr.stVencAttr.u32StrmBufSize   = 720 * 576 * 2;
            stDefAttr.stVencAttr.u32TargetBitRate = 3 * 1024 * 1024 / 2;
        }
        else
        {
            stDefAttr.stVencAttr.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_CIF;
            stDefAttr.stVencAttr.u32StrmBufSize   = 352 * 288 * 2;
            stDefAttr.stVencAttr.u32TargetBitRate = 800 * 1024;
        }
    }
    else if (vdecType == HI_UNF_VCODEC_TYPE_HEVC)
    {
        if (stDefAttr.stVencAttr.u32Width > 1280)
        {
            stDefAttr.stVencAttr.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_FULLHD;
            stDefAttr.stVencAttr.u32StrmBufSize   = 1920 * 1080 * 2;
            stDefAttr.stVencAttr.u32TargetBitRate = 2 * 1024 * 1024 ;
        }
        else if (stDefAttr.stVencAttr.u32Width > 720)
        {
            stDefAttr.stVencAttr.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_720P;
            stDefAttr.stVencAttr.u32StrmBufSize   = 1280 * 720 * 2;
            stDefAttr.stVencAttr.u32TargetBitRate = 768 * 1024 ;
        }
        else if (stDefAttr.stVencAttr.u32Width > 352)
        {
            stDefAttr.stVencAttr.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_D1;
            stDefAttr.stVencAttr.u32StrmBufSize   = 720 * 576 * 2;
            stDefAttr.stVencAttr.u32TargetBitRate = 1 * 1024 * 1024 / 2;
        }
        else
        {
            stDefAttr.stVencAttr.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_CIF;
            stDefAttr.stVencAttr.u32StrmBufSize   = 352 * 288 * 2;
            stDefAttr.stVencAttr.u32TargetBitRate = 400 * 1024;
        }

    }

    if (u32bitRate != 0)
    {
        stDefAttr.stVencAttr.u32TargetBitRate = u32bitRate;
    }

    printf("INFO: set venc target bit rate %dK.\n", stDefAttr.stVencAttr.u32TargetBitRate / 1024);

    stDefAttr.enDecType = vdecType;
    stDefAttr.bIsIpv4 = u32af_inet;

    if (stDefAttr.bIsIpv4)
    {
        if (0 == memcmp(localIpAddr, remoteIpAddr, strlen(localIpAddr)))
        {
            localIpAddr = "127.0.0.1";
            remoteIpAddr = "127.0.0.1";
        }

        stDefAttr.stLocalNetAttr.stIpv4Attr.sin_family = AF_INET;
        inet_pton(AF_INET, localIpAddr, (void*)&stDefAttr.stLocalNetAttr.stIpv4Attr.sin_addr);
        stDefAttr.stLocalNetAttr.stIpv4Attr.sin_port = htons(DFLT_RTP_PORT);
        stDefAttr.stRemoteNetAttr.stIpv4Attr.sin_family = AF_INET;
        inet_pton(AF_INET, remoteIpAddr, (void*)&stDefAttr.stRemoteNetAttr.stIpv4Attr.sin_addr);
        stDefAttr.stRemoteNetAttr.stIpv4Attr.sin_port = htons(DFLT_RTP_PORT);
    }
    else
    {
        if (0 == memcmp(localIpAddr, remoteIpAddr, strlen(localIpAddr)))
        {
            localIpAddr = "::1";
            remoteIpAddr = "::1";
        }
        else
        {
            stDefAttr.stLocalNetAttr.stIpv6Attr.sin6_scope_id = if_nametoindex(DFLT_SCOPE_ID);
        }

        stDefAttr.stLocalNetAttr.stIpv6Attr.sin6_family = AF_INET6;
        inet_pton(AF_INET6, localIpAddr, (void*)&stDefAttr.stLocalNetAttr.stIpv6Attr.sin6_addr);
        stDefAttr.stLocalNetAttr.stIpv6Attr.sin6_port = htons(DFLT_RTP_PORT);
        stDefAttr.stRemoteNetAttr.stIpv6Attr.sin6_family = AF_INET6;
        inet_pton(AF_INET6, remoteIpAddr, (void*)&stDefAttr.stRemoteNetAttr.stIpv6Attr.sin6_addr);
        stDefAttr.stRemoteNetAttr.stIpv6Attr.sin6_port = htons(DFLT_RTP_PORT);
    }

    s32Ret = HI_UNF_VP_Create(&stDefAttr, &hVP);

    if (HI_SUCCESS != s32Ret)
    {
        printf("ERR: call HI_UNF_VP_Create failed.\n");
        goto UsbCam_DeInit;
    }

    stSrcAttr.enSrcMode = HI_UNF_VP_SRC_MODE_USBCAM;
    stSrcAttr.hSrc = g_stUSBCamArgs.UsbCamFd;
    stSrcAttr.u32VIBufNum = 4;
    s32Ret = HI_UNF_VP_AttachSource(hVP, &stSrcAttr);

    if (HI_SUCCESS != s32Ret)
    {
        printf("ERR: call HI_UNF_VP_AttachSource failed.\n");
        goto VP_Destroy;
    }

    g_UsbPlugFlag = HI_TRUE;

    s32Ret = HI_UNF_VP_AttachLocalWin(hVP, hLocalWin);

    if (HI_SUCCESS != s32Ret)
    {
        printf("ERR: call HI_UNF_VP_AttachLocalWin failed.\n");
        goto VP_DetachSource;
    }

    s32Ret = HI_UNF_VP_AttachRemoteWin(hVP, hRemoteWin);

    if (HI_SUCCESS != s32Ret)
    {
        printf("ERR: call HI_UNF_VP_AttachRemoteWin failed.\n");
        goto VP_DetachLocalWin;
    }

    s32Ret = HI_UNF_VP_Start(hVP);

    if (HI_SUCCESS != s32Ret)
    {
        printf("ERR: call HI_UNF_VP_Start failed.\n");
        HI_UNF_VP_Stop(hVP);
        goto VP_DetachRemoteWin;
    }

    g_stUSBCamArgs.hVP = hVP;
    g_bUSBCamStop = HI_FALSE;
    pthread_create(&g_threadUSBCam, HI_NULL, USB_ScheduleCheckPlug, (void*)(&g_stUSBCamArgs));

    g_stopGet = 0;
    pthread_create(&g_threadSampleStatics, HI_NULL, Vp_ScheduleNetStatics, (void*)(&hVP));


    HI_UNF_VO_GetWindowAttr(hLocalWin, &stLocalWinAttr);
    HI_UNF_VO_GetWindowAttr(hRemoteWin, &stRemoteWinAttr);

    help();

    while (HI_FALSE == g_VpStop)
    {
        SAMPLE_GET_INPUTCMD(InputCmd);

        if ('q' == InputCmd[0])
        {
            printf("INFO: prepare to exit!\n");
            memset(InputCmd, 0, 32);
            g_VpStop = HI_TRUE;
        }

        if ('l' == InputCmd[0] && 'f' == InputCmd[1])
        {
            s32Ret = HI_UNF_VO_SetWindowZorder(hLocalWin, HI_LAYER_ZORDER_MOVEBOTTOM);
            s32Ret |= HI_UNF_VO_SetWindowZorder(hRemoteWin, HI_LAYER_ZORDER_MOVETOP);

            if (HI_SUCCESS != s32Ret)
            {
                printf("ERR: call HI_UNF_VO_SetWindowZorder failed.\n");
            }

            memset(&stLocalWinAttr.stOutputRect, 0, sizeof(HI_RECT_S));
            s32Ret |= HI_UNF_VO_SetWindowAttr(hLocalWin, &stLocalWinAttr);

            if (HI_SUCCESS != s32Ret)
            {
                printf("ERR: call HI_UNF_VO_SetWindowAttr failed.\n");
            }

            memset(&stRemoteWinAttr.stOutputRect, 0, sizeof(HI_RECT_S));
            stRemoteWinAttr.stOutputRect.s32X = 100;
            stRemoteWinAttr.stOutputRect.s32Y = 400;
            stRemoteWinAttr.stOutputRect.s32Width  = 320;
            stRemoteWinAttr.stOutputRect.s32Height = 240;
            s32Ret |= HI_UNF_VO_SetWindowAttr(hRemoteWin, &stRemoteWinAttr);

            if (HI_SUCCESS != s32Ret)
            {
                printf("ERR: call HI_UNF_VO_SetWindowAttr failed.\n");
            }

            memset(InputCmd, 0, 32);
            continue;
        }

        if ('l' == InputCmd[0])
        {
            s32Ret = HI_UNF_VO_SetWindowZorder(hLocalWin, HI_LAYER_ZORDER_MOVETOP);
            s32Ret |= HI_UNF_VO_SetWindowZorder(hRemoteWin, HI_LAYER_ZORDER_MOVEBOTTOM);

            if (HI_SUCCESS != s32Ret)
            {
                printf("ERR: call HI_UNF_VO_SetWindowZorder failed.\n");
            }

            memset(&stLocalWinAttr.stOutputRect, 0, sizeof(HI_RECT_S));
            s32Ret |= HI_UNF_VO_SetWindowAttr(hLocalWin, &stLocalWinAttr);

            if (HI_SUCCESS != s32Ret)
            {
                printf("ERR: call HI_UNF_VO_SetWindowAttr failed.\n");
            }

            memset(InputCmd, 0, 32);
            continue;
        }

        if ('r' == InputCmd[0] && 'f' == InputCmd[1])
        {
            s32Ret = HI_UNF_VO_SetWindowZorder(hLocalWin, HI_LAYER_ZORDER_MOVETOP);
            s32Ret |= HI_UNF_VO_SetWindowZorder(hRemoteWin, HI_LAYER_ZORDER_MOVEBOTTOM);

            if (HI_SUCCESS != s32Ret)
            {
                printf("ERR: call HI_UNF_VO_SetWindowZorder failed.\n");
            }

            memset(&stRemoteWinAttr.stOutputRect, 0, sizeof(HI_RECT_S));
            s32Ret |= HI_UNF_VO_SetWindowAttr(hRemoteWin, &stRemoteWinAttr);

            if (HI_SUCCESS != s32Ret)
            {
                printf("ERR: call HI_UNF_VO_SetWindowAttr failed.\n");
            }

            memset(&stLocalWinAttr.stOutputRect, 0, sizeof(HI_RECT_S));
            stLocalWinAttr.stOutputRect.s32X = 100;
            stLocalWinAttr.stOutputRect.s32Y = 400;
            stLocalWinAttr.stOutputRect.s32Width  = 320;
            stLocalWinAttr.stOutputRect.s32Height = 240;
            s32Ret |= HI_UNF_VO_SetWindowAttr(hLocalWin, &stLocalWinAttr);

            if (HI_SUCCESS != s32Ret)
            {
                printf("ERR: call HI_UNF_VO_SetWindowAttr failed.\n");
            }

            memset(InputCmd, 0, 32);
            continue;
        }

        if ('r' == InputCmd[0])
        {
            s32Ret = HI_UNF_VO_SetWindowZorder(hLocalWin, HI_LAYER_ZORDER_MOVEBOTTOM);
            s32Ret |= HI_UNF_VO_SetWindowZorder(hRemoteWin, HI_LAYER_ZORDER_MOVETOP);

            if (HI_SUCCESS != s32Ret)
            {
                printf("ERR: call HI_UNF_VO_SetWindowZorder failed.\n");
            }

            memset(&stRemoteWinAttr.stOutputRect, 0, sizeof(HI_RECT_S));
            s32Ret |= HI_UNF_VO_SetWindowAttr(hRemoteWin, &stRemoteWinAttr);

            if (HI_SUCCESS != s32Ret)
            {
                printf("ERR: call HI_UNF_VO_SetWindowAttr failed.\n");
            }

            memset(InputCmd, 0, 32);
            continue;
        }

        if ('b' == InputCmd[0])
        {
            s32Ret = HI_UNF_VO_SetWindowZorder(hRemoteWin, HI_LAYER_ZORDER_MOVETOP);
            s32Ret |= HI_UNF_VO_SetWindowZorder(hLocalWin, HI_LAYER_ZORDER_MOVETOP);

            if (HI_SUCCESS != s32Ret)
            {
                printf("ERR: call HI_UNF_VO_SetWindowZorder failed.\n");
            }

            memset(&stLocalWinAttr.stOutputRect, 0, sizeof(HI_RECT_S));
            stLocalWinAttr.stOutputRect.s32X = 0;
            stLocalWinAttr.stOutputRect.s32Y = 100;
            stLocalWinAttr.stOutputRect.s32Width  = 640;
            stLocalWinAttr.stOutputRect.s32Height = 480;
            s32Ret |= HI_UNF_VO_SetWindowAttr(hLocalWin, &stLocalWinAttr);

            if (HI_SUCCESS != s32Ret)
            {
                printf("ERR: call HI_UNF_VO_SetWindowAttr failed.\n");
            }

            memset(&stRemoteWinAttr.stOutputRect, 0, sizeof(HI_RECT_S));
            stRemoteWinAttr.stOutputRect.s32X = 640;
            stRemoteWinAttr.stOutputRect.s32Y = 100;
            stRemoteWinAttr.stOutputRect.s32Width  = 640;
            stRemoteWinAttr.stOutputRect.s32Height = 480;
            s32Ret |= HI_UNF_VO_SetWindowAttr(hRemoteWin, &stRemoteWinAttr);

            if (HI_SUCCESS != s32Ret)
            {
                printf("ERR: call HI_UNF_VO_SetWindowAttr failed.\n");
            }

            memset(InputCmd, 0, 32);
            continue;
        }
        if ('t' == InputCmd[0] && 's' == InputCmd[1] && '_' == InputCmd[2] && 'b' == InputCmd[3])
        {
            if(record_flag == HI_FALSE){
                time = vp_time();
                snprintf(record_file, 128, "./record_%08d.%05d.ts", time / 1000000, time % 1000000);
                s32Ret = HI_UNF_VP_StartRecord(hVP, HI_UNF_VP_RMT_MODE_SEND, HI_UNF_VP_RECORD_TS, record_file);
                if (HI_SUCCESS != s32Ret)
                {
                    printf("ERR: call HI_UNF_VP_StartRecord failed.\n");
                    help();
                }
                record_flag = HI_TRUE;
                printf("record file %s.\n", record_file);
            }else{
                printf("ERR: One record process is runing.\n");
                help();
            }
        }
        if ('t' == InputCmd[0] && 's' == InputCmd[1] && '_' == InputCmd[2] && 'e' == InputCmd[3])
        {
            if(record_flag == HI_TRUE){
                s32Ret = HI_UNF_VP_StopRecord(hVP);
                if (HI_SUCCESS != s32Ret)
                {
                    printf("ERR: call HI_UNF_VP_StopRecord failed.\n");
                    help();
                }
                printf("record file %s successfull.\n", record_file);
                record_flag = HI_FALSE;
            }else{
                printf("ERR: NO record process.\n");
                help();
            }
        }
        if ('h' == InputCmd[0])
        {
            help();
        }
    }

    g_stopGet = 1;
    pthread_join(g_threadSampleStatics, NULL);

    g_bUSBCamStop = HI_TRUE;
    pthread_join(g_threadUSBCam, NULL);

    HI_UNF_VP_Stop(hVP);


VP_DetachRemoteWin:
    HI_UNF_VP_DetachRemoteWin(hVP);

VP_DetachLocalWin:
    HI_UNF_VP_DetachLocalWin(hVP);

VP_DetachSource:

    if (g_UsbPlugFlag)
    {
        HI_UNF_VP_DetachSource(hVP);
        g_UsbPlugFlag = HI_FALSE;
    }

VP_Destroy:
    HI_UNF_VP_Destroy(hVP);

UsbCam_DeInit:

    SampleUsbCamDeinit(&g_stUSBCamArgs);

VO_DestroyWin:

    HI_UNF_VO_DestroyWindow(hLocalWin);
    HI_UNF_VO_DestroyWindow(hRemoteWin);

Global_DEINIT:
    Global_DeInit();

    return s32Ret;
}
