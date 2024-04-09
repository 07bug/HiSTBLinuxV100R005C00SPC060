#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <sys/time.h>
#include <math.h>

#include "hi_unf_common.h"
#include "hi_unf_avplay.h"
#include "hi_unf_sound.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_ecs.h"
#include "hi_unf_demux.h"
#include "HA.AUDIO.MP3.decode.h"
#include "hi_unf_ecs.h"
#include "hi_adp.h"
#include "hi_adp_hdmi.h"
#include "hi_adp_boardcfg.h"
#include "hi_adp_mpi.h"
#include "hi_adp_tuner.h"
#include "hi_unf_frontend.h"

#ifdef  CONFIG_SUPPORT_CA_RELEASE
#define HI_TUNER_ERR(format, arg...)
#define HI_TUNER_INFO(format, arg...)
#define HI_TUNER_WARN(format, arg...)
#else
#define HI_TUNER_ERR(format, arg...)    printf( "[ERR]: %s,%d: " format , __FUNCTION__, __LINE__, ## arg)
#define HI_TUNER_INFO(format, arg...)   printf( format , ## arg)
#define HI_TUNER_WARN(format, arg...)   printf( "[WARNING]: %s,%d: " format , __FUNCTION__, __LINE__, ## arg)
#endif

char *asignalTable[] = {"CAB","SAT","DVB-T","DVB-T2","ISDB-T","ATSC-T","DTMB","J83B"};


HI_UNF_DEMOD_DEV_TYPE_E S_DEMOD_TYPE = HI_UNF_DEMOD_DEV_TYPE_3130I;
typedef HI_VOID (*Test_Func_Proc)(char* args);
typedef struct stTEST_FUNC_S
{
    HI_CHAR*         name;
    Test_Func_Proc   proc;
} TEST_FUNC_S;

typedef struct stCMD_HELP_S
{
    HI_CHAR         name[30];
    HI_CHAR         help_info[3000];
} CMD_HELP_S;

typedef struct stT2MultiGroup
{
    HI_U32 u8GrpId;
    HI_U32 u8CommId;
    HI_U32 u8Combination;
}T2MultiGroup;

CMD_HELP_S g_cmdhelp[] =
{
    {"help", "help: show help menu, only input 'help' will print command list,\n"
                    "\t 'help cmd' will print the help infomation of the cmd.\n"},
    {"setport", "setport 0(tuner port number,max value is 3).\n"
                  "\t 0 is the first tuner.\n"
                  "\t 1 is the second tuner.\n"
                  "\t 2 is the third tuner.\n"
                  "\t 3 is the fourth tuner.\n"},
    {"setchnl", "setchnl 3840 27500000 0 (freqency/symbolrate/polar),\n"
                    "\t freqency unit MHz for cable and satellite, KHz for terrestrial. If test DVB S/S2, you should input downlink frequency here,\n"
                    "\t symbolrate unit baud for satellite,\n"
                    "\t polar 0:Horizontal 1:Vertical 2:Left-hand circular 3:Right-hand circular.\n"},
    {"play", "play [Program_Num]: set program number. The default value is 1.\n"},
    {"getber", "getber: get ber\n"},
    {"getsignalinfo", "getsignalinfo: get detailed infomation of current locked signal.[FOR satellite and terrestrial signal].\n"},
    {"getoffset", "getoffset : getfreq getsyb. \n"},

#if ((HI_TUNER_SIGNAL_TYPE == 2) || (HI_TUNER1_SIGNAL_TYPE == 2))
    {"setlnbpower", "setlnbpower 0: set LNB power.[FOR DVB-S/S2]\n"
                   "\t 0 Power off,  1 Power auto(13V/18V),  2 Enhanced(14V/19V).\n"},
    {"setlnb", "setlnb 1 5150 5750 0: set LNB band and Low/High Local Oscillator.[FOR DVB-S/S2]\n"
                   "\t Param1: LNB type:0 single LO, 1 dual LO.\n"
                   "\t Param2: LNB low LO: MHz, e.g.5150.\n"
                   "\t Param3: LNB low LO: MHz, e.g.5750.\n"
                   "\t Param4: LNB band:0 C, 1 Ku.\n"},
    {"getvcm", "getvcm \n"
                   "\t when signal mode is acm/vcm/multi stream,\n"
                   "\t print ISI ID of each stream.\n"},
    {"setvcm", "setvcm 0(ISI ID):set ISI ID \n"
                   "\t when signal mode is acm/vcm/multi stream,\n"
                   "\t ISI ID can be getted from 'getvcm' command\n"},
    {"setscram", "setscram 262140(physical layer scrambling code).\n"
                  "\t the scrambling code can be find out from website,0 is the default value.\n"},
    {"blindscan", "blindscan 0 [0] [0] [950000] [2150000]: Blind scan. [FOR DVB-S/S2]\n"
                  "\t Param1: blind scan type: 0 Auto, 1 Manual.\n"
                  "\t Param2: LNB Polarization: 0 H, 1 V. Only for manual type.\n"
                  "\t Param3: LNB 22K:0 Off, 1 On. Only for manual type.\n"
                  "\t Param4: Start frequency. Only for manual type.\n"
                  "\t Param5: Stop frequency. Only for manual type.\n"},
    {"bsstop", "bsstop: Stop blind scan. [FOR DVB-S/S2]\n"},
    {"cs", "cs [0] [0]: sample data. [FOR HI3136]\n"
           "\t Param1: data source: 0 ADC, 1 EQU.\n"
           "\t Param2: data length: can be 512, 1024, 2048.\n"},
    #ifdef DISEQC_SUPPORT
    {"switch", "switch 0 0 [0] [0]: Switch test. [FOR DVB-S/S2]\n"
                  "\t Param1: Switch type:0 0/12V, 1 Tone burst, 2 22K, 3 DiSEqC 1.0, 4 DiSEqC 1.1, 5 Reset, 6 Standby, 7 WakeUp.\n"
                  "\t Param2: Switch port:0 None, 1-16.\n"
                  "\t Param3: LNB Polarization: 0 H, 1 V.\n"
                  "\t Param4: LNB 22K:0 Off, 1 On.\n"},
    {"motor", "motor 0 [0]: DiSEqC motor test. [FOR DVB-S/S2]\n"
                  "\t Param1: Control type:0 StorePos, 1 GotoPos, 2 SetLimit, 3 Move, 4 Stop, 5 USALS, 6 Recalculate, 7 GotoAng.\n"
                  "\t StorePos: Param2:position(0-63).\n"
                  "\t GotoPos: Param2:position(0-63).\n"
                  "\t SetLimit: Param2:limit type(0 off, 1 east, 2 west).\n"
                  "\t Move: Param2:move direction(0 east 1 west ), Param3:move type(0 one step, 1 two step, ..., 9 nine step, 10 continus).\n"
                  "\t USALS: Param2:local longitude(0-3600), Param3:local latitude(0-1800), Param4:satellite longitude(0-3600).\n"
                  "\t Recalculate: Param2/Param3/Param4: parameter1/2/3 for recalculate.\n"
                  "\t GotoAng: Param2:angle.\n"},
    {"unic", "unic 0(function index):select unicable function.[FOR DVB-S/S2]\n"
                  "\t 0: start unicable1 user bands scanning.\n"
                  "\t 1: exit from unicable1 user bands scanning.\n"},
    #endif

#endif

    {"setplpid",    "select the plp id.[FOR DVB-T/T2]\n"},
    {"ant",         "ant 1: set Antena power on.[FOR DVB-T/T2]\n"},
    {"select",      "select 0: select inside tuner or outside\n"},

    /*{"settype", "settype 0: set tuner type. \n"
                   "\t 0  cd1616,  1  tdae3,  2  mt2081,  3  tdcc,   4  tmx7070x,\n"
                   "\t 5  tda18250, 6  tda18250b 7  mxl203, 8  r820c\n"},*/
    //{"setqam", "setqam  64: set qam type , 64 means 64qam etc.\n"},

    {"start", "start  500: lock 500 times --->time_file\n"},
    //{"setmode","setmode j83b/j83ac:change mode to j83b or j83ac\n"},

    {"exit", "exit    : exit the sample\n"}
};

#define MAX_CMD_BUFFER_LEN 256
#define UDP_STR_SPLIT ' '
#define TEST_ARGS_SPLIT " "
#define HI_RESULT_SUCCESS "SUCCESS"
#define HI_RESULT_FAIL "FAIL"
#define DEFAULT_PORT 1234
#define TUNER_NUM 5
#define HI_UNUSED(x) ((x)=(x))

static HI_S32 s_s32TunerPort = 0;
/*static HI_U32 s_u32TunerFreq = 403000;*/
/*static HI_U32 s_u32ErrorNum;*/
/*static HI_FLOAT s_fMskBer = 0.0014;*/
/*static HI_U8 s_au8MskTmp[64];*/
static HI_U32 s_u32CurrentQamType;

/*save results, then send client*/
char s_acTestResult[MAX_CMD_BUFFER_LEN];

static HI_UNF_TUNER_CONNECT_PARA_S  s_stConnectPara[TUNER_NUM];

static PMT_COMPACT_TBL *s_ProgTbl[TUNER_NUM] = {HI_NULL};

static HI_UNF_ENC_FMT_E   s_enDefaultFmt = HI_UNF_ENC_FMT_1080i_50;

HI_HANDLE phWin;
HI_HANDLE hAvplay;

HI_HANDLE hTrack;

FILE *fp = NULL;
static HI_S32 s_s32LoopNum = 0;

static HI_S32 s_s32FailTime =0;
static HI_S32 s_s32Out1Time = 0;
static HI_S32 s_s32OutFailTime = 0;
static HI_S32 s_s32Time = 0;



HI_U32 getcurtime()
{
    struct timeval tv;
    gettimeofday(&tv, HI_NULL );
    return (((HI_U32)tv.tv_sec)*1000 + ((HI_U32)tv.tv_usec)/1000);
}

HI_VOID set_pin_mux(HI_UNF_TUNER_ATTR_S stTunerAttr)
{
    HI_U32 *pu32MUXAddr = NULL;

    HI_UNUSED(pu32MUXAddr);

#if defined (CHIP_TYPE_hi3716cv200) || defined (CHIP_TYPE_hi3716mv400)
    #if (HI_TUNER_SIGNAL_TYPE == 2 || HI_TUNER_SIGNAL_TYPE == 4)
    pu32MUXAddr = (HI_U32 *)HI_MEM_Map(0xf8a21000, 0x1000);
    if (NULL == pu32MUXAddr)
    {
        return;
    }

    //config reset gpio output
    *(pu32MUXAddr + 0x190/4) = 0;

    //config i2c scl/sda multiplex
    *(pu32MUXAddr + 0x194/4) = 2;
    *(pu32MUXAddr + 0x198/4) = 2;

    //config TS multiplex
    *(pu32MUXAddr + 0x100/4) = 1;
    *(pu32MUXAddr + 0x104/4) = 1;
    *(pu32MUXAddr + 0x108/4) = 1;
    *(pu32MUXAddr + 0x10c/4) = 1;
    *(pu32MUXAddr + 0x110/4) = 1;
    *(pu32MUXAddr + 0x114/4) = 1;
    *(pu32MUXAddr + 0x118/4) = 1;
    *(pu32MUXAddr + 0x11c/4) = 1;
    *(pu32MUXAddr + 0x120/4) = 1;
    *(pu32MUXAddr + 0x124/4) = 1;
    *(pu32MUXAddr + 0x128/4) = 1;
    #endif
#endif
#if defined (CHIP_TYPE_hi3796mv200)
    printf("96mv200\n");
    pu32MUXAddr = (HI_U32 *)HI_MEM_Map(0xf8a21000, 0x1000);
    if (NULL == pu32MUXAddr)
    {
        return;
    }
    if (HI_DEMOD_TYPE == HI_UNF_DEMOD_DEV_TYPE_MXL541)
    {
        //H24 I2C2_SCL IOSHARE69
        *(pu32MUXAddr + 0x114/4) &= ~(0x7<<0);
        *(pu32MUXAddr + 0x114/4) |= 3;

        //H26 I2C2_SDA IOSHARE68
        *(pu32MUXAddr + 0x110/4) &= ~(0x7<<0);
        *(pu32MUXAddr + 0x110/4) |= 3;

        //J24 GPIO9-0  IOSHARE61
        *(pu32MUXAddr + 0x0F4/4) &= ~(0x7<<0);

        //G24 TSI0_D0  IOSHARE67
        *(pu32MUXAddr + 0x10C/4) &= ~(0x7<<0);
        *(pu32MUXAddr + 0x10C/4) |= 1;

        //G25 TSI0_CLK IOSHARE66
        *(pu32MUXAddr + 0x108/4) &= ~(0x7<<0);
        *(pu32MUXAddr + 0x108/4) |= 2;

        //H23 TSI1_D0  IOSHARE65
        *(pu32MUXAddr + 0x104/4) &= ~(0x7<<0);
        *(pu32MUXAddr + 0x104/4) |= 1;

        //H25 TSI1_CLK IOSHARE64
        *(pu32MUXAddr + 0x100/4) &= ~(0x7<<0);
        *(pu32MUXAddr + 0x100/4) |= 2;

        //J25 TSI2_CLK IOSHARE63
        *(pu32MUXAddr + 0x0FC/4) &= ~(0x7<<0);
        *(pu32MUXAddr + 0x0FC/4) |= 1;

        //J26 TSI2_D0  IOSHARE62
        *(pu32MUXAddr + 0x0F8/4) &= ~(0x7<<0);
        *(pu32MUXAddr + 0x0F8/4) |= 1;

        //K25 TSI3_D0  IOSHARE60
        *(pu32MUXAddr + 0x0F0/4) &= ~(0x7<<0);
        *(pu32MUXAddr + 0x0F0/4) |= 1;

        //K24 TSI3_CLK IOSHARE59
        *(pu32MUXAddr + 0x0EC/4) &= ~(0x7<<0);
        *(pu32MUXAddr + 0x0EC/4) |= 2;
    }
#endif
#if defined (CHIP_TYPE_hi3716mv410)
    pu32MUXAddr = (HI_U32 *)HI_MEM_Map(0xf8a21000, 0x1000);
    if (NULL == pu32MUXAddr)
    {
        printf("HI_MEM_Map failed.\n");
        return;
    }

    //config reset gpio output
    *(pu32MUXAddr + 0x068/4) &= ~(0x7<<0);     //TSI0_D7  ioshare_26  demod_reset

    //config i2c scl/sda multiplex
    *(pu32MUXAddr + 0x078/4) &= ~(0x7<<0);     //TSI0_D3  ioshare_30  SCL
    *(pu32MUXAddr + 0x078/4) |= 3;
    *(pu32MUXAddr + 0x07c/4) &= ~(0x7<<0);     //TSI0_D2  ioshare_31  SDA
    *(pu32MUXAddr + 0x07c/4) |= 3;

    //config TS0 multiplex
    *(pu32MUXAddr + 0x084/4) &= ~(0x7<<0);     //TSI0_D0  ioshare_33  tsi0_d0
    *(pu32MUXAddr + 0x084/4) |= 1;

    *(pu32MUXAddr + 0x080/4) &= ~(0x7<<0);     //TSI0_D1  ioshare_32  tsi0_d1
    *(pu32MUXAddr + 0x080/4) |= 1;

    //config TS1 multiplex
    *(pu32MUXAddr + 0x06c/4) &= ~(0x7<<0);     //TSI0_D6  ioshare_27  tsi1_d0
    *(pu32MUXAddr + 0x06c/4) |= 3;
    *(pu32MUXAddr + 0x070/4) &= ~(0x7<<0);     //TSI0_D5  ioshare_28  tsi1_clk
    *(pu32MUXAddr + 0x070/4) |= 3;
    *(pu32MUXAddr + 0x074/4) &= ~(0x7<<0);     //TSI0_D4  ioshare_29  tsi1_valid
    *(pu32MUXAddr + 0x074/4) |= 3;

#endif

}

void set_demux()
{
    HI_U32 *pu32MUXAddr = NULL;
    pu32MUXAddr = pu32MUXAddr;

#if defined (CHIP_TYPE_hi3796mv200) /*&& (HI_TUNER_NUMBER == 4)*/
    //demux: draw high the valid.
    pu32MUXAddr = (HI_U32 *)HI_MEM_Map(0xf9c01000, 0x1000);
    if (NULL == pu32MUXAddr)
    {
        printf("HI_MEM_Map failed.\n");
        return;
    }
    *(pu32MUXAddr + 0x200/4) |= 0x8000;
    *(pu32MUXAddr + 0x300/4) |= 0x8000;
    *(pu32MUXAddr + 0x400/4) |= 0x8000;
    *(pu32MUXAddr + 0x500/4) |= 0x8000;
    *(pu32MUXAddr + 0x600/4) |= 0x8000;
    *(pu32MUXAddr + 0x700/4) |= 0x8000;
    *(pu32MUXAddr + 0x800/4) |= 0x8000;
#endif

#if defined (CHIP_TYPE_hi3798mv200)
    pu32MUXAddr = (HI_U32 *)HI_MEM_Map(0xf9c01000, 0x1000);
    if (NULL == pu32MUXAddr)
    {
        printf("HI_MEM_Map failed.\n");
        return;
    }
    *(pu32MUXAddr + 0x100/4) |= 0x8000;
    *(pu32MUXAddr + 0x200/4) |= 0x8000;
    *(pu32MUXAddr + 0x300/4) |= 0x8000;
    *(pu32MUXAddr + 0x400/4) |= 0x8000;
#endif
}
//#define BOARD_TYPE_hi3716mdmo3fvera

HI_S32 dev_init()
{
    HI_S32 s32Ret = 0;
    HI_UNF_TUNER_ATTR_S   stTunerAttr;
    HI_S32 i;

    set_pin_mux(stTunerAttr);

    /*sys init*/
    HI_SYS_Init();

    HIADP_MCE_Exit();

    /*sound init*/
    s32Ret = HIADP_Snd_Init();
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HIADP_Snd_Init failed.\n");
        return s32Ret;
    }

    /*display init*/
    s32Ret = HIADP_Disp_Init(s_enDefaultFmt);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HIADP_Disp_DeInit failed.\n");
        return s32Ret;
    }

    /*vo init*/
    s32Ret = HIADP_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);
    s32Ret |= HIADP_VO_CreatWin(HI_NULL,&phWin);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HIADP_VO_Init failed.\n");
        HIADP_VO_DeInit();
        return s32Ret;
    }

    s32Ret = HIADP_Tuner_Init();
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HIADP_Tuner_Init failed.\n");
        HIADP_VO_DeInit();
        HI_UNF_TUNER_DeInit();
        return s32Ret;
    }

    for (i = 0; i < HI_TUNER_NUMBER; i++)
    {
        HIADP_Tuner_GetConnectPara(i, &s_stConnectPara[i]);
    }

    s32Ret = HI_UNF_DMX_Init();
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_UNF_DMX_Init failed.\n");
        HIADP_Tuner_DeInit();
        return s32Ret;
    }

    if (HI_DEMOD_TYPE == HI_UNF_DEMOD_DEV_TYPE_MXL541)
    {
        set_demux();
    }

    s32Ret = HIADP_DMX_AttachTSPort(0, 0);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HIADP_DMX_AttachTSPort failed 0x%x\n", s32Ret);
        HI_UNF_DMX_DeInit();
        HIADP_Tuner_DeInit();
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 dev_deinit()
{
    HI_S32 s32Ret = 0;

    s32Ret = HI_UNF_DMX_DetachTSPort(0);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_UNF_DMX_DetachTSPort failed.\n");
        return s32Ret;
    }

    s32Ret = HI_UNF_DMX_DeInit();
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_UNF_DMX_AttachTSPort failed.\n");
        return s32Ret;
    }

    HIADP_Tuner_DeInit();

    s32Ret = HI_UNF_VO_DestroyWindow(phWin);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_UNF_VO_DestroyWindow failed.\n");
        return s32Ret;
    }

    s32Ret = HI_UNF_VO_DeInit();
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_UNF_VO_DeInit failed.\n");
        return s32Ret;
    }

    s32Ret = HI_UNF_DISP_Close(HI_UNF_DISPLAY0);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_UNF_DISP_Close failed.\n");
        return s32Ret;
    }

    s32Ret = HI_UNF_DISP_Close(HI_UNF_DISPLAY1);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_UNF_DISP_Close failed.\n");
        return s32Ret;
    }

    s32Ret = HI_UNF_DISP_Detach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_UNF_DISP_Detach failed.\n");
        return s32Ret;
    }

    s32Ret = HI_UNF_DISP_DeInit();
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_UNF_DISP_DeInit failed.\n");
        return s32Ret;
    }

    /*aaa hdmiDeInit();*/
    s32Ret = HI_UNF_SND_Close(HI_UNF_SND_0);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_UNF_SND_Close failed.\n");
        return s32Ret;
    }

    s32Ret = HI_UNF_SND_DeInit();
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_UNF_SND_DeInit failed.\n");
        return s32Ret;
    }

    HI_SYS_DeInit();

    return HI_SUCCESS;
}

HI_S32 avplay_Init()
{
    HI_S32 s32Ret = 0;
    HI_UNF_AVPLAY_ATTR_S        stAvplayAttr;
    HI_UNF_SYNC_ATTR_S          stSyncAttr;
    HI_UNF_VCODEC_ATTR_S        stVdecAttr;
    HI_UNF_AUDIOTRACK_ATTR_S    stTrackAttr;

    /*register lib*/
    s32Ret = HIADP_AVPlay_RegADecLib();
    s32Ret |= HI_UNF_AVPLAY_Init();
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_WARN("call HI_UNF_AVPLAY_Init failed.\n");
        dev_deinit();
    }

    s32Ret = HI_UNF_AVPLAY_GetDefaultConfig(&stAvplayAttr, HI_UNF_AVPLAY_STREAM_TYPE_TS);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_UNF_AVPLAY_GetDefaultConfig failed.\n");
        HI_UNF_AVPLAY_DeInit();
        dev_deinit();
        return s32Ret;
    }
    stAvplayAttr.stStreamAttr.u32VidBufSize = 0x300000;
    s32Ret = HI_UNF_AVPLAY_Create(&stAvplayAttr, &hAvplay);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_UNF_AVPLAY_Create failed.\n");
        HI_UNF_AVPLAY_DeInit();
        dev_deinit();
        return s32Ret;
    }

    s32Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        HI_UNF_AVPLAY_Destroy(hAvplay);
        HI_UNF_AVPLAY_DeInit();
        dev_deinit();
        return s32Ret;
    }

    s32Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        HI_UNF_AVPLAY_Destroy(hAvplay);
        dev_deinit();
        return s32Ret;
    }

    s32Ret = HI_UNF_VO_AttachWindow(phWin, hAvplay);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_UNF_VO_AttachWindow failed.\n");
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        HI_UNF_AVPLAY_Destroy(hAvplay);
        HI_UNF_AVPLAY_DeInit();
        dev_deinit();
        return s32Ret;
    }

    s32Ret = HI_UNF_VO_SetWindowEnable(phWin, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_UNF_VO_SetWindowEnable failed.\n");
        HI_UNF_VO_DetachWindow(phWin, hAvplay);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        HI_UNF_AVPLAY_Destroy(hAvplay);
        HI_UNF_AVPLAY_DeInit();
        dev_deinit();
        return s32Ret;
    }

    //stTrackAttr.enTrackType = HI_UNF_SND_TRACK_TYPE_MASTER;
    s32Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &stTrackAttr);
    if (s32Ret != HI_SUCCESS)
    {
        HI_TUNER_ERR("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
        return s32Ret;
    }
    s32Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_UNF_SND_CreateTrack failed.\n");
        HI_UNF_VO_SetWindowEnable(phWin, HI_FALSE);
        HI_UNF_VO_DetachWindow(phWin, hAvplay);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        HI_UNF_AVPLAY_Destroy(hAvplay);
        HI_UNF_AVPLAY_DeInit();
        dev_deinit();
        return s32Ret;
    }

    s32Ret = HI_UNF_SND_Attach(hTrack, hAvplay);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_SND_Attach failed.\n");
        HI_UNF_SND_DestroyTrack(hTrack);
        HI_UNF_VO_SetWindowEnable(phWin, HI_FALSE);
        HI_UNF_VO_DetachWindow(phWin, hAvplay);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        HI_UNF_AVPLAY_Destroy(hAvplay);
        HI_UNF_AVPLAY_DeInit();
        dev_deinit();
        return s32Ret;
    }

    s32Ret = HIADP_AVPlay_SetAdecAttr(hAvplay, HA_AUDIO_ID_MP3, HD_DEC_MODE_RAWPCM, 1);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_UNF_AVPLAY_SetAttr_ADEC failed.\n");
        HI_UNF_AVPLAY_Destroy(hAvplay);
        HI_UNF_AVPLAY_DeInit();
        dev_deinit();
        return s32Ret;
    }

    HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_VDEC, &stVdecAttr);
    stVdecAttr.enMode = HI_UNF_VCODEC_MODE_NORMAL;
#if defined(ISDBT_IT9170)
    stVdecAttr.enType = HI_UNF_VCODEC_TYPE_H264;
#else
    stVdecAttr.enType = HI_UNF_VCODEC_TYPE_MPEG2;
#endif
    stVdecAttr.u32ErrCover = 80;
    stVdecAttr.u32Priority = HI_UNF_VCODEC_MAX_PRIORITY;
    stVdecAttr.bOrderOutput = HI_FALSE;
    s32Ret = HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_VDEC, &stVdecAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_UNF_AVPLAY_SetAttr_VDEC failed.\n");
        HI_UNF_AVPLAY_Destroy(hAvplay);
        HI_UNF_AVPLAY_DeInit();
        dev_deinit();
        return s32Ret;
    }

    s32Ret = HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &stSyncAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_UNF_AVPLAY_SetAttr failed.\n");
        HI_UNF_SND_Detach(hTrack, hAvplay);
        HI_UNF_SND_DestroyTrack(hTrack);
        HI_UNF_VO_SetWindowEnable(phWin, HI_FALSE);
        HI_UNF_VO_DetachWindow(phWin, hAvplay);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        HI_UNF_AVPLAY_Destroy(hAvplay);
        HI_UNF_AVPLAY_DeInit();
        dev_deinit();
        return s32Ret;
    }
    stSyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
    stSyncAttr.stSyncStartRegion.s32VidPlusTime = 100;
    stSyncAttr.stSyncStartRegion.s32VidNegativeTime = -100;
    stSyncAttr.bQuickOutput = HI_FALSE;
    s32Ret = HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &stSyncAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HI_UNF_AVPLAY_SetAttr failed.\n");
        HI_UNF_SND_Detach(hTrack, hAvplay);
        HI_UNF_SND_DestroyTrack(hTrack);
        HI_UNF_VO_SetWindowEnable(phWin, HI_FALSE);
        HI_UNF_VO_DetachWindow(phWin, hAvplay);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        HI_UNF_AVPLAY_Destroy(hAvplay);
        HI_UNF_AVPLAY_DeInit();
        dev_deinit();
        return s32Ret;
    }

    /*aaa AudioLineOutMuteCntrDisable();*/

    return HI_SUCCESS;
}

HI_S32 avplay_deinit()
{
    HI_S32 s32Ret = 0;
    HI_UNF_AVPLAY_STOP_OPT_S    stStop;

    stStop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    stStop.u32TimeoutMs = 0;

    s32Ret = HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &stStop);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_WARN("call HI_UNF_AVPLAY_Stop failed.\n");
    }

    s32Ret = HI_UNF_SND_Detach(hTrack, hAvplay);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_WARN("call HI_UNF_SND_Detach failed.\n");
    }

    s32Ret = HI_UNF_SND_DestroyTrack(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_WARN("call HI_UNF_SND_DestroyTrack failed.\n");
    }

    s32Ret = HI_UNF_VO_SetWindowEnable(phWin,HI_FALSE);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_WARN("call HI_UNF_VO_SetWindowEnable failed.\n");
    }

    s32Ret = HI_UNF_VO_DetachWindow(phWin, hAvplay);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_WARN("call HI_UNF_VO_DetachWindow failed.\n");
    }

    s32Ret= HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_WARN("call HI_UNF_AVPLAY_ChnClose failed.\n");
    }

    s32Ret = HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_WARN("call HI_UNF_AVPLAY_ChnClose failed.\n");
    }

    s32Ret = HI_UNF_AVPLAY_Destroy(hAvplay);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_WARN("call HI_UNF_AVPLAY_Destroy failed.\n");
    }

    s32Ret = HI_UNF_AVPLAY_DeInit();
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_WARN("call HI_UNF_AVPLAY_DeInit failed.\n");
    }

    return HI_SUCCESS;
}

static HI_S32 hi_tuner_getplpinfo()
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U8 u8PLPNUM = 0;
    HI_UNF_TUNER_T2_PLP_TYPE_E enPLPType = HI_UNF_TUNER_T2_PLP_TYPE_BUTT;
    HI_UNF_TUNER_TER_CHANNEL_ATTR_S stTpArray[200];
    HI_UNF_TUNER_TER_PLP_ATTR_S stPlpAttr[16],stPlpBuf;
    HI_U8 i = 0,j,k,u8PlpId = 0,u8GrpId = 0,u8GrpNum = 0,u8Cnt = 0,u8CommExist = 0;
    T2MultiGroup T2PLPArray[10];


    s32Ret = HI_UNF_TUNER_GetPLPNum(s_s32TunerPort, &u8PLPNUM);
    if(HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("HI_UNF_TUNER_GetPLPNum error.\n");
        return HI_FAILURE;
    }

    for(i = 0;i < u8PLPNUM;i++)
    {
        HI_UNF_TUNER_SetPLPMode(s_s32TunerPort,1);
        s32Ret = HI_UNF_TUNER_SetPLPID(s_s32TunerPort,i);
        if(HI_SUCCESS != s32Ret)
        {
            HI_TUNER_ERR("HI_UNF_TUNER_SetPLPID error.\n");
        }

        s32Ret = HI_UNF_TUNER_GetPLPId(s_s32TunerPort,&u8PlpId);
        if(HI_SUCCESS != s32Ret)
        {
            HI_TUNER_ERR("HI_UNF_TUNER_GetPLPId error.\n");
        }
        s32Ret = HI_UNF_TUNER_GetPLPGrpId(s_s32TunerPort,&u8GrpId);
        if(HI_SUCCESS != s32Ret)
        {
            HI_TUNER_ERR("HI_UNF_TUNER_GetPLPGrpId error.\n");
        }
        s32Ret = HI_UNF_TUNER_GetCurrentPLPType(s_s32TunerPort,&enPLPType);
        if(HI_SUCCESS != s32Ret)
        {
            HI_TUNER_ERR("HI_UNF_TUNER_GetCurrentPLPType error.\n");
        }

        stPlpAttr[i].u8PlpIndex = i;
        stPlpAttr[i].u8PlpId = u8PlpId;
        stPlpAttr[i].u8PlpGrpId = u8GrpId;
        stPlpAttr[i].enPlpType = enPLPType;
    }

    for(i=0;i<u8PLPNUM-1;i++)
    {
        for(j=0;j<u8PLPNUM - 1-i;j++)
        {
            if(stPlpAttr[j].u8PlpGrpId > stPlpAttr[j+1].u8PlpGrpId)
            {
                memcpy(&stPlpBuf,&stPlpAttr[j],sizeof(HI_UNF_TUNER_TER_PLP_ATTR_S));
                memcpy(&stPlpAttr[j],&stPlpAttr[j+1],sizeof(HI_UNF_TUNER_TER_PLP_ATTR_S));
                memcpy(&stPlpAttr[j+1],&stPlpBuf,sizeof(HI_UNF_TUNER_TER_PLP_ATTR_S));
            }
        }
    }

    memset(T2PLPArray,0,sizeof(T2PLPArray));
    T2PLPArray[0].u8GrpId = stPlpAttr[0].u8PlpGrpId;
    for(i = 0,u8GrpNum = 0;i < u8PLPNUM;i++)
    {
        if(T2PLPArray[u8GrpNum].u8GrpId != stPlpAttr[i].u8PlpGrpId)
        {
            u8GrpNum++;
            T2PLPArray[u8GrpNum].u8GrpId = stPlpAttr[i].u8PlpGrpId;
            u8Cnt = 0;
            u8CommExist = 0;
        }

        if(HI_UNF_TUNER_T2_PLP_TYPE_COM == stPlpAttr[i].enPlpType)
        {
            T2PLPArray[u8GrpNum].u8CommId = stPlpAttr[i].u8PlpIndex;
            u8CommExist = 1;
        }

        u8Cnt++;
        if((u8Cnt >= 2) && u8CommExist)
        {
            T2PLPArray[u8GrpNum].u8Combination = 1;
        }
    }

    u8GrpNum = u8GrpNum + 1;

    printf("plp index       group plp id       plp type\n");
    for(i=0;i<u8PLPNUM;i++)
    {
       printf("%d              %d                  %d\n",stPlpAttr[i].u8PlpIndex,stPlpAttr[i].u8PlpGrpId,stPlpAttr[i].enPlpType);
    }
    printf("---------------------------------------------\n");

    for(i=0,k=0;i<u8PLPNUM;i++)
    {
        for(j=0;j<u8GrpNum;j++)
        {
            if(stPlpAttr[i].u8PlpGrpId == T2PLPArray[j].u8GrpId)
                break;
        }

        if(HI_UNF_TUNER_T2_PLP_TYPE_COM == stPlpAttr[i].enPlpType)
        {
            continue;
        }

        stTpArray[k].u8PlpIndex = stPlpAttr[i].u8PlpIndex;
        stTpArray[k].u8PlpId = stPlpAttr[i].u8PlpId;
        stTpArray[k].u8CommId = T2PLPArray[j].u8CommId;
        stTpArray[k].u8Combination = T2PLPArray[j].u8Combination;
        k++;
    }

    printf("plp index       common plp index       combination\n");
    for(i=0;i<k;i++)
    {
        printf("%d              %d                  %d\n",stTpArray[i].u8PlpIndex,stTpArray[i].u8CommId,stTpArray[i].u8Combination);
    }

    return HI_SUCCESS;
}


/*lock freq function*/
HI_S32 hi_tuner_connect()
{
    HI_S32 s32Ret = HI_FAILURE;
    //HI_UNF_TUNER_SIGNALINFO_S stInfo;
    HI_UNF_TUNER_STATUS_S stTunerStatus;
    HI_U32 u32Loop = 0;
    HI_U32 u32LoopTimes = 400,u32TimeOut = 0;
    HI_U32 u32Freq = 0;
    HI_U32 u32SymbolRate = 0;
    HI_U32 u32BW = 0;
    HI_S32 s32Ret1 = HI_FAILURE;


    switch ((HI_U32)s_stConnectPara[s_s32TunerPort].enSigType)
    {
        case HI_UNF_TUNER_SIG_TYPE_SAT:
            u32Freq = s_stConnectPara[s_s32TunerPort].unConnectPara.stSat.u32Freq;
            u32SymbolRate = s_stConnectPara[s_s32TunerPort].unConnectPara.stSat.u32SymbolRate;
            if (u32SymbolRate < 5000000)
                u32LoopTimes = 1000;
            else if (u32SymbolRate < 10000000)
                u32LoopTimes = 120;
            else
                u32LoopTimes = 100;
            break;

        case HI_UNF_TUNER_SIG_TYPE_DVB_T:
        case HI_UNF_TUNER_SIG_TYPE_DVB_T2:
        case HI_UNF_TUNER_SIG_TYPE_ISDB_T:
        case HI_UNF_TUNER_SIG_TYPE_ATSC_T:
        case (HI_UNF_TUNER_SIG_TYPE_DVB_T|HI_UNF_TUNER_SIG_TYPE_DVB_T2):
        case HI_UNF_TUNER_SIG_TYPE_DTMB:
            u32Freq = s_stConnectPara[s_s32TunerPort].unConnectPara.stTer.u32Freq;
            u32BW   = s_stConnectPara[s_s32TunerPort].unConnectPara.stTer.u32BandWidth/1000;
#if defined(DVBT_IT9133) || defined(ISDBT_IT9170)
            u32LoopTimes = 1;
#endif
            break;
        default:
            return HI_SUCCESS;
    }

    if((HI_UNF_TUNER_SIG_TYPE_DVB_T2 & s_stConnectPara[s_s32TunerPort].enSigType))
    {
        /*set HI_UNF_TUNER_Connect output 0th PLP as default,if u8PlpId = 1 then output 1th PLP as default. */
        s_stConnectPara[s_s32TunerPort].unConnectPara.stTer.stPLPParam.u8PlpId = 0;
        s_stConnectPara[s_s32TunerPort].unConnectPara.stTer.stPLPParam.u8CommPlpId = 0;
        s_stConnectPara[s_s32TunerPort].unConnectPara.stTer.stPLPParam.u8Combination = 0;
    }

    s32Ret = HI_UNF_TUNER_Connect(s_s32TunerPort, &(s_stConnectPara[s_s32TunerPort]), u32TimeOut);
    if(0 == u32TimeOut)
        usleep(30*1000);

    if (HI_SUCCESS == s32Ret)
    {
        for (u32Loop = 0; u32Loop < u32LoopTimes; u32Loop++)
        {
            s32Ret = HI_UNF_TUNER_GetStatus(s_s32TunerPort, &stTunerStatus);
            if (HI_UNF_TUNER_SIGNAL_LOCKED == stTunerStatus.enLockStatus)
            {
                switch ((HI_U32)s_stConnectPara[s_s32TunerPort].enSigType)
                {
                    case HI_UNF_TUNER_SIG_TYPE_DVB_T:
                    case HI_UNF_TUNER_SIG_TYPE_DVB_T2:
                    case HI_UNF_TUNER_SIG_TYPE_ISDB_T:
                    case HI_UNF_TUNER_SIG_TYPE_ATSC_T:
                    case HI_UNF_TUNER_SIG_TYPE_DTMB:
                    case (HI_UNF_TUNER_SIG_TYPE_DVB_T|HI_UNF_TUNER_SIG_TYPE_DVB_T2):
                    {
                        printf("Tuner   Lock freq %d bandwidth %d Success!\n",
                               u32Freq, u32BW);

                        /*automatically play the first program after locked successfully*/
                        strcpy(s_acTestResult, HI_RESULT_SUCCESS);

                        if (HI_UNF_TUNER_SIG_TYPE_DVB_T2 & s_stConnectPara[s_s32TunerPort].enSigType)
                        {
                            //usleep(1000*1000);
                            s32Ret1 = hi_tuner_getplpinfo();
                            if (HI_SUCCESS != s32Ret1)
                            {
                                return HI_FAILURE;
                            }
                        }

                        return HI_SUCCESS;
                    }
                    case HI_UNF_TUNER_SIG_TYPE_SAT:
                    {
                        printf("Tuner   Lock freq %d symb %d Success!\n", u32Freq, u32SymbolRate);

                        /*automatically play the first program after locked successfully*/
                        printf("SUCCESS end\n");
                        strcpy(s_acTestResult, HI_RESULT_SUCCESS);

                        return HI_SUCCESS;
                    }
                    default:
                    {
                        return HI_SUCCESS;
                    }
                }
            }
            else
            {
                usleep(10000);
            }
        }
    }
    else
    {
        switch ((HI_U32)s_stConnectPara[s_s32TunerPort].enSigType)
        {
            case HI_UNF_TUNER_SIG_TYPE_DVB_T:
            case HI_UNF_TUNER_SIG_TYPE_DVB_T2:
            case HI_UNF_TUNER_SIG_TYPE_ISDB_T:
            case HI_UNF_TUNER_SIG_TYPE_ATSC_T:
            case HI_UNF_TUNER_SIG_TYPE_DTMB:
            case (HI_UNF_TUNER_SIG_TYPE_DVB_T|HI_UNF_TUNER_SIG_TYPE_DVB_T2):
                printf("Tuner Lock freq %d bandwidth %d Fail!, s32Ret = 0x%x\n", u32Freq, u32BW, s32Ret);
                break;
            case HI_UNF_TUNER_SIG_TYPE_SAT:
                printf("Tuner Lock freq %d symb %d  Fail!, s32Ret = 0x%x\n", u32Freq, u32SymbolRate, s32Ret);
                break;
            default:
                break;
        }
    }

    if (u32Loop == u32LoopTimes)
    {
        switch (s_stConnectPara[s_s32TunerPort].enSigType)
        {
            case HI_UNF_TUNER_SIG_TYPE_DVB_T:
            case HI_UNF_TUNER_SIG_TYPE_DVB_T2:
            case HI_UNF_TUNER_SIG_TYPE_ISDB_T:
            case HI_UNF_TUNER_SIG_TYPE_ATSC_T:
            case HI_UNF_TUNER_SIG_TYPE_DTMB:
                printf("Tuner Lock freq %d bandwidth %d Fail!\n", u32Freq, u32BW);
                break;
            case HI_UNF_TUNER_SIG_TYPE_SAT:
                printf("Tuner Lock freq %d symb %d  Fail!\n", u32Freq, u32SymbolRate);
                break;
            default:
                break;
        }
    }

    printf("FAIL end\n");
    strcpy(s_acTestResult,HI_RESULT_FAIL);
    return HI_FAILURE;
}

HI_S32 printime_init()
{

    FILE *time_file = NULL;


    time_file = fopen("time_file", "wt");
    if (NULL == time_file)
    {
        HI_TUNER_ERR("open time_file ,line = %d\n", __LINE__);
        return HI_FAILURE;
    }

    fclose(time_file);

    return HI_SUCCESS;
}

void printtime_file(int locknum, int locktime,int isfail)
{
    FILE *time_file = NULL;

#ifdef  CONFIG_SUPPORT_CA_RELEASE
    time_file = fopen("/tmp/time_file", "at");
#else
    time_file = fopen("time_file", "at");
#endif
    if (NULL == time_file)
    {
        HI_TUNER_INFO("open time_file,line = %d\n", __LINE__);
    }
    if(isfail== 1)
    {
        /*fprintf(time_file, "FAIL: locknum = %d,locktime = %d   isfail = %d\n", locknum, locktime,isfail);*/
        fprintf(time_file, "%d       isfail = %d\n", locktime,isfail);
        s_s32Time =s_s32Time+ locktime;
        s_s32FailTime++;
    }
    else if(isfail == 2)
    {
        s_s32Out1Time++;
        fprintf(time_file, "%d      isfail = %d\n",  locktime,isfail);
        s_s32Time =s_s32Time+ locktime;
    }
    else if(isfail == 3)
    {
        s_s32OutFailTime++;
        if(locktime>1000)
        {
            s_s32Out1Time++;
        }
        fprintf(time_file, "%d      isfail = %d\n",  locktime,isfail);
        s_s32Time =s_s32Time+ locktime;
    }
    else
    {
        /*fprintf(time_file, "OK: locknum = %d,locktime = %d,isfail = %d\n", locknum, locktime,isfail);*/
        fprintf(time_file, "%d   isfail = %d\n", locktime,isfail);
        s_s32Time =s_s32Time+ locktime;
    }

    if(locknum+1>= s_s32LoopNum)
    {
        /*printf("locknum =%d,s_s32LoopNum=%d\n",locknum,s_s32LoopNum);*/
        fprintf(time_file, "locknum =%d,s_s32LoopNum=%d\n",locknum+1,s_s32LoopNum);
        fprintf(time_file, "AVERVAGE TIME : %d\n", s_s32Time/(s_s32LoopNum));
        fprintf(time_file, "FAIL NUM: %d\n", s_s32FailTime);
        fprintf(time_file, " >1s NUM: %d\n", s_s32Out1Time);
        fprintf(time_file, " out fail  NUM: %d\n", s_s32OutFailTime);
    }
    fclose(time_file);

}

HI_VOID hi_tuner_start(char * locktime)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_UNF_TUNER_STATUS_S stTunerStatus;
    HI_UNF_TUNER_CONNECT_PARA_S  stTmpConnectPara;
    HI_U32 u32Loop = 0;
    HI_U32 u32StatTime = 0;
    HI_U32 u32EndTime = 0;
    HI_U32 u32TempTime = 0;
    HI_U32 u32IndexLockTime;
    HI_U32 u32TotalLockTime;

    if (HI_NULL_PTR == locktime)
    {
        HI_TUNER_ERR("please input loctime count\n");
        return;
    }
    u32TotalLockTime = atoi(locktime);

    memcpy(&stTmpConnectPara,&s_stConnectPara[s_s32TunerPort],sizeof(HI_UNF_TUNER_CONNECT_PARA_S));

    s_s32LoopNum = u32TotalLockTime;

    s_s32FailTime =0;
    s_s32Out1Time = 0;
    s_s32OutFailTime = 0;
    s_s32Time = 0;

    s32Ret = printime_init();
    if (HI_FAILURE == s32Ret)
    {
        HI_TUNER_ERR("printime_init failure\n");
        return;
    }

    for(u32IndexLockTime = 0; u32IndexLockTime < u32TotalLockTime; u32IndexLockTime++)
    {
           u32StatTime = getcurtime();
           s32Ret = HI_UNF_TUNER_Connect(s_s32TunerPort, &(s_stConnectPara[s_s32TunerPort]), 0);
            if (HI_SUCCESS == s32Ret)
            {
                for (u32Loop = 0; u32Loop < 300; u32Loop++)
                {
                    s32Ret = HI_UNF_TUNER_GetStatus(s_s32TunerPort, &stTunerStatus);
                    if (HI_UNF_TUNER_SIGNAL_LOCKED == stTunerStatus.enLockStatus)
                    {
                        u32EndTime = getcurtime();
                        u32TempTime = u32EndTime - u32StatTime;
                    if(u32TempTime > 1000)
                    {
                        HI_TUNER_INFO("===111===IndexLockTime=%d,locktime=%d\n",u32IndexLockTime,u32TempTime);
                        printtime_file(u32IndexLockTime, u32TempTime,2);
                    }
                    else
                    {
                        HI_TUNER_INFO("===000===IndexLockTime=%d,locktime=%d\n",u32IndexLockTime,u32TempTime);
                        printtime_file(u32IndexLockTime, u32TempTime,0);
                    }

                        HI_TUNER_INFO("SUCCESS end\n");
                        strcpy(s_acTestResult,HI_RESULT_SUCCESS);
                        break;
                    }
                    else
                    {
                        usleep(10000);
                    }
                }
            }
            else
            {
            HI_TUNER_WARN("Tuner Lock freq %d symb %d  qam%d Fail!, s32Ret = 0x%x\n",
                   s_stConnectPara[s_s32TunerPort].unConnectPara.stCab.u32Freq,
                   s_stConnectPara[s_s32TunerPort].unConnectPara.stCab.u32SymbolRate, s_u32CurrentQamType, s32Ret);
            }

            if (u32Loop == 300)
            {
            HI_TUNER_WARN("Tuner Lock freq %d symb %d  qam%d time out , s32Ret = 0x%x\n",
                   s_stConnectPara[s_s32TunerPort].unConnectPara.stCab.u32Freq,
                 s_stConnectPara[s_s32TunerPort].unConnectPara.stCab.u32SymbolRate, s_u32CurrentQamType, s32Ret);

                 u32EndTime = getcurtime();
                 u32TempTime = u32EndTime - u32StatTime;
                 printtime_file(u32IndexLockTime, u32TempTime, 3);
            }

            if((u32IndexLockTime%2) == 0)
            {

                stTmpConnectPara.unConnectPara.stCab.u32Freq =  s_stConnectPara[s_s32TunerPort].unConnectPara.stCab.u32Freq+8*1000;
                stTmpConnectPara.unConnectPara.stCab.enModType =  s_stConnectPara[s_s32TunerPort].unConnectPara.stCab.enModType;
                stTmpConnectPara.unConnectPara.stCab.u32SymbolRate =  s_stConnectPara[s_s32TunerPort].unConnectPara.stCab.u32SymbolRate;

                HI_UNF_TUNER_Connect(s_s32TunerPort, &stTmpConnectPara, 500);

                usleep(200000);
            }
    }
}

/* set signal type and call hi_tuner_connect */
HI_VOID hi_tuner_setsigtype(char * sigtype)
{
    if (sigtype == HI_NULL_PTR)
    {
        return;
    }

    switch (atoi(sigtype))
    {
        case 0:
            s_stConnectPara[s_s32TunerPort].enSigType = HI_UNF_TUNER_SIG_TYPE_CAB;
            s_stConnectPara[s_s32TunerPort].unConnectPara.stCab.u32SymbolRate = 6875000;
            break;
        case 1:
            s_stConnectPara[s_s32TunerPort].enSigType = HI_UNF_TUNER_SIG_TYPE_DVB_T;
            s_stConnectPara[s_s32TunerPort].unConnectPara.stTer.u32BandWidth = 8000;
            break;
        case 2:
            s_stConnectPara[s_s32TunerPort].enSigType = HI_UNF_TUNER_SIG_TYPE_DVB_T2;
            s_stConnectPara[s_s32TunerPort].unConnectPara.stTer.u32BandWidth = 8000;
            break;
        case 3:
            s_stConnectPara[s_s32TunerPort].enSigType = HI_UNF_TUNER_SIG_TYPE_ISDB_T;
            break;
        case 4:
            s_stConnectPara[s_s32TunerPort].enSigType = HI_UNF_TUNER_SIG_TYPE_ATSC_T;
            break;
        case 5:
            s_stConnectPara[s_s32TunerPort].enSigType = HI_UNF_TUNER_SIG_TYPE_DTMB;
            break;
        case 6:
            s_stConnectPara[s_s32TunerPort].enSigType = HI_UNF_TUNER_SIG_TYPE_SAT;
            break;
        default:
            s_stConnectPara[s_s32TunerPort].enSigType = HI_UNF_TUNER_SIG_TYPE_CAB;
    }

    hi_tuner_connect();
}

HI_VOID hi_tuner_selectCurrentPort(char * pPort)
{
    HI_S32 s32Ret;

    if (pPort == HI_NULL_PTR)
    {
        return;
    }

    if (HI_TUNER_NUMBER < 2)
    {
        HI_TUNER_ERR("HI_TUNER_NUMBER:%d,so this cmd is invalid.\n", HI_TUNER_NUMBER);
        return;
    }

    s_s32TunerPort = atoi(pPort);
    if(s_s32TunerPort >= HI_TUNER_NUMBER)
    {
        s_s32TunerPort %= HI_TUNER_NUMBER;
    }

    s32Ret = HIADP_DMX_AttachTSPort(0, s_s32TunerPort);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HIADP_DMX_AttachTSPort failed 0x%x\n", s32Ret);
        HI_UNF_DMX_DeInit();
        return;
    }

    HI_TUNER_INFO("s_s32TunerPort:%d,switch to demuxPort:%d\n",
                             s_s32TunerPort,
                             (s_s32TunerPort==0)?HI_DEMUX_PORT:HI_DEMUX1_PORT);

}

/* set channel freqency/symbolrate/polar and call hi_tuner_connect */
HI_VOID hi_tuner_setchannel(char * channel)
{
    HI_U32 u32Freq,u32Symb,u32Polar = 0;
    HI_S32 s32Return;
    HI_UNF_AVPLAY_STOP_OPT_S stStop;

    stStop.enMode = HI_UNF_AVPLAY_STOP_MODE_STILL;
    stStop.u32TimeoutMs = 0;

    if (channel == HI_NULL_PTR)
    {
        return;
    }

    sscanf(channel,  "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d",
            (HI_U32*)&u32Freq, (HI_U32*)&u32Symb, (HI_U32*)&u32Polar);

    if (HI_UNF_TUNER_FE_POLARIZATION_BUTT <= u32Polar)
    {
        return;
    }

#ifdef DEMUX_TAG_DEAL
    switch(s_s32TunerPort)
    {
        case 0:
        default:
            enDmxPort = HI_UNF_DMX_PORT_TAG_0;
            break;
        case 1:
            enDmxPort = HI_UNF_DMX_PORT_TAG_1;
            break;
    }

    s32Return = HI_UNF_DMX_AttachTSPort(0, enDmxPort);
    if (HI_SUCCESS != s32Return)
    {
        HI_TUNER_ERR("call HI_UNF_DMX_AttachTSPort failed.\n");
        return s32Return;
    }
#else
#endif

    if ((s_stConnectPara[s_s32TunerPort].enSigType == HI_UNF_TUNER_SIG_TYPE_CAB)
            || (s_stConnectPara[s_s32TunerPort].enSigType == HI_UNF_TUNER_SIG_TYPE_J83B))
    {
        s_stConnectPara[s_s32TunerPort].unConnectPara.stCab.u32Freq = u32Freq;
        s_stConnectPara[s_s32TunerPort].unConnectPara.stCab.u32SymbolRate = u32Symb;
    }
    else if (s_stConnectPara[s_s32TunerPort].enSigType == HI_UNF_TUNER_SIG_TYPE_SAT)
    {
        s_stConnectPara[s_s32TunerPort].unConnectPara.stSat.u32Freq = u32Freq * 1000;
        s_stConnectPara[s_s32TunerPort].unConnectPara.stSat.u32SymbolRate = u32Symb;
        s_stConnectPara[s_s32TunerPort].unConnectPara.stSat.enPolar = u32Polar;
    }
    else
    {
        s_stConnectPara[s_s32TunerPort].unConnectPara.stTer.u32Freq = u32Freq;
        s_stConnectPara[s_s32TunerPort].unConnectPara.stTer.u32BandWidth = u32Symb;
        s_stConnectPara[s_s32TunerPort].unConnectPara.stTer.enChannelMode = u32Polar;
        s_stConnectPara[s_s32TunerPort].unConnectPara.stTer.enDVBTPrio = (u32Polar+1);
    }

    //try dvb-t signal, if failed, then try dvb-t2 signal, finally, resume to dvb-t signal.
    if((HI_UNF_TUNER_SIG_TYPE_DVB_T == s_stConnectPara[s_s32TunerPort].enSigType)
        || (HI_UNF_TUNER_SIG_TYPE_DVB_T2 == s_stConnectPara[s_s32TunerPort].enSigType)
        || ((HI_UNF_TUNER_SIG_TYPE_DVB_T2|HI_UNF_TUNER_SIG_TYPE_DVB_T) == s_stConnectPara[s_s32TunerPort].enSigType))
    {
        s_stConnectPara[s_s32TunerPort].enSigType = (HI_UNF_TUNER_SIG_TYPE_DVB_T | HI_UNF_TUNER_SIG_TYPE_DVB_T2);
    }
    s32Return = hi_tuner_connect();

    if(s32Return != HI_SUCCESS)
    {
        return;
    }

    s32Return= HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &stStop);
    if (s32Return != HI_SUCCESS )
    {
        HI_TUNER_ERR("call HI_UNF_AVPLAY_Stop failed.\n");
        return ;
    }

    HIADP_Search_Init();
    s32Return = HIADP_Search_GetAllPmt(0, &s_ProgTbl[s_s32TunerPort]);
    if (HI_SUCCESS != s32Return)
    {
        HI_TUNER_ERR("call HIADP_Search_GetAllPmt failed\n");
        printf("FAIL end\n");
    }
    else
    {
        printf("SUCCESS end\n");
    }

    s32Return = HI_UNF_AVPLAY_Start(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, NULL);
    if (s32Return != HI_SUCCESS)
    {
        HI_TUNER_WARN("call HI_UNF_AVPLAY_Start_AUD failed.\n");
        /*return ;*/
    }

    s32Return = HI_UNF_AVPLAY_Start(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, NULL);
    if (s32Return != HI_SUCCESS)
    {
        HI_TUNER_ERR("call HI_UNF_AVPLAY_Start_VID failed.\n");
        return ;
    }
}

HI_VOID hi_tuner_setvcm(char *vcm)
{
    HI_S32 s32Return;
    HI_U32 u32IsiID = 0;
    HI_U8  u8TotalStream = 0;

    if(vcm == HI_NULL_PTR)
    {
        return;
    }

    s32Return = HI_UNF_TUNER_GetSatTotalStream(s_s32TunerPort, &u8TotalStream);
    if(s32Return != HI_SUCCESS)
    {
        HI_TUNER_ERR("HI_UNF_TUNER_GetSatTotalStream fail.\n");
    }
    if(0 == u8TotalStream)
    {
        HI_TUNER_ERR("vcm streams number is 0.\n");
        return;
    }

    u32IsiID = atoi(vcm);
    s32Return = HI_UNF_TUNER_SetSatIsiID(s_s32TunerPort,(HI_U8)u32IsiID);
    if(s32Return != HI_SUCCESS)
    {
        HI_TUNER_ERR("HI_UNF_TUNER_SetSatIsiID fail.\n");
    }

    HIADP_Search_Init();
    s32Return = HIADP_Search_GetAllPmt(0, &s_ProgTbl[s_s32TunerPort]);
    if (HI_SUCCESS != s32Return)
    {
        HI_TUNER_ERR("call HIADP_Search_GetAllPmt failed\n");
        //return;
    }

    return;
}

HI_VOID hi_tuner_getvcm(char *nouse)
{
    HI_S32 s32Return;
    HI_U8  i;
    HI_U8  u8IsiID[32] = {0};
    HI_U8  u8TotalStream = 0;

    s32Return = HI_UNF_TUNER_GetSatTotalStream(s_s32TunerPort, &u8TotalStream);
    if(s32Return != HI_SUCCESS)
    {
        HI_TUNER_ERR("HI_UNF_TUNER_GetSatTotalStream fail.\n");
    }

    printf("total vcm/acm stream number:%d\n",u8TotalStream);
    printf("STREAM\t\tISI ID\n");

    memset(u8IsiID,0,sizeof(u8IsiID));
    for(i=0 ;i<u8TotalStream; i++)
    {
        HI_UNF_TUNER_GetSatIsiID(s_s32TunerPort, (HI_U8)i, &u8IsiID[i]);
        printf("%d\t\t%d\n",i,u8IsiID[i]);
    }

    return;
}

HI_VOID hi_tuner_setscramble(char *scramble)
{
    HI_U32 u32N;

    if (!scramble)
    {
        HI_TUNER_ERR("Invalid input.\n");
        return;
    }

    u32N = atoi(scramble);
    s_stConnectPara[s_s32TunerPort].unConnectPara.stSat.u32ScrambleValue = u32N;

    return;
}

/* set  type of modulation and call hi_tuner_connect */
HI_VOID hi_tuner_setqam(char * qam)
{
    HI_S32 s32GetQam;

    if (qam == HI_NULL_PTR)
    {
        return;
    }

    s32GetQam = atoi(qam);
    s_u32CurrentQamType = s32GetQam;
    switch (s32GetQam)
    {
        case 64:
        {
            if(HI_UNF_DEMOD_DEV_TYPE_J83B == S_DEMOD_TYPE)
            {
                s_stConnectPara[s_s32TunerPort].unConnectPara.stCab.u32SymbolRate = 5057000;
            }
            else
            {
                s_stConnectPara[s_s32TunerPort].unConnectPara.stCab.u32SymbolRate = 6875000;
            }
            s_stConnectPara[s_s32TunerPort].unConnectPara.stCab.enModType = HI_UNF_MOD_TYPE_QAM_64;
            break;
        }
        case 256:
        {
            if(HI_UNF_DEMOD_DEV_TYPE_J83B == S_DEMOD_TYPE)
            {
                s_stConnectPara[s_s32TunerPort].unConnectPara.stCab.u32SymbolRate = 5361000;
            }
            else
            {
                s_stConnectPara[s_s32TunerPort].unConnectPara.stCab.u32SymbolRate = 6875000;
            }
            s_stConnectPara[s_s32TunerPort].unConnectPara.stCab.enModType = HI_UNF_MOD_TYPE_QAM_256;
            break;
        }
        case 16:
            s_stConnectPara[s_s32TunerPort].unConnectPara.stCab.enModType = HI_UNF_MOD_TYPE_QAM_16;
            break;
        case 32:
            s_stConnectPara[s_s32TunerPort].unConnectPara.stCab.enModType = HI_UNF_MOD_TYPE_QAM_32;
            break;
        case 128:
            s_stConnectPara[s_s32TunerPort].unConnectPara.stCab.enModType = HI_UNF_MOD_TYPE_QAM_128;
            break;
        default:
            s_u32CurrentQamType = 64;
            s_stConnectPara[s_s32TunerPort].unConnectPara.stCab.enModType = HI_UNF_MOD_TYPE_QAM_64;
            break;
    }

    hi_tuner_connect();
}

#if 1
HI_VOID hi_tuner_getmsc(char *arg)
{
    HI_S32 s32Ret;

    HI_S32 i;
    HI_S32 s32Time;
   HI_UNF_AVPLAY_STATUS_INFO_S stStatusInfoStart;
   HI_UNF_AVPLAY_STATUS_INFO_S stStatusInfoEnd;

    /*HI_U32 u32ErrNumStart = 0;
    HI_U32 u32TotalNumStart = 0;
    HI_U32 u32ErrNumEnd = 0;
    HI_U32 u32TotalNumEnd = 0;*/
    HI_U32 u32ErrNum;
    HI_S32 s32TotalErrNum = 0;
    if(arg == 0)
    {
        s32Time = 1;
    }
    else
    {
        sscanf(arg,"%d ",&s32Time);
    }

    /*msc_appear_times = 0;*/
    for(i = 0; i < s32Time; i++)
    {

        s32Ret = HI_UNF_AVPLAY_GetStatusInfo( hAvplay, &stStatusInfoStart);
    //s32Ret =  HI_MPI_VDEC_GetChanStatusInfo(0x260000, &stVdecStatInfoStart );

        sleep(1);

     s32Ret |= HI_UNF_AVPLAY_GetStatusInfo( hAvplay, &stStatusInfoEnd);
      //  s32Ret |= HI_MPI_VDEC_GetChanStatusInfo(0x260000, &stVdecStatInfoEnd );

        /*u32ErrNum = u32ErrNumEnd - u32ErrNumStart;*/
        //u32ErrNum = stVdecStatInfoEnd.u32TotalErrFrmNum - stVdecStatInfoStart.u32TotalErrFrmNum;
        u32ErrNum = stStatusInfoEnd.u32VidErrorFrameCount - stStatusInfoStart.u32VidErrorFrameCount;
        if(HI_SUCCESS == s32Ret)
        {
            if( u32ErrNum > 0 )
            {
                HI_TUNER_INFO("---SUCCESS%d end\n", u32ErrNum );
                s32TotalErrNum = s32TotalErrNum + u32ErrNum;
                sprintf(s_acTestResult,HI_RESULT_SUCCESS"%d", u32ErrNum );
                return;
            }
            /*else if( u32TotalNumStart == u32TotalNumEnd )*/
           // else if( stVdecStatInfoStart.u32TotalDecFrmNum == stVdecStatInfoEnd.u32TotalDecFrmNum )
            else if( stStatusInfoStart.u32VidFrameCount == stStatusInfoEnd.u32VidFrameCount )
            {
                HI_TUNER_ERR("SUCCESS%d end\n",25);
                sprintf(s_acTestResult,HI_RESULT_SUCCESS"%d",25);
                return;
            }
        }
        else
        {
            HI_TUNER_ERR("HI_VID_GetErrorFrameNum Faild %x!\n",s32Ret);
            HI_TUNER_ERR("FAIL end\n");
            strcpy(s_acTestResult,HI_RESULT_FAIL);
            return;
        }
    }

    HI_TUNER_INFO("SUCCESS%d end\n",0);
    sprintf(s_acTestResult,HI_RESULT_SUCCESS"%d",0);

    return ;
}
#endif
#if 0
/* not be used temporarily */
HI_VOID hi_tuner_getmsc_ber(char * arg)
{
    HI_S32 s32Ret;
    HI_U32 au32Ber[3];
    HI_U32 au32MskTmp[3];
    HI_DOUBLE dRealBer;
    struct timeval stBtv;
    struct timeval stEtv;
    HI_S32 s32UseTime;
    HI_S32 s32SetTime = 0;
    HI_S32 s32MskNum = 0;
    HI_FLOAT fMskBer = 0.0;
    HI_FLOAT fAvgBer = 0.0;
    HI_S32 i = 0;

    if(arg == 0)
    {
        s32SetTime = 2;
    }
    else
    {
        sscanf(arg,"%d %f",&s32SetTime,&fMskBer);
    }

    if(fMskBer < 0.0000001)
    {
        fMskBer = s_fMskBer;
    }

    gettimeofday(&stBtv,0);
    while(1)
    {
        s32Ret = HI_UNF_TUNER_GetBER(s_s32TunerPort, au32Ber);
        if(HI_SUCCESS == s32Ret)
        {
            sprintf((char *)au32MskTmp, "%d.%de-%d", au32Ber[0], au32Ber[1], au32Ber[2]);
            dRealBer = strtod((char *)au32MskTmp, NULL);
#if 0
            u32ber = (ber[0]<<16)|(ber[1]<<8)|ber[2];
            realber = u32ber /8388608.0;
#endif
            /*printf("ber :%f\n", realber);*/
            i++;
            fAvgBer = (fAvgBer * (i - 1) + dRealBer) / i;

            /*printf("HI_TUNER_GetBER ber:%10.6e    avg:%10.6e\n",realber,avgber);*/
            gettimeofday(&stEtv,0);
            s32UseTime = (stEtv.tv_sec - stBtv.tv_sec) * 1000 + (stEtv.tv_usec - stBtv.tv_usec) / 1000;
            if(fAvgBer > fMskBer)
            {
                s32MskNum = (int)(fAvgBer / fMskBer);
                if(s32SetTime > 10)
                {
                    HI_TUNER_INFO("SUCCESS%d end\n",s32MskNum);
                    break;
                }
            }

            if(s32UseTime >= s32SetTime * 1000)
            {
                HI_TUNER_INFO("SUCCESS%d end\n",s32MskNum);
                break;
            }
        }
        else
        {
            gettimeofday(&stEtv,0);
            s32UseTime = (stEtv.tv_sec - stBtv.tv_sec) * 1000 + (stEtv.tv_usec - stBtv.tv_usec) /1000;
            if(s32UseTime >= 2000)
            {
                HI_TUNER_WARN("NOTLOCK end\n");
                break;
            }

            usleep(250000);
        }

        /*usleep(100000);*/
    }

    return;
}
#endif

HI_VOID hi_tuner_settype(char * type)
{
    HI_UNF_TUNER_ATTR_S stTunerAttr;
    HI_S32 s32TunerType;
    HI_S32 s32Ret = HI_SUCCESS;

    if (type == HI_NULL_PTR)
    {
        return;
    }

    s32Ret = HI_UNF_TUNER_GetAttr(s_s32TunerPort,&stTunerAttr);
    if( HI_SUCCESS != s32Ret) return;

    s32TunerType = atoi(type);

    switch (s32TunerType)
    {
        case 0:
        stTunerAttr.enTunerDevType = HI_UNF_TUNER_DEV_TYPE_CD1616;
            break;

        case 1:
        stTunerAttr.enTunerDevType = HI_UNF_TUNER_DEV_TYPE_ALPS_TDAE;
            break;

        case 2:
        stTunerAttr.enTunerDevType = HI_UNF_TUNER_DEV_TYPE_MT2081;
            break;

        case 3:
        stTunerAttr.enTunerDevType = HI_UNF_TUNER_DEV_TYPE_TDCC;
            break;

        case 4:
        stTunerAttr.enTunerDevType = HI_UNF_TUNER_DEV_TYPE_TMX7070X;
            break;

        case 5:
        stTunerAttr.enTunerDevType = HI_UNF_TUNER_DEV_TYPE_TDA18250;
            break;

        case 6:
        stTunerAttr.enTunerDevType = HI_UNF_TUNER_DEV_TYPE_TDA18250B;
            break;
        case 7:
        stTunerAttr.enTunerDevType = HI_UNF_TUNER_DEV_TYPE_MXL203;
            break;
        case 8:
        stTunerAttr.enTunerDevType = HI_UNF_TUNER_DEV_TYPE_R820C;
            break;

        default:
        stTunerAttr.enTunerDevType = HI_UNF_TUNER_DEV_TYPE_CD1616;
            break;
    }

    (HI_VOID)HI_UNF_TUNER_SetAttr(s_s32TunerPort, &stTunerAttr);
    hi_tuner_connect();
}

static HI_VOID hi_tuner_getsignalinfo_fec(HI_UNF_TUNER_SIG_TYPE_E enSigType, HI_UNF_TUNER_FE_FECRATE_E enFECRate)
{
    if (enSigType == HI_UNF_TUNER_SIG_TYPE_ISDB_T)
    {
        HI_TUNER_INFO("\tFEC rate:\t");
    }
    else
    {
        HI_TUNER_INFO("FEC rate:\t\t");
    }

    switch (enFECRate)
    {
        case HI_UNF_TUNER_FE_FEC_1_2:
            HI_TUNER_INFO("1/2\n");
            break;
        case HI_UNF_TUNER_FE_FEC_2_3:
            HI_TUNER_INFO("2/3\n");
            break;
        case HI_UNF_TUNER_FE_FEC_3_4:
            HI_TUNER_INFO("3/4\n");
            break;
        case HI_UNF_TUNER_FE_FEC_4_5:
            HI_TUNER_INFO("4/5\n");
            break;
        case HI_UNF_TUNER_FE_FEC_5_6:
            HI_TUNER_INFO("5/6\n");
            break;
        case HI_UNF_TUNER_FE_FEC_6_7:
            HI_TUNER_INFO("6/7\n");
            break;
        case HI_UNF_TUNER_FE_FEC_7_8:
            HI_TUNER_INFO("7/8\n");
            break;
        case HI_UNF_TUNER_FE_FEC_8_9:
            HI_TUNER_INFO("8/9\n");
            break;
        case HI_UNF_TUNER_FE_FEC_9_10:
            HI_TUNER_INFO("9/10\n");
            break;
        case HI_UNF_TUNER_FE_FEC_1_4:
            HI_TUNER_INFO("1/4\n");
            break;
        case HI_UNF_TUNER_FE_FEC_1_3:
            HI_TUNER_INFO("1/3\n");
            break;
        case HI_UNF_TUNER_FE_FEC_2_5:
            HI_TUNER_INFO("2/5\n");
            break;
        case HI_UNF_TUNER_FE_FEC_3_5:
            HI_TUNER_INFO("3/5\n");
            break;
        case HI_UNF_TUNER_FE_FEC_13_45:
            HI_TUNER_INFO("13/45\n");
            break;
        case HI_UNF_TUNER_FE_FEC_9_20:
            HI_TUNER_INFO("9/20\n");
            break;
        case HI_UNF_TUNER_FE_FEC_11_20:
            HI_TUNER_INFO("11/20\n");
            break;
        case HI_UNF_TUNER_FE_FEC_5_9_L:
            HI_TUNER_INFO("5/9L\n");
            break;
        case HI_UNF_TUNER_FE_FEC_26_45_L:
            HI_TUNER_INFO("26/45L\n");
            break;
        case HI_UNF_TUNER_FE_FEC_23_36:
            HI_TUNER_INFO("23/36\n");
            break;
        case HI_UNF_TUNER_FE_FEC_25_36:
            HI_TUNER_INFO("25/36\n");
            break;
        case HI_UNF_TUNER_FE_FEC_13_18:
            HI_TUNER_INFO("13/18\n");
            break;
        case HI_UNF_TUNER_FE_FEC_1_2_L:
            HI_TUNER_INFO("1/2L\n");
            break;
        case HI_UNF_TUNER_FE_FEC_8_15_L:
            HI_TUNER_INFO("8/15L\n");
            break;
        case HI_UNF_TUNER_FE_FEC_26_45:
            HI_TUNER_INFO("26/45\n");
            break;
        case HI_UNF_TUNER_FE_FEC_3_5_L:
            HI_TUNER_INFO("3/5L\n");
            break;
        case HI_UNF_TUNER_FE_FEC_28_45:
            HI_TUNER_INFO("28/45\n");
            break;
        case HI_UNF_TUNER_FE_FEC_7_9:
            HI_TUNER_INFO("7/9\n");
            break;
        case HI_UNF_TUNER_FE_FEC_77_90:
            HI_TUNER_INFO("77/90\n");
            break;
        case HI_UNF_TUNER_FE_FEC_2_3_L:
            HI_TUNER_INFO("2/3L\n");
            break;
        case HI_UNF_TUNER_FE_FEC_32_45:
            HI_TUNER_INFO("32/45\n");
            break;
        case HI_UNF_TUNER_FE_FEC_11_15:
            HI_TUNER_INFO("11/15\n");
            break;
        case HI_UNF_TUNER_FE_FEC_11_45:
            HI_TUNER_INFO("11/45\n");
            break;
        case HI_UNF_TUNER_FE_FEC_4_15:
            HI_TUNER_INFO("4/15\n");
            break;
        case HI_UNF_TUNER_FE_FEC_14_45:
            HI_TUNER_INFO("14/45\n");
            break;
        case HI_UNF_TUNER_FE_FEC_7_15:
            HI_TUNER_INFO("7/15\n");
            break;
        case HI_UNF_TUNER_FE_FEC_8_15:
            HI_TUNER_INFO("8/15\n");
            break;
        case HI_UNF_TUNER_FE_FEC_2_9:
            HI_TUNER_INFO("2/9\n");
            break;
        case HI_UNF_TUNER_FE_FEC_11_15_L:
            HI_TUNER_INFO("11/15L\n");
            break;
        case HI_UNF_TUNER_FE_FEC_29_45_L:
            HI_TUNER_INFO("29/45L\n");
            break;
        case HI_UNF_TUNER_FE_FEC_31_45_L:
            HI_TUNER_INFO("31/45L\n");
            break;
        case HI_UNF_TUNER_FE_FEC_32_45_L:
            HI_TUNER_INFO("32/45L\n");
            break;
        case HI_UNF_TUNER_FE_FEC_AUTO:
            if (enSigType == HI_UNF_TUNER_SIG_TYPE_SAT)
            {
                HI_TUNER_INFO("Dummy\n");
            }
            else
            {
                HI_TUNER_INFO("Unknown\n");
            }
            break;
        case HI_UNF_TUNER_FE_FECRATE_BUTT:
        default:
            HI_TUNER_INFO("Unknown\n");
            break;
    }
}

static HI_VOID hi_tuner_getsignalinfo_sat(HI_UNF_TUNER_SAT_SIGNALINFO_S *pstSat)
{
    switch (pstSat->enModType)
    {
        case HI_UNF_MOD_TYPE_QAM_16:
        case HI_UNF_MOD_TYPE_QAM_32:
        case HI_UNF_MOD_TYPE_QAM_64:
        case HI_UNF_MOD_TYPE_QAM_128:
        case HI_UNF_MOD_TYPE_QAM_256:
        case HI_UNF_MOD_TYPE_QAM_512:
            HI_TUNER_INFO("Modulation type: \tQAM\n");
            break;
        case HI_UNF_MOD_TYPE_BPSK:
            HI_TUNER_INFO("Modulation type: \tBPSK\n");
            break;
        case HI_UNF_MOD_TYPE_QPSK:
            HI_TUNER_INFO("Modulation type: \tQPSK\n");
            break;
        case HI_UNF_MOD_TYPE_8PSK:
            HI_TUNER_INFO("Modulation type: \t8PSK\n");
            break;
        case HI_UNF_MOD_TYPE_16APSK:
            HI_TUNER_INFO("Modulation type: \t16APSK\n");
            break;
        case HI_UNF_MOD_TYPE_32APSK:
            HI_TUNER_INFO("Modulation type: \t32APSK\n");
            break;
        case HI_UNF_MOD_TYPE_64APSK:
            HI_TUNER_INFO("Modulation type: \t64APSK\n");
            break;
        case HI_UNF_MOD_TYPE_128APSK:
            HI_TUNER_INFO("Modulation type: \t128APSK\n");
            break;
        case HI_UNF_MOD_TYPE_256APSK:
            HI_TUNER_INFO("Modulation type: \t256APSK\n");
            break;
            break;
        case HI_UNF_MOD_TYPE_DEFAULT:
        case HI_UNF_MOD_TYPE_AUTO:
        case HI_UNF_MOD_TYPE_BUTT:
        default:
            HI_TUNER_INFO("Modulation type: \tUnknown\n");
            break;
    }

    switch (pstSat->enSATType)
    {
        case HI_UNF_TUNER_FE_DVBS:
            HI_TUNER_INFO("FEC type:\t\tDVBS\n");
            break;
        case HI_UNF_TUNER_FE_DVBS2:
            HI_TUNER_INFO("FEC type:\t\tDVBS2\n");
            break;
        case HI_UNF_TUNER_FE_DIRECTV:
            HI_TUNER_INFO("FEC type:\t\tDIRECTV\n");
            break;
        case HI_UNF_TUNER_FE_DVBS2X:
            HI_TUNER_INFO("FEC type:\t\tDVBS2X\n");
            break;
        case HI_UNF_TUNER_FE_BUTT:
        default:
            HI_TUNER_INFO("FEC type:\t\tUnknown\n");
            break;
    }

    hi_tuner_getsignalinfo_fec(HI_UNF_TUNER_SIG_TYPE_SAT, pstSat->enFECRate);

    if (HI_UNF_TUNER_FE_DVBS2 == pstSat->enSATType || HI_UNF_TUNER_FE_DVBS2X == pstSat->enSATType)
    {
        switch(pstSat->enFECFrameMode)
        {
            case HI_UNF_TUNER_SAT_FEC_FRAME_NORMAL:
                HI_TUNER_INFO("Fec frame:\t\tNormal\n");
                break;
            case HI_UNF_TUNER_SAT_FEC_FRAME_SHORT:
                HI_TUNER_INFO("Fec frame:\t\tShort\n");
                break;
            case HI_UNF_TUNER_SAT_FEC_FRAME_MEDIUM:
                HI_TUNER_INFO("Fec frame:\t\tMedium\n");
                break;
            default:
                HI_TUNER_INFO("Pilot:\t\tUnknown\n");
                break;
        }
        switch(pstSat->enCodeModulation)
        {
            case HI_UNF_TUNER_CODE_MODULATION_VCM_ACM:
                HI_TUNER_INFO("Code and Modulation:\tVCM/ACM.\n");
                break;
            case HI_UNF_TUNER_CODE_MODULATION_MULTISTREAM:
                HI_TUNER_INFO("Code and Modulation:\tMulti stream.\n");
                break;
            case HI_UNF_TUNER_CODE_MODULATION_CCM:
            default:
                HI_TUNER_INFO("Code and Modulation:\tCCM\n");
                break;
        }
        switch(pstSat->enRollOff)
        {
            case HI_UNF_TUNER_ROLLOFF_35:
                HI_TUNER_INFO("Roll off:\t\t0.35\n");
                break;
            case HI_UNF_TUNER_ROLLOFF_25:
                HI_TUNER_INFO("Roll off:\t\t0.25\n");
                break;
            case HI_UNF_TUNER_ROLLOFF_20:
                HI_TUNER_INFO("Roll off:\t\t0.20\n");
                break;
            case HI_UNF_TUNER_ROLLOFF_15:
                HI_TUNER_INFO("Roll off:\t\t0.15\n");
                break;
            case HI_UNF_TUNER_ROLLOFF_10:
                HI_TUNER_INFO("Roll off:\t\t0.10\n");
                break;
            case HI_UNF_TUNER_ROLLOFF_05:
                HI_TUNER_INFO("Roll off:\t\t0.05\n");
                break;
            default:
                HI_TUNER_INFO("Roll off:\t\tUnknown\n");
                break;
        }
        switch(pstSat->enPilot)
        {
            case HI_UNF_TUNER_PILOT_OFF:
                HI_TUNER_INFO("Pilot:\t\t\tOFF\n");
                break;
            case HI_UNF_TUNER_PILOT_ON:
                HI_TUNER_INFO("Pilot:\t\t\tON\n");
                break;
            default:
                HI_TUNER_INFO("Pilot:\t\t\tUnknown\n");
                break;
        }
        switch(pstSat->enStreamType)
        {
            case HI_UNF_TUNER_SAT_STREAM_TYPE_GENERIC_PACKETIZED:
                HI_TUNER_INFO("Stream type:\t\tGeneric packetized\n");
                break;
            case HI_UNF_TUNER_SAT_STREAM_TYPE_GENERIC_CONTINUOUS:
                HI_TUNER_INFO("Stream type:\t\tGeneric continous\n");
                break;
            case HI_UNF_TUNER_SAT_STREAM_TYPE_GSE_HEM:
                HI_TUNER_INFO("Stream type:\t\tGSE HEM\n");
                break;
            case HI_UNF_TUNER_SAT_STREAM_TYPE_TRANSPORT:
                HI_TUNER_INFO("Stream type:\t\tTransport\n");
                break;
            case HI_UNF_TUNER_SAT_STREAM_TYPE_GSE_LITE:
                HI_TUNER_INFO("Stream type:\t\tGSE Lite\n");
                break;
            case HI_UNF_TUNER_SAT_STREAM_TYPE_GSE_LITE_HEM:
                HI_TUNER_INFO("Stream type:\t\tGSE Lite HEM\n");
                break;
            case HI_UNF_TUNER_SAT_STREAM_TYPE_T2MI:
                HI_TUNER_INFO("Stream type:\t\tT2MI\n");
                break;
            default:
                HI_TUNER_INFO("Stream type:\t\tUnknow\n");
                break;
        }
    }
}

static HI_VOID hi_tuner_getsignalinfo_ter(HI_UNF_TUNER_SIG_TYPE_E enSigType, HI_UNF_TUNER_TER_SIGNALINFO_S *pstTer)
{
    HI_CHAR *acModType[] = {"1/128", "1/32", "1/16", "1/8", "1/4", "19/128", "19/256"};
    HI_CHAR *acFETType[] = {"1K", "2K", "4K", "8K", "16K", "32K", "64K"};

    hi_tuner_getsignalinfo_fec(enSigType, pstTer->enFECRate);

    printf("GI:\t\t\t");
    if (pstTer->enGuardIntv <= 0 || pstTer->enGuardIntv >= sizeof(acModType)/sizeof(acModType[0]))
    {
        printf("Unknown\n");
    }
    else
    {
        printf("%s\n", acModType[pstTer->enGuardIntv - 1]);
    }

    switch (pstTer->enModType)
    {
        case HI_UNF_MOD_TYPE_QPSK:
            printf("ModType:\t\tQPSK\n");
            break;
        case HI_UNF_MOD_TYPE_QAM_16:
            printf("ModType:\t\tQAM_16\n");
            break;
        case HI_UNF_MOD_TYPE_QAM_32:
            printf("ModType:\t\tQAM_32\n");
            break;
        case HI_UNF_MOD_TYPE_QAM_64:
            printf("ModType:\t\tQAM_64\n");
            break;
        case HI_UNF_MOD_TYPE_QAM_128:
            printf("ModType:\t\tQAM_128\n");
            break;
        case HI_UNF_MOD_TYPE_QAM_256:
            printf("ModType:\t\tQAM_256\n");
            break;
        case HI_UNF_MOD_TYPE_QAM_512:
            printf("ModType:\t\tQAM_512\n");
            break;
        case HI_UNF_MOD_TYPE_BPSK:
            printf("ModType:\t\tBPSK\n");
            break;
        case HI_UNF_MOD_TYPE_DQPSK:
            printf("ModType:\t\tDQPSK\n");
            break;
        case HI_UNF_MOD_TYPE_8PSK:
            printf("ModType:\t\t8PSK\n");
            break;
        case HI_UNF_MOD_TYPE_16APSK:
            printf("ModType:\t\t16APSK\n");
            break;
        case HI_UNF_MOD_TYPE_32APSK:
            printf("ModType:\t\t32APSK\n");
            break;
        default:
            printf("ModType:\t\tUnknown\n");
            break;
    }

    printf("FFTMode:\t\t");
    if (pstTer->enFFTMode <= 0 || pstTer->enFFTMode >= sizeof(acFETType)/sizeof(acFETType[0]))
    {
        printf("Unknown\n");
    }
    else
    {
        printf("%s\n", acFETType[pstTer->enFFTMode - 1]);
    }

    if (HI_UNF_TUNER_SIG_TYPE_DVB_T == enSigType)
    {
        switch (pstTer->enHierMod)
        {
            case HI_UNF_TUNER_FE_HIERARCHY_NO:
                printf("HierMod:\t\tNONE\n");
                break;
            case HI_UNF_TUNER_FE_HIERARCHY_ALHPA1:
                printf("HierMod:\t\tALHPA1\n");
                break;
            case HI_UNF_TUNER_FE_HIERARCHY_ALHPA2:
                printf("HierMod:\t\tALHPA2\n");
                break;
            case HI_UNF_TUNER_FE_HIERARCHY_ALHPA4:
                printf("HierMod:\t\tALHPA4\n");
                break;
            default:
                printf("HierMod:\t\tUnknown\n");
                break;
        }

        switch (pstTer->enTsPriority)
        {
            case HI_UNF_TUNER_TS_PRIORITY_NONE:
                printf("TsPriority:\t\tNONE\n");
                break;
            case HI_UNF_TUNER_TS_PRIORITY_HP:
                printf("TsPriority:\t\tHP\n");
                break;
            case HI_UNF_TUNER_TS_PRIORITY_LP:
                printf("TsPriority:\t\tLP\n");
                break;
            default:
                printf("TsPriority:\t\tUnknown\n");
                break;
        }
    }
    else if (HI_UNF_TUNER_SIG_TYPE_DVB_T2 == enSigType)
    {
        printf("Cell ID:\t\t%d\n", pstTer->u16CellID);
        printf("Network ID:\t\t%d\n", pstTer->u16NetworkID);
        printf("System ID:\t\t%d\n", pstTer->u16SystemID);
    }
}

static HI_VOID hi_tuner_getsignalinfo_isdbt(HI_UNF_TUNER_ISDB_T_SIGNALINFO_S *pstIsdbT)
{
    HI_UNF_TUNER_FE_HIERARCHY_E  enLayerHierMod = 0;
    HI_UNF_TUNER_FE_FECRATE_E    enLayerFECRate = 0;
    HI_UNF_MODULATION_TYPE_E     enLayerModType = 0;
    HI_U8 i = 0;

    printf("EmergencyFlag:\t\t%d\nPhaseShiftCorr:\t\t%d\nPartialFlag:\t\t%d\n",
            pstIsdbT->stISDBTTMCCInfo.u8EmergencyFlag,
            pstIsdbT->stISDBTTMCCInfo.u8PhaseShiftCorr,
            pstIsdbT->stISDBTTMCCInfo.u8PartialFlag);

    for (i = 0; i < 3; i++)
    {
        if (0 == i)
        {
            if (0 == pstIsdbT->unISDBTLayers.bits.u8LayerAExist)
            {
                printf("LayerA is not exist.\n");
                continue;
            }
            else
            {
                printf("LayerA info:\n");
                printf("\tLayerSegNum:\t%d\n",pstIsdbT->stISDBTTMCCInfo.stIsdbtLayersAInfoBits.u8LayerSegNum);
                enLayerModType = pstIsdbT->stISDBTTMCCInfo.stIsdbtLayersAInfoBits.enLayerModType;
                enLayerFECRate = pstIsdbT->stISDBTTMCCInfo.stIsdbtLayersAInfoBits.enLayerFECRate;
                enLayerHierMod = pstIsdbT->stISDBTTMCCInfo.stIsdbtLayersAInfoBits.enLayerHierMod;
            }
        }

        if (1 == i)
        {
            if (0 == pstIsdbT->unISDBTLayers.bits.u8LayerBExist)
            {
                printf("LayerB is not exist.\n");
                continue;
            }
            else
            {
                printf("LayerB info:\n");
                printf("\tLayerSegNum:\t%d\n",pstIsdbT->stISDBTTMCCInfo.stIsdbtLayersBInfoBits.u8LayerSegNum);
                enLayerModType = pstIsdbT->stISDBTTMCCInfo.stIsdbtLayersBInfoBits.enLayerModType;
                enLayerFECRate = pstIsdbT->stISDBTTMCCInfo.stIsdbtLayersBInfoBits.enLayerFECRate;
                enLayerHierMod = pstIsdbT->stISDBTTMCCInfo.stIsdbtLayersBInfoBits.enLayerHierMod;
            }
        }

        if (2 == i)
        {
            if (0 == pstIsdbT->unISDBTLayers.bits.u8LayerCExist)
            {
                printf("LayerC is not exist.\n");
                continue;
            }
            else
            {
                printf("LayerC info:\n");
                printf("\tLayerSegNum:\t%d\n",pstIsdbT->stISDBTTMCCInfo.stIsdbtLayersCInfoBits.u8LayerSegNum);
                enLayerModType = pstIsdbT->stISDBTTMCCInfo.stIsdbtLayersCInfoBits.enLayerModType;
                enLayerFECRate = pstIsdbT->stISDBTTMCCInfo.stIsdbtLayersCInfoBits.enLayerFECRate;
                enLayerHierMod = pstIsdbT->stISDBTTMCCInfo.stIsdbtLayersCInfoBits.enLayerHierMod;
            }
        }

        switch (enLayerModType)
        {
            case HI_UNF_MOD_TYPE_QPSK:
                printf("\tModType:\tQPSK\n");
                break;
            case HI_UNF_MOD_TYPE_QAM_16:
                printf("\tModType:\tQAM_16\n");
                break;
            case HI_UNF_MOD_TYPE_QAM_64:
                printf("\tModType:\tQAM_64\n");
                break;
            case HI_UNF_MOD_TYPE_QAM_128:
                printf("\tModType:\tQAM_128\n");
                break;
            case HI_UNF_MOD_TYPE_QAM_256:
                printf("\tModType:\tQAM_256\n");
                break;
            default:
                printf("\tModType:\tUnknown\n");
                break;
        }

        hi_tuner_getsignalinfo_fec(HI_UNF_TUNER_SIG_TYPE_ISDB_T, enLayerFECRate);

        switch (enLayerHierMod)
        {
            case HI_UNF_TUNER_FE_HIERARCHY_NO:
                printf("\tHierMod:\tNONE\n");
                break;
            case HI_UNF_TUNER_FE_HIERARCHY_ALHPA1:
                printf("\tHierMod:\tALHPA1\n");
                break;
            case HI_UNF_TUNER_FE_HIERARCHY_ALHPA2:
                printf("\tHierMod:\tALHPA2\n");
                break;
            case HI_UNF_TUNER_FE_HIERARCHY_ALHPA4:
                printf("\tHierMod:\tALHPA4\n");
                break;
            default:
                printf("\tHierMod:\tUnknown\n");
                break;
        }
    }

}

HI_VOID hi_tuner_getsignalinfo(char * para)
{
    HI_S32 s32Ret = 0;
    HI_UNF_TUNER_SIGNALINFO_S stInfo;
    HI_U32 au32BER[3];
    HI_U32 u32SNR;
    HI_U32 u32SignalStrength;
    HI_U32 u32SignalQuality;

    s32Ret = HI_UNF_TUNER_GetBER(s_s32TunerPort, au32BER);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("HI_UNF_TUNER_GetBER failed\n");
    }
    else
    {
        HI_TUNER_INFO("BER:\t\t\t%d.%03d*(E-%d)\n", au32BER[0], au32BER[1], au32BER[2]);
    }
    s32Ret = HI_UNF_TUNER_GetSNR(s_s32TunerPort, &u32SNR);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("HI_UNF_TUNER_GetSNR failed\n");
    }
    else
    {
        HI_TUNER_INFO("SNR:\t\t\t%d\n", u32SNR);
    }

    s32Ret = HI_UNF_TUNER_GetSignalStrength(s_s32TunerPort, &u32SignalStrength);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("HI_UNF_TUNER_GetSignalStrength failed\n");
    }
    else
    {
        HI_TUNER_INFO("Signal Strength:\t%d%%\n", u32SignalStrength);
    }

    s32Ret = HI_UNF_TUNER_GetSignalQuality(s_s32TunerPort, &u32SignalQuality);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("HI_UNF_TUNER_GetSignalQuality failed\n");
    }
    else
    {
        HI_TUNER_INFO("Signal Quality:\t\t%d%%\n", u32SignalQuality);
    }

    if ((HI_UNF_TUNER_SIG_TYPE_SAT <= s_stConnectPara[s_s32TunerPort].enSigType) ||
        (HI_UNF_TUNER_SIG_TYPE_BUTT > s_stConnectPara[s_s32TunerPort].enSigType))
    {
        s32Ret = HI_UNF_TUNER_GetSignalInfo(s_s32TunerPort, &stInfo);
        if (s32Ret != HI_SUCCESS)
        {
            HI_TUNER_ERR("call HI_UNF_TUNER_GetSignalInfo failed.\n");
            return;
        }

        switch (stInfo.enSigType)
        {
            case HI_UNF_TUNER_SIG_TYPE_CAB:
            case HI_UNF_TUNER_SIG_TYPE_J83B:
                HI_TUNER_INFO("Signal type:\t\tCable\n");
                break;
            case HI_UNF_TUNER_SIG_TYPE_DVB_T:
                HI_TUNER_INFO("Signal type:\t\tDVB-T\n");
                break;
            case HI_UNF_TUNER_SIG_TYPE_DVB_T2:
                HI_TUNER_INFO("Signal type:\t\tDVB-T2\n");
                break;
            case HI_UNF_TUNER_SIG_TYPE_ISDB_T:
            case HI_UNF_TUNER_SIG_TYPE_ATSC_T:
            case HI_UNF_TUNER_SIG_TYPE_DTMB:
                HI_TUNER_INFO("Signal type:\t\tTerrestrial\n");
                break;
            case HI_UNF_TUNER_SIG_TYPE_SAT:
                HI_TUNER_INFO("Signal type:\t\tSatellite\n");
                break;
            case HI_UNF_TUNER_SIG_TYPE_BUTT:
            default:
                HI_TUNER_INFO("Signal type:\t\tUnknown\n");
                break;
        }

        if (HI_UNF_TUNER_SIG_TYPE_SAT == stInfo.enSigType)
        {
            hi_tuner_getsignalinfo_sat(&stInfo.unSignalInfo.stSat);
        }
        else if (HI_UNF_TUNER_SIG_TYPE_ISDB_T == stInfo.enSigType)
        {
            hi_tuner_getsignalinfo_isdbt(&stInfo.unSignalInfo.stIsdbT);
        }
        else if (HI_UNF_TUNER_SIG_TYPE_DVB_T <= stInfo.enSigType
                && HI_UNF_TUNER_SIG_TYPE_DTMB >= stInfo.enSigType)
        {
            hi_tuner_getsignalinfo_ter(stInfo.enSigType, &stInfo.unSignalInfo.stTer);
        }
    }
}

/* set plp id */
HI_VOID hi_tuner_setplpid(char * plpid)
{
    HI_U32 u32PLPID = 0,u32ComPlpId = 0,u32Combination = 0;
    HI_S32 s32Return;
    HI_UNF_AVPLAY_STOP_OPT_S    stStop;
    HI_UNF_VCODEC_ATTR_S        stVdecAttr;

    if (plpid == HI_NULL_PTR)
    {
        return;
    }

    sscanf(plpid, "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d" ,&u32PLPID, &u32ComPlpId, &u32Combination);

    HI_UNF_TUNER_SetPLPMode(s_s32TunerPort,0);
    if (HI_SUCCESS != HI_UNF_TUNER_SetPLPID(s_s32TunerPort, (HI_U8)u32PLPID))
    {
        printf("set plpid %d failed.\n", u32PLPID);
    }
    else
    {
        printf("set plpid %d succeed.\n", u32PLPID);
    }

    if (HI_SUCCESS != HI_UNF_TUNER_SetCommonPLPID(s_s32TunerPort, (HI_U8)u32ComPlpId))
    {
        printf("set common plp id %d failed.\n", u32ComPlpId);
    }
    else
    {
        printf("set common plp id %d succeed.\n", u32ComPlpId);
    }

    if (HI_SUCCESS != HI_UNF_TUNER_SetCommonPLPCombination(s_s32TunerPort, (HI_U8)u32Combination))
    {
        printf("set common plp combination %d failed.\n", u32Combination);
    }
    else
    {
        printf("set common plp combination %d succeed.\n", u32Combination);
    }

    stStop.enMode = HI_UNF_AVPLAY_STOP_MODE_STILL;
    stStop.u32TimeoutMs = 0;

    s32Return= HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &stStop);
    if (s32Return != HI_SUCCESS )
    {
        HI_TUNER_ERR("call HI_UNF_AVPLAY_Stop failed.\n");
        return ;
    }

    HIADP_Search_Init();
    s32Return = HIADP_Search_GetAllPmt(0, &s_ProgTbl[s_s32TunerPort]);
    if (HI_SUCCESS != s32Return)
    {
        HI_TUNER_ERR("call HIADP_Search_GetAllPmt failed\n");
        //return;
    }
    else
    {
        HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_VDEC, &stVdecAttr);
        stVdecAttr.enMode = HI_UNF_VCODEC_MODE_NORMAL;
        stVdecAttr.enType = s_ProgTbl[s_s32TunerPort]->proginfo->VideoType;
        stVdecAttr.u32ErrCover = 80;
        stVdecAttr.u32Priority = HI_UNF_VCODEC_MAX_PRIORITY;
        stVdecAttr.bOrderOutput = HI_FALSE;
        s32Return = HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_VDEC, &stVdecAttr);
        if (HI_SUCCESS != s32Return)
        {
            HI_TUNER_ERR("call HI_UNF_AVPLAY_SetAttr_VDEC failed.\n");
            HI_UNF_AVPLAY_Destroy(hAvplay);
            HI_UNF_AVPLAY_DeInit();
            dev_deinit();
            return;
        }
    }
}


HI_VOID hi_tuner_setlnbpower(char * pPower)
{
    if (pPower == HI_NULL_PTR)
    {
        return;
    }

    if (HI_SUCCESS != HI_UNF_TUNER_SetLNBPower(s_s32TunerPort, atoi(pPower)))
    {
        HI_TUNER_ERR("Set LNB power fail:%d\n", atoi(pPower));
    }
}


/* Configurate LNB parameter */
HI_VOID hi_tuner_setlnb(char * freq)
{
    HI_UNF_TUNER_FE_LNB_TYPE_E enType;
    HI_U32 u32LowLOFreq  = 0;
    HI_U32 u32HighLOFreq = 0;
    HI_UNF_TUNER_FE_LNB_BAND_E enBand;
    HI_UNF_TUNER_FE_LNB_CONFIG_S stLNBConfig;
    HI_U32 u32SCRNO = 0;
    HI_U32 u32IFCenterFreq_MHz = 0;
    HI_UNF_TUNER_SATPOSITION_E enSatPosn = HI_UNF_TUNER_SATPOSN_A;

    if (freq == HI_NULL_PTR)
    {
        return;
    }

    sscanf(freq, "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d",
           (HI_U32*)&enType, &u32LowLOFreq, &u32HighLOFreq, (HI_U32*)&enBand, &u32SCRNO, &u32IFCenterFreq_MHz, (HI_U32*)&enSatPosn);
    HI_TUNER_INFO("hi_tuner_setlnb Type %d, Low LO:%dMHz, High LO: %dMHz, Band %d \n",
           enType, u32LowLOFreq, u32HighLOFreq, enBand);

    if (s_stConnectPara[s_s32TunerPort].enSigType == HI_UNF_TUNER_SIG_TYPE_SAT)
    {
        stLNBConfig.enLNBType = enType;
        stLNBConfig.u32LowLO  = u32LowLOFreq;
        stLNBConfig.u32HighLO = u32HighLOFreq;
        stLNBConfig.enLNBBand = enBand;
        stLNBConfig.u8UNIC_SCRNO = u32SCRNO;
        stLNBConfig.u32UNICIFFreqMHz = u32IFCenterFreq_MHz;
        stLNBConfig.enSatPosn = enSatPosn;
    }
    else
    {
        HI_TUNER_WARN("Your Signal Type unsupport lnb config.\n");
    }

    if (HI_SUCCESS != HI_UNF_TUNER_SetLNBConfig(s_s32TunerPort, &stLNBConfig))
    {
        HI_TUNER_ERR("call HI_UNF_TUNER_SetLNBConfig failed.\n");
    }
}



/* If your diseqc device need config polarization and 22K, you need registe the callback */
HI_VOID hi_tuner_diseqc_set(HI_U32 u32TunerId, HI_UNF_TUNER_FE_POLARIZATION_E enPolar,
                                                            HI_UNF_TUNER_FE_LNB_22K_E enLNB22K)
{
}

static struct timeval s_stStart, s_stStop;
static HI_S32 s_s32TPNum = 0;
static HI_UNF_TUNER_SAT_TPINFO_S s_astTP[400];

HI_VOID hi_tuner_blindscan_notify(HI_U32 u32TunerId, HI_UNF_TUNER_BLINDSCAN_EVT_E enEVT, HI_UNF_TUNER_BLINDSCAN_NOTIFY_U* punNotify)
{
    HI_S32 i = 0;
    HI_U32 u32TimeUse;

    switch (enEVT)
    {
        case HI_UNF_TUNER_BLINDSCAN_EVT_STATUS:
            if (HI_UNF_TUNER_BLINDSCAN_STATUS_FAIL == *(punNotify->penStatus))
            {
                HI_TUNER_ERR("Scan fail.\n");
            }
            else if ((HI_UNF_TUNER_BLINDSCAN_STATUS_FINISH == *(punNotify->penStatus))
                        || (HI_UNF_TUNER_BLINDSCAN_STATUS_QUIT == *(punNotify->penStatus)))
            {

                gettimeofday(&s_stStop, NULL );
                u32TimeUse = 1000000 * (s_stStop.tv_sec - s_stStart.tv_sec ) + s_stStop.tv_usec - s_stStart.tv_usec;
                u32TimeUse /= 1000000;
                HI_TUNER_INFO("100");
                putchar('%');
                HI_TUNER_INFO(" done!\n");
                HI_TUNER_INFO("Scan over, find %d TP, use %ds.\n", s_s32TPNum, u32TimeUse);
                for (i=0; i<s_s32TPNum; i++)
                {
                    HI_TUNER_INFO("%03d %d %d %d %d\n", i, s_astTP[i].u32Freq, s_astTP[i].u32SymbolRate, s_astTP[i].enPolar, \
                        s_astTP[i].cbs_reliablity/*, s_astTP[i].agc_h8*/);
                }
            }
            break;
        case HI_UNF_TUNER_BLINDSCAN_EVT_PROGRESS:
            HI_TUNER_INFO("%d",*(punNotify->pu16ProgressPercent));
            putchar('%');
            HI_TUNER_INFO(" done!\n");
            break;
        case HI_UNF_TUNER_BLINDSCAN_EVT_NEWRESULT:
            if(s_s32TPNum < sizeof(s_astTP) / sizeof(HI_UNF_TUNER_SAT_TPINFO_S))
            {
                s_astTP[s_s32TPNum] = *(punNotify->pstResult);
                s_s32TPNum++;
            }
            else
            {
                HI_TUNER_WARN("Too many channels!\n");
            }
            break;
        default:
            break;
    }
}

/* Blind scan */
HI_VOID hi_tuner_blindscan(char * pPara)
{
    HI_S32 s32Ret = 0;
    HI_S32 s32BlindScanType;
    HI_U32 u32StartFreq;
    HI_U32 u32StopFreq;
    HI_UNF_TUNER_FE_POLARIZATION_E enPolar;
    HI_UNF_TUNER_FE_LNB_22K_E enLNB22K;
    HI_UNF_TUNER_BLINDSCAN_PARA_S stBlindScanPara;

    if (pPara == HI_NULL_PTR)
    {
        return;
    }

    sscanf(pPara, "%d", (HI_S32*)&s32BlindScanType);
    if (1 == s32BlindScanType)
    {
        sscanf(pPara, "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d",
               (HI_S32*)&s32BlindScanType, (HI_S32*)&enPolar, (HI_S32*)&enLNB22K, &u32StartFreq, &u32StopFreq);
        HI_TUNER_INFO("hi_tuner_blindscan Type:%d, Polar %d, 22K %d,  %dkHz - %dkHz\n",
               s32BlindScanType, enPolar, enLNB22K, u32StartFreq, u32StopFreq);
    }

    s_s32TPNum = 0;
    gettimeofday(&s_stStart, NULL );

    if (s_stConnectPara[s_s32TunerPort].enSigType == HI_UNF_TUNER_SIG_TYPE_SAT)
    {
        if (0 == s32BlindScanType)
        {
            /* Auto */
            stBlindScanPara.enMode = HI_UNF_TUNER_BLINDSCAN_MODE_AUTO;
            /* If your diseqc device need config polarization and 22K, you need registe the callback */
            stBlindScanPara.unScanPara.stSat.pfnDISEQCSet = hi_tuner_diseqc_set;
            stBlindScanPara.unScanPara.stSat.pfnEVTNotify = hi_tuner_blindscan_notify;
        }
        else
        {
            stBlindScanPara.enMode = HI_UNF_TUNER_BLINDSCAN_MODE_MANUAL;
            stBlindScanPara.unScanPara.stSat.enPolar  = enPolar;
            stBlindScanPara.unScanPara.stSat.enLNB22K = enLNB22K;
            stBlindScanPara.unScanPara.stSat.u32StartFreq = u32StartFreq;
            stBlindScanPara.unScanPara.stSat.u32StopFreq = u32StopFreq;
            stBlindScanPara.unScanPara.stSat.pfnDISEQCSet = HI_NULL;
            stBlindScanPara.unScanPara.stSat.pfnEVTNotify = hi_tuner_blindscan_notify;
        }
    }

    s32Ret = HI_UNF_TUNER_BlindScanStart(s_s32TunerPort, &stBlindScanPara);
    if (s32Ret != HI_SUCCESS)
    {
        HI_TUNER_ERR("call HI_UNF_TUNER_BlindScanStart failed.\n");
        return;
    }
}

/* Stop blind scan */
HI_VOID hi_tuner_blindscan_stop(char * arg)
{
    HI_UNF_TUNER_BlindScanStop(s_s32TunerPort);
}

HI_VOID hi_tuner_ter_scan(char * arg)
{
    HI_S32 s32Ret = 0;
    HI_UNF_TUNER_TER_SCAN_PARA_S stTerScanPara;
    HI_U32 u32Frequency = 0,u32BandWidth = 0,u32Lite = 0;
    //HI_U32 i = 0;

    if (arg == HI_NULL_PTR)
    {
        return;
    }

    sscanf(arg, "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d",
               (HI_U32*)&u32Frequency, (HI_U32*)&u32BandWidth, (HI_U32*)&u32Lite);
    printf("hi_tuner_ter_scan u32Frequency %d, u32BandWidth %d, u32Lite  %d\n",
           u32Frequency, u32BandWidth, u32Lite);

    memset(&stTerScanPara,0,sizeof(HI_UNF_TUNER_TER_SCAN_PARA_S));

    stTerScanPara.stTer.u32Frequency = u32Frequency * 1000;
    stTerScanPara.stTer.u32BandWidth = u32BandWidth;
    stTerScanPara.stTer.enScanMode = HI_UNF_TUNER_TER_SCAN_DVB_T_T2_ALL;
    stTerScanPara.stTer.bScanLite = u32Lite;

    s32Ret = HI_UNF_TUNER_TerScanStart(s_s32TunerPort, &stTerScanPara);
    if (s32Ret != HI_SUCCESS)
    {
        HI_TUNER_ERR("call HI_UNF_TUNER_TerScanStart failed.\n");
        return;
    }

    /*printf("\n-----------------------scan result-------------------------\n");
    if(stTerScanPara.enChanArray[0].u8DVBTMode)   //dvb-t
    {
        printf("signal:DVB-T\n");
        printf("program number:%d\n",stTerScanPara.u32ChanNum);
    }
    else
    {
        printf("signal:DVB-T2\n");
        if(HI_UNF_TUNER_TER_MIXED_CHANNEL == stTerScanPara.enChanArray[0].enChannelMode)
        {
            printf("mixed channel,there are base and lite signals\n");
        }
        else
        {
            if(HI_UNF_TUNER_TER_MODE_BASE== stTerScanPara.enChanArray[0].enChannelMode)
                printf("pure channel,there is only base signal\n");
            else
                printf("pure channel,there is only lite signal\n");
        }

        printf("program number:%d\n",stTerScanPara.u32ChanNum);

        printf("plp index       plp id      common plp id       combination\n");
        for(i=0;i < stTerScanPara.u32ChanNum;i++)
        {
            printf("%d          %d          %d          %d\n",stTerScanPara.enChanArray[i].u8PlpIndex,\
                stTerScanPara.enChanArray[i].u8PlpId,stTerScanPara.enChanArray[i].u8CommId,\
                stTerScanPara.enChanArray[i].u8Combination);
        }
    }*/
}

/*sample data*/
HI_VOID hi_tuner_sample_data(char * arg)
{
    HI_S32 s32Ret = 0;
    HI_U32 u32SRC = 0;
    HI_U32 u32Len = 0;
    HI_UNF_TUNER_SAMPLE_DATALEN_E enDataLen = HI_UNF_TUNER_SAMPLE_DATALEN_BUTT;
    HI_U32 u32SpecData[2048];
    HI_UNF_TUNER_SAMPLE_DATA_S stConstData[2048];
    FILE *fp_data = NULL;
    HI_S32 i = 0;
    char s8Buf[100] = {0};

    if (arg == HI_NULL_PTR)
    {
        return;
    }

    sscanf(arg, "%d" TEST_ARGS_SPLIT "%d", \
           &u32SRC, &u32Len);

    switch (u32Len)
    {
        case 32:
            enDataLen = HI_UNF_TUNER_SAMPLE_DATALEN_32;
            break;
        case 64:
            enDataLen = HI_UNF_TUNER_SAMPLE_DATALEN_64;
            break;
        case 128:
            enDataLen = HI_UNF_TUNER_SAMPLE_DATALEN_128;
            break;
        case 256:
            enDataLen = HI_UNF_TUNER_SAMPLE_DATALEN_256;
            break;
        case 512:
            enDataLen = HI_UNF_TUNER_SAMPLE_DATALEN_512;
            break;
        case 1024:
            enDataLen = HI_UNF_TUNER_SAMPLE_DATALEN_1024;
            break;
        case 2048:
        default:
            enDataLen = HI_UNF_TUNER_SAMPLE_DATALEN_2048;
            u32Len = 2048;
            break;
    }

    if (0 == u32SRC)//AD
    {
        s32Ret = HI_UNF_TUNER_GetSpectrumData(s_s32TunerPort, enDataLen, u32SpecData);

        if (s32Ret != HI_SUCCESS)
        {
            HI_TUNER_ERR("call HI_UNF_TUNER_GetSpectrumData failed.\n");
            return;
        }

        HI_TUNER_INFO("AD data sample over !\n");

        fp_data = fopen("AD_data.txt", "w");

        if (fp_data)
        {
            HI_TUNER_INFO("Column:2\n");
            s32Ret = fprintf(fp_data, "\r\nColumn:2\r\n");
            for (i = 0; i < u32Len; i++)
            {
                HI_TUNER_INFO("%d,%d\n", i,u32SpecData[i]);
                s32Ret = fprintf(fp_data, "%d,%d\r\n", i,u32SpecData[i]);
                if (s32Ret < 0)
                {
                    HI_TUNER_ERR("fprintf failed.\n");
                    fclose(fp_data);
                    return;
                }
            }
        }
        else
        {
            HI_TUNER_ERR("open file failed.\n");
            return;
        }

        fclose(fp_data);
        HI_TUNER_INFO("AD_DATA file closed!\n");
    }
    else if(1 == u32SRC)//EQU
    {
        s32Ret = HI_UNF_TUNER_GetConstellationData(s_s32TunerPort, enDataLen, stConstData);

        if (s32Ret != HI_SUCCESS)
        {
            HI_TUNER_ERR("call HI_UNF_TUNER_GetConstellationData failed.\n");
            return;
        }

        fp_data = fopen("EQU_data.txt", "w");

        if (fp_data)
        {
            HI_TUNER_INFO("\r\nColumn:2\n");
            s32Ret = fprintf(fp_data, "Column:2\r\n");
            if (s32Ret < 0)
            {
                HI_TUNER_ERR("fprintf failed.\n");
                fclose(fp_data);
                return;
            }

            for (i = 0; i < u32Len; i++)
            {
                HI_TUNER_INFO("%d,%d\n", stConstData[i].s32DataIP, stConstData[i].s32DataQP);
                s32Ret = fprintf(fp_data, "%d,%d\r\n", stConstData[i].s32DataIP, stConstData[i].s32DataQP);
                if (s32Ret < 0)
                {
                    HI_TUNER_ERR("fprintf failed.\n");
                    fclose(fp_data);
                    return;
                }
            }
        }
        else
        {
            HI_TUNER_ERR("open file failed.\n");
            return;
        }

        fclose(fp_data);
        HI_TUNER_INFO("EQU_DATA file closed!\n");
    }
    else
    {
        memset(s8Buf,0,sizeof(s8Buf));
        snprintf(s8Buf,sizeof(s8Buf),"%s %d %d %s","echo cirplot ",s_s32TunerPort,u32Len," > /proc/msp/tuner\n");
        HI_TUNER_INFO("%s\n",s8Buf);
        system(s8Buf);
    }
}

#ifdef DISEQC_SUPPORT
/* Switch test, for DVB-S/S2 */
HI_VOID hi_tuner_switch(char * pSwitch)
{
    HI_S32 s32SwitchType;
    HI_S32 s32Port;
    HI_UNF_TUNER_FE_POLARIZATION_E enPolar;
    HI_UNF_TUNER_FE_LNB_22K_E enLNB22K;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_TUNER_DISEQC_SWITCH4PORT_S st4Port;
    HI_UNF_TUNER_DISEQC_SWITCH16PORT_S st16Port;

    if (pSwitch == HI_NULL_PTR)
    {
        return;
    }

    sscanf(pSwitch, "%d", (HI_S32*)&s32SwitchType);
    if (s32SwitchType == 3)
    {
        sscanf(pSwitch, "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d",
               (HI_S32*)&s32SwitchType, (HI_S32*)&s32Port, (HI_S32*)&enPolar, (HI_S32*)&enLNB22K);
        HI_TUNER_INFO("hi_tuner_switch Type %d, Port:%d, Polar: %d, LNB22K %d \n",
               s32SwitchType, s32Port, enPolar, enLNB22K);
    }
    else if (s32SwitchType < 5)
    {
        s32Ret = sscanf(pSwitch, "%d" TEST_ARGS_SPLIT "%d", (HI_S32*)&s32SwitchType, (HI_S32*)&s32Port);
        HI_TUNER_INFO("hi_tuner_switch Type %d, Port:%d \n", s32SwitchType, s32Port);
    }
    else if (s32SwitchType > 7)
    {
        HI_TUNER_WARN("Error SwitchType!\n");
        return;
    }

    switch (s32SwitchType)
    {
        case 0:
            s32Ret = HI_UNF_TUNER_Switch012V(s_s32TunerPort, (HI_UNF_TUNER_SWITCH_0_12V_E)s32Port);
            break;
        case 1:
            s32Ret = HI_UNF_TUNER_SwitchToneBurst(s_s32TunerPort, (HI_UNF_TUNER_SWITCH_TONEBURST_E)s32Port);
            break;
        case 2:
            s32Ret = HI_UNF_TUNER_Switch22K(s_s32TunerPort, (HI_UNF_TUNER_SWITCH_22K_E)s32Port);
            break;
        case 3:
            st4Port.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
            st4Port.enPort   = (HI_UNF_TUNER_DISEQC_SWITCH_PORT_E)s32Port;
            st4Port.enPolar  = enPolar;
            st4Port.enLNB22K = enLNB22K;
            s32Ret = HI_UNF_TUNER_DISEQC_Switch4Port(s_s32TunerPort, &st4Port);
            break;
        case 4:
            st16Port.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
            st16Port.enPort = (HI_UNF_TUNER_DISEQC_SWITCH_PORT_E)s32Port;
            s32Ret = HI_UNF_TUNER_DISEQC_Switch16Port(s_s32TunerPort, &st16Port);
            break;
        case 5:
            s32Ret = HI_UNF_TUNER_DISEQC_Reset(s_s32TunerPort, HI_UNF_TUNER_DISEQC_LEVEL_1_X);
            break;
        case 6:
            s32Ret = HI_UNF_TUNER_DISEQC_Standby(s_s32TunerPort, HI_UNF_TUNER_DISEQC_LEVEL_1_X);
            break;
        case 7:
            s32Ret = HI_UNF_TUNER_DISEQC_WakeUp(s_s32TunerPort, HI_UNF_TUNER_DISEQC_LEVEL_1_X);
            break;
    }

    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("Switch control failed.\n");
    }
}

/* Motor control test, for DVB-S/S2 */
HI_VOID hi_tuner_motor(char * pPara)
{
    HI_S32 s32CtrlType;
    HI_U32 u32Para1;
    HI_U32 u32Para2;
    HI_U32 u32Para3;
    HI_UNF_TUNER_DISEQC_POSITION_S stPos;
    HI_UNF_TUNER_DISEQC_LIMIT_S stLimit;
    HI_UNF_TUNER_DISEQC_MOVE_S stMove;
    HI_UNF_TUNER_DISEQC_USALS_PARA_S stUSALS;
    HI_UNF_TUNER_DISEQC_USALS_ANGULAR_S stAngular;
    HI_UNF_TUNER_DISEQC_RECALCULATE_S stRecal;
    HI_S32 s32Ret = HI_SUCCESS;

    if (pPara == HI_NULL_PTR)
    {
        return;
    }

    sscanf(pPara, "%d", (HI_S32*)&s32CtrlType);
    if (s32CtrlType <= 2)
    {
        sscanf(pPara, "%d" TEST_ARGS_SPLIT "%d", (HI_S32*)&s32CtrlType, (HI_S32*)&u32Para1);
        HI_TUNER_INFO("hi_tuner_motor Ctrl %d, Para1:%d\n", s32CtrlType, u32Para1);
    }
    else if (s32CtrlType == 3)
    {
        sscanf(pPara, "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d",
               (HI_S32*)&s32CtrlType, &u32Para1, &u32Para2);
        HI_TUNER_INFO("hi_tuner_motor Ctrl %d, Para1:%d, Para2:%d\n", s32CtrlType, u32Para1, u32Para2);
    }
    else if ((s32CtrlType == 5) || (s32CtrlType == 6))
    {
        sscanf(pPara, "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d",
               (HI_S32*)&s32CtrlType, &u32Para1, &u32Para2, &u32Para3);
        HI_TUNER_INFO("hi_tuner_motor Ctrl %d, Para1:%d, Para2:%d, Para3:%d\n", s32CtrlType, u32Para1, u32Para2, u32Para3);
    }
    else if (s32CtrlType == 7)
    {
        sscanf(pPara, "%d" TEST_ARGS_SPLIT "%d",
               (HI_S32*)&s32CtrlType, &u32Para1);
        HI_TUNER_INFO("hi_tuner_motor Ctrl %d, Para1:%d\n", s32CtrlType, u32Para1);
    }
    else if (s32CtrlType == 4)
    {
        s32Ret = sscanf(pPara, "%d", (HI_S32*)&s32CtrlType);
        HI_TUNER_INFO("hi_tuner_motor Ctrl %d\n", s32CtrlType);
    }
    else
    {
        HI_TUNER_WARN("Error Ctrl type!\n");
        return;
    }

    switch (s32CtrlType)
    {
        case 0:
            stPos.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
            stPos.u32Pos = u32Para1;
            s32Ret = HI_UNF_TUNER_DISEQC_StorePos(s_s32TunerPort, &stPos);
            break;
        case 1:
            stPos.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
            stPos.u32Pos = u32Para1;
            s32Ret = HI_UNF_TUNER_DISEQC_GotoPos(s_s32TunerPort, &stPos);
            break;
        case 2:
            stLimit.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
            stLimit.enLimit = (HI_UNF_TUNER_DISEQC_LIMIT_E)u32Para1;
            s32Ret = HI_UNF_TUNER_DISEQC_SetLimit(s_s32TunerPort, &stLimit);
            break;
        case 3:
            stMove.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
            stMove.enDir = (HI_UNF_TUNER_DISEQC_MOVE_DIR_E)u32Para1;
            stMove.enType = (HI_UNF_TUNER_DISEQC_MOVE_TYPE_E)u32Para2;
            s32Ret = HI_UNF_TUNER_DISEQC_Move(s_s32TunerPort, &stMove);
            break;
        case 4:
            s32Ret = HI_UNF_TUNER_DISEQC_Stop(s_s32TunerPort, HI_UNF_TUNER_DISEQC_LEVEL_1_X);
            break;
        case 5:
            stUSALS.u16LocalLongitude = (HI_U16)u32Para1;
            stUSALS.u16LocalLatitude = (HI_U16)u32Para2;
            stUSALS.u16SatLongitude = (HI_U16)u32Para3;
            s32Ret = HI_UNF_TUNER_DISEQC_CalcAngular(s_s32TunerPort, &stUSALS);
            HI_TUNER_INFO("Angular: %02x, %02x\n", (HI_U8)(stUSALS.u16Angular>>8), (HI_U8)stUSALS.u16Angular);
            stAngular.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
            stAngular.u16Angular = stUSALS.u16Angular;
            s32Ret |= HI_UNF_TUNER_DISEQC_GotoAngular(s_s32TunerPort, &stAngular);
            break;
        case 6:
            stRecal.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
            stRecal.u8Para1 = (HI_U8)u32Para1;
            stRecal.u8Para2 = (HI_U8)u32Para2;
            stRecal.u8Para3 = (HI_U8)u32Para3;
            s32Ret = HI_UNF_TUNER_DISEQC_Recalculate(s_s32TunerPort, &stRecal);
            break;
        case 7:
            stAngular.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
            stAngular.u16Angular = u32Para1;
            s32Ret = HI_UNF_TUNER_DISEQC_GotoAngular(s_s32TunerPort, &stAngular);
            break;
    }

    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("Motor control failed.\n");
    }
}

HI_VOID unicable_check_status(HI_U32 u32TunerId, HI_UNF_TUNER_UNICABLE_SCAN_USER_BAND_EVT_E enEvent,HI_UNF_TUNER_UNICABLE_SCAN_USER_BAND_NOTIFY_S *pstNotify)
{
    HI_UNF_TUNER_SCR_UB_S astUBInfo[8];
    HI_U32 u32UBNum;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 i = 0;


    if(enEvent == HI_UNF_TUNER_UNICABLE_SCAN_EVT_STATUS)
    {
        switch(*(pstNotify->penStatus))
        {
            case HI_UNF_TUNER_UNICABLE_SCAN_STATUS_IDLE:
                printf("@@@@@@@@@@@@@@@@@@@scan idle.\n");
                break;
            case HI_UNF_TUNER_UNICABLE_SCAN_STATUS_SCANNING:
                printf("@@@@@@@@@@@@@@@@@@@scan scanning.\n");
                break;
            case HI_UNF_TUNER_UNICABLE_SCAN_STATUS_FINISH:
                printf("@@@@@@@@@@@@@@@@@@@scan finish.\n");

                s32Ret = HI_UNF_TUNER_UNICABLE_GetUserBandsInfo(u32TunerId, (HI_UNF_TUNER_SCR_UB_S **)&astUBInfo, &u32UBNum);
                if (HI_SUCCESS != s32Ret)
                {
                    printf("Get UB info failed.\n");
                }
                else
                {
                    printf("Total %d UB:\n", u32UBNum);
                    for (i = 0; i < u32UBNum; i++)
                    {
                        printf("%d: %dMHz\n", i, astUBInfo[i].s32CenterFreq);
                    }
                }
                break;
            case HI_UNF_TUNER_UNICABLE_SCAN_STATUS_QUIT:
                printf("@@@@@@@@@@@@@@@@@@@scan quit.\n");
                break;
            case HI_UNF_TUNER_UNICABLE_SCAN_STATUS_FAIL:
                printf("@@@@@@@@@@@@@@@@@@@scan fail.\n");
                break;
            default:
                break;
        }
    }
    else if(enEvent == HI_UNF_TUNER_UNICABLE_SCAN_EVT_PROGRESS)
    {
        printf("%d%%\n", *(pstNotify->pu16ProgressPercent));
    }
    return;
}

HI_VOID hi_tuner_unicable_scan(char * pPara)
{
    HI_UNF_TUNER_UNICABLE_SCAN_PARA_S stScanPara;
    HI_S32 s32UnicType;
    HI_U32 u32SCRNO,u32Para;

    if (pPara == HI_NULL_PTR)
    {
        return;
    }

    sscanf(pPara, "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d", (HI_S32*)&s32UnicType,(HI_U32*)&u32SCRNO,(HI_U32*)&u32Para);
    stScanPara.pfnEVTNotify = unicable_check_status;
    switch(s32UnicType)
    {
        case 0:
            HI_UNF_TUNER_UNICABLE_ScanUserBands(s_s32TunerPort, stScanPara);
            break;
        case 1:
            HI_UNF_TUNER_UNICABLE_ExitScanUserBands(s_s32TunerPort);
        default:
            break;
    }
}

#endif /* DISEQC_SUPPORT */

/* Standby test */
HI_VOID hi_tuner_standby(char * pPara)
{
    HI_U32 u32Para;
    HI_S32 s32Ret = HI_SUCCESS;

    if (pPara == HI_NULL_PTR)
    {
        return;
    }

    sscanf(pPara, "%d", (HI_S32*)&u32Para);
    HI_TUNER_INFO("hi_tuner_standby %d\n", u32Para);

    if (0 == u32Para)
    {
        s32Ret = HI_UNF_TUNER_WakeUp(s_s32TunerPort);
        if (HI_SUCCESS != s32Ret)
        {
            HI_TUNER_ERR("Tuner wake up failed.\n");
        }
    }
    else
    {
        s32Ret = HI_UNF_TUNER_Standby(s_s32TunerPort);
        if (HI_SUCCESS != s32Ret)
        {
            HI_TUNER_ERR("Tuner standby failed.\n");
        }
    }
}

/*play program*/
HI_VOID hi_tuner_play(char * pPara)
{
    HI_S32 s32Ret;
    HI_S32 s32ProgNum = 1;
    HI_HANDLE hDmxVidChn = HI_INVALID_HANDLE;
    HI_HANDLE hDmxAudChn = HI_INVALID_HANDLE;
    HI_UNF_DMX_SCRAMBLED_FLAG_E enScrambleFlag;
    PMT_COMPACT_TBL *ProgTbl = s_ProgTbl[s_s32TunerPort];

    if (ProgTbl == HI_NULL)
    {
        HI_TUNER_INFO("Can't find a PMT(Program Map Table) yet.\n");
        return;
    }

    if (pPara == HI_NULL_PTR)
    {
        /* Select 1 by default */
        s32ProgNum = 1;
    }
    else
    {
        s32Ret = sscanf(pPara, "%d", &s32ProgNum);
        if (s32ProgNum <= 0 || s32ProgNum > ProgTbl->prog_num)
        {
            HI_TUNER_ERR("Invalid input %d\nMax Program number is %d\n", s32ProgNum, ProgTbl->prog_num);
            return;
        }
    }

    //Translate the number into the index of s_ProgTbl->proginfo[].
    s32ProgNum -= 1;

    s32Ret = HIADP_AVPlay_PlayProg(hAvplay, ProgTbl, s32ProgNum, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("call HIADP_AVPlay_PlayProg failed.\n");
        return ;
    }

    HI_TUNER_INFO("Play u32Vpid 0x%x u32Apid 0x%x\n", ProgTbl->proginfo[s32ProgNum].VElementPid, ProgTbl->proginfo[s32ProgNum].AElementPid);

    HI_TUNER_INFO("SUCCESS end\n");
    strcpy(s_acTestResult,HI_RESULT_SUCCESS);

    //�ж�����Ƶ�Ƿ����
    HI_TUNER_INFO("\n********************\n");
    if (0 == ProgTbl->proginfo[s32ProgNum].VElementPid)
    {
        //Don't have video, only audio
        HI_TUNER_INFO("Only radio program\n");
        return;
    }
    else
    {
        //Judge video Scrambled
        s32Ret = HI_UNF_AVPLAY_GetDmxVidChnHandle(hAvplay, &hDmxVidChn);
        if (HI_SUCCESS != s32Ret)
        {
            HI_TUNER_ERR("Get Dmx Vid channel failed.\n");
            return;
        }

        s32Ret = HI_UNF_DMX_GetScrambledFlag(hDmxVidChn, &enScrambleFlag);
        if (HI_SUCCESS != s32Ret)
        {
            HI_TUNER_ERR("Get srambled flag failed.\n");
            return;
        }
        if ((HI_UNF_DMX_SCRAMBLED_FLAG_TS == enScrambleFlag) || (HI_UNF_DMX_SCRAMBLED_FLAG_PES == enScrambleFlag))
        {
            HI_TUNER_INFO("\033[1;31;40m" "Video: Scrambled" "\033[0m\n");
        }
        else
        {
            HI_TUNER_INFO("Video: Unscrambled\n");
        }
    }

    if (0 == ProgTbl->proginfo[s32ProgNum].AElementPid)
    {
        //Don't have video, only audio
        HI_TUNER_INFO("Audio: None\n");
    }
    else
    {
        //Judge audio Scrambled
        s32Ret = HI_UNF_AVPLAY_GetDmxAudChnHandle(hAvplay, &hDmxAudChn);
        if (HI_SUCCESS != s32Ret)
        {
            HI_TUNER_ERR("Get Dmx Aud channel failed.\n");
            return;
        }
        s32Ret = HI_UNF_DMX_GetScrambledFlag(hDmxAudChn, &enScrambleFlag);
        if (HI_SUCCESS != s32Ret)
        {
            HI_TUNER_ERR("Get srambled flag failed.\n");
            return;
        }
        if ((HI_UNF_DMX_SCRAMBLED_FLAG_TS == enScrambleFlag) || (HI_UNF_DMX_SCRAMBLED_FLAG_PES == enScrambleFlag))
        {
            HI_TUNER_INFO("\033[1;31;40m" "Audio: Scrambled" "\033[0m\n");
        }
        else
        {
            HI_TUNER_INFO("Audio: Unscrambled\n");
        }
    }
    HI_TUNER_INFO("********************\n");
}


HI_VOID hi_tuner_getoffset()
{
    HI_U32 u32Symb;
    HI_U32 u32Freq;
    /*HI_U32 au32BER[3] = {0};
    HI_U32 u32SNR = 0;
    HI_U32 u32SignalStrength = 0;*/
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = HI_UNF_TUNER_GetRealFreqSymb(s_s32TunerPort, &u32Freq, &u32Symb );
    if ( HI_SUCCESS != s32Ret )
    {
        HI_TUNER_ERR("HI_UNF_TUNER_GetOffset failed\n");
        return;
    }
    HI_TUNER_INFO("freq = %d kHz, actul_symb = %d symbol/s\n",u32Freq, u32Symb);

    /*s32Ret = HI_UNF_TUNER_GetBER(s_s32TunerPort , au32BER);
    if ( HI_SUCCESS != s32Ret )
    {
        printf("HI_UNF_TUNER_GetBER failed\n");
        return;
    }
    printf("BER :%d.%de-%d\n", au32BER[0], au32BER[1], au32BER[2]);

    s32Ret = HI_UNF_TUNER_GetSNR(s_s32TunerPort, &u32SNR);
    if ( HI_SUCCESS != s32Ret )
    {
        printf("HI_UNF_TUNER_GetSNR failed\n");
        return;
    }
    printf("SNR :%d\n", u32SNR);

    s32Ret = HI_UNF_TUNER_GetSignalStrength(s_s32TunerPort, &u32SignalStrength);
    if ( HI_SUCCESS != s32Ret )
    {
        printf("HI_UNF_TUNER_GetSignalStrength failed\n");
        return;
    }
    printf("SignalStrength :%d\n", u32SignalStrength);*/

    return;
}


HI_VOID hi_tuner_change_ac_to_b(char *type)
{
    //HI_S32 s32Type = 0;
    char mode[10] = "";
    HI_S32 s32Ret = HI_FAILURE;
    HI_UNF_TUNER_ATTR_S stTunerAttr;

    if(type == HI_NULL_PTR)
    {
        printf("pointer null\n");
        return;
    }
    sscanf(type, "%s ", mode);
    printf("sizeof(mode)=%zu, strlen(mode)=%zu, mode=%s\n", sizeof(mode), strlen(mode), mode);

    s32Ret = HI_UNF_TUNER_GetAttr(s_s32TunerPort, &stTunerAttr);
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_UNF_TUNER_GetAttr fail\n");
        return;
    }
    //printf("type = %s \n", type);
    //printf("sizeof(type) = %d, strlen(type) = %d, %d\n", sizeof(type), strlen(type), strcmp(type, "j83b"));
    //if(0 == strcmp(type, "j83b"))
    //if(0 == strncmp(type, "j83b", (strlen(type) - 1)))
    if(0 == strcmp(mode, "j83b"))
    {
        printf("j83b\n");
        stTunerAttr.enDemodDevType = HI_UNF_DEMOD_DEV_TYPE_J83B;
        S_DEMOD_TYPE = HI_UNF_DEMOD_DEV_TYPE_J83B;
    }
    else
    {
        printf("j83ac\n");
        stTunerAttr.enDemodDevType = HI_UNF_DEMOD_DEV_TYPE_3130I;
        S_DEMOD_TYPE = HI_UNF_DEMOD_DEV_TYPE_3130I;
    }
    s32Ret = HI_UNF_TUNER_SetAttr(s_s32TunerPort, &stTunerAttr);
    if(HI_SUCCESS != s32Ret)
    {
        printf("HI_UNF_TUNER_SetAttr fail\n");
        return;
    }

    return;
}

/*typedef struct  hiAGC_TEST_S
{
    HI_U32      u32Port;
    HI_U32      u32Agc1;
    HI_U32      u32Agc2;
    HI_BOOL     bLockFlag;
    HI_BOOL     bAgcLockFlag;
    HI_U8       u8BagcCtrl12;
    HI_U32      u32Count;
}AGC_TEST_S;

extern HI_S32 HI_UNF_TUNER_TEST_SINGLE_AGC(HI_U32   u32tunerId , AGC_TEST_S  *pstAgcTest);

HI_VOID hi_tuner_single_agc()
{
    HI_S32 s32Ret = HI_FAILURE;
    AGC_TEST_S stAgcTest = { 0 };


    s32Ret = HI_UNF_TUNER_TEST_SINGLE_AGC(s_s32TunerPort, &stAgcTest);
    if ( HI_SUCCESS != s32Ret )
    {
        printf("hi_tuner_single_agc failed\n");
        return;
    }

    printf("lock = %d, agc_lock = %d, agc2 = %d,      BAGC_CTRL_12 = %d, end\n",
        stAgcTest.bLockFlag, stAgcTest.bAgcLockFlag , stAgcTest.u32Agc2, stAgcTest.u8BagcCtrl12 );

    return;
}*/

/*help function*/
HI_VOID hi_showhelp(char * pCmd)
{
    HI_U32 u32Loop = 0;
    HI_U32 u32CmdNum = sizeof(g_cmdhelp) / sizeof(CMD_HELP_S);

    if (pCmd == HI_NULL_PTR)
    {
        HI_TUNER_INFO("command list:\n");
        for (u32Loop = 0; u32Loop < u32CmdNum; u32Loop++)
        {
            HI_TUNER_INFO("%s:%s\n", g_cmdhelp[u32Loop].name, g_cmdhelp[u32Loop].help_info);
        }
        return;
    }

    for (u32Loop = 0; u32Loop < u32CmdNum; u32Loop++)
    {
        if (0 == strncmp(pCmd, g_cmdhelp[u32Loop].name, strlen(g_cmdhelp[u32Loop].name)))
        {
            HI_TUNER_INFO("%s", g_cmdhelp[u32Loop].help_info);
        }
    }
}

HI_VOID hi_tuner_setAntenaPower(char *power)
{
    HI_UNF_TUNER_TER_ANTENNA_POWER_E enPower;

    if (power == HI_NULL_PTR)
    {
        return;
    }

    sscanf(power, "%d",(HI_U32 *)&enPower);

    HI_TUNER_INFO("Set Antenna Power:%d\n",enPower);

    HI_UNF_TUNER_SetAntennaPower(s_s32TunerPort,enPower);
}

HI_VOID hi_tuner_monitor_layer(char * pPara)
{
    HI_UNF_TUNER_MONITOR_LAYERS_CONFIG_S stMonLayersConfig;
    HI_U32 u32Para;
    HI_S32 s32Ret = HI_SUCCESS;

    if (pPara == HI_NULL_PTR)
    {
        return;
    }

    sscanf(pPara, "%d", (HI_S32*)&u32Para);
    HI_TUNER_INFO("hi_tuner_monitor_ISDBT:%d\n", u32Para);

    memset(&stMonLayersConfig, 0, sizeof(HI_UNF_TUNER_MONITOR_LAYERS_CONFIG_S));
    stMonLayersConfig.enMonitorLayer = u32Para;

    s32Ret = HI_UNF_TUNER_MonitorISDBTLayer(s_s32TunerPort,&stMonLayersConfig);
    if (HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("HI_UNF_TUNER_MonitorISDBTLayer failed.\n");
    }

}

static HI_VOID hi_show_signal_type(HI_UNF_TUNER_SIG_TYPE_E enSigType, HI_CHAR **ppSignalType)
{
    switch(enSigType)
    {
        case HI_UNF_TUNER_SIG_TYPE_CAB:
            *ppSignalType = "DVBC ";
            break;
        case HI_UNF_TUNER_SIG_TYPE_SAT:
            *ppSignalType = "SAT ";
            break;
        case HI_UNF_TUNER_SIG_TYPE_DVB_T:
            *ppSignalType = "DVBT ";
            break;
        case HI_UNF_TUNER_SIG_TYPE_DVB_T2:
            *ppSignalType = "DVBT2 ";
            break;
        case HI_UNF_TUNER_SIG_TYPE_ISDB_T:
            *ppSignalType = "ISDBT ";
            break;
        case HI_UNF_TUNER_SIG_TYPE_ATSC_T:
            *ppSignalType = "ATSCT ";
            break;
        case HI_UNF_TUNER_SIG_TYPE_DTMB:
            *ppSignalType = "DTMB ";
            break;
        case HI_UNF_TUNER_SIG_TYPE_J83B:
            *ppSignalType = "J83B ";
            break;
        case HI_UNF_TUNER_SIG_TYPE_ABSS:
            *ppSignalType = "ABSS ";
            break;
        default:
            *ppSignalType = "Unknow ";
            break;
    }
}

static HI_VOID hi_show_demod_type(HI_UNF_DEMOD_DEV_TYPE_E enDemodDevType, HI_CHAR **ppDemodType)
{
    switch(enDemodDevType)
    {
        case HI_UNF_DEMOD_DEV_TYPE_3130I:
            *ppDemodType = "3130_inside";
            break;
        case HI_UNF_DEMOD_DEV_TYPE_3130E:
            *ppDemodType = "3130_outside";
            break;
        case HI_UNF_DEMOD_DEV_TYPE_J83B:
            *ppDemodType = "j83b";
            break;
        case HI_UNF_DEMOD_DEV_TYPE_AVL6211:
            *ppDemodType = "AVL6211";
            break;
        case HI_UNF_DEMOD_DEV_TYPE_MN88472:
            *ppDemodType = "MN88472";
            break;
        case HI_UNF_DEMOD_DEV_TYPE_MN88473:
            *ppDemodType = "MN88473";
            break;
        case HI_UNF_DEMOD_DEV_TYPE_3136:
            *ppDemodType = "Hi3136";
            break;
        case HI_UNF_DEMOD_DEV_TYPE_3137:
            *ppDemodType = "Hi3137";
            break;
        case HI_UNF_DEMOD_DEV_TYPE_MXL254:
            *ppDemodType = "MXL254";
            break;
        case HI_UNF_DEMOD_DEV_TYPE_MXL214:
            *ppDemodType = "MXL214";
            break;
        case HI_UNF_DEMOD_DEV_TYPE_TDA18280:
            *ppDemodType = "TDA18280";
            break;
        case HI_UNF_DEMOD_DEV_TYPE_ATBM888X:
            *ppDemodType = "ATBM888x";
            break;
        case HI_UNF_DEMOD_DEV_TYPE_MXL683:
            *ppDemodType = "MXL683";
            break;
        case HI_UNF_DEMOD_DEV_TYPE_TP5001:
            *ppDemodType = "TP5001";
            break;
        case HI_UNF_DEMOD_DEV_TYPE_HD2501:
            *ppDemodType = "HD2501";
            break;
        case HI_UNF_DEMOD_DEV_TYPE_AVL6381:
            *ppDemodType = "AVL6381";
            break;
        case HI_UNF_DEMOD_DEV_TYPE_MXL251:
            *ppDemodType = "MXL251";
            break;
        default:
            *ppDemodType = "Unknown";
            break;
    }
}

static HI_VOID hi_show_tuner_type(HI_UNF_TUNER_DEV_TYPE_E enTunerDevType, HI_CHAR **ppTunerType)
{
    HI_CHAR *acTunerName[] = {"Unsupport", "Unsupport", "Unsupport", "Unsupport", "TDA18250",
                              "Unsupport", "Unsupport", "Unsupport", "R820C",     "MXL203",
                              "AV2011",    "Unsupport", "Unsupport", "MXL603",    "Unsupport",
                              "Unsupport", "Unsupport", "TDA18250B", "Unsupport", "RDA5815",
                              "MXL254",    "Unsupport", "si2147",    "Rafael836", "MXL608",
                              "MXL214",    "TDA18280",  "TDA182I5A", "SI2144",    "AV2018",
                              "MXL251",    "Unsupport", "MXL601",    "MXL683",    "AV2026",
                              "R850",      "R858",      };


    HI_U32 u32TunerNum = sizeof(acTunerName) / sizeof(acTunerName[0]);  //���һ��"unkown TUNER"��������

    if (enTunerDevType < u32TunerNum - 1)
    {
        *ppTunerType = acTunerName[enTunerDevType];
    }
    else
    {
        *ppTunerType = "Unknown";
    }
}


HI_VOID hi_show_dev_info()
{
    HI_S32 i = 0;
    HI_S32 s32Ret = HI_FAILURE;
    HI_UNF_TUNER_ATTR_S stTunerAttr;
    HI_CHAR *pSignalType = HI_NULL;
    HI_CHAR *pDemodType = HI_NULL;
    HI_CHAR *pTunerType = HI_NULL;

    //printf("******************************************************************************\n");
    //printf("                              Channel Number: %d                           \n", HI_TUNER_NUMBER);
    for (i = 0; i < HI_TUNER_NUMBER; i++)
    {
         s32Ret = HIADP_Tuner_GetConfig(i, &stTunerAttr);
         if (HI_SUCCESS != s32Ret)
         {
            HI_TUNER_ERR("Get tuner config failed.\n");
            return;
         }

         hi_show_signal_type(stTunerAttr.enSigType, &pSignalType);
         hi_show_demod_type(stTunerAttr.enDemodDevType, &pDemodType);
         hi_show_tuner_type(stTunerAttr.enTunerDevType, &pTunerType);

         printf("******************************************************************************\n");
         printf("          |                      |                   |                       |\n");
         printf("Channel %d |    Demod = %-10s| Tuner = %-10s| Signal Type = %-8s|\n",
            i, pDemodType, pTunerType, pSignalType);
         printf("          |                      |                   |                       |\n");
         printf("******************************************************************************\n");
    }
}

/* set of received command */
TEST_FUNC_S g_testfunc[] =
{
    {"setport",         hi_tuner_selectCurrentPort},              /*���������ö˿ں�*/
    {"setchnl",         hi_tuner_setchannel},
    {"play",            hi_tuner_play },
    {"getsignalinfo",   hi_tuner_getsignalinfo  },
    {"getoffset",       hi_tuner_getoffset},
    //{"getber",        hi_tuner_getmsc_ber     },
    {"getmsc",          hi_tuner_getmsc},

    /* ���� */
    {"setlnbpower",     hi_tuner_setlnbpower    },
    {"setlnb",          hi_tuner_setlnb         },
    {"setvcm",          hi_tuner_setvcm},
    {"getvcm",          hi_tuner_getvcm},
    {"setscram",        hi_tuner_setscramble},
    {"blindscan",       hi_tuner_blindscan      },
    {"bsstop",          hi_tuner_blindscan_stop },
    {"cs",              hi_tuner_sample_data },
#ifdef DISEQC_SUPPORT
    {"switch",          hi_tuner_switch         },
    {"motor",           hi_tuner_motor          },
    {"unic",            hi_tuner_unicable_scan   },
#endif /* DISEQC_SUPPORT */

    /* ���� */
    /*{"setqam",        hi_tuner_setqam },*/
    /*{"setmode",       hi_tuner_change_ac_to_b},*/
    /*{"singleagc",     hi_tuner_single_agc},*/
    {"settype",         hi_tuner_settype},
    {"setsigtype",      hi_tuner_setsigtype        },

    /*T/T2�������*/
    {"terscan",         hi_tuner_ter_scan           },
    {"setplpid",        hi_tuner_setplpid         },
    {"ant",             hi_tuner_setAntenaPower},

    /*ISDB-T�������*/
    {"monitorlayer",    hi_tuner_monitor_layer},

    {"start",           hi_tuner_start},

    {"standby",         hi_tuner_standby        },

    {"help",            hi_showhelp}
};

/*search the handle function corresponding with the command in the character string */
Test_Func_Proc getFunbyName(char *name)
{
    HI_U32 u32Loop;
    HI_U32 u32FunNum = sizeof(g_testfunc) / sizeof(TEST_FUNC_S);

    if (HI_NULL_PTR == name)
    {
        return HI_NULL_PTR;
    }

    for (u32Loop = 0; u32Loop < u32FunNum; u32Loop++)
    {
        if (0 == strncmp(name, g_testfunc[u32Loop].name, strlen(g_testfunc[u32Loop].name)))
        {
            return g_testfunc[u32Loop].proc;
            HI_TUNER_WARN("here line:%d\n", __LINE__);
        }
    }

    return HI_NULL_PTR;
}

/*deals with the universal command */
HI_S32 procfun(char *funargs)
{
    char *argstr;
    Test_Func_Proc func;

    argstr = strchr(funargs, UDP_STR_SPLIT);
    if (HI_NULL_PTR != argstr)
    {
        *argstr = 0;
        argstr += 1;
    }

    func = getFunbyName(funargs);
    if (HI_NULL_PTR != func)
    {
        func(argstr);
        return HI_SUCCESS;
    }
    else
    {
        strcpy(s_acTestResult,HI_RESULT_FAIL" Can't find the function\n");
        HI_TUNER_ERR("Can't find the function  %s %s\n\n", funargs, argstr);
        return HI_FAILURE;
    }
}

int TestTCPOpen()
{
    HI_S32 s32SockFd = -1;
    struct sockaddr_in  stAddr;
    s32SockFd = socket(AF_INET,SOCK_STREAM,0);
    if(s32SockFd < 0)
    {
        HI_TUNER_ERR("Socket error...\n");
        return -1;
    }

    memset(&stAddr,0,sizeof(stAddr));
    stAddr.sin_family = AF_INET;
    stAddr.sin_addr.s_addr = INADDR_ANY;
    stAddr.sin_port = htons(DEFAULT_PORT);
    if(bind(s32SockFd,(struct sockaddr *)&stAddr,sizeof(struct sockaddr))<0)
    {
        close(s32SockFd);
        HI_TUNER_ERR("Bind error...\n");
        return -1;
    }

    listen(s32SockFd, 5);

    return s32SockFd;
}

void * tcprcv(void *arg)
{
    struct sockaddr_in stCliAddr;
    HI_S32 s32NewFd;
    HI_S32 s32Size;
    HI_S32 s32RcvLength;
    HI_CHAR acRecvBuf[MAX_CMD_BUFFER_LEN];
    HI_S32 s32Socketd = TestTCPOpen();
    HI_S32 s32Ret;
    if(s32Socketd < 0)
    {
        return (void *)0;
    }
    s32Size = sizeof(stCliAddr);
    if ( (s32NewFd = accept(s32Socketd, (struct sockaddr *) &stCliAddr, (socklen_t *)&s32Size)) < 0)
    {
        HI_TUNER_ERR("accept err\n");
        close(s32Socketd);
        return (void *)1;
    }
    HI_TUNER_INFO("accept socket %d\n",s32NewFd);

    while( 1)
    {
        s32RcvLength = read(s32NewFd, acRecvBuf, sizeof(acRecvBuf));
        if(s32RcvLength > 0)
        {
            acRecvBuf[s32RcvLength] = 0;
            HI_TUNER_INFO("receive cmd: %s\n",acRecvBuf);
            s32Ret = procfun(acRecvBuf);

            s_acTestResult[strlen(s_acTestResult)]= '\n';

            s32Ret = send(s32NewFd,  s_acTestResult, strlen(s_acTestResult), 0);
            if(s32Ret < 0)
            {
                HI_TUNER_WARN("send err:%s\n",strerror(errno));
            }
            HI_TUNER_INFO("%s result:%s\n",acRecvBuf,s_acTestResult);

            memset(s_acTestResult,0, sizeof(s_acTestResult));
            /*fflush(newfd);*/
        }
    }
}

HI_S32 main(HI_S32 argc, char *argv[])
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_CHAR acRecvBuf[MAX_CMD_BUFFER_LEN];
    HI_S32 s32Threadd;

    /* init device */
    s32Ret = dev_init();
    if(HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("%s: %d ErrorCode=0x%x\n", __FILE__, __LINE__, s32Ret);
        return s32Ret;
    }

    /*there are in Ret = HIADP_Snd_Init()*/
    /*AudioLineOutMuteCntrDisable();
    AudioSPDIFOutSharedEnable();*/

    /* init avplay */
    s32Ret = avplay_Init();
    if(HI_SUCCESS != s32Ret)
    {
        HI_TUNER_ERR("%s: %d ErrorCode=0x%x\n", __FILE__, __LINE__, s32Ret);
        return s32Ret;
    }

    pthread_create((pthread_t  *)&s32Threadd, 0, tcprcv, 0);

    /*print help*/
    hi_showhelp(HI_NULL);
    hi_show_dev_info();

    /* recieve command */
    while (1)
    {
        SAMPLE_GET_INPUTCMD(acRecvBuf);
        if (strlen(acRecvBuf) < 3)
        {
            usleep(10000);
            continue;
        }

        if (strncmp(acRecvBuf, "exit", 4) == 0)
        {
            break;
        }

        procfun(acRecvBuf);
    }

    /* deinit device */
    avplay_deinit();
    dev_deinit();

    return HI_SUCCESS;
}

