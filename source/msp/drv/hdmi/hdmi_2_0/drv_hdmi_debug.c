/******************************************************************************

  Copyright (C), 2014-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_hdmi_debug.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2015/06/24
  Description   :
  History       :
  Date          : 2015/06/24
  Author        : sdk
  Modification  :
*******************************************************************************/

#include "drv_hdmi_debug.h"
#include "drv_hdmi_common.h"
#include "drv_hdmi_intf.h"
#include "drv_hdmi_event.h"
#include "drv_hdmi_edid.h"
#include "drv_hdmi_common.h"
#include "hdmi_hal.h"
#include "hdmi_platform.h"
#include "hdmi_osal.h"
#include "hi_drv_hdmi.h"
#include "drv_hdmi_srm.h"

#ifdef HDMI_TEE_SUPPORT
#include "teek_client_api.h"    // tee
#include "drv_hdmi_tee.h"
#endif

#if defined (HDMI_SUPPORT_LOGIC_HISIV100)
#include "hdmi_hal_hdcp14.h"
#include "hdmi_hal_ctrl.h"
#include "hdmi_hal_phy.h"
#endif
#define HDMI_DBG_PRINT              HI_DRV_PROC_EchoHelper
#define HDMI_DBG_ERR                HDMI_DBG_PRINT("[HDMI DBG ERROR]: %s [%d],",__func__,__LINE__);HDMI_DBG_PRINT

#define DEBUG_MAX_CMD_CHAR_NUM      2048
#define DEBUG_MAX_ARGV_NUM          10

#define DEBUG_MAX_DELAY_MS          100000

#define DEBUG_CHAR_SPACE            0x20
#define DEBUG_CHAR_TAB              0x09
#define DEBUG_CHAR_END              0x0a

#define DEBUG_MAX_INFOFRAME_SIZE    31
#define DEBUG_MAX_CEC_SIZE          19
#define DEBUG_MAX_HDCPKEY_SIZE      2048
#define DEBUG_MAX_SRM_G1_SIZE       5120
#define DEBUG_MAX_EDIDBUF_SIZE      2048
#define DEBUG_DUMP_DEFAULT_LEN      16

#define STR_SUCC                    "success"
#define STR_FAIL                    "fail"

#ifndef TOLOWER
#define TOLOWER(x)                  ((x) | 0x20)
#endif


#define DEBUG_NULL_CHK(p) do{\
    if(HI_NULL == p)\
    {HDMI_WARN("%s null pointer!\n",#p);\
    HDMI_DBG_ERR("%s null pointer!\n",#p);\
    return HI_FAILURE;}\
}while(0)

#define DEBUG_NULL_CHK_NO_RET(p) do{\
    if(HI_NULL == p)\
    {HDMI_WARN("%s is null pointer!return fail.\n",#p);\
    return ;}\
}while(0)


#define DEBUG_FAILURE_RET_CHK(s32Ret) do{\
    if(HI_SUCCESS != s32Ret)\
    {HDMI_WARN("return failure!\n");\
    HDMI_DBG_ERR("return failure!\n");\
    return HI_FAILURE;}\
}while(0)


typedef struct file *PFILE;

typedef enum
{
    HDMI_DEBUG_BASE_OSD = 8 ,
    HDMI_DEBUG_BASE_DEC = 10,
    HDMI_DEBUG_BASE_HEX = 16,

}HDMI_DEBUG_BASE_E;


typedef struct{

    HDMI_DEVICE_ID_E    enHdmiId;
    HI_CHAR             *pcArgv[DEBUG_MAX_ARGV_NUM];
    HI_U32              u32Argc;
    HI_U32              u32RemainLen;

}HDMI_DEBUG_CMD_ARG_S;

typedef HI_S32 (*PFN_CMD_FUNC)(HDMI_DEBUG_CMD_ARG_S *pstCmdArg);

typedef struct{
    HI_CHAR         *pcName;
    HI_CHAR         *pcShortName;
    PFN_CMD_FUNC    pfnCmdFunc;
    HI_CHAR         *pCommentHelp;

}HDMI_DEBUG_CMD_INFO_S;

typedef struct {
    HI_BOOL bDataValid;
    HI_S32  s32Len;
    HI_U8   au8Data[HDMI_EDID_TOTAL_SIZE];
}HDMI_DEBUG_EDID_S;

static HDMI_DEBUG_EDID_S s_stDebugEdid = {0};

const static char *s_aEventStrTable[] = {
    "HPD",                      //HDMI_EVENT_HOTPLUG = 0x10,
    "HOTUNPLUG",                //HDMI_EVENT_HOTUNPLUG,
    "EDID_FAIL",                //HDMI_EVENT_EDID_FAIL,
    "HDCP_FAIL",                //HDMI_EVENT_HDCP_FAIL,
    "HDCP_SUCCESS",             //HDMI_EVENT_HDCP_SUCCESS,
    "RSEN_CONNECT",             //HDMI_EVENT_RSEN_CONNECT,
    "RSEN_DISCONNECT",          //HDMI_EVENT_RSEN_DISCONNECT,
    "HDCP_USERSETTING",         //HDMI_EVENT_HDCP_USERSETTING,
    "SCRAMBLE_FAIL",            //HDMI_EVENT_SCRAMBLE_FAIL,
    "SCRAMBLE_SUCCESS",         //HDMI_EVENT_SCRAMBLE_SUCCESS,
                                //HDMI_EVENT_BUTT
};

typedef struct
{
    HI_U32          u32DdcRegCfg;
    HI_U32          u32ApproximateValue;
    HI_CHAR         *pstReadValue;
}HDMI_DDC_FREQ_S;

HDMI_DDC_FREQ_S s_astDdcFreq[] = {

    {0x45,   20,  " 19.89"},
    {0x29,   30,  " 29.97"},
    {0x21,   40,  " 40.06"},
    {0x1a,   50,  " 49.90"},
    {0x15,   60,  " 60.53"},
    {0x12,   70,  " 69.42"},
    {0x0f,   80,  " 81.38"},
    {0x0d,   90,  " 91.87"},
    {0x0c,   100, " 98.11"},
    {0x0a,   110, "113.78"},
    {0x07,   150, "149.85"},
    {0x04,   220, "219.43"}

};
#if defined (HDMI_SUPPORT_LOGIC_HISIV100)
const static HI_CHAR *s_au8StrPredefineTimming[] =
{
    "480p",             // 00
    "576p",             // 01
    "720p50",           // 02
    "720p60",           // 03
    "1080p50",          // 04
    "1080p60",          // 05
    "2160p24",          // 06
    "2160p25",          // 07
    "2160p30",          // 08
    "2160p24_smpte",    // 09
    "1366x768_60",      // 10
    "800x600",          // 11
    "1680x1050",        // 12
    "1920x1200",        // 13
    "1600x1200_60",     // 14
    "2160p50",          // 15
    "2160p60",          // 16
    "1280x16_50",       // 17
    "240x16_60",        // 18

};

#define STR_PRE_TIMMING(n) ({(n>=HDMI_ARRAY_SIZE(s_au8StrPredefineTimming)) ? "ERROR" : s_au8StrPredefineTimming[n];})
#endif

static struct file *Debugfopen(const char *filename, int flags, int mode)
{
    struct file *filp = HI_NULL;

    if (!filename)
    {
        return HI_NULL;
    }

    filp = filp_open(filename, flags, mode);
    return (IS_ERR(filp)) ? NULL : filp;

}

static void Debugfclose(struct file *filp)
{
    if (filp)
        filp_close(filp, NULL);
}

static int Debugfread(char *buf, unsigned int len, struct file *filp)
{
    int readlen;
    mm_segment_t oldfs;
    loff_t pos;

    if (filp == NULL)
            return -ENOENT;
    if (((filp->f_flags & O_ACCMODE) & (O_RDONLY | O_RDWR)) == 0)
            return -EACCES;
    DEBUG_NULL_CHK(buf);

    oldfs = get_fs();
    set_fs(KERNEL_DS);
    pos = 0;
    /* filp->op->fread fail in linux-4.4,so we use vfs_read(4.4 & 3.18 test ok). */
    readlen = vfs_read(filp, buf, len, &pos);
    set_fs(oldfs);

    return readlen;
}

#if defined (HDMI_SUPPORT_LOGIC_SILICON)

static int Debugfwrite(char *buf, unsigned int len, struct file *filp)
{
    int writelen;
    mm_segment_t oldfs;
    loff_t pos;

    if (filp == NULL)
            return -ENOENT;
    if (((filp->f_flags & O_ACCMODE) & (O_WRONLY | O_RDWR)) == 0)
            return -EACCES;
    DEBUG_NULL_CHK(buf);

    oldfs = get_fs();
    set_fs(KERNEL_DS);
    pos = 0;
    writelen = vfs_write(filp, buf, len, &pos);
    set_fs(oldfs);

    return writelen;
}

static HI_S32 DebugSnprintf(HI_CHAR *pszStr, HI_SIZE_T ulLen, const HI_CHAR *pszFormat, ...)
{
    HI_S32 s32Len;
    va_list stArgs = {0};

    DEBUG_NULL_CHK(pszStr);
    DEBUG_NULL_CHK(pszFormat);

    va_start(stArgs, pszFormat);
    s32Len = vsnprintf(pszStr, ulLen, pszFormat, stArgs);
    va_end(stArgs);

    return s32Len;
}
#endif

static HI_BOOL IS_HEX_SPACE(HI_CHAR a)
{
    HI_BOOL bIsSpace = HI_FALSE;

    bIsSpace = ( a== DEBUG_CHAR_SPACE || a==DEBUG_CHAR_TAB || a==',' || a==';' || a=='\0' || a=='\n' || a=='\r' );

    return bIsSpace;
}

static HI_BOOL IS_HEX_CHAR(HI_CHAR a)
{
    HI_BOOL bIsChar = HI_FALSE;

    bIsChar = ( (a>='0' && a<='9') || (a>='a' && a<='f') || (a>='A' && a<='F') );

    return bIsChar;
}

static HI_CHAR HEX_VALUE_GET(HI_CHAR a)
{
    if ((a>='0' && a<='9'))
    {
        return a - '0';
    }
    else if (a>='a' && a<='f')
    {
        return a - 'a' + 0xa;
    }
    else if(a>='A' && a<='F')
    {
        return a - 'A' + 0xa;
    }
    else
    {
        return 0xff;
    }
}

static HI_BOOL IS_HEX_START(HI_CHAR *p,HI_CHAR **pcEnd)
{
    DEBUG_NULL_CHK(p);

    if (*p=='0' && (p[1]=='x' || p[1]=='X') )
    {
        if (pcEnd)
        {
            *pcEnd = p+2;
        }

        return HI_TRUE;
    }
    else if ( IS_HEX_CHAR(p[0])
            &&( IS_HEX_SPACE(p[1]) || (IS_HEX_CHAR(p[1]) && IS_HEX_SPACE(p[2]))) )
    {
        if (pcEnd)
        {
            *pcEnd = p;
        }
        return HI_TRUE;
    }
    else
    {
        if (pcEnd)
        {
            *pcEnd = p;
        }
        return HI_FALSE;
    }
}


static HI_S32 DebugStr2Hex(HI_CHAR *pcDest,HI_S32 s32Dlen,HI_CHAR *pcSrc,HI_U32 u32Slen)
{
    HI_U8 u8Result = 0;
    HI_CHAR *p = pcSrc;
    HI_S32  s32OldLen = s32Dlen;

    DEBUG_NULL_CHK(pcSrc);
    DEBUG_NULL_CHK(pcDest);

    while(p < (pcSrc+u32Slen) && s32Dlen)
    {
        if (IS_HEX_START(p,&p))
        {
            if(IS_HEX_CHAR(p[0]))
            {
                u8Result = HEX_VALUE_GET(p[0]);
                p++;
                if (IS_HEX_CHAR(p[0]))
                {
                    u8Result <<= 4;
                    u8Result |= HEX_VALUE_GET(p[0]);
                    p++;
                }

                if (pcDest)
                {
                    *pcDest++ = u8Result;
                    s32Dlen--;
                }
            }
            else
            {
                return HI_FAILURE;
            }
        }
        else
        {
            p++;
        }

    }

    return s32OldLen - s32Dlen;
}


static HDMI_DEBUG_BASE_E DebugBaseGet(const HI_CHAR *pcStr)
{
    if (pcStr[0] == '0')
    {
        if (TOLOWER(pcStr[1]) == 'x' )
        {
            return HDMI_DEBUG_BASE_HEX;
        }
        else
        {
            return HDMI_DEBUG_BASE_OSD;
        }
    }
    else
    {
        return HDMI_DEBUG_BASE_DEC;
    }
}

static HI_U32 DebugStrToU32(const HI_CHAR *pcStr, HI_CHAR **ppcEnd, HDMI_DEBUG_BASE_E enBase)
{
    HI_U32 u32Result = 0;

    DEBUG_NULL_CHK(pcStr);

    if (   HDMI_DEBUG_BASE_OSD != enBase
        && HDMI_DEBUG_BASE_DEC != enBase
        && HDMI_DEBUG_BASE_HEX != enBase)
    {
        enBase = DebugBaseGet(pcStr);
    }

    if (enBase == HDMI_DEBUG_BASE_HEX && pcStr[0] == '0' && TOLOWER(pcStr[1]) == 'x')
    {
        pcStr += 2;
    }

    while (*pcStr)
    {
        HI_U32 u32Value;

        u32Value = ((*pcStr >= '0') && (*pcStr <= '9')) ? *pcStr - '0' : TOLOWER(*pcStr) - 'a' + 10;
        if (u32Value >= enBase)
        {
            break;
        }
        u32Result = u32Result * enBase + u32Value;
        pcStr++;
    }

    if (ppcEnd)
    {
        *ppcEnd = (HI_CHAR *)pcStr;
    }

    return u32Result;
}

/************************ HDMI DEBUG CMD HANDLE ********************************************/

static HI_S32 DebugPrintHelp(HDMI_DEBUG_CMD_ARG_S *pstCmdArg);

static HI_S32 DebugThread(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32          s32Ret = HI_FAILURE;
    HDMI_DEVICE_S   *pstHdmiDev = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL)
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
       s32Ret = DRV_HDMI_ThreadStateSet(pstHdmiDev,HDMI_THREAD_STATE_STOP);
       HDMI_DBG_PRINT("\n thread set OFF %s! \n\n",s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC );
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
       s32Ret = DRV_HDMI_ThreadStateSet(pstHdmiDev,HDMI_THREAD_STATE_RUN);
       HDMI_DBG_PRINT("\n thread set ON %s! \n\n",s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC );
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo thread argv1 > /proc/msp/hdmi0\n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--thread off.\n"
                   "           1\t--thread on.\n");
    HDMI_DBG_PRINT("[example]: echo thread 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}


static HI_S32 DebugAuthenticate(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HDMI_DEVICE_S   *pstHdmiDev = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
       pstHdmiDev->stAttr.stAppAttr.bAuthMode = false;
       HDMI_DBG_PRINT("\n aut disable %s! \n\n", STR_SUCC );
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
       pstHdmiDev->stAttr.stAppAttr.bAuthMode = true;
       HDMI_DBG_PRINT("\n aut enable %s! \n\n", STR_SUCC );
    }
    else
    {
        HDMI_DBG_PRINT("\n aut status %d! \n\n", pstHdmiDev->stAttr.stAppAttr.bAuthMode);
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo aut argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--aut off.\n"
                   "           1\t--aut on.\n"
                   "           2\t--aut status get.\n");
    HDMI_DBG_PRINT("[example]: echo aut 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;

}

#ifdef HDMI_SUPPORT_LOGIC_SILICON

static HI_S32 DebugEmi(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HI_S32              s32Ret = 0;
    HDMI_ATTR_S         stAttr;
    HDMI_EMI_CONFIG_S   stEmiConfig;
    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_AttrGet(pstHdmiDev, &stAttr);
    if (s32Ret!=HI_SUCCESS)
    {
        HDMI_DBG_ERR("get attr error!\n");
        return HI_FAILURE;
    }
    HDMI_MEMSET(&stEmiConfig, 0, sizeof(HDMI_EMI_CONFIG_S));

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
        DRV_HDMI_Stop(pstHdmiDev);
        pstHdmiDev->bEmiEnable = HI_FALSE;
        s32Ret = DRV_HDMI_AttrSet(pstHdmiDev, &stAttr);
        DRV_HDMI_Start(pstHdmiDev);
        HDMI_DBG_PRINT(">>>>> disable emi.\n");
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        DRV_HDMI_Stop(pstHdmiDev);
        pstHdmiDev->bEmiEnable = HI_TRUE;
        s32Ret = DRV_HDMI_AttrSet(pstHdmiDev, &stAttr);
        DRV_HDMI_Start(pstHdmiDev);
        HDMI_DBG_PRINT(">>>>> enable emi.\n");
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2"))
    {
        stEmiConfig.bDebugEnable = HI_TRUE;
        HDMI_HAL_CALL(HAL_HDMI_EmiSet, pstHdmiDev->pstHdmiHal, &stEmiConfig);

        HDMI_DBG_PRINT(">>>>> emi debug enable.\n");
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"3"))
    {
        stEmiConfig.bDebugEnable = HI_FALSE;
        HDMI_HAL_CALL(HAL_HDMI_EmiSet, pstHdmiDev->pstHdmiHal, &stEmiConfig);

        HDMI_DBG_PRINT(">>>>> emi debug disable.\n");
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo emi argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--emi off.\n"
                   "           1\t--emi on.\n"
                   "           2\t--emi debug enable, it will not config emi regs.\n"
                   "           3\t--emi debug disable.\n");
    HDMI_DBG_PRINT("[example]: echo emi 1 > /proc/msp/hdmi0 \n");
    return HI_FAILURE;
}

#else

static HI_S32 DebugEmi(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HDMI_PHY_SSC_CFG_S  stPhySsc = {0};
    HI_CHAR             *pcChar = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc > 4 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    HDMI_MEMSET(&stPhySsc, 0, sizeof(HDMI_PHY_SSC_CFG_S));
    stPhySsc.u32PixClk      = (pstHdmiDev->stAttr.stAppAttr.enOutColorSpace == HDMI_COLORSPACE_YCbCr420)  ?
                              (pstHdmiDev->stAttr.stVOAttr.u32ClkFs >> 1) : pstHdmiDev->stAttr.stVOAttr.u32ClkFs;
    stPhySsc.u32TmdsClk     = pstHdmiDev->stAttr.stVOAttr.u32HdmiAdaptPixClk;
    stPhySsc.enDeepColor    = pstHdmiDev->stAttr.stAppAttr.enDeepColorMode;

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
        pstHdmiDev->bEmiEnable = HI_FALSE;

        stPhySsc.stHDMIPhySsc.bSscEnable     = HI_FALSE;
        stPhySsc.stHDMIPhySsc.bSscDebugEn    = HI_FALSE;
        stPhySsc.stHDMIPhySsc.stPhySscCfg.u32SscAmptd = 0;
        stPhySsc.stHDMIPhySsc.stPhySscCfg.u32SscFreq  = 0;

        DRV_HDMI_Stop(pstHdmiDev);
        HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_SSC, &stPhySsc);
        DRV_HDMI_Start(pstHdmiDev);
        HDMI_DBG_PRINT(">>>>> disable emi.\n");
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        pstHdmiDev->bEmiEnable = HI_TRUE;

        stPhySsc.stHDMIPhySsc.bSscEnable     = HI_TRUE;
        stPhySsc.stHDMIPhySsc.bSscDebugEn    = HI_FALSE;
        stPhySsc.stHDMIPhySsc.stPhySscCfg.u32SscAmptd = 0;
        stPhySsc.stHDMIPhySsc.stPhySscCfg.u32SscFreq  = 0;

        DRV_HDMI_Stop(pstHdmiDev);
        HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_SSC, &stPhySsc);
        DRV_HDMI_Start(pstHdmiDev);
        HDMI_DBG_PRINT(">>>>> enable emi.\n");
    }

    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2"))
    {
        DEBUG_NULL_CHK(pstCmdArg->pcArgv[2]);
        DEBUG_NULL_CHK(pstCmdArg->pcArgv[3]);

        pstHdmiDev->bEmiEnable = HI_TRUE;

        stPhySsc.stHDMIPhySsc.bSscEnable     = HI_TRUE;
        stPhySsc.stHDMIPhySsc.bSscDebugEn    = HI_TRUE;
        pcChar = pstCmdArg->pcArgv[2];
        stPhySsc.stHDMIPhySsc.stPhySscCfg.u32SscAmptd = DebugStrToU32(pcChar,&pcChar,HDMI_DEBUG_BASE_DEC);
        pcChar = pstCmdArg->pcArgv[3];
        stPhySsc.stHDMIPhySsc.stPhySscCfg.u32SscFreq  = DebugStrToU32(pcChar,&pcChar,HDMI_DEBUG_BASE_DEC);

        DRV_HDMI_Stop(pstHdmiDev);
        HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_SSC, &stPhySsc);
        DRV_HDMI_Start(pstHdmiDev);

        HDMI_DBG_PRINT(">>>>> emi debug enable & config param.\n");
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo emi argv1[argv2 argv3] > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--emi off.\n"
                   "           1\t--emi on.\n"
                   "           2\t--emi on,param config to argv2 & argv3.\n");
    HDMI_DBG_PRINT("[argv2  ]: emi Ssc Amptd.optional,range [0,500], weight in 0.001%%\n");
    HDMI_DBG_PRINT("[argv3  ]: emi Ssc Freq.optional,default 45000,range [20000,50000]\n");
    HDMI_DBG_PRINT("[example]: echo emi 1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[example]: echo emi 2 250 45000 > /proc/msp/hdmi0 \n");
    return HI_FAILURE;
}

#endif

static HI_S32 DebugCmd(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HDMI_DEVICE_S           *pstHdmiDev = HI_NULL;
    HDMI_BLACK_FRAME_INFO_S stBlackInfo;
    HDMI_HPD_FILLTER_S      *pstHpd = HI_NULL;
    HI_U32                  u32Tmp = 0;
    HI_CHAR                 *pcStr = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    pstHpd = &pstHdmiDev->stHpdFillter;
    stBlackInfo.inBitDepth = pstHdmiDev->stAttr.stVOAttr.enInBitDepth;
    stBlackInfo.inColorSpace = pstHdmiDev->stAttr.stVOAttr.enInColorSpace;
    stBlackInfo.inQuantization = (stBlackInfo.inColorSpace == HDMI_COLORSPACE_RGB) ? \
    pstHdmiDev->stAttr.stVOAttr.enRGBQuantization : pstHdmiDev->stAttr.stVOAttr.enYCCQuantization;

    if (pstCmdArg->u32Argc < 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argc!\n");
        goto usage_error;
    }
    else if ( (pstCmdArg->u32Argc == 3) && (pstCmdArg->pcArgv[2]) )
    {
        pcStr = pstCmdArg->pcArgv[2];
        DEBUG_NULL_CHK(pcStr);
        u32Tmp = DebugStrToU32(pcStr, &pcStr, HDMI_DEBUG_BASE_DEC);
    }
    else
    {
        //nothing.
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "0"))
    {
        DRV_HDMI_Stop(pstHdmiDev);
        HDMI_DBG_PRINT(">>>>> hdmi stop.\n");
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "1"))
    {
        DRV_HDMI_Start(pstHdmiDev);
        HDMI_DBG_PRINT(">>>>> hdmi start.\n");
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "2"))
    {
        stBlackInfo.bBlacEnable = HI_TRUE;
        HDMI_HAL_CALL(HAL_HDMI_BlackDataSet, pstHdmiDev->pstHdmiHal, &stBlackInfo);
        HDMI_DBG_PRINT(">>>>> black frame enable.\n");
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "3"))
    {
        stBlackInfo.bBlacEnable = HI_FALSE;
        HDMI_HAL_CALL(HAL_HDMI_BlackDataSet, pstHdmiDev->pstHdmiHal, &stBlackInfo);
        HDMI_DBG_PRINT(">>>>> black frame disable.\n");
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "4"))
    {
        pstHpd->bFillterEnable = u32Tmp ? HI_TRUE : HI_FALSE;
        pstHpd->u32FillTerHigh = u32Tmp ? (u32Tmp-1) : 0;
        HDMI_HAL_CALL(HAL_HDMI_Debug , pstHdmiDev->pstHdmiHal, HDMI_DEBUG_CMD_HPD_FILLTER,pstHpd);
        HDMI_DBG_PRINT(" \t%s=%d\n \t%s=%d\n \t%s=%d\n \n",
                            "bFillterEnable",pstHpd->bFillterEnable,
                            "u32FillTerHigh",pstHpd->u32FillTerHigh,
                            "u32FillTerLow",pstHpd->u32FillTerLow);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "5"))
    {
        pstHpd->bFillterEnable = u32Tmp ? HI_TRUE : HI_FALSE;
        pstHpd->u32FillTerLow  = u32Tmp ? (u32Tmp-1) : 0;
        HDMI_HAL_CALL(HAL_HDMI_Debug , pstHdmiDev->pstHdmiHal, HDMI_DEBUG_CMD_HPD_FILLTER,pstHpd);
        HDMI_DBG_PRINT(" \t%s=%d\n \t%s=%d\n \t%s=%d\n \n",
                            "bFillterEnable",pstHpd->bFillterEnable,
                            "u32FillTerHigh",pstHpd->u32FillTerHigh,
                            "u32FillTerLow",pstHpd->u32FillTerLow);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "6"))
    {
        HDMI_HAL_CALL(HAL_HDMI_Debug , pstHdmiDev->pstHdmiHal, HDMI_DEBUG_CMD_HPD_SIMULATE,&u32Tmp);
        HDMI_DBG_PRINT("simulate HPD=%d success.\n",u32Tmp);

    }
    else
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo cmd argv1 [argv2] > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--hdmi stop.no argv2\n"
                   "           1\t--hdmi start.no argv2\n"
                   "           2\t--black frame enable.no argv2\n"
                   "           3\t--black frame disable.no argv2\n"
                   "           4\t--set hpd fillter's high reshold.need argv2: high reshold value,0--disable fillter,default 100,in ms.\n"
                   "           5\t--set hpd fillter's low reshold.need argv2: low reshold value,0--disable fillter,default 10,in ms.\n"
                   "           6\t--set hpd software simulate HPD event.need argv2: 0--UnHotPlug;1--HotPlug;other--disable\n");

    HDMI_DBG_PRINT("[example]: echo cmd 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}


static HI_S32 DebugOe(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HDMI_DEVICE_S   *pstHdmiDev = HI_NULL;
    HDMI_BLACK_FRAME_INFO_S stBlackInfo;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    stBlackInfo.inBitDepth = pstHdmiDev->stAttr.stVOAttr.enInBitDepth;
    stBlackInfo.inColorSpace = pstHdmiDev->stAttr.stVOAttr.enInColorSpace;
    stBlackInfo.inQuantization = (stBlackInfo.inColorSpace == HDMI_COLORSPACE_RGB) ? \
    pstHdmiDev->stAttr.stVOAttr.enRGBQuantization : pstHdmiDev->stAttr.stVOAttr.enYCCQuantization;

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
       HDMI_HAL_CALL(HAL_HDMI_PhyOutputEnableSet, pstHdmiDev->pstHdmiHal, HI_FALSE);
       HDMI_DBG_PRINT("\n oe set OFF %s! \n\n", STR_SUCC );
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        HDMI_HAL_CALL(HAL_HDMI_PhyOutputEnableSet, pstHdmiDev->pstHdmiHal, HI_TRUE);
        HDMI_DBG_PRINT("\n oe set ON %s! \n\n", STR_SUCC );
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2"))
    {
       DRV_HDMI_AudioEnable(pstHdmiDev, HDMI_AO_MODE_DRV_SELF , HI_FALSE);
       stBlackInfo.bBlacEnable = HI_TRUE;
       HDMI_HAL_CALL(HAL_HDMI_BlackDataSet, pstHdmiDev->pstHdmiHal, &stBlackInfo);
       DRV_HDMI_AVMuteSet(pstHdmiDev, HI_TRUE);
       msleep(200);
       HDMI_HAL_CALL(HAL_HDMI_PhyOutputEnableSet, pstHdmiDev->pstHdmiHal, HI_FALSE);
       HDMI_DBG_PRINT("\n oe set OFF %s! \n\n", STR_SUCC );
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"3"))
    {
       DRV_HDMI_AVMuteSet(pstHdmiDev,HI_FALSE);
       HDMI_HAL_CALL(HAL_HDMI_PhyOutputEnableSet, pstHdmiDev->pstHdmiHal, HI_TRUE);
       stBlackInfo.bBlacEnable = HI_FALSE;
       HDMI_HAL_CALL(HAL_HDMI_BlackDataSet, pstHdmiDev->pstHdmiHal, &stBlackInfo);
       DRV_HDMI_AudioEnable(pstHdmiDev, HDMI_AO_MODE_DRV_SELF ,HI_TRUE);
       HDMI_DBG_PRINT("\n oe set ON %s! \n\n", STR_SUCC );
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo oe argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--oe off.\n"
                   "           1\t--oe on.\n"
                   "           2\t--oe off with black frame.\n"
                   "           3\t--oe on with black frame.\n");
    HDMI_DBG_PRINT("[example]: echo oe 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugEvent(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32                  s32Ret = HI_FAILURE;
    HDMI_EVENT_E            enEvent = 0;
    HDMI_DEVICE_S           *pstHdmiDev = HI_NULL;
    HI_CHAR                 *pcStr = pstCmdArg->pcArgv[0];

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);
    DEBUG_NULL_CHK(pcStr);

    if (pstCmdArg->u32Argc != 2 )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    pcStr = pstCmdArg->pcArgv[1];
    DEBUG_NULL_CHK(pcStr);
    enEvent = (HDMI_EVENT_E)DebugStrToU32(pcStr, &pcStr, HDMI_DEBUG_BASE_DEC);

    if ( (enEvent >= HDMI_EVENT_HOTPLUG)
        && (enEvent < HDMI_EVENT_BUTT) )
    {
        s32Ret = DRV_HDMI_EventPoolWrite(pstCmdArg->enHdmiId, enEvent, HI_FALSE);
        if ((enEvent-HDMI_EVENT_HOTPLUG) < HDMI_ARRAY_SIZE(s_aEventStrTable))
        {
            HDMI_DBG_PRINT("hardware event %s simulate %s.\n",
                        s_aEventStrTable[enEvent-HDMI_EVENT_HOTPLUG],
                        s32Ret!=HI_SUCCESS ? STR_FAIL: STR_SUCC);
        }
    }
    else
    {
        goto usage_error;
    }

    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo event argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: event type(DECMICAL) as follow\n");
    for (enEvent = HDMI_EVENT_HOTPLUG;
        enEvent < HDMI_EVENT_BUTT && ((enEvent-HDMI_EVENT_HOTPLUG) < HDMI_ARRAY_SIZE(s_aEventStrTable));
        enEvent++)
    {
        HDMI_DBG_PRINT("%-10s %d\t-- (0x%02x)%s\n","",enEvent,enEvent,
                        s_aEventStrTable[enEvent-HDMI_EVENT_HOTPLUG]);
    }
    HDMI_DBG_PRINT("[example]: echo event 16 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugEdidFromFile(HDMI_DEVICE_S *pstHdmiDev, HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32               s32Ret = HI_FAILURE;
    PFILE                pFile = HI_NULL;
    HI_U8               *pu8Buf = HI_NULL;
    HDMI_DEBUG_EDID_S   *pstDbgEdid = &s_stDebugEdid;
    HI_S32              s32Len = 0;

    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstCmdArg);
    DEBUG_NULL_CHK(pstCmdArg->pcArgv[2]);

    pFile = Debugfopen(pstCmdArg->pcArgv[2], O_RDWR, 0);
    if (pFile == HI_NULL)
    {
        HDMI_DBG_ERR("open file %s fail!\n",pstCmdArg->pcArgv[2]);
        return HI_FAILURE;
    }

    pu8Buf = (HI_U8 *)HDMI_VMALLOC(DEBUG_MAX_EDIDBUF_SIZE);
    if (pu8Buf)
    {
        HDMI_MEMSET(pstDbgEdid, 0, sizeof(HDMI_DEBUG_EDID_S));

        s32Len = Debugfread(pu8Buf, DEBUG_MAX_EDIDBUF_SIZE, pFile);
        if (s32Len <= 0)
        {
            HDMI_DBG_PRINT("read file size = %d!\n", s32Len);
        }
        else
        {
            s32Len = DebugStr2Hex(pstDbgEdid->au8Data, HDMI_EDID_TOTAL_SIZE, pu8Buf, (HI_U32)s32Len);
            if (s32Len < 0)
            {
                HDMI_DBG_ERR("string convert to hex error!\n");
            }
            else
            {
                pstDbgEdid->bDataValid = HI_TRUE;
                pstDbgEdid->s32Len     += s32Len;
                s32Ret = DRV_HDMI_EdidUpdate(&pstHdmiDev->stEdidInfo, HDMI_EDID_UPDATE_DEBUG);
            }
        }
        HDMI_VFREE(pu8Buf);
    }
    else
    {
        HDMI_DBG_ERR("vmalloc error!\n");
    }
    Debugfclose(pFile);

    if (s32Len < 0)
    {
        HDMI_DBG_ERR("error hex raw data format!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 DebugEdidFromCmd(HDMI_DEVICE_S *pstHdmiDev, HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32               s32Ret = HI_FAILURE;
    HDMI_DEBUG_EDID_S   *pstDbgEdid = &s_stDebugEdid;

    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstCmdArg);
    DEBUG_NULL_CHK(pstCmdArg->pcArgv[2]);

    HDMI_DBG_ERR("pstDbgEdid->s32Len=%d !\n", pstDbgEdid->s32Len);
    s32Ret = DebugStr2Hex(pstDbgEdid->au8Data + pstDbgEdid->s32Len,
                            HDMI_EDID_TOTAL_SIZE-pstDbgEdid->s32Len,
                            pstCmdArg->pcArgv[2],
                            pstCmdArg->u32RemainLen);
    if (s32Ret < 0)
    {
        HDMI_DBG_ERR("error hex raw data format!\n");
        return HI_FAILURE;
    }
    else
    {
        pstDbgEdid->bDataValid = HI_FALSE;
        pstDbgEdid->s32Len     += s32Ret;
        HDMI_DBG_ERR("pstDbgEdid->s32Len=%d !\n", pstDbgEdid->s32Len);
    }

    return HI_SUCCESS;
}

static HI_S32 DebugEdid(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32              s32Ret = HI_FAILURE;
    HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HI_S32              i = 0;
    HI_U8               *pu8Buf = HI_NULL;
    HDMI_DEBUG_EDID_S   *pstDbgEdid = &s_stDebugEdid;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc < 2)
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    DEBUG_NULL_CHK(pstCmdArg->pcArgv[1]);

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"s")
        || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
        HDMI_MEMSET(pstDbgEdid,0,sizeof(HDMI_DEBUG_EDID_S));
        s32Ret = DRV_HDMI_EdidUpdate(&pstHdmiDev->stEdidInfo,HDMI_EDID_UPDATE_SINK);
        if (s32Ret != HI_SUCCESS)
        {
            HDMI_DBG_ERR("update edid from sink fail!Make sure cable connect!\n");
        }
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"l")
        || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        DEBUG_NULL_CHK(pstCmdArg->pcArgv[2]);
        s32Ret = DebugEdidFromCmd(pstHdmiDev, pstCmdArg);
        DEBUG_FAILURE_RET_CHK(s32Ret);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"e")
        || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2"))
    {
        DEBUG_NULL_CHK(pstCmdArg->pcArgv[2]);
        s32Ret = DebugEdidFromCmd(pstHdmiDev, pstCmdArg);
        DEBUG_FAILURE_RET_CHK(s32Ret);
        s32Ret = DRV_HDMI_EdidUpdate(&pstHdmiDev->stEdidInfo,HDMI_EDID_UPDATE_DEBUG);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"f")
        || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"3"))
    {
        DEBUG_NULL_CHK(pstCmdArg->pcArgv[2]);
        s32Ret = DebugEdidFromFile(pstHdmiDev, pstCmdArg);
        DEBUG_FAILURE_RET_CHK(s32Ret);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"4"))
    {
        s32Ret = DRV_HDMI_EdidUpdate(&pstHdmiDev->stEdidInfo, HDMI_EDID_UPDATE_SINK);
        DEBUG_FAILURE_RET_CHK(s32Ret);
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    HDMI_DBG_PRINT(" edid load %s! \n",s32Ret<0 ? STR_FAIL : STR_SUCC);
    HDMI_DBG_PRINT("[Edid Data]:");
    pu8Buf= (HI_U8 *)HDMI_VMALLOC(HDMI_EDID_TOTAL_SIZE);
    if (pu8Buf)
    {
        s32Ret = DRV_HDMI_EdidRawGet(&pstHdmiDev->stEdidInfo, pu8Buf, HDMI_EDID_TOTAL_SIZE);

        for (i = 0; (i < s32Ret) && (i < HDMI_EDID_TOTAL_SIZE); i++)
        {
            if (!(i%16)){HDMI_DBG_PRINT("\n");}
            HDMI_DBG_PRINT(" %02x",pu8Buf[i]);
        }

        HDMI_DBG_PRINT("\n\n");
        HDMI_VFREE(pu8Buf);
    }
    else
    {
        HDMI_DBG_ERR("vmalloc fail!\n");
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo edid argv1 [argv2] > /proc/msp/hdmi0\n");
    HDMI_DBG_PRINT("[argv1  ]: edid operation mode as below\n");
    HDMI_DBG_PRINT("%10s 0(s)\t--finish using debug edid and read from sink.\n","");
    HDMI_DBG_PRINT("%10s 1(l)\t--read debug edid from argv2(a hex-string-line).\n","");
    HDMI_DBG_PRINT("%10s 2(el)--read debug edid from argv2(a hex-string-line),then finish reading.\n","");
    HDMI_DBG_PRINT("%10s 3(f)\t--read debug edid from argv2(a hex-string-file-path).\n","");
    HDMI_DBG_PRINT("%10s 4\t--force to read edid from sink.no argv2\n","");
    HDMI_DBG_PRINT("[argv2  ]: hex-data string/filepath.You have to use at least 1 charater of 'SPACE|TAB|,|0x' between 2 hex-bytes.\n");
    HDMI_DBG_PRINT("[example]: echo edid s > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[example]: echo edid l 0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[example]: echo edid f /mnt/edid_skyworth_300m.txt > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugInfoframe(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32              s32Ret = HI_FAILURE;
    HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HI_U8               au8IfBuf[DEBUG_MAX_INFOFRAME_SIZE+1];
    HI_U32              i = 0,u32Sum = 0;
    HI_U8               u8ChkSum = 0;
    HDMI_INFOFRAME_ID_E enInfoFrameId;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc < 3)
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    DEBUG_NULL_CHK(pstCmdArg->pcArgv[2]);
    DEBUG_NULL_CHK(pstCmdArg->pcArgv[1]);
    HDMI_MEMSET(au8IfBuf,0,sizeof(au8IfBuf));

    s32Ret = DebugStr2Hex(au8IfBuf,DEBUG_MAX_INFOFRAME_SIZE,
                pstCmdArg->pcArgv[2],pstCmdArg->u32RemainLen);
    if (s32Ret < 0)
    {
        HDMI_DBG_ERR("error hex raw data format!\n");
        goto usage_error;
    }

    for (i=0,u32Sum=0;i <= DEBUG_MAX_INFOFRAME_SIZE; i++)
    {
        if(i != 3)
        {
            u32Sum += au8IfBuf[i];
        }
    }

    u8ChkSum = (HI_U8)((0x100 - (u32Sum % 0x100)) % 0x100);
    if (au8IfBuf[3] != u8ChkSum)
    {
        HDMI_DBG_PRINT("error checksum 0x%02x -> 0x%02x\n",au8IfBuf[3],u8ChkSum);
        au8IfBuf[3] = u8ChkSum;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0")
        || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"avi")
        || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"v"))
    {
        enInfoFrameId = HDMI_INFOFRAME_TYPE_AVI;
        HDMI_DBG_PRINT(" avi");
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1")
        || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"audio")
        || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"a"))
    {
        enInfoFrameId = HDMI_INFOFRAME_TYPE_AUDIO;
        HDMI_DBG_PRINT(" audio");
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2")
        || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"vs")
        || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"s"))
    {
        enInfoFrameId = HDMI_INFOFRAME_TYPE_VENDOR;
        HDMI_DBG_PRINT(" vs");
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"3")
        || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"gdb")
        || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"g"))
    {
        enInfoFrameId = HDMI_INFOFRAME_TYPE_GBD;
        HDMI_DBG_PRINT(" gdb");
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"4")
        || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"drm")
        || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"d"))
    {
        enInfoFrameId = HDMI_INFOFRAME_TYPE_DRM;
        HDMI_DBG_PRINT(" drm");
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    HDMI_HAL_CALL(HAL_HDMI_InfoframeEnableSet, pstHdmiDev->pstHdmiHal, enInfoFrameId, HI_FALSE);
    HDMI_HAL_CALL(HAL_HDMI_InfoframeSet, pstHdmiDev->pstHdmiHal, enInfoFrameId, au8IfBuf);
    HDMI_HAL_CALL(HAL_HDMI_InfoframeEnableSet, pstHdmiDev->pstHdmiHal, enInfoFrameId, HI_TRUE);

    HDMI_DBG_PRINT(" infoframe send %s! \n",STR_SUCC);
    HDMI_DBG_PRINT("[InfoFrame Data]:");
    for (i=0;i<sizeof(au8IfBuf);i++)
    {
        HDMI_DBG_PRINT(" %02x",au8IfBuf[i]);
    }
    HDMI_DBG_PRINT("\n\n");

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo infoframe argv1 argv2 > /proc/msp/hdmi0\n");
    HDMI_DBG_PRINT("[argv1  ]: infoframe type list as below\n");
    HDMI_DBG_PRINT("%10s 0(v/avi)\t\t--avi .\n","");
    HDMI_DBG_PRINT("%10s 1(a/audio)\t\t--audio .\n","");
    HDMI_DBG_PRINT("%10s 2(s/vs)\t\t--vendor specif .\n","");
    HDMI_DBG_PRINT("%10s 3(g/gdb)\t\t--gdb packet.\n","");
    HDMI_DBG_PRINT("%10s 4(d/drm)\t\t--drm .\n","");
    HDMI_DBG_PRINT("[argv2  ]: infoframe hex-byte string.You have to use at least 1 charater of 'SPACE|TAB|,|0x' between 2 hex-bytes.\n");
    HDMI_DBG_PRINT("[example]: echo infoframe 0 82 02 0d 78 50 a8 00 13 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[example]: echo infoframe avi 0x82,0x2,0xd,0x78,0x50,0xa8,0x00,0x13 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}


static HI_S32 DebugAvmute(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HDMI_DEVICE_S   *pstHdmiDev = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
       DRV_HDMI_AVMuteSet(pstHdmiDev, HI_FALSE);
       HDMI_DBG_PRINT("\n avmute set OFF %s! \n\n", STR_SUCC );
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
       DRV_HDMI_AVMuteSet(pstHdmiDev, HI_TRUE);
       HDMI_DBG_PRINT("\n avmute set ON %s! \n\n", STR_SUCC );
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo avmute argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--avmute off.\n"
                   "           1\t--avmute on.\n");
    HDMI_DBG_PRINT("[example]: echo avmute 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}


static HI_S32 DebugAmute(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32                  s32Ret = HI_FAILURE;
    HDMI_DEVICE_S           *pstHdmiDev = HI_NULL;
    HI_CHAR                 *pcStr = HI_NULL;
    HI_U32                  u32Tmp = 0;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc < 2 )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }
    else if(pstCmdArg->u32Argc == 3 )
    {
        pcStr = pstCmdArg->pcArgv[2];
        DEBUG_NULL_CHK(pcStr);
        u32Tmp = DebugStrToU32(pcStr, &pcStr, HDMI_DEBUG_BASE_DEC);
    }

    if(IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
        s32Ret = HDMI_HAL_CALL_RET(HAL_HDMI_AudioMute, pstHdmiDev->pstHdmiHal,HI_FALSE);
        HDMI_DBG_PRINT("\n audio mute set OFF %s! \n\n",s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC);
    }
    else if(IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        s32Ret = HDMI_HAL_CALL_RET(HAL_HDMI_AudioMute, pstHdmiDev->pstHdmiHal,HI_TRUE);
        HDMI_DBG_PRINT("\n audio mute set ON %s! \n\n",s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC);
    }
    else if(IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2"))
    {
        s32Ret = HDMI_HAL_CALL_RET(HAL_HDMI_AudioEnable, pstHdmiDev->pstHdmiHal,HI_TRUE);
        HDMI_DBG_PRINT("\n audio enable set ON %s! \n\n",s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC);
    }
    else if(IS_STR_EQUAL(pstCmdArg->pcArgv[1],"3"))
    {
        s32Ret = HDMI_HAL_CALL_RET(HAL_HDMI_AudioEnable, pstHdmiDev->pstHdmiHal,HI_FALSE);
        HDMI_DBG_PRINT("\n audio enable set OFF %s! \n\n",s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC);
    }
    else if(IS_STR_EQUAL(pstCmdArg->pcArgv[1],"4"))
    {
        HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_SW_MODE,&u32Tmp);
        HDMI_DBG_PRINT("\n audio set sw mode %u! \n\n",u32Tmp);
    }
    else if(IS_STR_EQUAL(pstCmdArg->pcArgv[1],"5"))
    {
        HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_SWCTS,&u32Tmp);
        HDMI_DBG_PRINT("\n audio set Sw CTS %u(0x%x)! \n\n",u32Tmp,u32Tmp);
    }
    else if(IS_STR_EQUAL(pstCmdArg->pcArgv[1],"6"))
    {
        HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_N,&u32Tmp);
        HDMI_DBG_PRINT("\n audio set N %u(0x%x)! \n\n",u32Tmp,u32Tmp);
    }
    else if(IS_STR_EQUAL(pstCmdArg->pcArgv[1],"7"))
    {
        if (u32Tmp > DEBUG_MAX_DELAY_MS)
        {
            HDMI_DBG_ERR("error delay time!\n");
            goto usage_error;
        }

        HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_AUDIO_DELAY,&u32Tmp);
        HDMI_DBG_PRINT("\n audio set delay %u(0x%x)! \n\n",u32Tmp,u32Tmp);
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo amute argv1 [argv2] > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--audio mute OFF.\n"
                   "           1\t--audio mute ON.\n"
                   "           2\t--audio enable.\n"
                   "           3\t--audio disable.\n"
                   "           4\t--audio select sw CTS.[argv] is needed, 1--sw,0--hw\n"
                   "           5\t--audio SW CTS.[argv2] is needed as the setting value,in decimal system\n"
                   "           6\t--audio N .[argv2] is needed as the setting value,in decimal system\n"
                   "           7\t--audio delay .[argv2] a delay time value in range [0 , %u] ms,default 5ms.\n",DEBUG_MAX_DELAY_MS);
    HDMI_DBG_PRINT("[example]: echo amute 1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[example]: echo amute 6 6144 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugVmute(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32                  s32Ret = HI_FAILURE;
    HDMI_DEVICE_S           *pstHdmiDev = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    if(IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
        s32Ret = DRV_HDMI_VideoOutputEnableSet(pstHdmiDev,HI_TRUE);
        HDMI_DBG_PRINT("\n Video mute set OFF %s! \n\n",s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC);
    }
    else if(IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        s32Ret = DRV_HDMI_VideoOutputEnableSet(pstHdmiDev,HI_FALSE);
        HDMI_DBG_PRINT("\n Video mute set ON %s! \n\n",s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC);
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo vmute argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--OFF.\n"
                   "           1\t--ON.\n");
    HDMI_DBG_PRINT("[example]: echo vmute 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugDelay(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HI_CHAR             *pcStr = pstCmdArg->pcArgv[0];
    HI_U32              u32DelayTime = 0;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);
    DEBUG_NULL_CHK(pcStr);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1] == HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    pcStr = pstCmdArg->pcArgv[1];
    DEBUG_NULL_CHK(pcStr);
    u32DelayTime = DebugStrToU32(pcStr, &pcStr, HDMI_DEBUG_BASE_DEC);
    if(DEBUG_MAX_DELAY_MS < u32DelayTime)
    {
        HDMI_DBG_ERR("input para error.\n");
        goto usage_error;
    }

    pstHdmiDev->stDebugContext.u32StopDelay = u32DelayTime;

    return HI_SUCCESS;

usage_error:
        HDMI_DBG_PRINT("[Usage  ]: echo debugdelay argv1 > /proc/msp/hdmi0 \n");
        HDMI_DBG_PRINT("[argv1  ]: a delay time value in range [0 , %u] ms \n", DEBUG_MAX_DELAY_MS);
        HDMI_DBG_PRINT("[example]: echo debugdelay 100 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugMutedelay(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32                  s32Ret = HI_FAILURE;
    HI_U32                  u32OldDelay = 0;
    HDMI_DEVICE_S           *pstHdmiDev = HI_NULL;
    HDMI_DELAY_S            stDelay = {0};
    HI_CHAR                 *pcStr = pstCmdArg->pcArgv[0];

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);
    DEBUG_NULL_CHK(pcStr);

    if (pstCmdArg->u32Argc != 2 )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    HDMI_MEMSET(&stDelay, 0, sizeof(HDMI_DELAY_S));
    s32Ret = DRV_HDMI_DelayGet(pstHdmiDev,&stDelay);
    DEBUG_FAILURE_RET_CHK(s32Ret);
    u32OldDelay = stDelay.u32MuteDelay;

    pcStr = pstCmdArg->pcArgv[1];
    DEBUG_NULL_CHK(pcStr);
    stDelay.u32MuteDelay = DebugStrToU32(pcStr,&pcStr,HDMI_DEBUG_BASE_DEC);
    if (stDelay.u32MuteDelay > DEBUG_MAX_DELAY_MS)
    {
        HDMI_DBG_ERR("error delay time!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_DelaySet(pstHdmiDev,&stDelay);
    HDMI_DBG_PRINT("\n avmute delay set %u -> %u ms %s! \n\n",
                    u32OldDelay,
                    stDelay.u32MuteDelay,
                    s32Ret==HI_SUCCESS ? STR_SUCC : STR_FAIL);

    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo mutedelay argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: a delay time value in range [0 , %u] ms \n",DEBUG_MAX_DELAY_MS);
    HDMI_DBG_PRINT("[example]: echo mutedelay 100 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugFmtdelay(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32                  s32Ret = HI_FAILURE;
    HI_U32                  u32OldDelay = 0;
    HDMI_DEVICE_S           *pstHdmiDev = HI_NULL;
    HDMI_DELAY_S            stDelay = {0};
    HI_CHAR                 *pcStr = pstCmdArg->pcArgv[0];

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);
    DEBUG_NULL_CHK(pcStr);

    if (pstCmdArg->u32Argc != 2 )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    HDMI_MEMSET(&stDelay, 0, sizeof(HDMI_DELAY_S));
    s32Ret = DRV_HDMI_DelayGet(pstHdmiDev,&stDelay);
    DEBUG_FAILURE_RET_CHK(s32Ret);
    u32OldDelay = stDelay.u32FmtDelay;

    pcStr = pstCmdArg->pcArgv[1];
    DEBUG_NULL_CHK(pcStr);
    stDelay.u32FmtDelay = DebugStrToU32(pcStr,&pcStr,HDMI_DEBUG_BASE_DEC);
    if (stDelay.u32FmtDelay > DEBUG_MAX_DELAY_MS)
    {
        HDMI_DBG_ERR("error delay time!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_DelaySet(pstHdmiDev,&stDelay);
    HDMI_DBG_PRINT("\n format delay set %u -> %u ms %s! \n\n",
                    u32OldDelay,
                    stDelay.u32FmtDelay,
                    s32Ret==HI_SUCCESS ? STR_SUCC : STR_FAIL);

    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo fmtdelay argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: a delay time value in range [0 , %u] ms \n",DEBUG_MAX_DELAY_MS);
    HDMI_DBG_PRINT("[example]: echo fmtdelay 100 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugFmtForce(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32                  s32Ret = HI_FAILURE;
    HI_BOOL                 bOldMode = 0;
    HDMI_DEVICE_S           *pstHdmiDev = HI_NULL;
    HDMI_DELAY_S            stDelay = {0};

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    HDMI_MEMSET(&stDelay, 0, sizeof(HDMI_DELAY_S));
    s32Ret = DRV_HDMI_DelayGet(pstHdmiDev,&stDelay);
    DEBUG_FAILURE_RET_CHK(s32Ret);
    bOldMode = stDelay.bForceFmtDelay;

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
       stDelay.bForceFmtDelay = HI_FALSE;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
       stDelay.bForceFmtDelay = HI_TRUE;
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_DelaySet(pstHdmiDev,&stDelay);
    HDMI_DBG_PRINT("\n Format change set %s->%s mode %s! \n\n",
                    bOldMode ? "USER" : "KERNEL_DEFAULT",
                    stDelay.bForceFmtDelay ? "USER" : "KERNEL_DEFAULT",
                    s32Ret!=HI_SUCCESS ? STR_FAIL: STR_SUCC);

    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo fmtforce argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--format change mode in kernel default mode.\n"
                   "           1\t--format change mode in user mode.\n");
    HDMI_DBG_PRINT("[example]: echo fmtforce 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugMuteforce(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32                  s32Ret = HI_FAILURE;
    HI_BOOL                 bOldMode = 0;
    HDMI_DEVICE_S           *pstHdmiDev = HI_NULL;
    HDMI_DELAY_S            stDelay = {0};

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);
    HDMI_MEMSET(&stDelay, 0, sizeof(HDMI_DELAY_S));

    if (pstCmdArg->u32Argc != 2 )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_DelayGet(pstHdmiDev,&stDelay);
    DEBUG_FAILURE_RET_CHK(s32Ret);
    bOldMode = stDelay.bForceMuteDelay;

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
       stDelay.bForceMuteDelay = HI_FALSE;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
       stDelay.bForceMuteDelay = HI_TRUE;
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_DelaySet(pstHdmiDev,&stDelay);
    HDMI_DBG_PRINT("\n Format change set %s->%s mode %s! \n\n",
                    bOldMode ? "USER" : "KERNEL_DEFAULT",
                    stDelay.bForceMuteDelay ? "USER" : "KERNEL_DEFAULT",
                    s32Ret!=HI_SUCCESS ? STR_FAIL: STR_SUCC);

    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo muteforce argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--avmute change mode in kernel default mode.\n"
                   "           1\t--avmute change mode in user mode.\n");
    HDMI_DBG_PRINT("[example]: echo muteforce 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}


static HI_S32 DebugCbar(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HDMI_DEVICE_S   *pstHdmiDev = HI_NULL;
    HI_BOOL         bEnable = HI_FALSE;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
       bEnable = HI_FALSE;
       HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_COLOR_BAR,&bEnable);
       HDMI_DBG_PRINT("\n ColorBar is OFF %s! \n\n",STR_SUCC);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
       bEnable = HI_TRUE;
       HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_COLOR_BAR,&bEnable);
       HDMI_DBG_PRINT("\n ColorBar is ON %s! \n\n",STR_SUCC);
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo cbar argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--colorbar off.\n"
                   "           1\t--colorbar on.\n");
    HDMI_DBG_PRINT("[example]: echo cbar 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}




static HI_S32 DebugScdc(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HDMI_SCDC_STATUS_S  stScdcStatus = {0};

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);
    HDMI_MEMSET(&stScdcStatus, 0, sizeof(HDMI_SCDC_STATUS_S));

    if (pstCmdArg->u32Argc > 4 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }
#ifdef HDMI_SUPPORT_LOGIC_SILICON
    if (pstHdmiDev->stHdcpInfo.bHdcpDdcBusy)
    {
        HDMI_DBG_ERR("ddc busy now!\n");
        return HI_SUCCESS;
    }
#endif

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
       stScdcStatus.bSourceScrambleOn = HI_FALSE;
       stScdcStatus.bSinkScrambleOn = HI_FALSE;
       stScdcStatus.u8TmdsBitClkRatio = 10;
       HDMI_HAL_CALL(HAL_HDMI_PhyOutputEnableSet, pstHdmiDev->pstHdmiHal, HI_FALSE);
       HDMI_HAL_CALL(HAL_HDMI_ScdcStatusSet, pstHdmiDev->pstHdmiHal, &stScdcStatus);
       msleep(90);
       HDMI_HAL_CALL(HAL_HDMI_PhyOutputEnableSet, pstHdmiDev->pstHdmiHal, HI_TRUE);
       HDMI_MEMSET(&stScdcStatus,0,sizeof(stScdcStatus));

       msleep(3000);
       HDMI_HAL_CALL(HAL_HDMI_ScdcStatusGet, pstHdmiDev->pstHdmiHal, &stScdcStatus);
       HDMI_DBG_PRINT("\n scdc set OFF %s! \n\n",
                    (stScdcStatus.bSourceScrambleOn == HI_FALSE) &&
                    (stScdcStatus.bSinkScrambleOn == HI_FALSE) &&
                    (stScdcStatus.u8TmdsBitClkRatio == 10) ? STR_SUCC : STR_FAIL);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
       stScdcStatus.bSourceScrambleOn = HI_TRUE;
       stScdcStatus.bSinkScrambleOn = HI_TRUE;
       stScdcStatus.u8TmdsBitClkRatio = 40;
       HDMI_HAL_CALL(HAL_HDMI_PhyOutputEnableSet, pstHdmiDev->pstHdmiHal, HI_FALSE);
       HDMI_HAL_CALL(HAL_HDMI_ScdcStatusSet, pstHdmiDev->pstHdmiHal, &stScdcStatus);
       msleep(90);
       HDMI_HAL_CALL(HAL_HDMI_PhyOutputEnableSet, pstHdmiDev->pstHdmiHal, HI_TRUE);

       HDMI_MEMSET(&stScdcStatus,0,sizeof(stScdcStatus));
       msleep(3000);
       HDMI_HAL_CALL(HAL_HDMI_ScdcStatusGet, pstHdmiDev->pstHdmiHal, &stScdcStatus);

       HDMI_DBG_PRINT("\n scdc set ON %s! \n\n",
                    (stScdcStatus.bSourceScrambleOn == HI_TRUE) &&
                    (stScdcStatus.bSinkScrambleOn == HI_TRUE) &&
                    (stScdcStatus.u8TmdsBitClkRatio == 40) ? STR_SUCC : STR_FAIL);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2"))
    {
        HDMI_HAL_CALL(HAL_HDMI_ScdcStatusGet, pstHdmiDev->pstHdmiHal, &stScdcStatus);
    }
#if defined (HDMI_SUPPORT_LOGIC_HISIV100)
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"3"))
    {
        HI_CHAR *pcChar = HI_NULL;

        if (pstCmdArg->u32Argc < 4)
        {
            goto usage_error;
        }

        stScdcStatus.bSourceScrambleOn      = HI_TRUE;
        stScdcStatus.bSinkScrambleOn        = HI_TRUE;
        stScdcStatus.u8TmdsBitClkRatio      = 40;

        pcChar = pstCmdArg->pcArgv[2];
        DEBUG_NULL_CHK(pcChar);
        stScdcStatus.u32ScrambleInterval    = DebugStrToU32(pcChar,&pcChar,HDMI_DEBUG_BASE_DEC);

        pcChar = pstCmdArg->pcArgv[3];
        DEBUG_NULL_CHK(pcChar);
        stScdcStatus.u32ScrambleTimeout     = DebugStrToU32(pcChar,&pcChar,HDMI_DEBUG_BASE_DEC);
        stScdcStatus.bSinkReadQuest         = HI_FALSE;
        HDMI_HAL_CALL(HAL_HDMI_ScdcStatusSet, pstHdmiDev->pstHdmiHal, &stScdcStatus);
        HDMI_HAL_CALL(HAL_HDMI_ScdcStatusGet, pstHdmiDev->pstHdmiHal, &stScdcStatus);

    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"4"))
    {
        HI_CHAR *pcChar = HI_NULL;

        if (pstCmdArg->u32Argc < 4)
        {
            goto usage_error;
        }

        stScdcStatus.bSourceScrambleOn      = HI_TRUE;
        stScdcStatus.bSinkScrambleOn        = HI_TRUE;
        stScdcStatus.u8TmdsBitClkRatio      = 10;

        pcChar = pstCmdArg->pcArgv[2];
        stScdcStatus.u32ScrambleInterval    = DebugStrToU32(pcChar,&pcChar,HDMI_DEBUG_BASE_DEC);
        pcChar = pstCmdArg->pcArgv[3];
        stScdcStatus.u32ScrambleTimeout     = DebugStrToU32(pcChar,&pcChar,HDMI_DEBUG_BASE_DEC);
        stScdcStatus.bSinkReadQuest         = HI_FALSE;
        HDMI_HAL_CALL(HAL_HDMI_ScdcStatusSet, pstHdmiDev->pstHdmiHal, &stScdcStatus);
        HDMI_HAL_CALL(HAL_HDMI_ScdcStatusGet, pstHdmiDev->pstHdmiHal, &stScdcStatus);
    }
#endif
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }
    HDMI_DBG_PRINT("\n scdc get bSourceScrambleOn[%d] \n"
                       "            bSinkScrambleOn[%d] \n"
                       "          u8TmdsBitClkRatio[%d] \n\n",
                                    stScdcStatus.bSourceScrambleOn,
                                    stScdcStatus.bSinkScrambleOn,
                                    stScdcStatus.u8TmdsBitClkRatio);
    return HI_SUCCESS;

usage_error:
#if  defined (HDMI_SUPPORT_LOGIC_HISIV100)
    HDMI_DBG_PRINT("[Usage  ]: echo scdc argv1 [argv2] [argv3] > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--scdc off.\n"
                   "           1\t--scdc on.\n"
                   "           2\t--scdc status get.\n"
                   "           3\t--scdc on,40x,cfg interval & timeout.\n"
                   "           4\t--scdc on.10x,cfg interval & timeout.\n");

    HDMI_DBG_PRINT("[argv2  ]: interval.optional,in ms,range[20,200].\n");
    HDMI_DBG_PRINT("[argv3  ]: timeout.optional,in ms,range[200,1000].\n");
    HDMI_DBG_PRINT("[example]: echo scdc 1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[example]: echo scdc 3 25 300 > /proc/msp/hdmi0 \n");
#else
    HDMI_DBG_PRINT("[Usage  ]: echo scdc argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--scdc off.\n"
                   "           1\t--scdc on.\n"
                   "           2\t--scdc status get.\n");

    HDMI_DBG_PRINT("[example]: echo scdc 1 > /proc/msp/hdmi0 \n");
#endif
    return HI_FAILURE;
}

static HI_S32 DebugHdmimode(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HDMI_DEVICE_S   *pstHdmiDev = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
        HDMI_HAL_CALL(HAL_HDMI_TmdsModeSet, pstHdmiDev->pstHdmiHal,HDMI_TMDS_MODE_DVI);
        HDMI_DBG_PRINT("\n hdmi tmds mode set DVI %s! \n\n",STR_SUCC);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        HDMI_HAL_CALL(HAL_HDMI_TmdsModeSet, pstHdmiDev->pstHdmiHal,HDMI_TMDS_MODE_HDMI_1_4);
        HDMI_DBG_PRINT("\n hdmi tmds mode set HDMI1.4 %s! \n\n",STR_SUCC);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2"))
    {
        HDMI_HAL_CALL(HAL_HDMI_TmdsModeSet, pstHdmiDev->pstHdmiHal,HDMI_TMDS_MODE_HDMI_2_0);
        HDMI_DBG_PRINT("\n hdmi tmds mode set HDMI2.0 %s! \n\n",STR_SUCC);
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo hdmimode argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--DVI.\n"
                   "           1\t--HDMI1.4.\n"
                   "           2\t--HDMI2.0.\n");
    HDMI_DBG_PRINT("[example]: echo hdmimode 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugOutclrspace(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32              s32Ret = HI_FAILURE;
    HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HDMI_ATTR_S         stAttr;
    HI_U32              u32OldMode = 0;


    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_AttrGet(pstHdmiDev,&stAttr);
    DEBUG_FAILURE_RET_CHK(s32Ret);
    u32OldMode = (HI_U32)stAttr.stAppAttr.enOutColorSpace;

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
        stAttr.stAppAttr.enOutColorSpace = HDMI_COLORSPACE_RGB;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        stAttr.stAppAttr.enOutColorSpace = HDMI_COLORSPACE_YCbCr422;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2"))
    {
        stAttr.stAppAttr.enOutColorSpace = HDMI_COLORSPACE_YCbCr444;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"3"))
    {
        stAttr.stAppAttr.enOutColorSpace = HDMI_COLORSPACE_YCbCr420;
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_AttrSet(pstHdmiDev,&stAttr);
    HDMI_DBG_PRINT("\n output colorspace mode %d->%d %s! \n\n",
                    u32OldMode,
                    stAttr.stAppAttr.enOutColorSpace,
                    s32Ret==HI_SUCCESS ? STR_SUCC : STR_FAIL);

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo outclrspace argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--RGB.\n"
                   "           1\t--YUV422.\n"
                   "           2\t--YUV444.\n"
                   "           3\t--YUV420.\n");
    HDMI_DBG_PRINT("[example]: echo outclrspace 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugInclrspace(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32              s32Ret = HI_FAILURE;
    HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HDMI_ATTR_S         stAttr;
    HI_U32              u32OldMode = 0;


    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_AttrGet(pstHdmiDev,&stAttr);
    DEBUG_FAILURE_RET_CHK(s32Ret);
    u32OldMode = (HI_U32)stAttr.stVOAttr.enInColorSpace;

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
        stAttr.stVOAttr.enInColorSpace = HDMI_COLORSPACE_RGB;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        stAttr.stVOAttr.enInColorSpace = HDMI_COLORSPACE_YCbCr422;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2"))
    {
        stAttr.stVOAttr.enInColorSpace = HDMI_COLORSPACE_YCbCr444;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"3"))
    {
        stAttr.stVOAttr.enInColorSpace = HDMI_COLORSPACE_YCbCr420;
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_AttrSet(pstHdmiDev,&stAttr);
    HDMI_DBG_PRINT("\n input colorspace mode %d->%d %s! \n\n",
                    u32OldMode,
                    stAttr.stVOAttr.enInColorSpace,
                    s32Ret==HI_SUCCESS ? STR_SUCC : STR_FAIL);

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo inclrspace argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--RGB.\n"
                   "           1\t--YUV422.\n"
                   "           2\t--YUV444.\n"
                   "           3\t--YUV420.\n");
    HDMI_DBG_PRINT("[example]: echo inclrspace 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}


static HI_S32 DebugDeepclr(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32              s32Ret = HI_FAILURE;
    HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HDMI_ATTR_S         stAttr;
    HI_U32              u32OldMode = 0;


    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_AttrGet(pstHdmiDev,&stAttr);
    DEBUG_FAILURE_RET_CHK(s32Ret);
    u32OldMode = (HI_U32)stAttr.stAppAttr.enDeepColorMode;

    if (stAttr.stAppAttr.enOutColorSpace == HDMI_COLORSPACE_YCbCr422)
    {
        HDMI_DBG_ERR("current output colorspace YUV422 not support deepcolor set!Force set\n");
        //return HI_FAILURE;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
        stAttr.stAppAttr.enDeepColorMode = HDMI_DEEP_COLOR_24BIT;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        stAttr.stAppAttr.enDeepColorMode = HDMI_DEEP_COLOR_30BIT;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2"))
    {
        stAttr.stAppAttr.enDeepColorMode = HDMI_DEEP_COLOR_36BIT;
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_AttrSet(pstHdmiDev,&stAttr);
    HDMI_DBG_PRINT("\n deppcolor colorspace mode %d->%d %s! \n\n",
                    u32OldMode,
                    stAttr.stAppAttr.enDeepColorMode,
                    s32Ret==HI_SUCCESS ? STR_SUCC : STR_FAIL);

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo deepclr argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--08 bit.\n"
                   "           1\t--10 bit.\n"
                   "           2\t--12 bit.\n");
    HDMI_DBG_PRINT("[example]: echo deepclr 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}


static HI_S32 Debug3dmode(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32                  s32Ret = HI_FAILURE;
    HDMI_ATTR_S             stAttr;
    HI_U32                  u32OldMode = 0;
    HDMI_DEVICE_S           *pstHdmiDev = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_AttrGet(pstHdmiDev,&stAttr);
    DEBUG_FAILURE_RET_CHK(s32Ret);
    u32OldMode = (HI_U32)stAttr.stVOAttr.enStereoMode;

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
        stAttr.stVOAttr.enStereoMode = HDMI_3D_BUTT;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        stAttr.stVOAttr.enStereoMode = HDMI_3D_SIDE_BY_SIDE_FULL;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2"))
    {
        stAttr.stVOAttr.enStereoMode = HDMI_3D_TOP_AND_BOTTOM;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"3"))
    {
        stAttr.stVOAttr.enStereoMode = HDMI_3D_FRAME_PACKING;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"4"))
    {
        stAttr.stVOAttr.enStereoMode = HDMI_3D_SIDE_BY_SIDE_HALF;
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_AttrSet(pstHdmiDev,&stAttr);
    HDMI_DBG_PRINT("\n 3d mode set %d->%d  %s! \n\n",
                        u32OldMode ,
                        stAttr.stVOAttr.enStereoMode,
                        s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC);

    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo 3dmode argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--2D mode(%d) mode.\n",HDMI_3D_BUTT);
    HDMI_DBG_PRINT("           1\t--SIDE_BY_SIDE_FULL(%d) mode.\n",HDMI_3D_SIDE_BY_SIDE_FULL);
    HDMI_DBG_PRINT("           2\t--TOP_AND_BOTTOM(%d) mode.\n",HDMI_3D_TOP_AND_BOTTOM);
    HDMI_DBG_PRINT("           3\t--FRAME_PACKING(%d) mode.\n",HDMI_3D_FRAME_PACKING);
    HDMI_DBG_PRINT("           4\t--SIDE_BY_SIDE_HALF(%d) mode.\n",HDMI_3D_SIDE_BY_SIDE_HALF);
    HDMI_DBG_PRINT("[example]: echo 3dmode 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugPixrepet(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32                  s32Ret = HI_FAILURE;
    HDMI_ATTR_S             stAttr;
    HI_U32                  u32OldMode = 0;
    HI_U32                  u32TmpRepeat = 0;
    HI_CHAR                 *pcStr = HI_NULL;
    HDMI_DEVICE_S           *pstHdmiDev = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_AttrGet(pstHdmiDev,&stAttr);
    DEBUG_FAILURE_RET_CHK(s32Ret);
    u32OldMode = (HI_U32)stAttr.stVOAttr.u32PixelRepeat;

    pcStr = pstCmdArg->pcArgv[1];
    DEBUG_NULL_CHK(pcStr);

    u32TmpRepeat = DebugStrToU32(pcStr,&pcStr,HDMI_DEBUG_BASE_DEC);

    if (u32TmpRepeat >=1 && u32TmpRepeat <=10 && *pcStr=='\0')
    {
        stAttr.stVOAttr.u32PixelRepeat = u32TmpRepeat;
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_AttrSet(pstHdmiDev,&stAttr);
    HDMI_DBG_PRINT("\n pixel repetition set %d->%d times %s! \n\n",
                        u32OldMode ,
                        stAttr.stVOAttr.u32PixelRepeat,
                        s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC);

    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo pixrepet argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: pixel repetition times in range [1,10].\n");
    HDMI_DBG_PRINT("[example]: echo pixrepet 2 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}


static HI_S32 DebugSoundintf (HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32                  s32Ret = HI_FAILURE;
    HDMI_ATTR_S             stAttr;
    HI_U32                  u32OldMode = 0;

    HDMI_DEVICE_S           *pstHdmiDev = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_AttrGet(pstHdmiDev,&stAttr);
    DEBUG_FAILURE_RET_CHK(s32Ret);
    u32OldMode = (HI_U32)stAttr.stAOAttr.enSoundIntf;

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
        stAttr.stAOAttr.enSoundIntf = HDMI_AUDIO_INTERFACE__I2S;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        stAttr.stAOAttr.enSoundIntf = HDMI_AUDIO_INTERFACE__SPDIF;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2"))
    {
        stAttr.stAOAttr.enSoundIntf = HDMI_AUDIO_INTERFACE__HBRA;
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_AttrSet(pstHdmiDev,&stAttr);
    HDMI_DBG_PRINT("\n sound interface type set %d->%d %s! \n\n",
                        u32OldMode ,
                        stAttr.stAOAttr.enSoundIntf,
                        s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC);

    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo soundintf argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--I2S.\n"
                   "           1\t--SPDIF.\n"
                   "           2\t--HBRA.\n");
    HDMI_DBG_PRINT("[example]: echo soundintf 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugSamplefs (HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32                  s32Ret = HI_FAILURE;
    HDMI_ATTR_S             stAttr;
    HI_U32                  u32OldMode = 0;
    HI_U32                  u32TmpSample = 0;
    HI_CHAR                 *pcStr = HI_NULL;
    HDMI_DEVICE_S           *pstHdmiDev = HI_NULL;


    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_AttrGet(pstHdmiDev,&stAttr);
    DEBUG_FAILURE_RET_CHK(s32Ret);
    u32OldMode = (HI_U32)stAttr.stAOAttr.enSampleFs;

    pcStr = pstCmdArg->pcArgv[1];
    DEBUG_NULL_CHK(pcStr);

    u32TmpSample = DebugStrToU32(pcStr,&pcStr,HDMI_DEBUG_BASE_DEC);
    if (*pcStr != '\0')
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    switch(u32TmpSample)
    {
        case 0 :
                stAttr.stAOAttr.enSampleFs = HDMI_SAMPLE_RATE_UNKNOWN;
                break;
        case 1 :
                stAttr.stAOAttr.enSampleFs = HDMI_SAMPLE_RATE_8K;
                break;
        case 2 :
                stAttr.stAOAttr.enSampleFs = HDMI_SAMPLE_RATE_11K;
                break;
        case 3 :
                stAttr.stAOAttr.enSampleFs = HDMI_SAMPLE_RATE_12K;
                break;
        case 4 :
                stAttr.stAOAttr.enSampleFs = HDMI_SAMPLE_RATE_16K;
                break;
        case 5 :
                stAttr.stAOAttr.enSampleFs = HDMI_SAMPLE_RATE_22K;
                break;
        case 6 :
                stAttr.stAOAttr.enSampleFs = HDMI_SAMPLE_RATE_24K;
                break;
        case 7 :
                stAttr.stAOAttr.enSampleFs = HDMI_SAMPLE_RATE_32K;
                break;
        case 8 :
                stAttr.stAOAttr.enSampleFs = HDMI_SAMPLE_RATE_44K;
                break;
        case 9 :
                stAttr.stAOAttr.enSampleFs = HDMI_SAMPLE_RATE_48K;
                break;
        case 10 :
                stAttr.stAOAttr.enSampleFs = HDMI_SAMPLE_RATE_88K;
                break;
        case 11 :
                stAttr.stAOAttr.enSampleFs = HDMI_SAMPLE_RATE_96K;
                break;
        case 12 :
                stAttr.stAOAttr.enSampleFs = HDMI_SAMPLE_RATE_176K;
                break;
        case 13 :
                stAttr.stAOAttr.enSampleFs = HDMI_SAMPLE_RATE_192K;
                break;
        case 14 :
                stAttr.stAOAttr.enSampleFs = HDMI_SAMPLE_RATE_768K;
                break;
        default:
            HDMI_DBG_ERR("error argvs!\n");
            goto usage_error;
            break;
    }

    s32Ret = DRV_HDMI_AttrSet(pstHdmiDev,&stAttr);
    HDMI_DBG_PRINT("\n audio sampling frequency  set %d->%d HZ %s! \n\n",
                        u32OldMode ,
                        stAttr.stAOAttr.enSampleFs,
                        s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC);

    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo samplefs argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: audio sampling frequency list as below (HZ)\n");
    HDMI_DBG_PRINT("           0\t--%u.\n",HDMI_SAMPLE_RATE_UNKNOWN);
    HDMI_DBG_PRINT("           1\t--%u.\n",HDMI_SAMPLE_RATE_8K);
    HDMI_DBG_PRINT("           2\t--%u.\n",HDMI_SAMPLE_RATE_11K);
    HDMI_DBG_PRINT("           3\t--%u.\n",HDMI_SAMPLE_RATE_12K);
    HDMI_DBG_PRINT("           4\t--%u.\n",HDMI_SAMPLE_RATE_16K);
    HDMI_DBG_PRINT("           5\t--%u.\n",HDMI_SAMPLE_RATE_22K);
    HDMI_DBG_PRINT("           6\t--%u.\n",HDMI_SAMPLE_RATE_24K);
    HDMI_DBG_PRINT("           7\t--%u.\n",HDMI_SAMPLE_RATE_32K);
    HDMI_DBG_PRINT("           8\t--%u.\n",HDMI_SAMPLE_RATE_44K);
    HDMI_DBG_PRINT("           9\t--%u.\n",HDMI_SAMPLE_RATE_48K);
    HDMI_DBG_PRINT("           10\t--%u.\n",HDMI_SAMPLE_RATE_88K);
    HDMI_DBG_PRINT("           11\t--%u.\n",HDMI_SAMPLE_RATE_96K);
    HDMI_DBG_PRINT("           12\t--%u.\n",HDMI_SAMPLE_RATE_176K);
    HDMI_DBG_PRINT("           13\t--%u.\n",HDMI_SAMPLE_RATE_192K);
    HDMI_DBG_PRINT("           14\t--%u.\n",HDMI_SAMPLE_RATE_768K);
    HDMI_DBG_PRINT("[example]: echo samplefs 1 > /proc/msp/hdmi0 \n");
    return HI_FAILURE;
}


static HI_S32 DebugChannel(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32                  s32Ret = HI_FAILURE;
    HDMI_ATTR_S             stAttr;
    HI_U32                  u32OldMode = 0;

    HDMI_DEVICE_S           *pstHdmiDev = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_AttrGet(pstHdmiDev,&stAttr);
    DEBUG_FAILURE_RET_CHK(s32Ret);
    u32OldMode = (HI_U32)stAttr.stAOAttr.enChanels;

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
        stAttr.stAOAttr.enChanels = HDMI_AUDIO_FORMAT_2CH;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        stAttr.stAOAttr.enChanels = HDMI_AUDIO_FORMAT_8CH;
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_AttrSet(pstHdmiDev,&stAttr);
    HDMI_DBG_PRINT("\n audio channel set %d->%d %s! \n\n",
                        u32OldMode ,
                        stAttr.stAOAttr.enChanels,
                        s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC);

    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo channel argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--2 channels.\n"
                   "           1\t--8 channels (multi-channel).\n");
    HDMI_DBG_PRINT("[example]: echo channel 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}


static HI_S32 DebugSampledepth(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32                  s32Ret = HI_FAILURE;
    HDMI_ATTR_S             stAttr;
    HI_U32                  u32OldMode = 0;
    HI_U32                  u32TmpDepth = 0;
    HI_CHAR                 *pcStr = HI_NULL;
    HDMI_DEVICE_S           *pstHdmiDev = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_AttrGet(pstHdmiDev,&stAttr);
    DEBUG_FAILURE_RET_CHK(s32Ret);
    u32OldMode = (HI_U32)stAttr.stAOAttr.enSampleDepth;

    pcStr = pstCmdArg->pcArgv[1];
    DEBUG_NULL_CHK(pcStr);

    u32TmpDepth = DebugStrToU32(pcStr,&pcStr,HDMI_DEBUG_BASE_DEC);
    if (*pcStr != '\0')
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    switch(u32TmpDepth)
    {
        case 0 :
                stAttr.stAOAttr.enSampleDepth = HDMI_AUDIO_BIT_DEPTH_UNKNOWN;
                break;
        case 1 :
                stAttr.stAOAttr.enSampleDepth = HDMI_AUDIO_BIT_DEPTH_8;
                break;
        case 2 :
                stAttr.stAOAttr.enSampleDepth = HDMI_AUDIO_BIT_DEPTH_16;
                break;
        case 3 :
                stAttr.stAOAttr.enSampleDepth = HDMI_AUDIO_BIT_DEPTH_18;
                break;
        case 4 :
                stAttr.stAOAttr.enSampleDepth = HDMI_AUDIO_BIT_DEPTH_20;
                break;
        case 5 :
                stAttr.stAOAttr.enSampleDepth = HDMI_AUDIO_BIT_DEPTH_24;
                break;
        case 6 :
                stAttr.stAOAttr.enSampleDepth = HDMI_AUDIO_BIT_DEPTH_32;
                break;
        default:
                HDMI_DBG_ERR("error argvs!\n");
                goto usage_error;
                //break;
    }

    s32Ret = DRV_HDMI_AttrSet(pstHdmiDev,&stAttr);
    HDMI_DBG_PRINT("\n audio sampling depth set %d->%d %s! \n\n",
                        u32OldMode ,
                        stAttr.stAOAttr.enSampleDepth,
                        s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC);

    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo sampledepth argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: audio sampling depth list as below (BIT)\n");
    HDMI_DBG_PRINT("           0\t--%u.\n",HDMI_AUDIO_BIT_DEPTH_UNKNOWN);
    HDMI_DBG_PRINT("           1\t--%u.\n",HDMI_AUDIO_BIT_DEPTH_8);
    HDMI_DBG_PRINT("           2\t--%u.\n",HDMI_AUDIO_BIT_DEPTH_16);
    HDMI_DBG_PRINT("           3\t--%u.\n",HDMI_AUDIO_BIT_DEPTH_18);
    HDMI_DBG_PRINT("           4\t--%u.\n",HDMI_AUDIO_BIT_DEPTH_20);
    HDMI_DBG_PRINT("           5\t--%u.\n",HDMI_AUDIO_BIT_DEPTH_24);
    HDMI_DBG_PRINT("           6\t--%u.\n",HDMI_AUDIO_BIT_DEPTH_32);
    HDMI_DBG_PRINT("[example]: echo sampledepth 1 > /proc/msp/hdmi0 \n");
    return HI_FAILURE;
}


static HI_S32 DebugDither(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HDMI_VIDEO_DITHER_E enDitherMode = HDMI_VIDEO_DITHER_DISALBE;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    enDitherMode = HDMI_VIDEO_DITHER_DISALBE;

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
       enDitherMode = HDMI_VIDEO_DITHER_DISALBE;

       HDMI_DBG_PRINT("\n dither is disable %s! \n\n",STR_SUCC);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        enDitherMode = HDMI_VIDEO_DITHER_10_8;
        HDMI_DBG_PRINT("\n dither is enable 10_08 %s! \n\n",STR_SUCC);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2"))
    {
        enDitherMode = HDMI_VIDEO_DITHER_12_8;
        HDMI_DBG_PRINT("\n dither is enable 12_08 %s! \n\n",STR_SUCC);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"3"))
    {
        enDitherMode = HDMI_VIDEO_DITHER_12_10;
        HDMI_DBG_PRINT("\n dither is enable 12_10 %s! \n\n",STR_SUCC);
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_DITHER,&enDitherMode);

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo dither argv1 > /proc/msp/hdmi0\n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--dither disable.\n"
                   "           1\t--10_08.\n"
                   "           2\t--12_08.\n"
                   "           3\t--12_10.\n");
    HDMI_DBG_PRINT("[example]: echo dither 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugSwrst(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HDMI_DEVICE_S   *pstHdmiDev = HI_NULL;
    HI_CHAR         *pcStr = HI_NULL;
    HI_U32          u32DataRstMs = 0;
    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc < 1  )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }
    pcStr = pstCmdArg->pcArgv[2];
    if (pstCmdArg->pcArgv[2])
    {
        u32DataRstMs = DebugStrToU32(pcStr, &pcStr, HDMI_DEBUG_BASE_DEC);
    }

    if ( (!pstCmdArg->pcArgv[1]) || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0") )
    {
        HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_SW_RESET,HI_NULL);
        HDMI_DBG_PRINT("\n pwd reset set %s! \n\n",STR_SUCC);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        HDMI_HAL_CALL(HAL_HDMI_DataReset, pstHdmiDev->pstHdmiHal->stHalCtx.u32HdmiID, HI_TRUE,u32DataRstMs);
        HDMI_DBG_PRINT("\n audio & video reset set %s! \n\n",STR_SUCC);
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo swrst argv1 [argv2] > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--pwd reset.[argv2] no use.\n"
                   "           1\t--audio & video data reset.\n"
                   "[argv2  ]: only use for argv1 is 1,data reset delay times(ms).\n");
    HDMI_DBG_PRINT("[example]: echo swrst > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugSuspend(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HDMI_DEVICE_S   *pstHdmiDev = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
       pstHdmiDev->enSuspendState = HDMI_SUSPEND_NONE;

       HDMI_DBG_PRINT("\n suspendmode set none %s! \n\n",STR_SUCC);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        pstHdmiDev->enSuspendState = HDMI_SUSPEND_FAKE;
        HDMI_DBG_PRINT("\n suspendmode set fake %s! \n\n",STR_SUCC);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2"))
    {
        pstHdmiDev->enSuspendState = HDMI_SUSPEND_REAL;
        HDMI_DBG_PRINT("\n suspendmode set real %s! \n\n",STR_SUCC);
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }
    HDMI_DBG_PRINT("\n suspendmode debug %s! \n\n",STR_SUCC);

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo suspend > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--suspend mode none.\n"
                   "           1\t--suspend mode fake.\n"
                   "           2\t--suspend mode real.\n");
    HDMI_DBG_PRINT("[example]: echo suspend 2 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

#if defined (HDMI_SUPPORT_LOGIC_SILICON)

static HI_S32 DebugRgb2yuv(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HDMI_DEVICE_S           *pstHdmiDev = HI_NULL;
    HI_BOOL                 bEnable = HI_FALSE;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    HDMI_DBG_PRINT(" in-colorspace is %d(0-RGB;2-YUV444) !\n",pstHdmiDev->stAttr.stVOAttr.enInColorSpace);

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
        bEnable = HI_FALSE;
        HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_RGB2YUV,&bEnable);
        HDMI_DBG_PRINT("\n rgb2yuv set OFF %s! \n\n",STR_SUCC);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        bEnable = HI_TRUE;
        HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_RGB2YUV,&bEnable);
        HDMI_DBG_PRINT("\n rgb2yuv set ON %s! \n\n",STR_SUCC);
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo rgb2yuv argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--OFF.\n"
                   "           1\t--ON.\n");
    HDMI_DBG_PRINT("[example]: echo rgb2yuv 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugYuv2rgb(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HDMI_DEVICE_S           *pstHdmiDev = HI_NULL;
    HI_BOOL                 bEnable = HI_FALSE;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    HDMI_DBG_PRINT("in-colorspace is %d(0-RGB;2-YUV444) !\n",pstHdmiDev->stAttr.stVOAttr.enInColorSpace);

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
        bEnable = HI_FALSE;
        HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_YUV2RGB,&bEnable);
        HDMI_DBG_PRINT("\n Yuv2rgb set OFF %s! \n\n",STR_SUCC);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        bEnable = HI_TRUE;
        HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_YUV2RGB,&bEnable);
        HDMI_DBG_PRINT("\n Yuv2rgb set ON %s! \n\n",STR_SUCC);
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo yuv2rgb argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--OFF.\n"
                   "           1\t--ON.\n");
    HDMI_DBG_PRINT("[example]: echo yuv2rgb 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugDdc(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{

    HI_U32          u32DdcFreq      = 0;
    HI_U32          i               = 0;
    HDMI_DEVICE_S   *pstHdmiDev     = HI_NULL;
    HI_CHAR         *pcStr          = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    pcStr = pstCmdArg->pcArgv[1];


    u32DdcFreq = DebugStrToU32(pcStr,&pcStr,HDMI_DEBUG_BASE_DEC);

    if (u32DdcFreq >= HDMI_ARRAY_SIZE(s_astDdcFreq))
    {
        goto usage_error;
    }

    HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_DDC_FREQ,&s_astDdcFreq[u32DdcFreq].u32DdcRegCfg);
    HDMI_DBG_PRINT("\n ddc frequency set %s KHz %s! \n\n",s_astDdcFreq[u32DdcFreq].pstReadValue,STR_SUCC);


    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo ddc argv1 > /proc/msp/hdmi0\n");
    HDMI_DBG_PRINT("[argv1  ]: ddc frequency [0,%u]\n",HDMI_ARRAY_SIZE(s_astDdcFreq)-1);
    for (i = 0;i < HDMI_ARRAY_SIZE(s_astDdcFreq);i++)
    {
        HDMI_DBG_PRINT("           %2u -- %3u KHz (real %s KHz,Reg=0x%02x)\n",
            i,
            s_astDdcFreq[i].u32ApproximateValue,
            s_astDdcFreq[i].pstReadValue,
            s_astDdcFreq[i].u32DdcRegCfg);
    }
    HDMI_DBG_PRINT("[example]: echo ddc 1 > /proc/msp/hdmi0\n");

    return HI_FAILURE;
}

static HI_S32 DebugBypass(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HDMI_DEVICE_S   *pstHdmiDev = HI_NULL;
    HI_BOOL         bEnable = HI_FALSE;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
       bEnable = HI_FALSE;
       HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_BYPASS,&bEnable);
       HDMI_DBG_PRINT("\n bypass is OFF %s! \n\n",STR_SUCC);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
       bEnable = HI_TRUE;
       HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_BYPASS,&bEnable);
       HDMI_DBG_PRINT("\n bypass is ON %s! \n\n",STR_SUCC);
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo bypass argv1 > /proc/msp/hdmi0\n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--bypass off.\n"
                   "           1\t--bypass on.\n");
    HDMI_DBG_PRINT("[example]: echo bypass 1 > /proc/msp/hdmi0\n");

    return HI_FAILURE;
}

static HI_S32 DebugPhyParaPrint(HDMI_HAL_PHY_PARA_S *pstPhyCfg)
{
    DEBUG_NULL_CHK(pstPhyCfg);
    HDMI_DBG_PRINT("\t  %-20s= 0x%02x\n", "DataSwing",          pstPhyCfg->u8DataSwing);
    HDMI_DBG_PRINT("\t  %-20s= 0x%02x\n", "ClkSwing",           pstPhyCfg->u8ClkSwing);
    HDMI_DBG_PRINT("\t  %-20s= 0x%02x\n", "SrcTermination",     pstPhyCfg->u8SrcTermination);
    HDMI_DBG_PRINT("\t  %-20s= 0x%02x\n", "DrvVnbValue",        pstPhyCfg->u8DrvVnbValue);
    HDMI_DBG_PRINT("\t  %-20s= 0x%02x\n", "ClkSrcFineAdjust",   pstPhyCfg->u8ClkSrcFineAdjust);
    HDMI_DBG_PRINT("\t  %-20s= 0x%02x\n", "TxRegZone",          pstPhyCfg->u8TxRegZone);
    HDMI_DBG_PRINT("\t  %-20s= 0x%02x\n", "RiseTime",           pstPhyCfg->u8RiseTime);
    HDMI_DBG_PRINT("\t  %-20s= 0x%02x\n", "FallTime",           pstPhyCfg->u8FallTime);
    return HI_SUCCESS;
}

static HI_S32 DebugPhypara(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32              i = 0;
    HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HI_CHAR             *pcStr = HI_NULL;
    HI_CHAR             *pu8Phy = HI_NULL;
    HDMI_HAL_PHY_PARA_S stPhyCfg = {0};

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    HDMI_MEMSET(&stPhyCfg, 0, sizeof(HDMI_HAL_PHY_PARA_S));

    if (pstCmdArg->u32Argc != 9)
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;

    }
    for (i=0,pcStr = pstCmdArg->pcArgv[1],pu8Phy = (HI_U8 *)&stPhyCfg;
          i < sizeof(stPhyCfg) && pcStr;
          ++i,pcStr=pstCmdArg->pcArgv[1+i] )
    {
        pu8Phy[i] = (HI_U8)DebugStrToU32(pcStr,&pcStr,HDMI_DEBUG_BASE_HEX);
    }
    HDMI_HAL_CALL(HAL_HDMI_PhyOutputEnableSet, pstHdmiDev->pstHdmiHal, HI_FALSE);
    HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_PHY_PARA_SET,&stPhyCfg);
    msleep(90);
    HDMI_HAL_CALL(HAL_HDMI_PhyOutputEnableSet, pstHdmiDev->pstHdmiHal, HI_TRUE);
    HDMI_DBG_PRINT("\n config phy parameter manually %s! \n\n",STR_SUCC);
    DebugPhyParaPrint(&stPhyCfg);

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo phypara argv1 argv2 argv3 argv4 argv5 argv6 argv7 argv8 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1~8]: phypara parameter & default value list below\n");
    DebugPhyParaPrint(&stPhyCfg);
    HDMI_DBG_PRINT("[example]: echo phypara a > /proc/msp/hdmi0\n");
    HDMI_DBG_PRINT("[example]: echo phypara 0x16 0x15 0x0 0x2 0x1 0x2 0x01 0x01 > /proc/msp/hdmi0\n");

    return HI_FAILURE;
}

static HI_BOOL DebugFileWriteChk(HDMI_DEBUG_CMD_ARG_S *pstCmdArg, PFILE pFile)
{
    if(HI_NULL == pstCmdArg)
    {
        return HI_FALSE;
    }

    if(pstCmdArg->u32Argc != 3 && pstCmdArg->u32Argc != 2 && pFile)
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

static HI_VOID DebugCrgRegDump(HDMI_DEBUG_CMD_ARG_S *pstCmdArg, HDMI_DEVICE_S *pstHdmiDev, PFILE pFile)
{
    HI_S32              j = 0;
    HDMI_HAL_REG_S      stReg = {0};
    HI_U8               au8Data[50] = {0};

    DEBUG_NULL_CHK_NO_RET(pstCmdArg);
    DEBUG_NULL_CHK_NO_RET(pstHdmiDev);

    HDMI_MEMSET(au8Data, '\0', sizeof(au8Data));

    stReg.u32RegAddr = 0xf8a22278;
    HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_DUMP,&stReg);
    HDMI_DBG_PRINT("himm 0x%08x 0x%08x \n",stReg.u32RegAddr,stReg.u32RegVaule);
    if(HI_TRUE == DebugFileWriteChk(pstCmdArg, pFile))
    {
        HDMI_MEMSET(au8Data,'\0',sizeof(au8Data));
        DebugSnprintf(au8Data,sizeof(au8Data),"himm 0x%08x 0x%08x \n",stReg.u32RegAddr,stReg.u32RegVaule);
        Debugfwrite(au8Data,strlen(au8Data),pFile);
    }

    stReg.u32RegAddr = 0xf8a2210c;
    HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_DUMP,&stReg);
    HDMI_DBG_PRINT("himm 0x%08x 0x%08x \n",stReg.u32RegAddr,stReg.u32RegVaule);
    if(HI_TRUE == DebugFileWriteChk(pstCmdArg, pFile))
    {
        HDMI_MEMSET(au8Data,'\0',sizeof(au8Data));
        DebugSnprintf(au8Data,sizeof(au8Data),"himm 0x%08x 0x%08x \n",stReg.u32RegAddr,stReg.u32RegVaule);
        Debugfwrite(au8Data,strlen(au8Data),pFile);
    }

    stReg.u32RegAddr = 0xf8a22110;
    HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_DUMP,&stReg);
    HDMI_DBG_PRINT("himm 0x%08x 0x%08x \n",stReg.u32RegAddr,stReg.u32RegVaule);
    if(HI_TRUE == DebugFileWriteChk(pstCmdArg, pFile))
    {
        HDMI_MEMSET(au8Data,'\0',sizeof(au8Data));
        DebugSnprintf(au8Data,sizeof(au8Data),"himm 0x%08x 0x%08x \n",stReg.u32RegAddr,stReg.u32RegVaule);
        Debugfwrite(au8Data,strlen(au8Data),pFile);
    }

    stReg.u32RegAddr = 0xf8a2217c;
    HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_DUMP,&stReg);
    HDMI_DBG_PRINT("himm 0x%08x 0x%08x \n\n",stReg.u32RegAddr,stReg.u32RegVaule);
    if(HI_TRUE == DebugFileWriteChk(pstCmdArg, pFile))
    {
        HDMI_MEMSET(au8Data,'\0',sizeof(au8Data));
        DebugSnprintf(au8Data,sizeof(au8Data),"himm 0x%08x 0x%08x \n",stReg.u32RegAddr,stReg.u32RegVaule);
        Debugfwrite(au8Data,strlen(au8Data),pFile);
    }

    for (j=7; (j>=0) && (j<=7) ;j--)
    {
        stReg.u32RegAddr = 0xf8ccc000 | (j*4);
        HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_DUMP,&stReg);
        HDMI_DBG_PRINT("himm 0x%08x 0x%08x \n",stReg.u32RegAddr,stReg.u32RegVaule);
        if(pstCmdArg->u32Argc != 3 && pstCmdArg->u32Argc != 2 && pFile)
        {
            HDMI_MEMSET(au8Data,'\0',sizeof(au8Data));
            DebugSnprintf(au8Data,sizeof(au8Data),"himm 0x%08x 0x%08x \n",stReg.u32RegAddr,stReg.u32RegVaule);
            Debugfwrite(au8Data,strlen(au8Data),pFile);
        }
        if(j == 0)
        {
            DebugSnprintf(au8Data,sizeof(au8Data),"------ HDMI register ------\n");
            Debugfwrite(au8Data,strlen(au8Data),pFile);
        }
    }

    return;
}

static HI_S32 HdmiRegDump(HDMI_DEBUG_CMD_ARG_S *pstCmdArg, HDMI_DEVICE_S *pstHdmiDev, PFILE pFile,
                          HI_U32 u32DumpLen, HI_U32 u32RegAddr)
{
    HI_U32              i = 0;
    HDMI_HAL_REG_S      stReg = {0};
    HI_U8               au8Data[50] = {0};

    DEBUG_NULL_CHK(pstCmdArg);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    stReg.u32RegAddr = u32RegAddr;
    stReg.u32RegVaule = 0;

    for (i = 0; i < u32DumpLen && stReg.u32RegAddr <= (HDMI_CTRL_BASE_ADDR | 0x3ffc); i++,stReg.u32RegAddr+=4)
    {
        stReg.u32RegAddr |= HDMI_CTRL_BASE_ADDR;
        HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_DUMP,&stReg);

        if (pstCmdArg->u32Argc == 3 || pstCmdArg->u32Argc == 2)
        {
            if (!(i%16)){HDMI_DBG_PRINT("\n");}
            HDMI_DBG_PRINT("himm 0x%08x 0x%08x \n",stReg.u32RegAddr,stReg.u32RegVaule);
        }
        else if (pFile)
        {
            HDMI_MEMSET(au8Data,'\0',sizeof(au8Data));
            DebugSnprintf(au8Data,sizeof(au8Data),"himm 0x%08x 0x%08x \n%s",stReg.u32RegAddr,stReg.u32RegVaule,(i%16)? "" :"\n");
            Debugfwrite(au8Data,strlen(au8Data),pFile);
        }
        else
        {
            HDMI_DBG_ERR("error argvs!\n");
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

static HI_S32 DebugDump(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HI_CHAR             *pcStr = HI_NULL;
    HI_S32              s32Ret = HI_SUCCESS;
    HI_U32              u32DumpLen = DEBUG_DUMP_DEFAULT_LEN;
    HDMI_HAL_REG_S      stReg = {0};
    HI_U32              u32RegAddr = 0;
    PFILE               pFile = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc < 2)
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    if (pstCmdArg->u32Argc == 4 && pstCmdArg->pcArgv[3])
    {
        pFile = Debugfopen(pstCmdArg->pcArgv[3], O_RDWR | O_CREAT| O_TRUNC, 0777);
        if (pFile == HI_NULL)
        {
            HDMI_DBG_ERR("errro open file %s\n",pstCmdArg->pcArgv[3]);
            return HI_FAILURE;
        }
    }

    pcStr = pstCmdArg->pcArgv[2];
    if (pcStr)
    {
       u32DumpLen = DebugStrToU32(pcStr,&pcStr,HDMI_DEBUG_BASE_HEX);
    }

    DEBUG_NULL_CHK(pstCmdArg->pcArgv[1]);
    pcStr = pstCmdArg->pcArgv[1];
    s32Ret = strlen(pcStr);

    if (s32Ret == 4 || s32Ret == 6)
    {
        stReg.u32RegAddr = DebugStrToU32(pcStr, &pcStr, HDMI_DEBUG_BASE_HEX);
        if (stReg.u32RegAddr < 0x3000 || stReg.u32RegAddr > 0x3fff)
        {
            HDMI_DBG_ERR("error addr 0x%x !\n",stReg.u32RegAddr);
            goto usage_error;
        }

        stReg.u32RegAddr = ((stReg.u32RegAddr - 0x3000) * 4) | HDMI_CTRL_BASE_ADDR;
        stReg.u32RegVaule = 0;
        u32RegAddr = stReg.u32RegAddr;

        if (pFile == HI_NULL)
        {
            HDMI_DBG_PRINT("\n     %-10s %-10s \n","ADDR","VALUE");
        }

#if defined(CONFIG_HDMI_STB_SDK)
        DebugCrgRegDump(pstCmdArg, pstHdmiDev, pFile);
#endif

        stReg.u32RegAddr = u32RegAddr;
        stReg.u32RegVaule = 0;

        s32Ret = HdmiRegDump(pstCmdArg, pstHdmiDev, pFile, u32DumpLen, u32RegAddr);
        if(HI_SUCCESS != s32Ret)
        {
            goto usage_error;
        }
    }
    else if (s32Ret == 8 || s32Ret == 10)
    {
        stReg.u32RegAddr = DebugStrToU32(pcStr,&pcStr,HDMI_DEBUG_BASE_HEX);
        stReg.u32RegVaule = 0;

        if (stReg.u32RegAddr < HDMI_CTRL_BASE_ADDR || stReg.u32RegAddr > (HDMI_CTRL_BASE_ADDR|0xffff))
        {
            HDMI_DBG_ERR("error addr 0x%x !\n",stReg.u32RegAddr);
            goto usage_error;
        }
        u32RegAddr = stReg.u32RegAddr;

        if (pFile==HI_NULL)
        {
            HDMI_DBG_PRINT("\n     %-10s %-10s \n","ADDR","VALUE");
        }

#if defined(CONFIG_HDMI_STB_SDK)
        DebugCrgRegDump(pstCmdArg, pstHdmiDev, pFile);
#endif

        s32Ret = HdmiRegDump(pstCmdArg, pstHdmiDev, pFile, u32DumpLen, u32RegAddr);
        if(HI_SUCCESS != s32Ret)
        {
            goto usage_error;
        }
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }
    HDMI_DBG_PRINT("\n dump register u32DumpLen=%u(0x%x) %s! \n\n",u32DumpLen,u32DumpLen,STR_SUCC);

    Debugfclose(pFile);

    return HI_SUCCESS;

usage_error:

    Debugfclose(pFile);

    HDMI_DBG_PRINT("[Usage  ]: echo dump argv1 argv2 [argv3] > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: dump address in hex.range in [0x3000,0x3fff] or [0x%x,0x%x].\n", HDMI_CTRL_BASE_ADDR,HDMI_CTRL_BASE_ADDR|0x3ffc);
    HDMI_DBG_PRINT("[argv2  ]: dump length in hex.range in [0x1,0x1000] \n");
    HDMI_DBG_PRINT("[argv3  ]: dump file path,optional.when there is argv3 then dump to argv3,or dump to terminal.\n");
    HDMI_DBG_PRINT("[example]: echo dump 0x3710 0x1000 > /proc/msp/hdmi0\n");
    HDMI_DBG_PRINT("[example]: echo dump 0x%x 0x1000 > /proc/msp/hdmi0\n",HDMI_CTRL_BASE_ADDR);
    HDMI_DBG_PRINT("[example]: echo dump 0x%x 0x1000 /mnt/stream/20150708.txt > /proc/msp/hdmi0\n",HDMI_CTRL_BASE_ADDR);

    return HI_FAILURE;
}

static HI_S32 DebugAvpath(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{

    HI_U8 *pu8VirtualAddr = HI_NULL;

    HDMI_DEVICE_S *pstHdmiDev = HI_NULL;
    DEBUG_NULL_CHK(pstCmdArg);

    if( pstCmdArg->u32Argc > 2 )
    {
        goto usage_error;
    }

    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    if(pstHdmiDev == HI_NULL)
    {
        HDMI_ERR("pstHdmiDev is null! \n");
        goto usage_error;
    }
    if(pstHdmiDev->pu32VirtualBaseAddr == HI_NULL)
    {
        HDMI_ERR("pstHdmiDev->pu32VirtualBaseAddr is null! \n");
        return HI_FAILURE;
    }

#if defined(CONFIG_HDMI_STB_SDK)
    /* HDMI hw reset */
#if 0
    pu8VirtualAddr = (HI_U8 *)HDMI_IO_MAP(HDMI_CRG_BASE_ADDR + 0x210c, 4);

    *(volatile HI_U32 *)( pu8VirtualAddr )= 0x433f;
    msleep(10);
    *(volatile HI_U32 *)( pu8VirtualAddr )= 0x403f;

    HDMI_IO_UNMAP(pu8VirtualAddr);
#endif
#else
    HI_U32 u32RegValue = 0;
    pu8VirtualAddr = (HI_U8 *)HDMI_IO_MAP(HDMI_CRG_BASE_ADDR, 4);
    u32RegValue = *(volatile HI_U32 *)( pu8VirtualAddr );

    *(volatile HI_U32 *)( pu8VirtualAddr ) = u32RegValue | HDMITX_CTRL_SRST_REQ | HDMITX_CTRL_BUS_SRST_REQ;
    msleep(10);
    *(volatile HI_U32 *)( pu8VirtualAddr ) = u32RegValue &(~( HDMITX_CTRL_SRST_REQ | HDMITX_CTRL_BUS_SRST_REQ));
    HDMI_IO_UNMAP(pu8VirtualAddr);
#endif
    msleep(10);

    pu8VirtualAddr = (HI_U8 *)pstHdmiDev->pu32VirtualBaseAddr;


    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1EC8 ) = 0x0;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1fc0 ) = 0x0;
    msleep(10);


    /* VO 1080p60 timming ,cbar enable */
    pu8VirtualAddr = (HI_U8 *)HDMI_IO_MAP(HDMI_COLOR_BAR_BASE, 0x30);

    *(volatile HI_U32 *)( pu8VirtualAddr + 0x004 ) = 0x00c28437;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x008 ) = 0x00bf077f;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x00c ) = 0x00000057;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x010 ) = 0x00000000;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x014 ) = 0x0004002b;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x018 ) = 0x01c282a3;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x01c ) = 0x83dd8232;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x000 ) = 0xe0000011;


    HDMI_IO_UNMAP(pu8VirtualAddr);

    /* HDMI ctrl */
    pu8VirtualAddr = (HI_U8 *)pstHdmiDev->pu32VirtualBaseAddr;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x0034 ) = 0x00000006;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x002C ) = 0x00000001;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x004C ) = 0x0;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x01E4 ) = 0x6;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x0194 ) = 0x00000085;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x03DC ) = 0x2;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x0890 ) = 0x4;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x2C70 ) = 0x00000000;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x3480 ) = 0x0;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x3484 ) = 0x00000000;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x3680 ) = 0x00000040;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x3684 ) = 0x00000003;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1EC0 ) = 0x00000090;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1EC4 ) = 0x0;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1EC8 ) = 0xa7;

    *(volatile HI_U32 *)( pu8VirtualAddr + 0x01D4 ) = 0x00000000;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x288C ) = 0x00000010;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x2870 ) = 0xe4;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x2808 ) = 0x00000001;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x28BC ) = 0x2;

    *(volatile HI_U32 *)( pu8VirtualAddr + 0x280C ) = 0x0;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x2810 ) = 0x00000018;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x2814 ) = 0x0;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x2818 ) = 0x00000000;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x281C ) = 0x00000000;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x2820 ) = 0x00000000;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x2874 ) = 0x60;

    *(volatile HI_U32 *)( pu8VirtualAddr + 0x2890 ) = 0xb;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x2878 ) = 0x00000000;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x287C ) = 0x00000000;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x2880 ) = 0x00000000;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x2884 ) = 0x00000002;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x2888 ) = 0x0000000B;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x2850 ) = 0x00000010;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x284C ) = 0x1;

    /* AVI IF*/
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1afc ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b00 ) = 0x82;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b04 ) = 0x2;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b08 ) = 0x0d;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b0c ) = 0x67;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b10 ) = 0x50;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b14 ) = 0xa8;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b18 ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b1c ) = 0x10;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b20 ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b24 ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b28 ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b2c ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b30 ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b34 ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b38 ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b3c ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b40 ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b44 ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b48 ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b4c ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b50 ) = 0x00;

    /* AVI IF enable */
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1afc ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b7c ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b7c ) = 0xe0;


    /* AUDIO IF */
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1afc ) = 0x2 ;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b00 ) = 0x84;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b04 ) = 0x1;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b08 ) = 0x0a;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b0c ) = 0x71;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b10 ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b14 ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b18 ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b1c ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b20 ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b24 ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b28 ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b2c ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b30 ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b34 ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b38 ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b3c ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b40 ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b44 ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b48 ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b4c ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b50 ) = 0x00;

    /* AUDIO IF enable */
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1afc ) = 0x02;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b7c ) = 0x00;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1b7c ) = 0xe0;

    /* AUDIO MUTE */
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x28bc ) = 0x82;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x28bc ) = 0x02;

    /* AUDIO ID = I2S */
    pu8VirtualAddr = (HI_U8 *)HDMI_IO_MAP(PERI_HDMITX_CTRL_ADDR, 4);
    *(volatile HI_U32 *)( pu8VirtualAddr ) = 0x00050000; //bvt 0x12120150 / stb 0xf8a208b0
    *(volatile HI_U32 *)( pu8VirtualAddr ) = 0x00050002;
    HDMI_IO_UNMAP(pu8VirtualAddr);

    /* AUDIO PATH 48000HZ,2ch,16bit */
    pu8VirtualAddr = (HI_U8 *)pstHdmiDev->pu32VirtualBaseAddr;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x2850 ) = 0x00000010;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x2878 ) = 0x00000000;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x287c ) = 0x00000000;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x2880 ) = 0x00000000;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x2884 ) = 0x00000002;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x2888 ) = 0x0000000b;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x28a0 ) = 0x00000000;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x28a4 ) = 0x00000000;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x298c ) = 0x00000082;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x2984 ) = 0x00000007;

    /* AUDIO enable */
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x284c ) = 0x0;
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x284c ) = 0x1;

    /* OE */
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1EC8 ) = 0x0;
    msleep(100);
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1fc0 ) = 0x0;
    msleep(100);
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1EC8 ) = 0xa7;
    msleep(100);
    *(volatile HI_U32 *)( pu8VirtualAddr + 0x1fc0 ) = 0x10;

    HDMI_DBG_PRINT("\n video 1080p60 & cbar & audio path set %s! \n\n", STR_SUCC );

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo avpath > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[example]: echo avpath > /proc/msp/hdmi0 \n");

    return HI_FAILURE;

}
#endif

#ifdef HDMI_CEC_SUPPORT
static HI_S32 DebugCec(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32          s32Ret = HI_SUCCESS;
    HI_U32          j = 0;
    HDMI_CEC_CMD_S  stMsg = {0};
    HI_U8           au8CecBuf[DEBUG_MAX_CEC_SIZE];
    HDMI_CEC_INFO_S  stCecInfo = {0};
    HDMI_DEVICE_S   *pstHdmiDev = HI_NULL;
    HI_CHAR         *pcStr      = HI_NULL;
    HI_BOOL         bIsTuner = HI_FALSE;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);


    if (pstCmdArg->u32Argc < 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    HDMI_MEMSET(&stCecInfo, 0, sizeof(HDMI_CEC_INFO_S));

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
       s32Ret = DRV_HDMI_CecEnableSet(pstHdmiDev, HI_FALSE);
       HDMI_DBG_PRINT("\n cec set OFF %s! \n\n",s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC );
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        s32Ret = DRV_HDMI_CecEnableSet(pstHdmiDev, HI_TRUE);
        HDMI_DBG_PRINT("\n cec set ON %s! \n\n",s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC );
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2"))
    {
        s32Ret = DRV_HDMI_CecStatusGet(pstHdmiDev, &stCecInfo);
        HDMI_DBG_PRINT("logicalAddr = 0x%02x\n",stCecInfo.u8LogicalAddr);
        for (j=0;j<16;j++)
        {
            HDMI_DBG_PRINT("newwork[%d]= 0x%02x\n",j,stCecInfo.au8Network[j]);
        }

        HDMI_DBG_PRINT("\n cec set ON %s! \n\n",s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC );
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"3"))
    {
        s32Ret = DRV_HDMI_CecStatusGet(pstHdmiDev, &stCecInfo);
        stMsg.enDstAdd = HDMI_CEC_LOGICALADD_BROADCAST;
        stMsg.enSrcAdd = stCecInfo.u8LogicalAddr;
        stMsg.u8Opcode = 0x36;
        stMsg.stOperand.stRawData.u8Length = 0x0;
        DRV_HDMI_CecCmdSend(pstHdmiDev, &stMsg);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"4"))
    {
        s32Ret = DRV_HDMI_CecStatusGet(pstHdmiDev, &stCecInfo);
        //if (stCecInfo.au8Network[HDMI_CEC_LOGICALADD_TV])
        {
            stMsg.enDstAdd = HDMI_CEC_LOGICALADD_TV;
            stMsg.enSrcAdd = stCecInfo.u8LogicalAddr;
            stMsg.u8Opcode = 0x04; // image view on
            stMsg.stOperand.stRawData.u8Length = 0x0;
            DRV_HDMI_CecCmdSend(pstHdmiDev, &stMsg);
        }
        if (stCecInfo.au8Network[HDMI_CEC_LOGICALADD_AUDIOSYSTEM])
        {
            stMsg.enDstAdd = HDMI_CEC_LOGICALADD_AUDIOSYSTEM;
            stMsg.enSrcAdd = stCecInfo.u8LogicalAddr;
            stMsg.u8Opcode = 0x70; // system audio mode request
            stMsg.stOperand.stRawData.u8Length  = 0x2;
            stMsg.stOperand.stRawData.u8Data[0] = ((stCecInfo.au8PhysicalAddr[0] << 4) & 0xf0) | (stCecInfo.au8PhysicalAddr[1] & 0x0f);
            stMsg.stOperand.stRawData.u8Data[1] = ((stCecInfo.au8PhysicalAddr[2] << 4) & 0xf0) | (stCecInfo.au8PhysicalAddr[3] & 0x0f);
            DRV_HDMI_CecCmdSend(pstHdmiDev, &stMsg);
        }
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"5"))
    {
        s32Ret = DRV_HDMI_CecStatusGet(pstHdmiDev, &stCecInfo);
        HDMI_DBG_PRINT("\n cec Recieve message count %u! \n\n",stCecInfo.u32RecieveCnt);
        if(stCecInfo.u32RecieveCnt)
        {
            DRV_HDMI_CecCmdReceive(pstHdmiDev, &stMsg);
            HDMI_DBG_PRINT("\n %10s: 0x%x \n %10s: 0x%x \n %10s: 0x%x \n %10s: 0x%x \n %10s:",
                                                        "DEST",     stMsg.enDstAdd,
                                                        "SRC",      stMsg.enSrcAdd,
                                                        "OPCODE",   stMsg.u8Opcode,
                                                        "UIOPCODE", stMsg.stOperand.enUIOpcode,
                                                        "DATA(H)");
            for (j=0;j<sizeof(stMsg.stOperand.stRawData.u8Data);j++)
                HDMI_DBG_PRINT(" %x",stMsg.stOperand.stRawData.u8Data[j]);
            HDMI_DBG_PRINT("\n\n");
        }
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"6"))
    {
        memset(au8CecBuf,0,sizeof(au8CecBuf));
        s32Ret = DebugStr2Hex(au8CecBuf,DEBUG_MAX_INFOFRAME_SIZE,pstCmdArg->pcArgv[2],pstCmdArg->u32RemainLen);
        if (s32Ret < 0)
        {
            HDMI_DBG_ERR("error hex raw data format!\n");
            goto usage_error;
        }

        stMsg.enDstAdd = au8CecBuf[0];
        stMsg.enSrcAdd = au8CecBuf[1];
        stMsg.u8Opcode = au8CecBuf[2];
        stMsg.stOperand.stRawData.u8Length = au8CecBuf[3] ;

        if(stMsg.stOperand.stRawData.u8Length > 15)
        {
            stMsg.stOperand.stRawData.u8Length = 15;
        }

        for(j = 0;j<sizeof(stMsg.stOperand.stRawData.u8Data);j++)
        {
            stMsg.stOperand.stRawData.u8Data[j] = au8CecBuf[4+j];
        }

        DRV_HDMI_CecCmdSend(pstHdmiDev, &stMsg);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"7"))
    {
        if(pstCmdArg->u32Argc < 3)
        {
            goto usage_error;
        }

        pcStr   = pstCmdArg->pcArgv[2];
        DEBUG_NULL_CHK(pcStr);

        bIsTuner = DebugStrToU32(pcStr, &pcStr, HDMI_DEBUG_BASE_DEC);
        HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_CEC_DEVICE_TYPE, &bIsTuner);
        HDMI_HAL_CALL_RET(HAL_HDMI_CecNetPing, pstHdmiDev->pstHdmiHal, pstHdmiDev->stCecInfo.au8PhysicalAddr);
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }


    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo cec argv1 [argv list] > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--cec off.\n"
                   "           1\t--cec on.\n"
                   "           2\t--cec network status.\n"
                   "           3\t--cec sent cmd standby(0x36)\n"
                   "           4\t--cec sent cmd resume(0x04).\n"
                   "           5\t--cec recieve message show.\n"
                   "           6\t--cec sent cmd.argv list: dest_addr,src_addr,opcode,data_len, oprand0~oprand14\n"
                   "           7\t--cec ping (argv2 = 0-Playback, 1-Tuner).\n");

    HDMI_DBG_PRINT("[example]: echo cec 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

#endif

#ifdef HDMI_HDR_SUPPORT
static HI_S32 DebugHdr(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32              s32Ret      = HI_FAILURE;
    HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HDMI_ATTR_S         stAttr;
    HI_U32              u32OldMode  = 0;
    HDMI_HDR_ATTR_S     *pstHdrAttr = HI_NULL;
    HDMI_HDR_INFO_S     *pstHdrInfo = HI_NULL;
    HI_U32               u32Time    = 0;
    HI_CHAR             *pcStr      = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc < 2 || pstCmdArg->pcArgv[1] == HI_NULL)
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }
    pstHdrAttr = &(pstHdmiDev->stAttr.stHdrAttr);
    pstHdrInfo = &(pstHdmiDev->stHdrInfo);

    u32OldMode = pstHdrAttr->enUserHdrMode;

    if(IS_STR_EQUAL(pstCmdArg->pcArgv[1], "0"))
    {
        /* HDR mode set. */
        if (IS_STR_EQUAL(pstCmdArg->pcArgv[2], "1"))
        {
            pstHdrAttr->enUserHdrMode = HDMI_HDR_USERMODE_HDR10;
        }
        else if (IS_STR_EQUAL(pstCmdArg->pcArgv[2], "2"))
        {
            pstHdrAttr->enUserHdrMode = HDMI_HDR_USERMODE_DOLBY;
        }
        else
        {
            pstHdrAttr->enUserHdrMode = HDMI_HDR_USERMODE_SDR;
        }

        s32Ret = DRV_HDMI_AttrGet(pstHdmiDev, &stAttr);
        DEBUG_FAILURE_RET_CHK(s32Ret);

        DRV_HDMI_Stop(pstHdmiDev);
        s32Ret = DRV_HDMI_AttrSet(pstHdmiDev, &stAttr);
        DRV_HDMI_Start(pstHdmiDev);

        HDMI_DBG_PRINT("\n user hdr mode change %d->%d %s! \n\n",
                        u32OldMode,
                        stAttr.stHdrAttr.enUserHdrMode,
                        s32Ret==HI_SUCCESS ? STR_SUCC : STR_FAIL);
    }
    else if(IS_STR_EQUAL(pstCmdArg->pcArgv[1], "1"))
    {
        if(pstCmdArg->u32Argc < 3)
        {
            goto usage_error;
        }

        if(IS_STR_EQUAL(pstCmdArg->pcArgv[2], "1"))
        {
            pstHdrInfo->enHdrDebugMode = HDMI_HDR_DEBUG_MODE_OE;
        }
        else if(IS_STR_EQUAL(pstCmdArg->pcArgv[2], "2"))
        {
            pstHdrInfo->enHdrDebugMode = HDMI_HDR_DEBUG_MODE_AVMUTE;
        }
        else
        {
            pstHdrInfo->enHdrDebugMode = HDMI_HDR_DEBUG_MODE_NONE;
        }

        HDMI_DBG_PRINT("\n debug mode set %d! \n\n", pstHdrInfo->enHdrDebugMode);
    }
    else if(IS_STR_EQUAL(pstCmdArg->pcArgv[1], "2"))
    {
        if(pstCmdArg->u32Argc < 3)
        {
            goto usage_error;
        }

        pcStr   = pstCmdArg->pcArgv[2];
        DEBUG_NULL_CHK(pcStr);

        u32Time = DebugStrToU32(pcStr, &pcStr, HDMI_DEBUG_BASE_DEC);
        if(1 > u32Time)
        {
            goto usage_error;
        }

        HDMI_DBG_PRINT("\n debug OE delay time change %d->%d! \n\n", pstHdrInfo->stHdrModeChnTimer.u32Time, u32Time);
        pstHdrInfo->stHdrModeChnTimer.u32Time = u32Time;
    }
    else if(IS_STR_EQUAL(pstCmdArg->pcArgv[1], "3"))
    {
        if(pstCmdArg->u32Argc < 3)
        {
            goto usage_error;
        }

        pcStr   = pstCmdArg->pcArgv[2];
        DEBUG_NULL_CHK(pcStr);

        u32Time = DebugStrToU32(pcStr, &pcStr, HDMI_DEBUG_BASE_DEC);
        if(1 > u32Time)
        {
            goto usage_error;
        }
        HDMI_DBG_PRINT("\n debug Zero DRM Infoframe send time change %d->%d! \n\n", pstHdrInfo->stZeroDrmIfTimer.u32Time, u32Time);
        pstHdrInfo->stZeroDrmIfTimer.u32Time = u32Time;
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo hdr argv1 argv2 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: HDR debug command.\n");
    HDMI_DBG_PRINT("           0\t--debug HDR mode set (argv2 = 0-SDR, 1-HDR10, 2-Dolby).\n"
                   "           1\t--debug mode set when the HDR mode change to HDR10 (argv2 = 0-debug disable, 1-OE, 2-AVMUTE).\n"
                   "           2\t--debug mode delay time(1~10000ms, default 100ms).\n"
                   "           3\t--Zero DRM Infoframe send time(1-10000ms, default 2000ms).\n");

    HDMI_DBG_PRINT("[argv2  ]: Command param.\n");
    HDMI_DBG_PRINT("[example]: echo hdr 0 1 > /proc/msp/hdmi0\n");
    HDMI_DBG_PRINT("[example]: echo hdr 1 2 > /proc/msp/hdmi0\n");
    HDMI_DBG_PRINT("[example]: echo hdr 2 500 > /proc/msp/hdmi0\n");
    HDMI_DBG_PRINT("[example]: echo hdr 3 3000 > /proc/msp/hdmi0\n");

    return HI_FAILURE;
}

#endif


#ifdef HDMI_HDCP_SUPPORT
static HI_S32 DebugHdcp14(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32              s32Ret = HI_FAILURE;
    HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HDMI_ATTR_S         stAttr;
    //static HI_BOOL      bHdcp1preBack = HI_FALSE;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }
    //bHdcp1preBack = pstHdmiDev->stHdcpInfo.bHdcp1Prep;
    s32Ret = DRV_HDMI_AttrGet(pstHdmiDev, &stAttr);
    if (s32Ret!=HI_SUCCESS)
    {
        HDMI_DBG_ERR("get attr error!\n");
        return HI_FAILURE;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
        DRV_HDMI_Stop(pstHdmiDev);
        stAttr.stAppAttr.bHDCPEnable = HI_FALSE;
        stAttr.stAppAttr.enHDCPMode = HDMI_HDCP_MODE_1_4;
        s32Ret = DRV_HDMI_AttrSet(pstHdmiDev, &stAttr);
        DRV_HDMI_Start(pstHdmiDev);
        HDMI_DBG_PRINT("\n hdcp1.4 set OFF %s! \n\n",s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC );
        //pstHdmiDev->stHdcpInfo.bHdcp1Prep = HI_FALSE;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {

        DRV_HDMI_Stop(pstHdmiDev);
        stAttr.stAppAttr.bHDCPEnable = HI_TRUE;
        stAttr.stAppAttr.enHDCPMode = HDMI_HDCP_MODE_1_4;
        s32Ret = DRV_HDMI_AttrSet(pstHdmiDev, &stAttr);
        DRV_HDMI_Start(pstHdmiDev);
        HDMI_DBG_PRINT("\n hdcp1.4 set ON %s! \n\n",s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC );
        //pstHdmiDev->stHdcpInfo.bHdcp1Prep = HI_TRUE;
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo hdcp14 argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 1\t--hdcp1.4 on.\n"
                   "           0\t--hdcp1.4 off.\n");
    HDMI_DBG_PRINT("[example]: echo hdcp14 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugHdcp22(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32              s32Ret = HI_FAILURE;
    HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HDMI_ATTR_S         stAttr;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    s32Ret = DRV_HDMI_AttrGet(pstHdmiDev, &stAttr);
    if (s32Ret!=HI_SUCCESS)
    {
        HDMI_DBG_ERR("get attr error!\n");
        return HI_FAILURE;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
        DRV_HDMI_Stop(pstHdmiDev);
        stAttr.stAppAttr.bHDCPEnable = HI_FALSE;
        stAttr.stAppAttr.enHDCPMode = HDMI_HDCP_MODE_2_2;
        s32Ret = DRV_HDMI_AttrSet(pstHdmiDev, &stAttr);
        DRV_HDMI_Start(pstHdmiDev);
        HDMI_DBG_PRINT("\n hdcp2.2 set OFF %s! \n\n",s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC );
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        DRV_HDMI_Stop(pstHdmiDev);
        stAttr.stAppAttr.bHDCPEnable = HI_TRUE;
        stAttr.stAppAttr.enHDCPMode = HDMI_HDCP_MODE_2_2;
        s32Ret = DRV_HDMI_AttrSet(pstHdmiDev, &stAttr);
        DRV_HDMI_Start(pstHdmiDev);
        HDMI_DBG_PRINT("\n hdcp2.2 set ON %s! \n\n",s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC );
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2"))
    {
        s32Ret = HDMI_HAL_CALL_RET(HAL_HDMI_HdcpMcuCodeLoad, pstHdmiDev->pstHdmiHal,HDMI_HDCP_MODE_2_2);
        HDMI_DBG_PRINT("\n hdcp2.2 load mcu code %s! \n\n",s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC );
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo hdcp22 argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--hdcp2.2 off.\n"
                   "           1\t--hdcp2.2 on.\n"
                   "           2\t--hdcp2.2 load 8051 mcu code.\n");
    HDMI_DBG_PRINT("[example]: echo hdcp22 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugLoadkey(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32              s32Ret = HI_FAILURE;
    HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HI_U8               *pu8Buf = HI_NULL;
    PFILE               pFile = HI_NULL;
    HDMI_LOAD_KEY_S     stLoadKey ;


    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    HDMI_MEMSET(&stLoadKey,0,sizeof(stLoadKey));
    pu8Buf = (HI_U8 *)HDMI_VMALLOC(DEBUG_MAX_HDCPKEY_SIZE);
    DEBUG_NULL_CHK(pu8Buf);
    HDMI_MEMSET(pu8Buf,0,DEBUG_MAX_HDCPKEY_SIZE);

    pFile = Debugfopen(pstCmdArg->pcArgv[1],O_RDWR ,0);
    if (pFile == HI_NULL)
    {
        HDMI_DBG_ERR("errro open file %s\n",pstCmdArg->pcArgv[1]);
        HDMI_VFREE(pu8Buf);
        return HI_FAILURE;
    }
    s32Ret = Debugfread((HI_CHAR *)pu8Buf,DEBUG_MAX_HDCPKEY_SIZE-1,pFile);
    Debugfclose(pFile);
    if (s32Ret > 0)
    {
        stLoadKey.u32KeyLength = s32Ret;
        stLoadKey.pu8InputEncryptedKeyAddr = pu8Buf;
    }
    else
    {
        HDMI_DBG_ERR("read file len=%d \n",s32Ret);
        HDMI_VFREE(pu8Buf);
        return HI_FAILURE;
    }
    s32Ret = DRV_HDMI_KeyLoad(pstHdmiDev,&stLoadKey,HI_FALSE);
    HDMI_DBG_PRINT("\n loadkey size %u bytes %s! \n\n",
                    stLoadKey.u32KeyLength,
                    s32Ret==HI_SUCCESS ? STR_SUCC : STR_FAIL);

    HDMI_VFREE(pu8Buf);
#if defined (HDMI_SUPPORT_LOGIC_HISIV100)
    if (HI_SUCCESS!=HAL_HDMI_Hdcp14LoadKey(pstCmdArg->enHdmiId))
    {
        HDMI_DBG_PRINT("loadkey fail!\n");
        goto usage_error;
    }
    else
    {
        HDMI_DBG_PRINT("loadkey success!\n");
    }
#endif
    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo loadkey argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: a keyfile path string.\n");
    HDMI_DBG_PRINT("[example]: echo loadkey /mnt/stream/key/EncryptedKey_332bytes.bin > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugLoadsrm(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32              s32Ret = HI_FAILURE;
    PFILE               pFile = HI_NULL;
    HDMI_SRM_S          stLoadSrm ;
    HI_U8               *pu8Buf = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    HDMI_MEMSET(&stLoadSrm,0,sizeof(stLoadSrm));
    pu8Buf = (HI_U8 *)HDMI_VMALLOC(DEBUG_MAX_SRM_G1_SIZE);
    DEBUG_NULL_CHK(pu8Buf);
    HDMI_MEMSET(pu8Buf,0,DEBUG_MAX_SRM_G1_SIZE);

    pFile = Debugfopen(pstCmdArg->pcArgv[1],O_RDWR ,0);
    if (pFile == HI_NULL)
    {
        HDMI_DBG_ERR("errro open file %s\n",pstCmdArg->pcArgv[1]);
        HDMI_VFREE(pu8Buf);
        return HI_FAILURE;
    }
    s32Ret = Debugfread((HI_CHAR *)pu8Buf,DEBUG_MAX_SRM_G1_SIZE-1,pFile);
    Debugfclose(pFile);
    if ((s32Ret > 0) && (s32Ret < DEBUG_MAX_SRM_G1_SIZE))
    {
        stLoadSrm.u32Length = s32Ret;
        stLoadSrm.pu8SrmAddr= pu8Buf;
    }
    else
    {
        HDMI_DBG_ERR("read file len=%d \n",s32Ret);
        HDMI_VFREE(pu8Buf);
        return HI_FAILURE;
    }
    s32Ret = DRV_HDMI_SrmSet(stLoadSrm.pu8SrmAddr,stLoadSrm.u32Length,HI_FALSE);
    HDMI_DBG_PRINT("\n loadsrm size %u bytes %s! \n\n",
                    stLoadSrm.u32Length,
                    s32Ret==HI_SUCCESS ? STR_SUCC : STR_FAIL);

    HDMI_VFREE(pu8Buf);

    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo loadsrm argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: a srm file path string.\n");
    HDMI_DBG_PRINT("[example]: echo loadkey /mnt/stream/srm.bin > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugSrmInfo(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_U32          i = 0;
    HI_S32          s32Ret = HI_SUCCESS;
    SRM_INFO_S      *pstSrmInfo = HI_NULL;

    s32Ret = DRV_HDMI_SrmGet(&pstSrmInfo);

    if( pstSrmInfo && (HI_SUCCESS == s32Ret) )
    {
        HDMI_DBG_PRINT("-------------------------Revoction ID-------------------\n");
        for (i = 0; i < pstSrmInfo->unRevocInfo.bits.b10_NumOfDevices;i+=5)
        {
            HDMI_DBG_PRINT("NUM[%06u]: %02x %02x %02x %02x %02x \n",(i/5),
                pstSrmInfo->pu8HeadDeviceIds[0+i],
                pstSrmInfo->pu8HeadDeviceIds[1+i],
                pstSrmInfo->pu8HeadDeviceIds[2+i],
                pstSrmInfo->pu8HeadDeviceIds[3+i],
                pstSrmInfo->pu8HeadDeviceIds[4+i]);
        }
        HDMI_DBG_PRINT("-------------------------Header Parse-------------------\n");
        HDMI_DBG_PRINT("%-20s : 0x%x\n%-20s : 0x%x\n%-20s : 0x%x\n%-20s : 0x%x\n%-20s : 0x%x\n"
                    "%-20s : %u\n%-20s : 0x%x\n%-20s : 0x%x\n%-20s : %u\n%-20s : %u\n",
                "b04_SrmId",            pstSrmInfo->unHead1.bits.b04_SrmId,
                "b04_Hdcp2Indicator",   pstSrmInfo->unHead1.bits.b04_Hdcp2Indicator,
                "b08_Reserved",         pstSrmInfo->unHead1.bits.b08_Reserved,
                "b16_SrmVersion",       pstSrmInfo->unHead1.bits.b16_SrmVersion,

                "b08_SrmGenerationNum", pstSrmInfo->unHead2.bits.b08_SrmGenerationNum,
                "b24_Length",           pstSrmInfo->unHead2.bits.b24_Length,

                "b10_NumOfDevices",     pstSrmInfo->unRevocInfo.bits.b10_NumOfDevices,
                "b22_Reserved",         pstSrmInfo->unRevocInfo.bits.b22_Reserved,

                "bInit",                pstSrmInfo->bInit,
                "bValid",               pstSrmInfo->bValid);

    }
    else
    {
        HDMI_DBG_PRINT("info get fail!\n");
    }

    return s32Ret;

}


#endif


#ifdef HDMI_DEBUG
static HI_S32 DebugLogcat(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32                  s32Ret = HI_FAILURE;
    HDMI_DEVICE_S           *pstHdmiDev = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc < 2 || pstCmdArg->u32Argc > 3)
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    if (pstCmdArg->u32Argc==2 && IS_STR_EQUAL(pstCmdArg->pcArgv[1],"s"))
    {
        s32Ret = DRV_HDMI_LogCat(LOG_PRINT_TO_SCREEN, HI_NULL);
        HDMI_DBG_PRINT("\n logcat to screen %s! \n\n",
                                s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC);
    }
    else if (pstCmdArg->pcArgv[2]
            && (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2")  || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"f")))
    {
        s32Ret = DRV_HDMI_LogCat(LOG_PRINT_TO_FILE, pstCmdArg->pcArgv[2]);
        HDMI_DBG_PRINT("\n logcat to %s %s! \n\n",
                                pstCmdArg->pcArgv[2] ,
                                s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC);

    }
    else if (pstCmdArg->pcArgv[2]
             && (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"3") || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"a")))
    {
        s32Ret = DRV_HDMI_LogCat(LOG_PRINT_TO_ALL, pstCmdArg->pcArgv[2]);
        HDMI_DBG_PRINT("\n logcat to screen & %s %s! \n\n",
                                pstCmdArg->pcArgv[2] ,
                                s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC);
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo logcat argv1 [argv2] > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: print destination.\n");
    HDMI_DBG_PRINT("           0(s)\t--print to screen.\n");
    HDMI_DBG_PRINT("           1(f)\t--print to file.\n");
    HDMI_DBG_PRINT("           2(a)\t--print to both screen & file.\n");
    HDMI_DBG_PRINT("[argv2  ]: log output file path.optional,argv1 is 'f|a' needed.\n");
    HDMI_DBG_PRINT("[example]: echo logcat > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[example]: echo logcat f /mnt/stream/hdmilog/log20150710.txt > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugLogmask(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32                  s32Ret = HI_FAILURE;
    HDMI_DEVICE_S           *pstHdmiDev = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc < 2  )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0") || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"n"))
    {
        s32Ret = DRV_HDMI_LogSetMask(LOG_TYPE_FUNC_ALL);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1") || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"a"))
    {
        s32Ret = DRV_HDMI_LogSetMask(LOG_TYPE_FUNC_API);

    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2")  || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"h"))
    {
        s32Ret = DRV_HDMI_LogSetMask(LOG_TYPE_FUNC_HDCP);

    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"3") || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"e"))
    {
        s32Ret = DRV_HDMI_LogSetMask(LOG_TYPE_FUNC_EDID);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"4") || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"c"))
    {
        s32Ret = DRV_HDMI_LogSetMask(LOG_TYPE_FUNC_CEC);
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    HDMI_DBG_PRINT("\n logmask set %s %s! \n\n",pstCmdArg->pcArgv[1],s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC);

    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo logmask argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0(n)\t--none.\n");
    HDMI_DBG_PRINT("           1(a)\t--api.\n");
    HDMI_DBG_PRINT("           2(h)\t--hdcp.\n");
    HDMI_DBG_PRINT("           3(e)\t--edid.\n");
    HDMI_DBG_PRINT("           4(c)\t--cec .\n");
    HDMI_DBG_PRINT("[example]: echo logmode 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

static HI_S32 DebugLoglevel(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_S32                  s32Ret = HI_FAILURE;
    HDMI_DEVICE_S           *pstHdmiDev = HI_NULL;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc < 2 )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0") || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"i"))
    {
        s32Ret = DRV_HDMI_LogSetLevel(LOG_LEVEL_INFO);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1") || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"w"))
    {
        s32Ret = DRV_HDMI_LogSetLevel(LOG_LEVEL_WARN);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2")  || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"e"))
    {
        s32Ret = DRV_HDMI_LogSetLevel(LOG_LEVEL_ERROR);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"3") || IS_STR_EQUAL(pstCmdArg->pcArgv[1],"f"))
    {
        s32Ret = DRV_HDMI_LogSetLevel(LOG_LEVEL_FATAL);
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    HDMI_DBG_PRINT("\n loglevel set %s %s! \n\n",pstCmdArg->pcArgv[1],s32Ret!=HI_SUCCESS ? STR_FAIL : STR_SUCC);

    return s32Ret;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo loglevel argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT("[argv1  ]: 0(i)\t--info.\n");
    HDMI_DBG_PRINT("           1(w)\t--warn.\n");
    HDMI_DBG_PRINT("           2(e)\t--error.\n");
    HDMI_DBG_PRINT("           3(f)\t--fatal.\n");
    HDMI_DBG_PRINT("[example]: echo loglevel 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;
}

#endif /* #ifdef HDMI_DEBUG */

#if defined (HDMI_SUPPORT_LOGIC_HISIV100)

static HI_S32 DebugProc(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HDMI_DEVICE_ID_E    enHdmiId = HDMI_DEVICE_ID0;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    enHdmiId = pstCmdArg->enHdmiId;
    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1] == HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0") || (HI_SUCCESS == strncmp(pstCmdArg->pcArgv[1], "mach", 4)))
    {
       HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_PROC_MACH,&enHdmiId);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1")|| (HI_SUCCESS == strncmp(pstCmdArg->pcArgv[1], "scdc", 4)))
    {
       HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_PROC_SCDC,&enHdmiId);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"2") || (HI_SUCCESS == strncmp(pstCmdArg->pcArgv[1], "hdcp14", 6)))
    {
       HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_PROC_HDCP14,&enHdmiId);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"3") || (HI_SUCCESS == strncmp(pstCmdArg->pcArgv[1], "hdcp22", 6)))
    {
       HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_PROC_HDCP22,&enHdmiId);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"4") || (HI_SUCCESS == strncmp(pstCmdArg->pcArgv[1], "ddc", 3)))
    {
       HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_PROC_DDC,&enHdmiId);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"5") || (HI_SUCCESS == strncmp(pstCmdArg->pcArgv[1], "cectx", 5)))
    {
       HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_PROC_CECTX,&enHdmiId);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"6") || (HI_SUCCESS == strncmp(pstCmdArg->pcArgv[1], "cecrx", 5)))
    {
       HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_PROC_CECRX,&enHdmiId);
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo proc argv1 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT( "[argv1  ]: 0\t--mach.\n"
                    "           1\t--scdc.\n"
                    "           2\t--hdcp14.\n"
                    "           3\t--hdcp22.\n"
                    "           4\t--ddc.\n"
                    "           5\t--cectx.\n"
                    "           6\t--cecrx.\n");
    HDMI_DBG_PRINT("[example]: echo proc 1 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;

}

static HI_BOOL DebugZeroDetect(HI_U32 u32Argv)
{
    HI_BOOL bZero = HI_FALSE;

    bZero = (u32Argv > 0) ? HI_TRUE : HI_FALSE;

    return bZero;
}

static HI_S32 DebugVdbg(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_CHAR             *pcTmp = HI_NULL;
    HI_U32              i = 0;
    HI_U32              u32Argv2 = 0;
    HDMI_DEVICE_S       *pstHdmiDev = HI_NULL;
    HDMI_DBG_VIDEO_S    stDbgVideo = {0};

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);
    DEBUG_NULL_CHK(pstHdmiDev->pstHdmiHal);

    if (pstCmdArg->u32Argc != 3  || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    if (pstCmdArg->pcArgv[2]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }
    u32Argv2 = DebugStrToU32(pstCmdArg->pcArgv[2], &pcTmp, HDMI_DEBUG_BASE_DEC);

    HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal, HDMI_DEBUG_CMD_DBG_VIDEO_GET, &stDbgVideo);

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "0"))
    {
        stDbgVideo.bPatternEnable = DebugZeroDetect(u32Argv2);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "1"))
    {
        stDbgVideo.enPixFormat = (HDMI_DBG_PIX_FMT_E)u32Argv2;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "2"))
    {
        stDbgVideo.bSolidPattern = DebugZeroDetect(u32Argv2);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "3"))
    {
        stDbgVideo.bColorBar = DebugZeroDetect(u32Argv2);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "4"))
    {
        stDbgVideo.bSquarePattern = DebugZeroDetect(u32Argv2);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "5"))
    {
        stDbgVideo.bYMask = DebugZeroDetect(u32Argv2);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "6"))
    {
        stDbgVideo.bCbMask = DebugZeroDetect(u32Argv2);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "7"))
    {
        stDbgVideo.bCrMask = DebugZeroDetect(u32Argv2);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "8"))
    {
        stDbgVideo.bYCbCrSpace = DebugZeroDetect(u32Argv2);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"9"))
    {
        stDbgVideo.bTimmingEnable = DebugZeroDetect(u32Argv2);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "10"))
    {
        stDbgVideo.bSelfDefineTimming = DebugZeroDetect(u32Argv2);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "11"))
    {
        stDbgVideo.bHsyncPolarlity =  DebugZeroDetect(u32Argv2);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "12"))
    {
        stDbgVideo.bVsyncPolarlity = DebugZeroDetect(u32Argv2);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "13"))
    {
        stDbgVideo.enTimming = (HDMI_DBG_TIMMING_E)u32Argv2;
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1], "14"))
    {
        if(u32Argv2)
        {
            stDbgVideo.bTimmingEnable   = HI_TRUE;
            stDbgVideo.enTimming        = HDMI_DBG_TIMMING_720P_60;
            stDbgVideo.bPatternEnable   = HI_TRUE;
            stDbgVideo.bYCbCrSpace      = HI_TRUE;
            stDbgVideo.bColorBar        = HI_TRUE;
        }
        else
        {
            stDbgVideo.bTimmingEnable   = HI_FALSE;
            stDbgVideo.enTimming        = HDMI_DBG_TIMMING_480P;
            stDbgVideo.bPatternEnable   = HI_FALSE;
            stDbgVideo.bYCbCrSpace      = HI_FALSE;
            stDbgVideo.bColorBar        = HI_FALSE;
        }
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    HDMI_HAL_CALL(HAL_HDMI_Debug, pstHdmiDev->pstHdmiHal,HDMI_DEBUG_CMD_DBG_VIDEO_SET,&stDbgVideo);
    HDMI_DBG_PRINT("\tsettming stauts success:\n");
    HDMI_DBG_PRINT("\t 0.%-18s = %d\n","bPatternEnable", stDbgVideo.bPatternEnable);
    HDMI_DBG_PRINT("\t 1.%-18s = %d\n","enPixFormat",    stDbgVideo.enPixFormat);
    HDMI_DBG_PRINT("\t 2.%-18s = %d\n","bSolidPattern",  stDbgVideo.bSolidPattern);
    HDMI_DBG_PRINT("\t 3.%-18s = %d\n","bColorBar",      stDbgVideo.bColorBar);
    HDMI_DBG_PRINT("\t 4.%-18s = %d\n","bSquarePattern", stDbgVideo.bSquarePattern);
    HDMI_DBG_PRINT("\t 5.%-18s = %d\n","bYMask",         stDbgVideo.bYMask);
    HDMI_DBG_PRINT("\t 6.%-18s = %d\n","bCbMask",        stDbgVideo.bCbMask);
    HDMI_DBG_PRINT("\t 7.%-18s = %d\n","bCrMask",        stDbgVideo.bCrMask);
    HDMI_DBG_PRINT("\t 8.%-18s = %d\n","bYCbCrSpace",    stDbgVideo.bYCbCrSpace);
    HDMI_DBG_PRINT("\t 9.%-18s = %d\n","bTimmingEnable", stDbgVideo.bTimmingEnable);
    HDMI_DBG_PRINT("\t10.%-18s = %d\n","bSelfDefineTimming",stDbgVideo.bSelfDefineTimming);
    HDMI_DBG_PRINT("\t11.%-18s = %d\n","bHsyncPolarlity",stDbgVideo.bHsyncPolarlity);
    HDMI_DBG_PRINT("\t12.%-18s = %d\n","bVsyncPolarlity",stDbgVideo.bVsyncPolarlity);
    HDMI_DBG_PRINT("\t13.%-18s = %d(%s)\n","enTimming",  stDbgVideo.enTimming,STR_PRE_TIMMING(stDbgVideo.enTimming));
    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo vdbg arvg1 argv2 > /proc/msp/hdmi0 \n");
    HDMI_DBG_PRINT( "[argv1  argv2]:\n"
                    "\t 0\t--bPatternEnable.\t[0,1]:OFF ON\n"
                    "\t 1\t--enPixFormat.\t\t[0,2]:444 YUV422 YUV420\n"
                    "\t 2\t--bSolidPattern.\t[0,1]:OFF ON\n"
                    "\t 3\t--bColorBar.\t\t[0,1]:OFF ON\n"
                    "\t 4\t--bSquarePattern.\t[0,1]:OFF ON\n"
                    "\t 5\t--bYMask.\t\t[0,1]:OFF ON\n");

    HDMI_DBG_PRINT( "\t 6\t--bCbMask.\t\t[0,1]:OFF ON\n"
                    "\t 7\t--bCrMask.\t\t[0,1]:OFF ON\n"
                    "\t 8\t--bYCbCrSpace.\t\t[0,1]:OFF ON\n"
                    "\t 9\t--bTimmingEnable.\t[0,1]:OFF ON\n"
                    "\t10\t--bSelfDefineTimming.\t[0,1]:OFF ON\n"
                    "\t11\t--bHsyncPolarlity.\t[0,1]:P N\n"
                    "\t12\t--bVsyncPolarlity.\t[0,1]:P N\n"
                    "\t13\t--enTimming.\t\t[0,18]\n");
                    for (i=0;i<19;i++)
                    {
                        HDMI_DBG_PRINT("\t\t      %02d --%s\n",i,STR_PRE_TIMMING(i));
                    }
    HDMI_DBG_PRINT( "\t14\t--720p50 YUV444 colorbar enable.\t[0,1] OFF ON\n");
    HDMI_DBG_PRINT("[example]: echo vdbg 1 0 > /proc/msp/hdmi0 \n");

    return HI_FAILURE;

}

#endif /* #if defined (HDMI_SUPPORT_LOGIC_HISIV100)*/

static HI_S32 DebugNullpacket(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HDMI_DEVICE_S   *pstHdmiDev = HI_NULL;
    HI_BOOL         bEnable = HI_FALSE;

    DEBUG_NULL_CHK(pstCmdArg);
    pstHdmiDev = GetHdmiDevice(pstCmdArg->enHdmiId);
    DEBUG_NULL_CHK(pstHdmiDev);

    if (pstCmdArg->u32Argc != 2 || pstCmdArg->pcArgv[1]==HI_NULL )
    {
        HDMI_DBG_ERR("error argcs!\n");
        goto usage_error;
    }

    if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"0"))
    {
        bEnable = HI_FALSE;
        DRV_HDMI_InfoFrameEnableSet(&pstHdmiDev->stInfoFrame, HDMI_INFOFRAME_TYPE_NULL, HI_FALSE);
        HDMI_DBG_PRINT("\n null packet is disable %s! \n\n",STR_SUCC);
    }
    else if (IS_STR_EQUAL(pstCmdArg->pcArgv[1],"1"))
    {
        bEnable = HI_TRUE;
        DRV_HDMI_InfoFrameEnableSet(&pstHdmiDev->stInfoFrame, HDMI_INFOFRAME_TYPE_NULL, HI_TRUE);
        HDMI_DBG_PRINT("\n null packet is enable %s! \n\n",STR_SUCC);
    }
    else
    {
        HDMI_DBG_ERR("error argvs!\n");
        goto usage_error;
    }

    return HI_SUCCESS;

usage_error:
    HDMI_DBG_PRINT("[Usage  ]: echo nullpacket argv1 > /proc/msp/hdmi0\n");
    HDMI_DBG_PRINT("[argv1  ]: 0\t--nullpacket off.\n"
                   "           1\t--nullpacket on.\n");
    HDMI_DBG_PRINT("[example]: echo nullpacket 1 > /proc/msp/hdmi0\n");

    return HI_FAILURE;
}


const static HDMI_DEBUG_CMD_INFO_S s_stCmdTable[] = {
    /***name**** short name *** func ************** help info **********************/
    {"help"     ,   "h",    DebugPrintHelp      ,  "print these help info."                             },
    {"thread"   ,   "t",    DebugThread         ,  "thread status set on/off."                          },
    {"oe"       ,   "o",    DebugOe             ,  "phyoutput enable(oe) set on/off."                   },
    {"event"    ,   "e" ,   DebugEvent          ,  "hardware event [16,25] simulate."                   },
    {"infoframe",   "i",    DebugInfoframe      ,  "infoframe type set avi/audio/vs/gdb."               },
    {"edid"     ,   "ed",   DebugEdid           ,  "edid raw data load."                                },
    {"avmute"   ,   "a",    DebugAvmute         ,  "audio & video mute set on/off."                     },
    {"amute"    ,   "am",   DebugAmute          ,  "audio mute set on/off."                             },
    {"vmute"    ,   "vm",   DebugVmute          ,  "video mute set on/off."                             },
    {"mutedelay",   "md",   DebugMutedelay      ,  "avmute delay time(ms) [0,100000] set."              },
    {"fmtdelay" ,   "fd",   DebugFmtdelay       ,  "format setting delay time(ms) [0,100000] set."      },
    {"fmtforce" ,   "ff",   DebugFmtForce       ,  "format change mode set kernel/user."                },
    {"muteforce",   "mf",   DebugMuteforce      ,  "avmute change mode set kernel/user."                },
    {"cbar"     ,   "c",    DebugCbar           ,  "colorbar set on/off."                               },
    {"scdc"     ,   "sc",   DebugScdc           ,  "scdc set on/off."                                   },
    {"hdmimode" ,   "m" ,   DebugHdmimode       ,  "hdmi tmds mode set dvi/1.4/2.0."                    },
    {"outclrspace" ,"oc",   DebugOutclrspace    ,  "output colorspace mode set rgb/yuv422/yuv444/yuv420."},
    {"inclrspace" , "ic",   DebugInclrspace     ,  "input colorspace mode set rgb/yuv422/yuv444/yuv420."},
    {"deepclr"  ,   "d",    DebugDeepclr        ,  "output color depth  set 08/10/12bit."               },
    {"3dmode"   ,   "3d",   Debug3dmode         ,  "3d mode set fpk/sbs/tab."                           },
    {"pixrepet" ,   "p",    DebugPixrepet       ,  "pixel repetition [1,10] times set."                 },
    {"soundintf",   "si",   DebugSoundintf      ,  "audio sound interface tpye set i2s/spdif/hbra."     },
    {"samplefs" ,   "sf",   DebugSamplefs       ,  "audio sampling frequency set."                      },
    {"channel" ,    "ch",   DebugChannel        ,  "audio channels set 2/8."                            },
    {"sampledepth", "sd",   DebugSampledepth    ,  "audio sampling depth set."                          },
    {"dither"   ,   "di",   DebugDither         ,  "dither set on/off."                                 },
    {"swrst"    ,   "s",    DebugSwrst          ,  "software reset."                                    },
    {"suspend"  ,   "sus",  DebugSuspend        ,  "soft suspend mode."                                 },
#if defined (HDMI_SUPPORT_LOGIC_SILICON)
    {"rgb2yuv"  ,   "r",    DebugRgb2yuv        ,  "rgb to yuv444 set on/off."                          },
    {"yuv2rgb"  ,   "y",    DebugYuv2rgb        ,  "yuv444 to rgb set on/off."                          },
    {"ddc"      ,   "dd",   DebugDdc            ,  "ddc frequency set in range [0,11]."                 },
    {"bypass"   ,   "by",   DebugBypass         ,  "bypass set on/off."                                 },
    {"phypara"  ,   "ph",   DebugPhypara        ,  "phy parameter config."                              },
    {"dump"     ,   "dp",   DebugDump           ,  "dump a number of registers."                         },
    {"avpath"   ,   "pt",   DebugAvpath         ,  "reset hdmi hw,audio path & video 1080p60 colorbar." },
#endif

    {"aut"      ,   "au",   DebugAuthenticate   ,  "authentication mode set on/off."                    },
    {"emi"      ,   "em",   DebugEmi            ,  "emi set on/off."                                    },
    {"cmd"      ,   "cmd",  DebugCmd            ,  "cmd set start/stop/hpd fillter/hpd event."                                          },
    {"debugdelay",  "dl",   DebugDelay          ,  "debug context delay set."                           },
#ifdef HDMI_CEC_SUPPORT
    {"cec"      ,   "ce",   DebugCec            ,  "cec set on/off."                                    },
#endif
#ifdef HDMI_HDCP_SUPPORT
    {"hdcp14"   ,   "h1",   DebugHdcp14         ,  "hdcp1.4 set on/off."                                },
    {"hdcp22"   ,   "h2",   DebugHdcp22         ,  "hdcp2.2 set on/off."                                },
    {"loadkey"  ,   "l",    DebugLoadkey        ,  "load a hdcp1.4 key file."                           },
    {"loadsrm"  ,   "ls",   DebugLoadsrm        ,  "load a srm file."                                   },
    {"srminfo"  ,   "sr",   DebugSrmInfo        ,  "proc srm infomation."                               },
#endif
#ifdef HDMI_DEBUG
    {"logcat"   ,   "lc",   DebugLogcat         ,  "log cat set screen/file/all."                       },
    {"logmask"  ,   "lk",   DebugLogmask        ,  "log mask set none/api/edid/hdcp/cec."               },
    {"loglevel" ,   "ll",   DebugLoglevel       ,  "log level set info/warn/error/fatal."               },
#endif
#ifdef HDMI_HDR_SUPPORT
    {"hdr"      ,   "hm",   DebugHdr            ,  "hdr debug info set."                                },
#endif

#if defined (HDMI_SUPPORT_LOGIC_HISIV100)
    {"proc",        "pr",   DebugProc           ,  "proc mach/ddc/hdcp14/hdcp22/cectx/cecrx/scdc."      },
    {"vdbg",        "vd",   DebugVdbg           ,  "debug test video format."                           },
#endif
    {"nullpacket",  "np",   DebugNullpacket     ,  "null packet enable/disable."                        },
};

static HI_S32 DebugPrintHelp(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_U32 i = 0;

    DEBUG_NULL_CHK(pstCmdArg);

    for (i=0 ; i < HDMI_ARRAY_SIZE(s_stCmdTable) ; i++)
    {
        if (s_stCmdTable[i].pCommentHelp && s_stCmdTable[i].pcName && s_stCmdTable[i].pcShortName)
        {
            HDMI_DBG_PRINT("    %02d. %-20s",i,s_stCmdTable[i].pcName);
            HDMI_DBG_PRINT("--[%-2s]%s\n",s_stCmdTable[i].pcShortName,s_stCmdTable[i].pCommentHelp);
        }
        else
        {
            HDMI_DBG_ERR("s_stCmdTable[%d].pCommentHelp or pcName is null!\n", i);
        }
    }

    HDMI_DBG_PRINT("\n");
    HDMI_DBG_PRINT("    You can use 'echo cmd argv... > /proc/msp/hdmi0' execute a debug command.\n"
                   "    You can use 'echo cmd > /proc/msp/hdmi0' for more details about every command.\n"
                   "    Here,'cmd' refers to NO./complete-name/short-name above.\n");
    return HI_SUCCESS;
}

static HI_S32 DebugCmdHandle(HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_U32          i = 0,u32CmdNum = 0;
    HI_CHAR         *pcStr = pstCmdArg->pcArgv[0];

    DEBUG_NULL_CHK(pstCmdArg);
    DEBUG_NULL_CHK(pcStr);

    if (pstCmdArg->u32Argc > 0)
    {
        u32CmdNum = DebugStrToU32(pcStr,&pcStr,HDMI_DEBUG_BASE_DEC);

        for (i=0 ; i < HDMI_ARRAY_SIZE(s_stCmdTable) ; i++)
        {
            if ( s_stCmdTable[i].pcName )
            {
                if( ((u32CmdNum == i) && (*pcStr == '\0') )
                   || IS_STR_EQUAL(s_stCmdTable[i].pcName,pstCmdArg->pcArgv[0])
                   || IS_STR_EQUAL(s_stCmdTable[i].pcShortName,pstCmdArg->pcArgv[0]) )
                {

                    if (s_stCmdTable[i].pfnCmdFunc)
                    {
                        if(s_stCmdTable[i].pfnCmdFunc(pstCmdArg))
                        {
                            //goto error_help;
                        }
                    }
                    else
                    {
                        HDMI_DBG_ERR("s_stCmdTable[%d].pfnCmdFunc null\n",i);
                        goto error_help;
                    }
                    break;
                }

            }
            else
            {
                HDMI_DBG_ERR("s_stCmdTable[%d].pcName null\n",i);
                goto error_help;
            }

        }
    }

    if ( i == HDMI_ARRAY_SIZE(s_stCmdTable) )
    {
        goto error_help;
    }

    return HI_SUCCESS;

error_help:
    DebugPrintHelp(pstCmdArg);

    return HI_FAILURE;
}

static HI_S32 DebugCmdLineParse(HI_CHAR *pcCmdStr,HI_U32 u32Len,
                                HDMI_DEBUG_CMD_ARG_S *pstCmdArg)
{
    HI_U32      i = 0;
    HI_U32      u32TmpArgc = 0;
    HI_CHAR     *pTmpStr = NULL;


    if (pcCmdStr == HI_NULL
        || pstCmdArg == HI_NULL
        || u32Len == 0
        || u32Len >= DEBUG_MAX_CMD_CHAR_NUM)
    {
        HDMI_DBG_ERR("invalid param!\n");
        return HI_FAILURE;
    }
    else
    {
        pTmpStr = pcCmdStr;
    }

    pstCmdArg->u32Argc = 0;
    for (i = 0; i < DEBUG_MAX_ARGV_NUM; i++)
    {
        pstCmdArg->pcArgv[i] = HI_NULL;
    }

    if ( (*pTmpStr != DEBUG_CHAR_SPACE) && (*pTmpStr != DEBUG_CHAR_TAB) )
    {
        pstCmdArg->pcArgv[u32TmpArgc] = pTmpStr;
        u32TmpArgc++;
        pTmpStr++;
    }

    for (i=0; i < u32Len; pTmpStr++,i++)
    {
        if ( (*pTmpStr == DEBUG_CHAR_SPACE ) || (*pTmpStr == DEBUG_CHAR_TAB)  )
        {
            *pTmpStr = '\0';

            if( (*(pTmpStr+1) != DEBUG_CHAR_SPACE) && (*(pTmpStr+1) != DEBUG_CHAR_TAB))
            {
                pstCmdArg->pcArgv[u32TmpArgc] = pTmpStr + 1;
                u32TmpArgc++;

                if (u32TmpArgc == 3 )
                {
                    pstCmdArg->u32RemainLen = u32Len - i;
                    //break;
                }

                if (u32TmpArgc >= DEBUG_MAX_ARGV_NUM)
                {
                    HDMI_DBG_PRINT(" too much argcs.max argc = %d\n",DEBUG_MAX_ARGV_NUM);
                    u32TmpArgc = DEBUG_MAX_ARGV_NUM;
                    break;
                }
            }

        }
    }

    pstCmdArg->u32Argc = u32TmpArgc;

    return HI_SUCCESS;
}


/********************** HDMI DEBUG public interface ************************************/

HI_S32 DRV_HDMI_DebugEdidRawRead(HDMI_EDID_UPDATE_MODE_E enMode,
                                            HI_U8 *pau8Data,
                                            HI_U32 u32Len)
{
    HDMI_DEBUG_EDID_S *pstDbgEdid = &s_stDebugEdid;

    if ( (HDMI_EDID_UPDATE_DEBUG != enMode)
        || (HI_FALSE == pstDbgEdid->bDataValid)
        || (HI_NULL == pau8Data)
        || (u32Len > HDMI_EDID_TOTAL_SIZE)    )
    {
        HDMI_ERR("Fail, bDataValid=%d !\n",pstDbgEdid->bDataValid);
        return HI_FAILURE;
    }

    HDMI_MEMCPY(pau8Data,pstDbgEdid->au8Data,pstDbgEdid->s32Len);

    return pstDbgEdid->s32Len;
}

HI_S32 DRV_HDMI_DebugSourceWrite(struct file *fp,
                                            const char __user *pcUserBuf,
                                            size_t ulCount,
                                            loff_t *pData)
{
    HI_S32                  s32Ret = HI_FAILURE;
    HI_U32                  u32Len = 0;
    HI_CHAR                 *pcTmpBuf = HI_NULL;
    HDMI_DEBUG_CMD_ARG_S    stCmdArg;
    struct seq_file         *p = HI_NULL;
    DRV_PROC_ITEM_S         *pProcItem = HI_NULL;

    DEBUG_NULL_CHK(fp);
    DEBUG_NULL_CHK(pcUserBuf);

    p = fp->private_data;
    DEBUG_NULL_CHK(p);

    pProcItem = p->private;
    DEBUG_NULL_CHK(pProcItem);

    HDMI_MEMSET(&stCmdArg, 0 , sizeof(HDMI_DEBUG_CMD_ARG_S));

    stCmdArg.enHdmiId   = (HDMI_DEVICE_ID_E)pProcItem->data;

    pcTmpBuf = (HI_CHAR *)HDMI_VMALLOC(DEBUG_MAX_CMD_CHAR_NUM);
    if (!pcTmpBuf)
    {
        HDMI_DBG_ERR("vmalloc fail!\n");
        return EFAULT;
    }
    HDMI_MEMSET(pcTmpBuf, '\0' , DEBUG_MAX_CMD_CHAR_NUM);

    if(ulCount >= DEBUG_MAX_CMD_CHAR_NUM)
    {
        HDMI_DBG_ERR("\n Echo chars too long. ulCount=%lu,max cnt=%u\n",ulCount,DEBUG_MAX_CMD_CHAR_NUM);
        goto error;
    }

    if(copy_from_user(pcTmpBuf,pcUserBuf,ulCount))
    {
        HDMI_DBG_ERR("\n copy from user failed. \n");
        goto error;
    }

    if (ulCount > 0)
    {
        /* end char '\n' set '\0' */
        pcTmpBuf[ulCount-1] = '\0';
        u32Len = ulCount - 1;
    }
    else
    {
        HDMI_DBG_ERR("ulCount=%d\n",ulCount);
        goto error;
    }

    s32Ret = DebugCmdLineParse(pcTmpBuf, u32Len, &stCmdArg);
    if (s32Ret != HI_SUCCESS)
    {
        HDMI_DBG_ERR("\n Cmd Parse fail! \n");
        goto error;
    }

    s32Ret = DebugCmdHandle(&stCmdArg);
    if (s32Ret != HI_SUCCESS)
    {
        HDMI_DBG_ERR("\n Cmd handle error \n");
        goto error;
    }
    HDMI_VFREE(pcTmpBuf);
    return ulCount;

error:
    HDMI_VFREE(pcTmpBuf);
    return -EFAULT;

}





