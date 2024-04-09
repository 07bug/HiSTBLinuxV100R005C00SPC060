#include <linux/timer.h>
#include "vpss_drv_comm.h"
#if EDA_TEST
#include <stdlib.h>
#include <iostream>
using namespace std;
#endif

//VPSS_COEF_ADDR_S gstVpssCoefBufAddr;
HI_S32 rand(HI_VOID)
{
    struct timeval stTime;

    do_gettimeofday(&stTime);
    return (HI_S32)((HI_S32)(stTime.tv_usec) * (HI_S32)(stTime.tv_sec));
}

//----------------------------------------------------------------------
// ut functions
//----------------------------------------------------------------------
HI_U32 uGetRandEx(HI_U32 max, HI_U32 min)
{
    HI_U32 u32_max_data = 0;
    HI_U32 u32_min_data = 0;

    if (max > min)
    {
        u32_max_data = max;
        u32_min_data = min;
    }
    else
    {
        u32_max_data = min;
        u32_min_data = max;
    }

    return (u32_min_data + rand() % (u32_max_data + 1 - u32_min_data));
}

HI_S32 sGetRandEx(HI_S32 max, HI_S32 min)
{
    HI_U32 u32_max_data = 0;
    HI_U32 u32_min_data = 0;

    HI_S32 s32_return_data = 0;

    if (((max == 0) && (min == 0)) || (min == max))
    {
        return min;
        //#if EDA_TEST
        //        cout << "Error, Worng sRand seed!" << endl;
        //#endif
    }
    if (((max >= 0) && (min > 0)) || ((max > 0) && (min >= 0)))
    {
        if (max > min)
        {
            u32_max_data = max;
            u32_min_data = min;
        }
        else
        {
            u32_max_data = min;
            u32_min_data = max;
        }

        s32_return_data = (u32_min_data + rand() % (u32_max_data + 1 - u32_min_data));
    }
    else if (((max <= 0) && (min < 0)) || ((max < 0) && (min <= 0)))
    {
        if (abs(max) > abs(min))
        {
            u32_max_data = abs(max);
            u32_min_data = abs(min);
        }
        else
        {
            u32_max_data = abs(min);
            u32_min_data = abs(max);
        }

        s32_return_data = -(u32_min_data + rand() % (u32_max_data + 1 - u32_min_data));
    }
    else
    {
        if ((max > 0) && (min < 0))
        {
            u32_max_data = abs(max);
            u32_min_data = abs(min);
        }
        else
        {
            u32_max_data = abs(min);
            u32_min_data = abs(max);
        }

        if (rand() % 2 == 0)
        {
            s32_return_data = -(rand() % (u32_min_data + 1));
        }
        else
        {
            s32_return_data =    rand() % (u32_max_data + 1);
        }
    }

    return s32_return_data;
}
#if 0
unsigned int uGetRand(unsigned int low, unsigned high)
{
    return rand() % (high - low + 1) + low;
}

int sGetRand(int low, int high)
{
    return rand() % (high - low + 1) + low;
}
#endif

VPSS_ADDR_CFG_S  gstVpssAddrCfg;

HI_VOID VPSS_AddrInit(VPSS_ADDR_CFG_S *pstVpssAddrCfg, HI_U64 u64BaseAddr)
{
    HI_U64 ii = 0;
    HI_U64 u32MaxWth  = 4096  ;
    HI_U64 u32MaxHgt  = 2304  ;
    HI_U64 u32YStr    = u32MaxWth * 2 * 10 / 8;
    HI_U64 u32CStr    = u32MaxWth * 2 * 10 / 8;
    HI_U64 u64AddrSeg = ((u32YStr + u32CStr) * u32MaxHgt);

    memset(pstVpssAddrCfg, 0, sizeof(VPSS_ADDR_CFG_S));

    for (ii = 0; ii < VPSS_RCHN_MAX ; ii++)
    {
        pstVpssAddrCfg->stRchnAddr[ii].u64YAddr = u64BaseAddr + ii * u64AddrSeg;
        pstVpssAddrCfg->stRchnAddr[ii].u64UAddr = u64BaseAddr + ii * u64AddrSeg + u32YStr * u32MaxHgt  ;
        pstVpssAddrCfg->stRchnAddr[ii].u64VAddr = u64BaseAddr + ii * u64AddrSeg + u32YStr * u32MaxHgt * 2;
        pstVpssAddrCfg->stRchnAddr[ii].u32YStr  = u32YStr ;
        pstVpssAddrCfg->stRchnAddr[ii].u32CStr  = u32CStr ;
    }

    u64BaseAddr = u64BaseAddr + VPSS_RCHN_MAX * u64AddrSeg;

    for (ii = 0; ii < VPSS_WCHN_MAX ; ii++)
    {
        pstVpssAddrCfg->stWchnAddr[ii].u64YAddr = u64BaseAddr + ii * u64AddrSeg;
        pstVpssAddrCfg->stWchnAddr[ii].u64UAddr = u64BaseAddr + ii * u64AddrSeg + u32YStr * u32MaxHgt  ;
        pstVpssAddrCfg->stWchnAddr[ii].u64VAddr = u64BaseAddr + ii * u64AddrSeg + u32YStr * u32MaxHgt * 2;
        pstVpssAddrCfg->stWchnAddr[ii].u32YStr  = u32YStr ;
        pstVpssAddrCfg->stWchnAddr[ii].u32CStr  = u32CStr ;
    }

#if EDA_TEST
    cout << "================VPSS_ADDR_INIT=====================" << endl;

    for (ii = 0; ii < VPSS_RCHN_MAX ; ii++)
    {
        cout << dec << "[drv]pstVpssAddrCfg->stRchnAddr[" << ii << "].u64YAddr = 0x" << hex << pstVpssAddrCfg->stRchnAddr[ii].u64YAddr << endl;
        cout << dec << "[drv]pstVpssAddrCfg->stRchnAddr[" << ii << "].u64UAddr = 0x" << hex << pstVpssAddrCfg->stRchnAddr[ii].u64UAddr << endl;
        cout << dec << "[drv]pstVpssAddrCfg->stRchnAddr[" << ii << "].u64VAddr = 0x" << hex << pstVpssAddrCfg->stRchnAddr[ii].u64VAddr << endl;
        cout << dec << "[drv]pstVpssAddrCfg->stRchnAddr[" << ii << "].u32YStr  = 0x" << hex << pstVpssAddrCfg->stRchnAddr[ii].u32YStr  << endl;
        cout << dec << "[drv]pstVpssAddrCfg->stRchnAddr[" << ii << "].u32CStr  = 0x" << hex << pstVpssAddrCfg->stRchnAddr[ii].u32CStr  << endl;
    }

    for (ii = 0; ii < VPSS_WCHN_MAX ; ii++)
    {
        cout << dec << "[drv]pstVpssAddrCfg->stWchnAddr[" << ii << "].u64YAddr = 0x" << hex << pstVpssAddrCfg->stWchnAddr[ii].u64YAddr << endl;
        cout << dec << "[drv]pstVpssAddrCfg->stWchnAddr[" << ii << "].u64UAddr = 0x" << hex << pstVpssAddrCfg->stWchnAddr[ii].u64UAddr << endl;
        cout << dec << "[drv]pstVpssAddrCfg->stWchnAddr[" << ii << "].u64VAddr = 0x" << hex << pstVpssAddrCfg->stWchnAddr[ii].u64VAddr << endl;
        cout << dec << "[drv]pstVpssAddrCfg->stWchnAddr[" << ii << "].u32YStr  = 0x" << hex << pstVpssAddrCfg->stWchnAddr[ii].u32YStr  << endl;
        cout << dec << "[drv]pstVpssAddrCfg->stWchnAddr[" << ii << "].u32CStr  = 0x" << hex << pstVpssAddrCfg->stWchnAddr[ii].u32CStr  << endl;
    }

    cout << "================VPSS_ADDR_INIT=====================" << endl << endl;
#endif

    return;
}

HI_U32 VpssCalcChmWth(HI_U32 u32LumWth, XDP_PROC_FMT_E enDataFmt)
{
    HI_U32 u32ChmWth = 0;
    switch (enDataFmt)
    {
        case XDP_PROC_FMT_SP_420:
        case XDP_PROC_FMT_SP_422:
        {
            XDP_ASSERT((u32LumWth % 2) == 0);
            u32ChmWth = u32LumWth / 2;
            break;
        }
        case XDP_PROC_FMT_SP_444:
        {
            u32ChmWth = u32LumWth;
            break;
        }
        case XDP_PROC_FMT_SP_400:
        {
            u32ChmWth = 0;
            break;
        }
        default: XDP_ASSERT(0);
    }
    return u32ChmWth;
}

HI_U32 VpssCalcChmHgt(HI_U32 u32LumHgt, XDP_PROC_FMT_E enDataFmt)
{
    HI_U32 u32ChmHgt = 0;
    switch (enDataFmt)
    {
        case XDP_PROC_FMT_SP_420:
        {
            XDP_ASSERT((u32LumHgt % 2) == 0);
            u32ChmHgt = u32LumHgt / 2;
            break;
        }
        case XDP_PROC_FMT_SP_422:
        case XDP_PROC_FMT_SP_444:
        {
            u32ChmHgt = u32LumHgt;
            break;
        }
        case XDP_PROC_FMT_SP_400:
        {
            u32ChmHgt = 0;
            break;
        }
        default: XDP_ASSERT(0);
    }
    return u32ChmHgt;
}

HI_U64 VpssUpAlign(HI_U64 u64DataIn, HI_U64 u64Align)
{
    HI_U64 u64DataOut = u64DataIn;
    XDP_ASSERT(u64Align > 0);
    //u64DataOut = (u64DataIn + u64Align - 1)/u64Align*u64Align;
    u64DataOut = div_u64((u64DataIn + u64Align - 1), u64Align) * u64Align;
    return u64DataOut;
}

HI_U64 VpssDownAlign(HI_U64 u64DataIn, HI_U64 u64Align)
{
    HI_U64 u64DataOut = u64DataIn;
    XDP_ASSERT(u64Align > 0);
    //u64DataOut = (u64DataIn)/u64Align*u64Align;
    u64DataOut = div_u64(u64DataIn, u64Align) * u64Align;
    return u64DataOut;
}

HI_U64 VPSS_CalcAddrStr(XDP_SOLO_ADDR_S *pstAddr, XDP_RECT_S *pstRect, HI_U32 u32DataWidth, HI_BOOL bRandModeEn)
{
    HI_U64  u64AddrSeg    = 0 ;
    HI_U32  u32AlignByte  = 16;

    pstAddr->u32Str = VpssUpAlign((pstRect->u32Wth * u32DataWidth + 7) / 8, u32AlignByte);

    if (bRandModeEn)
    {
        pstAddr->u32Str += uGetRandEx(0, 15) * u32AlignByte;
    }

    u64AddrSeg = pstAddr->u32Str * pstRect->u32Hgt;
    pstAddr->u64Addr += u64AddrSeg;

    return u64AddrSeg;
}


