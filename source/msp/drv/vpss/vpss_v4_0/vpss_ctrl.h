#ifndef __VPSS_CTRL_H__
#define __VPSS_CTRL_H__

#include <linux/list.h>
#include "vpss_instance.h"
#include "vpss_fb.h"
#include "vpss_osal.h"
#include "hi_drv_dev.h"
#include <linux/completion.h>
#include <linux/semaphore.h>
#include <linux/rwlock.h>


#define VPSS0_IRQ_NUM                   125  //93+32
#define VPSS1_IRQ_NUM                   110  //78+32

#if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310)
#ifdef HI_FPGA_SUPPORT
//keep this macro equal to VPSS_CPU_INDEX value defined in drv_sys_ext_k.c!!!
#ifndef HI_TEE_SUPPORT
#define VPSS_CPU_INDEX                  1
#else
#define VPSS_CPU_INDEX                  0
#endif
#endif
#endif

#define VPSS_GET_IP(hVPSS) (hVPSS / VPSS_INSTANCE_MAX_NUMB)
#define VPSS_GET_INST_POS(hVPSS) (hVPSS % VPSS_INSTANCE_MAX_NUMB)

typedef struct completion VPSS_IRQ_LOCK;
typedef struct semaphore  VPSS_INSTLIST_LOCK;
typedef  struct task_struct    *VPSS_THREAD;

typedef struct hiVPSS_EXP_CTRL_S
{
    rwlock_t stListLock;

    // HI_U32 u32Target;

    HI_U32 u32InstanceNum;

    VPSS_INSTANCE_S *pstInstPool[VPSS_INSTANCE_MAX_NUMB];

} VPSS_INST_CTRL_S;

typedef enum hiVPSS_TASK_STATE_E
{
    TASK_STATE_READY = 0,
    TASK_STATE_WAIT,
    TASK_STATE_IDLE,
    TASK_STATE_BUTT
} VPSS_TASK_STATE_E;

typedef struct hiVPSS_TASK_S
{
    //VPSS_TASK_STATE_E stState;

    // VPSS_INSTANCE_S *pstInstance;

    HI_U32 u32SucRate;
    HI_U32 u32LastTotal;
    HI_U32 u32SuccessTotal;
    HI_U32 u32Create;
    HI_U32 u32Fail;
    HI_U32 u32TimeOut;
#ifdef VPSS_SUPPORT_OUT_TUNNEL
    HI_BOOL bOutLowDelay;
#endif

} VPSS_TASK_S;

typedef irqreturn_t (*FN_VPSS_InterruptRoute)(HI_S32 irq, HI_VOID *dev_id);

typedef struct hiVPSS_CTRL_THREAD_STATE_S
{
    volatile HI_U32     u32NeedSleep;
    volatile HI_U32     u32Position;
    VPSS_THREAD         hThread;
} VPSS_CTRL_THREAD_STATE_S;


typedef struct hiVPSS_CTRL_S
{
    HI_BOOL         bIPVaild;
    VPSS_IP_E       enIP;
    HI_U32          u32VpssIrqNum;
    HI_CHAR         isr_name[30];
    FN_VPSS_InterruptRoute pVpssIntService;

    HI_U32          s32IsVPSSOpen;

    OSAL_EVENT      stEventLogicDone;
    OSAL_EVENT      stEventInstanceListReady;
    OSAL_EVENT      stEventInstanceListDone;
#ifdef VPSS_SUPPORT_OUT_TUNNEL
    OSAL_EVENT      stEventOutTunnel;
    HI_S32          s32OutTunelInstanceCnt;
    HI_S32          s32OutTunnelInterruptCnt;
    HI_BOOL         bLogicDone;
    VPSS_OSAL_SPIN  stOutTunnelSpin;
#ifdef VPSS_SUPPORT_OUT_TUNNEL_DBG
    HI_S32          s32OutTunnelCntDbg;
    HI_S32          s32OutTunnelIntCntDbg;
    HI_S32          s32OutTunelEvtCreateCntDbg;
    HI_S32          s32OutTunelEvtDoneCntDbg;
    HI_S32          s32OutTunelEvtResetCntDbg;
#endif
#endif
    VPSS_TASK_S     stTask;
    HI_BOOL         bSuspend;

    HI_BOOL         bInMCE;

    HI_HANDLE       hVpssIRQ;

    VPSS_CTRL_THREAD_STATE_S logic;
    VPSS_CTRL_THREAD_STATE_S software;

#ifndef ZME_2L_TEST
    VPSS_BUFFER_S stRoBuf[DEF_HI_DRV_VPSS_PORT_MAX_NUMBER];
#endif
    VPSS_INST_CTRL_S  stInstCtrlInfo;

    HI_S32  s32RunInstCnt;
} VPSS_CTRL_S;

irqreturn_t VPSS0_CTRL_IntService(HI_S32 irq, HI_VOID *dev_id);
irqreturn_t VPSS1_CTRL_IntService(HI_S32 irq, HI_VOID *dev_id);
HI_S32 VPSS_CTRL_ProcRead(struct seq_file *p, HI_VOID *v);
HI_S32 VPSS_CTRL_ProcWrite(struct file *file,
                           const char __user *buf, size_t count, loff_t *ppos);


HI_S32 VPSS_CTRL_Init(HI_VOID);
HI_S32 VPSS_CTRL_DelInit(HI_VOID);
HI_S32 VPSS_CTRL_SetMceFlag(HI_BOOL bInMCE);
VPSS_HANDLE VPSS_CTRL_CreateInstance(HI_DRV_VPSS_CFG_S *pstVpssCfg);
HI_S32 VPSS_CTRL_DestoryInstance(VPSS_HANDLE hVPSS);
VPSS_INSTANCE_S *VPSS_CTRL_GetInstance(VPSS_HANDLE hVPSS);
HI_S32 VPSS_CTRL_SyncDistributeIP(VPSS_INSTANCE_S *pstInstance, HI_DRV_VPSS_IPMODE_E enIpmode);
HI_S32 VPSS_CTRL_WakeUpThread(HI_VOID);
HI_S32 VPSS_CTRL_Pause(VPSS_HANDLE hVPSS);
HI_S32 VPSS_CTRL_Resume(VPSS_HANDLE hVPSS);

HI_S32 VPSS_CTRL_GetInstanceNumber(VPSS_IP_E enIp, HI_U32 *pu32Number);

VPSS_INSTANCE_S *VPSS_CTRL_GetOnlyInstance(VPSS_IP_E enIp);
HI_S32 VPSS_CTRL_GetInstanceCnt(VPSS_IP_E enIp);

#endif
