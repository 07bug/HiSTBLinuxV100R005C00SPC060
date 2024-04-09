#ifndef __XDP_IP_HEAD_H__
#define __XDP_IP_HEAD_H__

//===========================
// include head
//===========================

#ifdef XDP_VPSS_FPGA
#include "vpss_stt.h"
#include "vpss_hal_getreg.h"
#else
#include "vpss_common.h"
#endif


#include "vpss_hal_sysctrl.h"
#include "vpss_hal_ip_mmu.h"
#include "vpss_hal_ip_master.h"
#include "vpss_hal_ip_rchn.h"
#include "vpss_hal_ip_wchn.h"
#include "vpss_hal_mac_ctrl.h"
#include "vpss_hal_scanctrl.h"
#include "vpss_hal_reg.h"
#include "xdp_drv_ip_mmu.h"
#include "vpss_drv_ip_mmu.h"
#include "vpss_drv_ip_master.h"
#include "vpss_drv_comm.h"
#include "vpss_func_mac_rchn.h"
#include "vpss_func_mac_wchn.h"







//==========================
// macro define
//==========================

#ifdef XDP_VPSS_FPGA
#define VPSS_FATAL printk
#endif
//==========================
// type define
//==========================


//==========================
//extern global var declare
//==========================



//=========================
//function declare
//=========================



#endif
