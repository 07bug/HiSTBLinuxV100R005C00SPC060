/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_hal_acc.c
  Version       : Initial Draft
  Author        :
  Created       : 2016/09/23
  Description   :

******************************************************************************/
#include "hi_type.h"
#include "hi_debug.h"
#include "hi_drv_mmz.h"
#include "hi_drv_mem.h"

#include "pq_hal_acc.h"

#define ACC_HISTGRAM_0_ADDR   0xf8cc7230
#define ACC_HISTGRAM_1_ADDR   0xf8cc7240

HI_VOID PQ_HAL_SetAccAccEn(HI_U32 u32Data, HI_U32 acc_en)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACCTHD1 VHDACCTHD1;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAccAccEn Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACCTHD1.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACCTHD1.u32)) + u32Data * PQ_VID_OFFSET));
    VHDACCTHD1.bits.acc_en = acc_en;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACCTHD1.u32)) + u32Data * PQ_VID_OFFSET), VHDACCTHD1.u32);

    return;
}

HI_VOID PQ_HAL_SetAccAccMode(HI_U32 u32Data, HI_U32 acc_mode)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACCTHD1 VHDACCTHD1;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAccAccMode Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACCTHD1.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACCTHD1.u32)) + u32Data * PQ_VID_OFFSET));
    VHDACCTHD1.bits.acc_mode = acc_mode;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACCTHD1.u32)) + u32Data * PQ_VID_OFFSET), VHDACCTHD1.u32);

    return;
}

HI_VOID PQ_HAL_SetAccThdMedLow(HI_U32 u32Data, HI_U32 thd_med_low)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACCTHD1 VHDACCTHD1;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAccThdMedLow Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACCTHD1.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACCTHD1.u32)) + u32Data * PQ_VID_OFFSET));
    VHDACCTHD1.bits.thd_med_low = thd_med_low;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACCTHD1.u32)) + u32Data * PQ_VID_OFFSET), VHDACCTHD1.u32);

    return;
}

HI_VOID PQ_HAL_SetAccThdHigh(HI_U32 u32Data, HI_U32 thd_high)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACCTHD1 VHDACCTHD1;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAccThdHigh Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACCTHD1.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACCTHD1.u32)) + u32Data * PQ_VID_OFFSET));
    VHDACCTHD1.bits.thd_high = thd_high;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACCTHD1.u32)) + u32Data * PQ_VID_OFFSET), VHDACCTHD1.u32);

    return;
}

HI_VOID PQ_HAL_SetAccThdLow(HI_U32 u32Data, HI_U32 thd_low)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACCTHD1 VHDACCTHD1;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAccThdLow Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACCTHD1.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACCTHD1.u32)) + u32Data * PQ_VID_OFFSET));
    VHDACCTHD1.bits.thd_low = thd_low;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACCTHD1.u32)) + u32Data * PQ_VID_OFFSET), VHDACCTHD1.u32);

    return;
}

HI_VOID PQ_HAL_SetAccAccRst(HI_U32 u32Data, HI_U32 acc_rst)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACCTHD2 VHDACCTHD2;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAccAccRst Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACCTHD2.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACCTHD2.u32)) + u32Data * PQ_VID_OFFSET));
    VHDACCTHD2.bits.acc_rst = acc_rst;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACCTHD2.u32)) + u32Data * PQ_VID_OFFSET), VHDACCTHD2.u32);

    return;
}

HI_VOID PQ_HAL_SetAccDemoMode(HI_U32 u32Data, HI_U32 acc_dbg_mode)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACCDEMO VHDACCDEMO;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAccAccRst Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACCDEMO.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACCDEMO.u32)) + u32Data * PQ_VID_OFFSET));
    VHDACCDEMO.bits.demo_mode = acc_dbg_mode;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACCDEMO.u32)) + u32Data * PQ_VID_OFFSET), VHDACCDEMO.u32);

    return;
}

HI_VOID PQ_HAL_SetAccDemoEn(HI_U32 u32Data, HI_U32 acc_demo_en)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACCDEMO VHDACCDEMO;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAccAccRst Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACCDEMO.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACCDEMO.u32)) + u32Data * PQ_VID_OFFSET));
    VHDACCDEMO.bits.demo_en = acc_demo_en;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACCDEMO.u32)) + u32Data * PQ_VID_OFFSET), VHDACCDEMO.u32);

    return;
}

HI_VOID PQ_HAL_SetAccThdMedHigh(HI_U32 u32Data, HI_U32 thd_med_high)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACCTHD2 VHDACCTHD2;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAccThdMedHigh Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACCTHD2.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACCTHD2.u32)) + u32Data * PQ_VID_OFFSET));
    VHDACCTHD2.bits.thd_med_high = thd_med_high;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACCTHD2.u32)) + u32Data * PQ_VID_OFFSET), VHDACCTHD2.u32);

    return;
}

HI_VOID PQ_HAL_SetAccAccPixTotal(HI_U32 u32Data, HI_U32 acc_pix_total)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACCTOTAL VHDACCTOTAL;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAccAccPixTotal Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACCTOTAL.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACCTOTAL.u32)) + u32Data * PQ_VID_OFFSET));
    VHDACCTOTAL.bits.acc_pix_total = acc_pix_total;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACCTOTAL.u32)) + u32Data * PQ_VID_OFFSET), VHDACCTOTAL.u32);

    return;
}

HI_S32 PQ_HAL_SetAccPara(HI_U32 u32Data, PQ_HAL_ACC_PARA_S stAccPara)
{
    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, Select Wrong Layer ID\n");

        return HI_FAILURE;
    }

    PQ_HAL_SetAccAccEn(u32Data,   stAccPara.stAccCfg.acc_en);
    PQ_HAL_SetAccAccMode(u32Data, stAccPara.stAccCfg.acc_mode);
    PQ_HAL_SetAccDemoMode(u32Data, stAccPara.stAccCfg.acc_dbg_mode);
    PQ_HAL_SetAccDemoEn(u32Data,   stAccPara.stAccCfg.acc_dbg_en);
    PQ_HAL_SetAccAccRst(u32Data,  stAccPara.stAccCfg.acc_rst);

    PQ_HAL_SetAccThdMedLow(u32Data,   stAccPara.thd_med_low);
    PQ_HAL_SetAccThdHigh(u32Data,     stAccPara.thd_high);
    PQ_HAL_SetAccThdLow(u32Data,      stAccPara.thd_low);
    PQ_HAL_SetAccThdMedHigh(u32Data,  stAccPara.thd_med_high);

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetAccTab(HI_U32 u32Data, HI_U32 *upTable)
{
    S_VDP_REGS_TYPE *pstVdpReg  = HI_NULL;

    U_VHDACCLOW1           VHDACCLOW1                        ; /* 0x720c */
    U_VHDACCLOW2           VHDACCLOW2                        ; /* 0x7210 */
    U_VHDACCLOW3           VHDACCLOW3                        ; /* 0x7214 */
    U_VHDACCMED1           VHDACCMED1                        ; /* 0x7218 */
    U_VHDACCMED2           VHDACCMED2                        ; /* 0x721c */
    U_VHDACCMED3           VHDACCMED3                        ; /* 0x7220 */
    U_VHDACCHIGH1          VHDACCHIGH1                       ; /* 0x7224 */
    U_VHDACCHIGH2          VHDACCHIGH2                       ; /* 0x7228 */
    U_VHDACCHIGH3          VHDACCHIGH3                       ; /* 0x722c */

    pstVdpReg = PQ_HAL_GetVdpReg();

    VHDACCLOW1.u32 = 0;
    VHDACCLOW1.bits.low_table_data0 = upTable[0];
    VHDACCLOW1.bits.low_table_data1 = upTable[1];
    VHDACCLOW1.bits.low_table_data2 = upTable[2];
    PQ_HAL_RegWrite((HI_U32 *)(HI_ULONG)(&(pstVdpReg->VHDACCLOW1.u32)), VHDACCLOW1.u32);

    VHDACCLOW2.u32 = 0;
    VHDACCLOW2.bits.low_table_data3 = upTable[3];
    VHDACCLOW2.bits.low_table_data4 = upTable[4];
    VHDACCLOW2.bits.low_table_data5 = upTable[5];
    PQ_HAL_RegWrite((HI_U32 *)(HI_ULONG)(&(pstVdpReg->VHDACCLOW2.u32)), VHDACCLOW2.u32);

    VHDACCLOW3.u32 = 0;
    VHDACCLOW3.bits.low_table_data6 = upTable[6];
    VHDACCLOW3.bits.low_table_data7 = upTable[7];
    VHDACCLOW3.bits.low_table_data8 = upTable[8];
    PQ_HAL_RegWrite((HI_U32 *)(HI_ULONG)(&(pstVdpReg->VHDACCLOW3.u32)), VHDACCLOW3.u32);

    VHDACCMED1.u32 = 0;
    VHDACCMED1.bits.mid_table_data0 = upTable[9];
    VHDACCMED1.bits.mid_table_data1 = upTable[10];
    VHDACCMED1.bits.mid_table_data2 = upTable[11];
    PQ_HAL_RegWrite((HI_U32 *)(HI_ULONG)(&(pstVdpReg->VHDACCMED1.u32)), VHDACCMED1.u32);

    VHDACCMED2.u32 = 0;
    VHDACCMED2.bits.mid_table_data3 = upTable[12];
    VHDACCMED2.bits.mid_table_data4 = upTable[13];
    VHDACCMED2.bits.mid_table_data5 = upTable[14];
    PQ_HAL_RegWrite((HI_U32 *)(HI_ULONG)(&(pstVdpReg->VHDACCMED2.u32)), VHDACCMED2.u32);

    VHDACCMED3.u32 = 0;
    VHDACCMED3.bits.mid_table_data6 = upTable[15];
    VHDACCMED3.bits.mid_table_data7 = upTable[16];
    VHDACCMED3.bits.mid_table_data8 = upTable[17];
    PQ_HAL_RegWrite((HI_U32 *)(HI_ULONG)(&(pstVdpReg->VHDACCMED3.u32)), VHDACCMED3.u32);

    VHDACCHIGH1.u32 = 0;
    VHDACCHIGH1.bits.high_table_data0 = upTable[18];
    VHDACCHIGH1.bits.high_table_data1 = upTable[19];
    VHDACCHIGH1.bits.high_table_data2 = upTable[20];
    PQ_HAL_RegWrite((HI_U32 *)(HI_ULONG)(&(pstVdpReg->VHDACCHIGH1.u32)), VHDACCHIGH1.u32);

    VHDACCHIGH2.u32 = 0;
    VHDACCHIGH2.bits.high_table_data3 = upTable[21];
    VHDACCHIGH2.bits.high_table_data4 = upTable[22];
    VHDACCHIGH2.bits.high_table_data5 = upTable[23];
    PQ_HAL_RegWrite((HI_U32 *)(HI_ULONG)(&(pstVdpReg->VHDACCHIGH2.u32)), VHDACCHIGH2.u32);

    VHDACCHIGH3.u32 = 0;
    VHDACCHIGH3.bits.high_table_data6 = upTable[24];
    VHDACCHIGH3.bits.high_table_data7 = upTable[25];
    VHDACCHIGH3.bits.high_table_data8 = upTable[26];
    PQ_HAL_RegWrite((HI_U32 *)(HI_ULONG)(&(pstVdpReg->VHDACCHIGH3.u32)), VHDACCHIGH3.u32);

    return HI_SUCCESS;
}


HI_S32 PQ_HAL_GetACCHistgram(ACC_HISTGRAM_S *pstACCHist)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    HI_U32 i;
    HI_U32 u32TempValue = 0;
    if (pstACCHist == NULL)
    {
        HI_ERR_PQ("pstACCHist is null point!\n");
        return HI_FAILURE;
    }
    pstVdpReg = PQ_HAL_GetVdpReg();

    for (i = 0; i < ACC_HISTGRAM0_SIZE; i++)
    {
        (HI_VOID)PQ_HAL_ReadRegister(0, ACC_HISTGRAM_0_ADDR + i * 4, &u32TempValue);
        pstACCHist->u32HistGram0[i] = u32TempValue;
    }

    for (i = 0; i < ACC_HISTGRAM1_SIZE; i++)
    {
        (HI_VOID)PQ_HAL_ReadRegister(0, ACC_HISTGRAM_1_ADDR + i * 4, &u32TempValue);
        pstACCHist->u32HistGram1[i] = u32TempValue;
    }

    return HI_SUCCESS;
}
