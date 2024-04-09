/******************************************************************************

  Copyright (C), 2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hal_otp.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __HAL_OTP_H__
#define __HAL_OTP_H__

#include "hi_common.h"
#include "hi_type.h"
#include "hi_error_mpi.h"

/**< Function trace log, strictly prohibited to expand */
#define HI_LOG_PrintFuncErr(Func, ErrCode)      HI_ERR_OTP("Call %s return [0x%08X]\n", #Func, ErrCode);
#define HI_LOG_PrintErrCode(ErrCode)            HI_ERR_OTP("Error Code: [0x%08X]\n", ErrCode);
#define HI_LOG_PrintWarnCode(ErrCode)            HI_WARN_OTP("Error Code: [0x%08X]\n", ErrCode);

#define OTP_CHECK_PARAM(val)  \
        do{ \
            if (val) \
            { \
                HI_ERR_OTP("param is invalid\n"); \
                return HI_ERR_OTP_INVALID_PARA;\
            }  \
        }while (0)

#define CHECK_NULL_PTR(ptr) \
        do {\
            if (NULL == (ptr))\
            {\
                HI_ERR_OTP("OTP('%s') is NULL.\n", # ptr); \
                return HI_ERR_OTP_PTR_NULL; \
            } \
        } while (0)

#define OTP_PrintErrorFunc(func,ret) HI_LOG_PrintFuncErr(func,ret)

#define OTP_PrintErrorCode(err) HI_LOG_PrintErrCode(err)

#define OTP_PrintWarnCode(err) HI_LOG_PrintWarnCode(err)

#define HI_LOG_D_FUNCTRACE (0)
#if HI_LOG_D_FUNCTRACE
#define HI_LOG_FuncEnter()                      HI_INFO_OTP(" =====>[Enter]\n")
#define HI_LOG_FuncExit()                       HI_INFO_OTP(" =====>[Exit]\n")
#else
#define HI_LOG_FuncEnter()
#define HI_LOG_FuncExit()
#endif

#define OTP_FUNC_ENTER   HI_LOG_FuncEnter
#define OTP_FUNC_EXIT   HI_LOG_FuncExit

#define OTP_BITS_PER_LONG 32
#define GENMASK_U(h, l) \
    (((~0U) << (l)) & (~0U >> (OTP_BITS_PER_LONG - 1 - (h))))
#define GENMASKREV_U(h, l) \
    ~(((~0U) << (l)) & (~0U >> (OTP_BITS_PER_LONG - 1 - (h))))


//PERM_CTRL register address
#define PERM_REG_BASE           (0xf8ab0000)
#define OTP_RW_CTRL             (PERM_REG_BASE + 0x4000)        //OTP MEM read and write control
#define OTP_RDATA               (PERM_REG_BASE + 0x4020)
#define OTP_WDATA               (PERM_REG_BASE + 0x4024)
#define OTP_RADDR               (PERM_REG_BASE + 0x4028)
#define OTP_WADDR               (PERM_REG_BASE + 0x402C)
#define OTP_CTR_ST0             (PERM_REG_BASE + 0x4034)        //OTP controller status
#define OTP_SH_UPDATE           (PERM_REG_BASE + 0x4040)        //Shadow register update request

#define RNG_BASE                      0xf8abc000
#define RNG_FIFO_DATA                 0x0204

/******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
typedef enum
{
    DRV_OTP_NO_FAKE_FLAG               = 0X00,
    DRV_OTP_GET_FAKE_BUFFER_FLAG       = 0X01,
    DRV_OTP_FAKE_BUFFER_FLAG           = 0X10,
    DRV_OTP_FAKE_BUFFER_RESET_FLAG     = 0X11,
    DRV_OTP_FAKE_ACCESS_ERR_FLAG       = 0X20,
    DRV_OTP_CLEAR_OTP_FAKE_BUFFER      = 0X30,
    DRV_OTP_FAKE_BUTT
}DRV_OTP_FAKE_FLAG_E;
#endif
/******* proc function end   ********/
typedef union
{
    struct
    {
        HI_U32 otp_init_rdy       : 1; //[0]
        HI_U32 soft_req_otp_rdy   : 1; //[1]
        HI_U32 prg_flag           : 1; //[2]
        HI_U32 rd_flag            : 1; //[3]
        HI_U32 err                : 1; //[4]
        HI_U32 prm_rd_fail        : 1; //[5]
        HI_U32 rd_fail            : 1; //[6]
        HI_U32 prog_disable       : 1; //[7]
        HI_U32 otp_init_err       : 1; //[8]
        HI_U32 reserved           : 23; //[23]
    } bits;
    HI_U32 u32;
} OTP_CTR_ST0_U;

#define OTP_STB_SECRETKEY_SPACE 0X280
#define OTP_STB_SECRETKEY_SPACE_LEN 0X80
#define OTP_CA_SECRETKEY_SPACE 0X400
#define OTP_CA_SECRETKEY_SPACE_LEN 0X200
#define OTP_HISI_SECRETKEY_SPACE 0X6C0
#define OTP_HISI_SECRETKEY_SPACE_LEN 0X10
#define ADDR_BETWEEN(addr, base, length) ((addr >= base) && (addr < base + length))
#define ADDR_OTP_READABLE(addr) \
    (!(ADDR_BETWEEN(addr, OTP_STB_SECRETKEY_SPACE, OTP_STB_SECRETKEY_SPACE_LEN) ||  \
     ADDR_BETWEEN(addr, OTP_CA_SECRETKEY_SPACE, OTP_CA_SECRETKEY_SPACE_LEN)   ||     \
     ADDR_BETWEEN(addr, OTP_HISI_SECRETKEY_SPACE, OTP_HISI_SECRETKEY_SPACE_LEN)))   \

#define OTP_READABLE( addr, value ) \
    do {                                              \
        HI_S32 read_ret = HI_FAILURE;                 \
        HI_U8 read_reg = 0;                           \
                                                      \
        read_ret = HAL_OTP_ReadByte(addr, &read_reg); \
        if((read_ret == HI_SUCCESS) &&                \
            (read_reg && value != value) &&            \
            ADDR_OTP_READABLE(addr))                  \
        {                                             \
            return HI_ERR_OTP_READABLE_FUSE_VERIFY;   \
        }                                             \
    } while (0)

HI_S32 HAL_OTP_Read(HI_U32 addr, HI_U32 *tdata);
HI_S32 HAL_OTP_ReadByte(HI_U32 addr, HI_U8 *tdata);
HI_S32 HAL_OTP_Init(HI_VOID);
HI_S32 HAL_OTP_Reset(HI_VOID);
HI_S32 HAL_OTP_ReadBitsOnebyte(HI_U32 addr, HI_U32 start_bit, HI_U32 bit_width, HI_U8 *value);
HI_S32 HAL_OTP_Write(HI_U32 addr,HI_U32 tdata);
HI_S32 HAL_OTP_WriteByte(HI_U32 addr,HI_U8 tdata);
HI_S32 HAL_OTP_WriteBit(HI_U32 addr, HI_U32 bit_pos, HI_U32  bit_value);
HI_S32 HAL_OTP_WriteBitsOnebyte(HI_U32 addr, HI_U32 start_bit, HI_U32 bit_width, HI_U8 value);
HI_U32 HAL_OTP_Export_Read(HI_U32 addr);
HI_U8 HAL_OTP_Export_ReadByte(HI_U32 addr);

#endif /* __HAL_OTP_H__ */
