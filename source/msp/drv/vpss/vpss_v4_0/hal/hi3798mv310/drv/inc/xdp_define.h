#ifndef _XDP_DEFINE_H_
#define _XDP_DEFINE_H_

#include "hi_type.h"

#define FPGA_TEST          1
#define VDP_CBB_FPGA       0
#define VDP_C_COMPILE      0

#define ERR_STOP

#define SYS_TEST           0
#define UT_TEST            0

#define EDA_TEST           (!(FPGA_TEST || VDP_CBB_FPGA || VDP_C_COMPILE))

typedef enum
{
    XDP_DATA_TYPE_SP_LINEAR = 0x0,
    XDP_DATA_TYPE_SP_TILE   = 0x1,
    XDP_DATA_TYPE_PACKAGE   = 0x2,
    XDP_DATA_TYPE_PLANAR    = 0x3,
    XDP_DATA_TYPE_BUTT
} XDP_DATA_TYPE_E;

typedef enum
{
    XDP_PROC_FMT_SP_420      = 0x0,
    XDP_PROC_FMT_SP_422      = 0x1,
    XDP_PROC_FMT_SP_444      = 0x2,//plannar,in YUV color domain
    XDP_PROC_FMT_SP_400      = 0x3,//plannar,in YUV color domain
    XDP_PROC_FMT_RGB_888     = 0x3,//package,in RGB color domain
    XDP_PROC_FMT_RGB_444     = 0x4,//plannar,in RGB color domain

    XDP_PROC_FMT_BUTT

} XDP_PROC_FMT_E;

typedef enum
{
    XDP_PKG_FMT_YUYV  = 0x0,
    XDP_PKG_FMT_YVYU  = 0x1,
    XDP_PKG_FMT_UYVY  = 0x2,
    XDP_PKG_FMT_VYUY  = 0x3,
    XDP_PKG_FMT_YYUV  = 0x4,
    XDP_PKG_FMT_YYVU  = 0x5,
    XDP_PKG_FMT_UVYY  = 0x6,
    XDP_PKG_FMT_VUYY  = 0x7,
    XDP_PKG_FMT_BUTT

} XDP_PKG_FMT_E;

typedef enum
{
    XDP_RMODE_INTERFACE   = 0,
    XDP_RMODE_INTERLACE   = 0,
    XDP_RMODE_PROGRESSIVE = 1,
    XDP_RMODE_TOP         = 2,
    XDP_RMODE_BOTTOM      = 3,
    XDP_RMODE_PRO_TOP     = 4,
    XDP_RMODE_PRO_BOTTOM  = 5,
    XDP_RMODE_BUTT

} XDP_DATA_RMODE_E;

typedef enum
{
    XDP_DATA_WTH_8  = 0,
    XDP_DATA_WTH_10 = 1,
    XDP_DATA_WTH_12 = 2,
    XDP_DATA_WTH_16 = 3,
    XDP_DATA_WTH_BUTT
} XDP_DATA_WTH;

typedef enum
{
    XDP_CMP_TYPE_OFF = 0,
    XDP_CMP_TYPE_SEG  ,
    XDP_CMP_TYPE_LINE ,
    XDP_CMP_TYPE_FRM  ,
    XDP_CMP_TYPE_BUTT
} XDP_CMP_TYPE_E;

typedef struct
{
    HI_U64 u64Addr;
    HI_U32 u32Str;
} XDP_SOLO_ADDR_S;

typedef struct
{
    HI_U64 u64LumAddr;
    HI_U64 u64ChmAddr;
    HI_U32 u32LumStr ;
    HI_U32 u32ChmStr ;
} XDP_DUO_ADDR_S;

typedef struct
{
    HI_U64 u64YAddr;
    HI_U64 u64UAddr;
    HI_U64 u64VAddr;
    HI_U32 u32YStr ;
    HI_U32 u32CStr ;
} XDP_TRIO_ADDR_S;

typedef struct
{
    HI_U32 u32X;
    HI_U32 u32Y;

    HI_U32 u32Wth;
    HI_U32 u32Hgt;

    HI_U32 u32SrcW;
    HI_U32 u32SrcH;

} XDP_RECT_S;

typedef enum
{
    XDP_REQ_LENGTH_16 = 0,
    XDP_REQ_LENGTH_8  = 1,
    XDP_REQ_LENGTH_BUTT
} XDP_REQ_LENGTH_E;

typedef enum
{
    XDP_REQ_CTRL_16BURST_1,
    XDP_REQ_CTRL_16BURST_2,
    XDP_REQ_CTRL_16BURST_4,
    XDP_REQ_CTRL_16BURST_8,
    XDP_REQ_CTRL_BUTT
} XDP_REQ_CTRL_E;

typedef struct
{
    HI_U32 u32BkgY;
    HI_U32 u32BkgU;
    HI_U32 u32BkgV;
    HI_U32 u32BkgA;
    HI_U32 bBkType;

} XDP_BKG_S;

//----------------------------------------------------------------------
// Platform define, EDA and FPGA is difference
//----------------------------------------------------------------------
#if !(FPGA_TEST)
#define XDP_ASSERT(expr) \
    if (!(expr)) { \
        cout << endl; \
        cout << "Assert Error at:" << endl; \
        cout << ">File name:" << __FILE__ << endl; \
        cout << ">Function :" << __FUNCTION__ << endl; \
        cout << dec << ">Line No. :" << __LINE__ << endl; \
        cout << ">Condition:" << #expr << endl; \
        exit(-1);\
    }
#else
#define XDP_ASSERT(expr) \
    if (!(expr)) { \
        printk("Assert Error at:\n"); \
        printk(">File name: %s.\n", __FILE__ ); \
        printk(">Function : %s.\n", __FUNCTION__ ); \
        printk(">Line No. : %d.\n", __LINE__ ); \
        printk(">Condition: %s.\n",#expr); \
        dump_stack(); \
    }
#endif

#if !(FPGA_TEST)
#define MyAssert(expr) \
    do{ \
        if (!(expr)) { \
            printf("\nAssert Error at:\n  >File name: %s\n  >Function : %s\n  >Line No. : %d\n  >Condition: %s\n", \
                   __FILE__,__FUNCTION__, __LINE__, #expr);\
            _exit(-1);\
        } \
    }while(0)
#else
//#define MyAssert(expr)
#endif

#if !(FPGA_TEST)
#define ASSERT(expr) \
    if (!(expr)) { \
        cout << endl; \
        cout << "Assert Error at:" << endl; \
        cout << ">File name:" << __FILE__ << endl; \
        cout << ">Function :" << __FUNCTION__ << endl; \
        cout << dec << ">Line No. :" << __LINE__ << endl; \
        cout << ">Condition:" << #expr << endl; \
        exit(-1);\
    }
#else
//#define ASSERT(expr)
#endif


#ifdef _DISP_PLATFORM_BOOT_
#define XDP_PRINT   printf
#else

#if (EDA_TEST || VDP_C_COMPILE)
#include <stdio.h>
#define XDP_PRINT   printf
#else
#define XDP_PRINT   printk
#endif

#endif//_DISP_PLATFORM_BOOT_

#endif

